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

#include "../wifi.h"
#include "../base.h"
#include "reg.h"
#include "def.h"
#include "phy.h"
#include "dm.h"

void rtl92cu_dm_dynamic_txpower(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_phy *rtlphy = &(rtlpriv->phy);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	long undecorated_smoothed_pwdb;

	if (!rtlpriv->dm.dynamic_txpower_enable)
		return;

	if (rtlpriv->dm.dm_flag & HAL_DM_HIPWR_DISABLE) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;
		return;
	}

	if ((mac->link_state < MAC80211_LINKED) &&
	    (rtlpriv->dm.entry_min_undecoratedsmoothed_pwdb == 0)) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_TRACE,
<<<<<<< HEAD
<<<<<<< HEAD
			 "Not connected to any\n");
=======
			 ("Not connected to any\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("Not connected to any\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;

		rtlpriv->dm.last_dtp_lvl = TXHIGHPWRLEVEL_NORMAL;
		return;
	}

	if (mac->link_state >= MAC80211_LINKED) {
		if (mac->opmode == NL80211_IFTYPE_ADHOC) {
			undecorated_smoothed_pwdb =
			    rtlpriv->dm.entry_min_undecoratedsmoothed_pwdb;
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
				 "AP Client PWDB = 0x%lx\n",
				 undecorated_smoothed_pwdb);
=======
				 ("AP Client PWDB = 0x%lx\n",
				  undecorated_smoothed_pwdb));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("AP Client PWDB = 0x%lx\n",
				  undecorated_smoothed_pwdb));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		} else {
			undecorated_smoothed_pwdb =
			    rtlpriv->dm.undecorated_smoothed_pwdb;
			RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
				 "STA Default Port PWDB = 0x%lx\n",
				 undecorated_smoothed_pwdb);
=======
				 ("STA Default Port PWDB = 0x%lx\n",
				  undecorated_smoothed_pwdb));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				 ("STA Default Port PWDB = 0x%lx\n",
				  undecorated_smoothed_pwdb));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
	} else {
		undecorated_smoothed_pwdb =
		    rtlpriv->dm.entry_min_undecoratedsmoothed_pwdb;

		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "AP Ext Port PWDB = 0x%lx\n",
			 undecorated_smoothed_pwdb);
=======
			 ("AP Ext Port PWDB = 0x%lx\n",
			  undecorated_smoothed_pwdb));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("AP Ext Port PWDB = 0x%lx\n",
			  undecorated_smoothed_pwdb));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	if (undecorated_smoothed_pwdb >= TX_POWER_NEAR_FIELD_THRESH_LVL2) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_LEVEL1;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x0)\n");
=======
			 ("TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x0)\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x0)\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	} else if ((undecorated_smoothed_pwdb <
		    (TX_POWER_NEAR_FIELD_THRESH_LVL2 - 3)) &&
		   (undecorated_smoothed_pwdb >=
		    TX_POWER_NEAR_FIELD_THRESH_LVL1)) {

		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_LEVEL1;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x10)\n");
=======
			 ("TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x10)\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("TXHIGHPWRLEVEL_LEVEL1 (TxPwr=0x10)\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	} else if (undecorated_smoothed_pwdb <
		   (TX_POWER_NEAR_FIELD_THRESH_LVL1 - 5)) {
		rtlpriv->dm.dynamic_txhighpower_lvl = TXHIGHPWRLEVEL_NORMAL;
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "TXHIGHPWRLEVEL_NORMAL\n");
=======
			 ("TXHIGHPWRLEVEL_NORMAL\n"));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("TXHIGHPWRLEVEL_NORMAL\n"));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	if ((rtlpriv->dm.dynamic_txhighpower_lvl != rtlpriv->dm.last_dtp_lvl)) {
		RT_TRACE(rtlpriv, COMP_POWER, DBG_LOUD,
<<<<<<< HEAD
<<<<<<< HEAD
			 "PHY_SetTxPowerLevel8192S() Channel = %d\n",
			 rtlphy->current_channel);
=======
			 ("PHY_SetTxPowerLevel8192S() Channel = %d\n",
			  rtlphy->current_channel));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 ("PHY_SetTxPowerLevel8192S() Channel = %d\n",
			  rtlphy->current_channel));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		rtl92c_phy_set_txpower_level(hw, rtlphy->current_channel);
	}

	rtlpriv->dm.last_dtp_lvl = rtlpriv->dm.dynamic_txhighpower_lvl;
}
