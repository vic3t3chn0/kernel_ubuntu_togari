/* arch/arm/mach-s5pv210/include/mach/regs-audss.h
 *
<<<<<<< HEAD
 * Copyright (c) 2011 Samsung Electronics
 *		http://www.samsung.com
 *
 * S5PV210 Audio SubSystem clock register definitions
=======
 * Copyright 2011 Samsung Electronics
 *
 * S5PV2XX Audio SubSystem clock register definitions
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

<<<<<<< HEAD
#ifndef __PLAT_REGS_AUDSS_H
#define __PLAT_REGS_AUDSS_H __FILE__

#define S5PV210_AUDSS_INT_MEM	(0xC0000000)

#endif /* _PLAT_REGS_AUDSS_H */
=======
#ifndef __MACH_REGS_AUDSS_H
#define __MACH_REGS_AUDSS_H __FILE__

#define S5P_AUDSSREG(x)			(S5P_VA_AUDSS + (x))

#define S5P_CLKSRC_AUDSS		S5P_AUDSSREG(0x0)
#define S5P_CLKDIV_AUDSS		S5P_AUDSSREG(0x4)
#define S5P_CLKGATE_AUDSS		S5P_AUDSSREG(0x8)

/* CLKSRC0 */
#define S5P_AUDSS_CLKSRC_MAIN_MASK	(0x1<<0)
#define S5P_AUDSS_CLKSRC_MAIN_SHIFT	(0)
#define S5P_AUDSS_CLKSRC_BUSCLK_MASK	(0x1<<1)
#define S5P_AUDSS_CLKSRC_BUSCLK_SHIFT	(1)
#define S5P_AUDSS_CLKSRC_I2SCLK_MASK	(0x3<<2)
#define S5P_AUDSS_CLKSRC_I2SCLK_SHIFT	(2)

/* CLKDIV0 */
#define S5P_AUDSS_CLKDIV_BUSCLK_MASK	(0xf<<0)
#define S5P_AUDSS_CLKDIV_BUSCLK_SHIFT	(0)
#define S5P_AUDSS_CLKDIV_I2SCLK_MASK	(0xf<<4)
#define S5P_AUDSS_CLKDIV_I2SCLK_SHIFT	(4)

/* IP Clock Gate 0 Registers */
#define S5P_AUDSS_CLKGATE_HCLKRP	(1<<0)
#define S5P_AUDSS_CLKGATE_HCLKBUF	(1<<1)
#define S5P_AUDSS_CLKGATE_HCLKDMA	(1<<2)
#define S5P_AUDSS_CLKGATE_HCLKHWA	(1<<3)
#define S5P_AUDSS_CLKGATE_HCLKUART	(1<<4)
#define S5P_AUDSS_CLKGATE_HCLKI2S	(1<<5)
#define S5P_AUDSS_CLKGATE_CLKI2S	(1<<6)

#endif /* _MACH_REGS_AUDSS_H */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
