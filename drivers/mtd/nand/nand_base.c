/*
 *  drivers/mtd/nand.c
 *
 *  Overview:
 *   This is the generic MTD driver for NAND flash devices. It should be
 *   capable of working with almost all NAND chips currently available.
 *   Basic support for AG-AND chips is provided.
 *
 *	Additional technical information is available on
 *	http://www.linux-mtd.infradead.org/doc/nand.html
 *
 *  Copyright (C) 2000 Steven J. Hill (sjhill@realitydiluted.com)
 *		  2002-2006 Thomas Gleixner (tglx@linutronix.de)
 *
 *  Credits:
 *	David Woodhouse for adding multichip support
 *
 *	Aleph One Ltd. and Toby Churchill Ltd. for supporting the
 *	rework for 2K page size chips
 *
 *  TODO:
 *	Enable cached programming for 2k page size chips
 *	Check, if mtd->ecctype should be set to MTD_ECC_HW
<<<<<<< HEAD
<<<<<<< HEAD
 *	if we have HW ECC support.
=======
 *	if we have HW ecc support.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 *	if we have HW ecc support.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *	The AG-AND chips have nice features for speed improvement,
 *	which are not supported yet. Read / program 4 pages in one go.
 *	BBT table is not serialized, has to be fixed
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/module.h>
#include <linux/delay.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/nand_bch.h>
#include <linux/interrupt.h>
#include <linux/bitops.h>
#include <linux/leds.h>
#include <linux/io.h>
#include <linux/mtd/partitions.h>

/* Define default oob placement schemes for large and small page devices */
static struct nand_ecclayout nand_oob_8 = {
	.eccbytes = 3,
	.eccpos = {0, 1, 2},
	.oobfree = {
		{.offset = 3,
		 .length = 2},
		{.offset = 6,
		 .length = 2} }
};

static struct nand_ecclayout nand_oob_16 = {
	.eccbytes = 6,
	.eccpos = {0, 1, 2, 3, 6, 7},
	.oobfree = {
		{.offset = 8,
		 . length = 8} }
};

static struct nand_ecclayout nand_oob_64 = {
	.eccbytes = 24,
	.eccpos = {
		   40, 41, 42, 43, 44, 45, 46, 47,
		   48, 49, 50, 51, 52, 53, 54, 55,
		   56, 57, 58, 59, 60, 61, 62, 63},
	.oobfree = {
		{.offset = 2,
		 .length = 38} }
};

static struct nand_ecclayout nand_oob_128 = {
	.eccbytes = 48,
	.eccpos = {
		   80, 81, 82, 83, 84, 85, 86, 87,
		   88, 89, 90, 91, 92, 93, 94, 95,
		   96, 97, 98, 99, 100, 101, 102, 103,
		   104, 105, 106, 107, 108, 109, 110, 111,
		   112, 113, 114, 115, 116, 117, 118, 119,
		   120, 121, 122, 123, 124, 125, 126, 127},
	.oobfree = {
		{.offset = 2,
		 .length = 78} }
};

static int nand_get_device(struct nand_chip *chip, struct mtd_info *mtd,
			   int new_state);

static int nand_do_write_oob(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops);

/*
 * For devices which display every fart in the system on a separate LED. Is
 * compiled away when LED support is disabled.
 */
DEFINE_LED_TRIGGER(nand_led_trigger);

static int check_offs_len(struct mtd_info *mtd,
					loff_t ofs, uint64_t len)
{
	struct nand_chip *chip = mtd->priv;
	int ret = 0;

	/* Start address must align on block boundary */
	if (ofs & ((1 << chip->phys_erase_shift) - 1)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: unaligned address\n", __func__);
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Unaligned address\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Unaligned address\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ret = -EINVAL;
	}

	/* Length must align on block boundary */
	if (len & ((1 << chip->phys_erase_shift) - 1)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: length not block aligned\n", __func__);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Length not block aligned\n",
					__func__);
		ret = -EINVAL;
	}

	/* Do not allow past end of device */
	if (ofs + len > mtd->size) {
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Past end of device\n",
					__func__);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ret = -EINVAL;
	}

	return ret;
}

/**
 * nand_release_device - [GENERIC] release chip
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 *
 * Deselect, release chip lock and wake up anyone waiting on the device.
=======
 * @mtd:	MTD device structure
 *
 * Deselect, release chip lock and wake up anyone waiting on the device
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
 *
 * Deselect, release chip lock and wake up anyone waiting on the device
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_release_device(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;

	/* De-select the NAND device */
	chip->select_chip(mtd, -1);

	/* Release the controller and the chip */
	spin_lock(&chip->controller->lock);
	chip->controller->active = NULL;
	chip->state = FL_READY;
	wake_up(&chip->controller->wq);
	spin_unlock(&chip->controller->lock);
}

/**
 * nand_read_byte - [DEFAULT] read one byte from the chip
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 *
 * Default read function for 8bit buswidth
=======
 * @mtd:	MTD device structure
 *
 * Default read function for 8bit buswith
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
 *
 * Default read function for 8bit buswith
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static uint8_t nand_read_byte(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	return readb(chip->IO_ADDR_R);
}

/**
 * nand_read_byte16 - [DEFAULT] read one byte endianess aware from the chip
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_byte16 - [DEFAULT] read one byte endianness aware from the chip
 * @mtd: MTD device structure
 *
 * Default read function for 16bit buswidth with endianness conversion.
 *
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 *
 * Default read function for 16bit buswith with
 * endianess conversion
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static uint8_t nand_read_byte16(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	return (uint8_t) cpu_to_le16(readw(chip->IO_ADDR_R));
}

/**
 * nand_read_word - [DEFAULT] read one word from the chip
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 *
 * Default read function for 16bit buswidth without endianness conversion.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 *
 * Default read function for 16bit buswith without
 * endianess conversion
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static u16 nand_read_word(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	return readw(chip->IO_ADDR_R);
}

/**
 * nand_select_chip - [DEFAULT] control CE line
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @chipnr: chipnumber to select, -1 for deselect
=======
 * @mtd:	MTD device structure
 * @chipnr:	chipnumber to select, -1 for deselect
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
 * @chipnr:	chipnumber to select, -1 for deselect
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Default select function for 1 chip devices.
 */
static void nand_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct nand_chip *chip = mtd->priv;

	switch (chipnr) {
	case -1:
		chip->cmd_ctrl(mtd, NAND_CMD_NONE, 0 | NAND_CTRL_CHANGE);
		break;
	case 0:
		break;

	default:
		BUG();
	}
}

/**
 * nand_write_buf - [DEFAULT] write buffer to chip
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @buf: data buffer
 * @len: number of bytes to write
 *
 * Default write function for 8bit buswidth.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @buf:	data buffer
 * @len:	number of bytes to write
 *
 * Default write function for 8bit buswith
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_write_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd->priv;

	for (i = 0; i < len; i++)
		writeb(buf[i], chip->IO_ADDR_W);
}

/**
 * nand_read_buf - [DEFAULT] read chip data into buffer
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @buf: buffer to store date
 * @len: number of bytes to read
 *
 * Default read function for 8bit buswidth.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @buf:	buffer to store date
 * @len:	number of bytes to read
 *
 * Default read function for 8bit buswith
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_read_buf(struct mtd_info *mtd, uint8_t *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd->priv;

	for (i = 0; i < len; i++)
		buf[i] = readb(chip->IO_ADDR_R);
}

/**
 * nand_verify_buf - [DEFAULT] Verify chip data against buffer
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @buf: buffer containing the data to compare
 * @len: number of bytes to compare
 *
 * Default verify function for 8bit buswidth.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @buf:	buffer containing the data to compare
 * @len:	number of bytes to compare
 *
 * Default verify function for 8bit buswith
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_verify_buf(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd->priv;

	for (i = 0; i < len; i++)
		if (buf[i] != readb(chip->IO_ADDR_R))
			return -EFAULT;
	return 0;
}

/**
 * nand_write_buf16 - [DEFAULT] write buffer to chip
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @buf: data buffer
 * @len: number of bytes to write
 *
 * Default write function for 16bit buswidth.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @buf:	data buffer
 * @len:	number of bytes to write
 *
 * Default write function for 16bit buswith
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_write_buf16(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd->priv;
	u16 *p = (u16 *) buf;
	len >>= 1;

	for (i = 0; i < len; i++)
		writew(p[i], chip->IO_ADDR_W);

}

/**
 * nand_read_buf16 - [DEFAULT] read chip data into buffer
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @buf: buffer to store date
 * @len: number of bytes to read
 *
 * Default read function for 16bit buswidth.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @buf:	buffer to store date
 * @len:	number of bytes to read
 *
 * Default read function for 16bit buswith
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_read_buf16(struct mtd_info *mtd, uint8_t *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd->priv;
	u16 *p = (u16 *) buf;
	len >>= 1;

	for (i = 0; i < len; i++)
		p[i] = readw(chip->IO_ADDR_R);
}

/**
 * nand_verify_buf16 - [DEFAULT] Verify chip data against buffer
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @buf: buffer containing the data to compare
 * @len: number of bytes to compare
 *
 * Default verify function for 16bit buswidth.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @buf:	buffer containing the data to compare
 * @len:	number of bytes to compare
 *
 * Default verify function for 16bit buswith
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_verify_buf16(struct mtd_info *mtd, const uint8_t *buf, int len)
{
	int i;
	struct nand_chip *chip = mtd->priv;
	u16 *p = (u16 *) buf;
	len >>= 1;

	for (i = 0; i < len; i++)
		if (p[i] != readw(chip->IO_ADDR_R))
			return -EFAULT;

	return 0;
}

/**
 * nand_block_bad - [DEFAULT] Read bad block marker from the chip
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @ofs: offset from device start
 * @getchip: 0, if the chip is already selected
=======
 * @mtd:	MTD device structure
 * @ofs:	offset from device start
 * @getchip:	0, if the chip is already selected
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
 * @ofs:	offset from device start
 * @getchip:	0, if the chip is already selected
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Check, if the block is bad.
 */
static int nand_block_bad(struct mtd_info *mtd, loff_t ofs, int getchip)
{
<<<<<<< HEAD
<<<<<<< HEAD
	int page, chipnr, res = 0, i = 0;
	struct nand_chip *chip = mtd->priv;
	u16 bad;

	if (chip->bbt_options & NAND_BBT_SCANLASTPAGE)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int page, chipnr, res = 0;
	struct nand_chip *chip = mtd->priv;
	u16 bad;

	if (chip->options & NAND_BBT_SCANLASTPAGE)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ofs += mtd->erasesize - mtd->writesize;

	page = (int)(ofs >> chip->page_shift) & chip->pagemask;

	if (getchip) {
		chipnr = (int)(ofs >> chip->chip_shift);

		nand_get_device(chip, mtd, FL_READING);

		/* Select the NAND device */
		chip->select_chip(mtd, chipnr);
	}

<<<<<<< HEAD
<<<<<<< HEAD
	do {
		if (chip->options & NAND_BUSWIDTH_16) {
			chip->cmdfunc(mtd, NAND_CMD_READOOB,
					chip->badblockpos & 0xFE, page);
			bad = cpu_to_le16(chip->read_word(mtd));
			if (chip->badblockpos & 0x1)
				bad >>= 8;
			else
				bad &= 0xFF;
		} else {
			chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos,
					page);
			bad = chip->read_byte(mtd);
		}

		if (likely(chip->badblockbits == 8))
			res = bad != 0xFF;
		else
			res = hweight8(bad) < chip->badblockbits;
		ofs += mtd->writesize;
		page = (int)(ofs >> chip->page_shift) & chip->pagemask;
		i++;
	} while (!res && i < 2 && (chip->bbt_options & NAND_BBT_SCAN2NDPAGE));
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (chip->options & NAND_BUSWIDTH_16) {
		chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos & 0xFE,
			      page);
		bad = cpu_to_le16(chip->read_word(mtd));
		if (chip->badblockpos & 0x1)
			bad >>= 8;
		else
			bad &= 0xFF;
	} else {
		chip->cmdfunc(mtd, NAND_CMD_READOOB, chip->badblockpos, page);
		bad = chip->read_byte(mtd);
	}

	if (likely(chip->badblockbits == 8))
		res = bad != 0xFF;
	else
		res = hweight8(bad) < chip->badblockbits;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (getchip)
		nand_release_device(mtd);

	return res;
}

/**
 * nand_default_block_markbad - [DEFAULT] mark a block bad
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @ofs: offset from device start
 *
 * This is the default implementation, which can be overridden by a hardware
 * specific driver. We try operations in the following order, according to our
 * bbt_options (NAND_BBT_NO_OOB_BBM and NAND_BBT_USE_FLASH):
 *  (1) erase the affected block, to allow OOB marker to be written cleanly
 *  (2) update in-memory BBT
 *  (3) write bad block marker to OOB area of affected block
 *  (4) update flash-based BBT
 * Note that we retain the first error encountered in (3) or (4), finish the
 * procedures, and dump the error in the end.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @ofs:	offset from device start
 *
 * This is the default implementation, which can be overridden by
 * a hardware specific driver.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
*/
static int nand_default_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd->priv;
	uint8_t buf[2] = { 0, 0 };
<<<<<<< HEAD
<<<<<<< HEAD
	int block, res, ret = 0, i = 0;
	int write_oob = !(chip->bbt_options & NAND_BBT_NO_OOB_BBM);

	if (write_oob) {
		struct erase_info einfo;

		/* Attempt erase before marking OOB */
		memset(&einfo, 0, sizeof(einfo));
		einfo.mtd = mtd;
		einfo.addr = ofs;
		einfo.len = 1 << chip->phys_erase_shift;
		nand_erase_nand(mtd, &einfo, 0);
	}

	/* Get block number */
	block = (int)(ofs >> chip->bbt_erase_shift);
	/* Mark block bad in memory-based BBT */
	if (chip->bbt)
		chip->bbt[block >> 2] |= 0x01 << ((block & 0x03) << 1);

	/* Write bad block marker to OOB */
	if (write_oob) {
		struct mtd_oob_ops ops;
		loff_t wr_ofs = ofs;

		nand_get_device(chip, mtd, FL_WRITING);

		ops.datbuf = NULL;
		ops.oobbuf = buf;
		ops.ooboffs = chip->badblockpos;
		if (chip->options & NAND_BUSWIDTH_16) {
			ops.ooboffs &= ~0x01;
			ops.len = ops.ooblen = 2;
		} else {
			ops.len = ops.ooblen = 1;
		}
		ops.mode = MTD_OPS_PLACE_OOB;

		/* Write to first/last page(s) if necessary */
		if (chip->bbt_options & NAND_BBT_SCANLASTPAGE)
			wr_ofs += mtd->erasesize - mtd->writesize;
		do {
			res = nand_do_write_oob(mtd, wr_ofs, &ops);
			if (!ret)
				ret = res;

			i++;
			wr_ofs += mtd->writesize;
		} while ((chip->bbt_options & NAND_BBT_SCAN2NDPAGE) && i < 2);

		nand_release_device(mtd);
	}

	/* Update flash-based bad block table */
	if (chip->bbt_options & NAND_BBT_USE_FLASH) {
		res = nand_update_bbt(mtd, ofs);
		if (!ret)
			ret = res;
	}

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int block, ret, i = 0;

	if (chip->options & NAND_BBT_SCANLASTPAGE)
		ofs += mtd->erasesize - mtd->writesize;

	/* Get block number */
	block = (int)(ofs >> chip->bbt_erase_shift);
	if (chip->bbt)
		chip->bbt[block >> 2] |= 0x01 << ((block & 0x03) << 1);

	/* Do we have a flash based bad block table ? */
	if (chip->options & NAND_USE_FLASH_BBT)
		ret = nand_update_bbt(mtd, ofs);
	else {
		nand_get_device(chip, mtd, FL_WRITING);

		/* Write to first two pages and to byte 1 and 6 if necessary.
		 * If we write to more than one location, the first error
		 * encountered quits the procedure. We write two bytes per
		 * location, so we dont have to mess with 16 bit access.
		 */
		do {
			chip->ops.len = chip->ops.ooblen = 2;
			chip->ops.datbuf = NULL;
			chip->ops.oobbuf = buf;
			chip->ops.ooboffs = chip->badblockpos & ~0x01;

			ret = nand_do_write_oob(mtd, ofs, &chip->ops);

			if (!ret && (chip->options & NAND_BBT_SCANBYTE1AND6)) {
				chip->ops.ooboffs = NAND_SMALL_BADBLOCK_POS
					& ~0x01;
				ret = nand_do_write_oob(mtd, ofs, &chip->ops);
			}
			i++;
			ofs += mtd->writesize;
		} while (!ret && (chip->options & NAND_BBT_SCAN2NDPAGE) &&
				i < 2);

		nand_release_device(mtd);
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!ret)
		mtd->ecc_stats.badblocks++;

	return ret;
}

/**
 * nand_check_wp - [GENERIC] check if the chip is write protected
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 *
 * Check, if the device is write protected. The function expects, that the
 * device is already selected.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * Check, if the device is write protected
 *
 * The function expects, that the device is already selected
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_check_wp(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Broken xD cards report WP despite being writable */
=======
	/* broken xD cards report WP despite being writable */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* broken xD cards report WP despite being writable */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (chip->options & NAND_BROKEN_XD)
		return 0;

	/* Check the WP bit */
	chip->cmdfunc(mtd, NAND_CMD_STATUS, -1, -1);
	return (chip->read_byte(mtd) & NAND_STATUS_WP) ? 0 : 1;
}

/**
 * nand_block_checkbad - [GENERIC] Check if a block is marked bad
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @ofs: offset from device start
 * @getchip: 0, if the chip is already selected
 * @allowbbt: 1, if its allowed to access the bbt area
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @ofs:	offset from device start
 * @getchip:	0, if the chip is already selected
 * @allowbbt:	1, if its allowed to access the bbt area
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Check, if the block is bad. Either by reading the bad block table or
 * calling of the scan function.
 */
static int nand_block_checkbad(struct mtd_info *mtd, loff_t ofs, int getchip,
			       int allowbbt)
{
	struct nand_chip *chip = mtd->priv;

	if (!chip->bbt)
		return chip->block_bad(mtd, ofs, getchip);

	/* Return info from the table */
	return nand_isbad_bbt(mtd, ofs, allowbbt);
}

/**
 * panic_nand_wait_ready - [GENERIC] Wait for the ready pin after commands.
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @timeo: Timeout
=======
 * @mtd:	MTD device structure
 * @timeo:	Timeout
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
 * @timeo:	Timeout
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Helper function for nand_wait_ready used when needing to wait in interrupt
 * context.
 */
static void panic_nand_wait_ready(struct mtd_info *mtd, unsigned long timeo)
{
	struct nand_chip *chip = mtd->priv;
	int i;

	/* Wait for the device to get ready */
	for (i = 0; i < timeo; i++) {
		if (chip->dev_ready(mtd))
			break;
		touch_softlockup_watchdog();
		mdelay(1);
	}
}

<<<<<<< HEAD
<<<<<<< HEAD
/* Wait for the ready pin, after a command. The timeout is caught later. */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Wait for the ready pin, after a command
 * The timeout is catched later.
 */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void nand_wait_ready(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	unsigned long timeo = jiffies + 2;

	/* 400ms timeout */
	if (in_interrupt() || oops_in_progress)
		return panic_nand_wait_ready(mtd, 400);

	led_trigger_event(nand_led_trigger, LED_FULL);
<<<<<<< HEAD
<<<<<<< HEAD
	/* Wait until command is processed or timeout occurs */
=======
	/* wait until command is processed or timeout occures */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* wait until command is processed or timeout occures */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	do {
		if (chip->dev_ready(mtd))
			break;
		touch_softlockup_watchdog();
	} while (time_before(jiffies, timeo));
	led_trigger_event(nand_led_trigger, LED_OFF);
}
EXPORT_SYMBOL_GPL(nand_wait_ready);

/**
 * nand_command - [DEFAULT] Send command to NAND device
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @command: the command to be sent
 * @column: the column address for this command, -1 if none
 * @page_addr: the page address for this command, -1 if none
 *
 * Send command to NAND device. This function is used for small page devices
 * (256/512 Bytes per page).
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @command:	the command to be sent
 * @column:	the column address for this command, -1 if none
 * @page_addr:	the page address for this command, -1 if none
 *
 * Send command to NAND device. This function is used for small page
 * devices (256/512 Bytes per page)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_command(struct mtd_info *mtd, unsigned int command,
			 int column, int page_addr)
{
	register struct nand_chip *chip = mtd->priv;
	int ctrl = NAND_CTRL_CLE | NAND_CTRL_CHANGE;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Write out the command to the device */
=======
	/*
	 * Write out the command to the device.
	 */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/*
	 * Write out the command to the device.
	 */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (command == NAND_CMD_SEQIN) {
		int readcmd;

		if (column >= mtd->writesize) {
			/* OOB area */
			column -= mtd->writesize;
			readcmd = NAND_CMD_READOOB;
		} else if (column < 256) {
			/* First 256 bytes --> READ0 */
			readcmd = NAND_CMD_READ0;
		} else {
			column -= 256;
			readcmd = NAND_CMD_READ1;
		}
		chip->cmd_ctrl(mtd, readcmd, ctrl);
		ctrl &= ~NAND_CTRL_CHANGE;
	}
	chip->cmd_ctrl(mtd, command, ctrl);

<<<<<<< HEAD
<<<<<<< HEAD
	/* Address cycle, when necessary */
=======
	/*
	 * Address cycle, when necessary
	 */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/*
	 * Address cycle, when necessary
	 */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ctrl = NAND_CTRL_ALE | NAND_CTRL_CHANGE;
	/* Serially input address */
	if (column != -1) {
		/* Adjust columns for 16 bit buswidth */
		if (chip->options & NAND_BUSWIDTH_16)
			column >>= 1;
		chip->cmd_ctrl(mtd, column, ctrl);
		ctrl &= ~NAND_CTRL_CHANGE;
	}
	if (page_addr != -1) {
		chip->cmd_ctrl(mtd, page_addr, ctrl);
		ctrl &= ~NAND_CTRL_CHANGE;
		chip->cmd_ctrl(mtd, page_addr >> 8, ctrl);
		/* One more address cycle for devices > 32MiB */
		if (chip->chipsize > (32 << 20))
			chip->cmd_ctrl(mtd, page_addr >> 16, ctrl);
	}
	chip->cmd_ctrl(mtd, NAND_CMD_NONE, NAND_NCE | NAND_CTRL_CHANGE);

	/*
<<<<<<< HEAD
<<<<<<< HEAD
	 * Program and erase have their own busy handlers status and sequential
	 * in needs no delay
=======
	 * program and erase have their own busy handlers
	 * status and sequential in needs no delay
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * program and erase have their own busy handlers
	 * status and sequential in needs no delay
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	switch (command) {

	case NAND_CMD_PAGEPROG:
	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_STATUS:
		return;

	case NAND_CMD_RESET:
		if (chip->dev_ready)
			break;
		udelay(chip->chip_delay);
		chip->cmd_ctrl(mtd, NAND_CMD_STATUS,
			       NAND_CTRL_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd,
			       NAND_CMD_NONE, NAND_NCE | NAND_CTRL_CHANGE);
		while (!(chip->read_byte(mtd) & NAND_STATUS_READY))
				;
		return;

		/* This applies to read commands */
	default:
		/*
		 * If we don't have access to the busy pin, we apply the given
		 * command delay
		 */
		if (!chip->dev_ready) {
			udelay(chip->chip_delay);
			return;
		}
	}
<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine.
	 */
=======
	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ndelay(100);

	nand_wait_ready(mtd);
}

/**
 * nand_command_lp - [DEFAULT] Send command to NAND large page device
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @command: the command to be sent
 * @column: the column address for this command, -1 if none
 * @page_addr: the page address for this command, -1 if none
 *
 * Send command to NAND device. This is the version for the new large page
 * devices. We don't have the separate regions as we have in the small page
 * devices. We must emulate NAND_CMD_READOOB to keep the code compatible.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @command:	the command to be sent
 * @column:	the column address for this command, -1 if none
 * @page_addr:	the page address for this command, -1 if none
 *
 * Send command to NAND device. This is the version for the new large page
 * devices We dont have the separate regions as we have in the small page
 * devices.  We must emulate NAND_CMD_READOOB to keep the code compatible.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_command_lp(struct mtd_info *mtd, unsigned int command,
			    int column, int page_addr)
{
	register struct nand_chip *chip = mtd->priv;

	/* Emulate NAND_CMD_READOOB */
	if (command == NAND_CMD_READOOB) {
		column += mtd->writesize;
		command = NAND_CMD_READ0;
	}

	/* Command latch cycle */
	chip->cmd_ctrl(mtd, command & 0xff,
		       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);

	if (column != -1 || page_addr != -1) {
		int ctrl = NAND_CTRL_CHANGE | NAND_NCE | NAND_ALE;

		/* Serially input address */
		if (column != -1) {
			/* Adjust columns for 16 bit buswidth */
			if (chip->options & NAND_BUSWIDTH_16)
				column >>= 1;
			chip->cmd_ctrl(mtd, column, ctrl);
			ctrl &= ~NAND_CTRL_CHANGE;
			chip->cmd_ctrl(mtd, column >> 8, ctrl);
		}
		if (page_addr != -1) {
			chip->cmd_ctrl(mtd, page_addr, ctrl);
			chip->cmd_ctrl(mtd, page_addr >> 8,
				       NAND_NCE | NAND_ALE);
			/* One more address cycle for devices > 128MiB */
			if (chip->chipsize > (128 << 20))
				chip->cmd_ctrl(mtd, page_addr >> 16,
					       NAND_NCE | NAND_ALE);
		}
	}
	chip->cmd_ctrl(mtd, NAND_CMD_NONE, NAND_NCE | NAND_CTRL_CHANGE);

	/*
<<<<<<< HEAD
<<<<<<< HEAD
	 * Program and erase have their own busy handlers status, sequential
	 * in, and deplete1 need no delay.
=======
	 * program and erase have their own busy handlers
	 * status, sequential in, and deplete1 need no delay
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * program and erase have their own busy handlers
	 * status, sequential in, and deplete1 need no delay
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	switch (command) {

	case NAND_CMD_CACHEDPROG:
	case NAND_CMD_PAGEPROG:
	case NAND_CMD_ERASE1:
	case NAND_CMD_ERASE2:
	case NAND_CMD_SEQIN:
	case NAND_CMD_RNDIN:
	case NAND_CMD_STATUS:
	case NAND_CMD_DEPLETE1:
		return;

<<<<<<< HEAD
<<<<<<< HEAD
=======
		/*
		 * read error status commands require only a short delay
		 */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/*
		 * read error status commands require only a short delay
		 */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case NAND_CMD_STATUS_ERROR:
	case NAND_CMD_STATUS_ERROR0:
	case NAND_CMD_STATUS_ERROR1:
	case NAND_CMD_STATUS_ERROR2:
	case NAND_CMD_STATUS_ERROR3:
<<<<<<< HEAD
<<<<<<< HEAD
		/* Read error status commands require only a short delay */
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		udelay(chip->chip_delay);
		return;

	case NAND_CMD_RESET:
		if (chip->dev_ready)
			break;
		udelay(chip->chip_delay);
		chip->cmd_ctrl(mtd, NAND_CMD_STATUS,
			       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE,
			       NAND_NCE | NAND_CTRL_CHANGE);
		while (!(chip->read_byte(mtd) & NAND_STATUS_READY))
				;
		return;

	case NAND_CMD_RNDOUT:
		/* No ready / busy check necessary */
		chip->cmd_ctrl(mtd, NAND_CMD_RNDOUTSTART,
			       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE,
			       NAND_NCE | NAND_CTRL_CHANGE);
		return;

	case NAND_CMD_READ0:
		chip->cmd_ctrl(mtd, NAND_CMD_READSTART,
			       NAND_NCE | NAND_CLE | NAND_CTRL_CHANGE);
		chip->cmd_ctrl(mtd, NAND_CMD_NONE,
			       NAND_NCE | NAND_CTRL_CHANGE);

		/* This applies to read commands */
	default:
		/*
		 * If we don't have access to the busy pin, we apply the given
<<<<<<< HEAD
<<<<<<< HEAD
		 * command delay.
=======
		 * command delay
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		 * command delay
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 */
		if (!chip->dev_ready) {
			udelay(chip->chip_delay);
			return;
		}
	}

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine.
	 */
=======
	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ndelay(100);

	nand_wait_ready(mtd);
}

/**
 * panic_nand_get_device - [GENERIC] Get chip for selected access
<<<<<<< HEAD
<<<<<<< HEAD
 * @chip: the nand chip descriptor
 * @mtd: MTD device structure
 * @new_state: the state which is requested
=======
 * @chip:	the nand chip descriptor
 * @mtd:	MTD device structure
 * @new_state:	the state which is requested
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @chip:	the nand chip descriptor
 * @mtd:	MTD device structure
 * @new_state:	the state which is requested
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Used when in panic, no locks are taken.
 */
static void panic_nand_get_device(struct nand_chip *chip,
		      struct mtd_info *mtd, int new_state)
{
<<<<<<< HEAD
<<<<<<< HEAD
	/* Hardware controller shared among independent devices */
=======
	/* Hardware controller shared among independend devices */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Hardware controller shared among independend devices */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	chip->controller->active = chip;
	chip->state = new_state;
}

/**
 * nand_get_device - [GENERIC] Get chip for selected access
<<<<<<< HEAD
<<<<<<< HEAD
 * @chip: the nand chip descriptor
 * @mtd: MTD device structure
 * @new_state: the state which is requested
=======
 * @chip:	the nand chip descriptor
 * @mtd:	MTD device structure
 * @new_state:	the state which is requested
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @chip:	the nand chip descriptor
 * @mtd:	MTD device structure
 * @new_state:	the state which is requested
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Get the device and lock it for exclusive access
 */
static int
nand_get_device(struct nand_chip *chip, struct mtd_info *mtd, int new_state)
{
	spinlock_t *lock = &chip->controller->lock;
	wait_queue_head_t *wq = &chip->controller->wq;
	DECLARE_WAITQUEUE(wait, current);
retry:
	spin_lock(lock);

	/* Hardware controller shared among independent devices */
	if (!chip->controller->active)
		chip->controller->active = chip;

	if (chip->controller->active == chip && chip->state == FL_READY) {
		chip->state = new_state;
		spin_unlock(lock);
		return 0;
	}
	if (new_state == FL_PM_SUSPENDED) {
		if (chip->controller->active->state == FL_PM_SUSPENDED) {
			chip->state = FL_PM_SUSPENDED;
			spin_unlock(lock);
			return 0;
		}
	}
	set_current_state(TASK_UNINTERRUPTIBLE);
	add_wait_queue(wq, &wait);
	spin_unlock(lock);
	schedule();
	remove_wait_queue(wq, &wait);
	goto retry;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * panic_nand_wait - [GENERIC] wait until the command is done
 * @mtd: MTD device structure
 * @chip: NAND chip structure
 * @timeo: timeout
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * panic_nand_wait - [GENERIC]  wait until the command is done
 * @mtd:	MTD device structure
 * @chip:	NAND chip structure
 * @timeo:	Timeout
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Wait for command done. This is a helper function for nand_wait used when
 * we are in interrupt context. May happen when in panic and trying to write
 * an oops through mtdoops.
 */
static void panic_nand_wait(struct mtd_info *mtd, struct nand_chip *chip,
			    unsigned long timeo)
{
	int i;
	for (i = 0; i < timeo; i++) {
		if (chip->dev_ready) {
			if (chip->dev_ready(mtd))
				break;
		} else {
			if (chip->read_byte(mtd) & NAND_STATUS_READY)
				break;
		}
		mdelay(1);
	}
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_wait - [DEFAULT] wait until the command is done
 * @mtd: MTD device structure
 * @chip: NAND chip structure
 *
 * Wait for command done. This applies to erase and program only. Erase can
 * take up to 400ms and program up to 20ms according to general NAND and
 * SmartMedia specs.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_wait - [DEFAULT]  wait until the command is done
 * @mtd:	MTD device structure
 * @chip:	NAND chip structure
 *
 * Wait for command done. This applies to erase and program only
 * Erase can take up to 400ms and program up to 20ms according to
 * general NAND and SmartMedia specs
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_wait(struct mtd_info *mtd, struct nand_chip *chip)
{

	unsigned long timeo = jiffies;
	int status, state = chip->state;

	if (state == FL_ERASING)
		timeo += (HZ * 400) / 1000;
	else
		timeo += (HZ * 20) / 1000;

	led_trigger_event(nand_led_trigger, LED_FULL);

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * Apply this short delay always to ensure that we do wait tWB in any
	 * case on any machine.
	 */
=======
	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Apply this short delay always to ensure that we do wait tWB in
	 * any case on any machine. */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ndelay(100);

	if ((state == FL_ERASING) && (chip->options & NAND_IS_AND))
		chip->cmdfunc(mtd, NAND_CMD_STATUS_MULTI, -1, -1);
	else
		chip->cmdfunc(mtd, NAND_CMD_STATUS, -1, -1);

	if (in_interrupt() || oops_in_progress)
		panic_nand_wait(mtd, chip, timeo);
	else {
		while (time_before(jiffies, timeo)) {
			if (chip->dev_ready) {
				if (chip->dev_ready(mtd))
					break;
			} else {
				if (chip->read_byte(mtd) & NAND_STATUS_READY)
					break;
			}
			cond_resched();
		}
	}
	led_trigger_event(nand_led_trigger, LED_OFF);

	status = (int)chip->read_byte(mtd);
	return status;
}

/**
 * __nand_unlock - [REPLACEABLE] unlocks specified locked blocks
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: mtd info
 * @ofs: offset to start unlock from
 * @len: length to unlock
 * @invert: when = 0, unlock the range of blocks within the lower and
 *                    upper boundary address
 *          when = 1, unlock the range of blocks outside the boundaries
 *                    of the lower and upper boundary address
 *
 * Returs unlock status.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * @mtd: mtd info
 * @ofs: offset to start unlock from
 * @len: length to unlock
 * @invert:   when = 0, unlock the range of blocks within the lower and
 *                      upper boundary address
 *            when = 1, unlock the range of blocks outside the boundaries
 *                      of the lower and upper boundary address
 *
 * return - unlock status
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int __nand_unlock(struct mtd_info *mtd, loff_t ofs,
					uint64_t len, int invert)
{
	int ret = 0;
	int status, page;
	struct nand_chip *chip = mtd->priv;

	/* Submit address of first page to unlock */
	page = ofs >> chip->page_shift;
	chip->cmdfunc(mtd, NAND_CMD_UNLOCK1, -1, page & chip->pagemask);

	/* Submit address of last page to unlock */
	page = (ofs + len) >> chip->page_shift;
	chip->cmdfunc(mtd, NAND_CMD_UNLOCK2, -1,
				(page | invert) & chip->pagemask);

	/* Call wait ready function */
	status = chip->waitfunc(mtd, chip);
<<<<<<< HEAD
<<<<<<< HEAD
	/* See if device thinks it succeeded */
	if (status & 0x01) {
		pr_debug("%s: error status = 0x%08x\n",
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	udelay(1000);
	/* See if device thinks it succeeded */
	if (status & 0x01) {
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Error status = 0x%08x\n",
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					__func__, status);
		ret = -EIO;
	}

	return ret;
}

/**
 * nand_unlock - [REPLACEABLE] unlocks specified locked blocks
<<<<<<< HEAD
<<<<<<< HEAD
=======
 *
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 *
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd: mtd info
 * @ofs: offset to start unlock from
 * @len: length to unlock
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * Returns unlock status.
=======
 * return - unlock status
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * return - unlock status
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
int nand_unlock(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	int ret = 0;
	int chipnr;
	struct nand_chip *chip = mtd->priv;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("%s: start = 0x%012llx, len = %llu\n",
=======
	DEBUG(MTD_DEBUG_LEVEL3, "%s: start = 0x%012llx, len = %llu\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	DEBUG(MTD_DEBUG_LEVEL3, "%s: start = 0x%012llx, len = %llu\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			__func__, (unsigned long long)ofs, len);

	if (check_offs_len(mtd, ofs, len))
		ret = -EINVAL;

	/* Align to last block address if size addresses end of the device */
	if (ofs + len == mtd->size)
		len -= mtd->erasesize;

	nand_get_device(chip, mtd, FL_UNLOCKING);

	/* Shift to get chip number */
	chipnr = ofs >> chip->chip_shift;

	chip->select_chip(mtd, chipnr);

	/* Check, if it is write protected */
	if (nand_check_wp(mtd)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: device is write protected!\n",
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Device is write protected!!!\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Device is write protected!!!\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					__func__);
		ret = -EIO;
		goto out;
	}

	ret = __nand_unlock(mtd, ofs, len, 0);

out:
	nand_release_device(mtd);

	return ret;
}
EXPORT_SYMBOL(nand_unlock);

/**
 * nand_lock - [REPLACEABLE] locks all blocks present in the device
<<<<<<< HEAD
<<<<<<< HEAD
=======
 *
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 *
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd: mtd info
 * @ofs: offset to start unlock from
 * @len: length to unlock
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * This feature is not supported in many NAND parts. 'Micron' NAND parts do
 * have this feature, but it allows only to lock all blocks, not for specified
 * range for block. Implementing 'lock' feature by making use of 'unlock', for
 * now.
 *
 * Returns lock status.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * return - lock status
 *
 * This feature is not supported in many NAND parts. 'Micron' NAND parts
 * do have this feature, but it allows only to lock all blocks, not for
 * specified range for block.
 *
 * Implementing 'lock' feature by making use of 'unlock', for now.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
int nand_lock(struct mtd_info *mtd, loff_t ofs, uint64_t len)
{
	int ret = 0;
	int chipnr, status, page;
	struct nand_chip *chip = mtd->priv;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("%s: start = 0x%012llx, len = %llu\n",
=======
	DEBUG(MTD_DEBUG_LEVEL3, "%s: start = 0x%012llx, len = %llu\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	DEBUG(MTD_DEBUG_LEVEL3, "%s: start = 0x%012llx, len = %llu\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			__func__, (unsigned long long)ofs, len);

	if (check_offs_len(mtd, ofs, len))
		ret = -EINVAL;

	nand_get_device(chip, mtd, FL_LOCKING);

	/* Shift to get chip number */
	chipnr = ofs >> chip->chip_shift;

	chip->select_chip(mtd, chipnr);

	/* Check, if it is write protected */
	if (nand_check_wp(mtd)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: device is write protected!\n",
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Device is write protected!!!\n",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Device is write protected!!!\n",
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					__func__);
		status = MTD_ERASE_FAILED;
		ret = -EIO;
		goto out;
	}

	/* Submit address of first page to lock */
	page = ofs >> chip->page_shift;
	chip->cmdfunc(mtd, NAND_CMD_LOCK, -1, page & chip->pagemask);

	/* Call wait ready function */
	status = chip->waitfunc(mtd, chip);
<<<<<<< HEAD
<<<<<<< HEAD
	/* See if device thinks it succeeded */
	if (status & 0x01) {
		pr_debug("%s: error status = 0x%08x\n",
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	udelay(1000);
	/* See if device thinks it succeeded */
	if (status & 0x01) {
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Error status = 0x%08x\n",
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
					__func__, status);
		ret = -EIO;
		goto out;
	}

	ret = __nand_unlock(mtd, ofs, len, 0x1);

out:
	nand_release_device(mtd);

	return ret;
}
EXPORT_SYMBOL(nand_lock);

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_page_raw - [INTERN] read raw page data without ecc
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @page: page number to read
 *
 * Not for syndrome calculating ECC controllers, which use a special oob layout.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_read_page_raw - [Intern] read raw page data without ecc
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	buffer to store read data
 * @page:	page number to read
 *
 * Not for syndrome calculating ecc controllers, which use a special oob layout
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read_page_raw(struct mtd_info *mtd, struct nand_chip *chip,
			      uint8_t *buf, int page)
{
	chip->read_buf(mtd, buf, mtd->writesize);
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);
	return 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_page_raw_syndrome - [INTERN] read raw page data without ecc
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @page: page number to read
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_read_page_raw_syndrome - [Intern] read raw page data without ecc
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	buffer to store read data
 * @page:	page number to read
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * We need a special oob layout and handling even when OOB isn't used.
 */
static int nand_read_page_raw_syndrome(struct mtd_info *mtd,
					struct nand_chip *chip,
					uint8_t *buf, int page)
{
	int eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	uint8_t *oob = chip->oob_poi;
	int steps, size;

	for (steps = chip->ecc.steps; steps > 0; steps--) {
		chip->read_buf(mtd, buf, eccsize);
		buf += eccsize;

		if (chip->ecc.prepad) {
			chip->read_buf(mtd, oob, chip->ecc.prepad);
			oob += chip->ecc.prepad;
		}

		chip->read_buf(mtd, oob, eccbytes);
		oob += eccbytes;

		if (chip->ecc.postpad) {
			chip->read_buf(mtd, oob, chip->ecc.postpad);
			oob += chip->ecc.postpad;
		}
	}

	size = mtd->oobsize - (oob - chip->oob_poi);
	if (size)
		chip->read_buf(mtd, oob, size);

	return 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_page_swecc - [REPLACEABLE] software ECC based page read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @page: page number to read
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_read_page_swecc - [REPLACABLE] software ecc based page read function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	buffer to store read data
 * @page:	page number to read
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read_page_swecc(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	uint8_t *ecc_code = chip->buffers->ecccode;
	uint32_t *eccpos = chip->ecc.layout->eccpos;

	chip->ecc.read_page_raw(mtd, chip, buf, page);

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);

	for (i = 0; i < chip->ecc.total; i++)
		ecc_code[i] = chip->oob_poi[eccpos[i]];

	eccsteps = chip->ecc.steps;
	p = buf;

	for (i = 0 ; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		stat = chip->ecc.correct(mtd, p, &ecc_code[i], &ecc_calc[i]);
		if (stat < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;
	}
	return 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_subpage - [REPLACEABLE] software ECC based sub-page read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @data_offs: offset of requested data within the page
 * @readlen: data length
 * @bufpoi: buffer to store read data
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_read_subpage - [REPLACABLE] software ecc based sub-page read function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @data_offs:	offset of requested data within the page
 * @readlen:	data length
 * @bufpoi:	buffer to store read data
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read_subpage(struct mtd_info *mtd, struct nand_chip *chip,
			uint32_t data_offs, uint32_t readlen, uint8_t *bufpoi)
{
	int start_step, end_step, num_steps;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	uint8_t *p;
	int data_col_addr, i, gaps = 0;
	int datafrag_len, eccfrag_len, aligned_len, aligned_pos;
	int busw = (chip->options & NAND_BUSWIDTH_16) ? 2 : 1;
	int index = 0;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Column address within the page aligned to ECC size (256bytes) */
=======
	/* Column address wihin the page aligned to ECC size (256bytes). */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Column address wihin the page aligned to ECC size (256bytes). */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	start_step = data_offs / chip->ecc.size;
	end_step = (data_offs + readlen - 1) / chip->ecc.size;
	num_steps = end_step - start_step + 1;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Data size aligned to ECC ecc.size */
=======
	/* Data size aligned to ECC ecc.size*/
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Data size aligned to ECC ecc.size*/
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	datafrag_len = num_steps * chip->ecc.size;
	eccfrag_len = num_steps * chip->ecc.bytes;

	data_col_addr = start_step * chip->ecc.size;
	/* If we read not a page aligned data */
	if (data_col_addr != 0)
		chip->cmdfunc(mtd, NAND_CMD_RNDOUT, data_col_addr, -1);

	p = bufpoi + data_col_addr;
	chip->read_buf(mtd, p, datafrag_len);

<<<<<<< HEAD
<<<<<<< HEAD
	/* Calculate ECC */
	for (i = 0; i < eccfrag_len ; i += chip->ecc.bytes, p += chip->ecc.size)
		chip->ecc.calculate(mtd, p, &chip->buffers->ecccalc[i]);

	/*
	 * The performance is faster if we position offsets according to
	 * ecc.pos. Let's make sure that there are no gaps in ECC positions.
	 */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Calculate  ECC */
	for (i = 0; i < eccfrag_len ; i += chip->ecc.bytes, p += chip->ecc.size)
		chip->ecc.calculate(mtd, p, &chip->buffers->ecccalc[i]);

	/* The performance is faster if to position offsets
	   according to ecc.pos. Let make sure here that
	   there are no gaps in ecc positions */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	for (i = 0; i < eccfrag_len - 1; i++) {
		if (eccpos[i + start_step * chip->ecc.bytes] + 1 !=
			eccpos[i + start_step * chip->ecc.bytes + 1]) {
			gaps = 1;
			break;
		}
	}
	if (gaps) {
		chip->cmdfunc(mtd, NAND_CMD_RNDOUT, mtd->writesize, -1);
		chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);
	} else {
<<<<<<< HEAD
<<<<<<< HEAD
		/*
		 * Send the command to read the particular ECC bytes take care
		 * about buswidth alignment in read_buf.
		 */
=======
		/* send the command to read the particular ecc bytes */
		/* take care about buswidth alignment in read_buf */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* send the command to read the particular ecc bytes */
		/* take care about buswidth alignment in read_buf */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		index = start_step * chip->ecc.bytes;

		aligned_pos = eccpos[index] & ~(busw - 1);
		aligned_len = eccfrag_len;
		if (eccpos[index] & (busw - 1))
			aligned_len++;
		if (eccpos[index + (num_steps * chip->ecc.bytes)] & (busw - 1))
			aligned_len++;

		chip->cmdfunc(mtd, NAND_CMD_RNDOUT,
					mtd->writesize + aligned_pos, -1);
		chip->read_buf(mtd, &chip->oob_poi[aligned_pos], aligned_len);
	}

	for (i = 0; i < eccfrag_len; i++)
		chip->buffers->ecccode[i] = chip->oob_poi[eccpos[i + index]];

	p = bufpoi + data_col_addr;
	for (i = 0; i < eccfrag_len ; i += chip->ecc.bytes, p += chip->ecc.size) {
		int stat;

		stat = chip->ecc.correct(mtd, p,
			&chip->buffers->ecccode[i], &chip->buffers->ecccalc[i]);
		if (stat < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;
	}
	return 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_page_hwecc - [REPLACEABLE] hardware ECC based page read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @page: page number to read
 *
 * Not for syndrome calculating ECC controllers which need a special oob layout.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_read_page_hwecc - [REPLACABLE] hardware ecc based page read function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	buffer to store read data
 * @page:	page number to read
 *
 * Not for syndrome calculating ecc controllers which need a special oob layout
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	uint8_t *ecc_code = chip->buffers->ecccode;
	uint32_t *eccpos = chip->ecc.layout->eccpos;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		chip->ecc.hwctl(mtd, NAND_ECC_READ);
		chip->read_buf(mtd, p, eccsize);
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);
	}
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);

	for (i = 0; i < chip->ecc.total; i++)
		ecc_code[i] = chip->oob_poi[eccpos[i]];

	eccsteps = chip->ecc.steps;
	p = buf;

	for (i = 0 ; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		stat = chip->ecc.correct(mtd, p, &ecc_code[i], &ecc_calc[i]);
		if (stat < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;
	}
	return 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_page_hwecc_oob_first - [REPLACEABLE] hw ecc, read oob first
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @page: page number to read
 *
 * Hardware ECC for large page chips, require OOB to be read first. For this
 * ECC mode, the write_page method is re-used from ECC_HW. These methods
 * read/write ECC from the OOB area, unlike the ECC_HW_SYNDROME support with
 * multiple ECC steps, follows the "infix ECC" scheme and reads/writes ECC from
 * the data area, by overwriting the NAND manufacturer bad block markings.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_read_page_hwecc_oob_first - [REPLACABLE] hw ecc, read oob first
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	buffer to store read data
 * @page:	page number to read
 *
 * Hardware ECC for large page chips, require OOB to be read first.
 * For this ECC mode, the write_page method is re-used from ECC_HW.
 * These methods read/write ECC from the OOB area, unlike the
 * ECC_HW_SYNDROME support with multiple ECC steps, follows the
 * "infix ECC" scheme and reads/writes ECC from the data area, by
 * overwriting the NAND manufacturer bad block markings.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read_page_hwecc_oob_first(struct mtd_info *mtd,
	struct nand_chip *chip, uint8_t *buf, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	uint8_t *ecc_code = chip->buffers->ecccode;
	uint32_t *eccpos = chip->ecc.layout->eccpos;
	uint8_t *ecc_calc = chip->buffers->ecccalc;

	/* Read the OOB area first */
	chip->cmdfunc(mtd, NAND_CMD_READOOB, 0, page);
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);
	chip->cmdfunc(mtd, NAND_CMD_READ0, 0, page);

	for (i = 0; i < chip->ecc.total; i++)
		ecc_code[i] = chip->oob_poi[eccpos[i]];

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		chip->ecc.hwctl(mtd, NAND_ECC_READ);
		chip->read_buf(mtd, p, eccsize);
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);

		stat = chip->ecc.correct(mtd, p, &ecc_code[i], NULL);
		if (stat < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;
	}
	return 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_page_syndrome - [REPLACEABLE] hardware ECC syndrome based page read
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: buffer to store read data
 * @page: page number to read
 *
 * The hw generator calculates the error syndrome automatically. Therefore we
 * need a special oob layout and handling.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_read_page_syndrome - [REPLACABLE] hardware ecc syndrom based page read
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	buffer to store read data
 * @page:	page number to read
 *
 * The hw generator calculates the error syndrome automatically. Therefor
 * we need a special oob layout and handling.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read_page_syndrome(struct mtd_info *mtd, struct nand_chip *chip,
				   uint8_t *buf, int page)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *p = buf;
	uint8_t *oob = chip->oob_poi;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		int stat;

		chip->ecc.hwctl(mtd, NAND_ECC_READ);
		chip->read_buf(mtd, p, eccsize);

		if (chip->ecc.prepad) {
			chip->read_buf(mtd, oob, chip->ecc.prepad);
			oob += chip->ecc.prepad;
		}

		chip->ecc.hwctl(mtd, NAND_ECC_READSYN);
		chip->read_buf(mtd, oob, eccbytes);
		stat = chip->ecc.correct(mtd, p, oob, NULL);

		if (stat < 0)
			mtd->ecc_stats.failed++;
		else
			mtd->ecc_stats.corrected += stat;

		oob += eccbytes;

		if (chip->ecc.postpad) {
			chip->read_buf(mtd, oob, chip->ecc.postpad);
			oob += chip->ecc.postpad;
		}
	}

	/* Calculate remaining oob bytes */
	i = mtd->oobsize - (oob - chip->oob_poi);
	if (i)
		chip->read_buf(mtd, oob, i);

	return 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_transfer_oob - [INTERN] Transfer oob to client buffer
 * @chip: nand chip structure
 * @oob: oob destination address
 * @ops: oob ops structure
 * @len: size of oob to transfer
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_transfer_oob - [Internal] Transfer oob to client buffer
 * @chip:	nand chip structure
 * @oob:	oob destination address
 * @ops:	oob ops structure
 * @len:	size of oob to transfer
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static uint8_t *nand_transfer_oob(struct nand_chip *chip, uint8_t *oob,
				  struct mtd_oob_ops *ops, size_t len)
{
	switch (ops->mode) {

<<<<<<< HEAD
<<<<<<< HEAD
	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_RAW:
		memcpy(oob, chip->oob_poi + ops->ooboffs, len);
		return oob + len;

	case MTD_OPS_AUTO_OOB: {
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case MTD_OOB_PLACE:
	case MTD_OOB_RAW:
		memcpy(oob, chip->oob_poi + ops->ooboffs, len);
		return oob + len;

	case MTD_OOB_AUTO: {
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		struct nand_oobfree *free = chip->ecc.layout->oobfree;
		uint32_t boffs = 0, roffs = ops->ooboffs;
		size_t bytes = 0;

		for (; free->length && len; free++, len -= bytes) {
<<<<<<< HEAD
<<<<<<< HEAD
			/* Read request not from offset 0? */
=======
			/* Read request not from offset 0 ? */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			/* Read request not from offset 0 ? */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (unlikely(roffs)) {
				if (roffs >= free->length) {
					roffs -= free->length;
					continue;
				}
				boffs = free->offset + roffs;
				bytes = min_t(size_t, len,
					      (free->length - roffs));
				roffs = 0;
			} else {
				bytes = min_t(size_t, len, free->length);
				boffs = free->offset;
			}
			memcpy(oob, chip->oob_poi + boffs, bytes);
			oob += bytes;
		}
		return oob;
	}
	default:
		BUG();
	}
	return NULL;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_do_read_ops - [INTERN] Read data with ECC
 * @mtd: MTD device structure
 * @from: offset to read from
 * @ops: oob ops structure
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_do_read_ops - [Internal] Read data with ECC
 *
 * @mtd:	MTD device structure
 * @from:	offset to read from
 * @ops:	oob ops structure
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Internal function. Called with chip held.
 */
static int nand_do_read_ops(struct mtd_info *mtd, loff_t from,
			    struct mtd_oob_ops *ops)
{
	int chipnr, page, realpage, col, bytes, aligned;
	struct nand_chip *chip = mtd->priv;
	struct mtd_ecc_stats stats;
	int blkcheck = (1 << (chip->phys_erase_shift - chip->page_shift)) - 1;
	int sndcmd = 1;
	int ret = 0;
	uint32_t readlen = ops->len;
	uint32_t oobreadlen = ops->ooblen;
<<<<<<< HEAD
<<<<<<< HEAD
	uint32_t max_oobsize = ops->mode == MTD_OPS_AUTO_OOB ?
=======
	uint32_t max_oobsize = ops->mode == MTD_OOB_AUTO ?
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	uint32_t max_oobsize = ops->mode == MTD_OOB_AUTO ?
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		mtd->oobavail : mtd->oobsize;

	uint8_t *bufpoi, *oob, *buf;

	stats = mtd->ecc_stats;

	chipnr = (int)(from >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);

	realpage = (int)(from >> chip->page_shift);
	page = realpage & chip->pagemask;

	col = (int)(from & (mtd->writesize - 1));

	buf = ops->datbuf;
	oob = ops->oobbuf;

	while (1) {
		bytes = min(mtd->writesize - col, readlen);
		aligned = (bytes == mtd->writesize);

<<<<<<< HEAD
<<<<<<< HEAD
		/* Is the current page in the buffer? */
=======
		/* Is the current page in the buffer ? */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* Is the current page in the buffer ? */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (realpage != chip->pagebuf || oob) {
			bufpoi = aligned ? buf : chip->buffers->databuf;

			if (likely(sndcmd)) {
				chip->cmdfunc(mtd, NAND_CMD_READ0, 0x00, page);
				sndcmd = 0;
			}

			/* Now read the page into the buffer */
<<<<<<< HEAD
<<<<<<< HEAD
			if (unlikely(ops->mode == MTD_OPS_RAW))
=======
			if (unlikely(ops->mode == MTD_OOB_RAW))
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			if (unlikely(ops->mode == MTD_OOB_RAW))
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				ret = chip->ecc.read_page_raw(mtd, chip,
							      bufpoi, page);
			else if (!aligned && NAND_SUBPAGE_READ(chip) && !oob)
				ret = chip->ecc.read_subpage(mtd, chip,
							col, bytes, bufpoi);
			else
				ret = chip->ecc.read_page(mtd, chip, bufpoi,
							  page);
<<<<<<< HEAD
<<<<<<< HEAD
			if (ret < 0) {
				if (!aligned)
					/* Invalidate page cache */
					chip->pagebuf = -1;
				break;
			}
=======
			if (ret < 0)
				break;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			if (ret < 0)
				break;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

			/* Transfer not aligned data */
			if (!aligned) {
				if (!NAND_SUBPAGE_READ(chip) && !oob &&
<<<<<<< HEAD
<<<<<<< HEAD
				    !(mtd->ecc_stats.failed - stats.failed) &&
				    (ops->mode != MTD_OPS_RAW))
					chip->pagebuf = realpage;
				else
					/* Invalidate page cache */
					chip->pagebuf = -1;
=======
				    !(mtd->ecc_stats.failed - stats.failed))
					chip->pagebuf = realpage;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				    !(mtd->ecc_stats.failed - stats.failed))
					chip->pagebuf = realpage;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				memcpy(buf, chip->buffers->databuf + col, bytes);
			}

			buf += bytes;

			if (unlikely(oob)) {

				int toread = min(oobreadlen, max_oobsize);

				if (toread) {
					oob = nand_transfer_oob(chip,
						oob, ops, toread);
					oobreadlen -= toread;
				}
			}

			if (!(chip->options & NAND_NO_READRDY)) {
				/*
				 * Apply delay or wait for ready/busy pin. Do
				 * this before the AUTOINCR check, so no
				 * problems arise if a chip which does auto
				 * increment is marked as NOAUTOINCR by the
				 * board driver.
				 */
				if (!chip->dev_ready)
					udelay(chip->chip_delay);
				else
					nand_wait_ready(mtd);
			}
		} else {
			memcpy(buf, chip->buffers->databuf + col, bytes);
			buf += bytes;
		}

		readlen -= bytes;

		if (!readlen)
			break;

<<<<<<< HEAD
<<<<<<< HEAD
		/* For subsequent reads align to page boundary */
=======
		/* For subsequent reads align to page boundary. */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* For subsequent reads align to page boundary. */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		col = 0;
		/* Increment page address */
		realpage++;

		page = realpage & chip->pagemask;
		/* Check, if we cross a chip boundary */
		if (!page) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}

<<<<<<< HEAD
<<<<<<< HEAD
		/*
		 * Check, if the chip supports auto page increment or if we
		 * have hit a block boundary.
=======
		/* Check, if the chip supports auto page increment
		 * or if we have hit a block boundary.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* Check, if the chip supports auto page increment
		 * or if we have hit a block boundary.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 */
		if (!NAND_CANAUTOINCR(chip) || !(page & blkcheck))
			sndcmd = 1;
	}

	ops->retlen = ops->len - (size_t) readlen;
	if (oob)
		ops->oobretlen = ops->ooblen - oobreadlen;

	if (ret)
		return ret;

	if (mtd->ecc_stats.failed - stats.failed)
		return -EBADMSG;

	return  mtd->ecc_stats.corrected - stats.corrected ? -EUCLEAN : 0;
}

/**
 * nand_read - [MTD Interface] MTD compatibility function for nand_do_read_ecc
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @from: offset to read from
 * @len: number of bytes to read
 * @retlen: pointer to variable to store the number of read bytes
 * @buf: the databuffer to put data
 *
 * Get hold of the chip and call nand_do_read.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @from:	offset to read from
 * @len:	number of bytes to read
 * @retlen:	pointer to variable to store the number of read bytes
 * @buf:	the databuffer to put data
 *
 * Get hold of the chip and call nand_do_read
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read(struct mtd_info *mtd, loff_t from, size_t len,
		     size_t *retlen, uint8_t *buf)
{
	struct nand_chip *chip = mtd->priv;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mtd_oob_ops ops;
	int ret;

	nand_get_device(chip, mtd, FL_READING);
	ops.len = len;
	ops.datbuf = buf;
	ops.oobbuf = NULL;
	ops.mode = 0;
	ret = nand_do_read_ops(mtd, from, &ops);
	*retlen = ops.retlen;
	nand_release_device(mtd);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret;

	/* Do not allow reads past end of device */
	if ((from + len) > mtd->size)
		return -EINVAL;
	if (!len)
		return 0;

	nand_get_device(chip, mtd, FL_READING);

	chip->ops.len = len;
	chip->ops.datbuf = buf;
	chip->ops.oobbuf = NULL;

	ret = nand_do_read_ops(mtd, from, &chip->ops);

	*retlen = chip->ops.retlen;

	nand_release_device(mtd);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_oob_std - [REPLACEABLE] the most common OOB data read function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to read
 * @sndcmd: flag whether to issue read command or not
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_read_oob_std - [REPLACABLE] the most common OOB data read function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @page:	page number to read
 * @sndcmd:	flag whether to issue read command or not
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read_oob_std(struct mtd_info *mtd, struct nand_chip *chip,
			     int page, int sndcmd)
{
	if (sndcmd) {
		chip->cmdfunc(mtd, NAND_CMD_READOOB, 0, page);
		sndcmd = 0;
	}
	chip->read_buf(mtd, chip->oob_poi, mtd->oobsize);
	return sndcmd;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_read_oob_syndrome - [REPLACEABLE] OOB data read function for HW ECC
 *			    with syndromes
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to read
 * @sndcmd: flag whether to issue read command or not
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_read_oob_syndrome - [REPLACABLE] OOB data read function for HW ECC
 *			    with syndromes
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @page:	page number to read
 * @sndcmd:	flag whether to issue read command or not
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read_oob_syndrome(struct mtd_info *mtd, struct nand_chip *chip,
				  int page, int sndcmd)
{
	uint8_t *buf = chip->oob_poi;
	int length = mtd->oobsize;
	int chunk = chip->ecc.bytes + chip->ecc.prepad + chip->ecc.postpad;
	int eccsize = chip->ecc.size;
	uint8_t *bufpoi = buf;
	int i, toread, sndrnd = 0, pos;

	chip->cmdfunc(mtd, NAND_CMD_READ0, chip->ecc.size, page);
	for (i = 0; i < chip->ecc.steps; i++) {
		if (sndrnd) {
			pos = eccsize + i * (eccsize + chunk);
			if (mtd->writesize > 512)
				chip->cmdfunc(mtd, NAND_CMD_RNDOUT, pos, -1);
			else
				chip->cmdfunc(mtd, NAND_CMD_READ0, pos, page);
		} else
			sndrnd = 1;
		toread = min_t(int, length, chunk);
		chip->read_buf(mtd, bufpoi, toread);
		bufpoi += toread;
		length -= toread;
	}
	if (length > 0)
		chip->read_buf(mtd, bufpoi, length);

	return 1;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_write_oob_std - [REPLACEABLE] the most common OOB data write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to write
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_write_oob_std - [REPLACABLE] the most common OOB data write function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @page:	page number to write
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_write_oob_std(struct mtd_info *mtd, struct nand_chip *chip,
			      int page)
{
	int status = 0;
	const uint8_t *buf = chip->oob_poi;
	int length = mtd->oobsize;

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, mtd->writesize, page);
	chip->write_buf(mtd, buf, length);
	/* Send command to program the OOB data */
	chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);

	status = chip->waitfunc(mtd, chip);

	return status & NAND_STATUS_FAIL ? -EIO : 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_write_oob_syndrome - [REPLACEABLE] OOB data write function for HW ECC
 *			     with syndrome - only for large page flash
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @page: page number to write
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_write_oob_syndrome - [REPLACABLE] OOB data write function for HW ECC
 *			     with syndrome - only for large page flash !
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @page:	page number to write
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_write_oob_syndrome(struct mtd_info *mtd,
				   struct nand_chip *chip, int page)
{
	int chunk = chip->ecc.bytes + chip->ecc.prepad + chip->ecc.postpad;
	int eccsize = chip->ecc.size, length = mtd->oobsize;
	int i, len, pos, status = 0, sndcmd = 0, steps = chip->ecc.steps;
	const uint8_t *bufpoi = chip->oob_poi;

	/*
	 * data-ecc-data-ecc ... ecc-oob
	 * or
	 * data-pad-ecc-pad-data-pad .... ecc-pad-oob
	 */
	if (!chip->ecc.prepad && !chip->ecc.postpad) {
		pos = steps * (eccsize + chunk);
		steps = 0;
	} else
		pos = eccsize;

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, pos, page);
	for (i = 0; i < steps; i++) {
		if (sndcmd) {
			if (mtd->writesize <= 512) {
				uint32_t fill = 0xFFFFFFFF;

				len = eccsize;
				while (len > 0) {
					int num = min_t(int, len, 4);
					chip->write_buf(mtd, (uint8_t *)&fill,
							num);
					len -= num;
				}
			} else {
				pos = eccsize + i * (eccsize + chunk);
				chip->cmdfunc(mtd, NAND_CMD_RNDIN, pos, -1);
			}
		} else
			sndcmd = 1;
		len = min_t(int, length, chunk);
		chip->write_buf(mtd, bufpoi, len);
		bufpoi += len;
		length -= len;
	}
	if (length > 0)
		chip->write_buf(mtd, bufpoi, length);

	chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
	status = chip->waitfunc(mtd, chip);

	return status & NAND_STATUS_FAIL ? -EIO : 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_do_read_oob - [INTERN] NAND read out-of-band
 * @mtd: MTD device structure
 * @from: offset to read from
 * @ops: oob operations description structure
 *
 * NAND read out-of-band data from the spare area.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_do_read_oob - [Intern] NAND read out-of-band
 * @mtd:	MTD device structure
 * @from:	offset to read from
 * @ops:	oob operations description structure
 *
 * NAND read out-of-band data from the spare area
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_do_read_oob(struct mtd_info *mtd, loff_t from,
			    struct mtd_oob_ops *ops)
{
	int page, realpage, chipnr, sndcmd = 1;
	struct nand_chip *chip = mtd->priv;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mtd_ecc_stats stats;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int blkcheck = (1 << (chip->phys_erase_shift - chip->page_shift)) - 1;
	int readlen = ops->ooblen;
	int len;
	uint8_t *buf = ops->oobbuf;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("%s: from = 0x%08Lx, len = %i\n",
			__func__, (unsigned long long)from, readlen);

	stats = mtd->ecc_stats;

	if (ops->mode == MTD_OPS_AUTO_OOB)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	DEBUG(MTD_DEBUG_LEVEL3, "%s: from = 0x%08Lx, len = %i\n",
			__func__, (unsigned long long)from, readlen);

	if (ops->mode == MTD_OOB_AUTO)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		len = chip->ecc.layout->oobavail;
	else
		len = mtd->oobsize;

	if (unlikely(ops->ooboffs >= len)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: attempt to start read outside oob\n",
				__func__);
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt to start read "
					"outside oob\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt to start read "
					"outside oob\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	/* Do not allow reads past end of device */
	if (unlikely(from >= mtd->size ||
		     ops->ooboffs + readlen > ((mtd->size >> chip->page_shift) -
					(from >> chip->page_shift)) * len)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: attempt to read beyond end of device\n",
				__func__);
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt read beyond end "
					"of device\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt read beyond end "
					"of device\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	chipnr = (int)(from >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);

	/* Shift to get page */
	realpage = (int)(from >> chip->page_shift);
	page = realpage & chip->pagemask;

	while (1) {
<<<<<<< HEAD
<<<<<<< HEAD
		if (ops->mode == MTD_OPS_RAW)
			sndcmd = chip->ecc.read_oob_raw(mtd, chip, page, sndcmd);
		else
			sndcmd = chip->ecc.read_oob(mtd, chip, page, sndcmd);
=======
		sndcmd = chip->ecc.read_oob(mtd, chip, page, sndcmd);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		sndcmd = chip->ecc.read_oob(mtd, chip, page, sndcmd);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

		len = min(len, readlen);
		buf = nand_transfer_oob(chip, buf, ops, len);

		if (!(chip->options & NAND_NO_READRDY)) {
			/*
			 * Apply delay or wait for ready/busy pin. Do this
			 * before the AUTOINCR check, so no problems arise if a
			 * chip which does auto increment is marked as
			 * NOAUTOINCR by the board driver.
			 */
			if (!chip->dev_ready)
				udelay(chip->chip_delay);
			else
				nand_wait_ready(mtd);
		}

		readlen -= len;
		if (!readlen)
			break;

		/* Increment page address */
		realpage++;

		page = realpage & chip->pagemask;
		/* Check, if we cross a chip boundary */
		if (!page) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}

<<<<<<< HEAD
<<<<<<< HEAD
		/*
		 * Check, if the chip supports auto page increment or if we
		 * have hit a block boundary.
=======
		/* Check, if the chip supports auto page increment
		 * or if we have hit a block boundary.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* Check, if the chip supports auto page increment
		 * or if we have hit a block boundary.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 */
		if (!NAND_CANAUTOINCR(chip) || !(page & blkcheck))
			sndcmd = 1;
	}

	ops->oobretlen = ops->ooblen;
<<<<<<< HEAD
<<<<<<< HEAD

	if (mtd->ecc_stats.failed - stats.failed)
		return -EBADMSG;

	return  mtd->ecc_stats.corrected - stats.corrected ? -EUCLEAN : 0;
=======
	return 0;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return 0;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/**
 * nand_read_oob - [MTD Interface] NAND read data and/or out-of-band
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @from: offset to read from
 * @ops: oob operation description structure
 *
 * NAND read data and/or out-of-band data.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @from:	offset to read from
 * @ops:	oob operation description structure
 *
 * NAND read data and/or out-of-band data
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_read_oob(struct mtd_info *mtd, loff_t from,
			 struct mtd_oob_ops *ops)
{
	struct nand_chip *chip = mtd->priv;
	int ret = -ENOTSUPP;

	ops->retlen = 0;

	/* Do not allow reads past end of device */
	if (ops->datbuf && (from + ops->len) > mtd->size) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: attempt to read beyond end of device\n",
				__func__);
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt read "
				"beyond end of device\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt read "
				"beyond end of device\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	nand_get_device(chip, mtd, FL_READING);

	switch (ops->mode) {
<<<<<<< HEAD
<<<<<<< HEAD
	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_AUTO_OOB:
	case MTD_OPS_RAW:
=======
	case MTD_OOB_PLACE:
	case MTD_OOB_AUTO:
	case MTD_OOB_RAW:
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	case MTD_OOB_PLACE:
	case MTD_OOB_AUTO:
	case MTD_OOB_RAW:
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;

	default:
		goto out;
	}

	if (!ops->datbuf)
		ret = nand_do_read_oob(mtd, from, ops);
	else
		ret = nand_do_read_ops(mtd, from, ops);

out:
	nand_release_device(mtd);
	return ret;
}


/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_write_page_raw - [INTERN] raw page write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
 *
 * Not for syndrome calculating ECC controllers, which use a special oob layout.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_write_page_raw - [Intern] raw page write function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	data buffer
 *
 * Not for syndrome calculating ecc controllers, which use a special oob layout
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_write_page_raw(struct mtd_info *mtd, struct nand_chip *chip,
				const uint8_t *buf)
{
	chip->write_buf(mtd, buf, mtd->writesize);
	chip->write_buf(mtd, chip->oob_poi, mtd->oobsize);
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_write_page_raw_syndrome - [INTERN] raw page write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_write_page_raw_syndrome - [Intern] raw page write function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	data buffer
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * We need a special oob layout and handling even when ECC isn't checked.
 */
static void nand_write_page_raw_syndrome(struct mtd_info *mtd,
					struct nand_chip *chip,
					const uint8_t *buf)
{
	int eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	uint8_t *oob = chip->oob_poi;
	int steps, size;

	for (steps = chip->ecc.steps; steps > 0; steps--) {
		chip->write_buf(mtd, buf, eccsize);
		buf += eccsize;

		if (chip->ecc.prepad) {
			chip->write_buf(mtd, oob, chip->ecc.prepad);
			oob += chip->ecc.prepad;
		}

		chip->read_buf(mtd, oob, eccbytes);
		oob += eccbytes;

		if (chip->ecc.postpad) {
			chip->write_buf(mtd, oob, chip->ecc.postpad);
			oob += chip->ecc.postpad;
		}
	}

	size = mtd->oobsize - (oob - chip->oob_poi);
	if (size)
		chip->write_buf(mtd, oob, size);
}
/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_write_page_swecc - [REPLACEABLE] software ECC based page write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_write_page_swecc - [REPLACABLE] software ecc based page write function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	data buffer
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_write_page_swecc(struct mtd_info *mtd, struct nand_chip *chip,
				  const uint8_t *buf)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	const uint8_t *p = buf;
	uint32_t *eccpos = chip->ecc.layout->eccpos;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Software ECC calculation */
=======
	/* Software ecc calculation */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Software ecc calculation */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize)
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);

	for (i = 0; i < chip->ecc.total; i++)
		chip->oob_poi[eccpos[i]] = ecc_calc[i];

	chip->ecc.write_page_raw(mtd, chip, buf);
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_write_page_hwecc - [REPLACEABLE] hardware ECC based page write function
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_write_page_hwecc - [REPLACABLE] hardware ecc based page write function
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	data buffer
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_write_page_hwecc(struct mtd_info *mtd, struct nand_chip *chip,
				  const uint8_t *buf)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	uint8_t *ecc_calc = chip->buffers->ecccalc;
	const uint8_t *p = buf;
	uint32_t *eccpos = chip->ecc.layout->eccpos;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {
		chip->ecc.hwctl(mtd, NAND_ECC_WRITE);
		chip->write_buf(mtd, p, eccsize);
		chip->ecc.calculate(mtd, p, &ecc_calc[i]);
	}

	for (i = 0; i < chip->ecc.total; i++)
		chip->oob_poi[eccpos[i]] = ecc_calc[i];

	chip->write_buf(mtd, chip->oob_poi, mtd->oobsize);
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_write_page_syndrome - [REPLACEABLE] hardware ECC syndrome based page write
 * @mtd: mtd info structure
 * @chip: nand chip info structure
 * @buf: data buffer
 *
 * The hw generator calculates the error syndrome automatically. Therefore we
 * need a special oob layout and handling.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_write_page_syndrome - [REPLACABLE] hardware ecc syndrom based page write
 * @mtd:	mtd info structure
 * @chip:	nand chip info structure
 * @buf:	data buffer
 *
 * The hw generator calculates the error syndrome automatically. Therefor
 * we need a special oob layout and handling.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_write_page_syndrome(struct mtd_info *mtd,
				    struct nand_chip *chip, const uint8_t *buf)
{
	int i, eccsize = chip->ecc.size;
	int eccbytes = chip->ecc.bytes;
	int eccsteps = chip->ecc.steps;
	const uint8_t *p = buf;
	uint8_t *oob = chip->oob_poi;

	for (i = 0; eccsteps; eccsteps--, i += eccbytes, p += eccsize) {

		chip->ecc.hwctl(mtd, NAND_ECC_WRITE);
		chip->write_buf(mtd, p, eccsize);

		if (chip->ecc.prepad) {
			chip->write_buf(mtd, oob, chip->ecc.prepad);
			oob += chip->ecc.prepad;
		}

		chip->ecc.calculate(mtd, p, oob);
		chip->write_buf(mtd, oob, eccbytes);
		oob += eccbytes;

		if (chip->ecc.postpad) {
			chip->write_buf(mtd, oob, chip->ecc.postpad);
			oob += chip->ecc.postpad;
		}
	}

	/* Calculate remaining oob bytes */
	i = mtd->oobsize - (oob - chip->oob_poi);
	if (i)
		chip->write_buf(mtd, oob, i);
}

/**
 * nand_write_page - [REPLACEABLE] write one page
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @chip: NAND chip descriptor
 * @buf: the data to write
 * @page: page number to write
 * @cached: cached programming
 * @raw: use _raw version of write_page
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @chip:	NAND chip descriptor
 * @buf:	the data to write
 * @page:	page number to write
 * @cached:	cached programming
 * @raw:	use _raw version of write_page
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_write_page(struct mtd_info *mtd, struct nand_chip *chip,
			   const uint8_t *buf, int page, int cached, int raw)
{
	int status;

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, 0x00, page);

	if (unlikely(raw))
		chip->ecc.write_page_raw(mtd, chip, buf);
	else
		chip->ecc.write_page(mtd, chip, buf);

	/*
<<<<<<< HEAD
<<<<<<< HEAD
	 * Cached progamming disabled for now. Not sure if it's worth the
	 * trouble. The speed gain is not very impressive. (2.3->2.6Mib/s).
=======
	 * Cached progamming disabled for now, Not sure if its worth the
	 * trouble. The speed gain is not very impressive. (2.3->2.6Mib/s)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * Cached progamming disabled for now, Not sure if its worth the
	 * trouble. The speed gain is not very impressive. (2.3->2.6Mib/s)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	cached = 0;

	if (!cached || !(chip->options & NAND_CACHEPRG)) {

		chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
		status = chip->waitfunc(mtd, chip);
		/*
		 * See if operation failed and additional status checks are
<<<<<<< HEAD
<<<<<<< HEAD
		 * available.
=======
		 * available
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		 * available
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 */
		if ((status & NAND_STATUS_FAIL) && (chip->errstat))
			status = chip->errstat(mtd, chip, FL_WRITING, status,
					       page);

		if (status & NAND_STATUS_FAIL)
			return -EIO;
	} else {
		chip->cmdfunc(mtd, NAND_CMD_CACHEDPROG, -1, -1);
		status = chip->waitfunc(mtd, chip);
	}

#ifdef CONFIG_MTD_NAND_VERIFY_WRITE
	/* Send command to read back the data */
	chip->cmdfunc(mtd, NAND_CMD_READ0, 0, page);

	if (chip->verify_buf(mtd, buf, mtd->writesize))
		return -EIO;
#endif
	return 0;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_fill_oob - [INTERN] Transfer client buffer to oob
 * @mtd: MTD device structure
 * @oob: oob data buffer
 * @len: oob data write length
 * @ops: oob ops structure
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_fill_oob - [Internal] Transfer client buffer to oob
 * @mtd:	MTD device structure
 * @oob:	oob data buffer
 * @len:	oob data write length
 * @ops:	oob ops structure
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static uint8_t *nand_fill_oob(struct mtd_info *mtd, uint8_t *oob, size_t len,
			      struct mtd_oob_ops *ops)
{
	struct nand_chip *chip = mtd->priv;

	/*
	 * Initialise to all 0xFF, to avoid the possibility of left over OOB
	 * data from a previous OOB read.
	 */
	memset(chip->oob_poi, 0xff, mtd->oobsize);

	switch (ops->mode) {

<<<<<<< HEAD
<<<<<<< HEAD
	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_RAW:
		memcpy(chip->oob_poi + ops->ooboffs, oob, len);
		return oob + len;

	case MTD_OPS_AUTO_OOB: {
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case MTD_OOB_PLACE:
	case MTD_OOB_RAW:
		memcpy(chip->oob_poi + ops->ooboffs, oob, len);
		return oob + len;

	case MTD_OOB_AUTO: {
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		struct nand_oobfree *free = chip->ecc.layout->oobfree;
		uint32_t boffs = 0, woffs = ops->ooboffs;
		size_t bytes = 0;

		for (; free->length && len; free++, len -= bytes) {
<<<<<<< HEAD
<<<<<<< HEAD
			/* Write request not from offset 0? */
=======
			/* Write request not from offset 0 ? */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			/* Write request not from offset 0 ? */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			if (unlikely(woffs)) {
				if (woffs >= free->length) {
					woffs -= free->length;
					continue;
				}
				boffs = free->offset + woffs;
				bytes = min_t(size_t, len,
					      (free->length - woffs));
				woffs = 0;
			} else {
				bytes = min_t(size_t, len, free->length);
				boffs = free->offset;
			}
			memcpy(chip->oob_poi + boffs, oob, bytes);
			oob += bytes;
		}
		return oob;
	}
	default:
		BUG();
	}
	return NULL;
}

#define NOTALIGNED(x)	((x & (chip->subpagesize - 1)) != 0)

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_do_write_ops - [INTERN] NAND write with ECC
 * @mtd: MTD device structure
 * @to: offset to write to
 * @ops: oob operations description structure
 *
 * NAND write with ECC.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_do_write_ops - [Internal] NAND write with ECC
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @ops:	oob operations description structure
 *
 * NAND write with ECC
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_do_write_ops(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops)
{
	int chipnr, realpage, page, blockmask, column;
	struct nand_chip *chip = mtd->priv;
	uint32_t writelen = ops->len;

	uint32_t oobwritelen = ops->ooblen;
<<<<<<< HEAD
<<<<<<< HEAD
	uint32_t oobmaxlen = ops->mode == MTD_OPS_AUTO_OOB ?
=======
	uint32_t oobmaxlen = ops->mode == MTD_OOB_AUTO ?
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	uint32_t oobmaxlen = ops->mode == MTD_OOB_AUTO ?
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				mtd->oobavail : mtd->oobsize;

	uint8_t *oob = ops->oobbuf;
	uint8_t *buf = ops->datbuf;
	int ret, subpage;

	ops->retlen = 0;
	if (!writelen)
		return 0;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Reject writes, which are not page aligned */
	if (NOTALIGNED(to) || NOTALIGNED(ops->len)) {
		pr_notice("%s: attempt to write non page aligned data\n",
			   __func__);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* reject writes, which are not page aligned */
	if (NOTALIGNED(to) || NOTALIGNED(ops->len)) {
		printk(KERN_NOTICE "%s: Attempt to write not "
				"page aligned data\n", __func__);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	column = to & (mtd->writesize - 1);
	subpage = column || (writelen & (mtd->writesize - 1));

	if (subpage && oob)
		return -EINVAL;

	chipnr = (int)(to >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);

	/* Check, if it is write protected */
	if (nand_check_wp(mtd))
		return -EIO;

	realpage = (int)(to >> chip->page_shift);
	page = realpage & chip->pagemask;
	blockmask = (1 << (chip->phys_erase_shift - chip->page_shift)) - 1;

	/* Invalidate the page cache, when we write to the cached page */
	if (to <= (chip->pagebuf << chip->page_shift) &&
	    (chip->pagebuf << chip->page_shift) < (to + ops->len))
		chip->pagebuf = -1;

	/* Don't allow multipage oob writes with offset */
	if (oob && ops->ooboffs && (ops->ooboffs + ops->ooblen > oobmaxlen))
		return -EINVAL;

	while (1) {
		int bytes = mtd->writesize;
		int cached = writelen > bytes && page != blockmask;
		uint8_t *wbuf = buf;

<<<<<<< HEAD
<<<<<<< HEAD
		/* Partial page write? */
=======
		/* Partial page write ? */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* Partial page write ? */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (unlikely(column || writelen < (mtd->writesize - 1))) {
			cached = 0;
			bytes = min_t(int, bytes - column, (int) writelen);
			chip->pagebuf = -1;
			memset(chip->buffers->databuf, 0xff, mtd->writesize);
			memcpy(&chip->buffers->databuf[column], buf, bytes);
			wbuf = chip->buffers->databuf;
		}

		if (unlikely(oob)) {
			size_t len = min(oobwritelen, oobmaxlen);
			oob = nand_fill_oob(mtd, oob, len, ops);
			oobwritelen -= len;
		} else {
			/* We still need to erase leftover OOB data */
			memset(chip->oob_poi, 0xff, mtd->oobsize);
		}

		ret = chip->write_page(mtd, chip, wbuf, page, cached,
<<<<<<< HEAD
<<<<<<< HEAD
				       (ops->mode == MTD_OPS_RAW));
=======
				       (ops->mode == MTD_OOB_RAW));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
				       (ops->mode == MTD_OOB_RAW));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (ret)
			break;

		writelen -= bytes;
		if (!writelen)
			break;

		column = 0;
		buf += bytes;
		realpage++;

		page = realpage & chip->pagemask;
		/* Check, if we cross a chip boundary */
		if (!page) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);
		}
	}

	ops->retlen = ops->len - writelen;
	if (unlikely(oob))
		ops->oobretlen = ops->ooblen;
	return ret;
}

/**
 * panic_nand_write - [MTD Interface] NAND write with ECC
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @to: offset to write to
 * @len: number of bytes to write
 * @retlen: pointer to variable to store the number of written bytes
 * @buf: the data to write
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @len:	number of bytes to write
 * @retlen:	pointer to variable to store the number of written bytes
 * @buf:	the data to write
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * NAND write with ECC. Used when performing writes in interrupt context, this
 * may for example be called by mtdoops when writing an oops while in panic.
 */
static int panic_nand_write(struct mtd_info *mtd, loff_t to, size_t len,
			    size_t *retlen, const uint8_t *buf)
{
	struct nand_chip *chip = mtd->priv;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mtd_oob_ops ops;
	int ret;

	/* Wait for the device to get ready */
	panic_nand_wait(mtd, chip, 400);

	/* Grab the device */
	panic_nand_get_device(chip, mtd, FL_WRITING);

	ops.len = len;
	ops.datbuf = (uint8_t *)buf;
	ops.oobbuf = NULL;
	ops.mode = 0;

	ret = nand_do_write_ops(mtd, to, &ops);

	*retlen = ops.retlen;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret;

	/* Do not allow reads past end of device */
	if ((to + len) > mtd->size)
		return -EINVAL;
	if (!len)
		return 0;

	/* Wait for the device to get ready.  */
	panic_nand_wait(mtd, chip, 400);

	/* Grab the device.  */
	panic_nand_get_device(chip, mtd, FL_WRITING);

	chip->ops.len = len;
	chip->ops.datbuf = (uint8_t *)buf;
	chip->ops.oobbuf = NULL;

	ret = nand_do_write_ops(mtd, to, &chip->ops);

	*retlen = chip->ops.retlen;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

/**
 * nand_write - [MTD Interface] NAND write with ECC
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @to: offset to write to
 * @len: number of bytes to write
 * @retlen: pointer to variable to store the number of written bytes
 * @buf: the data to write
 *
 * NAND write with ECC.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @len:	number of bytes to write
 * @retlen:	pointer to variable to store the number of written bytes
 * @buf:	the data to write
 *
 * NAND write with ECC
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_write(struct mtd_info *mtd, loff_t to, size_t len,
			  size_t *retlen, const uint8_t *buf)
{
	struct nand_chip *chip = mtd->priv;
<<<<<<< HEAD
<<<<<<< HEAD
	struct mtd_oob_ops ops;
	int ret;

	nand_get_device(chip, mtd, FL_WRITING);
	ops.len = len;
	ops.datbuf = (uint8_t *)buf;
	ops.oobbuf = NULL;
	ops.mode = 0;
	ret = nand_do_write_ops(mtd, to, &ops);
	*retlen = ops.retlen;
	nand_release_device(mtd);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret;

	/* Do not allow reads past end of device */
	if ((to + len) > mtd->size)
		return -EINVAL;
	if (!len)
		return 0;

	nand_get_device(chip, mtd, FL_WRITING);

	chip->ops.len = len;
	chip->ops.datbuf = (uint8_t *)buf;
	chip->ops.oobbuf = NULL;

	ret = nand_do_write_ops(mtd, to, &chip->ops);

	*retlen = chip->ops.retlen;

	nand_release_device(mtd);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

/**
 * nand_do_write_oob - [MTD Interface] NAND write out-of-band
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @to: offset to write to
 * @ops: oob operation description structure
 *
 * NAND write out-of-band.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @ops:	oob operation description structure
 *
 * NAND write out-of-band
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_do_write_oob(struct mtd_info *mtd, loff_t to,
			     struct mtd_oob_ops *ops)
{
	int chipnr, page, status, len;
	struct nand_chip *chip = mtd->priv;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("%s: to = 0x%08x, len = %i\n",
			 __func__, (unsigned int)to, (int)ops->ooblen);

	if (ops->mode == MTD_OPS_AUTO_OOB)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	DEBUG(MTD_DEBUG_LEVEL3, "%s: to = 0x%08x, len = %i\n",
			 __func__, (unsigned int)to, (int)ops->ooblen);

	if (ops->mode == MTD_OOB_AUTO)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		len = chip->ecc.layout->oobavail;
	else
		len = mtd->oobsize;

	/* Do not allow write past end of page */
	if ((ops->ooboffs + ops->ooblen) > len) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: attempt to write past end of page\n",
				__func__);
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt to write "
				"past end of page\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt to write "
				"past end of page\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	if (unlikely(ops->ooboffs >= len)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: attempt to start write outside oob\n",
				__func__);
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt to start "
				"write outside oob\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt to start "
				"write outside oob\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	/* Do not allow write past end of device */
	if (unlikely(to >= mtd->size ||
		     ops->ooboffs + ops->ooblen >
			((mtd->size >> chip->page_shift) -
			 (to >> chip->page_shift)) * len)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: attempt to write beyond end of device\n",
				__func__);
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt write beyond "
				"end of device\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt write beyond "
				"end of device\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	chipnr = (int)(to >> chip->chip_shift);
	chip->select_chip(mtd, chipnr);

	/* Shift to get page */
	page = (int)(to >> chip->page_shift);

	/*
	 * Reset the chip. Some chips (like the Toshiba TC5832DC found in one
	 * of my DiskOnChip 2000 test units) will clear the whole data page too
	 * if we don't do this. I have no clue why, but I seem to have 'fixed'
	 * it in the doc2000 driver in August 1999.  dwmw2.
	 */
	chip->cmdfunc(mtd, NAND_CMD_RESET, -1, -1);

	/* Check, if it is write protected */
	if (nand_check_wp(mtd))
		return -EROFS;

	/* Invalidate the page cache, if we write to the cached page */
	if (page == chip->pagebuf)
		chip->pagebuf = -1;

	nand_fill_oob(mtd, ops->oobbuf, ops->ooblen, ops);
<<<<<<< HEAD
<<<<<<< HEAD

	if (ops->mode == MTD_OPS_RAW)
		status = chip->ecc.write_oob_raw(mtd, chip, page & chip->pagemask);
	else
		status = chip->ecc.write_oob(mtd, chip, page & chip->pagemask);
=======
	status = chip->ecc.write_oob(mtd, chip, page & chip->pagemask);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	status = chip->ecc.write_oob(mtd, chip, page & chip->pagemask);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (status)
		return status;

	ops->oobretlen = ops->ooblen;

	return 0;
}

/**
 * nand_write_oob - [MTD Interface] NAND write data and/or out-of-band
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @to: offset to write to
 * @ops: oob operation description structure
=======
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @ops:	oob operation description structure
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
 * @to:		offset to write to
 * @ops:	oob operation description structure
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_write_oob(struct mtd_info *mtd, loff_t to,
			  struct mtd_oob_ops *ops)
{
	struct nand_chip *chip = mtd->priv;
	int ret = -ENOTSUPP;

	ops->retlen = 0;

	/* Do not allow writes past end of device */
	if (ops->datbuf && (to + ops->len) > mtd->size) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: attempt to write beyond end of device\n",
				__func__);
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt write beyond "
				"end of device\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Attempt write beyond "
				"end of device\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	nand_get_device(chip, mtd, FL_WRITING);

	switch (ops->mode) {
<<<<<<< HEAD
<<<<<<< HEAD
	case MTD_OPS_PLACE_OOB:
	case MTD_OPS_AUTO_OOB:
	case MTD_OPS_RAW:
=======
	case MTD_OOB_PLACE:
	case MTD_OOB_AUTO:
	case MTD_OOB_RAW:
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	case MTD_OOB_PLACE:
	case MTD_OOB_AUTO:
	case MTD_OOB_RAW:
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;

	default:
		goto out;
	}

	if (!ops->datbuf)
		ret = nand_do_write_oob(mtd, to, ops);
	else
		ret = nand_do_write_ops(mtd, to, ops);

out:
	nand_release_device(mtd);
	return ret;
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * single_erase_cmd - [GENERIC] NAND standard block erase command function
 * @mtd: MTD device structure
 * @page: the page address of the block which will be erased
 *
 * Standard erase command for NAND chips.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * single_erease_cmd - [GENERIC] NAND standard block erase command function
 * @mtd:	MTD device structure
 * @page:	the page address of the block which will be erased
 *
 * Standard erase command for NAND chips
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void single_erase_cmd(struct mtd_info *mtd, int page)
{
	struct nand_chip *chip = mtd->priv;
	/* Send commands to erase a block */
	chip->cmdfunc(mtd, NAND_CMD_ERASE1, -1, page);
	chip->cmdfunc(mtd, NAND_CMD_ERASE2, -1, -1);
}

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * multi_erase_cmd - [GENERIC] AND specific block erase command function
 * @mtd: MTD device structure
 * @page: the page address of the block which will be erased
 *
 * AND multi block erase command function. Erase 4 consecutive blocks.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * multi_erease_cmd - [GENERIC] AND specific block erase command function
 * @mtd:	MTD device structure
 * @page:	the page address of the block which will be erased
 *
 * AND multi block erase command function
 * Erase 4 consecutive blocks
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void multi_erase_cmd(struct mtd_info *mtd, int page)
{
	struct nand_chip *chip = mtd->priv;
	/* Send commands to erase a block */
	chip->cmdfunc(mtd, NAND_CMD_ERASE1, -1, page++);
	chip->cmdfunc(mtd, NAND_CMD_ERASE1, -1, page++);
	chip->cmdfunc(mtd, NAND_CMD_ERASE1, -1, page++);
	chip->cmdfunc(mtd, NAND_CMD_ERASE1, -1, page);
	chip->cmdfunc(mtd, NAND_CMD_ERASE2, -1, -1);
}

/**
 * nand_erase - [MTD Interface] erase block(s)
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @instr: erase instruction
 *
 * Erase one ore more blocks.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @instr:	erase instruction
 *
 * Erase one ore more blocks
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_erase(struct mtd_info *mtd, struct erase_info *instr)
{
	return nand_erase_nand(mtd, instr, 0);
}

#define BBT_PAGE_MASK	0xffffff3f
/**
<<<<<<< HEAD
<<<<<<< HEAD
 * nand_erase_nand - [INTERN] erase block(s)
 * @mtd: MTD device structure
 * @instr: erase instruction
 * @allowbbt: allow erasing the bbt area
 *
 * Erase one ore more blocks.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * nand_erase_nand - [Internal] erase block(s)
 * @mtd:	MTD device structure
 * @instr:	erase instruction
 * @allowbbt:	allow erasing the bbt area
 *
 * Erase one ore more blocks
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
int nand_erase_nand(struct mtd_info *mtd, struct erase_info *instr,
		    int allowbbt)
{
	int page, status, pages_per_block, ret, chipnr;
	struct nand_chip *chip = mtd->priv;
	loff_t rewrite_bbt[NAND_MAX_CHIPS] = {0};
	unsigned int bbt_masked_page = 0xffffffff;
	loff_t len;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("%s: start = 0x%012llx, len = %llu\n",
			__func__, (unsigned long long)instr->addr,
			(unsigned long long)instr->len);
=======
	DEBUG(MTD_DEBUG_LEVEL3, "%s: start = 0x%012llx, len = %llu\n",
				__func__, (unsigned long long)instr->addr,
				(unsigned long long)instr->len);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	DEBUG(MTD_DEBUG_LEVEL3, "%s: start = 0x%012llx, len = %llu\n",
				__func__, (unsigned long long)instr->addr,
				(unsigned long long)instr->len);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (check_offs_len(mtd, instr->addr, instr->len))
		return -EINVAL;

<<<<<<< HEAD
<<<<<<< HEAD
=======
	instr->fail_addr = MTD_FAIL_ADDR_UNKNOWN;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	instr->fail_addr = MTD_FAIL_ADDR_UNKNOWN;

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Grab the lock and see if the device is available */
	nand_get_device(chip, mtd, FL_ERASING);

	/* Shift to get first page */
	page = (int)(instr->addr >> chip->page_shift);
	chipnr = (int)(instr->addr >> chip->chip_shift);

	/* Calculate pages in each block */
	pages_per_block = 1 << (chip->phys_erase_shift - chip->page_shift);

	/* Select the NAND device */
	chip->select_chip(mtd, chipnr);

	/* Check, if it is write protected */
	if (nand_check_wp(mtd)) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_debug("%s: device is write protected!\n",
				__func__);
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Device is write protected!!!\n",
					__func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		DEBUG(MTD_DEBUG_LEVEL0, "%s: Device is write protected!!!\n",
					__func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		instr->state = MTD_ERASE_FAILED;
		goto erase_exit;
	}

	/*
	 * If BBT requires refresh, set the BBT page mask to see if the BBT
	 * should be rewritten. Otherwise the mask is set to 0xffffffff which
	 * can not be matched. This is also done when the bbt is actually
<<<<<<< HEAD
<<<<<<< HEAD
	 * erased to avoid recursive updates.
=======
	 * erased to avoid recusrsive updates
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * erased to avoid recusrsive updates
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	if (chip->options & BBT_AUTO_REFRESH && !allowbbt)
		bbt_masked_page = chip->bbt_td->pages[chipnr] & BBT_PAGE_MASK;

	/* Loop through the pages */
	len = instr->len;

	instr->state = MTD_ERASING;

	while (len) {
<<<<<<< HEAD
<<<<<<< HEAD
		/* Check if we have a bad block, we do not erase bad blocks! */
		if (nand_block_checkbad(mtd, ((loff_t) page) <<
					chip->page_shift, 0, allowbbt)) {
			pr_warn("%s: attempt to erase a bad block at page 0x%08x\n",
				    __func__, page);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		/*
		 * heck if we have a bad block, we do not erase bad blocks !
		 */
		if (nand_block_checkbad(mtd, ((loff_t) page) <<
					chip->page_shift, 0, allowbbt)) {
			printk(KERN_WARNING "%s: attempt to erase a bad block "
					"at page 0x%08x\n", __func__, page);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			instr->state = MTD_ERASE_FAILED;
			goto erase_exit;
		}

		/*
		 * Invalidate the page cache, if we erase the block which
<<<<<<< HEAD
<<<<<<< HEAD
		 * contains the current cached page.
=======
		 * contains the current cached page
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		 * contains the current cached page
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 */
		if (page <= chip->pagebuf && chip->pagebuf <
		    (page + pages_per_block))
			chip->pagebuf = -1;

		chip->erase_cmd(mtd, page & chip->pagemask);

		status = chip->waitfunc(mtd, chip);

		/*
		 * See if operation failed and additional status checks are
		 * available
		 */
		if ((status & NAND_STATUS_FAIL) && (chip->errstat))
			status = chip->errstat(mtd, chip, FL_ERASING,
					       status, page);

		/* See if block erase succeeded */
		if (status & NAND_STATUS_FAIL) {
<<<<<<< HEAD
<<<<<<< HEAD
			pr_debug("%s: failed erase, page 0x%08x\n",
					__func__, page);
=======
			DEBUG(MTD_DEBUG_LEVEL0, "%s: Failed erase, "
					"page 0x%08x\n", __func__, page);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			DEBUG(MTD_DEBUG_LEVEL0, "%s: Failed erase, "
					"page 0x%08x\n", __func__, page);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			instr->state = MTD_ERASE_FAILED;
			instr->fail_addr =
				((loff_t)page << chip->page_shift);
			goto erase_exit;
		}

		/*
		 * If BBT requires refresh, set the BBT rewrite flag to the
<<<<<<< HEAD
<<<<<<< HEAD
		 * page being erased.
=======
		 * page being erased
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		 * page being erased
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 */
		if (bbt_masked_page != 0xffffffff &&
		    (page & BBT_PAGE_MASK) == bbt_masked_page)
			    rewrite_bbt[chipnr] =
					((loff_t)page << chip->page_shift);

		/* Increment page address and decrement length */
		len -= (1 << chip->phys_erase_shift);
		page += pages_per_block;

		/* Check, if we cross a chip boundary */
		if (len && !(page & chip->pagemask)) {
			chipnr++;
			chip->select_chip(mtd, -1);
			chip->select_chip(mtd, chipnr);

			/*
			 * If BBT requires refresh and BBT-PERCHIP, set the BBT
<<<<<<< HEAD
<<<<<<< HEAD
			 * page mask to see if this BBT should be rewritten.
=======
			 * page mask to see if this BBT should be rewritten
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			 * page mask to see if this BBT should be rewritten
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			 */
			if (bbt_masked_page != 0xffffffff &&
			    (chip->bbt_td->options & NAND_BBT_PERCHIP))
				bbt_masked_page = chip->bbt_td->pages[chipnr] &
					BBT_PAGE_MASK;
		}
	}
	instr->state = MTD_ERASE_DONE;

erase_exit:

	ret = instr->state == MTD_ERASE_DONE ? 0 : -EIO;

	/* Deselect and wake up anyone waiting on the device */
	nand_release_device(mtd);

	/* Do call back function */
	if (!ret)
		mtd_erase_callback(instr);

	/*
	 * If BBT requires refresh and erase was successful, rewrite any
<<<<<<< HEAD
<<<<<<< HEAD
	 * selected bad block tables.
=======
	 * selected bad block tables
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * selected bad block tables
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	if (bbt_masked_page == 0xffffffff || ret)
		return ret;

	for (chipnr = 0; chipnr < chip->numchips; chipnr++) {
		if (!rewrite_bbt[chipnr])
			continue;
<<<<<<< HEAD
<<<<<<< HEAD
		/* Update the BBT for chip */
		pr_debug("%s: nand_update_bbt (%d:0x%0llx 0x%0x)\n",
				__func__, chipnr, rewrite_bbt[chipnr],
				chip->bbt_td->pages[chipnr]);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		/* update the BBT for chip */
		DEBUG(MTD_DEBUG_LEVEL0, "%s: nand_update_bbt "
			"(%d:0x%0llx 0x%0x)\n", __func__, chipnr,
			rewrite_bbt[chipnr], chip->bbt_td->pages[chipnr]);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		nand_update_bbt(mtd, rewrite_bbt[chipnr]);
	}

	/* Return more or less happy */
	return ret;
}

/**
 * nand_sync - [MTD Interface] sync
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 *
 * Sync is actually a wait for chip ready function.
=======
 * @mtd:	MTD device structure
 *
 * Sync is actually a wait for chip ready function
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
 *
 * Sync is actually a wait for chip ready function
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_sync(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_debug("%s: called\n", __func__);
=======
	DEBUG(MTD_DEBUG_LEVEL3, "%s: called\n", __func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	DEBUG(MTD_DEBUG_LEVEL3, "%s: called\n", __func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Grab the lock and see if the device is available */
	nand_get_device(chip, mtd, FL_SYNCING);
	/* Release it and go back */
	nand_release_device(mtd);
}

/**
 * nand_block_isbad - [MTD Interface] Check if block at offset is bad
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @offs: offset relative to mtd start
 */
static int nand_block_isbad(struct mtd_info *mtd, loff_t offs)
{
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @offs:	offset relative to mtd start
 */
static int nand_block_isbad(struct mtd_info *mtd, loff_t offs)
{
	/* Check for invalid offset */
	if (offs > mtd->size)
		return -EINVAL;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return nand_block_checkbad(mtd, offs, 1, 0);
}

/**
 * nand_block_markbad - [MTD Interface] Mark block at the given offset as bad
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @ofs: offset relative to mtd start
=======
 * @mtd:	MTD device structure
 * @ofs:	offset relative to mtd start
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
 * @ofs:	offset relative to mtd start
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_block_markbad(struct mtd_info *mtd, loff_t ofs)
{
	struct nand_chip *chip = mtd->priv;
	int ret;

	ret = nand_block_isbad(mtd, ofs);
	if (ret) {
<<<<<<< HEAD
<<<<<<< HEAD
		/* If it was bad already, return success and do nothing */
=======
		/* If it was bad already, return success and do nothing. */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* If it was bad already, return success and do nothing. */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (ret > 0)
			return 0;
		return ret;
	}

	return chip->block_markbad(mtd, ofs);
}

/**
 * nand_suspend - [MTD Interface] Suspend the NAND flash
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
=======
 * @mtd:	MTD device structure
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static int nand_suspend(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;

	return nand_get_device(chip, mtd, FL_PM_SUSPENDED);
}

/**
 * nand_resume - [MTD Interface] Resume the NAND flash
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
=======
 * @mtd:	MTD device structure
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static void nand_resume(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;

	if (chip->state == FL_PM_SUSPENDED)
		nand_release_device(mtd);
	else
<<<<<<< HEAD
<<<<<<< HEAD
		pr_err("%s called for a chip which is not in suspended state\n",
			__func__);
}

/* Set default functions */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		printk(KERN_ERR "%s called for a chip which is not "
		       "in suspended state\n", __func__);
}

/*
 * Set default functions
 */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void nand_set_defaults(struct nand_chip *chip, int busw)
{
	/* check for proper chip_delay setup, set 20us if not */
	if (!chip->chip_delay)
		chip->chip_delay = 20;

	/* check, if a user supplied command function given */
	if (chip->cmdfunc == NULL)
		chip->cmdfunc = nand_command;

	/* check, if a user supplied wait function given */
	if (chip->waitfunc == NULL)
		chip->waitfunc = nand_wait;

	if (!chip->select_chip)
		chip->select_chip = nand_select_chip;
	if (!chip->read_byte)
		chip->read_byte = busw ? nand_read_byte16 : nand_read_byte;
	if (!chip->read_word)
		chip->read_word = nand_read_word;
	if (!chip->block_bad)
		chip->block_bad = nand_block_bad;
	if (!chip->block_markbad)
		chip->block_markbad = nand_default_block_markbad;
	if (!chip->write_buf)
		chip->write_buf = busw ? nand_write_buf16 : nand_write_buf;
	if (!chip->read_buf)
		chip->read_buf = busw ? nand_read_buf16 : nand_read_buf;
	if (!chip->verify_buf)
		chip->verify_buf = busw ? nand_verify_buf16 : nand_verify_buf;
	if (!chip->scan_bbt)
		chip->scan_bbt = nand_default_bbt;

	if (!chip->controller) {
		chip->controller = &chip->hwcontrol;
		spin_lock_init(&chip->controller->lock);
		init_waitqueue_head(&chip->controller->wq);
	}

}

<<<<<<< HEAD
<<<<<<< HEAD
/* Sanitize ONFI strings so we can safely print them */
=======
/*
 * sanitize ONFI strings so we can safely print them
 */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
/*
 * sanitize ONFI strings so we can safely print them
 */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void sanitize_string(uint8_t *s, size_t len)
{
	ssize_t i;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Null terminate */
	s[len - 1] = 0;

	/* Remove non printable chars */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* null terminate */
	s[len - 1] = 0;

	/* remove non printable chars */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	for (i = 0; i < len - 1; i++) {
		if (s[i] < ' ' || s[i] > 127)
			s[i] = '?';
	}

<<<<<<< HEAD
<<<<<<< HEAD
	/* Remove trailing spaces */
=======
	/* remove trailing spaces */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* remove trailing spaces */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	strim(s);
}

static u16 onfi_crc16(u16 crc, u8 const *p, size_t len)
{
	int i;
	while (len--) {
		crc ^= *p++ << 8;
		for (i = 0; i < 8; i++)
			crc = (crc << 1) ^ ((crc & 0x8000) ? 0x8005 : 0);
	}

	return crc;
}

/*
<<<<<<< HEAD
<<<<<<< HEAD
 * Check if the NAND chip is ONFI compliant, returns 1 if it is, 0 otherwise.
 */
static int nand_flash_detect_onfi(struct mtd_info *mtd, struct nand_chip *chip,
					int *busw)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * Check if the NAND chip is ONFI compliant, returns 1 if it is, 0 otherwise
 */
static int nand_flash_detect_onfi(struct mtd_info *mtd, struct nand_chip *chip,
					int busw)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct nand_onfi_params *p = &chip->onfi_params;
	int i;
	int val;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Try ONFI for unknown chip or LP */
=======
	/* try ONFI for unknow chip or LP */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* try ONFI for unknow chip or LP */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	chip->cmdfunc(mtd, NAND_CMD_READID, 0x20, -1);
	if (chip->read_byte(mtd) != 'O' || chip->read_byte(mtd) != 'N' ||
		chip->read_byte(mtd) != 'F' || chip->read_byte(mtd) != 'I')
		return 0;

<<<<<<< HEAD
<<<<<<< HEAD
=======
	printk(KERN_INFO "ONFI flash detected\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	printk(KERN_INFO "ONFI flash detected\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	chip->cmdfunc(mtd, NAND_CMD_PARAM, 0, -1);
	for (i = 0; i < 3; i++) {
		chip->read_buf(mtd, (uint8_t *)p, sizeof(*p));
		if (onfi_crc16(ONFI_CRC_BASE, (uint8_t *)p, 254) ==
				le16_to_cpu(p->crc)) {
<<<<<<< HEAD
<<<<<<< HEAD
			pr_info("ONFI param page %d valid\n", i);
=======
			printk(KERN_INFO "ONFI param page %d valid\n", i);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			printk(KERN_INFO "ONFI param page %d valid\n", i);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			break;
		}
	}

	if (i == 3)
		return 0;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Check version */
=======
	/* check version */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* check version */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	val = le16_to_cpu(p->revision);
	if (val & (1 << 5))
		chip->onfi_version = 23;
	else if (val & (1 << 4))
		chip->onfi_version = 22;
	else if (val & (1 << 3))
		chip->onfi_version = 21;
	else if (val & (1 << 2))
		chip->onfi_version = 20;
	else if (val & (1 << 1))
		chip->onfi_version = 10;
	else
		chip->onfi_version = 0;

	if (!chip->onfi_version) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_info("%s: unsupported ONFI version: %d\n", __func__, val);
=======
		printk(KERN_INFO "%s: unsupported ONFI version: %d\n",
								__func__, val);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_INFO "%s: unsupported ONFI version: %d\n",
								__func__, val);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return 0;
	}

	sanitize_string(p->manufacturer, sizeof(p->manufacturer));
	sanitize_string(p->model, sizeof(p->model));
	if (!mtd->name)
		mtd->name = p->model;
	mtd->writesize = le32_to_cpu(p->byte_per_page);
	mtd->erasesize = le32_to_cpu(p->pages_per_block) * mtd->writesize;
	mtd->oobsize = le16_to_cpu(p->spare_bytes_per_page);
<<<<<<< HEAD
<<<<<<< HEAD
	chip->chipsize = le32_to_cpu(p->blocks_per_lun);
	chip->chipsize *= (uint64_t)mtd->erasesize * p->lun_count;
	*busw = 0;
	if (le16_to_cpu(p->features) & 1)
		*busw = NAND_BUSWIDTH_16;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	chip->chipsize = (uint64_t)le32_to_cpu(p->blocks_per_lun) * mtd->erasesize;
	busw = 0;
	if (le16_to_cpu(p->features) & 1)
		busw = NAND_BUSWIDTH_16;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	chip->options &= ~NAND_CHIPOPTIONS_MSK;
	chip->options |= (NAND_NO_READRDY |
			NAND_NO_AUTOINCR) & NAND_CHIPOPTIONS_MSK;

<<<<<<< HEAD
<<<<<<< HEAD
	pr_info("ONFI flash detected\n");
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 1;
}

/*
<<<<<<< HEAD
<<<<<<< HEAD
 * Get the flash and manufacturer id and lookup if the type is supported.
=======
 * Get the flash and manufacturer id and lookup if the type is supported
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Get the flash and manufacturer id and lookup if the type is supported
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
static struct nand_flash_dev *nand_get_flash_type(struct mtd_info *mtd,
						  struct nand_chip *chip,
						  int busw,
						  int *maf_id, int *dev_id,
						  struct nand_flash_dev *type)
{
	int i, maf_idx;
	u8 id_data[8];
	int ret;

	/* Select the device */
	chip->select_chip(mtd, 0);

	/*
	 * Reset the chip, required by some chips (e.g. Micron MT29FxGxxxxx)
<<<<<<< HEAD
<<<<<<< HEAD
	 * after power-up.
=======
	 * after power-up
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * after power-up
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	chip->cmdfunc(mtd, NAND_CMD_RESET, -1, -1);

	/* Send the command for reading device ID */
	chip->cmdfunc(mtd, NAND_CMD_READID, 0x00, -1);

	/* Read manufacturer and device IDs */
	*maf_id = chip->read_byte(mtd);
	*dev_id = chip->read_byte(mtd);

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * Try again to make sure, as some systems the bus-hold or other
=======
	/* Try again to make sure, as some systems the bus-hold or other
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Try again to make sure, as some systems the bus-hold or other
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 * interface concerns can cause random data which looks like a
	 * possibly credible NAND flash to appear. If the two results do
	 * not match, ignore the device completely.
	 */

	chip->cmdfunc(mtd, NAND_CMD_READID, 0x00, -1);

	for (i = 0; i < 2; i++)
		id_data[i] = chip->read_byte(mtd);

	if (id_data[0] != *maf_id || id_data[1] != *dev_id) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_info("%s: second ID read did not match "
			"%02x,%02x against %02x,%02x\n", __func__,
			*maf_id, *dev_id, id_data[0], id_data[1]);
=======
		printk(KERN_INFO "%s: second ID read did not match "
		       "%02x,%02x against %02x,%02x\n", __func__,
		       *maf_id, *dev_id, id_data[0], id_data[1]);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_INFO "%s: second ID read did not match "
		       "%02x,%02x against %02x,%02x\n", __func__,
		       *maf_id, *dev_id, id_data[0], id_data[1]);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return ERR_PTR(-ENODEV);
	}

	if (!type)
		type = nand_flash_ids;

	for (; type->name != NULL; type++)
		if (*dev_id == type->id)
			break;

	chip->onfi_version = 0;
	if (!type->name || !type->pagesize) {
		/* Check is chip is ONFI compliant */
<<<<<<< HEAD
<<<<<<< HEAD
		ret = nand_flash_detect_onfi(mtd, chip, &busw);
=======
		ret = nand_flash_detect_onfi(mtd, chip, busw);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		ret = nand_flash_detect_onfi(mtd, chip, busw);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (ret)
			goto ident_done;
	}

	chip->cmdfunc(mtd, NAND_CMD_READID, 0x00, -1);

	/* Read entire ID string */

	for (i = 0; i < 8; i++)
		id_data[i] = chip->read_byte(mtd);

	if (!type->name)
		return ERR_PTR(-ENODEV);

	if (!mtd->name)
		mtd->name = type->name;

	chip->chipsize = (uint64_t)type->chipsize << 20;

	if (!type->pagesize && chip->init_size) {
<<<<<<< HEAD
<<<<<<< HEAD
		/* Set the pagesize, oobsize, erasesize by the driver */
=======
		/* set the pagesize, oobsize, erasesize by the driver*/
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* set the pagesize, oobsize, erasesize by the driver*/
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		busw = chip->init_size(mtd, chip, id_data);
	} else if (!type->pagesize) {
		int extid;
		/* The 3rd id byte holds MLC / multichip data */
		chip->cellinfo = id_data[2];
		/* The 4th id byte is the important one */
		extid = id_data[3];

		/*
		 * Field definitions are in the following datasheets:
		 * Old style (4,5 byte ID): Samsung K9GAG08U0M (p.32)
		 * New style   (6 byte ID): Samsung K9GBG08U0M (p.40)
		 *
		 * Check for wraparound + Samsung ID + nonzero 6th byte
		 * to decide what to do.
		 */
		if (id_data[0] == id_data[6] && id_data[1] == id_data[7] &&
				id_data[0] == NAND_MFR_SAMSUNG &&
				(chip->cellinfo & NAND_CI_CELLTYPE_MSK) &&
				id_data[5] != 0x00) {
			/* Calc pagesize */
			mtd->writesize = 2048 << (extid & 0x03);
			extid >>= 2;
			/* Calc oobsize */
			switch (extid & 0x03) {
			case 1:
				mtd->oobsize = 128;
				break;
			case 2:
				mtd->oobsize = 218;
				break;
			case 3:
				mtd->oobsize = 400;
				break;
			default:
				mtd->oobsize = 436;
				break;
			}
			extid >>= 2;
			/* Calc blocksize */
			mtd->erasesize = (128 * 1024) <<
				(((extid >> 1) & 0x04) | (extid & 0x03));
			busw = 0;
		} else {
			/* Calc pagesize */
			mtd->writesize = 1024 << (extid & 0x03);
			extid >>= 2;
			/* Calc oobsize */
			mtd->oobsize = (8 << (extid & 0x01)) *
				(mtd->writesize >> 9);
			extid >>= 2;
			/* Calc blocksize. Blocksize is multiples of 64KiB */
			mtd->erasesize = (64 * 1024) << (extid & 0x03);
			extid >>= 2;
			/* Get buswidth information */
			busw = (extid & 0x01) ? NAND_BUSWIDTH_16 : 0;
		}
	} else {
		/*
<<<<<<< HEAD
<<<<<<< HEAD
		 * Old devices have chip data hardcoded in the device id table.
=======
		 * Old devices have chip data hardcoded in the device id table
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		 * Old devices have chip data hardcoded in the device id table
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 */
		mtd->erasesize = type->erasesize;
		mtd->writesize = type->pagesize;
		mtd->oobsize = mtd->writesize / 32;
		busw = type->options & NAND_BUSWIDTH_16;

		/*
		 * Check for Spansion/AMD ID + repeating 5th, 6th byte since
		 * some Spansion chips have erasesize that conflicts with size
<<<<<<< HEAD
<<<<<<< HEAD
		 * listed in nand_ids table.
=======
		 * listed in nand_ids table
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		 * listed in nand_ids table
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 * Data sheet (5 byte ID): Spansion S30ML-P ORNAND (p.39)
		 */
		if (*maf_id == NAND_MFR_AMD && id_data[4] != 0x00 &&
				id_data[5] == 0x00 && id_data[6] == 0x00 &&
				id_data[7] == 0x00 && mtd->writesize == 512) {
			mtd->erasesize = 128 * 1024;
			mtd->erasesize <<= ((id_data[3] & 0x03) << 1);
		}
	}
	/* Get chip options, preserve non chip based options */
	chip->options &= ~NAND_CHIPOPTIONS_MSK;
	chip->options |= type->options & NAND_CHIPOPTIONS_MSK;

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * Check if chip is not a Samsung device. Do not clear the
	 * options for chips which do not have an extended id.
=======
	/* Check if chip is a not a samsung device. Do not clear the
	 * options for chips which are not having an extended id.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Check if chip is a not a samsung device. Do not clear the
	 * options for chips which are not having an extended id.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	if (*maf_id != NAND_MFR_SAMSUNG && !type->pagesize)
		chip->options &= ~NAND_SAMSUNG_LP_OPTIONS;
ident_done:

	/*
<<<<<<< HEAD
<<<<<<< HEAD
	 * Set chip as a default. Board drivers can override it, if necessary.
=======
	 * Set chip as a default. Board drivers can override it, if necessary
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * Set chip as a default. Board drivers can override it, if necessary
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	chip->options |= NAND_NO_AUTOINCR;

	/* Try to identify manufacturer */
	for (maf_idx = 0; nand_manuf_ids[maf_idx].id != 0x0; maf_idx++) {
		if (nand_manuf_ids[maf_idx].id == *maf_id)
			break;
	}

	/*
	 * Check, if buswidth is correct. Hardware drivers should set
<<<<<<< HEAD
<<<<<<< HEAD
	 * chip correct!
	 */
	if (busw != (chip->options & NAND_BUSWIDTH_16)) {
		pr_info("NAND device: Manufacturer ID:"
			" 0x%02x, Chip ID: 0x%02x (%s %s)\n", *maf_id,
			*dev_id, nand_manuf_ids[maf_idx].name, mtd->name);
		pr_warn("NAND bus width %d instead %d bit\n",
			   (chip->options & NAND_BUSWIDTH_16) ? 16 : 8,
			   busw ? 16 : 8);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 * chip correct !
	 */
	if (busw != (chip->options & NAND_BUSWIDTH_16)) {
		printk(KERN_INFO "NAND device: Manufacturer ID:"
		       " 0x%02x, Chip ID: 0x%02x (%s %s)\n", *maf_id,
		       *dev_id, nand_manuf_ids[maf_idx].name, mtd->name);
		printk(KERN_WARNING "NAND bus width %d instead %d bit\n",
		       (chip->options & NAND_BUSWIDTH_16) ? 16 : 8,
		       busw ? 16 : 8);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return ERR_PTR(-EINVAL);
	}

	/* Calculate the address shift from the page size */
	chip->page_shift = ffs(mtd->writesize) - 1;
<<<<<<< HEAD
<<<<<<< HEAD
	/* Convert chipsize to number of pages per chip -1 */
=======
	/* Convert chipsize to number of pages per chip -1. */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	/* Convert chipsize to number of pages per chip -1. */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	chip->pagemask = (chip->chipsize >> chip->page_shift) - 1;

	chip->bbt_erase_shift = chip->phys_erase_shift =
		ffs(mtd->erasesize) - 1;
	if (chip->chipsize & 0xffffffff)
		chip->chip_shift = ffs((unsigned)chip->chipsize) - 1;
	else {
		chip->chip_shift = ffs((unsigned)(chip->chipsize >> 32));
		chip->chip_shift += 32 - 1;
	}

	chip->badblockbits = 8;

	/* Set the bad block position */
	if (mtd->writesize > 512 || (busw & NAND_BUSWIDTH_16))
		chip->badblockpos = NAND_LARGE_BADBLOCK_POS;
	else
		chip->badblockpos = NAND_SMALL_BADBLOCK_POS;

	/*
	 * Bad block marker is stored in the last page of each block
	 * on Samsung and Hynix MLC devices; stored in first two pages
	 * of each block on Micron devices with 2KiB pages and on
<<<<<<< HEAD
<<<<<<< HEAD
	 * SLC Samsung, Hynix, Toshiba, AMD/Spansion, and Macronix.
	 * All others scan only the first page.
=======
	 * SLC Samsung, Hynix, Toshiba and AMD/Spansion. All others scan
	 * only the first page.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * SLC Samsung, Hynix, Toshiba and AMD/Spansion. All others scan
	 * only the first page.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	if ((chip->cellinfo & NAND_CI_CELLTYPE_MSK) &&
			(*maf_id == NAND_MFR_SAMSUNG ||
			 *maf_id == NAND_MFR_HYNIX))
<<<<<<< HEAD
<<<<<<< HEAD
		chip->bbt_options |= NAND_BBT_SCANLASTPAGE;
=======
		chip->options |= NAND_BBT_SCANLASTPAGE;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		chip->options |= NAND_BBT_SCANLASTPAGE;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	else if ((!(chip->cellinfo & NAND_CI_CELLTYPE_MSK) &&
				(*maf_id == NAND_MFR_SAMSUNG ||
				 *maf_id == NAND_MFR_HYNIX ||
				 *maf_id == NAND_MFR_TOSHIBA ||
<<<<<<< HEAD
<<<<<<< HEAD
				 *maf_id == NAND_MFR_AMD ||
				 *maf_id == NAND_MFR_MACRONIX)) ||
			(mtd->writesize == 2048 &&
			 *maf_id == NAND_MFR_MICRON))
		chip->bbt_options |= NAND_BBT_SCAN2NDPAGE;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
				 *maf_id == NAND_MFR_AMD)) ||
			(mtd->writesize == 2048 &&
			 *maf_id == NAND_MFR_MICRON))
		chip->options |= NAND_BBT_SCAN2NDPAGE;

	/*
	 * Numonyx/ST 2K pages, x8 bus use BOTH byte 1 and 6
	 */
	if (!(busw & NAND_BUSWIDTH_16) &&
			*maf_id == NAND_MFR_STMICRO &&
			mtd->writesize == 2048) {
		chip->options |= NAND_BBT_SCANBYTE1AND6;
		chip->badblockpos = 0;
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Check for AND chips with 4 page planes */
	if (chip->options & NAND_4PAGE_ARRAY)
		chip->erase_cmd = multi_erase_cmd;
	else
		chip->erase_cmd = single_erase_cmd;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Do not replace user supplied command function! */
	if (mtd->writesize > 512 && chip->cmdfunc == nand_command)
		chip->cmdfunc = nand_command_lp;

	pr_info("NAND device: Manufacturer ID:"
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Do not replace user supplied command function ! */
	if (mtd->writesize > 512 && chip->cmdfunc == nand_command)
		chip->cmdfunc = nand_command_lp;

	/* TODO onfi flash name */
	printk(KERN_INFO "NAND device: Manufacturer ID:"
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		" 0x%02x, Chip ID: 0x%02x (%s %s)\n", *maf_id, *dev_id,
		nand_manuf_ids[maf_idx].name,
		chip->onfi_version ? chip->onfi_params.model : type->name);

	return type;
}

/**
 * nand_scan_ident - [NAND Interface] Scan for the NAND device
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @maxchips: number of chips to scan for
 * @table: alternative NAND ID table
 *
 * This is the first phase of the normal nand_scan() function. It reads the
 * flash ID and sets up MTD fields accordingly.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	     MTD device structure
 * @maxchips:	     Number of chips to scan for
 * @table:	     Alternative NAND ID table
 *
 * This is the first phase of the normal nand_scan() function. It
 * reads the flash ID and sets up MTD fields accordingly.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * The mtd->owner field must be set to the module of the caller.
 */
int nand_scan_ident(struct mtd_info *mtd, int maxchips,
		    struct nand_flash_dev *table)
{
	int i, busw, nand_maf_id, nand_dev_id;
	struct nand_chip *chip = mtd->priv;
	struct nand_flash_dev *type;

	/* Get buswidth to select the correct functions */
	busw = chip->options & NAND_BUSWIDTH_16;
	/* Set the default functions */
	nand_set_defaults(chip, busw);

	/* Read the flash type */
	type = nand_get_flash_type(mtd, chip, busw,
				&nand_maf_id, &nand_dev_id, table);

	if (IS_ERR(type)) {
		if (!(chip->options & NAND_SCAN_SILENT_NODEV))
<<<<<<< HEAD
<<<<<<< HEAD
			pr_warn("No NAND device found\n");
=======
			printk(KERN_WARNING "No NAND device found.\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			printk(KERN_WARNING "No NAND device found.\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		chip->select_chip(mtd, -1);
		return PTR_ERR(type);
	}

	/* Check for a chip array */
	for (i = 1; i < maxchips; i++) {
		chip->select_chip(mtd, i);
		/* See comment in nand_get_flash_type for reset */
		chip->cmdfunc(mtd, NAND_CMD_RESET, -1, -1);
		/* Send the command for reading device ID */
		chip->cmdfunc(mtd, NAND_CMD_READID, 0x00, -1);
		/* Read manufacturer and device IDs */
		if (nand_maf_id != chip->read_byte(mtd) ||
		    nand_dev_id != chip->read_byte(mtd))
			break;
	}
	if (i > 1)
<<<<<<< HEAD
<<<<<<< HEAD
		pr_info("%d NAND chips detected\n", i);
=======
		printk(KERN_INFO "%d NAND chips detected\n", i);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_INFO "%d NAND chips detected\n", i);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Store the number of chips and calc total size for mtd */
	chip->numchips = i;
	mtd->size = i * chip->chipsize;

	return 0;
}
EXPORT_SYMBOL(nand_scan_ident);

<<<<<<< HEAD
<<<<<<< HEAD

/**
 * nand_scan_tail - [NAND Interface] Scan for the NAND device
 * @mtd: MTD device structure
 *
 * This is the second phase of the normal nand_scan() function. It fills out
 * all the uninitialized function pointers with the defaults and scans for a
 * bad block table if appropriate.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void nand_panic_wait(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;
	int i;

	if (chip->state != FL_READY)
		for (i = 0; i < 40; i++) {
			if (chip->dev_ready(mtd))
				break;
			mdelay(10);
		}
	chip->state = FL_READY;
}

static int nand_panic_write(struct mtd_info *mtd, loff_t to, size_t len,
			    size_t *retlen, const u_char *buf)
{
	struct nand_chip *chip = mtd->priv;
	int ret;

	/* Do not allow reads past end of device */
	if ((to + len) > mtd->size)
		return -EINVAL;
	if (!len)
		return 0;

	nand_panic_wait(mtd);

	chip->ops.len = len;
	chip->ops.datbuf = (uint8_t *)buf;
	chip->ops.oobbuf = NULL;

	ret = nand_do_write_ops(mtd, to, &chip->ops);

	*retlen = chip->ops.retlen;
	return ret;
}


/**
 * nand_scan_tail - [NAND Interface] Scan for the NAND device
 * @mtd:	    MTD device structure
 *
 * This is the second phase of the normal nand_scan() function. It
 * fills out all the uninitialized function pointers with the defaults
 * and scans for a bad block table if appropriate.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
int nand_scan_tail(struct mtd_info *mtd)
{
	int i;
	struct nand_chip *chip = mtd->priv;

<<<<<<< HEAD
<<<<<<< HEAD
	/* New bad blocks should be marked in OOB, flash-based BBT, or both */
	BUG_ON((chip->bbt_options & NAND_BBT_NO_OOB_BBM) &&
			!(chip->bbt_options & NAND_BBT_USE_FLASH));

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!(chip->options & NAND_OWN_BUFFERS))
		chip->buffers = kmalloc(sizeof(*chip->buffers), GFP_KERNEL);
	if (!chip->buffers)
		return -ENOMEM;

	/* Set the internal oob buffer location, just after the page data */
	chip->oob_poi = chip->buffers->databuf + mtd->writesize;

	/*
<<<<<<< HEAD
<<<<<<< HEAD
	 * If no default placement scheme is given, select an appropriate one.
=======
	 * If no default placement scheme is given, select an appropriate one
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * If no default placement scheme is given, select an appropriate one
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	if (!chip->ecc.layout && (chip->ecc.mode != NAND_ECC_SOFT_BCH)) {
		switch (mtd->oobsize) {
		case 8:
			chip->ecc.layout = &nand_oob_8;
			break;
		case 16:
			chip->ecc.layout = &nand_oob_16;
			break;
		case 64:
			chip->ecc.layout = &nand_oob_64;
			break;
		case 128:
			chip->ecc.layout = &nand_oob_128;
			break;
		default:
<<<<<<< HEAD
<<<<<<< HEAD
			pr_warn("No oob scheme defined for oobsize %d\n",
				   mtd->oobsize);
=======
			printk(KERN_WARNING "No oob scheme defined for "
			       "oobsize %d\n", mtd->oobsize);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			printk(KERN_WARNING "No oob scheme defined for "
			       "oobsize %d\n", mtd->oobsize);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			BUG();
		}
	}

	if (!chip->write_page)
		chip->write_page = nand_write_page;

	/*
<<<<<<< HEAD
<<<<<<< HEAD
	 * Check ECC mode, default to software if 3byte/512byte hardware ECC is
=======
	 * check ECC mode, default to software if 3byte/512byte hardware ECC is
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	 * check ECC mode, default to software if 3byte/512byte hardware ECC is
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 * selected and we have 256 byte pagesize fallback to software ECC
	 */

	switch (chip->ecc.mode) {
	case NAND_ECC_HW_OOB_FIRST:
		/* Similar to NAND_ECC_HW, but a separate read_page handle */
		if (!chip->ecc.calculate || !chip->ecc.correct ||
		     !chip->ecc.hwctl) {
<<<<<<< HEAD
<<<<<<< HEAD
			pr_warn("No ECC functions supplied; "
				   "hardware ECC not possible\n");
=======
			printk(KERN_WARNING "No ECC functions supplied; "
			       "Hardware ECC not possible\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			printk(KERN_WARNING "No ECC functions supplied; "
			       "Hardware ECC not possible\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			BUG();
		}
		if (!chip->ecc.read_page)
			chip->ecc.read_page = nand_read_page_hwecc_oob_first;

	case NAND_ECC_HW:
<<<<<<< HEAD
<<<<<<< HEAD
		/* Use standard hwecc read page function? */
=======
		/* Use standard hwecc read page function ? */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		/* Use standard hwecc read page function ? */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!chip->ecc.read_page)
			chip->ecc.read_page = nand_read_page_hwecc;
		if (!chip->ecc.write_page)
			chip->ecc.write_page = nand_write_page_hwecc;
		if (!chip->ecc.read_page_raw)
			chip->ecc.read_page_raw = nand_read_page_raw;
		if (!chip->ecc.write_page_raw)
			chip->ecc.write_page_raw = nand_write_page_raw;
		if (!chip->ecc.read_oob)
			chip->ecc.read_oob = nand_read_oob_std;
		if (!chip->ecc.write_oob)
			chip->ecc.write_oob = nand_write_oob_std;

	case NAND_ECC_HW_SYNDROME:
		if ((!chip->ecc.calculate || !chip->ecc.correct ||
		     !chip->ecc.hwctl) &&
		    (!chip->ecc.read_page ||
		     chip->ecc.read_page == nand_read_page_hwecc ||
		     !chip->ecc.write_page ||
		     chip->ecc.write_page == nand_write_page_hwecc)) {
<<<<<<< HEAD
<<<<<<< HEAD
			pr_warn("No ECC functions supplied; "
				   "hardware ECC not possible\n");
			BUG();
		}
		/* Use standard syndrome read/write page function? */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			printk(KERN_WARNING "No ECC functions supplied; "
			       "Hardware ECC not possible\n");
			BUG();
		}
		/* Use standard syndrome read/write page function ? */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		if (!chip->ecc.read_page)
			chip->ecc.read_page = nand_read_page_syndrome;
		if (!chip->ecc.write_page)
			chip->ecc.write_page = nand_write_page_syndrome;
		if (!chip->ecc.read_page_raw)
			chip->ecc.read_page_raw = nand_read_page_raw_syndrome;
		if (!chip->ecc.write_page_raw)
			chip->ecc.write_page_raw = nand_write_page_raw_syndrome;
		if (!chip->ecc.read_oob)
			chip->ecc.read_oob = nand_read_oob_syndrome;
		if (!chip->ecc.write_oob)
			chip->ecc.write_oob = nand_write_oob_syndrome;

		if (mtd->writesize >= chip->ecc.size)
			break;
<<<<<<< HEAD
<<<<<<< HEAD
		pr_warn("%d byte HW ECC not possible on "
			   "%d byte page size, fallback to SW ECC\n",
			   chip->ecc.size, mtd->writesize);
=======
		printk(KERN_WARNING "%d byte HW ECC not possible on "
		       "%d byte page size, fallback to SW ECC\n",
		       chip->ecc.size, mtd->writesize);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_WARNING "%d byte HW ECC not possible on "
		       "%d byte page size, fallback to SW ECC\n",
		       chip->ecc.size, mtd->writesize);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		chip->ecc.mode = NAND_ECC_SOFT;

	case NAND_ECC_SOFT:
		chip->ecc.calculate = nand_calculate_ecc;
		chip->ecc.correct = nand_correct_data;
		chip->ecc.read_page = nand_read_page_swecc;
		chip->ecc.read_subpage = nand_read_subpage;
		chip->ecc.write_page = nand_write_page_swecc;
		chip->ecc.read_page_raw = nand_read_page_raw;
		chip->ecc.write_page_raw = nand_write_page_raw;
		chip->ecc.read_oob = nand_read_oob_std;
		chip->ecc.write_oob = nand_write_oob_std;
		if (!chip->ecc.size)
			chip->ecc.size = 256;
		chip->ecc.bytes = 3;
<<<<<<< HEAD
<<<<<<< HEAD
		chip->ecc.strength = 1;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;

	case NAND_ECC_SOFT_BCH:
		if (!mtd_nand_has_bch()) {
<<<<<<< HEAD
<<<<<<< HEAD
			pr_warn("CONFIG_MTD_ECC_BCH not enabled\n");
=======
			printk(KERN_WARNING "CONFIG_MTD_ECC_BCH not enabled\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			printk(KERN_WARNING "CONFIG_MTD_ECC_BCH not enabled\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			BUG();
		}
		chip->ecc.calculate = nand_bch_calculate_ecc;
		chip->ecc.correct = nand_bch_correct_data;
		chip->ecc.read_page = nand_read_page_swecc;
		chip->ecc.read_subpage = nand_read_subpage;
		chip->ecc.write_page = nand_write_page_swecc;
		chip->ecc.read_page_raw = nand_read_page_raw;
		chip->ecc.write_page_raw = nand_write_page_raw;
		chip->ecc.read_oob = nand_read_oob_std;
		chip->ecc.write_oob = nand_write_oob_std;
		/*
		 * Board driver should supply ecc.size and ecc.bytes values to
		 * select how many bits are correctable; see nand_bch_init()
<<<<<<< HEAD
<<<<<<< HEAD
		 * for details. Otherwise, default to 4 bits for large page
		 * devices.
=======
		 * for details.
		 * Otherwise, default to 4 bits for large page devices
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		 * for details.
		 * Otherwise, default to 4 bits for large page devices
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		 */
		if (!chip->ecc.size && (mtd->oobsize >= 64)) {
			chip->ecc.size = 512;
			chip->ecc.bytes = 7;
		}
		chip->ecc.priv = nand_bch_init(mtd,
					       chip->ecc.size,
					       chip->ecc.bytes,
					       &chip->ecc.layout);
		if (!chip->ecc.priv) {
<<<<<<< HEAD
<<<<<<< HEAD
			pr_warn("BCH ECC initialization failed!\n");
			BUG();
		}
		chip->ecc.strength =
			chip->ecc.bytes*8 / fls(8*chip->ecc.size);
		break;

	case NAND_ECC_NONE:
		pr_warn("NAND_ECC_NONE selected by board driver. "
			   "This is not recommended!\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			printk(KERN_WARNING "BCH ECC initialization failed!\n");
			BUG();
		}
		break;

	case NAND_ECC_NONE:
		printk(KERN_WARNING "NAND_ECC_NONE selected by board driver. "
		       "This is not recommended !!\n");
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		chip->ecc.read_page = nand_read_page_raw;
		chip->ecc.write_page = nand_write_page_raw;
		chip->ecc.read_oob = nand_read_oob_std;
		chip->ecc.read_page_raw = nand_read_page_raw;
		chip->ecc.write_page_raw = nand_write_page_raw;
		chip->ecc.write_oob = nand_write_oob_std;
		chip->ecc.size = mtd->writesize;
		chip->ecc.bytes = 0;
<<<<<<< HEAD
<<<<<<< HEAD
		chip->ecc.strength = 0;
		break;

	default:
		pr_warn("Invalid NAND_ECC_MODE %d\n", chip->ecc.mode);
		BUG();
	}

	/* For many systems, the standard OOB write also works for raw */
	if (!chip->ecc.read_oob_raw)
		chip->ecc.read_oob_raw = chip->ecc.read_oob;
	if (!chip->ecc.write_oob_raw)
		chip->ecc.write_oob_raw = chip->ecc.write_oob;

	/*
	 * The number of bytes available for a client to place data into
	 * the out of band area.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;

	default:
		printk(KERN_WARNING "Invalid NAND_ECC_MODE %d\n",
		       chip->ecc.mode);
		BUG();
	}

	/*
	 * The number of bytes available for a client to place data into
	 * the out of band area
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	chip->ecc.layout->oobavail = 0;
	for (i = 0; chip->ecc.layout->oobfree[i].length
			&& i < ARRAY_SIZE(chip->ecc.layout->oobfree); i++)
		chip->ecc.layout->oobavail +=
			chip->ecc.layout->oobfree[i].length;
	mtd->oobavail = chip->ecc.layout->oobavail;

	/*
	 * Set the number of read / write steps for one page depending on ECC
<<<<<<< HEAD
<<<<<<< HEAD
	 * mode.
	 */
	chip->ecc.steps = mtd->writesize / chip->ecc.size;
	if (chip->ecc.steps * chip->ecc.size != mtd->writesize) {
		pr_warn("Invalid ECC parameters\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 * mode
	 */
	chip->ecc.steps = mtd->writesize / chip->ecc.size;
	if (chip->ecc.steps * chip->ecc.size != mtd->writesize) {
		printk(KERN_WARNING "Invalid ecc parameters\n");
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		BUG();
	}
	chip->ecc.total = chip->ecc.steps * chip->ecc.bytes;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Allow subpage writes up to ecc.steps. Not possible for MLC flash */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * Allow subpage writes up to ecc.steps. Not possible for MLC
	 * FLASH.
	 */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!(chip->options & NAND_NO_SUBPAGE_WRITE) &&
	    !(chip->cellinfo & NAND_CI_CELLTYPE_MSK)) {
		switch (chip->ecc.steps) {
		case 2:
			mtd->subpage_sft = 1;
			break;
		case 4:
		case 8:
		case 16:
			mtd->subpage_sft = 2;
			break;
		}
	}
	chip->subpagesize = mtd->writesize >> mtd->subpage_sft;

	/* Initialize state */
	chip->state = FL_READY;

	/* De-select the device */
	chip->select_chip(mtd, -1);

	/* Invalidate the pagebuffer reference */
	chip->pagebuf = -1;

	/* Fill in remaining MTD driver data */
	mtd->type = MTD_NANDFLASH;
	mtd->flags = (chip->options & NAND_ROM) ? MTD_CAP_ROM :
						MTD_CAP_NANDFLASH;
<<<<<<< HEAD
<<<<<<< HEAD
	mtd->_erase = nand_erase;
	mtd->_point = NULL;
	mtd->_unpoint = NULL;
	mtd->_read = nand_read;
	mtd->_write = nand_write;
	mtd->_panic_write = panic_nand_write;
	mtd->_read_oob = nand_read_oob;
	mtd->_write_oob = nand_write_oob;
	mtd->_sync = nand_sync;
	mtd->_lock = NULL;
	mtd->_unlock = NULL;
	mtd->_suspend = nand_suspend;
	mtd->_resume = nand_resume;
	mtd->_block_isbad = nand_block_isbad;
	mtd->_block_markbad = nand_block_markbad;
	mtd->writebufsize = mtd->writesize;

	/* propagate ecc info to mtd_info */
	mtd->ecclayout = chip->ecc.layout;
	mtd->ecc_strength = chip->ecc.strength * chip->ecc.steps;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mtd->erase = nand_erase;
	mtd->point = NULL;
	mtd->unpoint = NULL;
	mtd->read = nand_read;
	mtd->write = nand_write;
	mtd->panic_write = panic_nand_write;
	mtd->read_oob = nand_read_oob;
	mtd->write_oob = nand_write_oob;
	mtd->panic_write = nand_panic_write;
	mtd->sync = nand_sync;
	mtd->lock = NULL;
	mtd->unlock = NULL;
	mtd->suspend = nand_suspend;
	mtd->resume = nand_resume;
	mtd->block_isbad = nand_block_isbad;
	mtd->block_markbad = nand_block_markbad;
	mtd->writebufsize = mtd->writesize;

	/* propagate ecc.layout to mtd_info */
	mtd->ecclayout = chip->ecc.layout;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Check, if we should skip the bad block table scan */
	if (chip->options & NAND_SKIP_BBTSCAN)
		return 0;

	/* Build bad block table */
	return chip->scan_bbt(mtd);
}
EXPORT_SYMBOL(nand_scan_tail);

<<<<<<< HEAD
<<<<<<< HEAD
/*
 * is_module_text_address() isn't exported, and it's mostly a pointless
 * test if this is a module _anyway_ -- they'd have to try _really_ hard
 * to call us from in-kernel code if the core NAND support is modular.
 */
=======
/* is_module_text_address() isn't exported, and it's mostly a pointless
 * test if this is a module _anyway_ -- they'd have to try _really_ hard
 * to call us from in-kernel code if the core NAND support is modular. */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
/* is_module_text_address() isn't exported, and it's mostly a pointless
 * test if this is a module _anyway_ -- they'd have to try _really_ hard
 * to call us from in-kernel code if the core NAND support is modular. */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifdef MODULE
#define caller_is_module() (1)
#else
#define caller_is_module() \
	is_module_text_address((unsigned long)__builtin_return_address(0))
#endif

/**
 * nand_scan - [NAND Interface] Scan for the NAND device
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 * @maxchips: number of chips to scan for
 *
 * This fills out all the uninitialized function pointers with the defaults.
 * The flash ID is read and the mtd/chip structures are filled with the
 * appropriate values. The mtd->owner field must be set to the module of the
 * caller.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @mtd:	MTD device structure
 * @maxchips:	Number of chips to scan for
 *
 * This fills out all the uninitialized function pointers
 * with the defaults.
 * The flash ID is read and the mtd/chip structures are
 * filled with the appropriate values.
 * The mtd->owner field must be set to the module of the caller
 *
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
int nand_scan(struct mtd_info *mtd, int maxchips)
{
	int ret;

	/* Many callers got this wrong, so check for it for a while... */
	if (!mtd->owner && caller_is_module()) {
<<<<<<< HEAD
<<<<<<< HEAD
		pr_crit("%s called with NULL mtd->owner!\n", __func__);
=======
		printk(KERN_CRIT "%s called with NULL mtd->owner!\n",
				__func__);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		printk(KERN_CRIT "%s called with NULL mtd->owner!\n",
				__func__);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		BUG();
	}

	ret = nand_scan_ident(mtd, maxchips, NULL);
	if (!ret)
		ret = nand_scan_tail(mtd);
	return ret;
}
EXPORT_SYMBOL(nand_scan);

/**
 * nand_release - [NAND Interface] Free resources held by the NAND device
<<<<<<< HEAD
<<<<<<< HEAD
 * @mtd: MTD device structure
 */
=======
 * @mtd:	MTD device structure
*/
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * @mtd:	MTD device structure
*/
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void nand_release(struct mtd_info *mtd)
{
	struct nand_chip *chip = mtd->priv;

	if (chip->ecc.mode == NAND_ECC_SOFT_BCH)
		nand_bch_free((struct nand_bch_control *)chip->ecc.priv);

	mtd_device_unregister(mtd);

	/* Free bad block table memory */
	kfree(chip->bbt);
	if (!(chip->options & NAND_OWN_BUFFERS))
		kfree(chip->buffers);

	/* Free bad block descriptor memory */
	if (chip->badblock_pattern && chip->badblock_pattern->options
			& NAND_BBT_DYNAMICSTRUCT)
		kfree(chip->badblock_pattern);
}
EXPORT_SYMBOL_GPL(nand_release);

static int __init nand_base_init(void)
{
	led_trigger_register_simple("nand-disk", &nand_led_trigger);
	return 0;
}

static void __exit nand_base_exit(void)
{
	led_trigger_unregister_simple(nand_led_trigger);
}

module_init(nand_base_init);
module_exit(nand_base_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Steven J. Hill <sjhill@realitydiluted.com>");
MODULE_AUTHOR("Thomas Gleixner <tglx@linutronix.de>");
MODULE_DESCRIPTION("Generic NAND flash driver code");
