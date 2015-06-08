<<<<<<< HEAD
<<<<<<< HEAD
/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
=======
/*
 * Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
/*
 * Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

<<<<<<< HEAD
<<<<<<< HEAD
/* add additional information to our printk's */
#define pr_fmt(fmt) "%s: " fmt "\n", __func__

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/mutex.h>
#include <linux/platform_device.h>
#include <linux/ratelimit.h>
=======
#include <linux/platform_device.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <linux/platform_device.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/uaccess.h>
#include <linux/usb.h>
#include <linux/debugfs.h>
#include <mach/diag_bridge.h>

<<<<<<< HEAD
<<<<<<< HEAD
#define DRIVER_DESC	"USB host diag bridge driver"
#define DRIVER_VERSION	"1.0"

#define MAX_DIAG_BRIDGE_DEVS	2
#define AUTOSUSP_DELAY_WITH_USB 1000
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef CONFIG_MDM_HSIC_PM
#include <linux/mdm_hsic_pm.h>
static const char rmnet_pm_dev[] = "mdm_hsic_pm0";
#endif

#define DRIVER_DESC	"USB host diag bridge driver"
#define DRIVER_VERSION	"1.0"
/* zero_pky.patch */
#define IN_BUF_SIZE	16384
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

struct diag_bridge {
	struct usb_device	*udev;
	struct usb_interface	*ifc;
	struct usb_anchor	submitted;
	__u8			in_epAddr;
	__u8			out_epAddr;
	int			err;
	struct kref		kref;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mutex		ifc_mutex;
	struct diag_bridge_ops	*ops;
	struct platform_device	*pdev;
	unsigned		default_autosusp_delay;
	int			id;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct diag_bridge_ops	*ops;
	struct platform_device	*pdev;
	/* zero_pky.patch */
	unsigned char		*buf_in;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* debugging counters */
	unsigned long		bytes_to_host;
	unsigned long		bytes_to_mdm;
	unsigned		pending_reads;
	unsigned		pending_writes;
};
<<<<<<< HEAD
<<<<<<< HEAD
struct diag_bridge *__dev[MAX_DIAG_BRIDGE_DEVS];

int diag_bridge_open(int id, struct diag_bridge_ops *ops)
{
	struct diag_bridge	*dev;

	if (id < 0 || id >= MAX_DIAG_BRIDGE_DEVS) {
		pr_err("Invalid device ID");
		return -ENODEV;
	}

	dev = __dev[id];
	if (!dev) {
		pr_err("dev is null");
		return -ENODEV;
	}

	if (dev->ops) {
		pr_err("bridge already opened");
		return -EALREADY;
	}

	dev->ops = ops;
	dev->err = 0;

#ifdef CONFIG_PM_RUNTIME
	dev->default_autosusp_delay = dev->udev->dev.power.autosuspend_delay;
#endif
	pm_runtime_set_autosuspend_delay(&dev->udev->dev,
			AUTOSUSP_DELAY_WITH_USB);

	kref_get(&dev->kref);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct diag_bridge *__dev;

int diag_bridge_open(struct diag_bridge_ops *ops)
{
	struct diag_bridge	*dev = __dev;

	if (!dev) {
		err("dev is null");
		return -ENODEV;
	}

	dev->ops = ops;
	dev->err = 0;
	usb_kill_anchored_urbs(&dev->submitted);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}
EXPORT_SYMBOL(diag_bridge_open);

<<<<<<< HEAD
<<<<<<< HEAD
static void diag_bridge_delete(struct kref *kref)
{
	struct diag_bridge *dev = container_of(kref, struct diag_bridge, kref);
	int id = dev->id;

	usb_put_dev(dev->udev);
	__dev[id] = 0;
	kfree(dev);
}

void diag_bridge_close(int id)
{
	struct diag_bridge	*dev;

	if (id < 0 || id >= MAX_DIAG_BRIDGE_DEVS) {
		pr_err("Invalid device ID");
		return;
	}

	dev = __dev[id];
	if (!dev) {
		pr_err("dev is null");
		return;
	}

	if (!dev->ops) {
		pr_err("can't close bridge that was not open");
		return;
	}

	dev_dbg(&dev->ifc->dev, "%s:\n", __func__);

	usb_kill_anchored_urbs(&dev->submitted);
	dev->ops = 0;

	pm_runtime_set_autosuspend_delay(&dev->udev->dev,
			dev->default_autosusp_delay);

	kref_put(&dev->kref, diag_bridge_delete);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* zero_pky.patch */
/* Even when no driver is using the diag bridge
   we are setting default read on this endpoint.
   This will consume any packet sent by CP
   and its dropped  */
static void read_hsic_cb(struct urb* urb);
static void read_hsic(void)
{
	struct diag_bridge	*dev = __dev;
	struct urb              *urb = NULL;
	unsigned int            pipe;
	int                     ret;

	dev_info(&dev->udev->dev, "%s:\n", __func__);
	if (!dev->ifc) {
                dev_err(&dev->udev->dev, "device is disconnected\n");
                return;
	}

        /* if there was a previous unrecoverable error, just quit */
        if (dev->err)
                return;

        urb = usb_alloc_urb(0, GFP_KERNEL);
        if (!urb) {
                dev_err(&dev->udev->dev, "unable to allocate urb\n");
                return;
	}

        pipe = usb_rcvbulkpipe(dev->udev, dev->in_epAddr);
        usb_fill_bulk_urb(urb, dev->udev, pipe, dev->buf_in,IN_BUF_SIZE,
		read_hsic_cb, dev);
        usb_anchor_urb(urb, &dev->submitted);
        ret = usb_submit_urb(urb, GFP_KERNEL);
        if (ret) {
		dev_err(&dev->udev->dev, "submitting urb failed err:%d\n", ret);
		dev->pending_reads--;
                usb_unanchor_urb(urb);
                usb_free_urb(urb);
		return;
        }

        usb_free_urb(urb);
}

static void read_hsic_cb(struct urb *urb)
{
	struct diag_bridge	*dev = urb->context;
	struct diag_bridge_ops	*cbs = dev->ops;

	pr_info("%s: status:%d actual:%d\n", __func__,
					urb->status, urb->actual_length);

	/* Drop the packet */
	if (urb->status == -EPROTO) {
		pr_err("%s: drop packet from protocol error\n", __func__);
		return;
	}
}

void diag_bridge_close(void)
{
	struct diag_bridge	*dev = __dev;

	dev_dbg(&dev->udev->dev, "%s:\n", __func__);

	usb_kill_anchored_urbs(&dev->submitted);

	dev->ops = 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
EXPORT_SYMBOL(diag_bridge_close);

static void diag_bridge_read_cb(struct urb *urb)
{
	struct diag_bridge	*dev = urb->context;
	struct diag_bridge_ops	*cbs = dev->ops;

<<<<<<< HEAD
<<<<<<< HEAD
	dev_dbg(&dev->ifc->dev, "%s: status:%d actual:%d\n", __func__,
			urb->status, urb->actual_length);

	/* save error so that subsequent read/write returns ENODEV */
	if (urb->status == -EPROTO)
		dev->err = urb->status;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (urb->status == -EPROTO) {
		dev_err(&dev->udev->dev, "%s: proto error\n", __func__);
		/* save error so that subsequent read/write returns ESHUTDOWN */
		dev->err = urb->status;
		return;
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (cbs && cbs->read_complete_cb)
		cbs->read_complete_cb(cbs->ctxt,
			urb->transfer_buffer,
			urb->transfer_buffer_length,
			urb->status < 0 ? urb->status : urb->actual_length);

	dev->bytes_to_host += urb->actual_length;
	dev->pending_reads--;
<<<<<<< HEAD
<<<<<<< HEAD
	kref_put(&dev->kref, diag_bridge_delete);
}

int diag_bridge_read(int id, char *data, int size)
{
	struct urb		*urb = NULL;
	unsigned int		pipe;
	struct diag_bridge	*dev;
	int			ret;

	if (id < 0 || id >= MAX_DIAG_BRIDGE_DEVS) {
		pr_err("Invalid device ID");
		return -ENODEV;
	}

	pr_debug("reading %d bytes", size);

	dev = __dev[id];
	if (!dev) {
		pr_err("device is disconnected");
		return -ENODEV;
	}

	mutex_lock(&dev->ifc_mutex);
	if (!dev->ifc) {
		ret = -ENODEV;
		goto error;
	}

	if (!dev->ops) {
		pr_err("bridge is not open");
		ret = -ENODEV;
		goto error;
	}

	if (!size) {
		dev_err(&dev->ifc->dev, "invalid size:%d\n", size);
		ret = -EINVAL;
		goto error;
	}

	/* if there was a previous unrecoverable error, just quit */
	if (dev->err) {
		ret = -ENODEV;
		goto error;
	}

	kref_get(&dev->kref);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb) {
		dev_err(&dev->ifc->dev, "unable to allocate urb\n");
		ret = -ENOMEM;
		goto put_error;
	}

	ret = usb_autopm_get_interface(dev->ifc);
	if (ret < 0 && ret != -EAGAIN && ret != -EACCES) {
		pr_err_ratelimited("read: autopm_get failed:%d", ret);
		goto free_error;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

int diag_bridge_read(char *data, int size)
{
	struct urb		*urb = NULL;
	unsigned int		pipe;
	struct diag_bridge	*dev = __dev;
	int			ret;
	int			spin = 50;

	if (!dev || !dev->udev)
		return -ENODEV;

	if (!size) {
		dev_err(&dev->udev->dev, "invalid size:%d\n", size);
		return -EINVAL;
	}

	if (!dev->ifc) {
		dev_err(&dev->udev->dev, "device is disconnected\n");
		return -ENODEV;
	}

	/* if there was a previous unrecoverable error, just quit */
	if (dev->err)
		return -ESHUTDOWN;

	while (check_request_blocked(rmnet_pm_dev) && spin--) {
		pr_debug("%s: wake up wait loop\n", __func__);
		msleep(20);
	}

	if (check_request_blocked(rmnet_pm_dev)) {
		pr_err("%s: in lpa wakeup, return EAGAIN\n", __func__);
		return -EAGAIN;
	}

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb) {
		dev_err(&dev->udev->dev, "unable to allocate urb\n");
		return -ENOMEM;
	}

	ret = usb_autopm_get_interface(dev->ifc);
	if (ret < 0) {
		dev_err(&dev->udev->dev, "autopm_get failed:%d\n", ret);
		usb_free_urb(urb);
		return ret;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	pipe = usb_rcvbulkpipe(dev->udev, dev->in_epAddr);
	usb_fill_bulk_urb(urb, dev->udev, pipe, data, size,
				diag_bridge_read_cb, dev);
	usb_anchor_urb(urb, &dev->submitted);
	dev->pending_reads++;

	ret = usb_submit_urb(urb, GFP_KERNEL);
	if (ret) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err_ratelimited("submitting urb failed err:%d", ret);
		dev->pending_reads--;
		usb_unanchor_urb(urb);
	}
	usb_autopm_put_interface(dev->ifc);

free_error:
	usb_free_urb(urb);
put_error:
	if (ret) /* otherwise this is done in the completion handler */
		kref_put(&dev->kref, diag_bridge_delete);
error:
	mutex_unlock(&dev->ifc_mutex);
	return ret;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		dev_err(&dev->udev->dev, "submitting urb failed err:%d\n", ret);
		dev->pending_reads--;
		usb_unanchor_urb(urb);
		usb_free_urb(urb);
		usb_autopm_put_interface(dev->ifc);
		return ret;
	}

	usb_autopm_put_interface(dev->ifc);
	usb_free_urb(urb);

	return 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
EXPORT_SYMBOL(diag_bridge_read);

static void diag_bridge_write_cb(struct urb *urb)
{
	struct diag_bridge	*dev = urb->context;
	struct diag_bridge_ops	*cbs = dev->ops;

<<<<<<< HEAD
<<<<<<< HEAD
	dev_dbg(&dev->ifc->dev, "%s:\n", __func__);

	usb_autopm_put_interface_async(dev->ifc);

	/* save error so that subsequent read/write returns ENODEV */
	if (urb->status == -EPROTO)
		dev->err = urb->status;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	usb_autopm_put_interface_async(dev->ifc);

	if (urb->status == -EPROTO) {
		dev_err(&dev->udev->dev, "%s: proto error\n", __func__);
		/* save error so that subsequent read/write returns ESHUTDOWN */
		dev->err = urb->status;
		usb_free_urb(urb);
		return;
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (cbs && cbs->write_complete_cb)
		cbs->write_complete_cb(cbs->ctxt,
			urb->transfer_buffer,
			urb->transfer_buffer_length,
			urb->status < 0 ? urb->status : urb->actual_length);

	dev->bytes_to_mdm += urb->actual_length;
	dev->pending_writes--;
<<<<<<< HEAD
<<<<<<< HEAD
	kref_put(&dev->kref, diag_bridge_delete);
}

int diag_bridge_write(int id, char *data, int size)
{
	struct urb		*urb = NULL;
	unsigned int		pipe;
	struct diag_bridge	*dev;
	int			ret;

	if (id < 0 || id >= MAX_DIAG_BRIDGE_DEVS) {
		pr_err("Invalid device ID");
		return -ENODEV;
	}

	pr_debug("writing %d bytes", size);

	dev = __dev[id];
	if (!dev) {
		pr_err("device is disconnected");
		return -ENODEV;
	}

	mutex_lock(&dev->ifc_mutex);
	if (!dev->ifc) {
		ret = -ENODEV;
		goto error;
	}

	if (!dev->ops) {
		pr_err("bridge is not open");
		ret = -ENODEV;
		goto error;
	}

	if (!size) {
		dev_err(&dev->ifc->dev, "invalid size:%d\n", size);
		ret = -EINVAL;
		goto error;
	}

	/* if there was a previous unrecoverable error, just quit */
	if (dev->err) {
		ret = -ENODEV;
		goto error;
	}

	kref_get(&dev->kref);

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb) {
		dev_err(&dev->ifc->dev, "unable to allocate urb\n");
		ret = -ENOMEM;
		goto put_error;
	}

	ret = usb_autopm_get_interface(dev->ifc);
	if (ret < 0 && ret != -EAGAIN && ret != -EACCES) {
		pr_err_ratelimited("write: autopm_get failed:%d", ret);
		goto free_error;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	usb_free_urb(urb);
}

int diag_bridge_write(char *data, int size)
{
	struct urb		*urb = NULL;
	unsigned int		pipe;
	struct diag_bridge	*dev = __dev;
	struct usb_device	*udev;
	int			ret;
	int			spin;


	if (!dev || !dev->udev)
		return -ENODEV;

	if (!size) {
		dev_err(&dev->udev->dev, "invalid size:%d\n", size);
		return -EINVAL;
	}

	if (!dev->ifc) {
		dev_err(&dev->udev->dev, "device is disconnected\n");
		return -ENODEV;
	}

	/* if there was a previous unrecoverable error, just quit */
	if (dev->err)
		return -ESHUTDOWN;

	spin = 50;
	while (check_request_blocked(rmnet_pm_dev) && spin--) {
		pr_info("%s: wake up wait loop\n", __func__);
		msleep(20);
	}

	if (check_request_blocked(rmnet_pm_dev)) {
		pr_err("%s: in lpa wakeup, return EAGAIN\n", __func__);
		return -EAGAIN;
	}

	urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!urb) {
		err("unable to allocate urb");
		return -ENOMEM;
	}

	udev = interface_to_usbdev(dev->ifc);
	/* if dev handling suspend wait for suspended or active*/
	if (pm_dev_runtime_get_enabled(udev) < 0) {
		usb_free_urb(urb);
		return -EAGAIN;
	}

	ret = usb_autopm_get_interface_async(dev->ifc);
	if (ret < 0) {
		dev_err(&dev->udev->dev, "autopm_get failed:%d\n", ret);
		usb_free_urb(urb);
		return ret;
	}

	for (spin = 0; spin < 50; spin++) {
		/* check rpm active */
		if (dev->udev->dev.power.runtime_status == RPM_ACTIVE) {
			ret = 0;
			break;
		} else {
			dev_err(&dev->udev->dev, "waiting rpm active\n");
			ret = -EAGAIN;
		}
		msleep(20);
	}
	if (ret < 0) {
		dev_err(&dev->udev->dev, "rpm active failed:%d\n", ret);
		usb_free_urb(urb);
		usb_autopm_put_interface(dev->ifc);
		return ret;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	pipe = usb_sndbulkpipe(dev->udev, dev->out_epAddr);
	usb_fill_bulk_urb(urb, dev->udev, pipe, data, size,
				diag_bridge_write_cb, dev);
<<<<<<< HEAD
<<<<<<< HEAD
	urb->transfer_flags |= URB_ZERO_PACKET;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	usb_anchor_urb(urb, &dev->submitted);
	dev->pending_writes++;

	ret = usb_submit_urb(urb, GFP_KERNEL);
	if (ret) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err_ratelimited("submitting urb failed err:%d", ret);
		dev->pending_writes--;
		usb_unanchor_urb(urb);
		usb_autopm_put_interface(dev->ifc);
		goto free_error;
	}

free_error:
	usb_free_urb(urb);
put_error:
	if (ret) /* otherwise this is done in the completion handler */
		kref_put(&dev->kref, diag_bridge_delete);
error:
	mutex_unlock(&dev->ifc_mutex);
	return ret;
}
EXPORT_SYMBOL(diag_bridge_write);

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		dev_err(&dev->udev->dev, "submitting urb failed err:%d\n", ret);
		dev->pending_writes--;
		usb_unanchor_urb(urb);
		usb_free_urb(urb);
		usb_autopm_put_interface(dev->ifc);
		return ret;
	}
#if 0
	usb_free_urb(urb);
#endif
	return 0;
}
EXPORT_SYMBOL(diag_bridge_write);

static void diag_bridge_delete(struct kref *kref)
{
	struct diag_bridge *dev =
		container_of(kref, struct diag_bridge, kref);

	usb_put_dev(dev->udev);
	__dev = 0;
	kfree(dev);
}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#if defined(CONFIG_DEBUG_FS)
#define DEBUG_BUF_SIZE	512
static ssize_t diag_read_stats(struct file *file, char __user *ubuf,
				size_t count, loff_t *ppos)
{
<<<<<<< HEAD
<<<<<<< HEAD
	char			*buf;
	int			i, ret = 0;
=======
	struct diag_bridge	*dev = __dev;
	char			*buf;
	int			ret;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct diag_bridge	*dev = __dev;
	char			*buf;
	int			ret;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	buf = kzalloc(sizeof(char) * DEBUG_BUF_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

<<<<<<< HEAD
<<<<<<< HEAD
	for (i = 0; i < MAX_DIAG_BRIDGE_DEVS; i++) {
		struct diag_bridge *dev = __dev[i];
		if (!dev)
			continue;

		ret += scnprintf(buf, DEBUG_BUF_SIZE,
				"epin:%d, epout:%d\n"
				"bytes to host: %lu\n"
				"bytes to mdm: %lu\n"
				"pending reads: %u\n"
				"pending writes: %u\n"
				"last error: %d\n",
				dev->in_epAddr, dev->out_epAddr,
				dev->bytes_to_host, dev->bytes_to_mdm,
				dev->pending_reads, dev->pending_writes,
				dev->err);
	}
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = scnprintf(buf, DEBUG_BUF_SIZE,
			"epin:%d, epout:%d\n"
			"bytes to host: %lu\n"
			"bytes to mdm: %lu\n"
			"pending reads: %u\n"
			"pending writes: %u\n"
			"last error: %d\n",
			dev->in_epAddr, dev->out_epAddr,
			dev->bytes_to_host, dev->bytes_to_mdm,
			dev->pending_reads, dev->pending_writes,
			dev->err);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	ret = simple_read_from_buffer(ubuf, count, ppos, buf, ret);
	kfree(buf);
	return ret;
}

static ssize_t diag_reset_stats(struct file *file, const char __user *buf,
				 size_t count, loff_t *ppos)
{
<<<<<<< HEAD
<<<<<<< HEAD
	int i;

	for (i = 0; i < MAX_DIAG_BRIDGE_DEVS; i++) {
		struct diag_bridge *dev = __dev[i];
		if (dev) {
			dev->bytes_to_host = dev->bytes_to_mdm = 0;
			dev->pending_reads = dev->pending_writes = 0;
		}
	}
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct diag_bridge	*dev = __dev;

	dev->bytes_to_host = dev->bytes_to_mdm = 0;
	dev->pending_reads = dev->pending_writes = 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return count;
}

const struct file_operations diag_stats_ops = {
	.read = diag_read_stats,
	.write = diag_reset_stats,
};

static struct dentry *dent;

static void diag_bridge_debugfs_init(void)
{
	struct dentry *dfile;

	dent = debugfs_create_dir("diag_bridge", 0);
	if (IS_ERR(dent))
		return;

	dfile = debugfs_create_file("status", 0444, dent, 0, &diag_stats_ops);
	if (!dfile || IS_ERR(dfile))
		debugfs_remove(dent);
}

static void diag_bridge_debugfs_cleanup(void)
{
	if (dent) {
		debugfs_remove_recursive(dent);
		dent = NULL;
	}
}
#else
static inline void diag_bridge_debugfs_init(void) { }
static inline void diag_bridge_debugfs_cleanup(void) { }
#endif

static int
diag_bridge_probe(struct usb_interface *ifc, const struct usb_device_id *id)
{
	struct diag_bridge		*dev;
	struct usb_host_interface	*ifc_desc;
	struct usb_endpoint_descriptor	*ep_desc;
<<<<<<< HEAD
<<<<<<< HEAD
	int				i, devid, ret = -ENOMEM;
	__u8				ifc_num;

	pr_debug("id:%lu", id->driver_info);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int				i;
	int				ret = -ENOMEM;
	__u8				ifc_num;

	dbg("%s: id:%lu", __func__, id->driver_info);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	ifc_num = ifc->cur_altsetting->desc.bInterfaceNumber;

	/* is this interface supported ? */
<<<<<<< HEAD
<<<<<<< HEAD
	if (ifc_num != (id->driver_info & 0xFF))
		return -ENODEV;

	devid = (id->driver_info >> 8) & 0xFF;
	if (devid < 0 || devid >= MAX_DIAG_BRIDGE_DEVS)
		return -ENODEV;

	/* already probed? */
	if (__dev[devid]) {
		pr_err("Diag device already probed");
		return -ENODEV;
	}

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		pr_err("unable to allocate dev");
		return -ENOMEM;
	}

	__dev[devid] = dev;
	dev->id = devid;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ifc_num != id->driver_info)
		return -ENODEV;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		pr_err("%s: unable to allocate dev\n", __func__);
		return -ENOMEM;
	}
	dev->pdev = platform_device_alloc("diag_bridge", -1);
	if (!dev->pdev) {
		pr_err("%s: unable to allocate platform device\n", __func__);
		kfree(dev);
		return -ENOMEM;
	}
	/* zero_pky.patch */
	dev->buf_in = kzalloc(IN_BUF_SIZE, GFP_KERNEL);
	if (!dev->buf_in) {
		pr_err("%s: unable to allocate dev->buf_in\n", __func__);
		return -ENOMEM;
	}
	__dev = dev;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	dev->udev = usb_get_dev(interface_to_usbdev(ifc));
	dev->ifc = ifc;
	kref_init(&dev->kref);
<<<<<<< HEAD
<<<<<<< HEAD
	mutex_init(&dev->ifc_mutex);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	init_usb_anchor(&dev->submitted);

	ifc_desc = ifc->cur_altsetting;
	for (i = 0; i < ifc_desc->desc.bNumEndpoints; i++) {
		ep_desc = &ifc_desc->endpoint[i].desc;

		if (!dev->in_epAddr && usb_endpoint_is_bulk_in(ep_desc))
			dev->in_epAddr = ep_desc->bEndpointAddress;

		if (!dev->out_epAddr && usb_endpoint_is_bulk_out(ep_desc))
			dev->out_epAddr = ep_desc->bEndpointAddress;
	}

	if (!(dev->in_epAddr && dev->out_epAddr)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("could not find bulk in and bulk out endpoints");
=======
		err("could not find bulk in and bulk out endpoints");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		err("could not find bulk in and bulk out endpoints");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ret = -ENODEV;
		goto error;
	}

	usb_set_intfdata(ifc, dev);
	diag_bridge_debugfs_init();
<<<<<<< HEAD
<<<<<<< HEAD
	dev->pdev = platform_device_register_simple("diag_bridge", devid,
						    NULL, 0);
	if (IS_ERR(dev->pdev)) {
		pr_err("unable to allocate platform device");
		ret = PTR_ERR(dev->pdev);
		goto error;
	}

	dev_dbg(&dev->ifc->dev, "%s: complete\n", __func__);
=======
	platform_device_add(dev->pdev);

	dev_dbg(&dev->udev->dev, "%s: complete\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	platform_device_add(dev->pdev);

	dev_dbg(&dev->udev->dev, "%s: complete\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;

error:
	if (dev)
		kref_put(&dev->kref, diag_bridge_delete);

	return ret;
}

static void diag_bridge_disconnect(struct usb_interface *ifc)
{
	struct diag_bridge	*dev = usb_get_intfdata(ifc);

<<<<<<< HEAD
<<<<<<< HEAD
	dev_dbg(&dev->ifc->dev, "%s:\n", __func__);

	platform_device_unregister(dev->pdev);
	mutex_lock(&dev->ifc_mutex);
	dev->ifc = NULL;
	mutex_unlock(&dev->ifc_mutex);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev_dbg(&dev->udev->dev, "%s:\n", __func__);

	platform_device_del(dev->pdev);
	/* zero_pky.patch */
	kfree(dev->buf_in);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	diag_bridge_debugfs_cleanup();
	kref_put(&dev->kref, diag_bridge_delete);
	usb_set_intfdata(ifc, NULL);
}

static int diag_bridge_suspend(struct usb_interface *ifc, pm_message_t message)
{
	struct diag_bridge	*dev = usb_get_intfdata(ifc);
	struct diag_bridge_ops	*cbs = dev->ops;
	int ret = 0;

	if (cbs && cbs->suspend) {
		ret = cbs->suspend(cbs->ctxt);
		if (ret) {
<<<<<<< HEAD
<<<<<<< HEAD
			dev_dbg(&dev->ifc->dev,
				"%s: diag veto'd suspend\n", __func__);
			return ret;
		}

		usb_kill_anchored_urbs(&dev->submitted);
	}

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			dev_dbg(&dev->udev->dev,
				"%s: diag veto'd suspend\n", __func__);
			return ret;
		}
	}

	/* zero_pky.patch */
	usb_kill_anchored_urbs(&dev->submitted);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static int diag_bridge_resume(struct usb_interface *ifc)
{
	struct diag_bridge	*dev = usb_get_intfdata(ifc);
	struct diag_bridge_ops	*cbs = dev->ops;


	if (cbs && cbs->resume)
		cbs->resume(cbs->ctxt);
<<<<<<< HEAD
<<<<<<< HEAD
=======
	/* set the default read */ /* zero_pky.patch */
	else
		read_hsic();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* set the default read */ /* zero_pky.patch */
	else
		read_hsic();
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

#define VALID_INTERFACE_NUM	0
<<<<<<< HEAD
<<<<<<< HEAD
#define DEV_ID(n)		((n)<<8)

static const struct usb_device_id diag_bridge_ids[] = {
	{ USB_DEVICE(0x5c6, 0x9001),
	.driver_info = VALID_INTERFACE_NUM | DEV_ID(0), },
	{ USB_DEVICE(0x5c6, 0x9034),
	.driver_info = VALID_INTERFACE_NUM | DEV_ID(0), },
	{ USB_DEVICE(0x5c6, 0x9048),
	.driver_info = VALID_INTERFACE_NUM | DEV_ID(0), },
	{ USB_DEVICE(0x5c6, 0x904C),
	.driver_info = VALID_INTERFACE_NUM | DEV_ID(0), },
	{ USB_DEVICE(0x5c6, 0x9075),
	.driver_info = VALID_INTERFACE_NUM | DEV_ID(0), },
	{ USB_DEVICE(0x5c6, 0x9079),
	.driver_info = VALID_INTERFACE_NUM | DEV_ID(1), },
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static const struct usb_device_id diag_bridge_ids[] = {
	{ USB_DEVICE(0x5c6, 0x9001),
	.driver_info = VALID_INTERFACE_NUM, },
	{ USB_DEVICE(0x5c6, 0x9034),
	.driver_info = VALID_INTERFACE_NUM, },
	{ USB_DEVICE(0x5c6, 0x9048),
	.driver_info = VALID_INTERFACE_NUM, },
	{ USB_DEVICE(0x5c6, 0x904C),
	.driver_info = VALID_INTERFACE_NUM, },
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	{} /* terminating entry */
};
MODULE_DEVICE_TABLE(usb, diag_bridge_ids);

static struct usb_driver diag_bridge_driver = {
	.name =		"diag_bridge",
	.probe =	diag_bridge_probe,
	.disconnect =	diag_bridge_disconnect,
	.suspend =	diag_bridge_suspend,
	.resume =	diag_bridge_resume,
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.reset_resume =	diag_bridge_resume,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.reset_resume =	diag_bridge_resume,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.id_table =	diag_bridge_ids,
	.supports_autosuspend = 1,
};

static int __init diag_bridge_init(void)
{
	int ret;

	ret = usb_register(&diag_bridge_driver);
	if (ret) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("unable to register diag driver");
=======
		err("%s: unable to register diag driver", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		err("%s: unable to register diag driver", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return ret;
	}

	return 0;
}

static void __exit diag_bridge_exit(void)
{
	usb_deregister(&diag_bridge_driver);
}

module_init(diag_bridge_init);
module_exit(diag_bridge_exit);

MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE("GPL v2");
