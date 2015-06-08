/*
 * linux/drivers/media/video/s5p-mfc/s5p_mfc_ctrl.h
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

<<<<<<< HEAD
<<<<<<< HEAD
#ifndef S5P_MFC_CTRL_H
#define S5P_MFC_CTRL_H

#include "s5p_mfc_common.h"

int s5p_mfc_release_firmware(struct s5p_mfc_dev *dev);
int s5p_mfc_alloc_and_load_firmware(struct s5p_mfc_dev *dev);
int s5p_mfc_reload_firmware(struct s5p_mfc_dev *dev);

int s5p_mfc_init_hw(struct s5p_mfc_dev *dev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifndef __S5P_MFC_CTRL_H
#define __S5P_MFC_CTRL_H __FILE__

int s5p_mfc_release_firmware(struct s5p_mfc_dev *dev);
int s5p_mfc_alloc_firmware(struct s5p_mfc_dev *dev);
int s5p_mfc_load_firmware(struct s5p_mfc_dev *dev);
/*
int mfc_load_firmware(const unsigned char *data, size_t size);
*/

int s5p_mfc_init_hw(struct s5p_mfc_dev *dev);
void s5p_mfc_deinit_hw(struct s5p_mfc_dev *dev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

int s5p_mfc_sleep(struct s5p_mfc_dev *dev);
int s5p_mfc_wakeup(struct s5p_mfc_dev *dev);

<<<<<<< HEAD
<<<<<<< HEAD
int s5p_mfc_reset(struct s5p_mfc_dev *dev);

#endif /* S5P_MFC_CTRL_H */
=======
#endif /* __S5P_MFC_CTRL_H */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#endif /* __S5P_MFC_CTRL_H */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
