/*
 * linux/arch/arm/mach-mmp/include/mach/entry-macro.S
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <mach/regs-icu.h>

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	.macro	disable_fiq
	.endm

	.macro	arch_ret_to_user, tmp1, tmp2
	.endm

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.macro	get_irqnr_preamble, base, tmp
	mrc	p15, 0, \tmp, c0, c0, 0		@ CPUID
	and	\tmp, \tmp, #0xff00
	cmp	\tmp, #0x5800
	ldr	\base, =ICU_VIRT_BASE
	addne	\base, \base, #0x10c		@ PJ1 AP INT SEL register
	addeq	\base, \base, #0x104		@ PJ4 IRQ SEL register
	.endm

	.macro	get_irqnr_and_base, irqnr, irqstat, base, tmp
	ldr	\tmp, [\base, #0]
	and	\irqnr, \tmp, #0x3f
	tst	\tmp, #(1 << 6)
	.endm
