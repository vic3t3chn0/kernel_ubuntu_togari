/*
 * asm/leon_pci.h
 *
 * Copyright (C) 2011 Aeroflex Gaisler AB, Daniel Hellstrom
 */

#ifndef _ASM_LEON_PCI_H_
#define _ASM_LEON_PCI_H_

/* PCI related definitions */
struct leon_pci_info {
	struct pci_ops *ops;
	struct resource	io_space;
	struct resource	mem_space;
<<<<<<< HEAD
	int (*map_irq)(const struct pci_dev *dev, u8 slot, u8 pin);
=======
<<<<<<< HEAD
	int (*map_irq)(const struct pci_dev *dev, u8 slot, u8 pin);
=======
	int (*map_irq)(struct pci_dev *dev, u8 slot, u8 pin);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

extern void leon_pci_init(struct platform_device *ofdev,
				struct leon_pci_info *info);

#endif /* _ASM_LEON_PCI_H_ */
