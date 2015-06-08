/*
 * arch/arm/mach-dove/include/mach/io.h
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#ifndef __ASM_ARCH_IO_H
#define __ASM_ARCH_IO_H

#include "dove.h"

#define IO_SPACE_LIMIT		0xffffffff

#define __io(a)  	((void __iomem *)(((a) - DOVE_PCIE0_IO_BUS_BASE) + \
						 DOVE_PCIE0_IO_VIRT_BASE))
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define __mem_pci(a)	(a)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif
