<<<<<<< HEAD
/*
=======
<<<<<<< HEAD
/*
=======
/* arch/arm/mach-msm/include/mach/io.h
 *
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * Copyright (C) 2007 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __ASM_ARM_ARCH_IO_H
#define __ASM_ARM_ARCH_IO_H

#define IO_SPACE_LIMIT 0xffffffff

<<<<<<< HEAD
#define __io(a)		__typesafe_io(a)
#define __mem_pci(a)	(a)
=======
<<<<<<< HEAD
#define __io(a)		__typesafe_io(a)
#define __mem_pci(a)	(a)
=======
#define __arch_ioremap __msm_ioremap
#define __arch_iounmap __iounmap

void __iomem *__msm_ioremap(unsigned long phys_addr, size_t size, unsigned int mtype);

#define __io(a)		__typesafe_io(a)
#define __mem_pci(a)    (a)

void msm_map_qsd8x50_io(void);
void msm_map_msm7x30_io(void);
void msm_map_msm8x60_io(void);
void msm_map_msm8960_io(void);

extern unsigned int msm_shared_ram_phys;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif
