/******************************************************************************
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright(c) 2003 - 2012 Intel Corporation. All rights reserved.
=======
 * Copyright(c) 2003 - 2011 Intel Corporation. All rights reserved.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Copyright(c) 2003 - 2011 Intel Corporation. All rights reserved.
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
 *  Intel Linux Wireless <ilw@linux.intel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/

#ifndef __iwl_leds_h__
#define __iwl_leds_h__


struct iwl_priv;

#define IWL_LED_SOLID 11
#define IWL_DEF_LED_INTRVL cpu_to_le32(1000)

#define IWL_LED_ACTIVITY       (0<<1)
#define IWL_LED_LINK           (1<<1)

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * LED mode
 *    IWL_LED_DEFAULT:  use device default
 *    IWL_LED_RF_STATE: turn LED on/off based on RF state
 *			LED ON  = RF ON
 *			LED OFF = RF OFF
 *    IWL_LED_BLINK:    adjust led blink rate based on blink table
 */
enum iwl_led_mode {
	IWL_LED_DEFAULT,
	IWL_LED_RF_STATE,
	IWL_LED_BLINK,
};

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void iwlagn_led_enable(struct iwl_priv *priv);
void iwl_leds_init(struct iwl_priv *priv);
void iwl_leds_exit(struct iwl_priv *priv);

#endif /* __iwl_leds_h__ */
