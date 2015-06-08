#include <linux/kernel.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <linux/module.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/dma-mapping.h>
#include <linux/dma-debug.h>

#define PREALLOC_DMA_DEBUG_ENTRIES       (1 << 15)

static int __init dma_init(void)
{
	dma_debug_init(PREALLOC_DMA_DEBUG_ENTRIES);
	return 0;
}
fs_initcall(dma_init);
