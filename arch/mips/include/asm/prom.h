/*
 *  arch/mips/include/asm/prom.h
 *
 *  Copyright (C) 2010 Cisco Systems Inc. <dediao@cisco.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */
<<<<<<< HEAD
#ifndef __ASM_PROM_H
#define __ASM_PROM_H
=======
<<<<<<< HEAD
#ifndef __ASM_PROM_H
#define __ASM_PROM_H
=======
#ifndef __ASM_MIPS_PROM_H
#define __ASM_MIPS_PROM_H
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#ifdef CONFIG_OF
#include <asm/bootinfo.h>

extern int early_init_dt_scan_memory_arch(unsigned long node,
	const char *uname, int depth, void *data);

extern int reserve_mem_mach(unsigned long addr, unsigned long size);
extern void free_mem_mach(unsigned long addr, unsigned long size);

extern void device_tree_init(void);
#else /* CONFIG_OF */
static inline void device_tree_init(void) { }
#endif /* CONFIG_OF */

<<<<<<< HEAD
#endif /* __ASM_PROM_H */
=======
<<<<<<< HEAD
#endif /* __ASM_PROM_H */
=======
#endif /* _ASM_MIPS_PROM_H */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
