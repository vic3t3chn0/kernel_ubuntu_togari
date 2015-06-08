#ifndef __PLAT_AUDIO_H
#define __PLAT_AUDIO_H

<<<<<<< HEAD
struct kirkwood_asoc_platform_data {
=======
<<<<<<< HEAD
struct kirkwood_asoc_platform_data {
=======
#include <linux/mbus.h>

struct kirkwood_asoc_platform_data {
	u32 tclk;
	struct mbus_dram_target_info *dram;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int burst;
};
#endif
