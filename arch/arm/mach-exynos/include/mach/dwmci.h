<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/include/mach/dwmci.h
=======
<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/include/mach/dwmci.h
=======
/* linux/arch/arm/mach-exynos/include/mach/dwmci.h
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * Synopsys DesignWare Mobile Storage for EXYNOS4210
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARM_ARCH_DWMCI_H
#define __ASM_ARM_ARCH_DWMCI_H __FILE__

#include <linux/mmc/dw_mmc.h>

<<<<<<< HEAD
extern void exynos4_dwmci_set_platdata(struct dw_mci_board *pd);
=======
<<<<<<< HEAD
extern void exynos4_dwmci_set_platdata(struct dw_mci_board *pd);
=======
extern void exynos_dwmci_set_platdata(struct dw_mci_board *pd, u32 slot_id);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* __ASM_ARM_ARCH_DWMCI_H */
