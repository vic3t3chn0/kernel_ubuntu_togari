#ifndef ASM_DMA_CONTIGUOUS_H
#define ASM_DMA_CONTIGUOUS_H

#ifdef __KERNEL__
<<<<<<< HEAD
#ifdef CONFIG_CMA
=======
#ifdef CONFIG_DMA_CMA
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#include <linux/device.h>
#include <linux/dma-contiguous.h>

static inline struct cma *dev_get_cma_area(struct device *dev)
{
	if (dev && dev->cma_area)
		return dev->cma_area;
<<<<<<< HEAD
	return dma_contiguous_def_area;
=======
	return dma_contiguous_default_area;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

static inline void dev_set_cma_area(struct device *dev, struct cma *cma)
{
	if (dev)
		dev->cma_area = cma;
<<<<<<< HEAD
=======
	if (!dev || !dma_contiguous_default_area)
		dma_contiguous_default_area = cma;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

#endif
#endif

#endif
