/*
 * Funsoft Serial USB driver
 *
 * Copyright (C) 2006 Greg Kroah-Hartman <gregkh@suse.de>
 *
 *	This program is free software; you can redistribute it and/or
 *	modify it under the terms of the GNU General Public License version
 *	2 as published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/module.h>
#include <linux/usb.h>
#include <linux/usb/serial.h>
#include <linux/uaccess.h>

<<<<<<< HEAD
static bool debug;
=======
static int debug;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

static const struct usb_device_id id_table[] = {
	{ USB_DEVICE(0x1404, 0xcddc) },
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_driver funsoft_driver = {
	.name =		"funsoft",
	.probe =	usb_serial_probe,
	.disconnect =	usb_serial_disconnect,
	.id_table =	id_table,
<<<<<<< HEAD
=======
	.no_dynamic_id = 	1,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
};

static struct usb_serial_driver funsoft_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"funsoft",
	},
	.id_table =		id_table,
<<<<<<< HEAD
	.num_ports =		1,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&funsoft_device, NULL
};

module_usb_serial_driver(funsoft_driver, serial_drivers);

=======
	.usb_driver = 		&funsoft_driver,
	.num_ports =		1,
};

static int __init funsoft_init(void)
{
	int retval;

	retval = usb_serial_register(&funsoft_device);
	if (retval)
		return retval;
	retval = usb_register(&funsoft_driver);
	if (retval)
		usb_serial_deregister(&funsoft_device);
	return retval;
}

static void __exit funsoft_exit(void)
{
	usb_deregister(&funsoft_driver);
	usb_serial_deregister(&funsoft_device);
}

module_init(funsoft_init);
module_exit(funsoft_exit);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
MODULE_LICENSE("GPL");

module_param(debug, bool, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug enabled or not");
