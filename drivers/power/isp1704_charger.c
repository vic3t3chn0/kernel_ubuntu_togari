/*
 * ISP1704 USB Charger Detection driver
 *
 * Copyright (C) 2010 Nokia Corporation
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/sysfs.h>
#include <linux/platform_device.h>
#include <linux/power_supply.h>
#include <linux/delay.h>

#include <linux/usb/otg.h>
#include <linux/usb/ulpi.h>
#include <linux/usb/ch9.h>
#include <linux/usb/gadget.h>
#include <linux/power/isp1704_charger.h>

/* Vendor specific Power Control register */
#define ISP1704_PWR_CTRL		0x3d
#define ISP1704_PWR_CTRL_SWCTRL		(1 << 0)
#define ISP1704_PWR_CTRL_DET_COMP	(1 << 1)
#define ISP1704_PWR_CTRL_BVALID_RISE	(1 << 2)
#define ISP1704_PWR_CTRL_BVALID_FALL	(1 << 3)
#define ISP1704_PWR_CTRL_DP_WKPU_EN	(1 << 4)
#define ISP1704_PWR_CTRL_VDAT_DET	(1 << 5)
#define ISP1704_PWR_CTRL_DPVSRC_EN	(1 << 6)
#define ISP1704_PWR_CTRL_HWDETECT	(1 << 7)

#define NXP_VENDOR_ID			0x04cc

static u16 isp170x_id[] = {
	0x1704,
	0x1707,
};

struct isp1704_charger {
	struct device		*dev;
	struct power_supply	psy;
<<<<<<< HEAD
<<<<<<< HEAD
	struct usb_phy		*phy;
=======
	struct otg_transceiver	*otg;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct otg_transceiver	*otg;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct notifier_block	nb;
	struct work_struct	work;

	/* properties */
	char			model[8];
	unsigned		present:1;
	unsigned		online:1;
	unsigned		current_max;

	/* temp storage variables */
	unsigned long		event;
	unsigned		max_power;
};

<<<<<<< HEAD
<<<<<<< HEAD
static inline int isp1704_read(struct isp1704_charger *isp, u32 reg)
{
	return usb_phy_io_read(isp->phy, reg);
}

static inline int isp1704_write(struct isp1704_charger *isp, u32 val, u32 reg)
{
	return usb_phy_io_write(isp->phy, val, reg);
}

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Disable/enable the power from the isp1704 if a function for it
 * has been provided with platform data.
 */
static void isp1704_charger_set_power(struct isp1704_charger *isp, bool on)
{
	struct isp1704_charger_data	*board = isp->dev->platform_data;

<<<<<<< HEAD
<<<<<<< HEAD
	if (board && board->set_power)
=======
	if (board->set_power)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (board->set_power)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		board->set_power(on);
}

/*
 * Determine is the charging port DCP (dedicated charger) or CDP (Host/HUB
 * chargers).
 *
 * REVISIT: The method is defined in Battery Charging Specification and is
 * applicable to any ULPI transceiver. Nothing isp170x specific here.
 */
static inline int isp1704_charger_type(struct isp1704_charger *isp)
{
	u8 reg;
	u8 func_ctrl;
	u8 otg_ctrl;
	int type = POWER_SUPPLY_TYPE_USB_DCP;

<<<<<<< HEAD
<<<<<<< HEAD
	func_ctrl = isp1704_read(isp, ULPI_FUNC_CTRL);
	otg_ctrl = isp1704_read(isp, ULPI_OTG_CTRL);

	/* disable pulldowns */
	reg = ULPI_OTG_CTRL_DM_PULLDOWN | ULPI_OTG_CTRL_DP_PULLDOWN;
	isp1704_write(isp, ULPI_CLR(ULPI_OTG_CTRL), reg);

	/* full speed */
	isp1704_write(isp, ULPI_CLR(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_XCVRSEL_MASK);
	isp1704_write(isp, ULPI_SET(ULPI_FUNC_CTRL),
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	func_ctrl = otg_io_read(isp->otg, ULPI_FUNC_CTRL);
	otg_ctrl = otg_io_read(isp->otg, ULPI_OTG_CTRL);

	/* disable pulldowns */
	reg = ULPI_OTG_CTRL_DM_PULLDOWN | ULPI_OTG_CTRL_DP_PULLDOWN;
	otg_io_write(isp->otg, ULPI_CLR(ULPI_OTG_CTRL), reg);

	/* full speed */
	otg_io_write(isp->otg, ULPI_CLR(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_XCVRSEL_MASK);
	otg_io_write(isp->otg, ULPI_SET(ULPI_FUNC_CTRL),
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			ULPI_FUNC_CTRL_FULL_SPEED);

	/* Enable strong pull-up on DP (1.5K) and reset */
	reg = ULPI_FUNC_CTRL_TERMSELECT | ULPI_FUNC_CTRL_RESET;
<<<<<<< HEAD
<<<<<<< HEAD
	isp1704_write(isp, ULPI_SET(ULPI_FUNC_CTRL), reg);
	usleep_range(1000, 2000);

	reg = isp1704_read(isp, ULPI_DEBUG);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	otg_io_write(isp->otg, ULPI_SET(ULPI_FUNC_CTRL), reg);
	usleep_range(1000, 2000);

	reg = otg_io_read(isp->otg, ULPI_DEBUG);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if ((reg & 3) != 3)
		type = POWER_SUPPLY_TYPE_USB_CDP;

	/* recover original state */
<<<<<<< HEAD
<<<<<<< HEAD
	isp1704_write(isp, ULPI_FUNC_CTRL, func_ctrl);
	isp1704_write(isp, ULPI_OTG_CTRL, otg_ctrl);
=======
	otg_io_write(isp->otg, ULPI_FUNC_CTRL, func_ctrl);
	otg_io_write(isp->otg, ULPI_OTG_CTRL, otg_ctrl);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	otg_io_write(isp->otg, ULPI_FUNC_CTRL, func_ctrl);
	otg_io_write(isp->otg, ULPI_OTG_CTRL, otg_ctrl);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return type;
}

/*
 * ISP1704 detects PS/2 adapters as charger. To make sure the detected charger
 * is actually a dedicated charger, the following steps need to be taken.
 */
static inline int isp1704_charger_verify(struct isp1704_charger *isp)
{
	int	ret = 0;
	u8	r;

	/* Reset the transceiver */
<<<<<<< HEAD
<<<<<<< HEAD
	r = isp1704_read(isp, ULPI_FUNC_CTRL);
	r |= ULPI_FUNC_CTRL_RESET;
	isp1704_write(isp, ULPI_FUNC_CTRL, r);
=======
	r = otg_io_read(isp->otg, ULPI_FUNC_CTRL);
	r |= ULPI_FUNC_CTRL_RESET;
	otg_io_write(isp->otg, ULPI_FUNC_CTRL, r);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	r = otg_io_read(isp->otg, ULPI_FUNC_CTRL);
	r |= ULPI_FUNC_CTRL_RESET;
	otg_io_write(isp->otg, ULPI_FUNC_CTRL, r);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	usleep_range(1000, 2000);

	/* Set normal mode */
	r &= ~(ULPI_FUNC_CTRL_RESET | ULPI_FUNC_CTRL_OPMODE_MASK);
<<<<<<< HEAD
<<<<<<< HEAD
	isp1704_write(isp, ULPI_FUNC_CTRL, r);

	/* Clear the DP and DM pull-down bits */
	r = ULPI_OTG_CTRL_DP_PULLDOWN | ULPI_OTG_CTRL_DM_PULLDOWN;
	isp1704_write(isp, ULPI_CLR(ULPI_OTG_CTRL), r);

	/* Enable strong pull-up on DP (1.5K) and reset */
	r = ULPI_FUNC_CTRL_TERMSELECT | ULPI_FUNC_CTRL_RESET;
	isp1704_write(isp, ULPI_SET(ULPI_FUNC_CTRL), r);
	usleep_range(1000, 2000);

	/* Read the line state */
	if (!isp1704_read(isp, ULPI_DEBUG)) {
		/* Disable strong pull-up on DP (1.5K) */
		isp1704_write(isp, ULPI_CLR(ULPI_FUNC_CTRL),
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	otg_io_write(isp->otg, ULPI_FUNC_CTRL, r);

	/* Clear the DP and DM pull-down bits */
	r = ULPI_OTG_CTRL_DP_PULLDOWN | ULPI_OTG_CTRL_DM_PULLDOWN;
	otg_io_write(isp->otg, ULPI_CLR(ULPI_OTG_CTRL), r);

	/* Enable strong pull-up on DP (1.5K) and reset */
	r = ULPI_FUNC_CTRL_TERMSELECT | ULPI_FUNC_CTRL_RESET;
	otg_io_write(isp->otg, ULPI_SET(ULPI_FUNC_CTRL), r);
	usleep_range(1000, 2000);

	/* Read the line state */
	if (!otg_io_read(isp->otg, ULPI_DEBUG)) {
		/* Disable strong pull-up on DP (1.5K) */
		otg_io_write(isp->otg, ULPI_CLR(ULPI_FUNC_CTRL),
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				ULPI_FUNC_CTRL_TERMSELECT);
		return 1;
	}

	/* Is it a charger or PS/2 connection */

	/* Enable weak pull-up resistor on DP */
<<<<<<< HEAD
<<<<<<< HEAD
	isp1704_write(isp, ULPI_SET(ISP1704_PWR_CTRL),
			ISP1704_PWR_CTRL_DP_WKPU_EN);

	/* Disable strong pull-up on DP (1.5K) */
	isp1704_write(isp, ULPI_CLR(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_TERMSELECT);

	/* Enable weak pull-down resistor on DM */
	isp1704_write(isp, ULPI_SET(ULPI_OTG_CTRL),
			ULPI_OTG_CTRL_DM_PULLDOWN);

	/* It's a charger if the line states are clear */
	if (!(isp1704_read(isp, ULPI_DEBUG)))
		ret = 1;

	/* Disable weak pull-up resistor on DP */
	isp1704_write(isp, ULPI_CLR(ISP1704_PWR_CTRL),
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	otg_io_write(isp->otg, ULPI_SET(ISP1704_PWR_CTRL),
			ISP1704_PWR_CTRL_DP_WKPU_EN);

	/* Disable strong pull-up on DP (1.5K) */
	otg_io_write(isp->otg, ULPI_CLR(ULPI_FUNC_CTRL),
			ULPI_FUNC_CTRL_TERMSELECT);

	/* Enable weak pull-down resistor on DM */
	otg_io_write(isp->otg, ULPI_SET(ULPI_OTG_CTRL),
			ULPI_OTG_CTRL_DM_PULLDOWN);

	/* It's a charger if the line states are clear */
	if (!(otg_io_read(isp->otg, ULPI_DEBUG)))
		ret = 1;

	/* Disable weak pull-up resistor on DP */
	otg_io_write(isp->otg, ULPI_CLR(ISP1704_PWR_CTRL),
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			ISP1704_PWR_CTRL_DP_WKPU_EN);

	return ret;
}

static inline int isp1704_charger_detect(struct isp1704_charger *isp)
{
	unsigned long	timeout;
	u8		pwr_ctrl;
	int		ret = 0;

<<<<<<< HEAD
<<<<<<< HEAD
	pwr_ctrl = isp1704_read(isp, ISP1704_PWR_CTRL);

	/* set SW control bit in PWR_CTRL register */
	isp1704_write(isp, ISP1704_PWR_CTRL,
			ISP1704_PWR_CTRL_SWCTRL);

	/* enable manual charger detection */
	isp1704_write(isp, ULPI_SET(ISP1704_PWR_CTRL),
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	pwr_ctrl = otg_io_read(isp->otg, ISP1704_PWR_CTRL);

	/* set SW control bit in PWR_CTRL register */
	otg_io_write(isp->otg, ISP1704_PWR_CTRL,
			ISP1704_PWR_CTRL_SWCTRL);

	/* enable manual charger detection */
	otg_io_write(isp->otg, ULPI_SET(ISP1704_PWR_CTRL),
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			ISP1704_PWR_CTRL_SWCTRL
			| ISP1704_PWR_CTRL_DPVSRC_EN);
	usleep_range(1000, 2000);

	timeout = jiffies + msecs_to_jiffies(300);
	do {
		/* Check if there is a charger */
<<<<<<< HEAD
<<<<<<< HEAD
		if (isp1704_read(isp, ISP1704_PWR_CTRL)
=======
		if (otg_io_read(isp->otg, ISP1704_PWR_CTRL)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (otg_io_read(isp->otg, ISP1704_PWR_CTRL)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				& ISP1704_PWR_CTRL_VDAT_DET) {
			ret = isp1704_charger_verify(isp);
			break;
		}
	} while (!time_after(jiffies, timeout) && isp->online);

	/* recover original state */
<<<<<<< HEAD
<<<<<<< HEAD
	isp1704_write(isp, ISP1704_PWR_CTRL, pwr_ctrl);
=======
	otg_io_write(isp->otg, ISP1704_PWR_CTRL, pwr_ctrl);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	otg_io_write(isp->otg, ISP1704_PWR_CTRL, pwr_ctrl);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return ret;
}

static void isp1704_charger_work(struct work_struct *data)
{
	int			detect;
	unsigned long		event;
	unsigned		power;
	struct isp1704_charger	*isp =
		container_of(data, struct isp1704_charger, work);
	static DEFINE_MUTEX(lock);

	event = isp->event;
	power = isp->max_power;

	mutex_lock(&lock);

	if (event != USB_EVENT_NONE)
		isp1704_charger_set_power(isp, 1);

	switch (event) {
	case USB_EVENT_VBUS:
		isp->online = true;

		/* detect charger */
		detect = isp1704_charger_detect(isp);

		if (detect) {
			isp->present = detect;
			isp->psy.type = isp1704_charger_type(isp);
		}

		switch (isp->psy.type) {
		case POWER_SUPPLY_TYPE_USB_DCP:
			isp->current_max = 1800;
			break;
		case POWER_SUPPLY_TYPE_USB_CDP:
			/*
			 * Only 500mA here or high speed chirp
			 * handshaking may break
			 */
			isp->current_max = 500;
			/* FALLTHROUGH */
		case POWER_SUPPLY_TYPE_USB:
		default:
			/* enable data pullups */
<<<<<<< HEAD
<<<<<<< HEAD
			if (isp->phy->otg->gadget)
				usb_gadget_connect(isp->phy->otg->gadget);
=======
			if (isp->otg->gadget)
				usb_gadget_connect(isp->otg->gadget);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			if (isp->otg->gadget)
				usb_gadget_connect(isp->otg->gadget);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
		break;
	case USB_EVENT_NONE:
		isp->online = false;
		isp->current_max = 0;
		isp->present = 0;
		isp->current_max = 0;
		isp->psy.type = POWER_SUPPLY_TYPE_USB;

		/*
		 * Disable data pullups. We need to prevent the controller from
		 * enumerating.
		 *
		 * FIXME: This is here to allow charger detection with Host/HUB
		 * chargers. The pullups may be enabled elsewhere, so this can
		 * not be the final solution.
		 */
<<<<<<< HEAD
<<<<<<< HEAD
		if (isp->phy->otg->gadget)
			usb_gadget_disconnect(isp->phy->otg->gadget);
=======
		if (isp->otg->gadget)
			usb_gadget_disconnect(isp->otg->gadget);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (isp->otg->gadget)
			usb_gadget_disconnect(isp->otg->gadget);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		isp1704_charger_set_power(isp, 0);
		break;
	case USB_EVENT_ENUMERATED:
		if (isp->present)
			isp->current_max = 1800;
		else
			isp->current_max = power;
		break;
	default:
		goto out;
	}

	power_supply_changed(&isp->psy);
out:
	mutex_unlock(&lock);
}

static int isp1704_notifier_call(struct notifier_block *nb,
		unsigned long event, void *power)
{
	struct isp1704_charger *isp =
		container_of(nb, struct isp1704_charger, nb);

	isp->event = event;

	if (power)
		isp->max_power = *((unsigned *)power);

	schedule_work(&isp->work);

	return NOTIFY_OK;
}

static int isp1704_charger_get_property(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	struct isp1704_charger *isp =
		container_of(psy, struct isp1704_charger, psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = isp->present;
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = isp->online;
		break;
	case POWER_SUPPLY_PROP_CURRENT_MAX:
		val->intval = isp->current_max;
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = isp->model;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = "NXP";
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static enum power_supply_property power_props[] = {
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_CURRENT_MAX,
	POWER_SUPPLY_PROP_MODEL_NAME,
	POWER_SUPPLY_PROP_MANUFACTURER,
};

static inline int isp1704_test_ulpi(struct isp1704_charger *isp)
{
	int vendor;
	int product;
	int i;
	int ret = -ENODEV;

	/* Test ULPI interface */
<<<<<<< HEAD
<<<<<<< HEAD
	ret = isp1704_write(isp, ULPI_SCRATCH, 0xaa);
	if (ret < 0)
		return ret;

	ret = isp1704_read(isp, ULPI_SCRATCH);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = otg_io_write(isp->otg, ULPI_SCRATCH, 0xaa);
	if (ret < 0)
		return ret;

	ret = otg_io_read(isp->otg, ULPI_SCRATCH);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret < 0)
		return ret;

	if (ret != 0xaa)
		return -ENODEV;

	/* Verify the product and vendor id matches */
<<<<<<< HEAD
<<<<<<< HEAD
	vendor = isp1704_read(isp, ULPI_VENDOR_ID_LOW);
	vendor |= isp1704_read(isp, ULPI_VENDOR_ID_HIGH) << 8;
	if (vendor != NXP_VENDOR_ID)
		return -ENODEV;

	product = isp1704_read(isp, ULPI_PRODUCT_ID_LOW);
	product |= isp1704_read(isp, ULPI_PRODUCT_ID_HIGH) << 8;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	vendor = otg_io_read(isp->otg, ULPI_VENDOR_ID_LOW);
	vendor |= otg_io_read(isp->otg, ULPI_VENDOR_ID_HIGH) << 8;
	if (vendor != NXP_VENDOR_ID)
		return -ENODEV;

	product = otg_io_read(isp->otg, ULPI_PRODUCT_ID_LOW);
	product |= otg_io_read(isp->otg, ULPI_PRODUCT_ID_HIGH) << 8;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	for (i = 0; i < ARRAY_SIZE(isp170x_id); i++) {
		if (product == isp170x_id[i]) {
			sprintf(isp->model, "isp%x", product);
			return product;
		}
	}

	dev_err(isp->dev, "product id %x not matching known ids", product);

	return -ENODEV;
}

static int __devinit isp1704_charger_probe(struct platform_device *pdev)
{
	struct isp1704_charger	*isp;
	int			ret = -ENODEV;

	isp = kzalloc(sizeof *isp, GFP_KERNEL);
	if (!isp)
		return -ENOMEM;

<<<<<<< HEAD
<<<<<<< HEAD
	isp->phy = usb_get_transceiver();
	if (!isp->phy)
=======
	isp->otg = otg_get_transceiver();
	if (!isp->otg)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	isp->otg = otg_get_transceiver();
	if (!isp->otg)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto fail0;

	isp->dev = &pdev->dev;
	platform_set_drvdata(pdev, isp);

	isp1704_charger_set_power(isp, 1);

	ret = isp1704_test_ulpi(isp);
	if (ret < 0)
		goto fail1;

	isp->psy.name		= "isp1704";
	isp->psy.type		= POWER_SUPPLY_TYPE_USB;
	isp->psy.properties	= power_props;
	isp->psy.num_properties	= ARRAY_SIZE(power_props);
	isp->psy.get_property	= isp1704_charger_get_property;

	ret = power_supply_register(isp->dev, &isp->psy);
	if (ret)
		goto fail1;

	/*
<<<<<<< HEAD
<<<<<<< HEAD
	 * REVISIT: using work in order to allow the usb notifications to be
=======
	 * REVISIT: using work in order to allow the otg notifications to be
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * REVISIT: using work in order to allow the otg notifications to be
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 * made atomically in the future.
	 */
	INIT_WORK(&isp->work, isp1704_charger_work);

	isp->nb.notifier_call = isp1704_notifier_call;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = usb_register_notifier(isp->phy, &isp->nb);
=======
	ret = otg_register_notifier(isp->otg, &isp->nb);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ret = otg_register_notifier(isp->otg, &isp->nb);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret)
		goto fail2;

	dev_info(isp->dev, "registered with product id %s\n", isp->model);

	/*
	 * Taking over the D+ pullup.
	 *
	 * FIXME: The device will be disconnected if it was already
	 * enumerated. The charger driver should be always loaded before any
	 * gadget is loaded.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	if (isp->phy->otg->gadget)
		usb_gadget_disconnect(isp->phy->otg->gadget);

	/* Detect charger if VBUS is valid (the cable was already plugged). */
	ret = isp1704_read(isp, ULPI_USB_INT_STS);
	isp1704_charger_set_power(isp, 0);
	if ((ret & ULPI_INT_VBUS_VALID) && !isp->phy->otg->default_a) {
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (isp->otg->gadget)
		usb_gadget_disconnect(isp->otg->gadget);

	/* Detect charger if VBUS is valid (the cable was already plugged). */
	ret = otg_io_read(isp->otg, ULPI_USB_INT_STS);
	isp1704_charger_set_power(isp, 0);
	if ((ret & ULPI_INT_VBUS_VALID) && !isp->otg->default_a) {
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		isp->event = USB_EVENT_VBUS;
		schedule_work(&isp->work);
	}

	return 0;
fail2:
	power_supply_unregister(&isp->psy);
fail1:
<<<<<<< HEAD
<<<<<<< HEAD
	usb_put_transceiver(isp->phy);
=======
	otg_put_transceiver(isp->otg);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	otg_put_transceiver(isp->otg);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
fail0:
	kfree(isp);

	dev_err(&pdev->dev, "failed to register isp1704 with error %d\n", ret);

<<<<<<< HEAD
<<<<<<< HEAD
	isp1704_charger_set_power(isp, 0);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static int __devexit isp1704_charger_remove(struct platform_device *pdev)
{
	struct isp1704_charger *isp = platform_get_drvdata(pdev);

<<<<<<< HEAD
<<<<<<< HEAD
	usb_unregister_notifier(isp->phy, &isp->nb);
	power_supply_unregister(&isp->psy);
	usb_put_transceiver(isp->phy);
=======
	otg_unregister_notifier(isp->otg, &isp->nb);
	power_supply_unregister(&isp->psy);
	otg_put_transceiver(isp->otg);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	otg_unregister_notifier(isp->otg, &isp->nb);
	power_supply_unregister(&isp->psy);
	otg_put_transceiver(isp->otg);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	isp1704_charger_set_power(isp, 0);
	kfree(isp);

	return 0;
}

static struct platform_driver isp1704_charger_driver = {
	.driver = {
		.name = "isp1704_charger",
	},
	.probe = isp1704_charger_probe,
	.remove = __devexit_p(isp1704_charger_remove),
};

<<<<<<< HEAD
<<<<<<< HEAD
module_platform_driver(isp1704_charger_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init isp1704_charger_init(void)
{
	return platform_driver_register(&isp1704_charger_driver);
}
module_init(isp1704_charger_init);

static void __exit isp1704_charger_exit(void)
{
	platform_driver_unregister(&isp1704_charger_driver);
}
module_exit(isp1704_charger_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_ALIAS("platform:isp1704_charger");
MODULE_AUTHOR("Nokia Corporation");
MODULE_DESCRIPTION("ISP170x USB Charger driver");
MODULE_LICENSE("GPL");
