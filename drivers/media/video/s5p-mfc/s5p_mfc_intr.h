/*
 * drivers/media/video/samsung/mfc5/s5p_mfc_intr.h
 *
 * Header file for Samsung MFC (Multi Function Codec - FIMV) driver
 * It contains waiting functions declarations.
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * Kamil Debski, Copyright (C) 2011 Samsung Electronics
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

<<<<<<< HEAD
<<<<<<< HEAD
#ifndef S5P_MFC_INTR_H_
#define S5P_MFC_INTR_H_
=======
#ifndef _S5P_MFC_INTR_H_
#define _S5P_MFC_INTR_H_
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#ifndef _S5P_MFC_INTR_H_
#define _S5P_MFC_INTR_H_
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include "s5p_mfc_common.h"

int s5p_mfc_wait_for_done_ctx(struct s5p_mfc_ctx *ctx,
<<<<<<< HEAD
<<<<<<< HEAD
			      int command, int interrupt);
=======
						int command, int interrupt);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
						int command, int interrupt);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int s5p_mfc_wait_for_done_dev(struct s5p_mfc_dev *dev, int command);
void s5p_mfc_clean_ctx_int_flags(struct s5p_mfc_ctx *ctx);
void s5p_mfc_clean_dev_int_flags(struct s5p_mfc_dev *dev);

<<<<<<< HEAD
<<<<<<< HEAD
#endif /* S5P_MFC_INTR_H_ */
=======
#endif /* _S5P_MFC_INTR_H_ */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#endif /* _S5P_MFC_INTR_H_ */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
