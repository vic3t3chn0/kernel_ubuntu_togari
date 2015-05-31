#ifndef ASMARM_DMA_CONTIGUOUS_H
#define ASMARM_DMA_CONTIGUOUS_H

#ifdef __KERNEL__
<<<<<<< HEAD
#ifdef CONFIG_CMA
=======
#ifdef CONFIG_DMA_CMA
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#include <linux/types.h>
#include <asm-generic/dma-contiguous.h>

void dma_contiguous_early_fixup(phys_addr_t base, unsigned long size);

#endif
#endif

#endif
