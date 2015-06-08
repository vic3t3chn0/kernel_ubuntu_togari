/*
 *  arch/arm/mach-footbridge/include/mach/io.h
 *
 *  Copyright (C) 1997-1999 Russell King
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  Modifications:
 *   06-12-1997	RMK	Created.
 *   07-04-1999	RMK	Major cleanup
 */
#ifndef __ASM_ARM_ARCH_IO_H
#define __ASM_ARM_ARCH_IO_H

#ifdef CONFIG_MMU
#define MMU_IO(a, b)	(a)
#else
#define MMU_IO(a, b)	(b)
#endif

#define PCIO_SIZE       0x00100000
#define PCIO_BASE       MMU_IO(0xff000000, 0x7c000000)

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define IO_SPACE_LIMIT 0xffff

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Translation of various region addresses to virtual addresses
 */
#define __io(a)			((void __iomem *)(PCIO_BASE + (a)))
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#if 1
#define __mem_pci(a)		(a)
#else

static inline void __iomem *___mem_pci(void __iomem *p)
{
	unsigned long a = (unsigned long)p;
	BUG_ON(a <= 0xc0000000 || a >= 0xe0000000);
	return p;
}

#define __mem_pci(a)		___mem_pci(a)
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif
