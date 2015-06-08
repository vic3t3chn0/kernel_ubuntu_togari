/*
 * Marvell Wireless LAN device driver: utility functions
 *
 * Copyright (C) 2011, Marvell International Ltd.
 *
 * This software file (the "File") is distributed by Marvell International
 * Ltd. under the terms of the GNU General Public License Version 2, June 1991
 * (the "License").  You may use, redistribute and/or modify this File in
 * accordance with the terms and conditions of the License, a copy of which
 * is available by writing to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA or on the
 * worldwide web at http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt.
 *
 * THE FILE IS DISTRIBUTED AS-IS, WITHOUT WARRANTY OF ANY KIND, AND THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE
 * ARE EXPRESSLY DISCLAIMED.  The License provides additional details about
 * this warranty disclaimer.
 */

#ifndef _MWIFIEX_UTIL_H_
#define _MWIFIEX_UTIL_H_

static inline struct mwifiex_rxinfo *MWIFIEX_SKB_RXCB(struct sk_buff *skb)
{
<<<<<<< HEAD
<<<<<<< HEAD
	return (struct mwifiex_rxinfo *)(skb->cb + sizeof(phys_addr_t));
=======
	return (struct mwifiex_rxinfo *)skb->cb;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return (struct mwifiex_rxinfo *)skb->cb;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static inline struct mwifiex_txinfo *MWIFIEX_SKB_TXCB(struct sk_buff *skb)
{
<<<<<<< HEAD
<<<<<<< HEAD
	return (struct mwifiex_txinfo *)(skb->cb + sizeof(phys_addr_t));
}

static inline phys_addr_t *MWIFIEX_SKB_PACB(struct sk_buff *skb)
{
	return (phys_addr_t *)skb->cb;
=======
	return (struct mwifiex_txinfo *)skb->cb;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return (struct mwifiex_txinfo *)skb->cb;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
#endif /* !_MWIFIEX_UTIL_H_ */
