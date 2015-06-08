/******************************************************************************
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright(c) 2009-2012  Realtek Corporation.
=======
 * Copyright(c) 2009-2010  Realtek Corporation.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Copyright(c) 2009-2010  Realtek Corporation.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 * The full GNU General Public License is included in this distribution in the
 * file called LICENSE.
 *
 * Contact Information:
 * wlanfae <wlanfae@realtek.com>
 * Realtek Corporation, No. 2, Innovation Road II, Hsinchu Science Park,
 * Hsinchu 300, Taiwan.
 *
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 *****************************************************************************/

#include "wifi.h"
#include "core.h"
#include "cam.h"
#include "base.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "pci.h"
#include "ps.h"

#include <linux/export.h>

void rtl_fw_cb(const struct firmware *firmware, void *context)
{
	struct ieee80211_hw *hw = context;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	int err;

	RT_TRACE(rtlpriv, COMP_ERR, DBG_LOUD,
			 "Firmware callback routine entered!\n");
	complete(&rtlpriv->firmware_loading_complete);
	if (!firmware) {
		pr_err("Firmware %s not available\n", rtlpriv->cfg->fw_name);
		rtlpriv->max_fw_size = 0;
		return;
	}
	if (firmware->size > rtlpriv->max_fw_size) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 "Firmware is too big!\n");
		release_firmware(firmware);
		return;
	}
	memcpy(rtlpriv->rtlhal.pfirmware, firmware->data, firmware->size);
	rtlpriv->rtlhal.fwsize = firmware->size;
	release_firmware(firmware);

	err = ieee80211_register_hw(hw);
	if (err) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 "Can't register mac80211 hw\n");
		return;
	} else {
		rtlpriv->mac80211.mac80211_registered = 1;
	}
	set_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status);

	/*init rfkill */
	rtl_init_rfkill(hw);
}
EXPORT_SYMBOL(rtl_fw_cb);

=======
#include "ps.h"

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include "ps.h"

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*mutex for start & stop is must here. */
static int rtl_op_start(struct ieee80211_hw *hw)
{
	int err;
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));

	if (!is_hal_stop(rtlhal))
		return 0;
	if (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		return 0;
	mutex_lock(&rtlpriv->locks.conf_mutex);
	err = rtlpriv->intf_ops->adapter_start(hw);
	if (!err)
		rtl_watch_dog_timer_callback((unsigned long)hw);
	mutex_unlock(&rtlpriv->locks.conf_mutex);
	return err;
}

static void rtl_op_stop(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));

	if (is_hal_stop(rtlhal))
		return;

	if (unlikely(ppsc->rfpwr_state == ERFOFF)) {
		rtl_ips_nic_on(hw);
		mdelay(1);
	}

	mutex_lock(&rtlpriv->locks.conf_mutex);

	mac->link_state = MAC80211_NOLINK;
	memset(mac->bssid, 0, 6);
	mac->vendor = PEER_UNKNOWN;

	/*reset sec info */
	rtl_cam_reset_sec_info(hw);

	rtl_deinit_deferred_work(hw);
	rtlpriv->intf_ops->adapter_stop(hw);

	mutex_unlock(&rtlpriv->locks.conf_mutex);
}

static void rtl_op_tx(struct ieee80211_hw *hw, struct sk_buff *skb)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct rtl_tcb_desc tcb_desc;
	memset(&tcb_desc, 0, sizeof(struct rtl_tcb_desc));

	if (unlikely(is_hal_stop(rtlhal) || ppsc->rfpwr_state != ERFON))
		goto err_free;

	if (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		goto err_free;

	if (!rtlpriv->intf_ops->waitq_insert(hw, skb))
		rtlpriv->intf_ops->adapter_tx(hw, skb, &tcb_desc);

	return;

err_free:
	dev_kfree_skb_any(skb);
}

static int rtl_op_add_interface(struct ieee80211_hw *hw,
		struct ieee80211_vif *vif)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	int err = 0;

<<<<<<< HEAD
<<<<<<< HEAD
	vif->driver_flags |= IEEE80211_VIF_BEACON_FILTER;

	if (mac->vif) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "vif has been set!! mac->vif = 0x%p\n", mac->vif);
=======
	if (mac->vif) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 ("vif has been set!! mac->vif = 0x%p\n", mac->vif));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (mac->vif) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 ("vif has been set!! mac->vif = 0x%p\n", mac->vif));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EOPNOTSUPP;
	}

	rtl_ips_nic_on(hw);

	mutex_lock(&rtlpriv->locks.conf_mutex);
	switch (vif->type) {
	case NL80211_IFTYPE_STATION:
		if (mac->beacon_enabled == 1) {
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
				 "NL80211_IFTYPE_STATION\n");
=======
				 ("NL80211_IFTYPE_STATION\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("NL80211_IFTYPE_STATION\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			mac->beacon_enabled = 0;
			rtlpriv->cfg->ops->update_interrupt_mask(hw, 0,
					rtlpriv->cfg->maps
					[RTL_IBSS_INT_MASKS]);
		}
		break;
	case NL80211_IFTYPE_ADHOC:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "NL80211_IFTYPE_ADHOC\n");
=======
			 ("NL80211_IFTYPE_ADHOC\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("NL80211_IFTYPE_ADHOC\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		mac->link_state = MAC80211_LINKED;
		rtlpriv->cfg->ops->set_bcn_reg(hw);
		if (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
			mac->basic_rates = 0xfff;
		else
			mac->basic_rates = 0xff0;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
				(u8 *) (&mac->basic_rates));

		break;
	case NL80211_IFTYPE_AP:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "NL80211_IFTYPE_AP\n");
=======
			 ("NL80211_IFTYPE_AP\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("NL80211_IFTYPE_AP\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		mac->link_state = MAC80211_LINKED;
		rtlpriv->cfg->ops->set_bcn_reg(hw);
		if (rtlpriv->rtlhal.current_bandtype == BAND_ON_2_4G)
			mac->basic_rates = 0xfff;
		else
			mac->basic_rates = 0xff0;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
				(u8 *) (&mac->basic_rates));
		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
<<<<<<< HEAD
<<<<<<< HEAD
			 "operation mode %d is not supported!\n", vif->type);
=======
			 ("operation mode %d is not support!\n", vif->type));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("operation mode %d is not support!\n", vif->type));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		err = -EOPNOTSUPP;
		goto out;
	}

	mac->vif = vif;
	mac->opmode = vif->type;
	rtlpriv->cfg->ops->set_network_type(hw, vif->type);
	memcpy(mac->mac_addr, vif->addr, ETH_ALEN);
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ETHER_ADDR, mac->mac_addr);

out:
	mutex_unlock(&rtlpriv->locks.conf_mutex);
	return err;
}

static void rtl_op_remove_interface(struct ieee80211_hw *hw,
		struct ieee80211_vif *vif)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	mutex_lock(&rtlpriv->locks.conf_mutex);

	/* Free beacon resources */
	if ((mac->opmode == NL80211_IFTYPE_AP) ||
	    (mac->opmode == NL80211_IFTYPE_ADHOC) ||
	    (mac->opmode == NL80211_IFTYPE_MESH_POINT)) {
		if (mac->beacon_enabled == 1) {
			mac->beacon_enabled = 0;
			rtlpriv->cfg->ops->update_interrupt_mask(hw, 0,
					rtlpriv->cfg->maps
					[RTL_IBSS_INT_MASKS]);
		}
	}

	/*
	 *Note: We assume NL80211_IFTYPE_UNSPECIFIED as
	 *NO LINK for our hardware.
	 */
	mac->vif = NULL;
	mac->link_state = MAC80211_NOLINK;
	memset(mac->bssid, 0, 6);
	mac->vendor = PEER_UNKNOWN;
	mac->opmode = NL80211_IFTYPE_UNSPECIFIED;
	rtlpriv->cfg->ops->set_network_type(hw, mac->opmode);
	mutex_unlock(&rtlpriv->locks.conf_mutex);
}

static int rtl_op_config(struct ieee80211_hw *hw, u32 changed)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct ieee80211_conf *conf = &hw->conf;

	mutex_lock(&rtlpriv->locks.conf_mutex);
	if (changed & IEEE80211_CONF_CHANGE_LISTEN_INTERVAL) {	/*BIT(2)*/
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "IEEE80211_CONF_CHANGE_LISTEN_INTERVAL\n");
=======
			 ("IEEE80211_CONF_CHANGE_LISTEN_INTERVAL\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("IEEE80211_CONF_CHANGE_LISTEN_INTERVAL\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	/*For IPS */
	if (changed & IEEE80211_CONF_CHANGE_IDLE) {
		if (hw->conf.flags & IEEE80211_CONF_IDLE)
			rtl_ips_nic_off(hw);
		else
			rtl_ips_nic_on(hw);
	} else {
		/*
		 *although rfoff may not cause by ips, but we will
		 *check the reason in set_rf_power_state function
		 */
		if (unlikely(ppsc->rfpwr_state == ERFOFF))
			rtl_ips_nic_on(hw);
	}

	/*For LPS */
	if (changed & IEEE80211_CONF_CHANGE_PS) {
		cancel_delayed_work(&rtlpriv->works.ps_work);
		cancel_delayed_work(&rtlpriv->works.ps_rfon_wq);
		if (conf->flags & IEEE80211_CONF_PS) {
			rtlpriv->psc.sw_ps_enabled = true;
			/* sleep here is must, or we may recv the beacon and
			 * cause mac80211 into wrong ps state, this will cause
			 * power save nullfunc send fail, and further cause
			 * pkt loss, So sleep must quickly but not immediatly
			 * because that will cause nullfunc send by mac80211
			 * fail, and cause pkt loss, we have tested that 5mA
			 * is worked very well */
			if (!rtlpriv->psc.multi_buffered)
				queue_delayed_work(rtlpriv->works.rtl_wq,
						&rtlpriv->works.ps_work,
						MSECS(5));
		} else {
			rtl_swlps_rf_awake(hw);
			rtlpriv->psc.sw_ps_enabled = false;
		}
	}

	if (changed & IEEE80211_CONF_CHANGE_RETRY_LIMITS) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "IEEE80211_CONF_CHANGE_RETRY_LIMITS %x\n",
			 hw->conf.long_frame_max_tx_count);
=======
			 ("IEEE80211_CONF_CHANGE_RETRY_LIMITS %x\n",
			  hw->conf.long_frame_max_tx_count));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("IEEE80211_CONF_CHANGE_RETRY_LIMITS %x\n",
			  hw->conf.long_frame_max_tx_count));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		mac->retry_long = hw->conf.long_frame_max_tx_count;
		mac->retry_short = hw->conf.long_frame_max_tx_count;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_RETRY_LIMIT,
					      (u8 *) (&hw->conf.
						      long_frame_max_tx_count));
	}

	if (changed & IEEE80211_CONF_CHANGE_CHANNEL) {
		struct ieee80211_channel *channel = hw->conf.channel;
		u8 wide_chan = (u8) channel->hw_value;

		/*
		 *because we should back channel to
		 *current_network.chan in in scanning,
		 *So if set_chan == current_network.chan
		 *we should set it.
		 *because mac80211 tell us wrong bw40
		 *info for cisco1253 bw20, so we modify
		 *it here based on UPPER & LOWER
		 */
		switch (hw->conf.channel_type) {
		case NL80211_CHAN_HT20:
		case NL80211_CHAN_NO_HT:
			/* SC */
			mac->cur_40_prime_sc =
				PRIME_CHNL_OFFSET_DONT_CARE;
			rtlphy->current_chan_bw = HT_CHANNEL_WIDTH_20;
			mac->bw_40 = false;
			break;
		case NL80211_CHAN_HT40MINUS:
			/* SC */
			mac->cur_40_prime_sc = PRIME_CHNL_OFFSET_UPPER;
			rtlphy->current_chan_bw =
				HT_CHANNEL_WIDTH_20_40;
			mac->bw_40 = true;

			/*wide channel */
			wide_chan -= 2;

			break;
		case NL80211_CHAN_HT40PLUS:
			/* SC */
			mac->cur_40_prime_sc = PRIME_CHNL_OFFSET_LOWER;
			rtlphy->current_chan_bw =
				HT_CHANNEL_WIDTH_20_40;
			mac->bw_40 = true;

			/*wide channel */
			wide_chan += 2;

			break;
		default:
			mac->bw_40 = false;
			RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
<<<<<<< HEAD
<<<<<<< HEAD
				 "switch case not processed\n");
=======
					("switch case not processed\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
					("switch case not processed\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;
		}

		if (wide_chan <= 0)
			wide_chan = 1;

		/* In scanning, before we go offchannel we may send a ps=1 null
		 * to AP, and then we may send a ps = 0 null to AP quickly, but
		 * first null may have caused AP to put lots of packet to hw tx
		 * buffer. These packets must be tx'd before we go off channel
		 * so we must delay more time to let AP flush these packets
		 * before going offchannel, or dis-association or delete BA will
		 * happen by AP
		 */
<<<<<<< HEAD
<<<<<<< HEAD
		if (rtlpriv->mac80211.offchan_delay) {
			rtlpriv->mac80211.offchan_delay = false;
=======
		if (rtlpriv->mac80211.offchan_deley) {
			rtlpriv->mac80211.offchan_deley = false;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if (rtlpriv->mac80211.offchan_deley) {
			rtlpriv->mac80211.offchan_deley = false;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			mdelay(50);
		}
		rtlphy->current_channel = wide_chan;

		rtlpriv->cfg->ops->switch_channel(hw);
		rtlpriv->cfg->ops->set_channel_access(hw);
		rtlpriv->cfg->ops->set_bw_mode(hw,
					       hw->conf.channel_type);
	}

	mutex_unlock(&rtlpriv->locks.conf_mutex);

	return 0;
}

static void rtl_op_configure_filter(struct ieee80211_hw *hw,
			     unsigned int changed_flags,
			     unsigned int *new_flags, u64 multicast)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	*new_flags &= RTL_SUPPORTED_FILTERS;
	if (!changed_flags)
		return;

	/*TODO: we disable broadcase now, so enable here */
	if (changed_flags & FIF_ALLMULTI) {
		if (*new_flags & FIF_ALLMULTI) {
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_AM] |
			    rtlpriv->cfg->maps[MAC_RCR_AB];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
				 "Enable receive multicast frame\n");
=======
				 ("Enable receive multicast frame.\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("Enable receive multicast frame.\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		} else {
			mac->rx_conf &= ~(rtlpriv->cfg->maps[MAC_RCR_AM] |
					  rtlpriv->cfg->maps[MAC_RCR_AB]);
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
				 "Disable receive multicast frame\n");
=======
				 ("Disable receive multicast frame.\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("Disable receive multicast frame.\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
	}

	if (changed_flags & FIF_FCSFAIL) {
		if (*new_flags & FIF_FCSFAIL) {
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_ACRC32];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
				 "Enable receive FCS error frame\n");
		} else {
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_ACRC32];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Disable receive FCS error frame\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				 ("Enable receive FCS error frame.\n"));
		} else {
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_ACRC32];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 ("Disable receive FCS error frame.\n"));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
	}

	/* if ssid not set to hw don't check bssid
	 * here just used for linked scanning, & linked
	 * and nolink check bssid is set in set network_type */
	if ((changed_flags & FIF_BCN_PRBRESP_PROMISC) &&
		(mac->link_state >= MAC80211_LINKED)) {
		if (mac->opmode != NL80211_IFTYPE_AP) {
			if (*new_flags & FIF_BCN_PRBRESP_PROMISC) {
				rtlpriv->cfg->ops->set_chk_bssid(hw, false);
			} else {
				rtlpriv->cfg->ops->set_chk_bssid(hw, true);
			}
		}
	}

	if (changed_flags & FIF_CONTROL) {
		if (*new_flags & FIF_CONTROL) {
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_ACF];

			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
				 "Enable receive control frame\n");
		} else {
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_ACF];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Disable receive control frame\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				 ("Enable receive control frame.\n"));
		} else {
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_ACF];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 ("Disable receive control frame.\n"));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
	}

	if (changed_flags & FIF_OTHER_BSS) {
		if (*new_flags & FIF_OTHER_BSS) {
			mac->rx_conf |= rtlpriv->cfg->maps[MAC_RCR_AAP];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
				 "Enable receive other BSS's frame\n");
		} else {
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_AAP];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 "Disable receive other BSS's frame\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				 ("Enable receive other BSS's frame.\n"));
		} else {
			mac->rx_conf &= ~rtlpriv->cfg->maps[MAC_RCR_AAP];
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
				 ("Disable receive other BSS's frame.\n"));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
	}
}
static int rtl_op_sta_add(struct ieee80211_hw *hw,
			 struct ieee80211_vif *vif,
			 struct ieee80211_sta *sta)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	struct rtl_sta_info *sta_entry;

	if (sta) {
		sta_entry = (struct rtl_sta_info *) sta->drv_priv;
		if (rtlhal->current_bandtype == BAND_ON_2_4G) {
			sta_entry->wireless_mode = WIRELESS_MODE_G;
			if (sta->supp_rates[0] <= 0xf)
				sta_entry->wireless_mode = WIRELESS_MODE_B;
<<<<<<< HEAD
<<<<<<< HEAD
			if (sta->ht_cap.ht_supported)
				sta_entry->wireless_mode = WIRELESS_MODE_N_24G;
		} else if (rtlhal->current_bandtype == BAND_ON_5G) {
			sta_entry->wireless_mode = WIRELESS_MODE_A;
			if (sta->ht_cap.ht_supported)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (sta->ht_cap.ht_supported == true)
				sta_entry->wireless_mode = WIRELESS_MODE_N_24G;
		} else if (rtlhal->current_bandtype == BAND_ON_5G) {
			sta_entry->wireless_mode = WIRELESS_MODE_A;
			if (sta->ht_cap.ht_supported == true)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				sta_entry->wireless_mode = WIRELESS_MODE_N_24G;
		}

		/* I found some times mac80211 give wrong supp_rates for adhoc*/
		if (rtlpriv->mac80211.opmode == NL80211_IFTYPE_ADHOC)
			sta_entry->wireless_mode = WIRELESS_MODE_G;

		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
			 "Add sta addr is %pM\n", sta->addr);
=======
			("Add sta addr is "MAC_FMT"\n", MAC_ARG(sta->addr)));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			("Add sta addr is "MAC_FMT"\n", MAC_ARG(sta->addr)));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		rtlpriv->cfg->ops->update_rate_tbl(hw, sta, 0);
	}
	return 0;
}
static int rtl_op_sta_remove(struct ieee80211_hw *hw,
				struct ieee80211_vif *vif,
				struct ieee80211_sta *sta)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_sta_info *sta_entry;
	if (sta) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
			 "Remove sta addr is %pM\n", sta->addr);
=======
			("Remove sta addr is "MAC_FMT"\n", MAC_ARG(sta->addr)));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			("Remove sta addr is "MAC_FMT"\n", MAC_ARG(sta->addr)));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		sta_entry = (struct rtl_sta_info *) sta->drv_priv;
		sta_entry->wireless_mode = 0;
		sta_entry->ratr_index = 0;
	}
	return 0;
}
static int _rtl_get_hal_qnum(u16 queue)
{
	int qnum;

	switch (queue) {
	case 0:
		qnum = AC3_VO;
		break;
	case 1:
		qnum = AC2_VI;
		break;
	case 2:
		qnum = AC0_BE;
		break;
	case 3:
		qnum = AC1_BK;
		break;
	default:
		qnum = AC0_BE;
		break;
	}
	return qnum;
}

/*
 *for mac80211 VO=0, VI=1, BE=2, BK=3
 *for rtl819x  BE=0, BK=1, VI=2, VO=3
 */
<<<<<<< HEAD
<<<<<<< HEAD
static int rtl_op_conf_tx(struct ieee80211_hw *hw,
		   struct ieee80211_vif *vif, u16 queue,
=======
static int rtl_op_conf_tx(struct ieee80211_hw *hw, u16 queue,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int rtl_op_conf_tx(struct ieee80211_hw *hw, u16 queue,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		   const struct ieee80211_tx_queue_params *param)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	int aci;

	if (queue >= AC_MAX) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
<<<<<<< HEAD
<<<<<<< HEAD
			 "queue number %d is incorrect!\n", queue);
=======
			 ("queue number %d is incorrect!\n", queue));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("queue number %d is incorrect!\n", queue));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	aci = _rtl_get_hal_qnum(queue);
	mac->ac[aci].aifs = param->aifs;
	mac->ac[aci].cw_min = cpu_to_le16(param->cw_min);
	mac->ac[aci].cw_max = cpu_to_le16(param->cw_max);
	mac->ac[aci].tx_op = cpu_to_le16(param->txop);
	memcpy(&mac->edca_param[aci], param, sizeof(*param));
	rtlpriv->cfg->ops->set_qos(hw, aci);
	return 0;
}

static void rtl_op_bss_info_changed(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif,
			     struct ieee80211_bss_conf *bss_conf, u32 changed)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_hal *rtlhal = rtl_hal(rtlpriv);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	struct ieee80211_sta *sta = NULL;

	mutex_lock(&rtlpriv->locks.conf_mutex);
	if ((vif->type == NL80211_IFTYPE_ADHOC) ||
	    (vif->type == NL80211_IFTYPE_AP) ||
	    (vif->type == NL80211_IFTYPE_MESH_POINT)) {
		if ((changed & BSS_CHANGED_BEACON) ||
		    (changed & BSS_CHANGED_BEACON_ENABLED &&
		     bss_conf->enable_beacon)) {
			if (mac->beacon_enabled == 0) {
				RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
					 "BSS_CHANGED_BEACON_ENABLED\n");
=======
					 ("BSS_CHANGED_BEACON_ENABLED\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
					 ("BSS_CHANGED_BEACON_ENABLED\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

				/*start hw beacon interrupt. */
				/*rtlpriv->cfg->ops->set_bcn_reg(hw); */
				mac->beacon_enabled = 1;
				rtlpriv->cfg->ops->update_interrupt_mask(hw,
						rtlpriv->cfg->maps
						[RTL_IBSS_INT_MASKS],
						0);

				if (rtlpriv->cfg->ops->linked_set_reg)
					rtlpriv->cfg->ops->linked_set_reg(hw);
			}
		}
		if ((changed & BSS_CHANGED_BEACON_ENABLED &&
			!bss_conf->enable_beacon)) {
			if (mac->beacon_enabled == 1) {
				RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
					 "ADHOC DISABLE BEACON\n");
=======
					 ("ADHOC DISABLE BEACON\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
					 ("ADHOC DISABLE BEACON\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

				mac->beacon_enabled = 0;
				rtlpriv->cfg->ops->update_interrupt_mask(hw, 0,
						rtlpriv->cfg->maps
						[RTL_IBSS_INT_MASKS]);
			}
		}
		if (changed & BSS_CHANGED_BEACON_INT) {
			RT_TRACE(rtlpriv, COMP_BEACON, DBG_TRACE,
<<<<<<< HEAD
<<<<<<< HEAD
				 "BSS_CHANGED_BEACON_INT\n");
=======
				 ("BSS_CHANGED_BEACON_INT\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("BSS_CHANGED_BEACON_INT\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			mac->beacon_interval = bss_conf->beacon_int;
			rtlpriv->cfg->ops->set_bcn_intv(hw);
		}
	}

	/*TODO: reference to enum ieee80211_bss_change */
	if (changed & BSS_CHANGED_ASSOC) {
		if (bss_conf->assoc) {
			/* we should reset all sec info & cam
			 * before set cam after linked, we should not
			 * reset in disassoc, that will cause tkip->wep
			 * fail because some flag will be wrong */
			/* reset sec info */
			rtl_cam_reset_sec_info(hw);
			/* reset cam to fix wep fail issue
			 * when change from wpa to wep */
			rtl_cam_reset_all_entry(hw);

			mac->link_state = MAC80211_LINKED;
			mac->cnt_after_linked = 0;
			mac->assoc_id = bss_conf->aid;
			memcpy(mac->bssid, bss_conf->bssid, 6);

			if (rtlpriv->cfg->ops->linked_set_reg)
				rtlpriv->cfg->ops->linked_set_reg(hw);
			if (mac->opmode == NL80211_IFTYPE_STATION && sta)
				rtlpriv->cfg->ops->update_rate_tbl(hw, sta, 0);
			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
				 "BSS_CHANGED_ASSOC\n");
=======
				 ("BSS_CHANGED_ASSOC\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("BSS_CHANGED_ASSOC\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		} else {
			if (mac->link_state == MAC80211_LINKED)
				rtl_lps_leave(hw);

			mac->link_state = MAC80211_NOLINK;
			memset(mac->bssid, 0, 6);

			/* reset sec info */
			rtl_cam_reset_sec_info(hw);

			rtl_cam_reset_all_entry(hw);
			mac->vendor = PEER_UNKNOWN;

			RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
				 "BSS_CHANGED_UN_ASSOC\n");
=======
				 ("BSS_CHANGED_UN_ASSOC\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("BSS_CHANGED_UN_ASSOC\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
	}

	if (changed & BSS_CHANGED_ERP_CTS_PROT) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
<<<<<<< HEAD
<<<<<<< HEAD
			 "BSS_CHANGED_ERP_CTS_PROT\n");
=======
			 ("BSS_CHANGED_ERP_CTS_PROT\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("BSS_CHANGED_ERP_CTS_PROT\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		mac->use_cts_protect = bss_conf->use_cts_prot;
	}

	if (changed & BSS_CHANGED_ERP_PREAMBLE) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "BSS_CHANGED_ERP_PREAMBLE use short preamble:%x\n",
			 bss_conf->use_short_preamble);
=======
			 ("BSS_CHANGED_ERP_PREAMBLE use short preamble:%x\n",
			  bss_conf->use_short_preamble));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("BSS_CHANGED_ERP_PREAMBLE use short preamble:%x\n",
			  bss_conf->use_short_preamble));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		mac->short_preamble = bss_conf->use_short_preamble;
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_ACK_PREAMBLE,
					      (u8 *) (&mac->short_preamble));
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
<<<<<<< HEAD
<<<<<<< HEAD
			 "BSS_CHANGED_ERP_SLOT\n");
=======
			 ("BSS_CHANGED_ERP_SLOT\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("BSS_CHANGED_ERP_SLOT\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		if (bss_conf->use_short_slot)
			mac->slot_time = RTL_SLOT_TIME_9;
		else
			mac->slot_time = RTL_SLOT_TIME_20;

		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SLOT_TIME,
					      (u8 *) (&mac->slot_time));
	}

	if (changed & BSS_CHANGED_HT) {
<<<<<<< HEAD
<<<<<<< HEAD
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE, "BSS_CHANGED_HT\n");
		rcu_read_lock();
		sta = get_sta(hw, vif, bss_conf->bssid);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 ("BSS_CHANGED_HT\n"));
		rcu_read_lock();
		sta = get_sta(hw, vif, (u8 *)bss_conf->bssid);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (sta) {
			if (sta->ht_cap.ampdu_density >
			    mac->current_ampdu_density)
				mac->current_ampdu_density =
				    sta->ht_cap.ampdu_density;
			if (sta->ht_cap.ampdu_factor <
			    mac->current_ampdu_factor)
				mac->current_ampdu_factor =
				    sta->ht_cap.ampdu_factor;
		}
		rcu_read_unlock();

		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_SHORTGI_DENSITY,
					      (u8 *) (&mac->max_mss_density));
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AMPDU_FACTOR,
					      &mac->current_ampdu_factor);
		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_AMPDU_MIN_SPACE,
					      &mac->current_ampdu_density);
	}

	if (changed & BSS_CHANGED_BSSID) {
		u32 basic_rates;

		rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BSSID,
					      (u8 *) bss_conf->bssid);

<<<<<<< HEAD
<<<<<<< HEAD
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG, "%pM\n",
			 bss_conf->bssid);
=======
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
			 (MAC_FMT "\n", MAC_ARG(bss_conf->bssid)));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_DMESG,
			 (MAC_FMT "\n", MAC_ARG(bss_conf->bssid)));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		mac->vendor = PEER_UNKNOWN;
		memcpy(mac->bssid, bss_conf->bssid, 6);
		rtlpriv->cfg->ops->set_network_type(hw, vif->type);

		rcu_read_lock();
<<<<<<< HEAD
<<<<<<< HEAD
		sta = get_sta(hw, vif, bss_conf->bssid);
=======
		sta = get_sta(hw, vif, (u8 *)bss_conf->bssid);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		sta = get_sta(hw, vif, (u8 *)bss_conf->bssid);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!sta) {
			rcu_read_unlock();
			goto out;
		}

		if (rtlhal->current_bandtype == BAND_ON_5G) {
			mac->mode = WIRELESS_MODE_A;
		} else {
			if (sta->supp_rates[0] <= 0xf)
				mac->mode = WIRELESS_MODE_B;
			else
				mac->mode = WIRELESS_MODE_G;
		}

		if (sta->ht_cap.ht_supported) {
			if (rtlhal->current_bandtype == BAND_ON_2_4G)
				mac->mode = WIRELESS_MODE_N_24G;
			else
				mac->mode = WIRELESS_MODE_N_5G;
		}

		/* just station need it, because ibss & ap mode will
		 * set in sta_add, and will be NULL here */
		if (mac->opmode == NL80211_IFTYPE_STATION) {
			struct rtl_sta_info *sta_entry;
			sta_entry = (struct rtl_sta_info *) sta->drv_priv;
			sta_entry->wireless_mode = mac->mode;
		}

		if (sta->ht_cap.ht_supported) {
			mac->ht_enable = true;

			/*
			 * for cisco 1252 bw20 it's wrong
			 * if (ht_cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40) {
			 *	mac->bw_40 = true;
			 * }
			 * */
		}

		if (changed & BSS_CHANGED_BASIC_RATES) {
			/* for 5G must << RATE_6M_INDEX=4,
			 * because 5G have no cck rate*/
			if (rtlhal->current_bandtype == BAND_ON_5G)
				basic_rates = sta->supp_rates[1] << 4;
			else
				basic_rates = sta->supp_rates[0];

			mac->basic_rates = basic_rates;
			rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_BASIC_RATE,
					(u8 *) (&basic_rates));
		}
		rcu_read_unlock();
	}

	/*
	 * For FW LPS:
	 * To tell firmware we have connected
	 * to an AP. For 92SE/CE power save v2.
	 */
	if (changed & BSS_CHANGED_ASSOC) {
		if (bss_conf->assoc) {
			if (ppsc->fwctrl_lps) {
				u8 mstatus = RT_MEDIA_CONNECT;
				rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_H2C_FW_JOINBSSRPT,
						      (u8 *) (&mstatus));
				ppsc->report_linked = true;
			}
		} else {
			if (ppsc->fwctrl_lps) {
				u8 mstatus = RT_MEDIA_DISCONNECT;
				rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_H2C_FW_JOINBSSRPT,
						      (u8 *)(&mstatus));
				ppsc->report_linked = false;
			}
		}
	}

out:
	mutex_unlock(&rtlpriv->locks.conf_mutex);
}

<<<<<<< HEAD
<<<<<<< HEAD
static u64 rtl_op_get_tsf(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
=======
static u64 rtl_op_get_tsf(struct ieee80211_hw *hw)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static u64 rtl_op_get_tsf(struct ieee80211_hw *hw)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u64 tsf;

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_CORRECT_TSF, (u8 *) (&tsf));
	return tsf;
}

<<<<<<< HEAD
<<<<<<< HEAD
static void rtl_op_set_tsf(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			   u64 tsf)
=======
static void rtl_op_set_tsf(struct ieee80211_hw *hw, u64 tsf)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static void rtl_op_set_tsf(struct ieee80211_hw *hw, u64 tsf)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 bibss = (mac->opmode == NL80211_IFTYPE_ADHOC) ? 1 : 0;

	mac->tsf = tsf;
	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_CORRECT_TSF, (u8 *) (&bibss));
}

<<<<<<< HEAD
<<<<<<< HEAD
static void rtl_op_reset_tsf(struct ieee80211_hw *hw,
			     struct ieee80211_vif *vif)
=======
static void rtl_op_reset_tsf(struct ieee80211_hw *hw)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static void rtl_op_reset_tsf(struct ieee80211_hw *hw)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	u8 tmp = 0;

	rtlpriv->cfg->ops->set_hw_reg(hw, HW_VAR_DUAL_TSF_RST, (u8 *) (&tmp));
}

static void rtl_op_sta_notify(struct ieee80211_hw *hw,
			      struct ieee80211_vif *vif,
			      enum sta_notify_cmd cmd,
			      struct ieee80211_sta *sta)
{
	switch (cmd) {
	case STA_NOTIFY_SLEEP:
		break;
	case STA_NOTIFY_AWAKE:
		break;
	default:
		break;
	}
}

static int rtl_op_ampdu_action(struct ieee80211_hw *hw,
			       struct ieee80211_vif *vif,
			       enum ieee80211_ampdu_mlme_action action,
			       struct ieee80211_sta *sta, u16 tid, u16 *ssn,
			       u8 buf_size)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	switch (action) {
	case IEEE80211_AMPDU_TX_START:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
<<<<<<< HEAD
<<<<<<< HEAD
			 "IEEE80211_AMPDU_TX_START: TID:%d\n", tid);
=======
			 ("IEEE80211_AMPDU_TX_START: TID:%d\n", tid));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("IEEE80211_AMPDU_TX_START: TID:%d\n", tid));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return rtl_tx_agg_start(hw, sta, tid, ssn);
		break;
	case IEEE80211_AMPDU_TX_STOP:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
<<<<<<< HEAD
<<<<<<< HEAD
			 "IEEE80211_AMPDU_TX_STOP: TID:%d\n", tid);
=======
			 ("IEEE80211_AMPDU_TX_STOP: TID:%d\n", tid));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("IEEE80211_AMPDU_TX_STOP: TID:%d\n", tid));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return rtl_tx_agg_stop(hw, sta, tid);
		break;
	case IEEE80211_AMPDU_TX_OPERATIONAL:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
<<<<<<< HEAD
<<<<<<< HEAD
			 "IEEE80211_AMPDU_TX_OPERATIONAL:TID:%d\n", tid);
=======
			 ("IEEE80211_AMPDU_TX_OPERATIONAL:TID:%d\n", tid));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("IEEE80211_AMPDU_TX_OPERATIONAL:TID:%d\n", tid));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		rtl_tx_agg_oper(hw, sta, tid);
		break;
	case IEEE80211_AMPDU_RX_START:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
<<<<<<< HEAD
<<<<<<< HEAD
			 "IEEE80211_AMPDU_RX_START:TID:%d\n", tid);
		break;
	case IEEE80211_AMPDU_RX_STOP:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 "IEEE80211_AMPDU_RX_STOP:TID:%d\n", tid);
		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 "IEEE80211_AMPDU_ERR!!!!:\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			 ("IEEE80211_AMPDU_RX_START:TID:%d\n", tid));
		break;
	case IEEE80211_AMPDU_RX_STOP:
		RT_TRACE(rtlpriv, COMP_MAC80211, DBG_TRACE,
			 ("IEEE80211_AMPDU_RX_STOP:TID:%d\n", tid));
		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 ("IEEE80211_AMPDU_ERR!!!!:\n"));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EOPNOTSUPP;
	}
	return 0;
}

static void rtl_op_sw_scan_start(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

	mac->act_scanning = true;

<<<<<<< HEAD
<<<<<<< HEAD
	RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD, "\n");
=======
	RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD, ("\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD, ("\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (mac->link_state == MAC80211_LINKED) {
		rtl_lps_leave(hw);
		mac->link_state = MAC80211_LINKED_SCANNING;
	} else {
		rtl_ips_nic_on(hw);
	}

	/* Dual mac */
	rtlpriv->rtlhal.load_imrandiqk_setting_for2g = false;

	rtlpriv->cfg->ops->led_control(hw, LED_CTL_SITE_SURVEY);
	rtlpriv->cfg->ops->scan_operation_backup(hw, SCAN_OPT_BACKUP);
}

static void rtl_op_sw_scan_complete(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));

<<<<<<< HEAD
<<<<<<< HEAD
	RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD, "\n");
=======
	RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD, ("\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	RT_TRACE(rtlpriv, COMP_MAC80211, DBG_LOUD, ("\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mac->act_scanning = false;
	/* Dual mac */
	rtlpriv->rtlhal.load_imrandiqk_setting_for2g = false;

	if (mac->link_state == MAC80211_LINKED_SCANNING) {
		mac->link_state = MAC80211_LINKED;
		if (mac->opmode == NL80211_IFTYPE_STATION) {
			/* fix fwlps issue */
			rtlpriv->cfg->ops->set_network_type(hw, mac->opmode);
		}
	}

	rtlpriv->cfg->ops->scan_operation_backup(hw, SCAN_OPT_RESTORE);
}

static int rtl_op_set_key(struct ieee80211_hw *hw, enum set_key_cmd cmd,
			  struct ieee80211_vif *vif, struct ieee80211_sta *sta,
			  struct ieee80211_key_conf *key)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 key_type = NO_ENCRYPTION;
	u8 key_idx;
	bool group_key = false;
	bool wep_only = false;
	int err = 0;
	u8 mac_addr[ETH_ALEN];
	u8 bcast_addr[ETH_ALEN] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
	u8 zero_addr[ETH_ALEN] = { 0 };

	if (rtlpriv->cfg->mod_params->sw_crypto || rtlpriv->sec.use_sw_sec) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
<<<<<<< HEAD
<<<<<<< HEAD
			 "not open hw encryption\n");
		return -ENOSPC;	/*User disabled HW-crypto */
	}
	RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
		 "%s hardware based encryption for keyidx: %d, mac: %pM\n",
		 cmd == SET_KEY ? "Using" : "Disabling", key->keyidx,
		 sta ? sta->addr : bcast_addr);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			 ("not open hw encryption\n"));
		return -ENOSPC;	/*User disabled HW-crypto */
	}
	RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
		 ("%s hardware based encryption for keyidx: %d, mac: %pM\n",
		  cmd == SET_KEY ? "Using" : "Disabling", key->keyidx,
		  sta ? sta->addr : bcast_addr));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	rtlpriv->sec.being_setkey = true;
	rtl_ips_nic_on(hw);
	mutex_lock(&rtlpriv->locks.conf_mutex);
	/* <1> get encryption alg */

	switch (key->cipher) {
	case WLAN_CIPHER_SUITE_WEP40:
		key_type = WEP40_ENCRYPTION;
<<<<<<< HEAD
<<<<<<< HEAD
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG, "alg:WEP40\n");
		break;
	case WLAN_CIPHER_SUITE_WEP104:
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG, "alg:WEP104\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG, ("alg:WEP40\n"));
		break;
	case WLAN_CIPHER_SUITE_WEP104:
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
			 ("alg:WEP104\n"));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		key_type = WEP104_ENCRYPTION;
		break;
	case WLAN_CIPHER_SUITE_TKIP:
		key_type = TKIP_ENCRYPTION;
<<<<<<< HEAD
<<<<<<< HEAD
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG, "alg:TKIP\n");
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		key_type = AESCCMP_ENCRYPTION;
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG, "alg:CCMP\n");
		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG, "alg_err:%x!!!!\n",
			 key->cipher);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG, ("alg:TKIP\n"));
		break;
	case WLAN_CIPHER_SUITE_CCMP:
		key_type = AESCCMP_ENCRYPTION;
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG, ("alg:CCMP\n"));
		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
			 ("alg_err:%x!!!!:\n", key->cipher));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto out_unlock;
	}
	if (key_type == WEP40_ENCRYPTION ||
			key_type == WEP104_ENCRYPTION ||
			mac->opmode == NL80211_IFTYPE_ADHOC)
		rtlpriv->sec.use_defaultkey = true;

	/* <2> get key_idx */
	key_idx = (u8) (key->keyidx);
	if (key_idx > 3)
		goto out_unlock;
	/* <3> if pairwise key enable_hw_sec */
	group_key = !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE);

	/* wep always be group key, but there are two conditions:
	 * 1) wep only: is just for wep enc, in this condition
	 * rtlpriv->sec.pairwise_enc_algorithm == NO_ENCRYPTION
	 * will be true & enable_hw_sec will be set when wep
	 * ke setting.
	 * 2) wep(group) + AES(pairwise): some AP like cisco
	 * may use it, in this condition enable_hw_sec will not
	 * be set when wep key setting */
	/* we must reset sec_info after lingked before set key,
	 * or some flag will be wrong*/
	if (mac->opmode == NL80211_IFTYPE_AP) {
		if (!group_key || key_type == WEP40_ENCRYPTION ||
			key_type == WEP104_ENCRYPTION) {
			if (group_key)
				wep_only = true;
			rtlpriv->cfg->ops->enable_hw_sec(hw);
		}
	} else {
		if ((!group_key) || (mac->opmode == NL80211_IFTYPE_ADHOC) ||
		     rtlpriv->sec.pairwise_enc_algorithm == NO_ENCRYPTION) {
			if (rtlpriv->sec.pairwise_enc_algorithm ==
			    NO_ENCRYPTION &&
			    (key_type == WEP40_ENCRYPTION ||
			    key_type == WEP104_ENCRYPTION))
				wep_only = true;
			rtlpriv->sec.pairwise_enc_algorithm = key_type;
			RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
				 "set enable_hw_sec, key_type:%x(OPEN:0 WEP40:1 TKIP:2 AES:4 WEP104:5)\n",
				 key_type);
=======
				("set enable_hw_sec, key_type:%x(OPEN:0 WEP40:1"
				" TKIP:2 AES:4 WEP104:5)\n", key_type));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				("set enable_hw_sec, key_type:%x(OPEN:0 WEP40:1"
				" TKIP:2 AES:4 WEP104:5)\n", key_type));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			rtlpriv->cfg->ops->enable_hw_sec(hw);
		}
	}
	/* <4> set key based on cmd */
	switch (cmd) {
	case SET_KEY:
		if (wep_only) {
			RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
				 "set WEP(group/pairwise) key\n");
=======
				 ("set WEP(group/pairwise) key\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("set WEP(group/pairwise) key\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			/* Pairwise key with an assigned MAC address. */
			rtlpriv->sec.pairwise_enc_algorithm = key_type;
			rtlpriv->sec.group_enc_algorithm = key_type;
			/*set local buf about wep key. */
			memcpy(rtlpriv->sec.key_buf[key_idx],
			       key->key, key->keylen);
			rtlpriv->sec.key_len[key_idx] = key->keylen;
			memcpy(mac_addr, zero_addr, ETH_ALEN);
		} else if (group_key) {	/* group key */
			RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
				 "set group key\n");
=======
				 ("set group key\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("set group key\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			/* group key */
			rtlpriv->sec.group_enc_algorithm = key_type;
			/*set local buf about group key. */
			memcpy(rtlpriv->sec.key_buf[key_idx],
			       key->key, key->keylen);
			rtlpriv->sec.key_len[key_idx] = key->keylen;
			memcpy(mac_addr, bcast_addr, ETH_ALEN);
		} else {	/* pairwise key */
			RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
				 "set pairwise key\n");
			if (!sta) {
				RT_ASSERT(false,
					  "pairwise key without mac_addr\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				 ("set pairwise key\n"));
			if (!sta) {
				RT_ASSERT(false, ("pairwise key withnot"
						  "mac_addr\n"));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

				err = -EOPNOTSUPP;
				goto out_unlock;
			}
			/* Pairwise key with an assigned MAC address. */
			rtlpriv->sec.pairwise_enc_algorithm = key_type;
			/*set local buf about pairwise key. */
			memcpy(rtlpriv->sec.key_buf[PAIRWISE_KEYIDX],
			       key->key, key->keylen);
			rtlpriv->sec.key_len[PAIRWISE_KEYIDX] = key->keylen;
			rtlpriv->sec.pairwise_key =
			    rtlpriv->sec.key_buf[PAIRWISE_KEYIDX];
			memcpy(mac_addr, sta->addr, ETH_ALEN);
		}
		rtlpriv->cfg->ops->set_key(hw, key_idx, mac_addr,
					   group_key, key_type, wep_only,
					   false);
		/* <5> tell mac80211 do something: */
		/*must use sw generate IV, or can not work !!!!. */
		key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
		key->hw_key_idx = key_idx;
		if (key_type == TKIP_ENCRYPTION)
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
		break;
	case DISABLE_KEY:
		RT_TRACE(rtlpriv, COMP_SEC, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
			 "disable key delete one entry\n");
=======
			 ("disable key delete one entry\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("disable key delete one entry\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		/*set local buf about wep key. */
		if (mac->opmode == NL80211_IFTYPE_AP) {
			if (sta)
				rtl_cam_del_entry(hw, sta->addr);
		}
		memset(rtlpriv->sec.key_buf[key_idx], 0, key->keylen);
		rtlpriv->sec.key_len[key_idx] = 0;
		memcpy(mac_addr, zero_addr, ETH_ALEN);
		/*
		 *mac80211 will delete entrys one by one,
		 *so don't use rtl_cam_reset_all_entry
		 *or clear all entry here.
		 */
		rtl_cam_delete_one_entry(hw, mac_addr, key_idx);

		rtl_cam_reset_sec_info(hw);

		break;
	default:
		RT_TRACE(rtlpriv, COMP_ERR, DBG_EMERG,
<<<<<<< HEAD
<<<<<<< HEAD
			 "cmd_err:%x!!!!\n", cmd);
=======
			 ("cmd_err:%x!!!!:\n", cmd));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("cmd_err:%x!!!!:\n", cmd));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
out_unlock:
	mutex_unlock(&rtlpriv->locks.conf_mutex);
	rtlpriv->sec.being_setkey = false;
	return err;
}

static void rtl_op_rfkill_poll(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	bool radio_state;
	bool blocked;
	u8 valid = 0;

	if (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		return;

	mutex_lock(&rtlpriv->locks.conf_mutex);

	/*if Radio On return true here */
	radio_state = rtlpriv->cfg->ops->radio_onoff_checking(hw, &valid);

	if (valid) {
		if (unlikely(radio_state != rtlpriv->rfkill.rfkill_state)) {
			rtlpriv->rfkill.rfkill_state = radio_state;

			RT_TRACE(rtlpriv, COMP_RF, DBG_DMESG,
<<<<<<< HEAD
<<<<<<< HEAD
				 "wireless radio switch turned %s\n",
				 radio_state ? "on" : "off");
=======
				 (KERN_INFO "wireless radio switch turned %s\n",
				  radio_state ? "on" : "off"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 (KERN_INFO "wireless radio switch turned %s\n",
				  radio_state ? "on" : "off"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

			blocked = (rtlpriv->rfkill.rfkill_state == 1) ? 0 : 1;
			wiphy_rfkill_set_hw_state(hw->wiphy, blocked);
		}
	}

	mutex_unlock(&rtlpriv->locks.conf_mutex);
}

/* this function is called by mac80211 to flush tx buffer
 * before switch channle or power save, or tx buffer packet
 * maybe send after offchannel or rf sleep, this may cause
 * dis-association by AP */
static void rtl_op_flush(struct ieee80211_hw *hw, bool drop)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);

	if (rtlpriv->intf_ops->flush)
		rtlpriv->intf_ops->flush(hw, drop);
}

const struct ieee80211_ops rtl_ops = {
	.start = rtl_op_start,
	.stop = rtl_op_stop,
	.tx = rtl_op_tx,
	.add_interface = rtl_op_add_interface,
	.remove_interface = rtl_op_remove_interface,
	.config = rtl_op_config,
	.configure_filter = rtl_op_configure_filter,
	.sta_add = rtl_op_sta_add,
	.sta_remove = rtl_op_sta_remove,
	.set_key = rtl_op_set_key,
	.conf_tx = rtl_op_conf_tx,
	.bss_info_changed = rtl_op_bss_info_changed,
	.get_tsf = rtl_op_get_tsf,
	.set_tsf = rtl_op_set_tsf,
	.reset_tsf = rtl_op_reset_tsf,
	.sta_notify = rtl_op_sta_notify,
	.ampdu_action = rtl_op_ampdu_action,
	.sw_scan_start = rtl_op_sw_scan_start,
	.sw_scan_complete = rtl_op_sw_scan_complete,
	.rfkill_poll = rtl_op_rfkill_poll,
	.flush = rtl_op_flush,
};
