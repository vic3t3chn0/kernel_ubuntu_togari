/*
<<<<<<< HEAD
 *  linux/arch/arm/mach-exynos4/headsmp.S
=======
<<<<<<< HEAD
 *  linux/arch/arm/mach-exynos4/headsmp.S
=======
 *  linux/arch/arm/mach-exynos/headsmp.S
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 *  Cloned from linux/arch/arm/mach-realview/headsmp.S
 *
 *  Copyright (c) 2003 ARM Limited
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/linkage.h>
#include <linux/init.h>

	__CPUINIT

/*
 * exynos4 specific entry point for secondary CPUs.  This provides
 * a "holding pen" into which all secondary cores are held until we're
 * ready for them to initialise.
 */
<<<<<<< HEAD
ENTRY(exynos4_secondary_startup)
=======
<<<<<<< HEAD
ENTRY(exynos4_secondary_startup)
=======
ENTRY(exynos_secondary_startup)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mrc	p15, 0, r0, c0, c0, 5
	and	r0, r0, #15
	adr	r4, 1f
	ldmia	r4, {r5, r6}
	sub	r4, r4, r5
	add	r6, r6, r4
pen:	ldr	r7, [r6]
	cmp	r7, r0
	bne	pen

	/*
	 * we've been released from the holding pen: secondary_stack
	 * should now contain the SVC stack for this core
	 */
	b	secondary_startup
<<<<<<< HEAD
ENDPROC(exynos4_secondary_startup)

	.align 2
=======
<<<<<<< HEAD
ENDPROC(exynos4_secondary_startup)

	.align 2
=======

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
1:	.long	.
	.long	pen_release
