/*
 * arch/arm/plat-orion/include/plat/mv_xor.h
 *
 * Marvell XOR platform device data definition file.
 */

#ifndef __PLAT_MV_XOR_H
#define __PLAT_MV_XOR_H

#include <linux/dmaengine.h>
#include <linux/mbus.h>

#define MV_XOR_SHARED_NAME	"mv_xor_shared"
#define MV_XOR_NAME		"mv_xor"

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
struct mbus_dram_target_info;

struct mv_xor_platform_shared_data {
	struct mbus_dram_target_info	*dram;
};

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct mv_xor_platform_data {
	struct platform_device		*shared;
	int				hw_id;
	dma_cap_mask_t			cap_mask;
	size_t				pool_size;
};


#endif
