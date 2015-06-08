/*
 * linux/drivers/media/video/s5p-mfc/s5p_mfc_cmd.h
 *
<<<<<<< HEAD
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
=======
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

<<<<<<< HEAD
#ifndef S5P_MFC_CMD_H_
#define S5P_MFC_CMD_H_

#include "s5p_mfc_common.h"

#define MAX_H2R_ARG	4
=======
#ifndef __S5P_MFC_CMD_H
#define __S5P_MFC_CMD_H __FILE__

#define MAX_H2R_ARG		4
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

struct s5p_mfc_cmd_args {
	unsigned int	arg[MAX_H2R_ARG];
};

<<<<<<< HEAD
=======
int s5p_mfc_cmd_host2risc(int cmd, struct s5p_mfc_cmd_args *args);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
int s5p_mfc_sys_init_cmd(struct s5p_mfc_dev *dev);
int s5p_mfc_sleep_cmd(struct s5p_mfc_dev *dev);
int s5p_mfc_wakeup_cmd(struct s5p_mfc_dev *dev);
int s5p_mfc_open_inst_cmd(struct s5p_mfc_ctx *ctx);
int s5p_mfc_close_inst_cmd(struct s5p_mfc_ctx *ctx);

<<<<<<< HEAD
#endif /* S5P_MFC_CMD_H_ */
=======
#endif /* __S5P_MFC_CMD_H */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
