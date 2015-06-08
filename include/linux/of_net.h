/*
 * OF helpers for network devices.
 *
 * This file is released under the GPLv2
 */

#ifndef __LINUX_OF_NET_H
#define __LINUX_OF_NET_H

#ifdef CONFIG_OF_NET
#include <linux/of.h>
<<<<<<< HEAD
extern const int of_get_phy_mode(struct device_node *np);
=======
<<<<<<< HEAD
extern const int of_get_phy_mode(struct device_node *np);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern const void *of_get_mac_address(struct device_node *np);
#endif

#endif /* __LINUX_OF_NET_H */
