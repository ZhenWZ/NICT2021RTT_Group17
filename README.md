# 门禁监测助手 / Mask Detection Assistant

| Version | Date       | Description                                                  | Other      |
| ------- | ---------- | ------------------------------------------------------------ | ---------- |
| v1.0.0  | 2021/07/22 | 口罩监测模型部署到 ART-Pi 中                                   |            |

## 1. 项目说明 / Introduction

该项目将口罩监测模型部署到RT-Thread提供的ART-Pi开发板并通过gc0328读取图像数据，最后通过多媒体扩展版输出结果。

In this project, We trained a mask detection model and deployed it onto the ART-Pi development boarded. The development board takes in images collected by the gc0328 camera module, and output the result of mask detection model with an intergrated screen. 

## 2. 环境 / Environment

- 操作系统： Windows10
- X-CUBE-AI： 5.2.0
- RT-Thread Studio： 2.1.1
- RT-AK

    [RT-AK仓库](https://github.com/RT-Thread/RT-AK)
    
## 3. 元件 / Components

- ART-Pi
- ART-Pi 多媒体扩展版
- gc0328

## 4. 步骤 / Steps

### 4.0 准备文件

- RT-Thread工程
- RT-AK
- 准备好的模型
- X-CUBE-AI

### 4.1 部署模型 / Deployment

在命令行中进入到`RT-AK\rt_ai_tools`输入

```
python aitools.py --project="工程路径" --model="模型路径" --model_name="mask" --platform=stm32 --ext_tools="X-CUBE-AI路径" --clear
```

例如：

```
D:\RT-ThreadAI\RT-AK\rt_ai_tools>python aitools.py --project=D:\RT-ThreadAI\mask_detect --model=D:\RT-ThreadAI\RT-AK\rt_ai_tools\Models\mask_detect.tflite --model_name=mask --platform=stm32 --ext_tools=D:\RT-ThreadAI\stm32ai-windows-5.2.0\windows --clear
```

## 5. 训练模型 / Training

### 5.1 环境 / Environment

- tensorflow==2.4.0
- opencv-python==4.5.1
- matplotlib==3.3.3

### 5.2 数据集 / Datasets

- Face Mask Lite Dataset, <https://www.kaggle.com/prasoonkottarathil/face-mask-lite-dataset>
- COVID Face Mask Detection Dataset, <https://www.kaggle.com/prithwirajmitra/covid-face-mask-detection-dataset>
- With/Without Mask, <https://www.kaggle.com/niharika41298/withwithout-mask>
- Face Mask Detection, <https://www.kaggle.com/andrewmvd/face-mask-detection>
- Face Mask Detection ~12K Images Dataset, <https://www.kaggle.com/ashishjangra27/face-mask-12k-images-dataset>

### 5.3 网络结构 / Model Structure

- 两层卷积 + 一层全连接

![model](https://user-images.githubusercontent.com/48997918/126664710-692b93d4-696b-4bf1-98d8-d134d9d4f42c.png)


### 5.4 训练模型 & 验证模型 / Traning & Validating

- 训练模型 / Training

![training](https://user-images.githubusercontent.com/48997918/126664723-b9e23965-ee89-411a-853a-e34bb0b62929.png)


- 验证训练模型的准确率 / Accuracy

![evaluate](https://user-images.githubusercontent.com/48997918/126664763-96c984d4-bd6e-4ced-9597-06ab6552f4ac.png)


## 6. 运行结果 / Results

<img align="left" src=https://user-images.githubusercontent.com/48997918/126732799-459eb4a9-b067-45ee-ba04-f2875d0452c9.jpg width=200px/><img src=https://user-images.githubusercontent.com/48997918/126732808-3904e505-5377-47a5-af01-e26990329596.jpg width=200px/>


## 感谢名单 / Acknowledgements
- Derekduke
- lebhoryi
