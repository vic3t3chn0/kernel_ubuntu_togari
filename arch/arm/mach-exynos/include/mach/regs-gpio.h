<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/include/mach/regs-gpio.h
=======
<<<<<<< HEAD
/* linux/arch/arm/mach-exynos4/include/mach/regs-gpio.h
=======
/* linux/arch/arm/mach-exynos/include/mach/regs-gpio.h
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright (c) 2010-2011 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * EXYNOS4 - GPIO (including EINT) register definitions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#ifndef __ASM_ARCH_REGS_GPIO_H
#define __ASM_ARCH_REGS_GPIO_H __FILE__

#include <mach/map.h>
#include <mach/irqs.h>

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define EINT_REG_NR(x)			(EINT_OFFSET(x) >> 3)
#define EINT_CON(b, x)			(b + 0xE00 + (EINT_REG_NR(x) * 4))
#define EINT_FLTCON(b, x)		(b + 0xE80 + (EINT_REG_NR(x) * 4))
#define EINT_MASK(b, x)			(b + 0xF00 + (EINT_REG_NR(x) * 4))
#define EINT_PEND(b, x)			(b + 0xF40 + (EINT_REG_NR(x) * 4))

#define EINT_OFFSET_BIT(x)		(1 << (EINT_OFFSET(x) & 0x7))

/* compatibility for plat-s5p/irq-pm.c */
#define EXYNOS4_EINT40CON		(S5P_VA_GPIO2 + 0xE00)
#define S5P_EINT_CON(x)			(EXYNOS4_EINT40CON + ((x) * 0x4))

#define EXYNOS4_EINT40FLTCON0		(S5P_VA_GPIO2 + 0xE80)
#define S5P_EINT_FLTCON(x)		(EXYNOS4_EINT40FLTCON0 + ((x) * 0x4))

#define EXYNOS4_EINT40MASK		(S5P_VA_GPIO2 + 0xF00)
#define S5P_EINT_MASK(x)		(EXYNOS4_EINT40MASK + ((x) * 0x4))

#define EXYNOS4_EINT40PEND		(S5P_VA_GPIO2 + 0xF40)
#define S5P_EINT_PEND(x)		(EXYNOS4_EINT40PEND + ((x) * 0x4))

<<<<<<< HEAD
=======
=======
#if defined(CONFIG_ARCH_EXYNOS4)
#define EINT_BASE_ADD			S5P_VA_GPIO2
#define EINT_GPIO_0(x)			EXYNOS4_GPX0(x)
#define EINT_GPIO_1(x)			EXYNOS4_GPX1(x)
#define EINT_GPIO_2(x)			EXYNOS4_GPX2(x)
#define EINT_GPIO_3(x)			EXYNOS4_GPX3(x)

#elif defined(CONFIG_ARCH_EXYNOS5)
#define EINT_BASE_ADD			S5P_VA_GPIO1
#define EINT_GPIO_0(x)			EXYNOS5_GPX0(x)
#define EINT_GPIO_1(x)			EXYNOS5_GPX1(x)
#define EINT_GPIO_2(x)			EXYNOS5_GPX2(x)
#define EINT_GPIO_3(x)			EXYNOS5_GPX3(x)
#else
#error "ARCH_EXYNOS* is not defined"
#endif

#define EXYNOS_EINT40CON		(EINT_BASE_ADD + 0xE00)
#define S5P_EINT_CON(x)			(EXYNOS_EINT40CON + ((x) * 0x4))

#define EXYNOS_EINT40FLTCON0		(EINT_BASE_ADD + 0xE80)
#define S5P_EINT_FLTCON(x)		(EXYNOS_EINT40FLTCON0 + ((x) * 0x4))

#define EXYNOS_EINT40MASK		(EINT_BASE_ADD + 0xF00)
#define S5P_EINT_MASK(x)		(EXYNOS_EINT40MASK + ((x) * 0x4))

#define EXYNOS_EINT40PEND		(EINT_BASE_ADD + 0xF40)
#define S5P_EINT_PEND(x)		(EXYNOS_EINT40PEND + ((x) * 0x4))

#define EINT_REG_NR(x)			(EINT_OFFSET(x) >> 3)

#define eint_irq_to_bit(irq)		(1 << (EINT_OFFSET(irq) & 0x7))

#define EINT_MODE			S3C_GPIO_SFN(0xf)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* __ASM_ARCH_REGS_GPIO_H */
