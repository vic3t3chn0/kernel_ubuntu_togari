<<<<<<< HEAD
<<<<<<< HEAD
/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
=======
/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
/* Copyright (c) 2011-2012, Code Aurora Forum. All rights reserved.
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

#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kref.h>
#include <linux/debugfs.h>
#include <linux/platform_device.h>
#include <linux/uaccess.h>
#include <linux/ratelimit.h>
#include <linux/usb/ch9.h>
#include <linux/usb/cdc.h>
#include <linux/termios.h>
#include <asm/unaligned.h>
#include <mach/usb_bridge.h>
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/mdm_hsic_pm.h>

#ifdef CONFIG_MDM_HSIC_PM
#include <linux/mdm_hsic_pm.h>
static const char rmnet_pm_dev[] = "mdm_hsic_pm0";
#endif

static const char const *ctrl_bridge_names[] = {
	"dun_ctrl_hsic0",
	"rmnet_ctrl_hsic0"
};
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* polling interval for Interrupt ep */
#define HS_INTERVAL		7
#define FS_LS_INTERVAL		3

#define ACM_CTRL_DTR		(1 << 0)
#define DEFAULT_READ_URB_LENGTH	4096

#define SUSPENDED		BIT(0)

<<<<<<< HEAD
<<<<<<< HEAD
enum ctrl_bridge_rx_state {
	RX_IDLE, /* inturb is not queued */
	RX_WAIT, /* inturb is queued and waiting for data */
	RX_BUSY, /* inturb is completed. processing RX */
};

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct ctrl_bridge {
	struct usb_device	*udev;
	struct usb_interface	*intf;

<<<<<<< HEAD
<<<<<<< HEAD
	char			*name;

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned int		int_pipe;
	struct urb		*inturb;
	void			*intbuf;

	struct urb		*readurb;
	void			*readbuf;

	struct usb_anchor	tx_submitted;
	struct usb_anchor	tx_deferred;
	struct usb_ctrlrequest	*in_ctlreq;

	struct bridge		*brdg;
	struct platform_device	*pdev;

	unsigned long		flags;

	/* input control lines (DSR, CTS, CD, RI) */
	unsigned int		cbits_tohost;

	/* output control lines (DTR, RTS) */
	unsigned int		cbits_tomdm;

<<<<<<< HEAD
<<<<<<< HEAD
	spinlock_t lock;
	enum ctrl_bridge_rx_state rx_state;

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* counters */
	unsigned int		snd_encap_cmd;
	unsigned int		get_encap_res;
	unsigned int		resp_avail;
	unsigned int		set_ctrl_line_sts;
	unsigned int		notify_ser_state;
};

static struct ctrl_bridge	*__dev[MAX_BRIDGE_DEVICES];

<<<<<<< HEAD
<<<<<<< HEAD
static int get_ctrl_bridge_chid(char *xport_name)
{
	struct ctrl_bridge	*dev;
	int			i;

	for (i = 0; i < MAX_BRIDGE_DEVICES; i++) {
		dev = __dev[i];
		if (!strncmp(dev->name, xport_name, BRIDGE_NAME_MAX_LEN))
			return i;
	}

	return -ENODEV;
}
=======
/* counter used for indexing ctrl bridge devices */
static int	ch_id;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
/* counter used for indexing ctrl bridge devices */
static int	ch_id;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

unsigned int ctrl_bridge_get_cbits_tohost(unsigned int id)
{
	struct ctrl_bridge	*dev;

	if (id >= MAX_BRIDGE_DEVICES)
		return -EINVAL;

	dev = __dev[id];
	if (!dev)
		return -ENODEV;

	return dev->cbits_tohost;
}
EXPORT_SYMBOL(ctrl_bridge_get_cbits_tohost);

int ctrl_bridge_set_cbits(unsigned int id, unsigned int cbits)
{
	struct ctrl_bridge	*dev;
	struct bridge		*brdg;
	int			retval;

	if (id >= MAX_BRIDGE_DEVICES)
		return -EINVAL;

	dev = __dev[id];
	if (!dev)
		return -ENODEV;

	pr_debug("%s: dev[id] =%u cbits : %u\n", __func__, id, cbits);

	brdg = dev->brdg;
	if (!brdg)
		return -ENODEV;

	dev->cbits_tomdm = cbits;

	retval = ctrl_bridge_write(id, NULL, 0);

	/* if DTR is high, update latest modem info to host */
	if (brdg && (cbits & ACM_CTRL_DTR) && brdg->ops.send_cbits)
		brdg->ops.send_cbits(brdg->ctx, dev->cbits_tohost);

	return retval;
}
EXPORT_SYMBOL(ctrl_bridge_set_cbits);

<<<<<<< HEAD
<<<<<<< HEAD
static int ctrl_bridge_start_read(struct ctrl_bridge *dev, gfp_t gfp_flags)
{
	int	retval = 0;
	unsigned long flags;

	if (!dev->inturb) {
		dev_err(&dev->intf->dev, "%s: inturb is NULL\n", __func__);
		return -ENODEV;
	}

	retval = usb_submit_urb(dev->inturb, gfp_flags);
	if (retval < 0 && retval != -EPERM) {
		dev_err(&dev->intf->dev,
			"%s error submitting int urb %d\n",
			__func__, retval);
	}

	spin_lock_irqsave(&dev->lock, flags);
	if (retval)
		dev->rx_state = RX_IDLE;
	else
		dev->rx_state = RX_WAIT;
	spin_unlock_irqrestore(&dev->lock, flags);

	return retval;
}

static void resp_avail_cb(struct urb *urb)
{
	struct ctrl_bridge	*dev = urb->context;
	int			resubmit_urb = 1;
	struct bridge		*brdg = dev->brdg;
	unsigned long		flags;

	/*usb device disconnect*/
	if (urb->dev->state == USB_STATE_NOTATTACHED)
		return;

	switch (urb->status) {
	case 0:
		/*success*/
		dev->get_encap_res++;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void resp_avail_cb(struct urb *urb)
{
	struct ctrl_bridge	*dev = urb->context;
	struct usb_device	*udev;
	int			status = 0;
	int			resubmit_urb = 1;
	struct bridge		*brdg = dev->brdg;
	unsigned int		iface_num;

	udev = interface_to_usbdev(dev->intf);
	iface_num = dev->intf->cur_altsetting->desc.bInterfaceNumber;

	switch (urb->status) {
	case -ENOENT:
	case 0:
		/*success*/
		dev->get_encap_res++;
		pr_info("[RACB:%d]<\n", iface_num);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (brdg && brdg->ops.send_pkt)
			brdg->ops.send_pkt(brdg->ctx, urb->transfer_buffer,
				urb->actual_length);
		break;

	/*do not resubmit*/
	case -ESHUTDOWN:
<<<<<<< HEAD
<<<<<<< HEAD
	case -ENOENT:
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case -ECONNRESET:
		/* unplug */
	case -EPROTO:
		/*babble error*/
		resubmit_urb = 0;
	/*resubmit*/
	case -EOVERFLOW:
	default:
<<<<<<< HEAD
<<<<<<< HEAD
		dev_dbg(&dev->intf->dev, "%s: non zero urb status = %d\n",
			__func__, urb->status);
	}

	if (resubmit_urb) {
		/*re- submit int urb to check response available*/
		ctrl_bridge_start_read(dev, GFP_ATOMIC);
	} else {
		spin_lock_irqsave(&dev->lock, flags);
		dev->rx_state = RX_IDLE;
		spin_unlock_irqrestore(&dev->lock, flags);
	}

	usb_autopm_put_interface_async(dev->intf);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		dev_dbg(&udev->dev, "%s: non zero urb status = %d\n",
			__func__, urb->status);
	}

	if (urb->status != -ENOENT && resubmit_urb) {
		/*re- submit int urb to check response available*/
		status = usb_submit_urb(dev->inturb, GFP_ATOMIC);
		if (status) {
			dev_err(&udev->dev,
				"%s: Error re-submitting Int URB %d\n",
				__func__, status);
		}
		pr_info("[CHKRA:%d]>\n", iface_num);
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void notification_available_cb(struct urb *urb)
{
	int				status;
	struct usb_cdc_notification	*ctrl;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	struct usb_device		*udev;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct usb_device		*udev;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct ctrl_bridge		*dev = urb->context;
	struct bridge			*brdg = dev->brdg;
	unsigned int			ctrl_bits;
	unsigned char			*data;
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned long			flags;

	/*usb device disconnect*/
	if (urb->dev->state == USB_STATE_NOTATTACHED)
		return;

	spin_lock_irqsave(&dev->lock, flags);
	dev->rx_state = RX_IDLE;
	spin_unlock_irqrestore(&dev->lock, flags);

	switch (urb->status) {
	case 0:
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned int		iface_num;

	/* if this intf is already disconnected, this urb free-ed before
	 * calling from qh_completions. just return and do nothing */
	if (!dev->intf)
		return;

	udev = interface_to_usbdev(dev->intf);
	iface_num = dev->intf->cur_altsetting->desc.bInterfaceNumber;

	switch (urb->status) {
	case 0:
		pr_info("[NACB:%d]<\n", iface_num);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		/*success*/
		break;
	case -ESHUTDOWN:
	case -ENOENT:
	case -ECONNRESET:
	case -EPROTO:
		 /* unplug */
		 return;
	case -EPIPE:
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(&dev->intf->dev,
			"%s: stall on int endpoint\n", __func__);
=======
		dev_err(&udev->dev, "%s: stall on int endpoint\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_err(&udev->dev, "%s: stall on int endpoint\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		/* TBD : halt to be cleared in work */
	case -EOVERFLOW:
	default:
		pr_debug_ratelimited("%s: non zero urb status = %d\n",
					__func__, urb->status);
		goto resubmit_int_urb;
	}

	ctrl = (struct usb_cdc_notification *)urb->transfer_buffer;
	data = (unsigned char *)(ctrl + 1);

	switch (ctrl->bNotificationType) {
	case USB_CDC_NOTIFY_RESPONSE_AVAILABLE:
<<<<<<< HEAD
<<<<<<< HEAD
		spin_lock_irqsave(&dev->lock, flags);
		dev->rx_state = RX_BUSY;
		spin_unlock_irqrestore(&dev->lock, flags);
		dev->resp_avail++;
		usb_autopm_get_interface_no_resume(dev->intf);
		usb_fill_control_urb(dev->readurb, dev->udev,
					usb_rcvctrlpipe(dev->udev, 0),
=======
		dev->resp_avail++;
		usb_fill_control_urb(dev->readurb, udev,
					usb_rcvctrlpipe(udev, 0),
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev->resp_avail++;
		usb_fill_control_urb(dev->readurb, udev,
					usb_rcvctrlpipe(udev, 0),
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					(unsigned char *)dev->in_ctlreq,
					dev->readbuf,
					DEFAULT_READ_URB_LENGTH,
					resp_avail_cb, dev);

		status = usb_submit_urb(dev->readurb, GFP_ATOMIC);
		if (status) {
<<<<<<< HEAD
<<<<<<< HEAD
			dev_err(&dev->intf->dev,
				"%s: Error submitting Read URB %d\n",
				__func__, status);
			usb_autopm_put_interface_async(dev->intf);
			goto resubmit_int_urb;
		}
		return;
	case USB_CDC_NOTIFY_NETWORK_CONNECTION:
		dev_dbg(&dev->intf->dev, "%s network\n", ctrl->wValue ?
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			dev_err(&udev->dev,
				"%s: Error submitting Read URB %d\n",
				__func__, status);
			goto resubmit_int_urb;
		} else
			pr_info("[NRA:%d]>\n", iface_num);
		return;
	case USB_CDC_NOTIFY_NETWORK_CONNECTION:
		dev_dbg(&udev->dev, "%s network\n", ctrl->wValue ?
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					"connected to" : "disconnected from");
		break;
	case USB_CDC_NOTIFY_SERIAL_STATE:
		dev->notify_ser_state++;
		ctrl_bits = get_unaligned_le16(data);
<<<<<<< HEAD
<<<<<<< HEAD
		dev_dbg(&dev->intf->dev, "serial state: %d\n", ctrl_bits);
		dev->cbits_tohost = ctrl_bits;
		if (brdg && brdg->ops.send_cbits)
			brdg->ops.send_cbits(brdg->ctx, ctrl_bits);
		break;
	default:
		dev_err(&dev->intf->dev, "%s: unknown notification %d received:"
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		dev_dbg(&udev->dev, "serial state: %d\n", ctrl_bits);
		dev->cbits_tohost = ctrl_bits;
		if (brdg && brdg->ops.send_cbits)
			brdg->ops.send_cbits(brdg->ctx, ctrl_bits);
#ifdef CONFIG_MDM_HSIC_PM
		pr_info("%s: set lpa handling to false\n", __func__);
		lpa_handling = false;
#endif
		break;
	default:
		dev_err(&udev->dev, "%s: unknown notification %d received:"
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			"index %d len %d data0 %d data1 %d",
			__func__, ctrl->bNotificationType, ctrl->wIndex,
			ctrl->wLength, data[0], data[1]);
	}

resubmit_int_urb:
<<<<<<< HEAD
<<<<<<< HEAD
	ctrl_bridge_start_read(dev, GFP_ATOMIC);
}

int ctrl_bridge_open(struct bridge *brdg)
{
	struct ctrl_bridge	*dev;
	int			ch_id;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	status = usb_submit_urb(urb, GFP_ATOMIC);
	if (status) {
		dev_err(&udev->dev, "%s: Error re-submitting Int URB %d\n",
		__func__, status);
	} else
		pr_info("[CHKRA:%d]>\n", iface_num);
}

int ctrl_bridge_start_read(struct ctrl_bridge *dev)
{
	int			retval = 0;
	struct usb_device	*udev;
	unsigned int		iface_num;

	udev = interface_to_usbdev(dev->intf);
	iface_num = dev->intf->cur_altsetting->desc.bInterfaceNumber;

	if (!dev->inturb) {
		dev_err(&dev->udev->dev, "%s: inturb is NULL\n", __func__);
		return -ENODEV;
	}

	retval = usb_submit_urb(dev->inturb, GFP_KERNEL);
	if (retval < 0) {
		dev_err(&dev->udev->dev,
			"%s error submitting int urb %d\n",
			__func__, retval);

	} else
		pr_info("[CHKRA:%d]>\n", iface_num);

	return retval;
}

void ctrl_bridge_stop_read(struct ctrl_bridge *dev)
{
	usb_kill_urb(dev->readurb);
	usb_kill_urb(dev->inturb);
}

void ctrl_bridge_stop_all(void)
{
	int id;

	for (id = 0; id < MAX_BRIDGE_DEVICES; id++) {
		if (__dev[id])
			ctrl_bridge_stop_read(__dev[id]);
	}
}
EXPORT_SYMBOL(ctrl_bridge_stop_all);

int ctrl_bridge_open(struct bridge *brdg)
{
	struct ctrl_bridge	*dev;
	int			ret;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!brdg) {
		err("bridge is null\n");
		return -EINVAL;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	ch_id = get_ctrl_bridge_chid(brdg->name);
	if (ch_id < 0 || ch_id >= MAX_BRIDGE_DEVICES) {
		err("%s: %s dev not found\n", __func__, brdg->name);
		return ch_id;
	}

	brdg->ch_id = ch_id;

	dev = __dev[ch_id];
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (brdg->ch_id >= MAX_BRIDGE_DEVICES)
		return -EINVAL;

	dev = __dev[brdg->ch_id];
	if (!dev) {
		err("dev is null\n");
		return -ENODEV;
	}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev->brdg = brdg;
	dev->snd_encap_cmd = 0;
	dev->get_encap_res = 0;
	dev->resp_avail = 0;
	dev->set_ctrl_line_sts = 0;
	dev->notify_ser_state = 0;

<<<<<<< HEAD
<<<<<<< HEAD
	if (brdg->ops.send_cbits)
		brdg->ops.send_cbits(brdg->ctx, dev->cbits_tohost);

	return 0;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = usb_autopm_get_interface(dev->intf);
	if (ret < 0) {
		dev_err(&dev->udev->dev, "%s autopm_get fail: %d\n",
			__func__, ret);
		return ret;
	}

	ret = ctrl_bridge_start_read(dev);
	usb_autopm_put_interface(dev->intf);
	return ret;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
EXPORT_SYMBOL(ctrl_bridge_open);

void ctrl_bridge_close(unsigned int id)
{
	struct ctrl_bridge	*dev;

	if (id >= MAX_BRIDGE_DEVICES)
		return;

	dev  = __dev[id];
	if (!dev || !dev->brdg)
		return;

<<<<<<< HEAD
<<<<<<< HEAD
	dev_dbg(&dev->intf->dev, "%s:\n", __func__);

	ctrl_bridge_set_cbits(dev->brdg->ch_id, 0);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev_dbg(&dev->udev->dev, "%s:\n", __func__);

	ctrl_bridge_set_cbits(dev->brdg->ch_id, 0);
	usb_unlink_anchored_urbs(&dev->tx_submitted);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	dev->brdg = NULL;
}
EXPORT_SYMBOL(ctrl_bridge_close);

static void ctrl_write_callback(struct urb *urb)
{
	struct ctrl_bridge	*dev = urb->context;

	if (urb->status) {
		pr_debug("Write status/size %d/%d\n",
			urb->status, urb->actual_length);
	}

	kfree(urb->transfer_buffer);
	kfree(urb->setup_packet);
	usb_free_urb(urb);
<<<<<<< HEAD
<<<<<<< HEAD

	/* if we are here after device disconnect
	 * usb_unbind_interface() takes care of
	 * residual pm_autopm_get_interface_* calls
	 */
	if (urb->dev->state != USB_STATE_NOTATTACHED)
=======
	if (dev->intf)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (dev->intf)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		usb_autopm_put_interface_async(dev->intf);
}

int ctrl_bridge_write(unsigned int id, char *data, size_t size)
{
	int			result;
	struct urb		*writeurb;
	struct usb_ctrlrequest	*out_ctlreq;
<<<<<<< HEAD
<<<<<<< HEAD
	struct ctrl_bridge	*dev;
	unsigned long		flags;
=======
	struct usb_device	*udev;
	struct ctrl_bridge	*dev;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct usb_device	*udev;
	struct ctrl_bridge	*dev;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (id >= MAX_BRIDGE_DEVICES) {
		result = -EINVAL;
		goto free_data;
	}

	dev = __dev[id];

	if (!dev) {
		result = -ENODEV;
		goto free_data;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	dev_dbg(&dev->intf->dev, "%s:[id]:%u: write (%d bytes)\n",
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* wait till, LPA wake complete */
	if (pm_dev_wait_lpa_wake() < 0)
		return -EAGAIN;

	udev = interface_to_usbdev(dev->intf);

	dev_dbg(&udev->dev, "%s:[id]:%u: write (%d bytes)\n",
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		__func__, id, size);

	writeurb = usb_alloc_urb(0, GFP_ATOMIC);
	if (!writeurb) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(&dev->intf->dev, "%s: error allocating read urb\n",
=======
		dev_err(&udev->dev, "%s: error allocating read urb\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_err(&udev->dev, "%s: error allocating read urb\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			__func__);
		result = -ENOMEM;
		goto free_data;
	}

	out_ctlreq = kmalloc(sizeof(*out_ctlreq), GFP_ATOMIC);
	if (!out_ctlreq) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(&dev->intf->dev,
=======
		dev_err(&udev->dev,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_err(&udev->dev,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			"%s: error allocating setup packet buffer\n",
			__func__);
		result = -ENOMEM;
		goto free_urb;
	}

	/* CDC Send Encapsulated Request packet */
	out_ctlreq->bRequestType = (USB_DIR_OUT | USB_TYPE_CLASS |
				 USB_RECIP_INTERFACE);
	if (!data && !size) {
		out_ctlreq->bRequest = USB_CDC_REQ_SET_CONTROL_LINE_STATE;
		out_ctlreq->wValue = dev->cbits_tomdm;
		dev->set_ctrl_line_sts++;
	} else {
		out_ctlreq->bRequest = USB_CDC_SEND_ENCAPSULATED_COMMAND;
		out_ctlreq->wValue = 0;
		dev->snd_encap_cmd++;
	}
	out_ctlreq->wIndex =
		dev->intf->cur_altsetting->desc.bInterfaceNumber;
	out_ctlreq->wLength = cpu_to_le16(size);

<<<<<<< HEAD
<<<<<<< HEAD
	usb_fill_control_urb(writeurb, dev->udev,
				 usb_sndctrlpipe(dev->udev, 0),
=======
	usb_fill_control_urb(writeurb, udev,
				 usb_sndctrlpipe(udev, 0),
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	usb_fill_control_urb(writeurb, udev,
				 usb_sndctrlpipe(udev, 0),
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				 (unsigned char *)out_ctlreq,
				 (void *)data, size,
				 ctrl_write_callback, dev);

	result = usb_autopm_get_interface_async(dev->intf);
	if (result < 0) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_dbg(&dev->intf->dev, "%s: unable to resume interface: %d\n",
=======
		dev_err(&udev->dev, "%s: unable to resume interface: %d\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_err(&udev->dev, "%s: unable to resume interface: %d\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			__func__, result);

		/*
		  * Revisit: if (result == -EPERM)
		  * bridge_suspend(dev->intf, PMSG_SUSPEND);
		  */

		goto free_ctrlreq;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	spin_lock_irqsave(&dev->lock, flags);
	if (test_bit(SUSPENDED, &dev->flags)) {
		usb_anchor_urb(writeurb, &dev->tx_deferred);
		spin_unlock_irqrestore(&dev->lock, flags);
=======
	if (test_bit(SUSPENDED, &dev->flags)) {
		usb_anchor_urb(writeurb, &dev->tx_deferred);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (test_bit(SUSPENDED, &dev->flags)) {
		usb_anchor_urb(writeurb, &dev->tx_deferred);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto deferred;
	}

	usb_anchor_urb(writeurb, &dev->tx_submitted);
<<<<<<< HEAD
<<<<<<< HEAD
	spin_unlock_irqrestore(&dev->lock, flags);
	result = usb_submit_urb(writeurb, GFP_ATOMIC);
	if (result < 0) {
		dev_err(&dev->intf->dev, "%s: submit URB error %d\n",
=======
	result = usb_submit_urb(writeurb, GFP_ATOMIC);
	if (result < 0) {
		dev_err(&udev->dev, "%s: submit URB error %d\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	result = usb_submit_urb(writeurb, GFP_ATOMIC);
	if (result < 0) {
		dev_err(&udev->dev, "%s: submit URB error %d\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			__func__, result);
		usb_autopm_put_interface_async(dev->intf);
		goto unanchor_urb;
	}
deferred:
	return size;

unanchor_urb:
	usb_unanchor_urb(writeurb);
free_ctrlreq:
	kfree(out_ctlreq);
free_urb:
	usb_free_urb(writeurb);
free_data:
	kfree(data);

	return result;
}
EXPORT_SYMBOL(ctrl_bridge_write);

int ctrl_bridge_suspend(unsigned int id)
{
	struct ctrl_bridge	*dev;
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned long		flags;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (id >= MAX_BRIDGE_DEVICES)
		return -EINVAL;

	dev = __dev[id];
	if (!dev)
		return -ENODEV;

<<<<<<< HEAD
<<<<<<< HEAD
	spin_lock_irqsave(&dev->lock, flags);
	if (!usb_anchor_empty(&dev->tx_submitted) || dev->rx_state == RX_BUSY) {
		spin_unlock_irqrestore(&dev->lock, flags);
		return -EBUSY;
	}
	spin_unlock_irqrestore(&dev->lock, flags);

	usb_kill_urb(dev->inturb);

	spin_lock_irqsave(&dev->lock, flags);
	if (dev->rx_state != RX_IDLE) {
		spin_unlock_irqrestore(&dev->lock, flags);
		return -EBUSY;
	}
	if (!usb_anchor_empty(&dev->tx_submitted)) {
		spin_unlock_irqrestore(&dev->lock, flags);
		ctrl_bridge_start_read(dev, GFP_KERNEL);
		return -EBUSY;
	}
	set_bit(SUSPENDED, &dev->flags);
	spin_unlock_irqrestore(&dev->lock, flags);
=======
	set_bit(SUSPENDED, &dev->flags);
	usb_kill_anchored_urbs(&dev->tx_submitted);
	ctrl_bridge_stop_read(dev);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	set_bit(SUSPENDED, &dev->flags);
	usb_kill_anchored_urbs(&dev->tx_submitted);
	ctrl_bridge_stop_read(dev);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

int ctrl_bridge_resume(unsigned int id)
{
	struct ctrl_bridge	*dev;
	struct urb		*urb;
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned long		flags;
	int			ret;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (id >= MAX_BRIDGE_DEVICES)
		return -EINVAL;

	dev = __dev[id];
	if (!dev)
		return -ENODEV;

<<<<<<< HEAD
<<<<<<< HEAD
	if (!test_bit(SUSPENDED, &dev->flags))
		return 0;

	spin_lock_irqsave(&dev->lock, flags);
	/* submit pending write requests */
	while ((urb = usb_get_from_anchor(&dev->tx_deferred))) {
		spin_unlock_irqrestore(&dev->lock, flags);
		/*
		 * usb_get_from_anchor() does not drop the
		 * ref count incremented by the usb_anchro_urb()
		 * called in Tx submission path. Let us do it.
		 */
		usb_put_urb(urb);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!test_and_clear_bit(SUSPENDED, &dev->flags))
		return 0;

	/* submit pending write requests */
	while ((urb = usb_get_from_anchor(&dev->tx_deferred))) {
		int ret;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		usb_anchor_urb(urb, &dev->tx_submitted);
		ret = usb_submit_urb(urb, GFP_ATOMIC);
		if (ret < 0) {
			usb_unanchor_urb(urb);
			kfree(urb->setup_packet);
			kfree(urb->transfer_buffer);
			usb_free_urb(urb);
			usb_autopm_put_interface_async(dev->intf);
		}
<<<<<<< HEAD
<<<<<<< HEAD
		spin_lock_irqsave(&dev->lock, flags);
	}
	clear_bit(SUSPENDED, &dev->flags);
	spin_unlock_irqrestore(&dev->lock, flags);

	return ctrl_bridge_start_read(dev, GFP_KERNEL);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	/* if the bridge is open, resume reading */
#ifndef CONFIG_MDM_HSIC_PM
	if (dev->brdg)
		return ctrl_bridge_start_read(dev);
#else
	/* if the bridge is open or not, resume to consume mdm request
	 * because this link is not dead, it's alive
	 */
	return ctrl_bridge_start_read(dev);
#endif
	return 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

#if defined(CONFIG_DEBUG_FS)
#define DEBUG_BUF_SIZE	1024
static ssize_t ctrl_bridge_read_stats(struct file *file, char __user *ubuf,
		size_t count, loff_t *ppos)
{
	struct ctrl_bridge	*dev;
	char			*buf;
	int			ret;
	int			i;
	int			temp = 0;

	buf = kzalloc(sizeof(char) * DEBUG_BUF_SIZE, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

<<<<<<< HEAD
<<<<<<< HEAD
	for (i = 0; i < MAX_BRIDGE_DEVICES; i++) {
=======
	for (i = 0; i < ch_id; i++) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	for (i = 0; i < ch_id; i++) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		dev = __dev[i];
		if (!dev)
			continue;

		temp += scnprintf(buf + temp, DEBUG_BUF_SIZE - temp,
				"\nName#%s dev %p\n"
				"snd encap cmd cnt: %u\n"
				"get encap res cnt: %u\n"
				"res available cnt: %u\n"
				"set ctrlline sts cnt: %u\n"
				"notify ser state cnt: %u\n"
				"cbits_tomdm: %d\n"
				"cbits_tohost: %d\n"
				"suspended: %d\n",
<<<<<<< HEAD
<<<<<<< HEAD
				dev->name, dev,
=======
				dev->pdev->name, dev,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				dev->pdev->name, dev,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				dev->snd_encap_cmd,
				dev->get_encap_res,
				dev->resp_avail,
				dev->set_ctrl_line_sts,
				dev->notify_ser_state,
				dev->cbits_tomdm,
				dev->cbits_tohost,
				test_bit(SUSPENDED, &dev->flags));
	}

	ret = simple_read_from_buffer(ubuf, count, ppos, buf, temp);

	kfree(buf);

	return ret;
}

static ssize_t ctrl_bridge_reset_stats(struct file *file,
	const char __user *buf, size_t count, loff_t *ppos)
{
	struct ctrl_bridge	*dev;
	int			i;

<<<<<<< HEAD
<<<<<<< HEAD
	for (i = 0; i < MAX_BRIDGE_DEVICES; i++) {
=======
	for (i = 0; i < ch_id; i++) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	for (i = 0; i < ch_id; i++) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		dev = __dev[i];
		if (!dev)
			continue;

		dev->snd_encap_cmd = 0;
		dev->get_encap_res = 0;
		dev->resp_avail = 0;
		dev->set_ctrl_line_sts = 0;
		dev->notify_ser_state = 0;
	}
	return count;
}

const struct file_operations ctrl_stats_ops = {
	.read = ctrl_bridge_read_stats,
	.write = ctrl_bridge_reset_stats,
};

struct dentry	*ctrl_dent;
struct dentry	*ctrl_dfile;
static void ctrl_bridge_debugfs_init(void)
{
	ctrl_dent = debugfs_create_dir("ctrl_hsic_bridge", 0);
	if (IS_ERR(ctrl_dent))
		return;

	ctrl_dfile =
		debugfs_create_file("status", 0644, ctrl_dent, 0,
			&ctrl_stats_ops);
	if (!ctrl_dfile || IS_ERR(ctrl_dfile))
		debugfs_remove(ctrl_dent);
}

static void ctrl_bridge_debugfs_exit(void)
{
	debugfs_remove(ctrl_dfile);
	debugfs_remove(ctrl_dent);
}

#else
static void ctrl_bridge_debugfs_init(void) { }
static void ctrl_bridge_debugfs_exit(void) { }
#endif

int
ctrl_bridge_probe(struct usb_interface *ifc, struct usb_host_endpoint *int_in,
<<<<<<< HEAD
<<<<<<< HEAD
		char *name, int id)
=======
		int id)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		int id)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct ctrl_bridge		*dev;
	struct usb_device		*udev;
	struct usb_endpoint_descriptor	*ep;
	u16				wMaxPacketSize;
	int				retval = 0;
	int				interval;

	udev = interface_to_usbdev(ifc);

<<<<<<< HEAD
<<<<<<< HEAD
	dev = __dev[id];
	if (!dev) {
		pr_err("%s:device not found\n", __func__);
		return -ENODEV;
	}

	dev->name = name;

	dev->pdev = platform_device_alloc(name, -1);
	if (!dev->pdev) {
		retval = -ENOMEM;
		dev_err(&ifc->dev, "%s: unable to allocate platform device\n",
			__func__);
		goto free_name;
	}

	dev->flags = 0;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		dev_err(&udev->dev, "%s: unable to allocate dev\n",
			__func__);
		return -ENOMEM;
	}
	dev->pdev = platform_device_alloc(ctrl_bridge_names[id], id);
	if (!dev->pdev) {
		dev_err(&dev->udev->dev,
			"%s: unable to allocate platform device\n", __func__);
		retval = -ENOMEM;
		goto nomem;
	}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev->udev = udev;
	dev->int_pipe = usb_rcvintpipe(udev,
		int_in->desc.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK);
	dev->intf = ifc;

<<<<<<< HEAD
<<<<<<< HEAD
=======
	init_usb_anchor(&dev->tx_submitted);
	init_usb_anchor(&dev->tx_deferred);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	init_usb_anchor(&dev->tx_submitted);
	init_usb_anchor(&dev->tx_deferred);

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*use max pkt size from ep desc*/
	ep = &dev->intf->cur_altsetting->endpoint[0].desc;

	dev->inturb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->inturb) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(&ifc->dev, "%s: error allocating int urb\n", __func__);
		retval = -ENOMEM;
		goto pdev_put;
=======
		dev_err(&udev->dev, "%s: error allocating int urb\n", __func__);
		retval = -ENOMEM;
		goto pdev_del;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_err(&udev->dev, "%s: error allocating int urb\n", __func__);
		retval = -ENOMEM;
		goto pdev_del;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	wMaxPacketSize = le16_to_cpu(ep->wMaxPacketSize);

	dev->intbuf = kmalloc(wMaxPacketSize, GFP_KERNEL);
	if (!dev->intbuf) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(&ifc->dev, "%s: error allocating int buffer\n",
=======
		dev_err(&udev->dev, "%s: error allocating int buffer\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_err(&udev->dev, "%s: error allocating int buffer\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			__func__);
		retval = -ENOMEM;
		goto free_inturb;
	}

	interval =
		(udev->speed == USB_SPEED_HIGH) ? HS_INTERVAL : FS_LS_INTERVAL;

	usb_fill_int_urb(dev->inturb, udev, dev->int_pipe,
				dev->intbuf, wMaxPacketSize,
				notification_available_cb, dev, interval);

	dev->readurb = usb_alloc_urb(0, GFP_KERNEL);
	if (!dev->readurb) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(&ifc->dev, "%s: error allocating read urb\n",
=======
		dev_err(&udev->dev, "%s: error allocating read urb\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_err(&udev->dev, "%s: error allocating read urb\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			__func__);
		retval = -ENOMEM;
		goto free_intbuf;
	}

	dev->readbuf = kmalloc(DEFAULT_READ_URB_LENGTH, GFP_KERNEL);
	if (!dev->readbuf) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(&ifc->dev, "%s: error allocating read buffer\n",
=======
		dev_err(&udev->dev, "%s: error allocating read buffer\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_err(&udev->dev, "%s: error allocating read buffer\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			__func__);
		retval = -ENOMEM;
		goto free_rurb;
	}

	dev->in_ctlreq = kmalloc(sizeof(*dev->in_ctlreq), GFP_KERNEL);
	if (!dev->in_ctlreq) {
<<<<<<< HEAD
<<<<<<< HEAD
		dev_err(&ifc->dev, "%s:error allocating setup packet buffer\n",
=======
		dev_err(&udev->dev,
			"%s:error allocating setup packet buffer\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		dev_err(&udev->dev,
			"%s:error allocating setup packet buffer\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			__func__);
		retval = -ENOMEM;
		goto free_rbuf;
	}

	dev->in_ctlreq->bRequestType =
			(USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE);
	dev->in_ctlreq->bRequest  = USB_CDC_GET_ENCAPSULATED_RESPONSE;
	dev->in_ctlreq->wValue = 0;
	dev->in_ctlreq->wIndex =
		dev->intf->cur_altsetting->desc.bInterfaceNumber;
	dev->in_ctlreq->wLength = cpu_to_le16(DEFAULT_READ_URB_LENGTH);

<<<<<<< HEAD
<<<<<<< HEAD
	retval = platform_device_add(dev->pdev);
	if (retval) {
		dev_err(&ifc->dev, "%s:fail to add pdev\n", __func__);
		goto free_ctrlreq;
	}

	retval = ctrl_bridge_start_read(dev, GFP_KERNEL);
	if (retval) {
		dev_err(&ifc->dev, "%s:fail to start reading\n", __func__);
		goto pdev_del;
	}

	return 0;

pdev_del:
	platform_device_del(dev->pdev);
free_ctrlreq:
	kfree(dev->in_ctlreq);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	__dev[id] = dev;

	platform_device_add(dev->pdev);

	ch_id++;

#ifdef CONFIG_MDM_HSIC_PM
	/* if the bridge is open or not, resume to consume mdm request
	 * because this link is not dead, it's alive
	 */
	ctrl_bridge_start_read(dev);
#endif
	return retval;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
free_rbuf:
	kfree(dev->readbuf);
free_rurb:
	usb_free_urb(dev->readurb);
free_intbuf:
	kfree(dev->intbuf);
free_inturb:
	usb_free_urb(dev->inturb);
<<<<<<< HEAD
<<<<<<< HEAD
pdev_put:
	platform_device_put(dev->pdev);
free_name:
	dev->name = "none";
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
pdev_del:
	platform_device_del(dev->pdev);
nomem:
	kfree(dev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return retval;
}

void ctrl_bridge_disconnect(unsigned int id)
{
	struct ctrl_bridge	*dev = __dev[id];

<<<<<<< HEAD
<<<<<<< HEAD
	dev_dbg(&dev->intf->dev, "%s:\n", __func__);

	/*set device name to none to get correct channel id
	 * at the time of bridge open
	 */
	dev->name = "none";

	platform_device_unregister(dev->pdev);

	usb_scuttle_anchored_urbs(&dev->tx_deferred);
	usb_kill_anchored_urbs(&dev->tx_submitted);

	usb_kill_urb(dev->inturb);
	usb_kill_urb(dev->readurb);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev_dbg(&dev->udev->dev, "%s:\n", __func__);

	platform_device_del(dev->pdev);

	dev->intf = NULL;
	usb_kill_urb(dev->readurb);
	usb_kill_urb(dev->inturb);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	kfree(dev->in_ctlreq);
	kfree(dev->readbuf);
	kfree(dev->intbuf);

	usb_free_urb(dev->readurb);
	usb_free_urb(dev->inturb);
<<<<<<< HEAD
<<<<<<< HEAD
}

int ctrl_bridge_init(void)
{
	struct ctrl_bridge	*dev;
	int			i;
	int			retval = 0;

	for (i = 0; i < MAX_BRIDGE_DEVICES; i++) {

		dev = kzalloc(sizeof(*dev), GFP_KERNEL);
		if (!dev) {
			pr_err("%s: unable to allocate dev\n", __func__);
			retval = -ENOMEM;
			goto error;
		}

		/*transport name will be set during probe*/
		dev->name = "none";

		spin_lock_init(&dev->lock);
		init_usb_anchor(&dev->tx_submitted);
		init_usb_anchor(&dev->tx_deferred);

		__dev[i] = dev;
	}

	ctrl_bridge_debugfs_init();

	return 0;

error:
	while (--i >= 0) {
		kfree(__dev[i]);
		__dev[i] = NULL;
	}

	return retval;
}

void ctrl_bridge_exit(void)
{
	int	i;

	ctrl_bridge_debugfs_exit();

	for (i = 0; i < MAX_BRIDGE_DEVICES; i++) {
		kfree(__dev[i]);
		__dev[i] = NULL;
	}
}
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	__dev[id] = NULL;
	ch_id--;

	kfree(dev);
}

static int __init ctrl_bridge_init(void)
{
	ctrl_bridge_debugfs_init();

	return 0;
}
module_init(ctrl_bridge_init);

static void __exit ctrl_bridge_exit(void)
{
	ctrl_bridge_debugfs_exit();
}
module_exit(ctrl_bridge_exit);

MODULE_DESCRIPTION("Qualcomm modem control bridge driver");
MODULE_LICENSE("GPL v2");
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
