/*
 *  linux/arch/arm/mach-shark/pci.c
 *
 *  PCI bios-type initialisation for PCI machines
 *
 *  Bits taken from various places.
 */
#include <linux/kernel.h>
#include <linux/pci.h>
#include <linux/init.h>
<<<<<<< HEAD
#include <video/vga.h>
=======
<<<<<<< HEAD
#include <video/vga.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <asm/irq.h>
#include <asm/mach/pci.h>
#include <asm/mach-types.h>

<<<<<<< HEAD
static int __init shark_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
=======
<<<<<<< HEAD
static int __init shark_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
=======
static int __init shark_map_irq(struct pci_dev *dev, u8 slot, u8 pin)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	if (dev->bus->number == 0)
		if (dev->devfn == 0)
			return 255;
		else
			return 11;
	else
		return 255;
}

extern void __init via82c505_preinit(void);

static struct hw_pci shark_pci __initdata = {
	.setup		= via82c505_setup,
	.swizzle	= pci_std_swizzle,
	.map_irq	= shark_map_irq,
	.nr_controllers = 1,
	.scan		= via82c505_scan_bus,
	.preinit	= via82c505_preinit,
};

static int __init shark_pci_init(void)
{
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!machine_is_shark())
		return;

	pcibios_min_io = 0x6000;
	pcibios_min_mem = 0x50000000;
	vga_base = 0xe8000000;

	pci_common_init(&shark_pci);

<<<<<<< HEAD
=======
=======
	if (machine_is_shark())
		pci_common_init(&shark_pci);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

subsys_initcall(shark_pci_init);
