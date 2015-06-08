/*
 *  arch/arm/include/asm/clkdev.h
 *
 *  Copyright (C) 2008 Russell King.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Helper for the clk API to assist looking up a struct clk.
 */
#ifndef __ASM_CLKDEV_H
#define __ASM_CLKDEV_H

#include <linux/slab.h>

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_HAVE_MACH_CLKDEV
#include <mach/clkdev.h>
#else
#define __clk_get(clk)	({ 1; })
#define __clk_put(clk)	do { } while (0)
#endif
<<<<<<< HEAD
=======
=======
#include <mach/clkdev.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static inline struct clk_lookup_alloc *__clkdev_alloc(size_t size)
{
	return kzalloc(size, GFP_KERNEL);
}

#endif
