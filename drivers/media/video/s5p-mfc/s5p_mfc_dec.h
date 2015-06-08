/*
 * linux/drivers/media/video/s5p-mfc/s5p_mfc_dec.h
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
=======
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *		http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

<<<<<<< HEAD
<<<<<<< HEAD
#ifndef S5P_MFC_DEC_H_
#define S5P_MFC_DEC_H_

struct s5p_mfc_codec_ops *get_dec_codec_ops(void);
struct vb2_ops *get_dec_queue_ops(void);
const struct v4l2_ioctl_ops *get_dec_v4l2_ioctl_ops(void);
struct s5p_mfc_fmt *get_dec_def_fmt(bool src);
int s5p_mfc_dec_ctrls_setup(struct s5p_mfc_ctx *ctx);
void s5p_mfc_dec_ctrls_delete(struct s5p_mfc_ctx *ctx);

#endif /* S5P_MFC_DEC_H_ */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#ifndef __S5P_MFC_DEC_H_
#define __S5P_MFC_DEC_H_ __FILE__

#define MAX_FRAME_SIZE		(2*1024*1024)

const struct v4l2_ioctl_ops *get_dec_v4l2_ioctl_ops(void);
int s5p_mfc_init_dec_ctx(struct s5p_mfc_ctx *ctx);

#endif /* __S5P_MFC_DEC_H_ */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
