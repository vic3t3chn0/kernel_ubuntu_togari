<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/include/mach/regs-sysmmu.h
=======
<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/include/mach/regs-sysmmu.h
=======
/* linux/arch/arm/mach-exynos/include/mach/regs-sysmmu.h
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS4 - System MMU register
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_REGS_SYSMMU_H
#define __ASM_ARCH_REGS_SYSMMU_H __FILE__

#define S5P_MMU_CTRL			0x000
#define S5P_MMU_CFG			0x004
#define S5P_MMU_STATUS			0x008
#define S5P_MMU_FLUSH			0x00C
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define S5P_MMU_FLUSH_ENTRY		0x010
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define S5P_PT_BASE_ADDR		0x014
#define S5P_INT_STATUS			0x018
#define S5P_INT_CLEAR			0x01C
#define S5P_PAGE_FAULT_ADDR		0x024
#define S5P_AW_FAULT_ADDR		0x028
#define S5P_AR_FAULT_ADDR		0x02C
#define S5P_DEFAULT_SLAVE_ADDR		0x030
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define S5P_MMU_VERSION			0x034
#define S5P_PB0_SADDR			0x04C
#define S5P_PB0_EADDR			0x050
#define S5P_PB1_SADDR			0x054
#define S5P_PB1_EADDR			0x058
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* __ASM_ARCH_REGS_SYSMMU_H */
