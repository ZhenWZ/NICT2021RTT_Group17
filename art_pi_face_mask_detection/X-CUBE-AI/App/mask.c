/**
  ******************************************************************************
  * @file    mask.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Thu Jul 22 14:41:50 2021
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */


#include "mask.h"

#include "ai_platform_interface.h"
#include "ai_math_helpers.h"

#include "core_common.h"
#include "layers.h"



#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 5
#define AI_TOOLS_VERSION_MINOR 2
#define AI_TOOLS_VERSION_MICRO 0


#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 3
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_mask
 
#undef AI_MASK_MODEL_SIGNATURE
#define AI_MASK_MODEL_SIGNATURE     "1dffc1808f2b3c8d3667b7c889681048"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-5.2.0)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Thu Jul 22 14:41:50 2021"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_MASK_N_BATCHES
#define AI_MASK_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network array declarations  **************************************/
AI_STATIC ai_array conv2d_3_scratch1_array;   /* Array #0 */
AI_STATIC ai_array conv2d_3_scratch0_array;   /* Array #1 */
AI_STATIC ai_array conv2d_1_scratch1_array;   /* Array #2 */
AI_STATIC ai_array conv2d_1_scratch0_array;   /* Array #3 */
AI_STATIC ai_array dense_7_bias_array;   /* Array #4 */
AI_STATIC ai_array dense_7_weights_array;   /* Array #5 */
AI_STATIC ai_array dense_6_bias_array;   /* Array #6 */
AI_STATIC ai_array dense_6_weights_array;   /* Array #7 */
AI_STATIC ai_array conv2d_3_bias_array;   /* Array #8 */
AI_STATIC ai_array conv2d_3_weights_array;   /* Array #9 */
AI_STATIC ai_array conv2d_1_bias_array;   /* Array #10 */
AI_STATIC ai_array conv2d_1_weights_array;   /* Array #11 */
AI_STATIC ai_array conv2d_6_input_output_array;   /* Array #12 */
AI_STATIC ai_array conversion_0_output_array;   /* Array #13 */
AI_STATIC ai_array conv2d_1_output_array;   /* Array #14 */
AI_STATIC ai_array conv2d_3_output_array;   /* Array #15 */
AI_STATIC ai_array dense_6_output_array;   /* Array #16 */
AI_STATIC ai_array dense_7_output_array;   /* Array #17 */
AI_STATIC ai_array nl_8_output_array;   /* Array #18 */
AI_STATIC ai_array conversion_9_output_array;   /* Array #19 */


/**  Forward network tensor declarations  *************************************/
AI_STATIC ai_tensor conv2d_3_scratch1;   /* Tensor #0 */
AI_STATIC ai_tensor conv2d_3_scratch0;   /* Tensor #1 */
AI_STATIC ai_tensor conv2d_1_scratch1;   /* Tensor #2 */
AI_STATIC ai_tensor conv2d_1_scratch0;   /* Tensor #3 */
AI_STATIC ai_tensor dense_7_bias;   /* Tensor #4 */
AI_STATIC ai_tensor dense_7_weights;   /* Tensor #5 */
AI_STATIC ai_tensor dense_6_bias;   /* Tensor #6 */
AI_STATIC ai_tensor dense_6_weights;   /* Tensor #7 */
AI_STATIC ai_tensor conv2d_3_bias;   /* Tensor #8 */
AI_STATIC ai_tensor conv2d_3_weights;   /* Tensor #9 */
AI_STATIC ai_tensor conv2d_1_bias;   /* Tensor #10 */
AI_STATIC ai_tensor conv2d_1_weights;   /* Tensor #11 */
AI_STATIC ai_tensor conv2d_6_input_output;   /* Tensor #12 */
AI_STATIC ai_tensor conversion_0_output;   /* Tensor #13 */
AI_STATIC ai_tensor conv2d_1_output;   /* Tensor #14 */
AI_STATIC ai_tensor conv2d_3_output;   /* Tensor #15 */
AI_STATIC ai_tensor conv2d_3_output0;   /* Tensor #16 */
AI_STATIC ai_tensor dense_6_output;   /* Tensor #17 */
AI_STATIC ai_tensor dense_7_output;   /* Tensor #18 */
AI_STATIC ai_tensor nl_8_output;   /* Tensor #19 */
AI_STATIC ai_tensor conversion_9_output;   /* Tensor #20 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain conversion_0_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain conv2d_1_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain conv2d_3_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain dense_6_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain dense_7_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain nl_8_chain;   /* Chain #5 */
AI_STATIC_CONST ai_tensor_chain conversion_9_chain;   /* Chain #6 */


/**  Forward network layer declarations  **************************************/
AI_STATIC ai_layer_nl conversion_0_layer; /* Layer #0 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_1_layer; /* Layer #1 */
AI_STATIC ai_layer_conv2d_nl_pool conv2d_3_layer; /* Layer #2 */
AI_STATIC ai_layer_dense dense_6_layer; /* Layer #3 */
AI_STATIC ai_layer_dense dense_7_layer; /* Layer #4 */
AI_STATIC ai_layer_nl nl_8_layer; /* Layer #5 */
AI_STATIC ai_layer_nl conversion_9_layer; /* Layer #6 */


/**  Array declarations section  **********************************************/
/* Array#0 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 3712, AI_STATIC)

/* Array#1 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 7168, AI_STATIC)

/* Array#2 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch1_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 4032, AI_STATIC)

/* Array#3 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_scratch0_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2284, AI_STATIC)

/* Array#4 */
AI_ARRAY_OBJ_DECLARE(
  dense_7_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 2, AI_STATIC)

/* Array#5 */
AI_ARRAY_OBJ_DECLARE(
  dense_7_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 64, AI_STATIC)

/* Array#6 */
AI_ARRAY_OBJ_DECLARE(
  dense_6_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#7 */
AI_ARRAY_OBJ_DECLARE(
  dense_6_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 401408, AI_STATIC)

/* Array#8 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 64, AI_STATIC)

/* Array#9 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 18432, AI_STATIC)

/* Array#10 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_bias_array, AI_ARRAY_FORMAT_S32,
  NULL, NULL, 32, AI_STATIC)

/* Array#11 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_weights_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 864, AI_STATIC)

/* Array#12 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_6_input_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 49152, AI_STATIC)

/* Array#13 */
AI_ARRAY_OBJ_DECLARE(
  conversion_0_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 49152, AI_STATIC)

/* Array#14 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_1_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 30752, AI_STATIC)

/* Array#15 */
AI_ARRAY_OBJ_DECLARE(
  conv2d_3_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 12544, AI_STATIC)

/* Array#16 */
AI_ARRAY_OBJ_DECLARE(
  dense_6_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 32, AI_STATIC)

/* Array#17 */
AI_ARRAY_OBJ_DECLARE(
  dense_7_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2, AI_STATIC)

/* Array#18 */
AI_ARRAY_OBJ_DECLARE(
  nl_8_output_array, AI_ARRAY_FORMAT_S8,
  NULL, NULL, 2, AI_STATIC)

/* Array#19 */
AI_ARRAY_OBJ_DECLARE(
  conversion_9_output_array, AI_ARRAY_FORMAT_U8|AI_FMT_FLAG_IS_IO,
  NULL, NULL, 2, AI_STATIC)

/**  Array metadata declarations section  *************************************/
/* Int quant #0 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0042664832435548306f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #1 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_scratch1_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002945770276710391f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #2 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_7_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00014665181515738368f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #3 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_7_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003284539794549346f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #4 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_6_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(2.842708681782824e-06f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #5 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_6_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0006662884843535721f),
    AI_PACK_INTQ_ZP(0)))

/* Int quant #6 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(2.8416116037988104e-06f, 2.903443601098843e-06f, 2.613094920889125e-06f, 2.9090745101711946e-06f, 2.7297116957925027e-06f, 2.11039014175185e-06f, 2.6151315069000702e-06f, 2.1242467482807115e-06f, 2.9884099603805225e-06f, 2.572147423052229e-06f, 2.6067914404848125e-06f, 2.5617666778998682e-06f, 3.0412288651859853e-06f, 2.8285257940297015e-06f, 2.3041452550387476e-06f, 2.7603330181591446e-06f, 2.603937446110649e-06f, 2.7154433155374136e-06f, 2.660767449924606e-06f, 2.9118752991053043e-06f, 2.9345280836423626e-06f, 3.00121041618695e-06f, 2.8943115921720164e-06f, 2.9427424124151003e-06f, 2.1834002836840227e-06f, 2.1500193270185264e-06f, 2.825958063112921e-06f, 2.231137159469654e-06f, 2.999576508955215e-06f, 2.216481561845285e-06f, 2.954439423774602e-06f, 2.3368863821815467e-06f, 3.1568288250127807e-06f, 2.74211947726144e-06f, 3.4256684102729196e-06f, 3.64489233106724e-06f, 2.38317261391785e-06f, 3.1367360406875378e-06f, 2.128505457221763e-06f, 3.009300144185545e-06f, 2.7927299015573226e-06f, 3.2004052172851516e-06f, 2.6065774818562204e-06f, 2.2760934825782897e-06f, 2.6809543669514824e-06f, 3.4661231893551303e-06f, 2.4338671664736466e-06f, 2.4075259261735482e-06f, 3.288305833848426e-06f, 2.238509978269576e-06f, 2.5844763058557874e-06f, 2.835986379068345e-06f, 3.255741148677771e-06f, 2.550269528001081e-06f, 2.8884835501230555e-06f, 3.2656168968969723e-06f, 2.716820972636924e-06f, 2.892635393436649e-06f, 2.817692120515858e-06f, 3.0076787425059592e-06f, 2.763995553323184e-06f, 3.0603789582528407e-06f, 2.04974958251114e-06f, 2.5038152671186253e-06f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #7 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 64,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0009646412800066173f, 0.00098563136998564f, 0.000887066766154021f, 0.0009875429095700383f, 0.0009266546694561839f, 0.0007164137205109f, 0.0008877580985426903f, 0.0007211175980046391f, 0.0010144748957827687f, 0.0008731663110665977f, 0.0008849269361235201f, 0.0008696423610672355f, 0.001032405300065875f, 0.0009601990459486842f, 0.0007821876788511872f, 0.0009370496845804155f, 0.0008839580696076155f, 0.0009218109771609306f, 0.0009032501257024705f, 0.000988493673503399f, 0.000996183604001999f, 0.001018820214085281f, 0.0009825313463807106f, 0.0009989721002057195f, 0.0007411984261125326f, 0.0007298665586858988f, 0.000959327386226505f, 0.0007574036717414856f, 0.0010182656114920974f, 0.0007524284883402288f, 0.0010029429104179144f, 0.000793302315287292f, 0.0010716479737311602f, 0.0009308666922152042f, 0.001162910950370133f, 0.001237330841831863f, 0.000809015124104917f, 0.0010648270836099982f, 0.0007225633016787469f, 0.0010215664515271783f, 0.0009480473818257451f, 0.0010864408686757088f, 0.0008848542929627001f, 0.0007726649637334049f, 0.000910102971829474f, 0.001176644116640091f, 0.0008262243936769664f, 0.0008172822999767959f, 0.0011162804439663887f, 0.0007599064847454429f, 0.0008773516165092587f, 0.0009627316612750292f, 0.0011052257614210248f, 0.0008657394791953266f, 0.0009805528679862618f, 0.0011085782898589969f, 0.0009222786175087094f, 0.0009819623082876205f, 0.0009565213113091886f, 0.0010210160398855805f, 0.0009382930002175272f, 0.0010389061644673347f, 0.000695828057359904f, 0.0008499696268700063f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #8 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_bias_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(4.715145223599393e-06f, 4.406502739584539e-06f, 4.412866928760195e-06f, 4.0800237002258655e-06f, 4.0464788071403746e-06f, 3.929838840122102e-06f, 3.6490509955910966e-06f, 4.3493414523254614e-06f, 4.413513124745805e-06f, 4.783159511134727e-06f, 4.859634373133304e-06f, 4.296226961741922e-06f, 4.337451628089184e-06f, 4.09193262385088e-06f, 4.765686753671616e-06f, 4.415554940351285e-06f, 4.330064257374033e-06f, 3.202773996235919e-06f, 4.833523234992754e-06f, 4.265368716005469e-06f, 4.42458076577168e-06f, 4.012672434328124e-06f, 4.110502231924329e-06f, 4.504208845901303e-06f, 4.256719421391608e-06f, 3.889083927788306e-06f, 4.26627730121254e-06f, 4.498854650591966e-06f, 4.452161192602944e-06f, 4.435515165823745e-06f, 4.188552338746376e-06f, 4.093649295100477e-06f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #9 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_weights_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 32,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0012023620074614882f, 0.0011236581485718489f, 0.0011252809781581163f, 0.0010404059430584311f, 0.0010318519780412316f, 0.0010021087946370244f, 0.0009305079584009945f, 0.001109082018956542f, 0.0011254458222538233f, 0.001219705562107265f, 0.0012392066419124603f, 0.0010955377947539091f, 0.0011060500983148813f, 0.0010434427531436086f, 0.0012152499984949827f, 0.0011259664315730333f, 0.0011041662655770779f, 0.0008167073247022927f, 0.0012325483839958906f, 0.001087668933905661f, 0.0011282680789008737f, 0.0010232314234599471f, 0.001048178062774241f, 0.0011485732393339276f, 0.0010854634456336498f, 0.000991716398857534f, 0.0010879006003960967f, 0.0011472079204395413f, 0.0011353010777384043f, 0.0011310563422739506f, 0.0010680807754397392f, 0.0010438804747536778f),
    AI_PACK_INTQ_ZP(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)))

/* Int quant #10 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_6_input_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_UINTQ_ZP(0)))

/* Int quant #11 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conversion_0_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.003921568859368563f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #12 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_1_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.002945770276710391f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #13 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conv2d_3_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.0042664832435548306f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #14 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_6_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.044649120420217514f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #15 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(dense_7_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.04966994374990463f),
    AI_PACK_INTQ_ZP(-19)))

/* Int quant #16 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(nl_8_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_S8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_INTQ_ZP(-128)))

/* Int quant #17 */
AI_INTQ_INFO_LIST_OBJ_DECLARE(conversion_9_output_intq, AI_STATIC_CONST,
  AI_BUFFER_META_FLAG_SCALE_FLOAT|AI_BUFFER_META_FLAG_ZEROPOINT_U8, 1,
  AI_PACK_INTQ_INFO(
    AI_PACK_INTQ_SCALE(0.00390625f),
    AI_PACK_UINTQ_ZP(0)))

/**  Tensor declarations section  *********************************************/
/* Tensor #0 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 29, 2), AI_STRIDE_INIT(4, 1, 1, 64, 1856),
  1, &conv2d_3_scratch1_array, &conv2d_3_scratch1_intq)

/* Tensor #1 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 7168, 1, 1), AI_STRIDE_INIT(4, 1, 1, 7168, 7168),
  1, &conv2d_3_scratch0_array, NULL)

/* Tensor #2 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch1, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 63, 2), AI_STRIDE_INIT(4, 1, 1, 32, 2016),
  1, &conv2d_1_scratch1_array, &conv2d_1_scratch1_intq)

/* Tensor #3 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_scratch0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2284, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2284, 2284),
  1, &conv2d_1_scratch0_array, NULL)

/* Tensor #4 */
AI_TENSOR_OBJ_DECLARE(
  dense_7_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 4, 4, 8, 8),
  1, &dense_7_bias_array, &dense_7_bias_intq)

/* Tensor #5 */
AI_TENSOR_OBJ_DECLARE(
  dense_7_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 32, 2, 1, 1), AI_STRIDE_INIT(4, 1, 32, 64, 64),
  1, &dense_7_weights_array, &dense_7_weights_intq)

/* Tensor #6 */
AI_TENSOR_OBJ_DECLARE(
  dense_6_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &dense_6_bias_array, &dense_6_bias_intq)

/* Tensor #7 */
AI_TENSOR_OBJ_DECLARE(
  dense_6_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 12544, 32, 1, 1), AI_STRIDE_INIT(4, 1, 12544, 401408, 401408),
  1, &dense_6_weights_array, &dense_6_weights_intq)

/* Tensor #8 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 1, 1), AI_STRIDE_INIT(4, 4, 4, 256, 256),
  1, &conv2d_3_bias_array, &conv2d_3_bias_intq)

/* Tensor #9 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 32, 3, 3, 64), AI_STRIDE_INIT(4, 1, 32, 96, 288),
  1, &conv2d_3_weights_array, &conv2d_3_weights_intq)

/* Tensor #10 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_bias, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 4, 4, 128, 128),
  1, &conv2d_1_bias_array, &conv2d_1_bias_intq)

/* Tensor #11 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_weights, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 3, 3, 3, 32), AI_STRIDE_INIT(4, 1, 3, 9, 27),
  1, &conv2d_1_weights_array, &conv2d_1_weights_intq)

/* Tensor #12 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_6_input_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 128, 128), AI_STRIDE_INIT(4, 1, 1, 3, 384),
  1, &conv2d_6_input_output_array, &conv2d_6_input_output_intq)

/* Tensor #13 */
AI_TENSOR_OBJ_DECLARE(
  conversion_0_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 3, 128, 128), AI_STRIDE_INIT(4, 1, 1, 3, 384),
  1, &conversion_0_output_array, &conversion_0_output_intq)

/* Tensor #14 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_1_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 31, 31), AI_STRIDE_INIT(4, 1, 1, 32, 992),
  1, &conv2d_1_output_array, &conv2d_1_output_intq)

/* Tensor #15 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 64, 14, 14), AI_STRIDE_INIT(4, 1, 1, 64, 896),
  1, &conv2d_3_output_array, &conv2d_3_output_intq)

/* Tensor #16 */
AI_TENSOR_OBJ_DECLARE(
  conv2d_3_output0, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 12544, 1, 1), AI_STRIDE_INIT(4, 1, 1, 12544, 12544),
  1, &conv2d_3_output_array, &conv2d_3_output_intq)

/* Tensor #17 */
AI_TENSOR_OBJ_DECLARE(
  dense_6_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 32, 1, 1), AI_STRIDE_INIT(4, 1, 1, 32, 32),
  1, &dense_6_output_array, &dense_6_output_intq)

/* Tensor #18 */
AI_TENSOR_OBJ_DECLARE(
  dense_7_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2, 2),
  1, &dense_7_output_array, &dense_7_output_intq)

/* Tensor #19 */
AI_TENSOR_OBJ_DECLARE(
  nl_8_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2, 2),
  1, &nl_8_output_array, &nl_8_output_intq)

/* Tensor #20 */
AI_TENSOR_OBJ_DECLARE(
  conversion_9_output, AI_STATIC,
  0x0, 0x0,
  AI_SHAPE_INIT(4, 1, 2, 1, 1), AI_STRIDE_INIT(4, 1, 1, 2, 2),
  1, &conversion_9_output_array, &conversion_9_output_intq)



/**  Layer declarations section  **********************************************/


AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_0_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_6_input_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_0_layer, 0,
  NL_TYPE,
  nl, node_convert_integer,
  &AI_NET_OBJ_INSTANCE, &conv2d_1_layer, AI_STATIC,
  .tensors = &conversion_0_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_1_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_0_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_1_weights, &conv2d_1_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_1_scratch0, &conv2d_1_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_1_layer, 1,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &conv2d_3_layer, AI_STATIC,
  .tensors = &conv2d_1_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(2, 2), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conv2d_3_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_1_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 3, &conv2d_3_weights, &conv2d_3_bias, NULL),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &conv2d_3_scratch0, &conv2d_3_scratch1)
)

AI_LAYER_OBJ_DECLARE(
  conv2d_3_layer, 3,
  OPTIMIZED_CONV2D_TYPE,
  conv2d_nl_pool, forward_conv2d_nl_pool_integer_SSSA_ch,
  &AI_NET_OBJ_INSTANCE, &dense_6_layer, AI_STATIC,
  .tensors = &conv2d_3_chain, 
  .groups = 1, 
  .nl_func = NULL, 
  .filter_stride = AI_SHAPE_2D_INIT(1, 1), 
  .dilation = AI_SHAPE_2D_INIT(1, 1), 
  .filter_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_size = AI_SHAPE_2D_INIT(2, 2), 
  .pool_stride = AI_SHAPE_2D_INIT(2, 2), 
  .pool_pad = AI_SHAPE_INIT(4, 0, 0, 0, 0), 
  .pool_func = pool_func_mp_array_integer_INT8, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_6_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conv2d_3_output0),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_6_weights, &dense_6_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_6_layer, 6,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &dense_7_layer, AI_STATIC,
  .tensors = &dense_6_chain, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_7_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_6_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 2, &dense_7_weights, &dense_7_bias),
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_7_layer, 7,
  DENSE_TYPE,
  dense, forward_dense_integer_SSSA,
  &AI_NET_OBJ_INSTANCE, &nl_8_layer, AI_STATIC,
  .tensors = &dense_7_chain, 
)


AI_STATIC_CONST ai_i8 nl_8_nl_params_data[] = { -127, -127, -127, -127, -127, -127, -126, -126, -126, -126, -126, -126, -126, -126, -126, -126, -126, -125, -125, -125, -125, -125, -125, -124, -124, -124, -124, -124, -123, -123, -123, -123, -123, -122, -122, -122, -121, -121, -121, -120, -120, -120, -119, -119, -118, -118, -117, -117, -116, -116, -115, -114, -114, -113, -112, -112, -111, -110, -109, -108, -107, -106, -105, -104, -103, -102, -101, -100, -98, -97, -96, -94, -93, -91, -90, -88, -86, -85, -83, -81, -79, -77, -75, -73, -71, -68, -66, -64, -61, -59, -56, -54, -51, -48, -46, -43, -40, -37, -34, -31, -28, -25, -22, -19, -16, -13, -10, -6, -3, 0, 3, 6, 10, 13, 16, 19, 22, 25, 28, 31, 34, 37, 40, 43, 46, 48, 51, 54, 56, 59, 61, 64, 66, 68, 71, 73, 75, 77, 79, 81, 83, 85, 86, 88, 90, 91, 93, 94, 96, 97, 98, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 112, 113, 114, 114, 115, 116, 116, 117, 117, 118, 118, 119, 119, 120, 120, 120, 121, 121, 121, 122, 122, 122, 123, 123, 123, 123, 123, 124, 124, 124, 124, 124, 125, 125, 125, 125, 125, 125, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127, 127 };
AI_ARRAY_OBJ_DECLARE(
    nl_8_nl_params, AI_ARRAY_FORMAT_S8,
    nl_8_nl_params_data, nl_8_nl_params_data, 256, AI_STATIC_CONST)
AI_TENSOR_CHAIN_OBJ_DECLARE(
  nl_8_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &dense_7_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_8_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  nl_8_layer, 8,
  NL_TYPE,
  nl, forward_nl_integer,
  &AI_NET_OBJ_INSTANCE, &conversion_9_layer, AI_STATIC,
  .tensors = &nl_8_chain, 
  .nl_params = &nl_8_nl_params, 
)

AI_TENSOR_CHAIN_OBJ_DECLARE(
  conversion_9_chain, AI_STATIC_CONST, 4,
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &nl_8_output),
  AI_TENSOR_LIST_OBJ_INIT(AI_FLAG_NONE, 1, &conversion_9_output),
  AI_TENSOR_LIST_OBJ_EMPTY,
  AI_TENSOR_LIST_OBJ_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  conversion_9_layer, 9,
  NL_TYPE,
  nl, node_convert_integer,
  &AI_NET_OBJ_INSTANCE, &conversion_9_layer, AI_STATIC,
  .tensors = &conversion_9_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE, AI_STATIC,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 421288, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 56492, 1,
                     NULL),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_MASK_IN_NUM, &conv2d_6_input_output),
  AI_TENSOR_LIST_IO_OBJ_INIT(AI_FLAG_NONE, AI_MASK_OUT_NUM, &conversion_9_output),
  &conversion_0_layer, 0, NULL)



AI_DECLARE_STATIC
ai_bool mask_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, AI_MASK_ACTIVATIONS_ALIGNMENT));
  AI_ASSERT(activations)
  AI_UNUSED(net_ctx)

  {
    /* Updating activations (byte) offsets */
    conv2d_3_scratch1_array.data = AI_PTR(activations + 37920);
    conv2d_3_scratch1_array.data_start = AI_PTR(activations + 37920);
    conv2d_3_scratch0_array.data = AI_PTR(activations + 30752);
    conv2d_3_scratch0_array.data_start = AI_PTR(activations + 30752);
    conv2d_1_scratch1_array.data = AI_PTR(activations + 52460);
    conv2d_1_scratch1_array.data_start = AI_PTR(activations + 52460);
    conv2d_1_scratch0_array.data = AI_PTR(activations + 50176);
    conv2d_1_scratch0_array.data_start = AI_PTR(activations + 50176);
    conv2d_6_input_output_array.data = AI_PTR(NULL);
    conv2d_6_input_output_array.data_start = AI_PTR(NULL);
    conversion_0_output_array.data = AI_PTR(activations + 1024);
    conversion_0_output_array.data_start = AI_PTR(activations + 1024);
    conv2d_1_output_array.data = AI_PTR(activations + 0);
    conv2d_1_output_array.data_start = AI_PTR(activations + 0);
    conv2d_3_output_array.data = AI_PTR(activations + 41632);
    conv2d_3_output_array.data_start = AI_PTR(activations + 41632);
    dense_6_output_array.data = AI_PTR(activations + 0);
    dense_6_output_array.data_start = AI_PTR(activations + 0);
    dense_7_output_array.data = AI_PTR(activations + 32);
    dense_7_output_array.data_start = AI_PTR(activations + 32);
    nl_8_output_array.data = AI_PTR(activations + 0);
    nl_8_output_array.data_start = AI_PTR(activations + 0);
    conversion_9_output_array.data = AI_PTR(NULL);
    conversion_9_output_array.data_start = AI_PTR(NULL);
    
  }
  return true;
}



AI_DECLARE_STATIC
ai_bool mask_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT(weights)
  AI_UNUSED(net_ctx)

  {
    /* Updating weights (byte) offsets */
    
    dense_7_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_7_bias_array.data = AI_PTR(weights + 421280);
    dense_7_bias_array.data_start = AI_PTR(weights + 421280);
    dense_7_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_7_weights_array.data = AI_PTR(weights + 421216);
    dense_7_weights_array.data_start = AI_PTR(weights + 421216);
    dense_6_bias_array.format |= AI_FMT_FLAG_CONST;
    dense_6_bias_array.data = AI_PTR(weights + 421088);
    dense_6_bias_array.data_start = AI_PTR(weights + 421088);
    dense_6_weights_array.format |= AI_FMT_FLAG_CONST;
    dense_6_weights_array.data = AI_PTR(weights + 19680);
    dense_6_weights_array.data_start = AI_PTR(weights + 19680);
    conv2d_3_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_bias_array.data = AI_PTR(weights + 19424);
    conv2d_3_bias_array.data_start = AI_PTR(weights + 19424);
    conv2d_3_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_3_weights_array.data = AI_PTR(weights + 992);
    conv2d_3_weights_array.data_start = AI_PTR(weights + 992);
    conv2d_1_bias_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_bias_array.data = AI_PTR(weights + 864);
    conv2d_1_bias_array.data_start = AI_PTR(weights + 864);
    conv2d_1_weights_array.format |= AI_FMT_FLAG_CONST;
    conv2d_1_weights_array.data = AI_PTR(weights + 0);
    conv2d_1_weights_array.data_start = AI_PTR(weights + 0);
  }

  return true;
}


/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_mask_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_MASK_MODEL_NAME,
      .model_signature   = AI_MASK_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 19603590,
      .n_inputs          = 0,
      .inputs            = NULL,
      .n_outputs         = 0,
      .outputs           = NULL,
      .activations       = AI_STRUCT_INIT,
      .params            = AI_STRUCT_INIT,
      .n_nodes           = 0,
      .signature         = 0x0,
    };

    if ( !ai_platform_api_get_network_report(network, &r) ) return false;

    *report = r;
    return true;
  }

  return false;
}

AI_API_ENTRY
ai_error ai_mask_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_mask_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_mask_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_mask_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= mask_configure_weights(net_ctx, &params->params);
  ok &= mask_configure_activations(net_ctx, &params->activations);

  ok &= ai_platform_network_post_init(network);

  return ok;
}


AI_API_ENTRY
ai_i32 ai_mask_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_mask_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}




#undef AI_MASK_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

