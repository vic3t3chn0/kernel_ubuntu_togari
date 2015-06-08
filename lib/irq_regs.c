/* saved per-CPU IRQ register pointer
 *
 * Copyright (C) 2006 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
<<<<<<< HEAD
#include <linux/export.h>
#include <linux/percpu.h>
=======
<<<<<<< HEAD
#include <linux/export.h>
#include <linux/percpu.h>
=======
#include <linux/module.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/irq_regs.h>

#ifndef ARCH_HAS_OWN_IRQ_REGS
DEFINE_PER_CPU(struct pt_regs *, __irq_regs);
EXPORT_PER_CPU_SYMBOL(__irq_regs);
#endif
