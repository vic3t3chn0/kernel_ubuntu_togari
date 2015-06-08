/*
 * Driver for ICPlus PHYs
 *
 * Copyright (c) 2007 Freescale Semiconductor, Inc.
 *
 * This program is free software; you can redistribute  it and/or modify it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 *
 */
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/errno.h>
#include <linux/unistd.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/skbuff.h>
#include <linux/spinlock.h>
#include <linux/mm.h>
#include <linux/module.h>
#include <linux/mii.h>
#include <linux/ethtool.h>
#include <linux/phy.h>

#include <asm/io.h>
#include <asm/irq.h>
#include <asm/uaccess.h>

<<<<<<< HEAD
MODULE_DESCRIPTION("ICPlus IP175C/IP101A/IP101G/IC1001 PHY drivers");
MODULE_AUTHOR("Michael Barkowski");
MODULE_LICENSE("GPL");

/* IP101A/G - IP1001 */
#define IP10XX_SPEC_CTRL_STATUS		16	/* Spec. Control Register */
#define IP1001_SPEC_CTRL_STATUS_2	20	/* IP1001 Spec. Control Reg 2 */
#define IP1001_PHASE_SEL_MASK		3	/* IP1001 RX/TXPHASE_SEL */
#define IP1001_APS_ON			11	/* IP1001 APS Mode  bit */
#define IP101A_G_APS_ON			2	/* IP101A/G APS Mode bit */
#define IP101A_G_IRQ_CONF_STATUS	0x11	/* Conf Info IRQ & Status Reg */

=======
MODULE_DESCRIPTION("ICPlus IP175C/IC1001 PHY drivers");
MODULE_AUTHOR("Michael Barkowski");
MODULE_LICENSE("GPL");

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
static int ip175c_config_init(struct phy_device *phydev)
{
	int err, i;
	static int full_reset_performed = 0;

	if (full_reset_performed == 0) {

		/* master reset */
<<<<<<< HEAD
		err = mdiobus_write(phydev->bus, 30, 0, 0x175c);
=======
		err = phydev->bus->write(phydev->bus, 30, 0, 0x175c);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		if (err < 0)
			return err;

		/* ensure no bus delays overlap reset period */
<<<<<<< HEAD
		err = mdiobus_read(phydev->bus, 30, 0);
=======
		err = phydev->bus->read(phydev->bus, 30, 0);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

		/* data sheet specifies reset period is 2 msec */
		mdelay(2);

		/* enable IP175C mode */
<<<<<<< HEAD
		err = mdiobus_write(phydev->bus, 29, 31, 0x175c);
=======
		err = phydev->bus->write(phydev->bus, 29, 31, 0x175c);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		if (err < 0)
			return err;

		/* Set MII0 speed and duplex (in PHY mode) */
<<<<<<< HEAD
		err = mdiobus_write(phydev->bus, 29, 22, 0x420);
=======
		err = phydev->bus->write(phydev->bus, 29, 22, 0x420);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		if (err < 0)
			return err;

		/* reset switch ports */
		for (i = 0; i < 5; i++) {
<<<<<<< HEAD
			err = mdiobus_write(phydev->bus, i,
					    MII_BMCR, BMCR_RESET);
=======
			err = phydev->bus->write(phydev->bus, i,
						 MII_BMCR, BMCR_RESET);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
			if (err < 0)
				return err;
		}

		for (i = 0; i < 5; i++)
<<<<<<< HEAD
			err = mdiobus_read(phydev->bus, i, MII_BMCR);
=======
			err = phydev->bus->read(phydev->bus, i, MII_BMCR);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

		mdelay(2);

		full_reset_performed = 1;
	}

	if (phydev->addr != 4) {
		phydev->state = PHY_RUNNING;
		phydev->speed = SPEED_100;
		phydev->duplex = DUPLEX_FULL;
		phydev->link = 1;
		netif_carrier_on(phydev->attached_dev);
	}

	return 0;
}

<<<<<<< HEAD
static int ip1xx_reset(struct phy_device *phydev)
{
	int bmcr;

	/* Software Reset PHY */
	bmcr = phy_read(phydev, MII_BMCR);
	if (bmcr < 0)
		return bmcr;
	bmcr |= BMCR_RESET;
	bmcr = phy_write(phydev, MII_BMCR, bmcr);
	if (bmcr < 0)
		return bmcr;

	do {
		bmcr = phy_read(phydev, MII_BMCR);
		if (bmcr < 0)
			return bmcr;
	} while (bmcr & BMCR_RESET);

	return 0;
}

static int ip1001_config_init(struct phy_device *phydev)
{
	int c;

	c = ip1xx_reset(phydev);
	if (c < 0)
		return c;

	/* Enable Auto Power Saving mode */
	c = phy_read(phydev, IP1001_SPEC_CTRL_STATUS_2);
	if (c < 0)
		return c;
	c |= IP1001_APS_ON;
	c = phy_write(phydev, IP1001_SPEC_CTRL_STATUS_2, c);
	if (c < 0)
		return c;

	if (phydev->interface == PHY_INTERFACE_MODE_RGMII) {
		/* Additional delay (2ns) used to adjust RX clock phase
		 * at RGMII interface */
		c = phy_read(phydev, IP10XX_SPEC_CTRL_STATUS);
		if (c < 0)
			return c;

		c |= IP1001_PHASE_SEL_MASK;
		c = phy_write(phydev, IP10XX_SPEC_CTRL_STATUS, c);
		if (c < 0)
			return c;
	}

	return 0;
}

static int ip101a_g_config_init(struct phy_device *phydev)
{
	int c;

	c = ip1xx_reset(phydev);
	if (c < 0)
		return c;

	/* Enable Auto Power Saving mode */
	c = phy_read(phydev, IP10XX_SPEC_CTRL_STATUS);
	c |= IP101A_G_APS_ON;

	return phy_write(phydev, IP10XX_SPEC_CTRL_STATUS, c);
=======
static int ip1001_config_init(struct phy_device *phydev)
{
	int err, value;

	/* Software Reset PHY */
	value = phy_read(phydev, MII_BMCR);
	value |= BMCR_RESET;
	err = phy_write(phydev, MII_BMCR, value);
	if (err < 0)
		return err;

	do {
		value = phy_read(phydev, MII_BMCR);
	} while (value & BMCR_RESET);

	/* Additional delay (2ns) used to adjust RX clock phase
	 * at GMII/ RGMII interface */
	value = phy_read(phydev, 16);
	value |= 0x3;

	err = phy_write(phydev, 16, value);
	if (err < 0)
		return err;

	return err;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static int ip175c_read_status(struct phy_device *phydev)
{
	if (phydev->addr == 4) /* WAN port */
		genphy_read_status(phydev);
	else
		/* Don't need to read status for switch ports */
		phydev->irq = PHY_IGNORE_INTERRUPT;

	return 0;
}

static int ip175c_config_aneg(struct phy_device *phydev)
{
	if (phydev->addr == 4) /* WAN port */
		genphy_config_aneg(phydev);

	return 0;
}

<<<<<<< HEAD
static int ip101a_g_ack_interrupt(struct phy_device *phydev)
{
	int err = phy_read(phydev, IP101A_G_IRQ_CONF_STATUS);
	if (err < 0)
		return err;

	return 0;
}

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
static struct phy_driver ip175c_driver = {
	.phy_id		= 0x02430d80,
	.name		= "ICPlus IP175C",
	.phy_id_mask	= 0x0ffffff0,
	.features	= PHY_BASIC_FEATURES,
	.config_init	= &ip175c_config_init,
	.config_aneg	= &ip175c_config_aneg,
	.read_status	= &ip175c_read_status,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
	.driver		= { .owner = THIS_MODULE,},
};

static struct phy_driver ip1001_driver = {
	.phy_id		= 0x02430d90,
	.name		= "ICPlus IP1001",
	.phy_id_mask	= 0x0ffffff0,
	.features	= PHY_GBIT_FEATURES | SUPPORTED_Pause |
			  SUPPORTED_Asym_Pause,
	.config_init	= &ip1001_config_init,
	.config_aneg	= &genphy_config_aneg,
	.read_status	= &genphy_read_status,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
	.driver		= { .owner = THIS_MODULE,},
};

<<<<<<< HEAD
static struct phy_driver ip101a_g_driver = {
	.phy_id		= 0x02430c54,
	.name		= "ICPlus IP101A/G",
	.phy_id_mask	= 0x0ffffff0,
	.features	= PHY_BASIC_FEATURES | SUPPORTED_Pause |
			  SUPPORTED_Asym_Pause,
	.flags		= PHY_HAS_INTERRUPT,
	.ack_interrupt	= ip101a_g_ack_interrupt,
	.config_init	= &ip101a_g_config_init,
	.config_aneg	= &genphy_config_aneg,
	.read_status	= &genphy_read_status,
	.suspend	= genphy_suspend,
	.resume		= genphy_resume,
	.driver		= { .owner = THIS_MODULE,},
};

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
static int __init icplus_init(void)
{
	int ret = 0;

	ret = phy_driver_register(&ip1001_driver);
	if (ret < 0)
		return -ENODEV;

<<<<<<< HEAD
	ret = phy_driver_register(&ip101a_g_driver);
	if (ret < 0)
		return -ENODEV;

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return phy_driver_register(&ip175c_driver);
}

static void __exit icplus_exit(void)
{
	phy_driver_unregister(&ip1001_driver);
<<<<<<< HEAD
	phy_driver_unregister(&ip101a_g_driver);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	phy_driver_unregister(&ip175c_driver);
}

module_init(icplus_init);
module_exit(icplus_exit);

static struct mdio_device_id __maybe_unused icplus_tbl[] = {
	{ 0x02430d80, 0x0ffffff0 },
	{ 0x02430d90, 0x0ffffff0 },
<<<<<<< HEAD
	{ 0x02430c54, 0x0ffffff0 },
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	{ }
};

MODULE_DEVICE_TABLE(mdio, icplus_tbl);
