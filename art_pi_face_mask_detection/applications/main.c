/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-02     RT-Thread    first version
 * 2021-07-22     K_Wang       adapt to mask detection
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "drv_spi_ili9488.h"  // spi lcd driver
#include <lcd_spi_port.h>  // lcd ports
#include <rt_ai_mask_model.h>
#include <rt_ai.h>
#include <backend_cubeai.h>

struct rt_event ov2640_event;
struct rt_event show_event;
#define WITH_MASK_FLAG (1)
#define WITHOUT_MASK_FLAG (1<<2)

rt_uint8_t *input_gray;
rt_uint8_t *input_r_128;
rt_uint8_t *input_g_128;
rt_uint8_t *input_b_128;
rt_uint8_t *input_128;
rt_uint8_t *r;
rt_uint8_t *g;
rt_uint8_t *b;

float *input_buf;
rt_uint8_t ai_flag = 0;
char *mask_label[] = {"With Mask", "Without Mask"};

extern void DCMI_Start();
extern int rt_gc0328c_init();
static inline void _itof(float *dst,rt_uint8_t *src, uint32_t size, float div);
void rgbsplit(unsigned char *src, unsigned char *r, unsigned char *g, unsigned char *b, int width, int height);
void rgbcombine(unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *dsp, int width, int height);
void bilinera_interpolation(rt_uint8_t* in_array, short height, short width, rt_uint8_t* out_array, short out_height, short out_width);
void ai_run_complete(void *arg);

rt_thread_t tid = RT_NULL;

void print_mask_entry(void *param)
{
    while(1)
    {
        rt_event_recv(&show_event, WITH_MASK_FLAG, RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, RT_NULL);
        lcd_show_string(40, 240, 32, "Mask prediction:");
        lcd_show_string(40, 275, 32, "With Mask   ");
        rt_thread_mdelay(1000);
    }
    return;
}

void print_no_mask_entry(void *param)
{
    while(1)
    {
        rt_event_recv(&show_event, WITHOUT_MASK_FLAG, RT_EVENT_FLAG_OR|RT_EVENT_FLAG_CLEAR, RT_WAITING_FOREVER, RT_NULL);
        lcd_show_string(40, 240, 32, "Mask prediction:");
        lcd_show_string(40, 275, 32, "Without Mask");
        rt_thread_mdelay(1000);
    }
    return;
}

//yolo_region_layer r1;
void ai_camera();

int main(void)
{

    input_gray = rt_malloc(320*240*3);
    input_128 = rt_malloc(128*128*3);
    input_buf = rt_malloc(128*128*3*sizeof(float));
    r = rt_malloc(320*240);
    g = rt_malloc(320*240);
    b = rt_malloc(320*240);
    input_r_128 = rt_malloc(128*128);
    input_g_128 = rt_malloc(128*128);
    input_b_128 = rt_malloc(128*128);

    /* init spi data notify event */
    rt_event_init(&ov2640_event, "ov2640", RT_IPC_FLAG_FIFO);
    struct drv_lcd_device *lcd;
    lcd = (struct drv_lcd_device *)rt_device_find("lcd");
    struct rt_device_rect_info rect_info = {0, 0, LCD_WIDTH, 240};
    lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
//    int ai_run_complete_flag = 0;

    // find ai model handle
    rt_ai_t person_d = NULL;
    person_d = rt_ai_find(RT_AI_MASK_MODEL_NAME);
    if(!person_d) {rt_kprintf("ai find err\n"); return -1;}
    // alloc calculate mem
    rt_ai_buffer_t *work_buf = rt_malloc(RT_AI_MASK_WORK_BUFFER_BYTES);
    if(!work_buf) {rt_kprintf("malloc err\n");return -1;}
    // ai out
    rt_ai_buffer_t *_out = rt_malloc(RT_AI_MASK_OUT_1_SIZE_BYTES);
    if(!_out) {rt_kprintf("malloc err\n"); return -1;}

    if(rt_ai_init(person_d,work_buf) != 0){rt_kprintf("ai init err\n"); return -1;}
    rt_ai_config(person_d,CFG_INPUT_0_ADDR,(rt_ai_buffer_t*)input_buf);
    rt_ai_config(person_d,CFG_OUTPUT_0_ADDR,_out);
    ai_camera();


    rt_event_init(&show_event, "detect mask", RT_IPC_FLAG_PRIO);

    //创建输出戴口罩线程
    tid = rt_thread_create("show mask", print_mask_entry, (void*)0, 1024, 16, 20);
    if(tid == RT_NULL)
    {
        rt_kprintf("show thread error!\r\n");
        return -1;
    }
    rt_thread_startup(tid);

    //创建输出没带口罩线程
    rt_thread_t tid = RT_NULL;
    tid = rt_thread_create("show no mask", print_no_mask_entry, (void*)0, 1024, 16, 20);
    if(tid == RT_NULL)
    {
        rt_kprintf("show thread error!\r\n");
        return -1;
    }
    rt_thread_startup(tid);

    while(1){
        rt_event_recv(&ov2640_event, 1, (RT_EVENT_FLAG_AND | RT_EVENT_FLAG_CLEAR), RT_WAITING_FOREVER, RT_NULL);
        lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        if(ai_flag >= 0){
            rgbsplit(lcd->lcd_info.framebuffer, r, g, b, 320, 240);
            bilinera_interpolation(r, 240, 320, input_r_128, 128, 128);
            bilinera_interpolation(g, 240, 320, input_g_128, 128, 128);
            bilinera_interpolation(b, 240, 320, input_b_128, 128, 128);
            rgbcombine(input_r_128, input_g_128, input_b_128, input_buf, 128, 128);


//            _itof(input_buf,input_128, 128*128*3, 255.0);
            rt_ai_run(person_d, NULL, NULL);

            uint8_t *out = (uint8_t *)rt_ai_output(person_d, 0);
            //get argmax
            int max_index = 0;
            if(out[1] > out[max_index]){
                max_index = 1;
            }

            rt_kprintf("MASK prediction: %s\n", mask_label[max_index]);
            rt_kprintf("predict out [%d %d %d %d %d %d %d %d %d %d]\r\n", out[0], out[1], out[2], out[3], out[4], out[5], out[6], out[7], out[8], out[9]);
            if(max_index) {
                rt_kprintf("send no mask event.\r\n");
                rt_event_send(&show_event, WITHOUT_MASK_FLAG);
            }
            else {
                rt_kprintf("show wear mask event.\r\n");
                rt_event_send(&show_event, WITH_MASK_FLAG);
            }
            lcd->parent.control(&lcd->parent, RTGRAPHIC_CTRL_RECT_UPDATE, &rect_info);
        DCMI_Start();
        }
    }

    return RT_EOK;
}

#include "stm32h7xx.h"
static int vtor_config(void)
{
   /* Vector Table Relocation in Internal QSPI_FLASH */
   SCB->VTOR = QSPI_BASE;
   return 0;
}
INIT_BOARD_EXPORT(vtor_config);


void ai_camera()
{
    rt_gc0328c_init();
    ai_flag = 1;
    DCMI_Start();
}
// MSH_CMD_EXPORT(ai_camera, Start the AI camera to recognize person);

static inline void _itof(float *dst,rt_uint8_t *src, uint32_t size, float div){
    if (div == 0){
        return ;
    }else{
        int i = 0;
        for(i = 0; i < size; i++){
            dst[i] = (float)src[i] / div;
        }
    }
}

// img covnert to gray: Gray = 0.2989*R + 0.5870*G + 0.1140*B
// better: 4898*R + 9618*G + 1868*B >> 14
// int8: 76*R + 150*G + 30*B >> 8
void rgbsplit(unsigned char *src, unsigned char *r, unsigned char *g, unsigned char *b, int width, int height)
{
    for (int i=0; i<width*height; ++i)
    {
        *r++ = *src++; // load red
        *g++ = *src++; // load green
        *b++ = *src++; // load blue
    }
}

void rgbcombine(unsigned char *r, unsigned char *g, unsigned char *b, rt_uint8_t *dsp, int width, int height)
{
    for (int i=0; i<width*height; ++i)
    {
        *dsp++ = *r++; // load red
        *dsp++ = *g++; // load green
        *dsp++ = *b++; // load blue
        // build weighted average:
    }
}

int is_in_array(short x, short y, short height, short width)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return 1;
    else
        return 0;
}

void bilinera_interpolation(rt_uint8_t* in_array, short height, short width,
                            rt_uint8_t* out_array, short out_height, short out_width)
{
    double h_times = (double)out_height / (double)height,
           w_times = (double)out_width / (double)width;
    short  x1, y1, x2, y2, f11, f12, f21, f22;
    double x, y;

    for (int i = 0; i < out_height; i++){
        for (int j = 0; j < out_width; j++){
            x = j / w_times;
            y = i / h_times;

            x1 = (short)(x - 1);
            x2 = (short)(x + 1);
            y1 = (short)(y + 1);
            y2 = (short)(y - 1);
            f11 = is_in_array(x1, y1, height, width) ? in_array[y1*width+x1] : 0;
            f12 = is_in_array(x1, y2, height, width) ? in_array[y2*width+x1] : 0;
            f21 = is_in_array(x2, y1, height, width) ? in_array[y1*width+x2] : 0;
            f22 = is_in_array(x2, y2, height, width) ? in_array[y2*width+x2] : 0;
            out_array[i*out_width+j] = (rt_uint8_t)(((f11 * (x2 - x) * (y2 - y)) +
                                       (f21 * (x - x1) * (y2 - y)) +
                                       (f12 * (x2 - x) * (y - y1)) +
                                       (f22 * (x - x1) * (y - y1))) / ((x2 - x1) * (y2 - y1)));
        }
    }
}


