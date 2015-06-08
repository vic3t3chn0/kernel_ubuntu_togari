/*
 * OMAP4 clock function prototypes and macros
 *
 * Copyright (C) 2009 Texas Instruments, Inc.
 * Copyright (C) 2010 Nokia Corporation
 */

#ifndef __ARCH_ARM_MACH_OMAP2_CLOCK44XX_H
#define __ARCH_ARM_MACH_OMAP2_CLOCK44XX_H

/*
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * OMAP4430_REGM4XEN_MULT: If the CM_CLKMODE_DPLL_ABE.DPLL_REGM4XEN bit is
 *    set, then the DPLL's lock frequency is multiplied by 4 (OMAP4430 TRM
 *    vV Section 3.6.3.3.1 "DPLLs Output Clocks Parameters")
 */
#define OMAP4430_REGM4XEN_MULT	4
<<<<<<< HEAD
=======
=======
 * XXX Missing values for the OMAP4 DPLL_USB
 * XXX Missing min_multiplier values for all OMAP4 DPLLs
 */
#define OMAP4430_MAX_DPLL_MULT	2047
#define OMAP4430_MAX_DPLL_DIV	128
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

int omap4xxx_clk_init(void);

#endif
