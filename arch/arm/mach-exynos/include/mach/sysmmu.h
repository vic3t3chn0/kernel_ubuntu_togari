<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* linux/arch/arm/mach-exynos4/include/mach/sysmmu.h
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Samsung sysmmu driver for EXYNOS4
<<<<<<< HEAD
=======
=======
/*
 * Copyright (c) 2011-2012 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS - System MMU support
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
*/

#ifndef __ASM_ARM_ARCH_SYSMMU_H
#define __ASM_ARM_ARCH_SYSMMU_H __FILE__

enum exynos4_sysmmu_ips {
	SYSMMU_MDMA,
	SYSMMU_SSS,
	SYSMMU_FIMC0,
	SYSMMU_FIMC1,
	SYSMMU_FIMC2,
	SYSMMU_FIMC3,
	SYSMMU_JPEG,
	SYSMMU_FIMD0,
	SYSMMU_FIMD1,
	SYSMMU_PCIe,
	SYSMMU_G2D,
	SYSMMU_ROTATOR,
	SYSMMU_MDMA2,
	SYSMMU_TV,
	SYSMMU_MFC_L,
	SYSMMU_MFC_R,
	EXYNOS4_SYSMMU_TOTAL_IPNUM,
};

#define S5P_SYSMMU_TOTAL_IPNUM		EXYNOS4_SYSMMU_TOTAL_IPNUM

extern const char *sysmmu_ips_name[EXYNOS4_SYSMMU_TOTAL_IPNUM];

typedef enum exynos4_sysmmu_ips sysmmu_ips;

void sysmmu_clk_init(struct device *dev, sysmmu_ips ips);
void sysmmu_clk_enable(sysmmu_ips ips);
void sysmmu_clk_disable(sysmmu_ips ips);

#endif /* __ASM_ARM_ARCH_SYSMMU_H */
<<<<<<< HEAD
=======
=======
 */

#ifndef _ARM_MACH_EXYNOS_SYSMMU_H_
#define _ARM_MACH_EXYNOS_SYSMMU_H_

struct sysmmu_platform_data {
	char *dbgname;
	/* comma(,) separated list of clock names for clock gating */
	char *clockname;
};

#define SYSMMU_DEVNAME_BASE "exynos-sysmmu"

#define SYSMMU_CLOCK_NAME "sysmmu"
#define SYSMMU_CLOCK_NAME2 "sysmmu_mc"

#ifdef CONFIG_EXYNOS_DEV_SYSMMU
#include <linux/device.h>
struct platform_device;

#define SYSMMU_PLATDEV(ipname) exynos_device_sysmmu_##ipname

extern struct platform_device SYSMMU_PLATDEV(mfc_lr);
extern struct platform_device SYSMMU_PLATDEV(tv);
extern struct platform_device SYSMMU_PLATDEV(jpeg);
extern struct platform_device SYSMMU_PLATDEV(rot);
extern struct platform_device SYSMMU_PLATDEV(fimc0);
extern struct platform_device SYSMMU_PLATDEV(fimc1);
extern struct platform_device SYSMMU_PLATDEV(fimc2);
extern struct platform_device SYSMMU_PLATDEV(fimc3);
extern struct platform_device SYSMMU_PLATDEV(gsc0);
extern struct platform_device SYSMMU_PLATDEV(gsc1);
extern struct platform_device SYSMMU_PLATDEV(gsc2);
extern struct platform_device SYSMMU_PLATDEV(gsc3);
extern struct platform_device SYSMMU_PLATDEV(isp);
extern struct platform_device SYSMMU_PLATDEV(fimd0);
extern struct platform_device SYSMMU_PLATDEV(fimd1);
extern struct platform_device SYSMMU_PLATDEV(camif0);
extern struct platform_device SYSMMU_PLATDEV(camif1);
extern struct platform_device SYSMMU_PLATDEV(camif2);
extern struct platform_device SYSMMU_PLATDEV(2d);

#ifdef CONFIG_IOMMU_API
static inline void platform_set_sysmmu(
				struct device *sysmmu, struct device *dev)
{
	dev->archdata.iommu = sysmmu;
}
#else
#define platform_set_sysmmu(dev, sysmmu) do { } while (0)
#endif

#else /* !CONFIG_EXYNOS_DEV_SYSMMU */
#define platform_set_sysmmu(dev, sysmmu) do { } while (0)
#endif

#define SYSMMU_CLOCK_DEVNAME(ipname, id) (SYSMMU_DEVNAME_BASE "." #id)

#endif /* _ARM_MACH_EXYNOS_SYSMMU_H_ */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
