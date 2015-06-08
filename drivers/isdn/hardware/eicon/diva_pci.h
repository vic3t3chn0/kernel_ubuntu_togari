/* $Id: diva_pci.h,v 1.6 2003/01/04 15:29:45 schindler Exp $ */

#ifndef __DIVA_PCI_INTERFACE_H__
#define __DIVA_PCI_INTERFACE_H__

void __iomem *divasa_remap_pci_bar(diva_os_xdi_adapter_t *a,
<<<<<<< HEAD
<<<<<<< HEAD
				   int id,
				   unsigned long bar,
				   unsigned long area_length);
=======
			   int id,
			   unsigned long bar,
			   unsigned long area_length);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			   int id,
			   unsigned long bar,
			   unsigned long area_length);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void divasa_unmap_pci_bar(void __iomem *bar);
unsigned long divasa_get_pci_irq(unsigned char bus,
				 unsigned char func, void *pci_dev_handle);
unsigned long divasa_get_pci_bar(unsigned char bus,
				 unsigned char func,
				 int bar, void *pci_dev_handle);
byte diva_os_get_pci_bus(void *pci_dev_handle);
byte diva_os_get_pci_func(void *pci_dev_handle);

#endif
