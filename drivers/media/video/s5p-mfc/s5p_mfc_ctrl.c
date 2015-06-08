/*
 * linux/drivers/media/video/s5p-mfc/s5p_mfc_ctrl.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/delay.h>
<<<<<<< HEAD
#include <linux/err.h>
#include <linux/firmware.h>
#include <linux/jiffies.h>
#include <linux/sched.h>
#include "regs-mfc.h"
#include "s5p_mfc_cmd.h"
#include "s5p_mfc_common.h"
#include "s5p_mfc_debug.h"
#include "s5p_mfc_intr.h"
#include "s5p_mfc_pm.h"

static void *s5p_mfc_bitproc_buf;
static size_t s5p_mfc_bitproc_phys;
static unsigned char *s5p_mfc_bitproc_virt;

/* Allocate and load firmware */
int s5p_mfc_alloc_and_load_firmware(struct s5p_mfc_dev *dev)
{
	struct firmware *fw_blob;
	size_t bank2_base_phys;
	void *b_base;
	int err;

	/* Firmare has to be present as a separate file or compiled
	 * into kernel. */
	mfc_debug_enter();
	err = request_firmware((const struct firmware **)&fw_blob,
				     "s5p-mfc.fw", dev->v4l2_dev.dev);
	if (err != 0) {
		mfc_err("Firmware is not present in the /lib/firmware directory nor compiled in kernel\n");
		return -EINVAL;
	}
	dev->fw_size = ALIGN(fw_blob->size, FIRMWARE_ALIGN);
	if (s5p_mfc_bitproc_buf) {
		mfc_err("Attempting to allocate firmware when it seems that it is already loaded\n");
		release_firmware(fw_blob);
		return -ENOMEM;
	}
	s5p_mfc_bitproc_buf = vb2_dma_contig_memops.alloc(
		dev->alloc_ctx[MFC_BANK1_ALLOC_CTX], dev->fw_size);
	if (IS_ERR(s5p_mfc_bitproc_buf)) {
		s5p_mfc_bitproc_buf = 0;
		mfc_err("Allocating bitprocessor buffer failed\n");
		release_firmware(fw_blob);
		return -ENOMEM;
	}
	s5p_mfc_bitproc_phys = s5p_mfc_mem_cookie(
		dev->alloc_ctx[MFC_BANK1_ALLOC_CTX], s5p_mfc_bitproc_buf);
	if (s5p_mfc_bitproc_phys & ((1 << MFC_BASE_ALIGN_ORDER) - 1)) {
		mfc_err("The base memory for bank 1 is not aligned to 128KB\n");
		vb2_dma_contig_memops.put(s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		release_firmware(fw_blob);
		return -EIO;
	}
	s5p_mfc_bitproc_virt = vb2_dma_contig_memops.vaddr(s5p_mfc_bitproc_buf);
	if (!s5p_mfc_bitproc_virt) {
		mfc_err("Bitprocessor memory remap failed\n");
		vb2_dma_contig_memops.put(s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		release_firmware(fw_blob);
		return -EIO;
	}
	dev->bank1 = s5p_mfc_bitproc_phys;
	b_base = vb2_dma_contig_memops.alloc(
		dev->alloc_ctx[MFC_BANK2_ALLOC_CTX], 1 << MFC_BANK2_ALIGN_ORDER);
	if (IS_ERR(b_base)) {
		vb2_dma_contig_memops.put(s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		mfc_err("Allocating bank2 base failed\n");
	release_firmware(fw_blob);
		return -ENOMEM;
	}
	bank2_base_phys = s5p_mfc_mem_cookie(
		dev->alloc_ctx[MFC_BANK2_ALLOC_CTX], b_base);
	vb2_dma_contig_memops.put(b_base);
	if (bank2_base_phys & ((1 << MFC_BASE_ALIGN_ORDER) - 1)) {
		mfc_err("The base memory for bank 2 is not aligned to 128KB\n");
		vb2_dma_contig_memops.put(s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		release_firmware(fw_blob);
		return -EIO;
	}
	dev->bank2 = bank2_base_phys;
	memcpy(s5p_mfc_bitproc_virt, fw_blob->data, fw_blob->size);
	wmb();
	release_firmware(fw_blob);
	mfc_debug_leave();
	return 0;
}

/* Reload firmware to MFC */
int s5p_mfc_reload_firmware(struct s5p_mfc_dev *dev)
{
	struct firmware *fw_blob;
=======
#include <linux/jiffies.h>

#include <linux/firmware.h>
#include <linux/err.h>
#include <linux/sched.h>
#include <linux/cma.h>

#include "s5p_mfc_common.h"

#include "s5p_mfc_mem.h"
#include "s5p_mfc_intr.h"
#include "s5p_mfc_debug.h"
#include "s5p_mfc_reg.h"
#include "s5p_mfc_cmd.h"
#include "s5p_mfc_pm.h"

static void *s5p_mfc_bitproc_buf;
static dma_addr_t s5p_mfc_bitproc_phys;
static unsigned char *s5p_mfc_bitproc_virt;
//static dma_addr_t s5p_mfc_bitproc_dma;

/* Allocate firmware */
int s5p_mfc_alloc_firmware(struct s5p_mfc_dev *dev)
{
#if defined(CONFIG_S5P_MFC_VB2_CMA)
	int err;
	struct cma_info mem_info_f, mem_info_a, mem_info_b;
#endif
	unsigned int base_align = dev->variant->buf_align->mfc_base_align;
	unsigned int firmware_size = dev->variant->buf_size->firmware_code;

	mfc_debug_enter();

#if !defined(CONFIG_S5P_MFC_VB2_ION)
	if (s5p_mfc_bitproc_buf) {
		mfc_err("Attempting to allocate firmware when it seems that it is already loaded.\n");
		return -ENOMEM;
	}
#else
	if (s5p_mfc_bitproc_buf)
		return 0;
#endif

	/* Get memory region information and check if it is correct */
#if defined(CONFIG_S5P_MFC_VB2_CMA)
	err = cma_info(&mem_info_f, dev->v4l2_dev.dev, MFC_CMA_FW);
	mfc_debug(3, "Area \"%s\" is from %08x to %08x and has size %08x", "f",
				mem_info_f.lower_bound, mem_info_f.upper_bound,
							mem_info_f.total_size);
	if (err) {
		mfc_err("Couldn't get memory information from CMA.\n");
		return -EINVAL;
	}
	err = cma_info(&mem_info_a, dev->v4l2_dev.dev, MFC_CMA_BANK1);
	mfc_debug(3, "Area \"%s\" is from %08x to %08x and has size %08x", "a",
			mem_info_a.lower_bound, mem_info_a.upper_bound,
						mem_info_a.total_size);
	if (err) {
		mfc_err("Couldn't get memory information from CMA.\n");
		return -EINVAL;
	}

	if (mem_info_f.upper_bound > mem_info_a.lower_bound) {
			mfc_err("Firmware has to be "
			"allocated before  memory for buffers (bank A).\n");
		return -EINVAL;
	}
	mfc_debug(2, "Allocating memory for firmware.\n");
	s5p_mfc_bitproc_buf = s5p_mfc_mem_allocate(
		dev->alloc_ctx[MFC_CMA_FW_ALLOC_CTX], firmware_size);
	if (IS_ERR(s5p_mfc_bitproc_buf)) {
		s5p_mfc_bitproc_buf = 0;
		printk(KERN_ERR "Allocating bitprocessor buffer failed\n");
		return -ENOMEM;
	}
	s5p_mfc_bitproc_phys = s5p_mfc_mem_dma_addr(s5p_mfc_bitproc_buf);

	if (s5p_mfc_bitproc_phys & ((1 << base_align) - 1)) {
		mfc_err("The base memory is not aligned to %dBytes.\n",
				(1 << base_align));
		s5p_mfc_mem_free(s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		return -EIO;
	}
	dev->port_a = s5p_mfc_bitproc_phys;

	s5p_mfc_bitproc_virt = s5p_mfc_mem_vaddr(s5p_mfc_bitproc_buf);

	mfc_debug(2, "Virtual address for FW: %08lx\n",
				(long unsigned int)s5p_mfc_bitproc_virt);
	if (!s5p_mfc_bitproc_virt) {
		mfc_err("Bitprocessor memory remap failed\n");
		s5p_mfc_mem_free(s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		return -EIO;
	}

	if (HAS_PORTNUM(dev) && IS_TWOPORT(dev)) {
		err = cma_info(&mem_info_b, dev->v4l2_dev.dev, MFC_CMA_BANK2);
		mfc_debug(3, "Area \"%s\" is from %08x to %08x and has size %08x", "b",
				mem_info_b.lower_bound, mem_info_b.upper_bound,
				mem_info_b.total_size);
		if (err) {
			mfc_err("Couldn't get memory information from CMA.\n");
			return -EINVAL;
		}
		dev->port_b = mem_info_b.lower_bound;
		mfc_debug(2, "Port A: %08x Port B: %08x (FW: %08x size: %08x)\n",
				dev->port_a, dev->port_b, s5p_mfc_bitproc_phys,
							firmware_size);
	} else {
		mfc_debug(2, "Port : %08x (FW: %08x size: %08x)\n",
				dev->port_a, s5p_mfc_bitproc_phys,
						firmware_size);
	}
#elif defined(CONFIG_S5P_MFC_VB2_SDVMM)
	mfc_debug(2, "Allocating memory for firmware.\n");
	s5p_mfc_bitproc_buf = s5p_mfc_mem_alloc(
		dev->alloc_ctx[MFC_CMA_FW_ALLOC_CTX], firmware_size);
	if (IS_ERR(s5p_mfc_bitproc_buf)) {
		s5p_mfc_bitproc_buf = 0;
		printk(KERN_ERR "Allocating bitprocessor buffer failed\n");
		return -ENOMEM;
	}

	s5p_mfc_bitproc_phys = s5p_mfc_mem_cookie(
		dev->alloc_ctx[MFC_CMA_FW_ALLOC_CTX], s5p_mfc_bitproc_buf);
	if (s5p_mfc_bitproc_phys & ((1 << base_align) - 1)) {
		mfc_err("The base memory is not aligned to %dBytes.\n",
				(1 << base_align));
		s5p_mfc_mem_put(dev->alloc_ctx[MFC_CMA_FW_ALLOC_CTX],
							s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		return -EIO;
	}

	s5p_mfc_bitproc_virt = s5p_mfc_mem_vaddr(
		dev->alloc_ctx[MFC_CMA_FW_ALLOC_CTX], s5p_mfc_bitproc_buf);
	mfc_debug(2, "Virtual address for FW: %08lx\n",
				(long unsigned int)s5p_mfc_bitproc_virt);
	if (!s5p_mfc_bitproc_virt) {
		mfc_err("Bitprocessor memory remap failed\n");
		s5p_mfc_mem_put(dev->alloc_ctx[MFC_CMA_FW_ALLOC_CTX],
							s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		return -EIO;
	}

	dev->port_a = s5p_mfc_bitproc_phys;
	dev->port_b = s5p_mfc_bitproc_phys;

	mfc_debug(2, "Port A: %08x Port B: %08x (FW: %08x size: %08x)\n",
			dev->port_a, dev->port_b,
			s5p_mfc_bitproc_phys,
			firmware_size);
#elif defined(CONFIG_S5P_MFC_VB2_ION)
	mfc_debug(2, "Allocating memory for firmware.\n");
	s5p_mfc_bitproc_buf = s5p_mfc_mem_allocate(
		dev->alloc_ctx[MFC_CMA_FW_ALLOC_CTX], firmware_size);
	if (IS_ERR(s5p_mfc_bitproc_buf)) {
		s5p_mfc_bitproc_buf = 0;
		printk(KERN_ERR "Allocating bitprocessor buffer failed\n");
		return -ENOMEM;
	}

	s5p_mfc_bitproc_phys = s5p_mfc_mem_dma_addr(s5p_mfc_bitproc_buf);
	if (s5p_mfc_bitproc_phys & ((1 << base_align) - 1)) {
		mfc_err("The base memory is not aligned to %dBytes.\n",
				(1 << base_align));
		s5p_mfc_mem_free(s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		return -EIO;
	}

	s5p_mfc_bitproc_virt = s5p_mfc_mem_vaddr(s5p_mfc_bitproc_buf);
	mfc_debug(2, "Virtual address for FW: %08lx\n",
				(long unsigned int)s5p_mfc_bitproc_virt);
	if (!s5p_mfc_bitproc_virt) {
		mfc_err("Bitprocessor memory remap failed\n");
		s5p_mfc_mem_free(s5p_mfc_bitproc_buf);
		s5p_mfc_bitproc_phys = 0;
		s5p_mfc_bitproc_buf = 0;
		return -EIO;
	}

	dev->port_a = s5p_mfc_bitproc_phys;
	dev->port_b = s5p_mfc_bitproc_phys;

	mfc_debug(2, "Port A: %08x Port B: %08x (FW: %08x size: %08x)\n",
			dev->port_a, dev->port_b,
			s5p_mfc_bitproc_phys,
			firmware_size);

#endif
	mfc_debug_leave();

	return 0;
}

/* Load firmware to MFC */
int s5p_mfc_load_firmware(struct s5p_mfc_dev *dev)
{
	struct firmware *fw_blob;
	unsigned int firmware_size = dev->variant->buf_size->firmware_code;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	int err;

	/* Firmare has to be present as a separate file or compiled
	 * into kernel. */
	mfc_debug_enter();
<<<<<<< HEAD
	err = request_firmware((const struct firmware **)&fw_blob,
				     "s5p-mfc.fw", dev->v4l2_dev.dev);
	if (err != 0) {
		mfc_err("Firmware is not present in the /lib/firmware directory nor compiled in kernel\n");
		return -EINVAL;
	}
	if (fw_blob->size > dev->fw_size) {
		mfc_err("MFC firmware is too big to be loaded\n");
=======
	mfc_debug(2, "Requesting fw\n");
	err = request_firmware((const struct firmware **)&fw_blob,
					MFC_FW_NAME, dev->v4l2_dev.dev);

	if (err != 0) {
		mfc_err("Firmware is not present in the /lib/firmware directory nor compiled in kernel.\n");
		return -EINVAL;
	}

	mfc_debug(2, "Ret of request_firmware: %d Size: %d\n", err, fw_blob->size);

	if (fw_blob->size > firmware_size) {
		mfc_err("MFC firmware is too big to be loaded.\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		release_firmware(fw_blob);
		return -ENOMEM;
	}
	if (s5p_mfc_bitproc_buf == 0 || s5p_mfc_bitproc_phys == 0) {
<<<<<<< HEAD
		mfc_err("MFC firmware is not allocated or was not mapped correctly\n");
=======
		mfc_err("MFC firmware is not allocated or was not mapped correctly.\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		release_firmware(fw_blob);
		return -EINVAL;
	}
	memcpy(s5p_mfc_bitproc_virt, fw_blob->data, fw_blob->size);
<<<<<<< HEAD
	wmb();
=======
	/*
	s5p_mfc_bitproc_dma = dma_map_single(dev->v4l2_dev.dev,
					     s5p_mfc_bitproc_virt,
					     FIRMWARE_CODE_SIZE,
					     DMA_TO_DEVICE);
	*/
	s5p_mfc_cache_clean_fw(s5p_mfc_bitproc_buf);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	release_firmware(fw_blob);
	mfc_debug_leave();
	return 0;
}

/* Release firmware memory */
int s5p_mfc_release_firmware(struct s5p_mfc_dev *dev)
{
	/* Before calling this function one has to make sure
	 * that MFC is no longer processing */
	if (!s5p_mfc_bitproc_buf)
		return -EINVAL;
<<<<<<< HEAD
	vb2_dma_contig_memops.put(s5p_mfc_bitproc_buf);
	s5p_mfc_bitproc_virt =  0;
	s5p_mfc_bitproc_phys = 0;
	s5p_mfc_bitproc_buf = 0;
=======
	/*
	if (s5p_mfc_bitproc_dma)
		dma_unmap_single(dev->v4l2_dev.dev, s5p_mfc_bitproc_dma,
				 FIRMWARE_CODE_SIZE, DMA_TO_DEVICE);
	*/
	s5p_mfc_mem_free(s5p_mfc_bitproc_buf);

	s5p_mfc_bitproc_virt =  0;
	s5p_mfc_bitproc_phys = 0;
	s5p_mfc_bitproc_buf = 0;
	/*
	s5p_mfc_bitproc_dma = 0;
	*/
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}

/* Reset the device */
<<<<<<< HEAD
int s5p_mfc_reset(struct s5p_mfc_dev *dev)
{
	unsigned int mc_status;
	unsigned long timeout;

	mfc_debug_enter();
	/* Stop procedure */
	/*  reset RISC */
	mfc_write(dev, 0x3f6, S5P_FIMV_SW_RESET);
	/*  All reset except for MC */
	mfc_write(dev, 0x3e2, S5P_FIMV_SW_RESET);
	mdelay(10);

	timeout = jiffies + msecs_to_jiffies(MFC_BW_TIMEOUT);
	/* Check MC status */
	do {
		if (time_after(jiffies, timeout)) {
			mfc_err("Timeout while resetting MFC\n");
			return -EIO;
		}

		mc_status = mfc_read(dev, S5P_FIMV_MC_STATUS);

	} while (mc_status & 0x3);

	mfc_write(dev, 0x0, S5P_FIMV_SW_RESET);
	mfc_write(dev, 0x3fe, S5P_FIMV_SW_RESET);
	mfc_debug_leave();
=======
static int s5p_mfc_reset(struct s5p_mfc_dev *dev)
{
	int i;
	unsigned int status;
	unsigned long timeout;

	mfc_debug_enter();

	/* Stop procedure */
	/* FIXME: F/W can be access invalid address */
	/* Reset VI */
	/*
	s5p_mfc_write_reg(0x3f7, S5P_FIMV_SW_RESET);
	*/

	if (IS_MFCV6(dev)) {
		/* Reset IP */
		s5p_mfc_write_reg(0xFEE, S5P_FIMV_MFC_RESET);	/*  except RISC, reset */
		s5p_mfc_write_reg(0x0, S5P_FIMV_MFC_RESET);	/*  reset release */

		/* Zero Initialization of MFC registers */
		s5p_mfc_write_reg(0, S5P_FIMV_RISC2HOST_CMD);
		s5p_mfc_write_reg(0, S5P_FIMV_HOST2RISC_CMD);
		s5p_mfc_write_reg(0, S5P_FIMV_FW_VERSION);

		for (i = 0; i < S5P_FIMV_REG_CLEAR_COUNT; i++)
			s5p_mfc_write_reg(0, S5P_FIMV_REG_CLEAR_BEGIN + (i*4));

		/* Reset */
		s5p_mfc_write_reg(0x1, S5P_FIMV_MFC_BUS_RESET_CTRL);

		timeout = jiffies + msecs_to_jiffies(MFC_BW_TIMEOUT);
		/* Check bus status */
		do {
			if (time_after(jiffies, timeout)) {
				mfc_err("Timeout while resetting MFC.\n");
				return -EIO;
			}
			status = s5p_mfc_read_reg(S5P_FIMV_MFC_BUS_RESET_CTRL);
		} while ((status & 0x2) == 0);

		s5p_mfc_write_reg(0, S5P_FIMV_RISC_ON);
		s5p_mfc_write_reg(0x1FFF, S5P_FIMV_MFC_RESET);
		s5p_mfc_write_reg(0, S5P_FIMV_MFC_RESET);
	} else {
		s5p_mfc_write_reg(0x3f6, S5P_FIMV_SW_RESET);	/*  reset RISC */
		s5p_mfc_write_reg(0x3e2, S5P_FIMV_SW_RESET);	/*  All reset except for MC */
		mdelay(10);

		timeout = jiffies + msecs_to_jiffies(MFC_BW_TIMEOUT);

		/* Check MC status */
		do {
			if (time_after(jiffies, timeout)) {
				mfc_err("Timeout while resetting MFC.\n");
				return -EIO;
			}

			status = s5p_mfc_read_reg(S5P_FIMV_MC_STATUS);

		} while (status & 0x3);

		s5p_mfc_write_reg(0x0, S5P_FIMV_SW_RESET);
		s5p_mfc_write_reg(0x3fe, S5P_FIMV_SW_RESET);
	}

	mfc_debug_leave();

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}

static inline void s5p_mfc_init_memctrl(struct s5p_mfc_dev *dev)
{
<<<<<<< HEAD
	mfc_write(dev, dev->bank1, S5P_FIMV_MC_DRAMBASE_ADR_A);
	mfc_write(dev, dev->bank2, S5P_FIMV_MC_DRAMBASE_ADR_B);
	mfc_debug(2, "Bank1: %08x, Bank2: %08x\n", dev->bank1, dev->bank2);
=======
	if (IS_MFCV6(dev)) {
		s5p_mfc_write_reg(dev->port_a, S5P_FIMV_RISC_BASE_ADDRESS);
		mfc_debug(2, "Base Address : %08x\n", dev->port_a);
	} else {
		/* channelA, port0 */
		s5p_mfc_write_reg(dev->port_a, S5P_FIMV_MC_DRAMBASE_ADR_A);
		/* channelB, port1 */
		s5p_mfc_write_reg(dev->port_b, S5P_FIMV_MC_DRAMBASE_ADR_B);

		mfc_debug(2, "Port A: %08x, Port B: %08x\n", dev->port_a, dev->port_b);
	}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

static inline void s5p_mfc_clear_cmds(struct s5p_mfc_dev *dev)
{
<<<<<<< HEAD
	mfc_write(dev, 0xffffffff, S5P_FIMV_SI_CH0_INST_ID);
	mfc_write(dev, 0xffffffff, S5P_FIMV_SI_CH1_INST_ID);
	mfc_write(dev, 0, S5P_FIMV_RISC2HOST_CMD);
	mfc_write(dev, 0, S5P_FIMV_HOST2RISC_CMD);
=======
	if (IS_MFCV6(dev)) {
		/* Zero initialization should be done before RESET.
		 * Nothing to do here. */
	} else {
		s5p_mfc_write_reg(0xffffffff, S5P_FIMV_SI_CH0_INST_ID);
		s5p_mfc_write_reg(0xffffffff, S5P_FIMV_SI_CH1_INST_ID);

		s5p_mfc_write_reg(0, S5P_FIMV_RISC2HOST_CMD);
		s5p_mfc_write_reg(0, S5P_FIMV_HOST2RISC_CMD);
	}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

/* Initialize hardware */
int s5p_mfc_init_hw(struct s5p_mfc_dev *dev)
{
<<<<<<< HEAD
	unsigned int ver;
	int ret;

	mfc_debug_enter();
=======
	char dvx_info;
	int mfc_info;
	int ret = 0;

	mfc_debug_enter();

	/* RMVME: */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (!s5p_mfc_bitproc_buf)
		return -EINVAL;

	/* 0. MFC reset */
<<<<<<< HEAD
	mfc_debug(2, "MFC reset..\n");
	s5p_mfc_clock_on();
	ret = s5p_mfc_reset(dev);
	if (ret) {
		mfc_err("Failed to reset MFC - timeout\n");
		return ret;
	}
	mfc_debug(2, "Done MFC reset..\n");
	/* 1. Set DRAM base Addr */
	s5p_mfc_init_memctrl(dev);
	/* 2. Initialize registers of channel I/F */
	s5p_mfc_clear_cmds(dev);
	/* 3. Release reset signal to the RISC */
	s5p_mfc_clean_dev_int_flags(dev);
	mfc_write(dev, 0x3ff, S5P_FIMV_SW_RESET);
	mfc_debug(2, "Will now wait for completion of firmware transfer\n");
	if (s5p_mfc_wait_for_done_dev(dev, S5P_FIMV_R2H_CMD_FW_STATUS_RET)) {
		mfc_err("Failed to load firmware\n");
		s5p_mfc_reset(dev);
		s5p_mfc_clock_off();
		return -EIO;
	}
=======
	mfc_debug(2, "MFC reset...\n");

	s5p_mfc_clock_on();

	ret = s5p_mfc_reset(dev);
	if (ret) {
		mfc_err("Failed to reset MFC - timeout.\n");
		goto err_init_hw;
	}
	mfc_debug(2, "Done MFC reset...\n");

	/* 1. Set DRAM base Addr */
	s5p_mfc_init_memctrl(dev);

	/* 2. Initialize registers of channel I/F */
	s5p_mfc_clear_cmds(dev);

	/* 3. Release reset signal to the RISC */
	if (IS_MFCV6(dev))
		s5p_mfc_write_reg(0x1, S5P_FIMV_RISC_ON);
	else
		s5p_mfc_write_reg(0x3ff, S5P_FIMV_SW_RESET);

	mfc_debug(2, "Will now wait for completion of firmware transfer.\n");
	if (s5p_mfc_wait_for_done_dev(dev, S5P_FIMV_R2H_CMD_FW_STATUS_RET)) {
		mfc_err("Failed to load firmware.\n");
		s5p_mfc_clean_dev_int_flags(dev);
		ret = -EIO;
		goto err_init_hw;
	}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	s5p_mfc_clean_dev_int_flags(dev);
	/* 4. Initialize firmware */
	ret = s5p_mfc_sys_init_cmd(dev);
	if (ret) {
<<<<<<< HEAD
		mfc_err("Failed to send command to MFC - timeout\n");
		s5p_mfc_reset(dev);
		s5p_mfc_clock_off();
		return ret;
=======
		mfc_err("Failed to send command to MFC - timeout.\n");
		goto err_init_hw;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	}
	mfc_debug(2, "Ok, now will write a command to init the system\n");
	if (s5p_mfc_wait_for_done_dev(dev, S5P_FIMV_R2H_CMD_SYS_INIT_RET)) {
		mfc_err("Failed to load firmware\n");
<<<<<<< HEAD
		s5p_mfc_reset(dev);
		s5p_mfc_clock_off();
		return -EIO;
	}
	dev->int_cond = 0;
	if (dev->int_err != 0 || dev->int_type !=
					S5P_FIMV_R2H_CMD_SYS_INIT_RET) {
		/* Failure. */
		mfc_err("Failed to init firmware - error: %d int: %d\n",
						dev->int_err, dev->int_type);
		s5p_mfc_reset(dev);
		s5p_mfc_clock_off();
		return -EIO;
	}
	ver = mfc_read(dev, S5P_FIMV_FW_VERSION);
	mfc_debug(2, "MFC F/W version : %02xyy, %02xmm, %02xdd\n",
		(ver >> 16) & 0xFF, (ver >> 8) & 0xFF, ver & 0xFF);
	s5p_mfc_clock_off();
	mfc_debug_leave();
	return 0;
}


=======
		ret = -EIO;
		/* Disable the clock that enabled in s5p_mfc_sys_init_cmd() */
		s5p_mfc_clock_off();
		goto err_init_hw;
	}

	dev->int_cond = 0;
	if (dev->int_err != 0 || dev->int_type !=
						S5P_FIMV_R2H_CMD_SYS_INIT_RET) {
		/* Failure. */
		mfc_err("Failed to init firmware - error: %d"
				" int: %d.\n",dev->int_err, dev->int_type);
		ret = -EIO;
		goto err_init_hw;
	}

	dvx_info = MFC_GET_REG(SYS_FW_DVX_INFO);
	if (dvx_info != 'D' && dvx_info != 'E')
		dvx_info = 'N';

	mfc_info("MFC v%x.%x, F/W : (%c) %02xyy, %02xmm, %02xdd\n",
		 MFC_VER_MAJOR(dev->fw.ver),
		 MFC_VER_MINOR(dev->fw.ver),
		 dvx_info,
		 MFC_GET_REG(SYS_FW_VER_YEAR),
		 MFC_GET_REG(SYS_FW_VER_MONTH),
		 MFC_GET_REG(SYS_FW_VER_DATE));

	dev->fw.date = MFC_GET_REG(SYS_FW_VER_ALL);
	/* Check MFC version and F/W version */
	if (dev->fw.date >= 0x120328) {
		mfc_info = MFC_GET_REG(SYS_MFC_VER);
		if (mfc_info != dev->fw.ver) {
			mfc_err("Invalid F/W version(0x%x) for MFC H/W(0x%x)\n",
					mfc_info, dev->fw.ver);
			ret = -EIO;
			goto err_init_hw;
		}
	}

err_init_hw:
	s5p_mfc_clock_off();
	mfc_debug_leave();

	return ret;
}


/* Deinitialize hardware */
void s5p_mfc_deinit_hw(struct s5p_mfc_dev *dev)
{
	s5p_mfc_clock_on();

	s5p_mfc_reset(dev);
	if (IS_MFCV6(dev))
		s5p_mfc_release_dev_context_buffer(dev);

	s5p_mfc_clock_off();
}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
int s5p_mfc_sleep(struct s5p_mfc_dev *dev)
{
	int ret;

	mfc_debug_enter();
<<<<<<< HEAD
	s5p_mfc_clock_on();
	s5p_mfc_clean_dev_int_flags(dev);
	ret = s5p_mfc_sleep_cmd(dev);
	if (ret) {
		mfc_err("Failed to send command to MFC - timeout\n");
		return ret;
	}
	if (s5p_mfc_wait_for_done_dev(dev, S5P_FIMV_R2H_CMD_SLEEP_RET)) {
		mfc_err("Failed to sleep\n");
		return -EIO;
	}
	s5p_mfc_clock_off();
=======

	s5p_mfc_clock_on();

	s5p_mfc_clean_dev_int_flags(dev);
	ret = s5p_mfc_sleep_cmd(dev);
	if (ret) {
		mfc_err("Failed to send command to MFC - timeout.\n");
		goto err_mfc_sleep;
	}
	if (s5p_mfc_wait_for_done_dev(dev, S5P_FIMV_R2H_CMD_SLEEP_RET)) {
		mfc_err("Failed to sleep\n");
		ret = -EIO;
		goto err_mfc_sleep;
	}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	dev->int_cond = 0;
	if (dev->int_err != 0 || dev->int_type !=
						S5P_FIMV_R2H_CMD_SLEEP_RET) {
		/* Failure. */
<<<<<<< HEAD
		mfc_err("Failed to sleep - error: %d int: %d\n", dev->int_err,
								dev->int_type);
		return -EIO;
	}
	mfc_debug_leave();
=======
		mfc_err("Failed to sleep - error: %d"
				" int: %d.\n",dev->int_err, dev->int_type);
		ret = -EIO;
		goto err_mfc_sleep;
	}

err_mfc_sleep:
	s5p_mfc_clock_off();
	mfc_debug_leave();

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return ret;
}

int s5p_mfc_wakeup(struct s5p_mfc_dev *dev)
{
	int ret;

	mfc_debug_enter();
<<<<<<< HEAD
	/* 0. MFC reset */
	mfc_debug(2, "MFC reset..\n");
	s5p_mfc_clock_on();
	ret = s5p_mfc_reset(dev);
	if (ret) {
		mfc_err("Failed to reset MFC - timeout\n");
		return ret;
	}
	mfc_debug(2, "Done MFC reset..\n");
	/* 1. Set DRAM base Addr */
	s5p_mfc_init_memctrl(dev);
	/* 2. Initialize registers of channel I/F */
	s5p_mfc_clear_cmds(dev);
=======

	/* 0. MFC reset */
	mfc_debug(2, "MFC reset...\n");

	s5p_mfc_clock_on();

	ret = s5p_mfc_reset(dev);
	if (ret) {
		mfc_err("Failed to reset MFC - timeout.\n");
		goto err_mfc_wakeup;
	}
	mfc_debug(2, "Done MFC reset...\n");

	/* 1. Set DRAM base Addr */
	s5p_mfc_init_memctrl(dev);

	/* 2. Initialize registers of channel I/F */
	s5p_mfc_clear_cmds(dev);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	s5p_mfc_clean_dev_int_flags(dev);
	/* 3. Initialize firmware */
	ret = s5p_mfc_wakeup_cmd(dev);
	if (ret) {
<<<<<<< HEAD
		mfc_err("Failed to send command to MFC - timeout\n");
		return ret;
	}
	/* 4. Release reset signal to the RISC */
	mfc_write(dev, 0x3ff, S5P_FIMV_SW_RESET);
	mfc_debug(2, "Ok, now will write a command to wakeup the system\n");
	if (s5p_mfc_wait_for_done_dev(dev, S5P_FIMV_R2H_CMD_WAKEUP_RET)) {
		mfc_err("Failed to load firmware\n");
		return -EIO;
	}
	s5p_mfc_clock_off();
=======
		mfc_err("Failed to send command to MFC - timeout.\n");
		goto err_mfc_wakeup;
	}

	/* 4. Release reset signal to the RISC */
	if (IS_MFCV6(dev))
		s5p_mfc_write_reg(0x1, S5P_FIMV_RISC_ON);
	else
		s5p_mfc_write_reg(0x3ff, S5P_FIMV_SW_RESET);

	mfc_debug(2, "Ok, now will write a command to wakeup the system\n");
	if (s5p_mfc_wait_for_done_dev(dev, S5P_FIMV_R2H_CMD_WAKEUP_RET)) {
		mfc_err("Failed to load firmware\n");
		ret = -EIO;
		goto err_mfc_wakeup;
	}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	dev->int_cond = 0;
	if (dev->int_err != 0 || dev->int_type !=
						S5P_FIMV_R2H_CMD_WAKEUP_RET) {
		/* Failure. */
<<<<<<< HEAD
		mfc_err("Failed to wakeup - error: %d int: %d\n", dev->int_err,
								dev->int_type);
		return -EIO;
	}
	mfc_debug_leave();
	return 0;
}

=======
		mfc_err("Failed to wakeup - error: %d"
				" int: %d.\n",dev->int_err, dev->int_type);
		ret = -EIO;
		goto err_mfc_wakeup;
	}

err_mfc_wakeup:
	s5p_mfc_clock_off();
	mfc_debug_leave();

	return 0;
}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
