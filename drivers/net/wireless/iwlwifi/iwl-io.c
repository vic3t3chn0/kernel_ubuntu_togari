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
 * Portions of this file are derived from the ipw3945 project.
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
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/delay.h>
#include <linux/device.h>

#include "iwl-io.h"
#include"iwl-csr.h"
#include "iwl-debug.h"

#define IWL_POLL_INTERVAL 10	/* microseconds */

static inline void __iwl_set_bit(struct iwl_trans *trans, u32 reg, u32 mask)
{
	iwl_write32(trans, reg, iwl_read32(trans, reg) | mask);
}

static inline void __iwl_clear_bit(struct iwl_trans *trans, u32 reg, u32 mask)
{
	iwl_write32(trans, reg, iwl_read32(trans, reg) & ~mask);
}

void iwl_set_bit(struct iwl_trans *trans, u32 reg, u32 mask)
{
	unsigned long flags;

	spin_lock_irqsave(&trans->reg_lock, flags);
	__iwl_set_bit(trans, reg, mask);
	spin_unlock_irqrestore(&trans->reg_lock, flags);
}

void iwl_clear_bit(struct iwl_trans *trans, u32 reg, u32 mask)
{
	unsigned long flags;

	spin_lock_irqsave(&trans->reg_lock, flags);
	__iwl_clear_bit(trans, reg, mask);
	spin_unlock_irqrestore(&trans->reg_lock, flags);
}

int iwl_poll_bit(struct iwl_trans *trans, u32 addr,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include "iwl-io.h"

#define IWL_POLL_INTERVAL 10	/* microseconds */

static inline void __iwl_set_bit(struct iwl_priv *priv, u32 reg, u32 mask)
{
	iwl_write32(priv, reg, iwl_read32(priv, reg) | mask);
}

static inline void __iwl_clear_bit(struct iwl_priv *priv, u32 reg, u32 mask)
{
	iwl_write32(priv, reg, iwl_read32(priv, reg) & ~mask);
}

void iwl_set_bit(struct iwl_priv *priv, u32 reg, u32 mask)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->reg_lock, flags);
	__iwl_set_bit(priv, reg, mask);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
}

void iwl_clear_bit(struct iwl_priv *priv, u32 reg, u32 mask)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->reg_lock, flags);
	__iwl_clear_bit(priv, reg, mask);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
}

int iwl_poll_bit(struct iwl_priv *priv, u32 addr,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 u32 bits, u32 mask, int timeout)
{
	int t = 0;

	do {
<<<<<<< HEAD
<<<<<<< HEAD
		if ((iwl_read32(trans, addr) & mask) == (bits & mask))
=======
		if ((iwl_read32(priv, addr) & mask) == (bits & mask))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if ((iwl_read32(priv, addr) & mask) == (bits & mask))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			return t;
		udelay(IWL_POLL_INTERVAL);
		t += IWL_POLL_INTERVAL;
	} while (t < timeout);

	return -ETIMEDOUT;
}

<<<<<<< HEAD
<<<<<<< HEAD
int iwl_grab_nic_access_silent(struct iwl_trans *trans)
{
	int ret;

	lockdep_assert_held(&trans->reg_lock);

	/* this bit wakes up the NIC */
	__iwl_set_bit(trans, CSR_GP_CNTRL,
		      CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int iwl_grab_nic_access_silent(struct iwl_priv *priv)
{
	int ret;

	lockdep_assert_held(&priv->reg_lock);

	/* this bit wakes up the NIC */
	__iwl_set_bit(priv, CSR_GP_CNTRL, CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/*
	 * These bits say the device is running, and should keep running for
	 * at least a short while (at least as long as MAC_ACCESS_REQ stays 1),
	 * but they do not indicate that embedded SRAM is restored yet;
	 * 3945 and 4965 have volatile SRAM, and must save/restore contents
	 * to/from host DRAM when sleeping/waking for power-saving.
	 * Each direction takes approximately 1/4 millisecond; with this
	 * overhead, it's a good idea to grab and hold MAC_ACCESS_REQUEST if a
	 * series of register accesses are expected (e.g. reading Event Log),
	 * to keep device from sleeping.
	 *
	 * CSR_UCODE_DRV_GP1 register bit MAC_SLEEP == 0 indicates that
	 * SRAM is okay/restored.  We don't check that here because this call
	 * is just for hardware register access; but GP1 MAC_SLEEP check is a
	 * good idea before accessing 3945/4965 SRAM (e.g. reading Event Log).
	 *
	 * 5000 series and later (including 1000 series) have non-volatile SRAM,
	 * and do not save/restore SRAM when power cycling.
	 */
<<<<<<< HEAD
<<<<<<< HEAD
	ret = iwl_poll_bit(trans, CSR_GP_CNTRL,
=======
	ret = iwl_poll_bit(priv, CSR_GP_CNTRL,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ret = iwl_poll_bit(priv, CSR_GP_CNTRL,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			   CSR_GP_CNTRL_REG_VAL_MAC_ACCESS_EN,
			   (CSR_GP_CNTRL_REG_FLAG_MAC_CLOCK_READY |
			    CSR_GP_CNTRL_REG_FLAG_GOING_TO_SLEEP), 15000);
	if (ret < 0) {
<<<<<<< HEAD
<<<<<<< HEAD
		iwl_write32(trans, CSR_RESET, CSR_RESET_REG_FLAG_FORCE_NMI);
=======
		iwl_write32(priv, CSR_RESET, CSR_RESET_REG_FLAG_FORCE_NMI);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		iwl_write32(priv, CSR_RESET, CSR_RESET_REG_FLAG_FORCE_NMI);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EIO;
	}

	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
bool iwl_grab_nic_access(struct iwl_trans *trans)
{
	int ret = iwl_grab_nic_access_silent(trans);
	if (unlikely(ret)) {
		u32 val = iwl_read32(trans, CSR_GP_CNTRL);
		WARN_ONCE(1, "Timeout waiting for hardware access "
			     "(CSR_GP_CNTRL 0x%08x)\n", val);
		return false;
	}

	return true;
}

void iwl_release_nic_access(struct iwl_trans *trans)
{
	lockdep_assert_held(&trans->reg_lock);
	__iwl_clear_bit(trans, CSR_GP_CNTRL,
			CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
	/*
	 * Above we read the CSR_GP_CNTRL register, which will flush
	 * any previous writes, but we need the write that clears the
	 * MAC_ACCESS_REQ bit to be performed before any other writes
	 * scheduled on different CPUs (after we drop reg_lock).
	 */
	mmiowb();
}

u32 iwl_read_direct32(struct iwl_trans *trans, u32 reg)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int iwl_grab_nic_access(struct iwl_priv *priv)
{
	int ret = iwl_grab_nic_access_silent(priv);
	if (ret) {
		u32 val = iwl_read32(priv, CSR_GP_CNTRL);
		IWL_ERR(priv,
			"MAC is in deep sleep!. CSR_GP_CNTRL = 0x%08X\n", val);
	}

	return ret;
}

void iwl_release_nic_access(struct iwl_priv *priv)
{
	lockdep_assert_held(&priv->reg_lock);
	__iwl_clear_bit(priv, CSR_GP_CNTRL,
			CSR_GP_CNTRL_REG_FLAG_MAC_ACCESS_REQ);
}

u32 iwl_read_direct32(struct iwl_priv *priv, u32 reg)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	u32 value;
	unsigned long flags;

<<<<<<< HEAD
<<<<<<< HEAD
	spin_lock_irqsave(&trans->reg_lock, flags);
	iwl_grab_nic_access(trans);
	value = iwl_read32(trans, reg);
	iwl_release_nic_access(trans);
	spin_unlock_irqrestore(&trans->reg_lock, flags);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spin_lock_irqsave(&priv->reg_lock, flags);
	iwl_grab_nic_access(priv);
	value = iwl_read32(priv, reg);
	iwl_release_nic_access(priv);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return value;
}

<<<<<<< HEAD
<<<<<<< HEAD
void iwl_write_direct32(struct iwl_trans *trans, u32 reg, u32 value)
{
	unsigned long flags;

	spin_lock_irqsave(&trans->reg_lock, flags);
	if (likely(iwl_grab_nic_access(trans))) {
		iwl_write32(trans, reg, value);
		iwl_release_nic_access(trans);
	}
	spin_unlock_irqrestore(&trans->reg_lock, flags);
}

int iwl_poll_direct_bit(struct iwl_trans *trans, u32 addr, u32 mask,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void iwl_write_direct32(struct iwl_priv *priv, u32 reg, u32 value)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->reg_lock, flags);
	if (!iwl_grab_nic_access(priv)) {
		iwl_write32(priv, reg, value);
		iwl_release_nic_access(priv);
	}
	spin_unlock_irqrestore(&priv->reg_lock, flags);
}

int iwl_poll_direct_bit(struct iwl_priv *priv, u32 addr, u32 mask,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			int timeout)
{
	int t = 0;

	do {
<<<<<<< HEAD
<<<<<<< HEAD
		if ((iwl_read_direct32(trans, addr) & mask) == mask)
=======
		if ((iwl_read_direct32(priv, addr) & mask) == mask)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		if ((iwl_read_direct32(priv, addr) & mask) == mask)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			return t;
		udelay(IWL_POLL_INTERVAL);
		t += IWL_POLL_INTERVAL;
	} while (t < timeout);

	return -ETIMEDOUT;
}

<<<<<<< HEAD
<<<<<<< HEAD
static inline u32 __iwl_read_prph(struct iwl_trans *trans, u32 reg)
{
	iwl_write32(trans, HBUS_TARG_PRPH_RADDR, reg | (3 << 24));
	return iwl_read32(trans, HBUS_TARG_PRPH_RDAT);
}

static inline void __iwl_write_prph(struct iwl_trans *trans, u32 addr, u32 val)
{
	iwl_write32(trans, HBUS_TARG_PRPH_WADDR,
		    ((addr & 0x0000FFFF) | (3 << 24)));
	iwl_write32(trans, HBUS_TARG_PRPH_WDAT, val);
}

u32 iwl_read_prph(struct iwl_trans *trans, u32 reg)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static inline u32 __iwl_read_prph(struct iwl_priv *priv, u32 reg)
{
	iwl_write32(priv, HBUS_TARG_PRPH_RADDR, reg | (3 << 24));
	rmb();
	return iwl_read32(priv, HBUS_TARG_PRPH_RDAT);
}

static inline void __iwl_write_prph(struct iwl_priv *priv, u32 addr, u32 val)
{
	iwl_write32(priv, HBUS_TARG_PRPH_WADDR,
		    ((addr & 0x0000FFFF) | (3 << 24)));
	wmb();
	iwl_write32(priv, HBUS_TARG_PRPH_WDAT, val);
}

u32 iwl_read_prph(struct iwl_priv *priv, u32 reg)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	unsigned long flags;
	u32 val;

<<<<<<< HEAD
<<<<<<< HEAD
	spin_lock_irqsave(&trans->reg_lock, flags);
	iwl_grab_nic_access(trans);
	val = __iwl_read_prph(trans, reg);
	iwl_release_nic_access(trans);
	spin_unlock_irqrestore(&trans->reg_lock, flags);
	return val;
}

void iwl_write_prph(struct iwl_trans *trans, u32 addr, u32 val)
{
	unsigned long flags;

	spin_lock_irqsave(&trans->reg_lock, flags);
	if (likely(iwl_grab_nic_access(trans))) {
		__iwl_write_prph(trans, addr, val);
		iwl_release_nic_access(trans);
	}
	spin_unlock_irqrestore(&trans->reg_lock, flags);
}

void iwl_set_bits_prph(struct iwl_trans *trans, u32 reg, u32 mask)
{
	unsigned long flags;

	spin_lock_irqsave(&trans->reg_lock, flags);
	if (likely(iwl_grab_nic_access(trans))) {
		__iwl_write_prph(trans, reg,
				 __iwl_read_prph(trans, reg) | mask);
		iwl_release_nic_access(trans);
	}
	spin_unlock_irqrestore(&trans->reg_lock, flags);
}

void iwl_set_bits_mask_prph(struct iwl_trans *trans, u32 reg,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spin_lock_irqsave(&priv->reg_lock, flags);
	iwl_grab_nic_access(priv);
	val = __iwl_read_prph(priv, reg);
	iwl_release_nic_access(priv);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
	return val;
}

void iwl_write_prph(struct iwl_priv *priv, u32 addr, u32 val)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->reg_lock, flags);
	if (!iwl_grab_nic_access(priv)) {
		__iwl_write_prph(priv, addr, val);
		iwl_release_nic_access(priv);
	}
	spin_unlock_irqrestore(&priv->reg_lock, flags);
}

void iwl_set_bits_prph(struct iwl_priv *priv, u32 reg, u32 mask)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->reg_lock, flags);
	iwl_grab_nic_access(priv);
	__iwl_write_prph(priv, reg, __iwl_read_prph(priv, reg) | mask);
	iwl_release_nic_access(priv);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
}

void iwl_set_bits_mask_prph(struct iwl_priv *priv, u32 reg,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			    u32 bits, u32 mask)
{
	unsigned long flags;

<<<<<<< HEAD
<<<<<<< HEAD
	spin_lock_irqsave(&trans->reg_lock, flags);
	if (likely(iwl_grab_nic_access(trans))) {
		__iwl_write_prph(trans, reg,
				 (__iwl_read_prph(trans, reg) & mask) | bits);
		iwl_release_nic_access(trans);
	}
	spin_unlock_irqrestore(&trans->reg_lock, flags);
}

void iwl_clear_bits_prph(struct iwl_trans *trans, u32 reg, u32 mask)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spin_lock_irqsave(&priv->reg_lock, flags);
	iwl_grab_nic_access(priv);
	__iwl_write_prph(priv, reg,
			 (__iwl_read_prph(priv, reg) & mask) | bits);
	iwl_release_nic_access(priv);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
}

void iwl_clear_bits_prph(struct iwl_priv *priv, u32 reg, u32 mask)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	unsigned long flags;
	u32 val;

<<<<<<< HEAD
<<<<<<< HEAD
	spin_lock_irqsave(&trans->reg_lock, flags);
	if (likely(iwl_grab_nic_access(trans))) {
		val = __iwl_read_prph(trans, reg);
		__iwl_write_prph(trans, reg, (val & ~mask));
		iwl_release_nic_access(trans);
	}
	spin_unlock_irqrestore(&trans->reg_lock, flags);
}

void _iwl_read_targ_mem_words(struct iwl_trans *trans, u32 addr,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spin_lock_irqsave(&priv->reg_lock, flags);
	iwl_grab_nic_access(priv);
	val = __iwl_read_prph(priv, reg);
	__iwl_write_prph(priv, reg, (val & ~mask));
	iwl_release_nic_access(priv);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
}

void _iwl_read_targ_mem_words(struct iwl_priv *priv, u32 addr,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			      void *buf, int words)
{
	unsigned long flags;
	int offs;
	u32 *vals = buf;

<<<<<<< HEAD
<<<<<<< HEAD
	spin_lock_irqsave(&trans->reg_lock, flags);
	if (likely(iwl_grab_nic_access(trans))) {
		iwl_write32(trans, HBUS_TARG_MEM_RADDR, addr);
		for (offs = 0; offs < words; offs++)
			vals[offs] = iwl_read32(trans, HBUS_TARG_MEM_RDAT);
		iwl_release_nic_access(trans);
	}
	spin_unlock_irqrestore(&trans->reg_lock, flags);
}

u32 iwl_read_targ_mem(struct iwl_trans *trans, u32 addr)
{
	u32 value;

	_iwl_read_targ_mem_words(trans, addr, &value, 1);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	spin_lock_irqsave(&priv->reg_lock, flags);
	iwl_grab_nic_access(priv);

	iwl_write32(priv, HBUS_TARG_MEM_RADDR, addr);
	rmb();

	for (offs = 0; offs < words; offs++)
		vals[offs] = iwl_read32(priv, HBUS_TARG_MEM_RDAT);

	iwl_release_nic_access(priv);
	spin_unlock_irqrestore(&priv->reg_lock, flags);
}

u32 iwl_read_targ_mem(struct iwl_priv *priv, u32 addr)
{
	u32 value;

	_iwl_read_targ_mem_words(priv, addr, &value, 1);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return value;
}

<<<<<<< HEAD
<<<<<<< HEAD
int _iwl_write_targ_mem_words(struct iwl_trans *trans, u32 addr,
				void *buf, int words)
{
	unsigned long flags;
	int offs, result = 0;
	u32 *vals = buf;

	spin_lock_irqsave(&trans->reg_lock, flags);
	if (likely(iwl_grab_nic_access(trans))) {
		iwl_write32(trans, HBUS_TARG_MEM_WADDR, addr);
		for (offs = 0; offs < words; offs++)
			iwl_write32(trans, HBUS_TARG_MEM_WDAT, vals[offs]);
		iwl_release_nic_access(trans);
	} else
		result = -EBUSY;
	spin_unlock_irqrestore(&trans->reg_lock, flags);

	return result;
}

int iwl_write_targ_mem(struct iwl_trans *trans, u32 addr, u32 val)
{
	return _iwl_write_targ_mem_words(trans, addr, &val, 1);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void iwl_write_targ_mem(struct iwl_priv *priv, u32 addr, u32 val)
{
	unsigned long flags;

	spin_lock_irqsave(&priv->reg_lock, flags);
	if (!iwl_grab_nic_access(priv)) {
		iwl_write32(priv, HBUS_TARG_MEM_WADDR, addr);
		wmb();
		iwl_write32(priv, HBUS_TARG_MEM_WDAT, val);
		iwl_release_nic_access(priv);
	}
	spin_unlock_irqrestore(&priv->reg_lock, flags);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
