/*
 * arch/sh/drivers/pci/fixups-r7780rp.c
 *
 * Highlander R7780RP-1 PCI fixups
 *
 * Copyright (C) 2003  Lineo uSolutions, Inc.
 * Copyright (C) 2004 - 2006  Paul Mundt
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 */
#include <linux/pci.h>
#include <linux/io.h>
#include "pci-sh4.h"

static char irq_tab[] __initdata = {
	65, 66, 67, 68,
};

<<<<<<< HEAD
int __init pcibios_map_platform_irq(const struct pci_dev *pdev, u8 slot, u8 pin)
=======
<<<<<<< HEAD
int __init pcibios_map_platform_irq(const struct pci_dev *pdev, u8 slot, u8 pin)
=======
int __init pcibios_map_platform_irq(struct pci_dev *pdev, u8 slot, u8 pin)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return irq_tab[slot];
}
