/*
 * Broadcom specific AMBA
 * PCI Core
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright 2005, 2011, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <m@bues.ch>
 * Copyright 2011, 2012, Hauke Mehrtens <hauke@hauke-m.de>
=======
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <mb@bu3sch.de>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Copyright 2005, Broadcom Corporation
 * Copyright 2006, 2007, Michael Buesch <mb@bu3sch.de>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Licensed under the GNU/GPL. See COPYING for details.
 */

#include "bcma_private.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/export.h>
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/bcma/bcma.h>

/**************************************************
 * R/W ops.
 **************************************************/

<<<<<<< HEAD
<<<<<<< HEAD
u32 bcma_pcie_read(struct bcma_drv_pci *pc, u32 address)
{
	pcicore_write32(pc, BCMA_CORE_PCI_PCIEIND_ADDR, address);
	pcicore_read32(pc, BCMA_CORE_PCI_PCIEIND_ADDR);
	return pcicore_read32(pc, BCMA_CORE_PCI_PCIEIND_DATA);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static u32 bcma_pcie_read(struct bcma_drv_pci *pc, u32 address)
{
	pcicore_write32(pc, 0x130, address);
	pcicore_read32(pc, 0x130);
	return pcicore_read32(pc, 0x134);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

#if 0
static void bcma_pcie_write(struct bcma_drv_pci *pc, u32 address, u32 data)
{
<<<<<<< HEAD
<<<<<<< HEAD
	pcicore_write32(pc, BCMA_CORE_PCI_PCIEIND_ADDR, address);
	pcicore_read32(pc, BCMA_CORE_PCI_PCIEIND_ADDR);
	pcicore_write32(pc, BCMA_CORE_PCI_PCIEIND_DATA, data);
=======
	pcicore_write32(pc, 0x130, address);
	pcicore_read32(pc, 0x130);
	pcicore_write32(pc, 0x134, data);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	pcicore_write32(pc, 0x130, address);
	pcicore_read32(pc, 0x130);
	pcicore_write32(pc, 0x134, data);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
#endif

static void bcma_pcie_mdio_set_phy(struct bcma_drv_pci *pc, u8 phy)
{
<<<<<<< HEAD
<<<<<<< HEAD
	u32 v;
	int i;

	v = BCMA_CORE_PCI_MDIODATA_START;
	v |= BCMA_CORE_PCI_MDIODATA_WRITE;
	v |= (BCMA_CORE_PCI_MDIODATA_DEV_ADDR <<
	      BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF);
	v |= (BCMA_CORE_PCI_MDIODATA_BLK_ADDR <<
	      BCMA_CORE_PCI_MDIODATA_REGADDR_SHF);
	v |= BCMA_CORE_PCI_MDIODATA_TA;
	v |= (phy << 4);
	pcicore_write32(pc, BCMA_CORE_PCI_MDIO_DATA, v);

	udelay(10);
	for (i = 0; i < 200; i++) {
		v = pcicore_read32(pc, BCMA_CORE_PCI_MDIO_CONTROL);
		if (v & BCMA_CORE_PCI_MDIOCTL_ACCESS_DONE)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	const u16 mdio_control = 0x128;
	const u16 mdio_data = 0x12C;
	u32 v;
	int i;

	v = (1 << 30); /* Start of Transaction */
	v |= (1 << 28); /* Write Transaction */
	v |= (1 << 17); /* Turnaround */
	v |= (0x1F << 18);
	v |= (phy << 4);
	pcicore_write32(pc, mdio_data, v);

	udelay(10);
	for (i = 0; i < 200; i++) {
		v = pcicore_read32(pc, mdio_control);
		if (v & 0x100 /* Trans complete */)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;
		msleep(1);
	}
}

static u16 bcma_pcie_mdio_read(struct bcma_drv_pci *pc, u8 device, u8 address)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
	const u16 mdio_control = 0x128;
	const u16 mdio_data = 0x12C;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	const u16 mdio_control = 0x128;
	const u16 mdio_data = 0x12C;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int max_retries = 10;
	u16 ret = 0;
	u32 v;
	int i;

<<<<<<< HEAD
<<<<<<< HEAD
	/* enable mdio access to SERDES */
	v = BCMA_CORE_PCI_MDIOCTL_PREAM_EN;
	v |= BCMA_CORE_PCI_MDIOCTL_DIVISOR_VAL;
	pcicore_write32(pc, BCMA_CORE_PCI_MDIO_CONTROL, v);
=======
	v = 0x80; /* Enable Preamble Sequence */
	v |= 0x2; /* MDIO Clock Divisor */
	pcicore_write32(pc, mdio_control, v);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	v = 0x80; /* Enable Preamble Sequence */
	v |= 0x2; /* MDIO Clock Divisor */
	pcicore_write32(pc, mdio_control, v);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (pc->core->id.rev >= 10) {
		max_retries = 200;
		bcma_pcie_mdio_set_phy(pc, device);
<<<<<<< HEAD
<<<<<<< HEAD
		v = (BCMA_CORE_PCI_MDIODATA_DEV_ADDR <<
		     BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF);
		v |= (address << BCMA_CORE_PCI_MDIODATA_REGADDR_SHF);
	} else {
		v = (device << BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF_OLD);
		v |= (address << BCMA_CORE_PCI_MDIODATA_REGADDR_SHF_OLD);
	}

	v = BCMA_CORE_PCI_MDIODATA_START;
	v |= BCMA_CORE_PCI_MDIODATA_READ;
	v |= BCMA_CORE_PCI_MDIODATA_TA;

	pcicore_write32(pc, BCMA_CORE_PCI_MDIO_DATA, v);
	/* Wait for the device to complete the transaction */
	udelay(10);
	for (i = 0; i < max_retries; i++) {
		v = pcicore_read32(pc, BCMA_CORE_PCI_MDIO_CONTROL);
		if (v & BCMA_CORE_PCI_MDIOCTL_ACCESS_DONE) {
			udelay(10);
			ret = pcicore_read32(pc, BCMA_CORE_PCI_MDIO_DATA);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	v = (1 << 30); /* Start of Transaction */
	v |= (1 << 29); /* Read Transaction */
	v |= (1 << 17); /* Turnaround */
	if (pc->core->id.rev < 10)
		v |= (u32)device << 22;
	v |= (u32)address << 18;
	pcicore_write32(pc, mdio_data, v);
	/* Wait for the device to complete the transaction */
	udelay(10);
	for (i = 0; i < max_retries; i++) {
		v = pcicore_read32(pc, mdio_control);
		if (v & 0x100 /* Trans complete */) {
			udelay(10);
			ret = pcicore_read32(pc, mdio_data);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;
		}
		msleep(1);
	}
<<<<<<< HEAD
<<<<<<< HEAD
	pcicore_write32(pc, BCMA_CORE_PCI_MDIO_CONTROL, 0);
=======
	pcicore_write32(pc, mdio_control, 0);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	pcicore_write32(pc, mdio_control, 0);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static void bcma_pcie_mdio_write(struct bcma_drv_pci *pc, u8 device,
				u8 address, u16 data)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
	const u16 mdio_control = 0x128;
	const u16 mdio_data = 0x12C;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	const u16 mdio_control = 0x128;
	const u16 mdio_data = 0x12C;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int max_retries = 10;
	u32 v;
	int i;

<<<<<<< HEAD
<<<<<<< HEAD
	/* enable mdio access to SERDES */
	v = BCMA_CORE_PCI_MDIOCTL_PREAM_EN;
	v |= BCMA_CORE_PCI_MDIOCTL_DIVISOR_VAL;
	pcicore_write32(pc, BCMA_CORE_PCI_MDIO_CONTROL, v);
=======
	v = 0x80; /* Enable Preamble Sequence */
	v |= 0x2; /* MDIO Clock Divisor */
	pcicore_write32(pc, mdio_control, v);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	v = 0x80; /* Enable Preamble Sequence */
	v |= 0x2; /* MDIO Clock Divisor */
	pcicore_write32(pc, mdio_control, v);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (pc->core->id.rev >= 10) {
		max_retries = 200;
		bcma_pcie_mdio_set_phy(pc, device);
<<<<<<< HEAD
<<<<<<< HEAD
		v = (BCMA_CORE_PCI_MDIODATA_DEV_ADDR <<
		     BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF);
		v |= (address << BCMA_CORE_PCI_MDIODATA_REGADDR_SHF);
	} else {
		v = (device << BCMA_CORE_PCI_MDIODATA_DEVADDR_SHF_OLD);
		v |= (address << BCMA_CORE_PCI_MDIODATA_REGADDR_SHF_OLD);
	}

	v = BCMA_CORE_PCI_MDIODATA_START;
	v |= BCMA_CORE_PCI_MDIODATA_WRITE;
	v |= BCMA_CORE_PCI_MDIODATA_TA;
	v |= data;
	pcicore_write32(pc, BCMA_CORE_PCI_MDIO_DATA, v);
	/* Wait for the device to complete the transaction */
	udelay(10);
	for (i = 0; i < max_retries; i++) {
		v = pcicore_read32(pc, BCMA_CORE_PCI_MDIO_CONTROL);
		if (v & BCMA_CORE_PCI_MDIOCTL_ACCESS_DONE)
			break;
		msleep(1);
	}
	pcicore_write32(pc, BCMA_CORE_PCI_MDIO_CONTROL, 0);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	v = (1 << 30); /* Start of Transaction */
	v |= (1 << 28); /* Write Transaction */
	v |= (1 << 17); /* Turnaround */
	if (pc->core->id.rev < 10)
		v |= (u32)device << 22;
	v |= (u32)address << 18;
	v |= data;
	pcicore_write32(pc, mdio_data, v);
	/* Wait for the device to complete the transaction */
	udelay(10);
	for (i = 0; i < max_retries; i++) {
		v = pcicore_read32(pc, mdio_control);
		if (v & 0x100 /* Trans complete */)
			break;
		msleep(1);
	}
	pcicore_write32(pc, mdio_control, 0);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/**************************************************
 * Workarounds.
 **************************************************/

static u8 bcma_pcicore_polarity_workaround(struct bcma_drv_pci *pc)
{
<<<<<<< HEAD
<<<<<<< HEAD
	u32 tmp;

	tmp = bcma_pcie_read(pc, BCMA_CORE_PCI_PLP_STATUSREG);
	if (tmp & BCMA_CORE_PCI_PLP_POLARITYINV_STAT)
		return BCMA_CORE_PCI_SERDES_RX_CTRL_FORCE |
		       BCMA_CORE_PCI_SERDES_RX_CTRL_POLARITY;
	else
		return BCMA_CORE_PCI_SERDES_RX_CTRL_FORCE;
=======
	return (bcma_pcie_read(pc, 0x204) & 0x10) ? 0xC0 : 0x80;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return (bcma_pcie_read(pc, 0x204) & 0x10) ? 0xC0 : 0x80;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void bcma_pcicore_serdes_workaround(struct bcma_drv_pci *pc)
{
<<<<<<< HEAD
<<<<<<< HEAD
	u16 tmp;

	bcma_pcie_mdio_write(pc, BCMA_CORE_PCI_MDIODATA_DEV_RX,
	                     BCMA_CORE_PCI_SERDES_RX_CTRL,
			     bcma_pcicore_polarity_workaround(pc));
	tmp = bcma_pcie_mdio_read(pc, BCMA_CORE_PCI_MDIODATA_DEV_PLL,
	                          BCMA_CORE_PCI_SERDES_PLL_CTRL);
	if (tmp & BCMA_CORE_PCI_PLL_CTRL_FREQDET_EN)
		bcma_pcie_mdio_write(pc, BCMA_CORE_PCI_MDIODATA_DEV_PLL,
		                     BCMA_CORE_PCI_SERDES_PLL_CTRL,
		                     tmp & ~BCMA_CORE_PCI_PLL_CTRL_FREQDET_EN);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	const u8 serdes_pll_device = 0x1D;
	const u8 serdes_rx_device = 0x1F;
	u16 tmp;

	bcma_pcie_mdio_write(pc, serdes_rx_device, 1 /* Control */,
			      bcma_pcicore_polarity_workaround(pc));
	tmp = bcma_pcie_mdio_read(pc, serdes_pll_device, 1 /* Control */);
	if (tmp & 0x4000)
		bcma_pcie_mdio_write(pc, serdes_pll_device, 1, tmp & ~0x4000);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/**************************************************
 * Init.
 **************************************************/

<<<<<<< HEAD
<<<<<<< HEAD
static void __devinit bcma_core_pci_clientmode_init(struct bcma_drv_pci *pc)
{
	bcma_pcicore_serdes_workaround(pc);
}

void __devinit bcma_core_pci_init(struct bcma_drv_pci *pc)
{
	if (pc->setup_done)
		return;

#ifdef CONFIG_BCMA_DRIVER_PCI_HOSTMODE
	pc->hostmode = bcma_core_pci_is_in_hostmode(pc);
	if (pc->hostmode)
		bcma_core_pci_hostmode_init(pc);
#endif /* CONFIG_BCMA_DRIVER_PCI_HOSTMODE */

	if (!pc->hostmode)
		bcma_core_pci_clientmode_init(pc);
}

int bcma_core_pci_irq_ctl(struct bcma_drv_pci *pc, struct bcma_device *core,
			  bool enable)
{
	struct pci_dev *pdev = pc->core->bus->host_pci;
	u32 coremask, tmp;
	int err = 0;

	if (core->bus->hosttype != BCMA_HOSTTYPE_PCI) {
		/* This bcma device is not on a PCI host-bus. So the IRQs are
		 * not routed through the PCI core.
		 * So we must not enable routing through the PCI core. */
		goto out;
	}

	err = pci_read_config_dword(pdev, BCMA_PCI_IRQMASK, &tmp);
	if (err)
		goto out;

	coremask = BIT(core->core_index) << 8;
	if (enable)
		tmp |= coremask;
	else
		tmp &= ~coremask;

	err = pci_write_config_dword(pdev, BCMA_PCI_IRQMASK, tmp);

out:
	return err;
}
EXPORT_SYMBOL_GPL(bcma_core_pci_irq_ctl);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void bcma_core_pci_init(struct bcma_drv_pci *pc)
{
	bcma_pcicore_serdes_workaround(pc);
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
