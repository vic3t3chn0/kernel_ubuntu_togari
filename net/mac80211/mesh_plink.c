/*
 * Copyright (c) 2008, 2009 open80211s Ltd.
 * Author:     Luis Carlos Cobo <luisca@cozybit.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/gfp.h>
#include <linux/kernel.h>
#include <linux/random.h>
#include "ieee80211_i.h"
#include "rate.h"
#include "mesh.h"

#ifdef CONFIG_MAC80211_VERBOSE_MPL_DEBUG
#define mpl_dbg(fmt, args...)	printk(KERN_DEBUG fmt, ##args)
#else
#define mpl_dbg(fmt, args...)	do { (void)(0); } while (0)
#endif

<<<<<<< HEAD
#define PLINK_GET_LLID(p) (p + 2)
#define PLINK_GET_PLID(p) (p + 4)
=======
#define PLINK_GET_LLID(p) (p + 4)
#define PLINK_GET_PLID(p) (p + 6)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#define mod_plink_timer(s, t) (mod_timer(&s->plink_timer, \
				jiffies + HZ * t / 1000))

<<<<<<< HEAD
=======
/* Peer link cancel reasons, all subject to ANA approval */
#define MESH_LINK_CANCELLED			2
#define MESH_MAX_NEIGHBORS			3
#define MESH_CAPABILITY_POLICY_VIOLATION	4
#define MESH_CLOSE_RCVD				5
#define MESH_MAX_RETRIES			6
#define MESH_CONFIRM_TIMEOUT			7
#define MESH_SECURITY_ROLE_NEGOTIATION_DIFFERS	8
#define MESH_SECURITY_AUTHENTICATION_IMPOSSIBLE	9
#define MESH_SECURITY_FAILED_VERIFICATION	10

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#define dot11MeshMaxRetries(s) (s->u.mesh.mshcfg.dot11MeshMaxRetries)
#define dot11MeshRetryTimeout(s) (s->u.mesh.mshcfg.dot11MeshRetryTimeout)
#define dot11MeshConfirmTimeout(s) (s->u.mesh.mshcfg.dot11MeshConfirmTimeout)
#define dot11MeshHoldingTimeout(s) (s->u.mesh.mshcfg.dot11MeshHoldingTimeout)
#define dot11MeshMaxPeerLinks(s) (s->u.mesh.mshcfg.dot11MeshMaxPeerLinks)

<<<<<<< HEAD
/* We only need a valid sta if user configured a minimum rssi_threshold. */
#define rssi_threshold_check(sta, sdata) \
		(sdata->u.mesh.mshcfg.rssi_threshold == 0 ||\
		(sta && (s8) -ewma_read(&sta->avg_signal) > \
		sdata->u.mesh.mshcfg.rssi_threshold))
=======
enum plink_frame_type {
	PLINK_OPEN = 1,
	PLINK_CONFIRM,
	PLINK_CLOSE
};
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

enum plink_event {
	PLINK_UNDEFINED,
	OPN_ACPT,
	OPN_RJCT,
	OPN_IGNR,
	CNF_ACPT,
	CNF_RJCT,
	CNF_IGNR,
	CLS_ACPT,
	CLS_IGNR
};

<<<<<<< HEAD
static int mesh_plink_frame_tx(struct ieee80211_sub_if_data *sdata,
		enum ieee80211_self_protected_actioncode action,
		u8 *da, __le16 llid, __le16 plid, __le16 reason);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
static inline
void mesh_plink_inc_estab_count(struct ieee80211_sub_if_data *sdata)
{
	atomic_inc(&sdata->u.mesh.mshstats.estab_plinks);
	mesh_accept_plinks_update(sdata);
}

static inline
void mesh_plink_dec_estab_count(struct ieee80211_sub_if_data *sdata)
{
	atomic_dec(&sdata->u.mesh.mshstats.estab_plinks);
	mesh_accept_plinks_update(sdata);
}

/**
 * mesh_plink_fsm_restart - restart a mesh peer link finite state machine
 *
 * @sta: mesh peer link to restart
 *
 * Locking: this function must be called holding sta->lock
 */
static inline void mesh_plink_fsm_restart(struct sta_info *sta)
{
	sta->plink_state = NL80211_PLINK_LISTEN;
	sta->llid = sta->plid = sta->reason = 0;
	sta->plink_retries = 0;
}

/*
 * NOTE: This is just an alias for sta_info_alloc(), see notes
 *       on it in the lifecycle management section!
 */
static struct sta_info *mesh_plink_alloc(struct ieee80211_sub_if_data *sdata,
<<<<<<< HEAD
					 u8 *hw_addr, u32 rates,
					 struct ieee802_11_elems *elems)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_supported_band *sband;
	struct sta_info *sta;

	sband = local->hw.wiphy->bands[local->oper_channel->band];

=======
					 u8 *hw_addr, u32 rates)
{
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	if (local->num_sta >= MESH_MAX_PLINKS)
		return NULL;

	sta = sta_info_alloc(sdata, hw_addr, GFP_KERNEL);
	if (!sta)
		return NULL;

<<<<<<< HEAD
	sta_info_pre_move_state(sta, IEEE80211_STA_AUTH);
	sta_info_pre_move_state(sta, IEEE80211_STA_ASSOC);
	sta_info_pre_move_state(sta, IEEE80211_STA_AUTHORIZED);

	set_sta_flag(sta, WLAN_STA_WME);

	sta->sta.supp_rates[local->hw.conf.channel->band] = rates;
	if (elems->ht_cap_elem)
		ieee80211_ht_cap_ie_to_sta_ht_cap(sdata, sband,
						  elems->ht_cap_elem,
						  &sta->sta.ht_cap);
=======
	sta->flags = WLAN_STA_AUTHORIZED | WLAN_STA_AUTH;
	sta->sta.supp_rates[local->hw.conf.channel->band] = rates;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	rate_control_rate_init(sta);

	return sta;
}

/**
 * __mesh_plink_deactivate - deactivate mesh peer link
 *
 * @sta: mesh peer link to deactivate
 *
 * All mesh paths with this peer as next hop will be flushed
 *
 * Locking: the caller must hold sta->lock
 */
static bool __mesh_plink_deactivate(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	bool deactivated = false;

	if (sta->plink_state == NL80211_PLINK_ESTAB) {
		mesh_plink_dec_estab_count(sdata);
		deactivated = true;
	}
	sta->plink_state = NL80211_PLINK_BLOCKED;
	mesh_path_flush_by_nexthop(sta);

	return deactivated;
}

/**
 * mesh_plink_deactivate - deactivate mesh peer link
 *
 * @sta: mesh peer link to deactivate
 *
 * All mesh paths with this peer as next hop will be flushed
 */
void mesh_plink_deactivate(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	bool deactivated;

	spin_lock_bh(&sta->lock);
	deactivated = __mesh_plink_deactivate(sta);
<<<<<<< HEAD
	sta->reason = cpu_to_le16(WLAN_REASON_MESH_PEER_CANCELED);
	mesh_plink_frame_tx(sdata, WLAN_SP_MESH_PEERING_CLOSE,
			    sta->sta.addr, sta->llid, sta->plid,
			    sta->reason);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	spin_unlock_bh(&sta->lock);

	if (deactivated)
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BEACON);
}

static int mesh_plink_frame_tx(struct ieee80211_sub_if_data *sdata,
<<<<<<< HEAD
		enum ieee80211_self_protected_actioncode action,
		u8 *da, __le16 llid, __le16 plid, __le16 reason) {
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb;
	struct ieee80211_mgmt *mgmt;
	bool include_plid = false;
	u16 peering_proto = 0;
	u8 *pos, ie_len = 4;
	int hdr_len = offsetof(struct ieee80211_mgmt, u.action.u.self_prot) +
		      sizeof(mgmt->u.action.u.self_prot);

	skb = dev_alloc_skb(local->tx_headroom +
			    hdr_len +
			    2 + /* capability info */
			    2 + /* AID */
			    2 + 8 + /* supported rates */
			    2 + (IEEE80211_MAX_SUPP_RATES - 8) +
			    2 + sdata->u.mesh.mesh_id_len +
			    2 + sizeof(struct ieee80211_meshconf_ie) +
			    2 + sizeof(struct ieee80211_ht_cap) +
			    2 + sizeof(struct ieee80211_ht_info) +
			    2 + 8 + /* peering IE */
			    sdata->u.mesh.ie_len);
	if (!skb)
		return -1;
	skb_reserve(skb, local->tx_headroom);
	mgmt = (struct ieee80211_mgmt *) skb_put(skb, hdr_len);
	memset(mgmt, 0, hdr_len);
=======
		enum plink_frame_type action, u8 *da, __le16 llid, __le16 plid,
		__le16 reason) {
	struct ieee80211_local *local = sdata->local;
	struct sk_buff *skb = dev_alloc_skb(local->hw.extra_tx_headroom + 400 +
			sdata->u.mesh.ie_len);
	struct ieee80211_mgmt *mgmt;
	bool include_plid = false;
	static const u8 meshpeeringproto[] = { 0x00, 0x0F, 0xAC, 0x2A };
	u8 *pos;
	int ie_len;

	if (!skb)
		return -1;
	skb_reserve(skb, local->hw.extra_tx_headroom);
	/* 25 is the size of the common mgmt part (24) plus the size of the
	 * common action part (1)
	 */
	mgmt = (struct ieee80211_mgmt *)
		skb_put(skb, 25 + sizeof(mgmt->u.action.u.plink_action));
	memset(mgmt, 0, 25 + sizeof(mgmt->u.action.u.plink_action));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);
	memcpy(mgmt->da, da, ETH_ALEN);
	memcpy(mgmt->sa, sdata->vif.addr, ETH_ALEN);
	memcpy(mgmt->bssid, sdata->vif.addr, ETH_ALEN);
<<<<<<< HEAD
	mgmt->u.action.category = WLAN_CATEGORY_SELF_PROTECTED;
	mgmt->u.action.u.self_prot.action_code = action;

	if (action != WLAN_SP_MESH_PEERING_CLOSE) {
		/* capability info */
		pos = skb_put(skb, 2);
		memset(pos, 0, 2);
		if (action == WLAN_SP_MESH_PEERING_CONFIRM) {
			/* AID */
			pos = skb_put(skb, 2);
			memcpy(pos + 2, &plid, 2);
		}
		if (ieee80211_add_srates_ie(&sdata->vif, skb) ||
		    ieee80211_add_ext_srates_ie(&sdata->vif, skb) ||
		    mesh_add_rsn_ie(skb, sdata) ||
		    mesh_add_meshid_ie(skb, sdata) ||
		    mesh_add_meshconf_ie(skb, sdata))
			return -1;
	} else {	/* WLAN_SP_MESH_PEERING_CLOSE */
		if (mesh_add_meshid_ie(skb, sdata))
			return -1;
	}

	/* Add Mesh Peering Management element */
	switch (action) {
	case WLAN_SP_MESH_PEERING_OPEN:
		break;
	case WLAN_SP_MESH_PEERING_CONFIRM:
		ie_len += 2;
		include_plid = true;
		break;
	case WLAN_SP_MESH_PEERING_CLOSE:
		if (plid) {
			ie_len += 2;
			include_plid = true;
		}
		ie_len += 2;	/* reason code */
		break;
	default:
		return -EINVAL;
	}

	if (WARN_ON(skb_tailroom(skb) < 2 + ie_len))
		return -ENOMEM;

	pos = skb_put(skb, 2 + ie_len);
	*pos++ = WLAN_EID_PEER_MGMT;
	*pos++ = ie_len;
	memcpy(pos, &peering_proto, 2);
	pos += 2;
	memcpy(pos, &llid, 2);
	pos += 2;
	if (include_plid) {
		memcpy(pos, &plid, 2);
		pos += 2;
	}
	if (action == WLAN_SP_MESH_PEERING_CLOSE) {
		memcpy(pos, &reason, 2);
		pos += 2;
	}

	if (action != WLAN_SP_MESH_PEERING_CLOSE) {
		if (mesh_add_ht_cap_ie(skb, sdata) ||
		    mesh_add_ht_info_ie(skb, sdata))
			return -1;
	}

	if (mesh_add_vendor_ies(skb, sdata))
		return -1;

=======
	mgmt->u.action.category = WLAN_CATEGORY_MESH_ACTION;
	mgmt->u.action.u.plink_action.action_code = action;

	if (action == PLINK_CLOSE)
		mgmt->u.action.u.plink_action.aux = reason;
	else {
		mgmt->u.action.u.plink_action.aux = cpu_to_le16(0x0);
		if (action == PLINK_CONFIRM) {
			pos = skb_put(skb, 4);
			/* two-byte status code followed by two-byte AID */
			memset(pos, 0, 2);
			memcpy(pos + 2, &plid, 2);
		}
		mesh_mgmt_ies_add(skb, sdata);
	}

	/* Add Peer Link Management element */
	switch (action) {
	case PLINK_OPEN:
		ie_len = 6;
		break;
	case PLINK_CONFIRM:
		ie_len = 8;
		include_plid = true;
		break;
	case PLINK_CLOSE:
	default:
		if (!plid)
			ie_len = 8;
		else {
			ie_len = 10;
			include_plid = true;
		}
		break;
	}

	pos = skb_put(skb, 2 + ie_len);
	*pos++ = WLAN_EID_PEER_LINK;
	*pos++ = ie_len;
	memcpy(pos, meshpeeringproto, sizeof(meshpeeringproto));
	pos += 4;
	memcpy(pos, &llid, 2);
	if (include_plid) {
		pos += 2;
		memcpy(pos, &plid, 2);
	}
	if (action == PLINK_CLOSE) {
		pos += 2;
		memcpy(pos, &reason, 2);
	}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	ieee80211_tx_skb(sdata, skb);
	return 0;
}

void mesh_neighbour_update(u8 *hw_addr, u32 rates,
		struct ieee80211_sub_if_data *sdata,
		struct ieee802_11_elems *elems)
{
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;

	rcu_read_lock();

	sta = sta_info_get(sdata, hw_addr);
	if (!sta) {
		rcu_read_unlock();
		/* Userspace handles peer allocation when security is enabled
		 * */
		if (sdata->u.mesh.security & IEEE80211_MESH_SEC_AUTHED)
			cfg80211_notify_new_peer_candidate(sdata->dev, hw_addr,
					elems->ie_start, elems->total_len,
					GFP_KERNEL);
		else
<<<<<<< HEAD
			sta = mesh_plink_alloc(sdata, hw_addr, rates, elems);
=======
			sta = mesh_plink_alloc(sdata, hw_addr, rates);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (!sta)
			return;
		if (sta_info_insert_rcu(sta)) {
			rcu_read_unlock();
			return;
		}
	}

	sta->last_rx = jiffies;
	sta->sta.supp_rates[local->hw.conf.channel->band] = rates;
	if (mesh_peer_accepts_plinks(elems) &&
			sta->plink_state == NL80211_PLINK_LISTEN &&
			sdata->u.mesh.accepting_plinks &&
<<<<<<< HEAD
			sdata->u.mesh.mshcfg.auto_open_plinks &&
			rssi_threshold_check(sta, sdata))
=======
			sdata->u.mesh.mshcfg.auto_open_plinks)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		mesh_plink_open(sta);

	rcu_read_unlock();
}

static void mesh_plink_timer(unsigned long data)
{
	struct sta_info *sta;
	__le16 llid, plid, reason;
	struct ieee80211_sub_if_data *sdata;

	/*
	 * This STA is valid because sta_info_destroy() will
	 * del_timer_sync() this timer after having made sure
	 * it cannot be readded (by deleting the plink.)
	 */
	sta = (struct sta_info *) data;

	if (sta->sdata->local->quiescing) {
		sta->plink_timer_was_running = true;
		return;
	}

	spin_lock_bh(&sta->lock);
	if (sta->ignore_plink_timer) {
		sta->ignore_plink_timer = false;
		spin_unlock_bh(&sta->lock);
		return;
	}
	mpl_dbg("Mesh plink timer for %pM fired on state %d\n",
		sta->sta.addr, sta->plink_state);
	reason = 0;
	llid = sta->llid;
	plid = sta->plid;
	sdata = sta->sdata;

	switch (sta->plink_state) {
	case NL80211_PLINK_OPN_RCVD:
	case NL80211_PLINK_OPN_SNT:
		/* retry timer */
		if (sta->plink_retries < dot11MeshMaxRetries(sdata)) {
			u32 rand;
			mpl_dbg("Mesh plink for %pM (retry, timeout): %d %d\n",
				sta->sta.addr, sta->plink_retries,
				sta->plink_timeout);
			get_random_bytes(&rand, sizeof(u32));
			sta->plink_timeout = sta->plink_timeout +
					     rand % sta->plink_timeout;
			++sta->plink_retries;
			mod_plink_timer(sta, sta->plink_timeout);
			spin_unlock_bh(&sta->lock);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata, WLAN_SP_MESH_PEERING_OPEN,
					    sta->sta.addr, llid, 0, 0);
			break;
		}
		reason = cpu_to_le16(WLAN_REASON_MESH_MAX_RETRIES);
=======
			mesh_plink_frame_tx(sdata, PLINK_OPEN, sta->sta.addr, llid,
					    0, 0);
			break;
		}
		reason = cpu_to_le16(MESH_MAX_RETRIES);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		/* fall through on else */
	case NL80211_PLINK_CNF_RCVD:
		/* confirm timer */
		if (!reason)
<<<<<<< HEAD
			reason = cpu_to_le16(WLAN_REASON_MESH_CONFIRM_TIMEOUT);
		sta->plink_state = NL80211_PLINK_HOLDING;
		mod_plink_timer(sta, dot11MeshHoldingTimeout(sdata));
		spin_unlock_bh(&sta->lock);
		mesh_plink_frame_tx(sdata, WLAN_SP_MESH_PEERING_CLOSE,
				    sta->sta.addr, llid, plid, reason);
=======
			reason = cpu_to_le16(MESH_CONFIRM_TIMEOUT);
		sta->plink_state = NL80211_PLINK_HOLDING;
		mod_plink_timer(sta, dot11MeshHoldingTimeout(sdata));
		spin_unlock_bh(&sta->lock);
		mesh_plink_frame_tx(sdata, PLINK_CLOSE, sta->sta.addr, llid, plid,
				    reason);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		break;
	case NL80211_PLINK_HOLDING:
		/* holding timer */
		del_timer(&sta->plink_timer);
		mesh_plink_fsm_restart(sta);
		spin_unlock_bh(&sta->lock);
		break;
	default:
		spin_unlock_bh(&sta->lock);
		break;
	}
}

#ifdef CONFIG_PM
void mesh_plink_quiesce(struct sta_info *sta)
{
	if (del_timer_sync(&sta->plink_timer))
		sta->plink_timer_was_running = true;
}

void mesh_plink_restart(struct sta_info *sta)
{
	if (sta->plink_timer_was_running) {
		add_timer(&sta->plink_timer);
		sta->plink_timer_was_running = false;
	}
}
#endif

static inline void mesh_plink_timer_set(struct sta_info *sta, int timeout)
{
	sta->plink_timer.expires = jiffies + (HZ * timeout / 1000);
	sta->plink_timer.data = (unsigned long) sta;
	sta->plink_timer.function = mesh_plink_timer;
	sta->plink_timeout = timeout;
	add_timer(&sta->plink_timer);
}

int mesh_plink_open(struct sta_info *sta)
{
	__le16 llid;
	struct ieee80211_sub_if_data *sdata = sta->sdata;

<<<<<<< HEAD
	if (!test_sta_flag(sta, WLAN_STA_AUTH))
=======
	if (!test_sta_flags(sta, WLAN_STA_AUTH))
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		return -EPERM;

	spin_lock_bh(&sta->lock);
	get_random_bytes(&llid, 2);
	sta->llid = llid;
	if (sta->plink_state != NL80211_PLINK_LISTEN) {
		spin_unlock_bh(&sta->lock);
		return -EBUSY;
	}
	sta->plink_state = NL80211_PLINK_OPN_SNT;
	mesh_plink_timer_set(sta, dot11MeshRetryTimeout(sdata));
	spin_unlock_bh(&sta->lock);
	mpl_dbg("Mesh plink: starting establishment with %pM\n",
		sta->sta.addr);

<<<<<<< HEAD
	return mesh_plink_frame_tx(sdata, WLAN_SP_MESH_PEERING_OPEN,
=======
	return mesh_plink_frame_tx(sdata, PLINK_OPEN,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
				   sta->sta.addr, llid, 0, 0);
}

void mesh_plink_block(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	bool deactivated;

	spin_lock_bh(&sta->lock);
	deactivated = __mesh_plink_deactivate(sta);
	sta->plink_state = NL80211_PLINK_BLOCKED;
	spin_unlock_bh(&sta->lock);

	if (deactivated)
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BEACON);
}


void mesh_rx_plink_frame(struct ieee80211_sub_if_data *sdata, struct ieee80211_mgmt *mgmt,
			 size_t len, struct ieee80211_rx_status *rx_status)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee802_11_elems elems;
	struct sta_info *sta;
	enum plink_event event;
<<<<<<< HEAD
	enum ieee80211_self_protected_actioncode ftype;
=======
	enum plink_frame_type ftype;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	size_t baselen;
	bool deactivated, matches_local = true;
	u8 ie_len;
	u8 *baseaddr;
	__le16 plid, llid, reason;
#ifdef CONFIG_MAC80211_VERBOSE_MPL_DEBUG
	static const char *mplstates[] = {
		[NL80211_PLINK_LISTEN] = "LISTEN",
		[NL80211_PLINK_OPN_SNT] = "OPN-SNT",
		[NL80211_PLINK_OPN_RCVD] = "OPN-RCVD",
		[NL80211_PLINK_CNF_RCVD] = "CNF_RCVD",
		[NL80211_PLINK_ESTAB] = "ESTAB",
		[NL80211_PLINK_HOLDING] = "HOLDING",
		[NL80211_PLINK_BLOCKED] = "BLOCKED"
	};
#endif

	/* need action_code, aux */
	if (len < IEEE80211_MIN_ACTION_SIZE + 3)
		return;

	if (is_multicast_ether_addr(mgmt->da)) {
		mpl_dbg("Mesh plink: ignore frame from multicast address");
		return;
	}

<<<<<<< HEAD
	baseaddr = mgmt->u.action.u.self_prot.variable;
	baselen = (u8 *) mgmt->u.action.u.self_prot.variable - (u8 *) mgmt;
	if (mgmt->u.action.u.self_prot.action_code ==
						WLAN_SP_MESH_PEERING_CONFIRM) {
=======
	baseaddr = mgmt->u.action.u.plink_action.variable;
	baselen = (u8 *) mgmt->u.action.u.plink_action.variable - (u8 *) mgmt;
	if (mgmt->u.action.u.plink_action.action_code == PLINK_CONFIRM) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		baseaddr += 4;
		baselen += 4;
	}
	ieee802_11_parse_elems(baseaddr, len - baselen, &elems);
<<<<<<< HEAD
	if (!elems.peering) {
=======
	if (!elems.peer_link) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		mpl_dbg("Mesh plink: missing necessary peer link ie\n");
		return;
	}
	if (elems.rsn_len &&
			sdata->u.mesh.security == IEEE80211_MESH_SEC_NONE) {
		mpl_dbg("Mesh plink: can't establish link with secure peer\n");
		return;
	}

<<<<<<< HEAD
	ftype = mgmt->u.action.u.self_prot.action_code;
	ie_len = elems.peering_len;
	if ((ftype == WLAN_SP_MESH_PEERING_OPEN && ie_len != 4) ||
	    (ftype == WLAN_SP_MESH_PEERING_CONFIRM && ie_len != 6) ||
	    (ftype == WLAN_SP_MESH_PEERING_CLOSE && ie_len != 6
							&& ie_len != 8)) {
=======
	ftype = mgmt->u.action.u.plink_action.action_code;
	ie_len = elems.peer_link_len;
	if ((ftype == PLINK_OPEN && ie_len != 6) ||
	    (ftype == PLINK_CONFIRM && ie_len != 8) ||
	    (ftype == PLINK_CLOSE && ie_len != 8 && ie_len != 10)) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		mpl_dbg("Mesh plink: incorrect plink ie length %d %d\n",
		    ftype, ie_len);
		return;
	}

<<<<<<< HEAD
	if (ftype != WLAN_SP_MESH_PEERING_CLOSE &&
				(!elems.mesh_id || !elems.mesh_config)) {
=======
	if (ftype != PLINK_CLOSE && (!elems.mesh_id || !elems.mesh_config)) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		mpl_dbg("Mesh plink: missing necessary ie\n");
		return;
	}
	/* Note the lines below are correct, the llid in the frame is the plid
	 * from the point of view of this host.
	 */
<<<<<<< HEAD
	memcpy(&plid, PLINK_GET_LLID(elems.peering), 2);
	if (ftype == WLAN_SP_MESH_PEERING_CONFIRM ||
	    (ftype == WLAN_SP_MESH_PEERING_CLOSE && ie_len == 8))
		memcpy(&llid, PLINK_GET_PLID(elems.peering), 2);
=======
	memcpy(&plid, PLINK_GET_LLID(elems.peer_link), 2);
	if (ftype == PLINK_CONFIRM || (ftype == PLINK_CLOSE && ie_len == 10))
		memcpy(&llid, PLINK_GET_PLID(elems.peer_link), 2);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	rcu_read_lock();

	sta = sta_info_get(sdata, mgmt->sa);
<<<<<<< HEAD
	if (!sta && ftype != WLAN_SP_MESH_PEERING_OPEN) {
=======
	if (!sta && ftype != PLINK_OPEN) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		mpl_dbg("Mesh plink: cls or cnf from unknown peer\n");
		rcu_read_unlock();
		return;
	}

<<<<<<< HEAD
	if (ftype == WLAN_SP_MESH_PEERING_OPEN &&
	    !rssi_threshold_check(sta, sdata)) {
		mpl_dbg("Mesh plink: %pM does not meet rssi threshold\n",
			mgmt->sa);
		rcu_read_unlock();
		return;
	}

	if (sta && !test_sta_flag(sta, WLAN_STA_AUTH)) {
=======
	if (sta && !test_sta_flags(sta, WLAN_STA_AUTH)) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		mpl_dbg("Mesh plink: Action frame from non-authed peer\n");
		rcu_read_unlock();
		return;
	}

	if (sta && sta->plink_state == NL80211_PLINK_BLOCKED) {
		rcu_read_unlock();
		return;
	}

	/* Now we will figure out the appropriate event... */
	event = PLINK_UNDEFINED;
<<<<<<< HEAD
	if (ftype != WLAN_SP_MESH_PEERING_CLOSE &&
	    (!mesh_matches_local(&elems, sdata))) {
		matches_local = false;
		switch (ftype) {
		case WLAN_SP_MESH_PEERING_OPEN:
			event = OPN_RJCT;
			break;
		case WLAN_SP_MESH_PEERING_CONFIRM:
			event = CNF_RJCT;
			break;
		default:
=======
	if (ftype != PLINK_CLOSE && (!mesh_matches_local(&elems, sdata))) {
		matches_local = false;
		switch (ftype) {
		case PLINK_OPEN:
			event = OPN_RJCT;
			break;
		case PLINK_CONFIRM:
			event = CNF_RJCT;
			break;
		case PLINK_CLOSE:
			/* avoid warning */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		}
	}

	if (!sta && !matches_local) {
		rcu_read_unlock();
<<<<<<< HEAD
		reason = cpu_to_le16(WLAN_REASON_MESH_CONFIG);
		llid = 0;
		mesh_plink_frame_tx(sdata, WLAN_SP_MESH_PEERING_CLOSE,
				    mgmt->sa, llid, plid, reason);
		return;
	} else if (!sta) {
		/* ftype == WLAN_SP_MESH_PEERING_OPEN */
=======
		reason = cpu_to_le16(MESH_CAPABILITY_POLICY_VIOLATION);
		llid = 0;
		mesh_plink_frame_tx(sdata, PLINK_CLOSE, mgmt->sa, llid,
				    plid, reason);
		return;
	} else if (!sta) {
		/* ftype == PLINK_OPEN */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		u32 rates;

		rcu_read_unlock();

		if (!mesh_plink_free_count(sdata)) {
			mpl_dbg("Mesh plink error: no more free plinks\n");
			return;
		}

		rates = ieee80211_sta_get_rates(local, &elems, rx_status->band);
<<<<<<< HEAD
		sta = mesh_plink_alloc(sdata, mgmt->sa, rates, &elems);
=======
		sta = mesh_plink_alloc(sdata, mgmt->sa, rates);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		if (!sta) {
			mpl_dbg("Mesh plink error: plink table full\n");
			return;
		}
		if (sta_info_insert_rcu(sta)) {
			rcu_read_unlock();
			return;
		}
		event = OPN_ACPT;
		spin_lock_bh(&sta->lock);
	} else if (matches_local) {
		spin_lock_bh(&sta->lock);
		switch (ftype) {
<<<<<<< HEAD
		case WLAN_SP_MESH_PEERING_OPEN:
=======
		case PLINK_OPEN:
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			if (!mesh_plink_free_count(sdata) ||
			    (sta->plid && sta->plid != plid))
				event = OPN_IGNR;
			else
				event = OPN_ACPT;
			break;
<<<<<<< HEAD
		case WLAN_SP_MESH_PEERING_CONFIRM:
=======
		case PLINK_CONFIRM:
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			if (!mesh_plink_free_count(sdata) ||
			    (sta->llid != llid || sta->plid != plid))
				event = CNF_IGNR;
			else
				event = CNF_ACPT;
			break;
<<<<<<< HEAD
		case WLAN_SP_MESH_PEERING_CLOSE:
=======
		case PLINK_CLOSE:
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			if (sta->plink_state == NL80211_PLINK_ESTAB)
				/* Do not check for llid or plid. This does not
				 * follow the standard but since multiple plinks
				 * per sta are not supported, it is necessary in
				 * order to avoid a livelock when MP A sees an
				 * establish peer link to MP B but MP B does not
				 * see it. This can be caused by a timeout in
				 * B's peer link establishment or B beign
				 * restarted.
				 */
				event = CLS_ACPT;
			else if (sta->plid != plid)
				event = CLS_IGNR;
			else if (ie_len == 7 && sta->llid != llid)
				event = CLS_IGNR;
			else
				event = CLS_ACPT;
			break;
		default:
			mpl_dbg("Mesh plink: unknown frame subtype\n");
			spin_unlock_bh(&sta->lock);
			rcu_read_unlock();
			return;
		}
	} else {
		spin_lock_bh(&sta->lock);
	}

	mpl_dbg("Mesh plink (peer, state, llid, plid, event): %pM %s %d %d %d\n",
		mgmt->sa, mplstates[sta->plink_state],
		le16_to_cpu(sta->llid), le16_to_cpu(sta->plid),
		event);
	reason = 0;
	switch (sta->plink_state) {
		/* spin_unlock as soon as state is updated at each case */
	case NL80211_PLINK_LISTEN:
		switch (event) {
		case CLS_ACPT:
			mesh_plink_fsm_restart(sta);
			spin_unlock_bh(&sta->lock);
			break;
		case OPN_ACPT:
			sta->plink_state = NL80211_PLINK_OPN_RCVD;
			sta->plid = plid;
			get_random_bytes(&llid, 2);
			sta->llid = llid;
			mesh_plink_timer_set(sta, dot11MeshRetryTimeout(sdata));
			spin_unlock_bh(&sta->lock);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata,
					    WLAN_SP_MESH_PEERING_OPEN,
					    sta->sta.addr, llid, 0, 0);
			mesh_plink_frame_tx(sdata,
					    WLAN_SP_MESH_PEERING_CONFIRM,
					    sta->sta.addr, llid, plid, 0);
=======
			mesh_plink_frame_tx(sdata, PLINK_OPEN, sta->sta.addr, llid,
					    0, 0);
			mesh_plink_frame_tx(sdata, PLINK_CONFIRM, sta->sta.addr,
					    llid, plid, 0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		default:
			spin_unlock_bh(&sta->lock);
			break;
		}
		break;

	case NL80211_PLINK_OPN_SNT:
		switch (event) {
		case OPN_RJCT:
		case CNF_RJCT:
<<<<<<< HEAD
			reason = cpu_to_le16(WLAN_REASON_MESH_CONFIG);
		case CLS_ACPT:
			if (!reason)
				reason = cpu_to_le16(WLAN_REASON_MESH_CLOSE);
=======
			reason = cpu_to_le16(MESH_CAPABILITY_POLICY_VIOLATION);
		case CLS_ACPT:
			if (!reason)
				reason = cpu_to_le16(MESH_CLOSE_RCVD);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			sta->reason = reason;
			sta->plink_state = NL80211_PLINK_HOLDING;
			if (!mod_plink_timer(sta,
					     dot11MeshHoldingTimeout(sdata)))
				sta->ignore_plink_timer = true;

			llid = sta->llid;
			spin_unlock_bh(&sta->lock);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata,
					    WLAN_SP_MESH_PEERING_CLOSE,
					    sta->sta.addr, llid, plid, reason);
=======
			mesh_plink_frame_tx(sdata, PLINK_CLOSE, sta->sta.addr, llid,
					    plid, reason);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		case OPN_ACPT:
			/* retry timer is left untouched */
			sta->plink_state = NL80211_PLINK_OPN_RCVD;
			sta->plid = plid;
			llid = sta->llid;
			spin_unlock_bh(&sta->lock);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata,
					    WLAN_SP_MESH_PEERING_CONFIRM,
					    sta->sta.addr, llid, plid, 0);
=======
			mesh_plink_frame_tx(sdata, PLINK_CONFIRM, sta->sta.addr, llid,
					    plid, 0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		case CNF_ACPT:
			sta->plink_state = NL80211_PLINK_CNF_RCVD;
			if (!mod_plink_timer(sta,
					     dot11MeshConfirmTimeout(sdata)))
				sta->ignore_plink_timer = true;

			spin_unlock_bh(&sta->lock);
			break;
		default:
			spin_unlock_bh(&sta->lock);
			break;
		}
		break;

	case NL80211_PLINK_OPN_RCVD:
		switch (event) {
		case OPN_RJCT:
		case CNF_RJCT:
<<<<<<< HEAD
			reason = cpu_to_le16(WLAN_REASON_MESH_CONFIG);
		case CLS_ACPT:
			if (!reason)
				reason = cpu_to_le16(WLAN_REASON_MESH_CLOSE);
=======
			reason = cpu_to_le16(MESH_CAPABILITY_POLICY_VIOLATION);
		case CLS_ACPT:
			if (!reason)
				reason = cpu_to_le16(MESH_CLOSE_RCVD);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			sta->reason = reason;
			sta->plink_state = NL80211_PLINK_HOLDING;
			if (!mod_plink_timer(sta,
					     dot11MeshHoldingTimeout(sdata)))
				sta->ignore_plink_timer = true;

			llid = sta->llid;
			spin_unlock_bh(&sta->lock);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata, WLAN_SP_MESH_PEERING_CLOSE,
					    sta->sta.addr, llid, plid, reason);
=======
			mesh_plink_frame_tx(sdata, PLINK_CLOSE, sta->sta.addr, llid,
					    plid, reason);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		case OPN_ACPT:
			llid = sta->llid;
			spin_unlock_bh(&sta->lock);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata,
					    WLAN_SP_MESH_PEERING_CONFIRM,
					    sta->sta.addr, llid, plid, 0);
=======
			mesh_plink_frame_tx(sdata, PLINK_CONFIRM, sta->sta.addr, llid,
					    plid, 0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		case CNF_ACPT:
			del_timer(&sta->plink_timer);
			sta->plink_state = NL80211_PLINK_ESTAB;
			spin_unlock_bh(&sta->lock);
			mesh_plink_inc_estab_count(sdata);
			ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BEACON);
			mpl_dbg("Mesh plink with %pM ESTABLISHED\n",
				sta->sta.addr);
			break;
		default:
			spin_unlock_bh(&sta->lock);
			break;
		}
		break;

	case NL80211_PLINK_CNF_RCVD:
		switch (event) {
		case OPN_RJCT:
		case CNF_RJCT:
<<<<<<< HEAD
			reason = cpu_to_le16(WLAN_REASON_MESH_CONFIG);
		case CLS_ACPT:
			if (!reason)
				reason = cpu_to_le16(WLAN_REASON_MESH_CLOSE);
=======
			reason = cpu_to_le16(MESH_CAPABILITY_POLICY_VIOLATION);
		case CLS_ACPT:
			if (!reason)
				reason = cpu_to_le16(MESH_CLOSE_RCVD);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			sta->reason = reason;
			sta->plink_state = NL80211_PLINK_HOLDING;
			if (!mod_plink_timer(sta,
					     dot11MeshHoldingTimeout(sdata)))
				sta->ignore_plink_timer = true;

			llid = sta->llid;
			spin_unlock_bh(&sta->lock);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata,
					    WLAN_SP_MESH_PEERING_CLOSE,
					    sta->sta.addr, llid, plid, reason);
=======
			mesh_plink_frame_tx(sdata, PLINK_CLOSE, sta->sta.addr, llid,
					    plid, reason);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		case OPN_ACPT:
			del_timer(&sta->plink_timer);
			sta->plink_state = NL80211_PLINK_ESTAB;
			spin_unlock_bh(&sta->lock);
			mesh_plink_inc_estab_count(sdata);
			ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BEACON);
			mpl_dbg("Mesh plink with %pM ESTABLISHED\n",
				sta->sta.addr);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata,
					    WLAN_SP_MESH_PEERING_CONFIRM,
					    sta->sta.addr, llid, plid, 0);
=======
			mesh_plink_frame_tx(sdata, PLINK_CONFIRM, sta->sta.addr, llid,
					    plid, 0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		default:
			spin_unlock_bh(&sta->lock);
			break;
		}
		break;

	case NL80211_PLINK_ESTAB:
		switch (event) {
		case CLS_ACPT:
<<<<<<< HEAD
			reason = cpu_to_le16(WLAN_REASON_MESH_CLOSE);
=======
			reason = cpu_to_le16(MESH_CLOSE_RCVD);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			sta->reason = reason;
			deactivated = __mesh_plink_deactivate(sta);
			sta->plink_state = NL80211_PLINK_HOLDING;
			llid = sta->llid;
			mod_plink_timer(sta, dot11MeshHoldingTimeout(sdata));
			spin_unlock_bh(&sta->lock);
			if (deactivated)
				ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BEACON);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata, WLAN_SP_MESH_PEERING_CLOSE,
					    sta->sta.addr, llid, plid, reason);
=======
			mesh_plink_frame_tx(sdata, PLINK_CLOSE, sta->sta.addr, llid,
					    plid, reason);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		case OPN_ACPT:
			llid = sta->llid;
			spin_unlock_bh(&sta->lock);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata,
					    WLAN_SP_MESH_PEERING_CONFIRM,
					    sta->sta.addr, llid, plid, 0);
=======
			mesh_plink_frame_tx(sdata, PLINK_CONFIRM, sta->sta.addr, llid,
					    plid, 0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		default:
			spin_unlock_bh(&sta->lock);
			break;
		}
		break;
	case NL80211_PLINK_HOLDING:
		switch (event) {
		case CLS_ACPT:
			if (del_timer(&sta->plink_timer))
				sta->ignore_plink_timer = 1;
			mesh_plink_fsm_restart(sta);
			spin_unlock_bh(&sta->lock);
			break;
		case OPN_ACPT:
		case CNF_ACPT:
		case OPN_RJCT:
		case CNF_RJCT:
			llid = sta->llid;
			reason = sta->reason;
			spin_unlock_bh(&sta->lock);
<<<<<<< HEAD
			mesh_plink_frame_tx(sdata, WLAN_SP_MESH_PEERING_CLOSE,
					    sta->sta.addr, llid, plid, reason);
=======
			mesh_plink_frame_tx(sdata, PLINK_CLOSE, sta->sta.addr,
					    llid, plid, reason);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
			break;
		default:
			spin_unlock_bh(&sta->lock);
		}
		break;
	default:
		/* should not get here, PLINK_BLOCKED is dealt with at the
		 * beginning of the function
		 */
		spin_unlock_bh(&sta->lock);
		break;
	}

	rcu_read_unlock();
}
