#ifndef __LINUX_USB_PCI_QUIRKS_H
#define __LINUX_USB_PCI_QUIRKS_H

#ifdef CONFIG_PCI
void uhci_reset_hc(struct pci_dev *pdev, unsigned long base);
int uhci_check_and_reset_hc(struct pci_dev *pdev, unsigned long base);
int usb_amd_find_chipset_info(void);
void usb_amd_dev_put(void);
void usb_amd_quirk_pll_disable(void);
void usb_amd_quirk_pll_enable(void);
bool usb_is_intel_switchable_xhci(struct pci_dev *pdev);
void usb_enable_xhci_ports(struct pci_dev *xhci_pdev);
<<<<<<< HEAD
<<<<<<< HEAD
=======
void usb_disable_xhci_ports(struct pci_dev *xhci_pdev);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
void usb_disable_xhci_ports(struct pci_dev *xhci_pdev);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#else
static inline void usb_amd_quirk_pll_disable(void) {}
static inline void usb_amd_quirk_pll_enable(void) {}
static inline void usb_amd_dev_put(void) {}
<<<<<<< HEAD
<<<<<<< HEAD
=======
static inline void usb_disable_xhci_ports(struct pci_dev *xhci_pdev) {}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static inline void usb_disable_xhci_ports(struct pci_dev *xhci_pdev) {}
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif  /* CONFIG_PCI */

#endif  /*  __LINUX_USB_PCI_QUIRKS_H  */
