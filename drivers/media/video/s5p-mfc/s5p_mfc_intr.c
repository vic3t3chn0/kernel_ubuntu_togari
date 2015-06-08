/*
 * drivers/media/video/samsung/mfc5/s5p_mfc_intr.c
 *
 * C file for Samsung MFC (Multi Function Codec - FIMV) driver
 * This file contains functions used to wait for command completion.
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * Kamil Debski, Copyright (C) 2011 Samsung Electronics Co., Ltd.
=======
 * Kamil Debski, Copyright (c) 2010 Samsung Electronics
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Kamil Debski, Copyright (c) 2010 Samsung Electronics
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/delay.h>
#include <linux/errno.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/io.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include "regs-mfc.h"
#include "s5p_mfc_common.h"
#include "s5p_mfc_debug.h"
#include "s5p_mfc_intr.h"
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/io.h>

#include "s5p_mfc_common.h"

#include "s5p_mfc_intr.h"
#include "s5p_mfc_debug.h"
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

int s5p_mfc_wait_for_done_dev(struct s5p_mfc_dev *dev, int command)
{
	int ret;

	ret = wait_event_interruptible_timeout(dev->queue,
		(dev->int_cond && (dev->int_type == command
		|| dev->int_type == S5P_FIMV_R2H_CMD_ERR_RET)),
		msecs_to_jiffies(MFC_INT_TIMEOUT));
	if (ret == 0) {
<<<<<<< HEAD
<<<<<<< HEAD
		mfc_err("Interrupt (dev->int_type:%d, command:%d) timed out\n",
							dev->int_type, command);
		return 1;
	} else if (ret == -ERESTARTSYS) {
		mfc_err("Interrupted by a signal\n");
		return 1;
	}
	mfc_debug(1, "Finished waiting (dev->int_type:%d, command: %d)\n",
							dev->int_type, command);
	if (dev->int_type == S5P_FIMV_R2H_CMD_ERR_RET)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		mfc_err("Interrupt (dev->int_type:%d, command:%d) timed out.\n",
							dev->int_type, command);
		return 1;
	} else if (ret == -ERESTARTSYS) {
		mfc_err("Interrupted by a signal.\n");
		return 1;
	}
	mfc_debug(1, "Finished waiting (dev->int_type:%d, command: %d).\n",
							dev->int_type, command);
	/* RMVME: */
	if (dev->int_type == S5P_FIMV_R2H_CMD_RSV_RET)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return 1;
	return 0;
}

void s5p_mfc_clean_dev_int_flags(struct s5p_mfc_dev *dev)
{
	dev->int_cond = 0;
	dev->int_type = 0;
	dev->int_err = 0;
}

int s5p_mfc_wait_for_done_ctx(struct s5p_mfc_ctx *ctx,
				    int command, int interrupt)
{
	int ret;

	if (interrupt) {
		ret = wait_event_interruptible_timeout(ctx->queue,
				(ctx->int_cond && (ctx->int_type == command
			|| ctx->int_type == S5P_FIMV_R2H_CMD_ERR_RET)),
					msecs_to_jiffies(MFC_INT_TIMEOUT));
	} else {
		ret = wait_event_timeout(ctx->queue,
				(ctx->int_cond && (ctx->int_type == command
			|| ctx->int_type == S5P_FIMV_R2H_CMD_ERR_RET)),
					msecs_to_jiffies(MFC_INT_TIMEOUT));
	}
	if (ret == 0) {
<<<<<<< HEAD
<<<<<<< HEAD
		mfc_err("Interrupt (ctx->int_type:%d, command:%d) timed out\n",
							ctx->int_type, command);
		return 1;
	} else if (ret == -ERESTARTSYS) {
		mfc_err("Interrupted by a signal\n");
		return 1;
	}
	mfc_debug(1, "Finished waiting (ctx->int_type:%d, command: %d)\n",
							ctx->int_type, command);
	if (ctx->int_type == S5P_FIMV_R2H_CMD_ERR_RET)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		mfc_err("Interrupt (ctx->int_type:%d, command:%d) timed out.\n",
							ctx->int_type, command);
		return 1;
	} else if (ret == -ERESTARTSYS) {
		mfc_err("Interrupted by a signal.\n");
		return 1;
	}
	mfc_debug(1, "Finished waiting (ctx->int_type:%d, command: %d).\n",
							ctx->int_type, command);
	/* RMVME: */
	if (ctx->int_type == S5P_FIMV_R2H_CMD_RSV_RET)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return 1;
	return 0;
}

void s5p_mfc_clean_ctx_int_flags(struct s5p_mfc_ctx *ctx)
{
	ctx->int_cond = 0;
	ctx->int_type = 0;
	ctx->int_err = 0;
}

