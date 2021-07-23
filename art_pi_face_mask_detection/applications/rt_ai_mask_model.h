#ifndef __RT_AI_MASK_MODEL_H
#define __RT_AI_MASK_MODEL_H

/* model info ... */

// model name
#define RT_AI_MASK_MODEL_NAME			"mask"

#define RT_AI_MASK_WORK_BUFFER_BYTES		(56492)

#define AI_MASK_DATA_WEIGHTS_SIZE		(421288)

#define RT_AI_MASK_BUFFER_ALIGNMENT		(4)

#define RT_AI_MASK_IN_NUM				(1)

#define RT_AI_MASK_IN_SIZE_BYTES	{	\
	((128 * 128 * 3) * 1),	\
}
#define RT_AI_MASK_IN_1_SIZE			(128 * 128 * 3)
#define RT_AI_MASK_IN_1_SIZE_BYTES		((128 * 128 * 3) * 1)
#define RT_AI_MASK_IN_TOTAL_SIZE_BYTES		((128 * 128 * 3) * 1)



#define RT_AI_MASK_OUT_NUM				(1)

#define RT_AI_MASK_OUT_SIZE_BYTES	{	\
	((1 * 1 * 2) * 1),	\
}
#define RT_AI_MASK_OUT_1_SIZE			(1 * 1 * 2)
#define RT_AI_MASK_OUT_1_SIZE_BYTES		((1 * 1 * 2) * 1)
#define RT_AI_MASK_OUT_TOTAL_SIZE_BYTES		((1 * 1 * 2) * 1)




#define RT_AI_MASK_TOTAL_BUFFER_SIZE		//unused

#endif	//end
