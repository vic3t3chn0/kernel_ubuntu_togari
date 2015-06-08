/*
 * Copyright 2004, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef _WME_H
#define _WME_H

#include <linux/netdevice.h>
#include "ieee80211_i.h"

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern const int ieee802_1d_to_ac[8];

u16 ieee80211_select_queue_80211(struct ieee80211_local *local,
				 struct sk_buff *skb,
				 struct ieee80211_hdr *hdr);
u16 ieee80211_select_queue(struct ieee80211_sub_if_data *sdata,
			   struct sk_buff *skb);
void ieee80211_set_qos_hdr(struct ieee80211_sub_if_data *sdata,
			   struct sk_buff *skb);
<<<<<<< HEAD
=======
=======
#define QOS_CONTROL_ACK_POLICY_NORMAL 0
#define QOS_CONTROL_ACK_POLICY_NOACK 1

#define QOS_CONTROL_ACK_POLICY_SHIFT 5

extern const int ieee802_1d_to_ac[8];

u16 ieee80211_select_queue(struct ieee80211_sub_if_data *sdata,
			   struct sk_buff *skb);
void ieee80211_set_qos_hdr(struct ieee80211_local *local, struct sk_buff *skb);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
u16 ieee80211_downgrade_queue(struct ieee80211_local *local,
                              struct sk_buff *skb);


#endif /* _WME_H */
