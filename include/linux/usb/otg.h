/* USB OTG (On The Go) defines */
/*
 *
 * These APIs may be used between USB controllers.  USB device drivers
 * (for either host or peripheral roles) don't use these calls; they
 * continue to use just usb_device and usb_gadget.
 */

#ifndef __LINUX_USB_OTG_H
#define __LINUX_USB_OTG_H

#include <linux/notifier.h>

/* OTG defines lots of enumeration states before device reset */
enum usb_otg_state {
	OTG_STATE_UNDEFINED = 0,

	/* single-role peripheral, and dual-role default-b */
	OTG_STATE_B_IDLE,
	OTG_STATE_B_SRP_INIT,
	OTG_STATE_B_PERIPHERAL,

	/* extra dual-role default-b states */
	OTG_STATE_B_WAIT_ACON,
	OTG_STATE_B_HOST,

	/* dual-role default-a */
	OTG_STATE_A_IDLE,
	OTG_STATE_A_WAIT_VRISE,
	OTG_STATE_A_WAIT_BCON,
	OTG_STATE_A_HOST,
	OTG_STATE_A_SUSPEND,
	OTG_STATE_A_PERIPHERAL,
	OTG_STATE_A_WAIT_VFALL,
	OTG_STATE_A_VBUS_ERR,
};

<<<<<<< HEAD
enum usb_otg_event {
	/* Device is not connected within
	 * TA_WAIT_BCON or not responding.
	 */
	OTG_EVENT_DEV_CONN_TMOUT,
	/* B-device returned STALL for
	 * B_HNP_ENABLE feature request.
	 */
	OTG_EVENT_NO_RESP_FOR_HNP_ENABLE,
	/* HUB class devices are not
	 * supported.
	 */
	OTG_EVENT_HUB_NOT_SUPPORTED,
	/* Device is not supported i.e
	 * not listed in TPL.
	 */
	OTG_EVENT_DEV_NOT_SUPPORTED,
	/* HNP failed due to
	 * TA_AIDL_BDIS timeout or
	 * TB_ASE0_BRST timeout
	 */
	OTG_EVENT_HNP_FAILED,
	/* B-device did not detect VBUS
	 * within TB_SRP_FAIL time.
	 */
	OTG_EVENT_NO_RESP_FOR_SRP,
};

enum usb_phy_events {
=======
enum usb_xceiv_events {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	USB_EVENT_NONE,         /* no events or cable disconnected */
	USB_EVENT_VBUS,         /* vbus valid event */
	USB_EVENT_ID,           /* id was grounded */
	USB_EVENT_CHARGER,      /* usb dedicated charger */
	USB_EVENT_ENUMERATED,   /* gadget driver enumerated */
};

<<<<<<< HEAD
struct usb_phy;
=======
struct otg_transceiver;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

/* for transceivers connected thru an ULPI interface, the user must
 * provide access ops
 */
<<<<<<< HEAD
struct usb_phy_io_ops {
	int (*read)(struct usb_phy *x, u32 reg);
	int (*write)(struct usb_phy *x, u32 val, u32 reg);
};

struct usb_otg {
	u8			default_a;

	struct usb_phy		*phy;
	struct usb_bus		*host;
	struct usb_gadget	*gadget;

	/* bind/unbind the host controller */
	int	(*set_host)(struct usb_otg *otg, struct usb_bus *host);

	/* bind/unbind the peripheral controller */
	int	(*set_peripheral)(struct usb_otg *otg,
					struct usb_gadget *gadget);

	/* effective for A-peripheral, ignored for B devices */
	int	(*set_vbus)(struct usb_otg *otg, bool enabled);

	/* for B devices only:  start session with A-Host */
	int	(*start_srp)(struct usb_otg *otg);

	/* start or continue HNP role switch */
	int	(*start_hnp)(struct usb_otg *otg);

	/* send events to user space */
	int	(*send_event)(struct usb_otg *otg,
			enum usb_otg_event event);

=======
struct otg_io_access_ops {
	int (*read)(struct otg_transceiver *otg, u32 reg);
	int (*write)(struct otg_transceiver *otg, u32 val, u32 reg);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};

/*
 * the otg driver needs to interact with both device side and host side
 * usb controllers.  it decides which controller is active at a given
 * moment, using the transceiver, ID signal, HNP and sometimes static
 * configuration information (including "board isn't wired for otg").
 */
<<<<<<< HEAD
struct usb_phy {
=======
struct otg_transceiver {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	struct device		*dev;
	const char		*label;
	unsigned int		 flags;

<<<<<<< HEAD
	enum usb_otg_state	state;
	enum usb_phy_events	last_event;

	struct usb_otg		*otg;

	struct device		*io_dev;
	struct usb_phy_io_ops	*io_ops;
	void __iomem		*io_priv;

	/* for notification of usb_phy_events */
=======
	u8			default_a;
	enum usb_otg_state	state;
	enum usb_xceiv_events	last_event;

	struct usb_bus		*host;
	struct usb_gadget	*gadget;

	struct otg_io_access_ops	*io_ops;
	void __iomem			*io_priv;

	/* for notification of usb_xceiv_events */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	struct atomic_notifier_head	notifier;

	/* to pass extra port status to the root hub */
	u16			port_status;
	u16			port_change;

	/* initialize/shutdown the OTG controller */
<<<<<<< HEAD
	int	(*init)(struct usb_phy *x);
	void	(*shutdown)(struct usb_phy *x);

	/* effective for B devices, ignored for A-peripheral */
	int	(*set_power)(struct usb_phy *x,
				unsigned mA);

	/* for non-OTG B devices: set transceiver into suspend mode */
	int	(*set_suspend)(struct usb_phy *x,
				int suspend);

=======
	int	(*init)(struct otg_transceiver *otg);
	void	(*shutdown)(struct otg_transceiver *otg);

	/* bind/unbind the host controller */
	int	(*set_host)(struct otg_transceiver *otg,
				struct usb_bus *host);

	/* bind/unbind the peripheral controller */
	int	(*set_peripheral)(struct otg_transceiver *otg,
				struct usb_gadget *gadget);

	/* effective for B devices, ignored for A-peripheral */
	int	(*set_power)(struct otg_transceiver *otg,
				unsigned mA);

	/* effective for A-peripheral, ignored for B devices */
	int	(*set_vbus)(struct otg_transceiver *otg,
				bool enabled);

	/* for non-OTG B devices: set transceiver into suspend mode */
	int	(*set_suspend)(struct otg_transceiver *otg,
				int suspend);

	/* for B devices only:  start session with A-Host */
	int	(*start_srp)(struct otg_transceiver *otg);

	/* start or continue HNP role switch */
	int	(*start_hnp)(struct otg_transceiver *otg);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};


/* for board-specific init logic */
<<<<<<< HEAD
extern int usb_set_transceiver(struct usb_phy *);
=======
extern int otg_set_transceiver(struct otg_transceiver *);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#if defined(CONFIG_NOP_USB_XCEIV) || (defined(CONFIG_NOP_USB_XCEIV_MODULE) && defined(MODULE))
/* sometimes transceivers are accessed only through e.g. ULPI */
extern void usb_nop_xceiv_register(void);
extern void usb_nop_xceiv_unregister(void);
#else
static inline void usb_nop_xceiv_register(void)
{
}

static inline void usb_nop_xceiv_unregister(void)
{
}
#endif

/* helpers for direct access thru low-level io interface */
<<<<<<< HEAD
static inline int usb_phy_io_read(struct usb_phy *x, u32 reg)
{
	if (x->io_ops && x->io_ops->read)
		return x->io_ops->read(x, reg);
=======
static inline int otg_io_read(struct otg_transceiver *otg, u32 reg)
{
	if (otg->io_ops && otg->io_ops->read)
		return otg->io_ops->read(otg, reg);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	return -EINVAL;
}

<<<<<<< HEAD
static inline int usb_phy_io_write(struct usb_phy *x, u32 val, u32 reg)
{
	if (x->io_ops && x->io_ops->write)
		return x->io_ops->write(x, val, reg);
=======
static inline int otg_io_write(struct otg_transceiver *otg, u32 val, u32 reg)
{
	if (otg->io_ops && otg->io_ops->write)
		return otg->io_ops->write(otg, val, reg);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	return -EINVAL;
}

static inline int
<<<<<<< HEAD
usb_phy_init(struct usb_phy *x)
{
	if (x->init)
		return x->init(x);
=======
otg_init(struct otg_transceiver *otg)
{
	if (otg->init)
		return otg->init(otg);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	return 0;
}

static inline void
<<<<<<< HEAD
usb_phy_shutdown(struct usb_phy *x)
{
	if (x->shutdown)
		x->shutdown(x);
}

/* for USB core, host and peripheral controller drivers */
/* Context: can sleep */
extern int otg_send_event(enum usb_otg_event event);

/* for usb host and peripheral controller drivers */
#ifdef CONFIG_USB_OTG_UTILS
extern struct usb_phy *usb_get_transceiver(void);
extern void usb_put_transceiver(struct usb_phy *);
extern const char *otg_state_string(enum usb_otg_state state);
#else
static inline struct usb_phy *usb_get_transceiver(void)
=======
otg_shutdown(struct otg_transceiver *otg)
{
	if (otg->shutdown)
		otg->shutdown(otg);
}

/* for usb host and peripheral controller drivers */
#ifdef CONFIG_USB_OTG_UTILS
extern struct otg_transceiver *otg_get_transceiver(void);
extern void otg_put_transceiver(struct otg_transceiver *);
extern const char *otg_state_string(enum usb_otg_state state);
#else
static inline struct otg_transceiver *otg_get_transceiver(void)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
	return NULL;
}

<<<<<<< HEAD
static inline void usb_put_transceiver(struct usb_phy *x)
=======
static inline void otg_put_transceiver(struct otg_transceiver *x)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
{
}

static inline const char *otg_state_string(enum usb_otg_state state)
{
	return NULL;
}
#endif

/* Context: can sleep */
static inline int
<<<<<<< HEAD
otg_start_hnp(struct usb_otg *otg)
{
	if (otg && otg->start_hnp)
		return otg->start_hnp(otg);

	return -ENOTSUPP;
=======
otg_start_hnp(struct otg_transceiver *otg)
{
	return otg->start_hnp(otg);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

/* Context: can sleep */
static inline int
<<<<<<< HEAD
otg_set_vbus(struct usb_otg *otg, bool enabled)
{
	if (otg && otg->set_vbus)
		return otg->set_vbus(otg, enabled);

	return -ENOTSUPP;
=======
otg_set_vbus(struct otg_transceiver *otg, bool enabled)
{
	return otg->set_vbus(otg, enabled);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

/* for HCDs */
static inline int
<<<<<<< HEAD
otg_set_host(struct usb_otg *otg, struct usb_bus *host)
{
	if (otg && otg->set_host)
		return otg->set_host(otg, host);

	return -ENOTSUPP;
=======
otg_set_host(struct otg_transceiver *otg, struct usb_bus *host)
{
	return otg->set_host(otg, host);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

/* for usb peripheral controller drivers */

/* Context: can sleep */
static inline int
<<<<<<< HEAD
otg_set_peripheral(struct usb_otg *otg, struct usb_gadget *periph)
{
	if (otg && otg->set_peripheral)
		return otg->set_peripheral(otg, periph);

	return -ENOTSUPP;
}

static inline int
usb_phy_set_power(struct usb_phy *x, unsigned mA)
{
	if (x && x->set_power)
		return x->set_power(x, mA);
	return 0;
=======
otg_set_peripheral(struct otg_transceiver *otg, struct usb_gadget *periph)
{
	return otg->set_peripheral(otg, periph);
}

static inline int
otg_set_power(struct otg_transceiver *otg, unsigned mA)
{
	return otg->set_power(otg, mA);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

/* Context: can sleep */
static inline int
<<<<<<< HEAD
usb_phy_set_suspend(struct usb_phy *x, int suspend)
{
	if (x->set_suspend != NULL)
		return x->set_suspend(x, suspend);
=======
otg_set_suspend(struct otg_transceiver *otg, int suspend)
{
	if (otg->set_suspend != NULL)
		return otg->set_suspend(otg, suspend);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	else
		return 0;
}

static inline int
<<<<<<< HEAD
otg_start_srp(struct usb_otg *otg)
{
	if (otg && otg->start_srp)
		return otg->start_srp(otg);

	return -ENOTSUPP;
=======
otg_start_srp(struct otg_transceiver *otg)
{
	return otg->start_srp(otg);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

/* notifiers */
static inline int
<<<<<<< HEAD
usb_register_notifier(struct usb_phy *x, struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&x->notifier, nb);
}

static inline void
usb_unregister_notifier(struct usb_phy *x, struct notifier_block *nb)
{
	atomic_notifier_chain_unregister(&x->notifier, nb);
=======
otg_register_notifier(struct otg_transceiver *otg, struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&otg->notifier, nb);
}

static inline void
otg_unregister_notifier(struct otg_transceiver *otg, struct notifier_block *nb)
{
	atomic_notifier_chain_unregister(&otg->notifier, nb);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
}

/* for OTG controller drivers (and maybe other stuff) */
extern int usb_bus_start_enum(struct usb_bus *bus, unsigned port_num);

#endif /* __LINUX_USB_OTG_H */
