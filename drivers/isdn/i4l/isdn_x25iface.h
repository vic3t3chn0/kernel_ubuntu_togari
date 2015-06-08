/* $Id: isdn_x25iface.h,v 1.1.2.2 2004/01/12 22:37:19 keil Exp $
 *
 * header for Linux ISDN subsystem, x.25 related functions
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#ifndef _LINUX_ISDN_X25IFACE_H
#define _LINUX_ISDN_X25IFACE_H

#define ISDN_X25IFACE_MAGIC 0x1e75a2b9
/* #define DEBUG_ISDN_X25 if you want isdn_x25 debugging messages */
#ifdef DEBUG_ISDN_X25
<<<<<<< HEAD
<<<<<<< HEAD
#   define IX25DEBUG(fmt, args...) printk(KERN_DEBUG fmt, ##args)
#else
#   define IX25DEBUG(fmt, args...)
=======
#   define IX25DEBUG(fmt,args...) printk(KERN_DEBUG fmt , ## args)
#else
#   define IX25DEBUG(fmt,args...)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#   define IX25DEBUG(fmt,args...) printk(KERN_DEBUG fmt , ## args)
#else
#   define IX25DEBUG(fmt,args...)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif

#include <linux/skbuff.h>
#include <linux/wanrouter.h>
#include <linux/isdn.h>
#include <linux/concap.h>

<<<<<<< HEAD
<<<<<<< HEAD
extern struct concap_proto_ops *isdn_x25iface_concap_proto_ops_pt;
extern struct concap_proto *isdn_x25iface_proto_new(void);
=======
extern struct concap_proto_ops * isdn_x25iface_concap_proto_ops_pt;
extern struct concap_proto     * isdn_x25iface_proto_new(void);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
extern struct concap_proto_ops * isdn_x25iface_concap_proto_ops_pt;
extern struct concap_proto     * isdn_x25iface_proto_new(void);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2



#endif
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2








<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
