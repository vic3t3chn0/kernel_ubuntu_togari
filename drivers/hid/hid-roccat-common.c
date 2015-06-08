/*
 * Roccat common functions for device specific drivers
 *
 * Copyright (c) 2011 Stefan Achatz <erazor_de@users.sourceforge.net>
 */

/*
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 */

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/hid.h>
#include <linux/slab.h>
#include <linux/module.h>
#include "hid-roccat-common.h"

static inline uint16_t roccat_common_feature_report(uint8_t report_id)
{
	return 0x300 | report_id;
}

int roccat_common_receive(struct usb_device *usb_dev, uint report_id,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/slab.h>
#include "hid-roccat-common.h"

int roccat_common_receive(struct usb_device *usb_dev, uint usb_command,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		void *data, uint size)
{
	char *buf;
	int len;

	buf = kmalloc(size, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	len = usb_control_msg(usb_dev, usb_rcvctrlpipe(usb_dev, 0),
<<<<<<< HEAD
<<<<<<< HEAD
			HID_REQ_GET_REPORT,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_IN,
			roccat_common_feature_report(report_id),
			0, buf, size, USB_CTRL_SET_TIMEOUT);
=======
			USB_REQ_CLEAR_FEATURE,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_IN,
			usb_command, 0, buf, size, USB_CTRL_SET_TIMEOUT);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			USB_REQ_CLEAR_FEATURE,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_IN,
			usb_command, 0, buf, size, USB_CTRL_SET_TIMEOUT);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	memcpy(data, buf, size);
	kfree(buf);
	return ((len < 0) ? len : ((len != size) ? -EIO : 0));
}
EXPORT_SYMBOL_GPL(roccat_common_receive);

<<<<<<< HEAD
<<<<<<< HEAD
int roccat_common_send(struct usb_device *usb_dev, uint report_id,
=======
int roccat_common_send(struct usb_device *usb_dev, uint usb_command,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
int roccat_common_send(struct usb_device *usb_dev, uint usb_command,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		void const *data, uint size)
{
	char *buf;
	int len;

<<<<<<< HEAD
<<<<<<< HEAD
	buf = kmemdup(data, size, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	len = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			HID_REQ_SET_REPORT,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_OUT,
			roccat_common_feature_report(report_id),
			0, buf, size, USB_CTRL_SET_TIMEOUT);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	buf = kmalloc(size, GFP_KERNEL);
	if (buf == NULL)
		return -ENOMEM;

	memcpy(buf, data, size);

	len = usb_control_msg(usb_dev, usb_sndctrlpipe(usb_dev, 0),
			USB_REQ_SET_CONFIGURATION,
			USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_DIR_OUT,
			usb_command, 0, buf, size, USB_CTRL_SET_TIMEOUT);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	kfree(buf);
	return ((len < 0) ? len : ((len != size) ? -EIO : 0));
}
EXPORT_SYMBOL_GPL(roccat_common_send);

MODULE_AUTHOR("Stefan Achatz");
MODULE_DESCRIPTION("USB Roccat common driver");
MODULE_LICENSE("GPL v2");
