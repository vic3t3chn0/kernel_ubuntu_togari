#ifndef LINUX_BCMA_PRIVATE_H_
#define LINUX_BCMA_PRIVATE_H_

#ifndef pr_fmt
#define pr_fmt(fmt)		KBUILD_MODNAME ": " fmt
#endif

#include <linux/bcma/bcma.h>
#include <linux/delay.h>

#define BCMA_CORE_SIZE		0x1000

struct bcma_bus;

/* main.c */
<<<<<<< HEAD
<<<<<<< HEAD
int __devinit bcma_bus_register(struct bcma_bus *bus);
void bcma_bus_unregister(struct bcma_bus *bus);
int __init bcma_bus_early_register(struct bcma_bus *bus,
				   struct bcma_device *core_cc,
				   struct bcma_device *core_mips);
#ifdef CONFIG_PM
int bcma_bus_suspend(struct bcma_bus *bus);
int bcma_bus_resume(struct bcma_bus *bus);
#endif

/* scan.c */
int bcma_bus_scan(struct bcma_bus *bus);
int __init bcma_bus_scan_early(struct bcma_bus *bus,
			       struct bcma_device_id *match,
			       struct bcma_device *core);
void bcma_init_bus(struct bcma_bus *bus);

/* sprom.c */
int bcma_sprom_get(struct bcma_bus *bus);

/* driver_chipcommon.c */
#ifdef CONFIG_BCMA_DRIVER_MIPS
void bcma_chipco_serial_init(struct bcma_drv_cc *cc);
#endif /* CONFIG_BCMA_DRIVER_MIPS */

/* driver_chipcommon_pmu.c */
u32 bcma_pmu_alp_clock(struct bcma_drv_cc *cc);
u32 bcma_pmu_get_clockcpu(struct bcma_drv_cc *cc);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern int bcma_bus_register(struct bcma_bus *bus);
extern void bcma_bus_unregister(struct bcma_bus *bus);

/* scan.c */
int bcma_bus_scan(struct bcma_bus *bus);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#ifdef CONFIG_BCMA_HOST_PCI
/* host_pci.c */
extern int __init bcma_host_pci_init(void);
extern void __exit bcma_host_pci_exit(void);
#endif /* CONFIG_BCMA_HOST_PCI */

<<<<<<< HEAD
<<<<<<< HEAD
/* driver_pci.c */
u32 bcma_pcie_read(struct bcma_drv_pci *pc, u32 address);

#ifdef CONFIG_BCMA_DRIVER_PCI_HOSTMODE
bool __devinit bcma_core_pci_is_in_hostmode(struct bcma_drv_pci *pc);
void __devinit bcma_core_pci_hostmode_init(struct bcma_drv_pci *pc);
#endif /* CONFIG_BCMA_DRIVER_PCI_HOSTMODE */

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
