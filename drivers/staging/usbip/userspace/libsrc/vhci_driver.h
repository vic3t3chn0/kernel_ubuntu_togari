/*
 * Copyright (C) 2005-2007 Takahiro Hirofuchi
 */

<<<<<<< HEAD
<<<<<<< HEAD
#ifndef __VHCI_DRIVER_H
#define __VHCI_DRIVER_H

#include <sysfs/libsysfs.h>
#include <stdint.h>

#include "usbip_common.h"

#define USBIP_VHCI_BUS_TYPE "platform"
#define MAXNPORT 128

struct usbip_class_device {
	char class_path[SYSFS_PATH_MAX];
	char dev_path[SYSFS_PATH_MAX];
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifndef _VHCI_DRIVER_H
#define _VHCI_DRIVER_H

#include "usbip.h"



#define MAXNPORT 128

struct class_device {
	char clspath[SYSFS_PATH_MAX];
	char devpath[SYSFS_PATH_MAX];
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

struct usbip_imported_device {
	uint8_t port;
	uint32_t status;

	uint32_t devid;

	uint8_t busnum;
	uint8_t devnum;

<<<<<<< HEAD
<<<<<<< HEAD
	/* usbip_class_device list */
	struct dlist *cdev_list;
	struct usbip_usb_device udev;
=======

	struct dlist *cdev_list;	/* list of class device */
	struct usb_device udev;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

	struct dlist *cdev_list;	/* list of class device */
	struct usb_device udev;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

struct usbip_vhci_driver {
	char sysfs_mntpath[SYSFS_PATH_MAX];
<<<<<<< HEAD
<<<<<<< HEAD

	/* /sys/devices/platform/vhci_hcd */
	struct sysfs_device *hc_device;

	/* usbip_class_device list */
	struct dlist *cdev_list;
=======
	struct sysfs_device *hc_device; /* /sys/devices/platform/vhci_hcd */

	struct dlist *cdev_list;	/* list of class device */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct sysfs_device *hc_device; /* /sys/devices/platform/vhci_hcd */

	struct dlist *cdev_list;	/* list of class device */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	int nports;
	struct usbip_imported_device idev[MAXNPORT];
};


extern struct usbip_vhci_driver *vhci_driver;

int usbip_vhci_driver_open(void);
void usbip_vhci_driver_close(void);

int  usbip_vhci_refresh_device_list(void);


int usbip_vhci_get_free_port(void);
int usbip_vhci_attach_device2(uint8_t port, int sockfd, uint32_t devid,
		uint32_t speed);

/* will be removed */
int usbip_vhci_attach_device(uint8_t port, int sockfd, uint8_t busnum,
		uint8_t devnum, uint32_t speed);

int usbip_vhci_detach_device(uint8_t port);
<<<<<<< HEAD
<<<<<<< HEAD

#endif /* __VHCI_DRIVER_H */
=======
#endif
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#endif
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
