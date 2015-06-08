/* Core PCI functionality used only by PCI hotplug */

#include <linux/pci.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/export.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include "pci.h"


unsigned int __devinit pci_do_scan_bus(struct pci_bus *bus)
{
	unsigned int max;

	max = pci_scan_child_bus(bus);

	/*
	 * Make the discovered devices available.
	 */
	pci_bus_add_devices(bus);

	return max;
}
EXPORT_SYMBOL(pci_do_scan_bus);
