/*
 * Arch specific extensions to struct device
 *
 * This file is released under the GPLv2
 */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifndef __ASM_SH_DEVICE_H
#define __ASM_SH_DEVICE_H

#include <asm-generic/device.h>
<<<<<<< HEAD
=======
=======

struct dev_archdata {
};
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

struct platform_device;
/* allocate contiguous memory chunk and fill in struct resource */
int platform_resource_setup_memory(struct platform_device *pdev,
				   char *name, unsigned long memsize);

void plat_early_device_setup(void);

<<<<<<< HEAD
#endif /* __ASM_SH_DEVICE_H */
=======
<<<<<<< HEAD
#endif /* __ASM_SH_DEVICE_H */
=======
#define PDEV_ARCHDATA_FLAG_INIT 0
#define PDEV_ARCHDATA_FLAG_IDLE 1
#define PDEV_ARCHDATA_FLAG_SUSP 2

struct pdev_archdata {
	int hwblk_id;
#ifdef CONFIG_PM_RUNTIME
	unsigned long flags;
	struct list_head entry;
	struct mutex mutex;
#endif
};
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
