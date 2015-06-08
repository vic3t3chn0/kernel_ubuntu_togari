/*
 * ppc64 "iomap" interface implementation.
 *
 * (C) Copyright 2004 Linus Torvalds
 */
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/mm.h>
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/export.h>
#include <asm/io.h>
#include <asm/pci-bridge.h>

<<<<<<< HEAD
=======
=======
#include <asm/io.h>
#include <asm/pci-bridge.h>

void __iomem *pci_iomap(struct pci_dev *dev, int bar, unsigned long max)
{
	resource_size_t start = pci_resource_start(dev, bar);
	resource_size_t len = pci_resource_len(dev, bar);
	unsigned long flags = pci_resource_flags(dev, bar);

	if (!len)
		return NULL;
	if (max && len > max)
		len = max;
	if (flags & IORESOURCE_IO)
		return ioport_map(start, len);
	if (flags & IORESOURCE_MEM)
		return ioremap(start, len);
	/* What? */
	return NULL;
}
EXPORT_SYMBOL(pci_iomap);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void pci_iounmap(struct pci_dev *dev, void __iomem *addr)
{
	if (isa_vaddr_is_ioport(addr))
		return;
	if (pcibios_vaddr_is_ioport(addr))
		return;
	iounmap(addr);
}
EXPORT_SYMBOL(pci_iounmap);
