/*
 * ZIO Motherboard USB driver
 *
 * Copyright (C) 2010 Zilogic Systems <code@zilogic.com>
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

static const struct usb_device_id id_table[] = {
	{ USB_DEVICE(0x1CBE, 0x0103) },
	{ },
};
MODULE_DEVICE_TABLE(usb, id_table);

static struct usb_driver zio_driver = {
	.name =		"zio",
	.probe =	usb_serial_probe,
	.disconnect =	usb_serial_disconnect,
	.id_table =	id_table,
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.no_dynamic_id =	1,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.no_dynamic_id =	1,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static struct usb_serial_driver zio_device = {
	.driver = {
		.owner =	THIS_MODULE,
		.name =		"zio",
	},
	.id_table =		id_table,
<<<<<<< HEAD
<<<<<<< HEAD
	.num_ports =		1,
};

static struct usb_serial_driver * const serial_drivers[] = {
	&zio_device, NULL
};

module_usb_serial_driver(zio_driver, serial_drivers);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.usb_driver =		&zio_driver,
	.num_ports =		1,
};

static int __init zio_init(void)
{
	int retval;

	retval = usb_serial_register(&zio_device);
	if (retval)
		return retval;
	retval = usb_register(&zio_driver);
	if (retval)
		usb_serial_deregister(&zio_device);
	return retval;
}

static void __exit zio_exit(void)
{
	usb_deregister(&zio_driver);
	usb_serial_deregister(&zio_device);
}

module_init(zio_init);
module_exit(zio_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
MODULE_LICENSE("GPL");
