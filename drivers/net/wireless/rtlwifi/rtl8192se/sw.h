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
 *****************************************************************************/
#ifndef __REALTEK_PCI92SE_SW_H__
#define __REALTEK_PCI92SE_SW_H__

#define EFUSE_MAX_SECTION	16

int rtl92se_init_sw(struct ieee80211_hw *hw);
void rtl92se_deinit_sw(struct ieee80211_hw *hw);
void rtl92se_init_var_map(struct ieee80211_hw *hw);

#endif
