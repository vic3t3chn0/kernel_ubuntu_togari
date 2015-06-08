/*
 * linux/drivers/media/video/s5p-mfc/s5p_mfc_dec.c
 *
<<<<<<< HEAD
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
=======
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 *		http://www.samsung.com/
 * Kamil Debski, <k.debski@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

<<<<<<< HEAD
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/version.h>
#include <linux/videodev2.h>
#include <linux/workqueue.h>
#include <media/v4l2-ctrls.h>
#include <media/videobuf2-core.h>
#include "regs-mfc.h"
#include "s5p_mfc_common.h"
#include "s5p_mfc_debug.h"
#include "s5p_mfc_dec.h"
#include "s5p_mfc_intr.h"
#include "s5p_mfc_opr.h"
#include "s5p_mfc_pm.h"
#include "s5p_mfc_shm.h"

static struct s5p_mfc_fmt formats[] = {
	{
		.name		= "4:2:0 2 Planes 64x32 Tiles",
		.fourcc		= V4L2_PIX_FMT_NV12MT,
		.codec_mode	= S5P_FIMV_CODEC_NONE,
		.type		= MFC_FMT_RAW,
		.num_planes	= 2,
	 },
	{
		.name = "4:2:0 2 Planes",
		.fourcc = V4L2_PIX_FMT_NV12M,
		.codec_mode = S5P_FIMV_CODEC_NONE,
=======
#include <linux/io.h>
#include <linux/sched.h>
#include <linux/clk.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/version.h>
#include <linux/workqueue.h>
#include <linux/videodev2.h>
#include <linux/videodev2_exynos_media.h>
#include <media/videobuf2-core.h>

#ifdef CONFIG_BUSFREQ_OPP
#ifdef CONFIG_CPU_EXYNOS5250
#include <mach/dev.h>
#endif
#endif

#include "s5p_mfc_common.h"

#include "s5p_mfc_intr.h"
#include "s5p_mfc_mem.h"
#include "s5p_mfc_debug.h"
#include "s5p_mfc_reg.h"
#include "s5p_mfc_dec.h"
#include "s5p_mfc_pm.h"

#undef STREAM_SAVE

#ifdef STREAM_SAVE
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/file.h>

static void save_stream(unsigned long addr, unsigned int size)
{
	struct file *file;
	loff_t pos = 0;
	int fd;
	mm_segment_t old_fs;
	char filename[128];
	char save_path[128] = "/data/app";

	static int frame_count = 0;
	char infobuf[128];
	int infolen;
	char infoname[128];

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	sprintf(filename, "%s/stream.dump", save_path);
	fd = sys_open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd >= 0) {
		file = fget(fd);

		if (file) {
			vfs_write(file, (u8 *)addr, size, &pos);
			fput(file);
		}

		sys_close(fd);
	} else {
		mfc_err("failed to open file to dump: %d\n", fd);
	}

	sprintf(infoname, "%s/stream.info", save_path);
	infolen = sprintf(infobuf, "%d, %d\n", frame_count, size);

	fd = sys_open(infoname, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd >= 0) {
		file = fget(fd);

		if (file) {
			vfs_write(file, (u8 *)infobuf, infolen, &pos);
			fput(file);
		}

		sys_close(fd);
	} else {
		mfc_err("failed to open file to dump: %d\n", fd);
	}

	frame_count++;

	set_fs(old_fs);
}

static void vb2_save_buf(struct vb2_buffer *vb, unsigned int plane_no)
{
	unsigned char *addr;

	addr = (unsigned char *)vb2_plane_vaddr(vb, plane_no);
	s5p_mfc_cache_inv(vb, plane_no);

	save_stream((unsigned long)addr, vb->v4l2_planes[plane_no].bytesused);
}
#endif

#define DEF_SRC_FMT	2
#define DEF_DST_FMT	0

static struct s5p_mfc_fmt formats[] = {
	{
		.name = "4:2:0 2 Planes 16x16 Tiles",
		.fourcc = V4L2_PIX_FMT_NV12MT_16X16,
		.codec_mode = MFC_FORMATS_NO_CODEC,
		.type = MFC_FMT_RAW,
		.num_planes = 2,
	},
	{
		.name = "4:2:0 2 Planes 64x32 Tiles",
		.fourcc = V4L2_PIX_FMT_NV12MT,
		.codec_mode = MFC_FORMATS_NO_CODEC,
		.type = MFC_FMT_RAW,
		.num_planes = 2,
	},
	{
		.name = "4:2:0 2 Planes Y/CbCr",
		.fourcc = V4L2_PIX_FMT_NV12M,
		.codec_mode = MFC_FORMATS_NO_CODEC,
		.type = MFC_FMT_RAW,
		.num_planes = 2,
	},
	{
		.name = "4:2:0 2 Planes Y/CrCb",
		.fourcc = V4L2_PIX_FMT_NV21M,
		.codec_mode = MFC_FORMATS_NO_CODEC,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		.type = MFC_FMT_RAW,
		.num_planes = 2,
	},
	{
		.name = "H264 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_H264,
		.codec_mode = S5P_FIMV_CODEC_H264_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
<<<<<<< HEAD
=======
	/* MFC 6.x only */
	{
		.name = "H264/MVC Encoded Stream",
		.fourcc = V4L2_PIX_FMT_H264_MVC,
		.codec_mode = S5P_FIMV_CODEC_H264_MVC_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	{
		.name = "H263 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_H263,
		.codec_mode = S5P_FIMV_CODEC_H263_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
		.name = "MPEG1 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_MPEG1,
		.codec_mode = S5P_FIMV_CODEC_MPEG2_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
		.name = "MPEG2 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_MPEG2,
		.codec_mode = S5P_FIMV_CODEC_MPEG2_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
		.name = "MPEG4 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_MPEG4,
		.codec_mode = S5P_FIMV_CODEC_MPEG4_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
<<<<<<< HEAD
=======
		.name = "FIMV Encoded Stream",
		.fourcc = V4L2_PIX_FMT_FIMV,
		.codec_mode = S5P_FIMV_CODEC_MPEG4_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
		.name = "FIMV1 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_FIMV1,
		.codec_mode = S5P_FIMV_CODEC_FIMV1_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
		.name = "FIMV2 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_FIMV2,
		.codec_mode = S5P_FIMV_CODEC_FIMV2_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
		.name = "FIMV3 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_FIMV3,
		.codec_mode = S5P_FIMV_CODEC_FIMV3_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
		.name = "FIMV4 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_FIMV4,
		.codec_mode = S5P_FIMV_CODEC_FIMV4_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		.name = "XviD Encoded Stream",
		.fourcc = V4L2_PIX_FMT_XVID,
		.codec_mode = S5P_FIMV_CODEC_MPEG4_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
		.name = "VC1 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_VC1_ANNEX_G,
		.codec_mode = S5P_FIMV_CODEC_VC1_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
	{
		.name = "VC1 RCV Encoded Stream",
		.fourcc = V4L2_PIX_FMT_VC1_ANNEX_L,
		.codec_mode = S5P_FIMV_CODEC_VC1RCV_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
<<<<<<< HEAD
=======
	{
		.name = "VC8 Encoded Stream",
		.fourcc = V4L2_PIX_FMT_VP8,
		.codec_mode = S5P_FIMV_CODEC_VP8_DEC,
		.type = MFC_FMT_DEC,
		.num_planes = 1,
	},
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
};

#define NUM_FORMATS ARRAY_SIZE(formats)

/* Find selected format description */
static struct s5p_mfc_fmt *find_format(struct v4l2_format *f, unsigned int t)
{
	unsigned int i;

	for (i = 0; i < NUM_FORMATS; i++) {
		if (formats[i].fourcc == f->fmt.pix_mp.pixelformat &&
		    formats[i].type == t)
<<<<<<< HEAD
			return &formats[i];
	}
	return NULL;
}

static struct mfc_control controls[] = {
	{
		.id = V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "H264 Display Delay",
		.minimum = 0,
		.maximum = 16383,
=======
			return (struct s5p_mfc_fmt *)&formats[i];
	}

	return NULL;
}

static struct v4l2_queryctrl controls[] = {
	{
		.id = V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "H.264 Display Delay",
		.minimum = -1,
		.maximum = 32,
		.step = 1,
		.default_value = -1,
	},
	{
		.id = V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Mpeg4 Loop Filter Enable",
		.minimum = 0,
		.maximum = 1,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		.step = 1,
		.default_value = 0,
	},
	{
<<<<<<< HEAD
		.id = V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY_ENABLE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "H264 Display Delay Enable",
=======
		.id = V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Slice Interface Enable",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.default_value = 0,
	},
	{
<<<<<<< HEAD
		.id = V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Mpeg4 Loop Filter Enable",
=======
		.id = V4L2_CID_MPEG_MFC51_VIDEO_PACKED_PB,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Packed PB Enable",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.default_value = 0,
	},
	{
<<<<<<< HEAD
		.id = V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Slice Interface Enable",
=======
		.id = V4L2_CID_MPEG_MFC51_VIDEO_FRAME_TAG,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Frame Tag",
		.minimum = 0,
		.maximum = INT_MAX,
		.step = 1,
		.default_value = 0,
	},
	{
		.id = V4L2_CID_CACHEABLE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Cacheable flag",
		.minimum = 0,
		.maximum = 3,
		.step = 1,
		.default_value = 0,
	},
	{
		.id = V4L2_CID_MPEG_MFC51_VIDEO_CRC_ENABLE,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "CRC enable",
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.default_value = 0,
	},
	{
<<<<<<< HEAD
		.id = V4L2_CID_MIN_BUFFERS_FOR_CAPTURE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Minimum number of cap bufs",
		.minimum = 1,
		.maximum = 32,
		.step = 1,
		.default_value = 1,
		.is_volatile = 1,
=======
		.id = V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_LUMA,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "CRC data",
		.minimum = 0,
		.maximum = INT_MAX,
		.step = 1,
		.default_value = 0,
	},
	{
		.id = V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_CHROMA,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "CRC data",
		.minimum = 0,
		.maximum = INT_MAX,
		.step = 1,
		.default_value = 0,
	},
	{
		.id = V4L2_CID_MPEG_MFC51_VIDEO_DISPLAY_STATUS,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Display status",
		.minimum = 0,
		.maximum = 3,
		.step = 1,
		.default_value = 0,
	},
	{
		.id = V4L2_CID_MPEG_MFC51_VIDEO_FRAME_TYPE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.name = "Frame type",
		.minimum = 0,
		.maximum = INT_MAX,
		.step = 1,
		.default_value = 0,
	},
#if defined(CONFIG_S5P_MFC_VB2_ION)
	{
		.id		= V4L2_CID_SET_SHAREABLE,
		.type		= V4L2_CTRL_TYPE_BOOLEAN,
		.name		= "File descriptor for ION",
		.minimum	= 0,
		.maximum	= 1,
		.default_value	= 1,
	},
#endif
	{
		.id = V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING,
		.type = V4L2_CTRL_TYPE_BOOLEAN,
		.name = "Frame pack sei parse flag",
		.minimum = 0,
		.maximum = 1,
		.step = 1,
		.default_value = 0,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	},
};

#define NUM_CTRLS ARRAY_SIZE(controls)

<<<<<<< HEAD
/* Check whether a context should be run on hardware */
static int s5p_mfc_ctx_ready(struct s5p_mfc_ctx *ctx)
{
=======
static struct v4l2_queryctrl *get_ctrl(int id)
{
	int i;

	for (i = 0; i < NUM_CTRLS; ++i)
		if (id == controls[i].id)
			return &controls[i];
	return NULL;
}

/* Check whether a ctrl value if correct */
static int check_ctrl_val(struct s5p_mfc_ctx *ctx, struct v4l2_control *ctrl)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct v4l2_queryctrl *c;

	c = get_ctrl(ctrl->id);
	if (!c)
		return -EINVAL;

	if (ctrl->value < c->minimum || ctrl->value > c->maximum
		|| (c->step != 0 && ctrl->value % c->step != 0)) {
		v4l2_err(&dev->v4l2_dev, "invalid control value\n");
		return -ERANGE;
	}

	return 0;
}

static struct s5p_mfc_ctrl_cfg mfc_ctrl_list[] = {
	{
		.type = MFC_CTRL_TYPE_SET,
		.id = V4L2_CID_MPEG_MFC51_VIDEO_FRAME_TAG,
		.is_volatile = 1,
		.mode = MFC_CTRL_MODE_CUSTOM,
		.addr = S5P_FIMV_SHARED_SET_FRAME_TAG,
		.mask = 0xFFFFFFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_DST,
		.id = V4L2_CID_MPEG_MFC51_VIDEO_FRAME_TAG,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_CUSTOM,
		.addr = S5P_FIMV_SHARED_GET_FRAME_TAG_TOP,
		.mask = 0xFFFFFFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_DST,
		.id = V4L2_CID_MPEG_MFC51_VIDEO_DISPLAY_STATUS,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_SFR,
		.addr = S5P_FIMV_SI_DISPLAY_STATUS,
		.mask = 0x7,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	/* CRC related definitions are based on non-H.264 type */
	{
		.type = MFC_CTRL_TYPE_GET_SRC,
		.id = V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_LUMA,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_SFR,
		.addr = S5P_FIMV_CRC_LUMA0,
		.mask = 0xFFFFFFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_SRC,
		.id = V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_CHROMA,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_SFR,
		.addr = S5P_FIMV_CRC_CHROMA0,
		.mask = 0xFFFFFFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_SRC,
		.id = V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_LUMA_BOT,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_SFR,
		.addr = S5P_FIMV_CRC_LUMA1,
		.mask = 0xFFFFFFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_SRC,
		.id = V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_CHROMA_BOT,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_SFR,
		.addr = S5P_FIMV_CRC_CHROMA1,
		.mask = 0xFFFFFFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_SRC,
		.id = V4L2_CID_MPEG_MFC51_VIDEO_CRC_GENERATED,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_SFR,
		.addr = S5P_FIMV_SI_DECODED_STATUS,
		.mask = S5P_FIMV_DEC_CRC_GEN_MASK,
		.shft = S5P_FIMV_DEC_CRC_GEN_SHIFT,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_DST,
		.id = V4L2_CID_MPEG_VIDEO_H264_SEI_FP_AVAIL,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_CUSTOM,
		.addr = S5P_FIMV_FRAME_PACK_SEI_AVAIL,
		.mask = 0x1,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_DST,
		.id = V4L2_CID_MPEG_VIDEO_H264_SEI_FP_ARRGMENT_ID,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_CUSTOM,
		.addr = S5P_FIMV_FRAME_PACK_ARRGMENT_ID,
		.mask = 0xFFFFFFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_DST,
		.id = V4L2_CID_MPEG_VIDEO_H264_SEI_FP_INFO,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_CUSTOM,
		.addr = S5P_FIMV_FRAME_PACK_SEI_INFO,
		.mask = 0x3FFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_DST,
		.id = V4L2_CID_MPEG_VIDEO_H264_SEI_FP_GRID_POS,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_CUSTOM,
		.addr = S5P_FIMV_FRAME_PACK_GRID_POS,
		.mask = 0xFFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
	{
		.type = MFC_CTRL_TYPE_GET_DST,
		.id = V4L2_CID_MPEG_VIDEO_H264_MVC_VIEW_ID,
		.is_volatile = 0,
		.mode = MFC_CTRL_MODE_CUSTOM,
		.addr = S5P_FIMV_D_MVC_VIEW_ID,
		.mask = 0xFFFF,
		.shft = 0,
		.flag_mode = MFC_CTRL_MODE_NONE,
		.flag_addr = 0,
		.flag_shft = 0,
	},
};

#define NUM_CTRL_CFGS ARRAY_SIZE(mfc_ctrl_list)

/* Check whether a context should be run on hardware */
static int s5p_mfc_ctx_ready(struct s5p_mfc_ctx *ctx)
{
	mfc_debug(2, "src=%d, dst=%d, state=%d capstat=%d\n",
		  ctx->src_queue_cnt, ctx->dst_queue_cnt,
		  ctx->state, ctx->capture_state);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	/* Context is to parse header */
	if (ctx->src_queue_cnt >= 1 && ctx->state == MFCINST_GOT_INST)
		return 1;
	/* Context is to decode a frame */
	if (ctx->src_queue_cnt >= 1 &&
	    ctx->state == MFCINST_RUNNING &&
	    ctx->dst_queue_cnt >= ctx->dpb_count)
		return 1;
	/* Context is to return last frame */
	if (ctx->state == MFCINST_FINISHING &&
	    ctx->dst_queue_cnt >= ctx->dpb_count)
		return 1;
	/* Context is to set buffers */
	if (ctx->src_queue_cnt >= 1 &&
	    ctx->state == MFCINST_HEAD_PARSED &&
	    ctx->capture_state == QUEUE_BUFS_MMAPED)
		return 1;
	/* Resolution change */
	if ((ctx->state == MFCINST_RES_CHANGE_INIT ||
		ctx->state == MFCINST_RES_CHANGE_FLUSH) &&
		ctx->dst_queue_cnt >= ctx->dpb_count)
		return 1;
	if (ctx->state == MFCINST_RES_CHANGE_END &&
		ctx->src_queue_cnt >= 1)
		return 1;
<<<<<<< HEAD
	mfc_debug(2, "ctx is not ready\n");
=======

	mfc_debug(2, "s5p_mfc_ctx_ready: ctx is not ready.\n");

	return 0;
}

static int dec_init_ctx_ctrls(struct s5p_mfc_ctx *ctx)
{
	int i;
	struct s5p_mfc_ctx_ctrl *ctx_ctrl;

	INIT_LIST_HEAD(&ctx->ctrls);

	for (i = 0; i < NUM_CTRL_CFGS; i++) {
		ctx_ctrl = kzalloc(sizeof(struct s5p_mfc_ctx_ctrl), GFP_KERNEL);
		if (ctx_ctrl == NULL) {
			mfc_err("failed to allocate ctx_ctrl type: %d, id: 0x%08x\n",
				mfc_ctrl_list[i].type, mfc_ctrl_list[i].id);

			return -ENOMEM;
		}

		ctx_ctrl->type = mfc_ctrl_list[i].type;
		ctx_ctrl->id = mfc_ctrl_list[i].id;
		ctx_ctrl->addr = mfc_ctrl_list[i].addr;
		ctx_ctrl->has_new = 0;
		ctx_ctrl->val = 0;

		list_add_tail(&ctx_ctrl->list, &ctx->ctrls);

		mfc_debug(5, "add ctx ctrl id: 0x%08x, type : %d\n",
				ctx_ctrl->id, ctx_ctrl->type);
	}

	return 0;
}

static int dec_cleanup_ctx_ctrls(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_ctx_ctrl *ctx_ctrl;

	while (!list_empty(&ctx->ctrls)) {
		ctx_ctrl = list_entry((&ctx->ctrls)->next,
				      struct s5p_mfc_ctx_ctrl, list);

		mfc_debug(5, "del ctx ctrl id: 0x%08x\n", ctx_ctrl->id);

		list_del(&ctx_ctrl->list);
		kfree(ctx_ctrl);
	}

	INIT_LIST_HEAD(&ctx->ctrls);

	return 0;
}

static int dec_init_buf_ctrls(struct s5p_mfc_ctx *ctx,
	enum s5p_mfc_ctrl_type type, unsigned int index)
{
	int i;
	struct s5p_mfc_ctx_ctrl *ctx_ctrl;
	struct s5p_mfc_buf_ctrl *buf_ctrl;
	struct list_head *head;

	if (type & MFC_CTRL_TYPE_SRC) {
		head = &ctx->src_ctrls[index];
		ctx->src_ctrls_flag[index] = 1;
	} else if (type & MFC_CTRL_TYPE_DST) {
		head = &ctx->dst_ctrls[index];
		ctx->dst_ctrls_flag[index] = 1;
	} else {
		mfc_err("Control type missmatch. type : %d\n", type);
		return -EINVAL;
	}

	INIT_LIST_HEAD(head);

	list_for_each_entry(ctx_ctrl, &ctx->ctrls, list) {
		if (!(type & ctx_ctrl->type))
			continue;

		for (i = 0; i < NUM_CTRL_CFGS; i++)
			if (ctx_ctrl->id == mfc_ctrl_list[i].id)
				break;

		if (i == NUM_CTRL_CFGS) {
			mfc_err("Failed to get control. id : 0x%x\n", ctx_ctrl->id);
			return -EINVAL;
		}

		buf_ctrl = kzalloc(sizeof(struct s5p_mfc_buf_ctrl), GFP_KERNEL);
		if (buf_ctrl == NULL) {
			mfc_err("failed to allocate buf_ctrl type: %d, id: 0x%08x\n",
				mfc_ctrl_list[i].type, mfc_ctrl_list[i].id);

			return -ENOMEM;
		}

		buf_ctrl->id = ctx_ctrl->id;
		buf_ctrl->type = ctx_ctrl->type;
		buf_ctrl->has_new = 0;
		buf_ctrl->val = 0;
		buf_ctrl->old_val = 0;
		buf_ctrl->is_volatile = mfc_ctrl_list[i].is_volatile;
		buf_ctrl->mode = mfc_ctrl_list[i].mode;
		buf_ctrl->addr = ctx_ctrl->addr;
		buf_ctrl->mask = mfc_ctrl_list[i].mask;
		buf_ctrl->shft = mfc_ctrl_list[i].shft;
		buf_ctrl->flag_mode = mfc_ctrl_list[i].flag_mode;
		buf_ctrl->flag_addr = mfc_ctrl_list[i].flag_addr;
		buf_ctrl->flag_shft = mfc_ctrl_list[i].flag_shft;

		list_add_tail(&buf_ctrl->list, head);

		mfc_debug(5, "add buf ctrl id: 0x%08x, type : %d\n",
				buf_ctrl->id, buf_ctrl->type);
	}

	return 0;
}

static int dec_cleanup_buf_ctrls(struct s5p_mfc_ctx *ctx, struct list_head *head)
{
	struct s5p_mfc_buf_ctrl *buf_ctrl;

	while (!list_empty(head)) {
		buf_ctrl = list_entry(head->next,
				      struct s5p_mfc_buf_ctrl, list);

		mfc_debug(5, "del buf ctrl id: 0x%08x\n",  buf_ctrl->id);

		list_del(&buf_ctrl->list);
		kfree(buf_ctrl);
	}

	INIT_LIST_HEAD(head);

	return 0;
}

static int dec_to_buf_ctrls(struct s5p_mfc_ctx *ctx, struct list_head *head)
{
	struct s5p_mfc_ctx_ctrl *ctx_ctrl;
	struct s5p_mfc_buf_ctrl *buf_ctrl;

	list_for_each_entry(ctx_ctrl, &ctx->ctrls, list) {
		if ((ctx_ctrl->type != MFC_CTRL_TYPE_SET) || (!ctx_ctrl->has_new))
			continue;

		list_for_each_entry(buf_ctrl, head, list) {
			if (buf_ctrl->id == ctx_ctrl->id) {
				buf_ctrl->has_new = 1;
				buf_ctrl->val = ctx_ctrl->val;
				if (buf_ctrl->is_volatile)
					buf_ctrl->updated = 0;

				ctx_ctrl->has_new = 0;
				break;
			}
		}
	}

	list_for_each_entry(buf_ctrl, head, list) {
		if (buf_ctrl->has_new)
			mfc_debug(5, "id: 0x%08x val: %d\n",
				 buf_ctrl->id, buf_ctrl->val);
	}

	return 0;
}

static int dec_to_ctx_ctrls(struct s5p_mfc_ctx *ctx, struct list_head *head)
{
	struct s5p_mfc_ctx_ctrl *ctx_ctrl;
	struct s5p_mfc_buf_ctrl *buf_ctrl;

	list_for_each_entry(buf_ctrl, head, list) {
		if (!buf_ctrl->has_new)
			continue;

		list_for_each_entry(ctx_ctrl, &ctx->ctrls, list) {
			if ((ctx_ctrl->type & MFC_CTRL_TYPE_GET) == 0)
				continue;

			if (ctx_ctrl->id == buf_ctrl->id) {
				mfc_debug(2, "overwrite ctx ctrl value\n");

				ctx_ctrl->has_new = 1;
				ctx_ctrl->val = buf_ctrl->val;

				buf_ctrl->has_new = 0;
			}
		}
	}

	list_for_each_entry(ctx_ctrl, &ctx->ctrls, list) {
		if (ctx_ctrl->has_new)
			mfc_debug(5, "id: 0x%08x val: %d\n",
				  ctx_ctrl->id, ctx_ctrl->val);
	}

	return 0;
}

static int dec_set_buf_ctrls_val(struct s5p_mfc_ctx *ctx, struct list_head *head)
{
	struct s5p_mfc_buf_ctrl *buf_ctrl;
	unsigned int value = 0;

	list_for_each_entry(buf_ctrl, head, list) {
		if (!buf_ctrl->has_new)
			continue;

		/* read old vlaue */
		if (buf_ctrl->mode == MFC_CTRL_MODE_SFR)
			value = s5p_mfc_read_reg(buf_ctrl->addr);
		else if (buf_ctrl->mode == MFC_CTRL_MODE_SHM)
			value = s5p_mfc_read_info(ctx, buf_ctrl->addr);

		/* save old vlaue for recovery */
		if (buf_ctrl->is_volatile)
			buf_ctrl->old_val = (value >> buf_ctrl->shft) & buf_ctrl->mask;

		/* write new value */
		value &= ~(buf_ctrl->mask << buf_ctrl->shft);
		value |= ((buf_ctrl->val & buf_ctrl->mask) << buf_ctrl->shft);

		if (buf_ctrl->mode == MFC_CTRL_MODE_SFR)
			s5p_mfc_write_reg(value, buf_ctrl->addr);
		else if (buf_ctrl->mode == MFC_CTRL_MODE_SHM)
			s5p_mfc_write_info(ctx, value, buf_ctrl->addr);

		/* set change flag bit */
		if (buf_ctrl->flag_mode == MFC_CTRL_MODE_SFR) {
			value = s5p_mfc_read_reg(buf_ctrl->flag_addr);
			value |= (1 << buf_ctrl->flag_shft);
			s5p_mfc_write_reg(value, buf_ctrl->flag_addr);
		} else if (buf_ctrl->flag_mode == MFC_CTRL_MODE_SHM) {
			value = s5p_mfc_read_info(ctx, buf_ctrl->flag_addr);
			value |= (1 << buf_ctrl->flag_shft);
			s5p_mfc_write_info(ctx, value, buf_ctrl->flag_addr);
		}

		buf_ctrl->has_new = 0;
		buf_ctrl->updated = 1;

		mfc_debug(5, "id: 0x%08x val: %d\n", buf_ctrl->id,
			  buf_ctrl->val);
	}

	return 0;
}

static int dec_get_buf_ctrls_val(struct s5p_mfc_ctx *ctx, struct list_head *head)
{
	struct s5p_mfc_buf_ctrl *buf_ctrl;
	unsigned int value = 0;

	list_for_each_entry(buf_ctrl, head, list) {
		if ((buf_ctrl->type & MFC_CTRL_TYPE_GET) == 0)
			continue;

		if (buf_ctrl->mode == MFC_CTRL_MODE_SFR)
			value = s5p_mfc_read_reg(buf_ctrl->addr);
		else if (buf_ctrl->mode == MFC_CTRL_MODE_SHM)
			value = s5p_mfc_read_info(ctx, buf_ctrl->addr);

		value = (value >> buf_ctrl->shft) & buf_ctrl->mask;

		buf_ctrl->val = value;
		buf_ctrl->has_new = 1;

		mfc_debug(5, "id: 0x%08x val: %d\n", buf_ctrl->id,
			  buf_ctrl->val);
	}

	return 0;
}

static int dec_recover_buf_ctrls_val(struct s5p_mfc_ctx *ctx, struct list_head *head)
{
	struct s5p_mfc_buf_ctrl *buf_ctrl;
	unsigned int value = 0;

	list_for_each_entry(buf_ctrl, head, list) {
		if ((!buf_ctrl->is_volatile) || (!buf_ctrl->updated))
			continue;

		if (buf_ctrl->mode == MFC_CTRL_MODE_SFR)
			value = s5p_mfc_read_reg(buf_ctrl->addr);
		else if (buf_ctrl->mode == MFC_CTRL_MODE_SHM)
			value = s5p_mfc_read_info(ctx, buf_ctrl->addr);

		value &= ~(buf_ctrl->mask << buf_ctrl->shft);
		value |= ((buf_ctrl->old_val & buf_ctrl->mask) << buf_ctrl->shft);

		if (buf_ctrl->mode == MFC_CTRL_MODE_SFR)
			s5p_mfc_write_reg(value, buf_ctrl->addr);
		else if (buf_ctrl->mode == MFC_CTRL_MODE_SHM)
			s5p_mfc_write_info(ctx, value, buf_ctrl->addr);

		/* clear change flag bit */
		if (buf_ctrl->flag_mode == MFC_CTRL_MODE_SFR) {
			value = s5p_mfc_read_reg(buf_ctrl->flag_addr);
			value &= ~(1 << buf_ctrl->flag_shft);
			s5p_mfc_write_reg(value, buf_ctrl->flag_addr);
		} else if (buf_ctrl->flag_mode == MFC_CTRL_MODE_SHM) {
			value = s5p_mfc_read_info(ctx, buf_ctrl->flag_addr);
			value &= ~(1 << buf_ctrl->flag_shft);
			s5p_mfc_write_info(ctx, value, buf_ctrl->flag_addr);
		}

		mfc_debug(5, "id: 0x%08x old_val: %d\n", buf_ctrl->id,
			  buf_ctrl->old_val);
	}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}

static struct s5p_mfc_codec_ops decoder_codec_ops = {
	.pre_seq_start		= NULL,
	.post_seq_start		= NULL,
	.pre_frame_start	= NULL,
	.post_frame_start	= NULL,
<<<<<<< HEAD
=======
	.init_ctx_ctrls		= dec_init_ctx_ctrls,
	.cleanup_ctx_ctrls	= dec_cleanup_ctx_ctrls,
	.init_buf_ctrls		= dec_init_buf_ctrls,
	.cleanup_buf_ctrls	= dec_cleanup_buf_ctrls,
	.to_buf_ctrls		= dec_to_buf_ctrls,
	.to_ctx_ctrls		= dec_to_ctx_ctrls,
	.set_buf_ctrls_val	= dec_set_buf_ctrls_val,
	.get_buf_ctrls_val	= dec_get_buf_ctrls_val,
	.recover_buf_ctrls_val	= dec_recover_buf_ctrls_val,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
};

/* Query capabilities of the device */
static int vidioc_querycap(struct file *file, void *priv,
			   struct v4l2_capability *cap)
{
	struct s5p_mfc_dev *dev = video_drvdata(file);

	strncpy(cap->driver, dev->plat_dev->name, sizeof(cap->driver) - 1);
	strncpy(cap->card, dev->plat_dev->name, sizeof(cap->card) - 1);
	cap->bus_info[0] = 0;
	cap->version = KERNEL_VERSION(1, 0, 0);
<<<<<<< HEAD
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE_MPLANE |
			V4L2_CAP_VIDEO_OUTPUT_MPLANE | V4L2_CAP_STREAMING;
=======
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_VIDEO_OUTPUT
						    | V4L2_CAP_STREAMING;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}

/* Enumerate format */
static int vidioc_enum_fmt(struct v4l2_fmtdesc *f, bool mplane, bool out)
{
	struct s5p_mfc_fmt *fmt;
	int i, j = 0;

	for (i = 0; i < ARRAY_SIZE(formats); ++i) {
		if (mplane && formats[i].num_planes == 1)
			continue;
		else if (!mplane && formats[i].num_planes > 1)
			continue;
<<<<<<< HEAD
=======
		/* FIXME: to Kamil */
		/*
		if (out && formats[i].type != MFC_FMT_RAW)
			continue;
		else if (!out && formats[i].type != MFC_FMT_DEC)
			continue;
		*/
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		if (out && formats[i].type != MFC_FMT_DEC)
			continue;
		else if (!out && formats[i].type != MFC_FMT_RAW)
			continue;

		if (j == f->index)
			break;
		++j;
	}
	if (i == ARRAY_SIZE(formats))
		return -EINVAL;
	fmt = &formats[i];
	strlcpy(f->description, fmt->name, sizeof(f->description));
	f->pixelformat = fmt->fourcc;
	return 0;
}

static int vidioc_enum_fmt_vid_cap(struct file *file, void *pirv,
							struct v4l2_fmtdesc *f)
{
	return vidioc_enum_fmt(f, false, false);
}

static int vidioc_enum_fmt_vid_cap_mplane(struct file *file, void *pirv,
							struct v4l2_fmtdesc *f)
{
	return vidioc_enum_fmt(f, true, false);
}

static int vidioc_enum_fmt_vid_out(struct file *file, void *prov,
							struct v4l2_fmtdesc *f)
{
	return vidioc_enum_fmt(f, false, true);
}

static int vidioc_enum_fmt_vid_out_mplane(struct file *file, void *prov,
							struct v4l2_fmtdesc *f)
{
	return vidioc_enum_fmt(f, true, true);
}

/* Get format */
static int vidioc_g_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);
=======
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
	struct s5p_mfc_dec *dec = ctx->dec_priv;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	struct v4l2_pix_format_mplane *pix_mp;

	mfc_debug_enter();
	pix_mp = &f->fmt.pix_mp;
<<<<<<< HEAD
	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    (ctx->state == MFCINST_GOT_INST || ctx->state ==
						MFCINST_RES_CHANGE_END)) {
=======
	mfc_debug(2, "f->type = %d ctx->state = %d\n", f->type, ctx->state);
	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    (ctx->state == MFCINST_GOT_INST || ctx->state == MFCINST_RES_CHANGE_END)) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		/* If the MFC is parsing the header,
		 * so wait until it is finished */
		s5p_mfc_clean_ctx_int_flags(ctx);
		s5p_mfc_wait_for_done_ctx(ctx, S5P_FIMV_R2H_CMD_SEQ_DONE_RET,
<<<<<<< HEAD
									0);
=======
									1);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	}
	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE &&
	    ctx->state >= MFCINST_HEAD_PARSED &&
	    ctx->state < MFCINST_ABORT) {
<<<<<<< HEAD
		/* This is run on CAPTURE (decode output) */
=======
		/* This is run on CAPTURE (deocde output) */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		/* Width and height are set to the dimensions
		   of the movie, the buffer is bigger and
		   further processing stages should crop to this
		   rectangle. */
<<<<<<< HEAD
		pix_mp->width = ctx->buf_width;
		pix_mp->height = ctx->buf_height;
=======
		pix_mp->width = ctx->img_width;
		pix_mp->height = ctx->img_height;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		pix_mp->field = V4L2_FIELD_NONE;
		pix_mp->num_planes = 2;
		/* Set pixelformat to the format in which MFC
		   outputs the decoded frame */
		pix_mp->pixelformat = V4L2_PIX_FMT_NV12MT;
		pix_mp->plane_fmt[0].bytesperline = ctx->buf_width;
<<<<<<< HEAD
		pix_mp->plane_fmt[0].sizeimage = ctx->luma_size;
		pix_mp->plane_fmt[1].bytesperline = ctx->buf_width;
		pix_mp->plane_fmt[1].sizeimage = ctx->chroma_size;
=======
		pix_mp->plane_fmt[0].sizeimage = ctx->buf_width * ctx->buf_height;
		pix_mp->plane_fmt[1].bytesperline = ctx->buf_width;
		pix_mp->plane_fmt[1].sizeimage = ctx->buf_width * (ctx->buf_height >> 1);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	} else if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		/* This is run on OUTPUT
		   The buffer contains compressed image
		   so width and height have no meaning */
		pix_mp->width = 0;
		pix_mp->height = 0;
		pix_mp->field = V4L2_FIELD_NONE;
<<<<<<< HEAD
		pix_mp->plane_fmt[0].bytesperline = ctx->dec_src_buf_size;
		pix_mp->plane_fmt[0].sizeimage = ctx->dec_src_buf_size;
=======
		pix_mp->plane_fmt[0].bytesperline = dec->src_buf_size;
		pix_mp->plane_fmt[0].sizeimage = dec->src_buf_size;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		pix_mp->pixelformat = ctx->src_fmt->fourcc;
		pix_mp->num_planes = ctx->src_fmt->num_planes;
	} else {
		mfc_err("Format could not be read\n");
		mfc_debug(2, "%s-- with error\n", __func__);
		return -EINVAL;
	}
	mfc_debug_leave();
	return 0;
}

/* Try format */
static int vidioc_try_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
<<<<<<< HEAD
	struct s5p_mfc_fmt *fmt;

	if (f->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		mfc_err("This node supports decoding only\n");
		return -EINVAL;
	}
	fmt = find_format(f, MFC_FMT_DEC);
	if (!fmt) {
		mfc_err("Unsupported format\n");
		return -EINVAL;
	}
	if (fmt->type != MFC_FMT_DEC) {
		mfc_err("\n");
		return -EINVAL;
	}
=======
	struct s5p_mfc_dev *dev = video_drvdata(file);
	struct s5p_mfc_fmt *fmt;

	mfc_debug(2, "Type is %d\n", f->type);
	if (f->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		fmt = find_format(f, MFC_FMT_DEC);
		if (!fmt) {
			mfc_err("Unsupported format for source.\n");
			return -EINVAL;
		}
		if (!IS_MFCV6(dev)) {
			if (fmt->fourcc == V4L2_PIX_FMT_VP8) {
				mfc_err("Not supported format.\n");
				return -EINVAL;
			}
		}
	} else if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		fmt = find_format(f, MFC_FMT_RAW);
		if (!fmt) {
			mfc_err("Unsupported format for destination.\n");
			return -EINVAL;
		}
		if (IS_MFCV6(dev)) {
			if (fmt->fourcc == V4L2_PIX_FMT_NV12MT) {
				mfc_err("Not supported format.\n");
				return -EINVAL;
			}
		} else {
			if (fmt->fourcc != V4L2_PIX_FMT_NV12MT) {
				mfc_err("Not supported format.\n");
				return -EINVAL;
			}
		}
	}
	/* Width and height are left intact as they may be relevant for
	 * FIMV1 decoding. */

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}

/* Set format */
static int vidioc_s_fmt(struct file *file, void *priv, struct v4l2_format *f)
{
	struct s5p_mfc_dev *dev = video_drvdata(file);
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	int ret = 0;
	struct s5p_mfc_fmt *fmt;
	struct v4l2_pix_format_mplane *pix_mp;
=======
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
	struct s5p_mfc_dec *dec = ctx->dec_priv;
	unsigned long flags;
	int ret = 0;
	struct s5p_mfc_fmt *fmt;
	struct v4l2_pix_format_mplane *pix_mp;
	int i;
	struct s5p_mfc_ctx_ctrl *ctx_ctrl;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

	mfc_debug_enter();
	ret = vidioc_try_fmt(file, priv, f);
	pix_mp = &f->fmt.pix_mp;
	if (ret)
		return ret;
	if (ctx->vq_src.streaming || ctx->vq_dst.streaming) {
		v4l2_err(&dev->v4l2_dev, "%s queue busy\n", __func__);
		ret = -EBUSY;
		goto out;
	}
<<<<<<< HEAD
	fmt = find_format(f, MFC_FMT_DEC);
	if (!fmt || fmt->codec_mode == S5P_FIMV_CODEC_NONE) {
		mfc_err("Unknown codec\n");
		ret = -EINVAL;
		goto out;
	}
	if (fmt->type != MFC_FMT_DEC) {
		mfc_err("Wrong format selected, you should choose "
					"format for decoding\n");
		ret = -EINVAL;
		goto out;
=======

	if (f->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		fmt = find_format(f, MFC_FMT_RAW);
		if (!fmt) {
			mfc_err("Unsupported format for source.\n");
			return -EINVAL;
		}
		if (!IS_MFCV6(dev)) {
			if (fmt->fourcc != V4L2_PIX_FMT_NV12MT) {
				mfc_err("Not supported format.\n");
				return -EINVAL;
			}
		} else if (IS_MFCV6(dev)) {
			if (fmt->fourcc == V4L2_PIX_FMT_NV12MT) {
				mfc_err("Not supported format.\n");
				return -EINVAL;
			}
		}
		ctx->dst_fmt = fmt;
		mfc_debug_leave();
		return ret;
	} else if (f->type != V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		mfc_err("Wrong type error for S_FMT : %d", f->type);
		return -EINVAL;
	}

	fmt = find_format(f, MFC_FMT_DEC);
	if (!fmt || fmt->codec_mode == MFC_FORMATS_NO_CODEC) {
		mfc_err("Unknown codec.\n");
		ret = -EINVAL;
		goto out;
	}
	if (!IS_MFCV6(dev)) {
		if (fmt->fourcc == V4L2_PIX_FMT_VP8) {
			mfc_err("Not supported format.\n");
			return -EINVAL;
		}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	}
	ctx->src_fmt = fmt;
	ctx->codec_mode = fmt->codec_mode;
	mfc_debug(2, "The codec number is: %d\n", ctx->codec_mode);
<<<<<<< HEAD
	pix_mp->height = 0;
	pix_mp->width = 0;
	if (pix_mp->plane_fmt[0].sizeimage)
		ctx->dec_src_buf_size = pix_mp->plane_fmt[0].sizeimage;
	else
		pix_mp->plane_fmt[0].sizeimage = ctx->dec_src_buf_size =
								DEF_CPB_SIZE;
	pix_mp->plane_fmt[0].bytesperline = 0;
	ctx->state = MFCINST_INIT;
=======
	ctx->pix_format = pix_mp->pixelformat;
	if ((pix_mp->width > 0) && (pix_mp->height > 0)) {
		ctx->img_height = pix_mp->height;
		ctx->img_width = pix_mp->width;
	}
	/* As this buffer will contain compressed data, the size is set
	 * to the maximum size. */
	if (pix_mp->plane_fmt[0].sizeimage)
		dec->src_buf_size = pix_mp->plane_fmt[0].sizeimage;
	else
		dec->src_buf_size = MAX_FRAME_SIZE;
	mfc_debug(2, "s_fmt w/h: %dx%d, ctx: %dx%d\n", pix_mp->width,
		pix_mp->height, ctx->img_width, ctx->img_height);
	mfc_debug(2, "sizeimage: %d\n", pix_mp->plane_fmt[0].sizeimage);
	pix_mp->plane_fmt[0].bytesperline = 0;

	/* In case of calling s_fmt twice or more */
	if (ctx->inst_no != MFC_NO_INSTANCE_SET) {
		ctx->state = MFCINST_RETURN_INST;
		spin_lock_irqsave(&dev->condlock, flags);
		set_bit(ctx->num, &dev->ctx_work_bits);
		spin_unlock_irqrestore(&dev->condlock, flags);
		s5p_mfc_clean_ctx_int_flags(ctx);
		s5p_mfc_try_run(dev);
		/* Wait until instance is returned or timeout occured */
		if (s5p_mfc_wait_for_done_ctx
		    (ctx, S5P_FIMV_R2H_CMD_CLOSE_INSTANCE_RET, 0)) {
			mfc_err("Err returning instance.\n");
		}
		/* Free resources */
		s5p_mfc_release_instance_buffer(ctx);
		s5p_mfc_release_dec_desc_buffer(ctx);

		ctx->state = MFCINST_INIT;
	}

	if (dec->crc_enable && (ctx->codec_mode == S5P_FIMV_CODEC_H264_DEC ||
				ctx->codec_mode == S5P_FIMV_CODEC_H264_MVC_DEC)) {
		/* CRC related control types should be changed by the codec mode. */
		mfc_debug(5, "ctx_ctrl is changed for H.264\n");
		list_for_each_entry(ctx_ctrl, &ctx->ctrls, list) {
			switch (ctx_ctrl->id) {
			case V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_LUMA:
				ctx_ctrl->type = MFC_CTRL_TYPE_GET_DST;
				ctx_ctrl->addr = S5P_FIMV_CRC_DISP_LUMA0;
				break;
			case V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_CHROMA:
				ctx_ctrl->type = MFC_CTRL_TYPE_GET_DST;
				ctx_ctrl->addr = S5P_FIMV_CRC_DISP_CHROMA0;
				break;
			case V4L2_CID_MPEG_MFC51_VIDEO_CRC_GENERATED:
				ctx_ctrl->type = MFC_CTRL_TYPE_GET_DST;
				ctx_ctrl->addr = S5P_FIMV_CRC_DISP_STATUS;
				break;
			case V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_LUMA_BOT:
			case V4L2_CID_MPEG_MFC51_VIDEO_CRC_DATA_CHROMA_BOT:
				ctx_ctrl->type = MFC_CTRL_TYPE_GET_DST;
				break;
			default:
				break;
			}
		}

		/* Reinitialize controls for source buffers */
		for (i = 0; i < MFC_MAX_BUFFERS; i++) {
			if (ctx->src_ctrls_flag[i]) {
				if (call_cop(ctx, cleanup_buf_ctrls, ctx, &ctx->src_ctrls[i]) < 0)
					mfc_err("failed in cleanup_buf_ctrls\n");
				ctx->src_ctrls_flag[i] = 0;
				if (call_cop(ctx, init_buf_ctrls, ctx, MFC_CTRL_TYPE_SRC, i) < 0)
					mfc_err("failed in init_buf_ctrls\n");
			}
		}
	}

	s5p_mfc_alloc_instance_buffer(ctx);
	s5p_mfc_alloc_dec_temp_buffers(ctx);
	spin_lock_irqsave(&dev->condlock, flags);
	set_bit(ctx->num, &dev->ctx_work_bits);
	spin_unlock_irqrestore(&dev->condlock, flags);
	s5p_mfc_clean_ctx_int_flags(ctx);
	s5p_mfc_try_run(dev);
	if (s5p_mfc_wait_for_done_ctx(ctx,
				S5P_FIMV_R2H_CMD_OPEN_INSTANCE_RET, 1)) {
		/* Error or timeout */
		mfc_err("Error getting instance from hardware.\n");
		s5p_mfc_release_instance_buffer(ctx);
		s5p_mfc_release_dec_desc_buffer(ctx);
		ret = -EIO;
		goto out;
	}
	mfc_debug(2, "Got instance number: %d\n", ctx->inst_no);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
out:
	mfc_debug_leave();
	return ret;
}

/* Reqeust buffers */
static int vidioc_reqbufs(struct file *file, void *priv,
<<<<<<< HEAD
					  struct v4l2_requestbuffers *reqbufs)
{
	struct s5p_mfc_dev *dev = video_drvdata(file);
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	int ret = 0;
	unsigned long flags;

	if (reqbufs->memory != V4L2_MEMORY_MMAP) {
		mfc_err("Only V4L2_MEMORY_MAP is supported\n");
		return -EINVAL;
	}
	if (reqbufs->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		/* Can only request buffers after an instance has been opened.*/
		if (ctx->state == MFCINST_INIT) {
			ctx->src_bufs_cnt = 0;
			if (reqbufs->count == 0) {
				mfc_debug(2, "Freeing buffers\n");
				s5p_mfc_clock_on();
				ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
				s5p_mfc_clock_off();
=======
		struct v4l2_requestbuffers *reqbufs)
{
	struct s5p_mfc_dev *dev = video_drvdata(file);
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
	struct s5p_mfc_dec *dec = ctx->dec_priv;
	int ret = 0;
	unsigned long flags;
	int cacheable;

	mfc_debug_enter();
	mfc_debug(2, "Memory type: %d\n", reqbufs->memory);

	if (reqbufs->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		cacheable = (ctx->cacheable & MFCMASK_SRC_CACHE) ? 1 : 0;
		s5p_mfc_mem_set_cacheable(ctx->dev->alloc_ctx[MFC_CMA_BANK1_ALLOC_CTX], cacheable);
		/* Can only request buffers after
		   an instance has been opened.*/
		if (ctx->state == MFCINST_GOT_INST) {
			if (reqbufs->count == 0) {
				mfc_debug(2, "Freeing buffers.\n");
				ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
				return ret;
			}
			/* Decoding */
			if (ctx->output_state != QUEUE_FREE) {
<<<<<<< HEAD
				mfc_err("Bufs have already been requested\n");
				return -EINVAL;
			}
			s5p_mfc_clock_on();
			ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
			s5p_mfc_clock_off();
			if (ret) {
				mfc_err("vb2_reqbufs on output failed\n");
=======
				mfc_err("Bufs have already been requested.\n");
				return -EINVAL;
			}
			ret = vb2_reqbufs(&ctx->vq_src, reqbufs);
			if (ret) {
				mfc_err("vb2_reqbufs on output failed.\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
				return ret;
			}
			mfc_debug(2, "vb2_reqbufs: %d\n", ret);
			ctx->output_state = QUEUE_BUFS_REQUESTED;
		}
	} else if (reqbufs->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
<<<<<<< HEAD
		ctx->dst_bufs_cnt = 0;
		if (reqbufs->count == 0) {
			mfc_debug(2, "Freeing buffers\n");
			s5p_mfc_clock_on();
			ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
			s5p_mfc_clock_off();
			return ret;
		}
		if (ctx->capture_state != QUEUE_FREE) {
			mfc_err("Bufs have already been requested\n");
			return -EINVAL;
		}
		ctx->capture_state = QUEUE_BUFS_REQUESTED;
		s5p_mfc_clock_on();
		ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
		s5p_mfc_clock_off();
		if (ret) {
			mfc_err("vb2_reqbufs on capture failed\n");
			return ret;
		}
		if (reqbufs->count < ctx->dpb_count) {
			mfc_err("Not enough buffers allocated\n");
			reqbufs->count = 0;
			s5p_mfc_clock_on();
			ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
			s5p_mfc_clock_off();
			return -ENOMEM;
		}
		ctx->total_dpb_count = reqbufs->count;
		ret = s5p_mfc_alloc_codec_buffers(ctx);
		if (ret) {
			mfc_err("Failed to allocate decoding buffers\n");
			reqbufs->count = 0;
			s5p_mfc_clock_on();
			ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
			s5p_mfc_clock_off();
			return -ENOMEM;
		}
		if (ctx->dst_bufs_cnt == ctx->total_dpb_count) {
			ctx->capture_state = QUEUE_BUFS_MMAPED;
		} else {
			mfc_err("Not all buffers passed to buf_init\n");
			reqbufs->count = 0;
			s5p_mfc_clock_on();
			ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
			s5p_mfc_release_codec_buffers(ctx);
			s5p_mfc_clock_off();
			return -ENOMEM;
		}
=======
		dec->dst_memtype = reqbufs->memory;

		/* cacheable setting */
		cacheable = (ctx->cacheable & MFCMASK_DST_CACHE) ? 1 : 0;
		if (ctx->is_drm) {
			s5p_mfc_mem_set_cacheable(ctx->dev->alloc_ctx_drm,
				cacheable);
		} else {
			if (!IS_MFCV6(dev))
				s5p_mfc_mem_set_cacheable(ctx->dev->alloc_ctx[MFC_CMA_BANK2_ALLOC_CTX],
					cacheable);

			s5p_mfc_mem_set_cacheable(ctx->dev->alloc_ctx[MFC_CMA_BANK1_ALLOC_CTX],
				cacheable);
		}

		if (reqbufs->count == 0) {
			mfc_debug(2, "Freeing buffers.\n");
			ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
			dec->dpb_queue_cnt = 0;
			return ret;
		}

		if (ctx->capture_state != QUEUE_FREE) {
			mfc_err("Bufs have already been requested.\n");
			return -EINVAL;
		}

		ctx->capture_state = QUEUE_BUFS_REQUESTED;

		ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
		if (ret) {
			mfc_err("vb2_reqbufs on capture failed.\n");
			return ret;
		}

		if (reqbufs->count < ctx->dpb_count) {
			mfc_err("Not enough buffers allocated.\n");
			reqbufs->count = 0;
			ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
			return -ENOMEM;
		}

		dec->total_dpb_count = reqbufs->count;

		ret = s5p_mfc_alloc_codec_buffers(ctx);
		if (ret) {
			mfc_err("Failed to allocate decoding buffers.\n");
			reqbufs->count = 0;
			ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
			return -ENOMEM;
		}

		if (dec->dst_memtype == V4L2_MEMORY_MMAP) {
			if (dec->dpb_queue_cnt == dec->total_dpb_count) {
				ctx->capture_state = QUEUE_BUFS_MMAPED;
			} else {
				mfc_err("Not all buffers passed to buf_init.\n");
				reqbufs->count = 0;
				ret = vb2_reqbufs(&ctx->vq_dst, reqbufs);
				s5p_mfc_release_codec_buffers(ctx);
				return -ENOMEM;
			}
		}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		if (s5p_mfc_ctx_ready(ctx)) {
			spin_lock_irqsave(&dev->condlock, flags);
			set_bit(ctx->num, &dev->ctx_work_bits);
			spin_unlock_irqrestore(&dev->condlock, flags);
		}
<<<<<<< HEAD
		s5p_mfc_try_run(dev);
		s5p_mfc_wait_for_done_ctx(ctx,
					 S5P_FIMV_R2H_CMD_INIT_BUFFERS_RET, 0);
	}
=======

		s5p_mfc_try_run(dev);

		if (dec->dst_memtype == V4L2_MEMORY_MMAP) {
			s5p_mfc_wait_for_done_ctx(ctx,
					S5P_FIMV_R2H_CMD_INIT_BUFFERS_RET, 1);
		}
	}

	mfc_debug_leave();

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return ret;
}

/* Query buffer */
static int vidioc_querybuf(struct file *file, void *priv,
						   struct v4l2_buffer *buf)
{
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	int ret;
	int i;

	if (buf->memory != V4L2_MEMORY_MMAP) {
		mfc_err("Only mmaped buffers can be used\n");
		return -EINVAL;
	}
	mfc_debug(2, "State: %d, buf->type: %d\n", ctx->state, buf->type);
	if (ctx->state == MFCINST_INIT &&
=======
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
	int ret;
	int i;

	mfc_debug_enter();

	if (buf->memory != V4L2_MEMORY_MMAP) {
		mfc_err("Only mmaped buffers can be used.\n");
		return -EINVAL;
	}

	mfc_debug(2, "State: %d, buf->type: %d\n", ctx->state, buf->type);
	if (ctx->state == MFCINST_GOT_INST &&
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
			buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		ret = vb2_querybuf(&ctx->vq_src, buf);
	} else if (ctx->state == MFCINST_RUNNING &&
			buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		ret = vb2_querybuf(&ctx->vq_dst, buf);
		for (i = 0; i < buf->length; i++)
			buf->m.planes[i].m.mem_offset += DST_QUEUE_OFF_BASE;
	} else {
<<<<<<< HEAD
		mfc_err("vidioc_querybuf called in an inappropriate state\n");
=======
		mfc_err("vidioc_querybuf called in an inappropriate state.\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		ret = -EINVAL;
	}
	mfc_debug_leave();
	return ret;
}

/* Queue a buffer */
static int vidioc_qbuf(struct file *file, void *priv, struct v4l2_buffer *buf)
{
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	if (ctx->state == MFCINST_ERROR) {
		mfc_err("Call on QBUF after unrecoverable error\n");
		return -EIO;
	}
	if (buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		return vb2_qbuf(&ctx->vq_src, buf);
	else if (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		return vb2_qbuf(&ctx->vq_dst, buf);
=======
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);

	mfc_debug_enter();

	mfc_debug(2, "Enqueued buf: %d, (type = %d)\n", buf->index, buf->type);
	if (ctx->state == MFCINST_ERROR) {
		mfc_err("Call on QBUF after unrecoverable error.\n");
		return -EIO;
	}

	if (buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		return vb2_qbuf(&ctx->vq_src, buf);
	else
		return vb2_qbuf(&ctx->vq_dst, buf);

	mfc_debug_leave();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return -EINVAL;
}

/* Dequeue a buffer */
static int vidioc_dqbuf(struct file *file, void *priv, struct v4l2_buffer *buf)
{
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	if (ctx->state == MFCINST_ERROR) {
		mfc_err("Call on DQBUF after unrecoverable error\n");
		return -EIO;
	}
	if (buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		return vb2_dqbuf(&ctx->vq_src, buf, file->f_flags & O_NONBLOCK);
	else if (buf->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		return vb2_dqbuf(&ctx->vq_dst, buf, file->f_flags & O_NONBLOCK);
	return -EINVAL;
=======
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
	int ret;

	mfc_debug_enter();
	mfc_debug(2, "Addr: %p %p %p Type: %d\n", &ctx->vq_src, buf, buf->m.planes,
								buf->type);
	if (ctx->state == MFCINST_ERROR) {
		mfc_err("Call on DQBUF after unrecoverable error.\n");
		return -EIO;
	}
	if (buf->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		ret = vb2_dqbuf(&ctx->vq_src, buf, file->f_flags & O_NONBLOCK);
	else
		ret = vb2_dqbuf(&ctx->vq_dst, buf, file->f_flags & O_NONBLOCK);
	mfc_debug_leave();
	return ret;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
}

/* Stream on */
static int vidioc_streamon(struct file *file, void *priv,
			   enum v4l2_buf_type type)
{
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned long flags;
=======
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
#ifdef CONFIG_BUSFREQ_OPP
#ifdef CONFIG_CPU_EXYNOS5250
	struct s5p_mfc_dev *dev = ctx->dev;
	int freq_mif = 400;
	int freq_int = 200;
	int lock_bw = 1280 * 720;
#endif
#endif
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	int ret = -EINVAL;

	mfc_debug_enter();
	if (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
<<<<<<< HEAD

		if (ctx->state == MFCINST_INIT) {
			ctx->dst_bufs_cnt = 0;
			ctx->src_bufs_cnt = 0;
			ctx->capture_state = QUEUE_FREE;
			ctx->output_state = QUEUE_FREE;
			s5p_mfc_alloc_instance_buffer(ctx);
			s5p_mfc_alloc_dec_temp_buffers(ctx);
			spin_lock_irqsave(&dev->condlock, flags);
			set_bit(ctx->num, &dev->ctx_work_bits);
			spin_unlock_irqrestore(&dev->condlock, flags);
			s5p_mfc_clean_ctx_int_flags(ctx);
			s5p_mfc_try_run(dev);

			if (s5p_mfc_wait_for_done_ctx(ctx,
				S5P_FIMV_R2H_CMD_OPEN_INSTANCE_RET, 0)) {
				/* Error or timeout */
				mfc_err("Error getting instance from hardware\n");
				s5p_mfc_release_instance_buffer(ctx);
				s5p_mfc_release_dec_desc_buffer(ctx);
				return -EIO;
			}
			mfc_debug(2, "Got instance number: %d\n", ctx->inst_no);
		}
		ret = vb2_streamon(&ctx->vq_src, type);
		}
	else if (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		ret = vb2_streamon(&ctx->vq_dst, type);
=======
		ret = vb2_streamon(&ctx->vq_src, type);
	} else {
#ifdef CONFIG_BUSFREQ_OPP
#ifdef CONFIG_CPU_EXYNOS5250
		if ((atomic_read(&dev->busfreq_lock) == 0) &&
				(ctx->img_width * ctx->img_height > lock_bw)) {
			dev_lock(dev->bus_dev, dev->v4l2_dev.dev, (freq_mif * 1000) + freq_int);
			atomic_set(&dev->busfreq_lock, 1);
			mfc_debug(1, "busfreq locked on <%d/%d>MHz\n", freq_mif, freq_int);
		}
#endif
#endif
		ret = vb2_streamon(&ctx->vq_dst, type);
	}
	mfc_debug(2, "ctx->src_queue_cnt = %d ctx->state = %d "
		  "ctx->dst_queue_cnt = %d ctx->dpb_count = %d\n",
		  ctx->src_queue_cnt, ctx->state, ctx->dst_queue_cnt,
		  ctx->dpb_count);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	mfc_debug_leave();
	return ret;
}

/* Stream off, which equals to a pause */
static int vidioc_streamoff(struct file *file, void *priv,
			    enum v4l2_buf_type type)
{
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);

	if (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE)
		return vb2_streamoff(&ctx->vq_src, type);
	else if (type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE)
		return vb2_streamoff(&ctx->vq_dst, type);
	return -EINVAL;
}

/* Set controls - v4l2 control framework */
static int s5p_mfc_dec_s_ctrl(struct v4l2_ctrl *ctrl)
{
	struct s5p_mfc_ctx *ctx = ctrl_to_ctx(ctrl);

	switch (ctrl->id) {
	case V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY:
		ctx->loop_filter_mpeg4 = ctrl->val;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY_ENABLE:
		ctx->display_delay_enable = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
		ctx->display_delay = ctrl->val;
		break;
	case V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE:
		ctx->slice_interface = ctrl->val;
		break;
	default:
		mfc_err("Invalid control 0x%08x\n", ctrl->id);
		return -EINVAL;
	}
	return 0;
}

static int s5p_mfc_dec_g_v_ctrl(struct v4l2_ctrl *ctrl)
{
	struct s5p_mfc_ctx *ctx = ctrl_to_ctx(ctrl);
	struct s5p_mfc_dev *dev = ctx->dev;

	switch (ctrl->id) {
	case V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		if (ctx->state >= MFCINST_HEAD_PARSED &&
		    ctx->state < MFCINST_ABORT) {
			ctrl->val = ctx->dpb_count;
			break;
		} else if (ctx->state != MFCINST_INIT) {
			v4l2_err(&dev->v4l2_dev, "Decoding not initialised\n");
			return -EINVAL;
		}
		/* Should wait for the header to be parsed */
		s5p_mfc_clean_ctx_int_flags(ctx);
		s5p_mfc_wait_for_done_ctx(ctx,
				S5P_FIMV_R2H_CMD_SEQ_DONE_RET, 0);
		if (ctx->state >= MFCINST_HEAD_PARSED &&
		    ctx->state < MFCINST_ABORT) {
			ctrl->val = ctx->dpb_count;
		} else {
			v4l2_err(&dev->v4l2_dev, "Decoding not initialised\n");
			return -EINVAL;
		}
		break;
	}
	return 0;
}


static const struct v4l2_ctrl_ops s5p_mfc_dec_ctrl_ops = {
	.s_ctrl = s5p_mfc_dec_s_ctrl,
	.g_volatile_ctrl = s5p_mfc_dec_g_v_ctrl,
};
=======
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
#ifdef CONFIG_BUSFREQ_OPP
#ifdef CONFIG_CPU_EXYNOS5250
	struct s5p_mfc_dev *dev = ctx->dev;
#endif
#endif
	int ret;

	mfc_debug_enter();
	ret = -EINVAL;
	if (type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		ret = vb2_streamoff(&ctx->vq_src, type);
	} else {
		ret = vb2_streamoff(&ctx->vq_dst, type);
#ifdef CONFIG_BUSFREQ_OPP
#ifdef CONFIG_CPU_EXYNOS5250
		if (atomic_read(&dev->busfreq_lock) == 1) {
			dev_unlock(dev->bus_dev, dev->v4l2_dev.dev);
			atomic_set(&dev->busfreq_lock, 0);
			mfc_debug(1, "busfreq locked off\n");
		}
#endif
#endif
	}
	mfc_debug_leave();
	return ret;
}

/* Query a ctrl */
static int vidioc_queryctrl(struct file *file, void *priv,
			    struct v4l2_queryctrl *qc)
{
	struct v4l2_queryctrl *c;

	c = get_ctrl(qc->id);
	if (!c)
		return -EINVAL;
	*qc = *c;
	return 0;
}

/* Get ctrl */
static int get_ctrl_val(struct s5p_mfc_ctx *ctx, struct v4l2_control *ctrl)
{
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_dec *dec = ctx->dec_priv;
	struct s5p_mfc_ctx_ctrl *ctx_ctrl;
	int ret = 0;

	mfc_debug_enter();

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
		ctrl->value = dec->loop_filter_mpeg4;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY:
		ctrl->value = dec->display_delay;
		break;
	case V4L2_CID_CACHEABLE:
		ctrl->value = ctx->cacheable;
		break;
	case V4L2_CID_MIN_BUFFERS_FOR_CAPTURE:
		if (ctx->state >= MFCINST_HEAD_PARSED &&
		    ctx->state < MFCINST_ABORT) {
			ctrl->value = ctx->dpb_count;
			break;
		} else if (ctx->state != MFCINST_INIT) {
			v4l2_err(&dev->v4l2_dev, "Decoding not initialised.\n");
			return -EINVAL;
		}

		/* Should wait for the header to be parsed */
		s5p_mfc_clean_ctx_int_flags(ctx);
		s5p_mfc_wait_for_done_ctx(ctx,
				S5P_FIMV_R2H_CMD_SEQ_DONE_RET, 1);
		if (ctx->state >= MFCINST_HEAD_PARSED &&
		    ctx->state < MFCINST_ABORT) {
			ctrl->value = ctx->dpb_count;
		} else {
			v4l2_err(&dev->v4l2_dev,
					 "Decoding not initialised.\n");
			return -EINVAL;
		}
		break;
	case V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE:
		ctrl->value = dec->slice_enable;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_PACKED_PB:
		ctrl->value = dec->is_packedpb;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_CRC_ENABLE:
		ctrl->value = dec->crc_enable;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_CHECK_STATE:
		if (ctx->state == MFCINST_RES_CHANGE_FLUSH
				|| ctx->state == MFCINST_RES_CHANGE_END
				|| ctx->state == MFCINST_HEAD_PARSED)
			ctrl->value = MFCSTATE_DEC_RES_DETECT;
		else if (ctx->state == MFCINST_FINISHING)
			ctrl->value = MFCSTATE_DEC_TERMINATING;
		else
			ctrl->value = MFCSTATE_PROCESSING;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING:
		ctrl->value = dec->sei_parse;
		break;
	default:
		list_for_each_entry(ctx_ctrl, &ctx->ctrls, list) {
			if ((ctx_ctrl->type & MFC_CTRL_TYPE_GET) == 0)
				continue;

			if (ctx_ctrl->id == ctrl->id) {
				if (ctx_ctrl->has_new) {
					ctx_ctrl->has_new = 0;
					ctrl->value = ctx_ctrl->val;
				} else {
					ctrl->value = 0;
				}

				ret = 1;
				break;
			}
		}
		if (!ret) {
			v4l2_err(&dev->v4l2_dev, "invalid control 0x%08x\n", ctrl->id);
			return -EINVAL;
		}
	}

	mfc_debug_leave();

	return 0;
}

/* Get a ctrl */
static int vidioc_g_ctrl(struct file *file, void *priv,
			struct v4l2_control *ctrl)
{
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
	int ret = 0;

	mfc_debug_enter();
	ret = get_ctrl_val(ctx, ctrl);
	mfc_debug_leave();

	return ret;
}

/* Set a ctrl */
static int vidioc_s_ctrl(struct file *file, void *priv,
			 struct v4l2_control *ctrl)
{
	struct s5p_mfc_dev *dev = video_drvdata(file);
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
	struct s5p_mfc_dec *dec = ctx->dec_priv;
	struct s5p_mfc_ctx_ctrl *ctx_ctrl;
	int ret = 0;
	int stream_on;

	mfc_debug_enter();

	stream_on = ctx->vq_src.streaming || ctx->vq_dst.streaming;

	ret = check_ctrl_val(ctx, ctrl);
	if (ret != 0)
		return ret;

	switch (ctrl->id) {
	case V4L2_CID_MPEG_VIDEO_DECODER_MPEG4_DEBLOCK_FILTER:
		if (stream_on)
			return -EBUSY;
		dec->loop_filter_mpeg4 = ctrl->value;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_DECODER_H264_DISPLAY_DELAY:
		if (stream_on)
			return -EBUSY;
		dec->display_delay = ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_DECODER_SLICE_INTERFACE:
		if (stream_on)
			return -EBUSY;
		dec->slice_enable = ctrl->value;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_PACKED_PB:
		if (stream_on)
			return -EBUSY;
		if (ctx->codec_mode != S5P_FIMV_CODEC_MPEG4_DEC &&
			ctx->codec_mode != S5P_FIMV_CODEC_FIMV1_DEC &&
			ctx->codec_mode != S5P_FIMV_CODEC_FIMV2_DEC &&
			ctx->codec_mode != S5P_FIMV_CODEC_FIMV3_DEC &&
			ctx->codec_mode != S5P_FIMV_CODEC_FIMV4_DEC)
			return -EINVAL;
		dec->is_packedpb = ctrl->value;
		break;
	case V4L2_CID_MPEG_MFC51_VIDEO_CRC_ENABLE:
		if (ctrl->value == 1 || ctrl->value == 0)
			dec->crc_enable = ctrl->value;
		else
			dec->crc_enable = 0;
		break;
	case V4L2_CID_CACHEABLE:
		/*if (stream_on)
			return -EBUSY; */
		ctx->cacheable |= ctrl->value;
		break;
	case V4L2_CID_MPEG_VIDEO_H264_SEI_FRAME_PACKING:
		/*if (stream_on)
			return -EBUSY; */
		if(ctrl->value == 0 || ctrl->value ==1)
			dec->sei_parse = ctrl->value;
		else
			dec->sei_parse = 0;
		break;
	default:
		list_for_each_entry(ctx_ctrl, &ctx->ctrls, list) {
			if (ctx_ctrl->type != MFC_CTRL_TYPE_SET)
				continue;

			if (ctx_ctrl->id == ctrl->id) {
				ctx_ctrl->has_new = 1;
				ctx_ctrl->val = ctrl->value;

				ret = 1;
				break;
			}
		}

		if (!ret) {
			v4l2_err(&dev->v4l2_dev, "invalid control 0x%08x\n", ctrl->id);
			return -EINVAL;
		}
	}

	mfc_debug_leave();

	return 0;
}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

/* Get cropping information */
static int vidioc_g_crop(struct file *file, void *priv,
		struct v4l2_crop *cr)
{
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(priv);
	u32 left, right, top, bottom;

	if (ctx->state != MFCINST_HEAD_PARSED &&
	ctx->state != MFCINST_RUNNING && ctx->state != MFCINST_FINISHING
					&& ctx->state != MFCINST_FINISHED) {
			mfc_err("Cannont set crop\n");
			return -EINVAL;
		}
	if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_H264) {
		left = s5p_mfc_read_shm(ctx, CROP_INFO_H);
		right = left >> S5P_FIMV_SHARED_CROP_RIGHT_SHIFT;
		left = left & S5P_FIMV_SHARED_CROP_LEFT_MASK;
		top = s5p_mfc_read_shm(ctx, CROP_INFO_V);
=======
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
	u32 left, right, top, bottom;

	mfc_debug_enter();
	if (ctx->state != MFCINST_HEAD_PARSED &&
	ctx->state != MFCINST_RUNNING && ctx->state != MFCINST_FINISHING
					&& ctx->state != MFCINST_FINISHED) {
			mfc_debug(2, "%s-- with error\n", __func__);
			return -EINVAL;
		}
	if (ctx->src_fmt->fourcc == V4L2_PIX_FMT_H264) {
		s5p_mfc_clock_on();
		left = s5p_mfc_read_info(ctx, CROP_INFO_H);
		right = left >> S5P_FIMV_SHARED_CROP_RIGHT_SHIFT;
		left = left & S5P_FIMV_SHARED_CROP_LEFT_MASK;
		top = s5p_mfc_read_info(ctx, CROP_INFO_V);
		s5p_mfc_clock_off();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		bottom = top >> S5P_FIMV_SHARED_CROP_BOTTOM_SHIFT;
		top = top & S5P_FIMV_SHARED_CROP_TOP_MASK;
		cr->c.left = left;
		cr->c.top = top;
		cr->c.width = ctx->img_width - left - right;
		cr->c.height = ctx->img_height - top - bottom;
		mfc_debug(2, "Cropping info [h264]: l=%d t=%d "
			"w=%d h=%d (r=%d b=%d fw=%d fh=%d\n", left, top,
			cr->c.width, cr->c.height, right, bottom,
			ctx->buf_width, ctx->buf_height);
	} else {
		cr->c.left = 0;
		cr->c.top = 0;
		cr->c.width = ctx->img_width;
		cr->c.height = ctx->img_height;
		mfc_debug(2, "Cropping info: w=%d h=%d fw=%d "
			"fh=%d\n", cr->c.width,	cr->c.height, ctx->buf_width,
							ctx->buf_height);
	}
<<<<<<< HEAD
	return 0;
}

=======
	mfc_debug_leave();
	return 0;
}

static int vidioc_g_ext_ctrls(struct file *file, void *priv,
			struct v4l2_ext_controls *f)
{
	struct s5p_mfc_ctx *ctx = fh_to_mfc_ctx(file->private_data);
	struct v4l2_ext_control *ext_ctrl;
	struct v4l2_control ctrl;
	int i;
	int ret = 0;

	if (f->ctrl_class != V4L2_CTRL_CLASS_MPEG)
		return -EINVAL;

	for (i = 0; i < f->count; i++) {
		ext_ctrl = (f->controls + i);

		ctrl.id = ext_ctrl->id;

		ret = get_ctrl_val(ctx, &ctrl);
		if (ret == 0) {
			ext_ctrl->value = ctrl.value;
		} else {
			f->error_idx = i;
			break;
		}

		mfc_debug(2, "[%d] id: 0x%08x, value: %d", i, ext_ctrl->id, ext_ctrl->value);
	}

	return ret;
}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
/* v4l2_ioctl_ops */
static const struct v4l2_ioctl_ops s5p_mfc_dec_ioctl_ops = {
	.vidioc_querycap = vidioc_querycap,
	.vidioc_enum_fmt_vid_cap = vidioc_enum_fmt_vid_cap,
	.vidioc_enum_fmt_vid_cap_mplane = vidioc_enum_fmt_vid_cap_mplane,
	.vidioc_enum_fmt_vid_out = vidioc_enum_fmt_vid_out,
	.vidioc_enum_fmt_vid_out_mplane = vidioc_enum_fmt_vid_out_mplane,
	.vidioc_g_fmt_vid_cap_mplane = vidioc_g_fmt,
	.vidioc_g_fmt_vid_out_mplane = vidioc_g_fmt,
	.vidioc_try_fmt_vid_cap_mplane = vidioc_try_fmt,
	.vidioc_try_fmt_vid_out_mplane = vidioc_try_fmt,
	.vidioc_s_fmt_vid_cap_mplane = vidioc_s_fmt,
	.vidioc_s_fmt_vid_out_mplane = vidioc_s_fmt,
	.vidioc_reqbufs = vidioc_reqbufs,
	.vidioc_querybuf = vidioc_querybuf,
	.vidioc_qbuf = vidioc_qbuf,
	.vidioc_dqbuf = vidioc_dqbuf,
	.vidioc_streamon = vidioc_streamon,
	.vidioc_streamoff = vidioc_streamoff,
<<<<<<< HEAD
	.vidioc_g_crop = vidioc_g_crop,
};

static int s5p_mfc_queue_setup(struct vb2_queue *vq,
			const struct v4l2_format *fmt, unsigned int *buf_count,
			unsigned int *plane_count, unsigned int psize[],
			void *allocators[])
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);

	/* Video output for decoding (source)
	 * this can be set after getting an instance */
	if (ctx->state == MFCINST_INIT &&
	    vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
=======
	.vidioc_queryctrl = vidioc_queryctrl,
	.vidioc_g_ctrl = vidioc_g_ctrl,
	.vidioc_s_ctrl = vidioc_s_ctrl,
	.vidioc_g_crop = vidioc_g_crop,
	.vidioc_g_ext_ctrls = vidioc_g_ext_ctrls,
};

static int s5p_mfc_queue_setup(struct vb2_queue *vq, unsigned int *buf_count,
			       unsigned int *plane_count, unsigned long psize[],
			       void *allocators[])
{
	struct s5p_mfc_ctx *ctx = vq->drv_priv;
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_dec *dec = ctx->dec_priv;

	mfc_debug_enter();

	/* Video output for decoding (source)
	 * this can be set after getting an instance */
	if (ctx->state == MFCINST_GOT_INST &&
	    vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		mfc_debug(2, "setting for VIDEO output\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		/* A single plane is required for input */
		*plane_count = 1;
		if (*buf_count < 1)
			*buf_count = 1;
		if (*buf_count > MFC_MAX_BUFFERS)
			*buf_count = MFC_MAX_BUFFERS;
	/* Video capture for decoding (destination)
	 * this can be set after the header was parsed */
	} else if (ctx->state == MFCINST_HEAD_PARSED &&
		   vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
<<<<<<< HEAD
=======
		mfc_debug(2, "setting for VIDEO capture\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
		/* Output plane count is 2 - one for Y and one for CbCr */
		*plane_count = 2;
		/* Setup buffer count */
		if (*buf_count < ctx->dpb_count)
			*buf_count = ctx->dpb_count;
		if (*buf_count > ctx->dpb_count + MFC_MAX_EXTRA_DPB)
			*buf_count = ctx->dpb_count + MFC_MAX_EXTRA_DPB;
		if (*buf_count > MFC_MAX_BUFFERS)
			*buf_count = MFC_MAX_BUFFERS;
	} else {
		mfc_err("State seems invalid. State = %d, vq->type = %d\n",
							ctx->state, vq->type);
		return -EINVAL;
	}
<<<<<<< HEAD
	mfc_debug(2, "Buffer count=%d, plane count=%d\n",
						*buf_count, *plane_count);
=======
	mfc_debug(2, "%s, buffer count=%d, plane count=%d type=0x%x\n", __func__,
					*buf_count, *plane_count, vq->type);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (ctx->state == MFCINST_HEAD_PARSED &&
	    vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		psize[0] = ctx->luma_size;
		psize[1] = ctx->chroma_size;
<<<<<<< HEAD
		allocators[0] = ctx->dev->alloc_ctx[MFC_BANK2_ALLOC_CTX];
		allocators[1] = ctx->dev->alloc_ctx[MFC_BANK1_ALLOC_CTX];
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE &&
		   ctx->state == MFCINST_INIT) {
		psize[0] = ctx->dec_src_buf_size;
		allocators[0] = ctx->dev->alloc_ctx[MFC_BANK1_ALLOC_CTX];
	} else {
		mfc_err("This video node is dedicated to decoding. Decoding not initalised\n");
		return -EINVAL;
	}
=======

		if (IS_MFCV6(dev))
			allocators[0] = ctx->dev->alloc_ctx[MFC_CMA_BANK1_ALLOC_CTX];
		else
			allocators[0] = ctx->dev->alloc_ctx[MFC_CMA_BANK2_ALLOC_CTX];
		allocators[1] = ctx->dev->alloc_ctx[MFC_CMA_BANK1_ALLOC_CTX];
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE &&
		   ctx->state == MFCINST_GOT_INST) {
		psize[0] = dec->src_buf_size;
		allocators[0] = ctx->dev->alloc_ctx[MFC_CMA_BANK1_ALLOC_CTX];
	} else {
		mfc_err("Currently only decoding is supported. Decoding not initalised.\n");
		return -EINVAL;
	}

	mfc_debug(2, "%s, plane=0, size=%lu\n", __func__, psize[0]);
	mfc_debug(2, "%s, plane=1, size=%lu\n", __func__, psize[1]);

	mfc_debug_leave();

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}

static void s5p_mfc_unlock(struct vb2_queue *q)
{
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
=======
	struct s5p_mfc_ctx *ctx = q->drv_priv;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	struct s5p_mfc_dev *dev = ctx->dev;

	mutex_unlock(&dev->mfc_mutex);
}

static void s5p_mfc_lock(struct vb2_queue *q)
{
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
=======
	struct s5p_mfc_ctx *ctx = q->drv_priv;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	struct s5p_mfc_dev *dev = ctx->dev;

	mutex_lock(&dev->mfc_mutex);
}

static int s5p_mfc_buf_init(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	unsigned int i;

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		if (ctx->capture_state == QUEUE_BUFS_MMAPED)
			return 0;
		for (i = 0; i <= ctx->src_fmt->num_planes ; i++) {
			if (IS_ERR_OR_NULL(ERR_PTR(
					vb2_dma_contig_plane_dma_addr(vb, i)))) {
				mfc_err("Plane mem not allocated\n");
				return -EINVAL;
			}
		}
		if (vb2_plane_size(vb, 0) < ctx->luma_size ||
			vb2_plane_size(vb, 1) < ctx->chroma_size) {
			mfc_err("Plane buffer (CAPTURE) is too small\n");
			return -EINVAL;
		}
		i = vb->v4l2_buf.index;
		ctx->dst_bufs[i].b = vb;
		ctx->dst_bufs[i].cookie.raw.luma =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->dst_bufs[i].cookie.raw.chroma =
					vb2_dma_contig_plane_dma_addr(vb, 1);
		ctx->dst_bufs_cnt++;
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		if (IS_ERR_OR_NULL(ERR_PTR(
					vb2_dma_contig_plane_dma_addr(vb, 0)))) {
			mfc_err("Plane memory not allocated\n");
			return -EINVAL;
		}
		if (vb2_plane_size(vb, 0) < ctx->dec_src_buf_size) {
			mfc_err("Plane buffer (OUTPUT) is too small\n");
			return -EINVAL;
		}

		i = vb->v4l2_buf.index;
		ctx->src_bufs[i].b = vb;
		ctx->src_bufs[i].cookie.stream =
					vb2_dma_contig_plane_dma_addr(vb, 0);
		ctx->src_bufs_cnt++;
	} else {
		mfc_err("s5p_mfc_buf_init: unknown queue type\n");
		return -EINVAL;
	}
	return 0;
}

static int s5p_mfc_start_streaming(struct vb2_queue *q, unsigned int count)
{
	struct s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned long flags;

	v4l2_ctrl_handler_setup(&ctx->ctrl_handler);
	if (ctx->state == MFCINST_FINISHING ||
		ctx->state == MFCINST_FINISHED)
		ctx->state = MFCINST_RUNNING;
=======
	struct s5p_mfc_ctx *ctx = vq->drv_priv;
	struct s5p_mfc_dec *dec = ctx->dec_priv;
	struct s5p_mfc_buf *buf = vb_to_mfc_buf(vb);
	int i;

	mfc_debug_enter();

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		if (ctx->capture_state == QUEUE_BUFS_MMAPED) {
			mfc_debug_leave();
			return 0;
		}
		for (i = 0; i <= ctx->src_fmt->num_planes ; i++) {
			if (mfc_plane_cookie(vb, i) == 0) {
				mfc_err("Plane mem not allocated.\n");
				return -EINVAL;
			}
		}

		buf->cookie.raw.luma = mfc_plane_cookie(vb, 0);
		buf->cookie.raw.chroma = mfc_plane_cookie(vb, 1);

		list_add_tail(&buf->list, &dec->dpb_queue);
		dec->dpb_queue_cnt++;

		if (call_cop(ctx, init_buf_ctrls, ctx, MFC_CTRL_TYPE_DST, vb->v4l2_buf.index) < 0)
			mfc_err("failed in init_buf_ctrls\n");
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		if (mfc_plane_cookie(vb, 0)  == 0) {
			mfc_err("Plane memory not allocated.\n");
			return -EINVAL;
		}
		buf->cookie.stream = mfc_plane_cookie(vb, 0);

		if (call_cop(ctx, init_buf_ctrls, ctx, MFC_CTRL_TYPE_SRC, vb->v4l2_buf.index) < 0)
			mfc_err("failed in init_buf_ctrls\n");
	} else {
		mfc_err("s5p_mfc_buf_init: unknown queue type.\n");
		return -EINVAL;
	}

	mfc_debug_leave();

	return 0;
}

static int s5p_mfc_buf_prepare(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
	struct s5p_mfc_ctx *ctx = vq->drv_priv;
	struct s5p_mfc_dec *dec = ctx->dec_priv;
	unsigned int index = vb->v4l2_buf.index;

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		if (vb2_plane_size(vb, 0) < ctx->luma_size ||
			vb2_plane_size(vb, 1) < ctx->chroma_size) {
			mfc_err("Plane buffer (CAPTURE) is too small.\n");
			return -EINVAL;
		}
		mfc_debug(2, "Size: 0=%lu 2=%lu\n", vb2_plane_size(vb, 0),
							vb2_plane_size(vb, 1));
		if (ctx->cacheable & MFCMASK_DST_CACHE)
			s5p_mfc_mem_cache_flush(vb, 2);
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		if (ctx->cacheable & MFCMASK_SRC_CACHE)
			s5p_mfc_mem_cache_flush(vb, 1);
		mfc_debug(2, "Plane size: %ld, ctx->dec_src_buf_size: %d\n",
				vb2_plane_size(vb, 0), dec->src_buf_size);
		if (vb2_plane_size(vb, 0) < dec->src_buf_size) {
			mfc_err("Plane buffer (OUTPUT) is too small.\n");
			return -EINVAL;
		}
		if (call_cop(ctx, to_buf_ctrls, ctx, &ctx->src_ctrls[index]) < 0)
			mfc_err("failed in to_buf_ctrls\n");
	}
	return 0;
}

static int s5p_mfc_buf_finish(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
	struct s5p_mfc_ctx *ctx = vq->drv_priv;
	unsigned int index = vb->v4l2_buf.index;

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		if (ctx->cacheable & MFCMASK_DST_CACHE)
			s5p_mfc_mem_cache_flush(vb, 2);
		if (call_cop(ctx, to_ctx_ctrls, ctx, &ctx->dst_ctrls[index]) < 0)
			mfc_err("failed in to_buf_ctrls\n");
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		if (call_cop(ctx, to_ctx_ctrls, ctx, &ctx->src_ctrls[index]) < 0)
			mfc_err("failed in to_buf_ctrls\n");
		#if 0
		/* if there are not-handled mfc_ctrl, remove all */
		while (!list_empty(&ctx->src_ctrls[index])) {
			mfc_ctrl = list_entry((&ctx->src_ctrls[index])->next,
					      struct s5p_mfc_ctrl, list);
			mfc_debug(2, "not handled ctrl id: 0x%08x val: %d\n",
				  mfc_ctrl->id, mfc_ctrl->val);
			list_del(&mfc_ctrl->list);
			kfree(mfc_ctrl);
		}
		#endif
	}

	return 0;
}

static void s5p_mfc_buf_cleanup(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
	struct s5p_mfc_ctx *ctx = vq->drv_priv;
	unsigned int index = vb->v4l2_buf.index;

	mfc_debug_enter();

	if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		if (call_cop(ctx, cleanup_buf_ctrls, ctx, &ctx->dst_ctrls[index]) < 0)
			mfc_err("failed in cleanup_buf_ctrls\n");
		ctx->dst_ctrls_flag[index] = 0;
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		if (call_cop(ctx, cleanup_buf_ctrls, ctx, &ctx->src_ctrls[index]) < 0)
			mfc_err("failed in cleanup_buf_ctrls\n");
		ctx->src_ctrls_flag[index] = 0;
	} else {
		mfc_err("s5p_mfc_buf_cleanup: unknown queue type.\n");
	}

	mfc_debug_leave();
}

static int s5p_mfc_start_streaming(struct vb2_queue *q)
{
	struct s5p_mfc_ctx *ctx = q->drv_priv;
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned long flags;

	if (ctx->state == MFCINST_FINISHING || ctx->state == MFCINST_FINISHED)
		ctx->state = MFCINST_RUNNING;

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	/* If context is ready then dev = work->data;schedule it to run */
	if (s5p_mfc_ctx_ready(ctx)) {
		spin_lock_irqsave(&dev->condlock, flags);
		set_bit(ctx->num, &dev->ctx_work_bits);
		spin_unlock_irqrestore(&dev->condlock, flags);
	}
<<<<<<< HEAD
	s5p_mfc_try_run(dev);
=======

	s5p_mfc_try_run(dev);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}

static int s5p_mfc_stop_streaming(struct vb2_queue *q)
{
	unsigned long flags;
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(q->drv_priv);
=======
	struct s5p_mfc_ctx *ctx = q->drv_priv;
	struct s5p_mfc_dec *dec = ctx->dec_priv;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	struct s5p_mfc_dev *dev = ctx->dev;
	int aborted = 0;

	if ((ctx->state == MFCINST_FINISHING ||
		ctx->state ==  MFCINST_RUNNING) &&
<<<<<<< HEAD
		dev->curr_ctx == ctx->num && dev->hw_lock) {
		ctx->state = MFCINST_ABORT;
		s5p_mfc_wait_for_done_ctx(ctx,
					S5P_FIMV_R2H_CMD_FRAME_DONE_RET, 0);
		aborted = 1;
	}
	spin_lock_irqsave(&dev->irqlock, flags);
=======
		(dev->curr_ctx == ctx->num) && test_bit(0, &dev->hw_lock)) {
		ctx->state = MFCINST_ABORT;
		s5p_mfc_wait_for_done_ctx(ctx, S5P_FIMV_R2H_CMD_FRAME_DONE_RET,
					  0);
		aborted = 1;
	}

	spin_lock_irqsave(&dev->irqlock, flags);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (q->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		s5p_mfc_cleanup_queue(&ctx->dst_queue, &ctx->vq_dst);
		INIT_LIST_HEAD(&ctx->dst_queue);
		ctx->dst_queue_cnt = 0;
<<<<<<< HEAD
		ctx->dpb_flush_flag = 1;
		ctx->dec_dst_flag = 0;
	}
=======
		dec->dpb_flush = 1;
		dec->dpb_status = 0;

		INIT_LIST_HEAD(&dec->dpb_queue);
		dec->dpb_queue_cnt = 0;
	}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (q->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		s5p_mfc_cleanup_queue(&ctx->src_queue, &ctx->vq_src);
		INIT_LIST_HEAD(&ctx->src_queue);
		ctx->src_queue_cnt = 0;
	}
<<<<<<< HEAD
	if (aborted)
		ctx->state = MFCINST_RUNNING;
	spin_unlock_irqrestore(&dev->irqlock, flags);
=======

	if (aborted)
		ctx->state = MFCINST_RUNNING;

	spin_unlock_irqrestore(&dev->irqlock, flags);

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	return 0;
}


static void s5p_mfc_buf_queue(struct vb2_buffer *vb)
{
	struct vb2_queue *vq = vb->vb2_queue;
<<<<<<< HEAD
	struct s5p_mfc_ctx *ctx = fh_to_ctx(vq->drv_priv);
	struct s5p_mfc_dev *dev = ctx->dev;
	unsigned long flags;
	struct s5p_mfc_buf *mfc_buf;

	if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		mfc_buf = &ctx->src_bufs[vb->v4l2_buf.index];
		mfc_buf->used = 0;
		spin_lock_irqsave(&dev->irqlock, flags);
		list_add_tail(&mfc_buf->list, &ctx->src_queue);
		ctx->src_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		mfc_buf = &ctx->dst_bufs[vb->v4l2_buf.index];
		mfc_buf->used = 0;
		/* Mark destination as available for use by MFC */
		spin_lock_irqsave(&dev->irqlock, flags);
		set_bit(vb->v4l2_buf.index, &ctx->dec_dst_flag);
		list_add_tail(&mfc_buf->list, &ctx->dst_queue);
		ctx->dst_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);
	} else {
		mfc_err("Unsupported buffer type (%d)\n", vq->type);
	}
=======
	struct s5p_mfc_ctx *ctx = vq->drv_priv;
	struct s5p_mfc_dev *dev = ctx->dev;
	struct s5p_mfc_dec *dec = ctx->dec_priv;
	unsigned long flags;
	struct s5p_mfc_buf *buf = vb_to_mfc_buf(vb);
	struct s5p_mfc_buf *dpb_buf, *tmp_buf;
	int wait_flag = 0;
	int remove_flag = 0;

	mfc_debug_enter();

	if (vq->type == V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE) {
		buf->used = 0;
		mfc_debug(2, "Src queue: %p\n", &ctx->src_queue);
		mfc_debug(2, "Adding to src: %p (%08lx, %08x)\n", vb,
				mfc_plane_cookie(vb, 0),
				buf->cookie.stream);
		spin_lock_irqsave(&dev->irqlock, flags);
		list_add_tail(&buf->list, &ctx->src_queue);
		ctx->src_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);

#ifdef STREAM_SAVE
		vb2_save_buf(vb, 0);
#endif
	} else if (vq->type == V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE) {
		buf->used = 0;
		mfc_debug(2, "Dst queue: %p\n", &ctx->dst_queue);
		mfc_debug(2, "Adding to dst: %p (%lx)\n", vb,
						  mfc_plane_cookie(vb, 0));
		mfc_debug(2, "ADDING Flag before: %lx (%d)\n",
					dec->dpb_status, vb->v4l2_buf.index);
		/* Mark destination as available for use by MFC */
		spin_lock_irqsave(&dev->irqlock, flags);
		if (!list_empty(&dec->dpb_queue)) {
			remove_flag = 0;
			list_for_each_entry_safe(dpb_buf, tmp_buf, &dec->dpb_queue, list) {
				if (dpb_buf == buf) {
					list_del(&dpb_buf->list);
					remove_flag = 1;
					break;
				}
			}
			if (remove_flag == 0) {
				mfc_err("Can't find buf(0x%x)\n", buf->cookie.raw.luma);
				spin_unlock_irqrestore(&dev->irqlock, flags);
				return;
			}
		}
		set_bit(vb->v4l2_buf.index, &dec->dpb_status);
		mfc_debug(2, "ADDING Flag after: %lx\n", dec->dpb_status);
		list_add_tail(&buf->list, &ctx->dst_queue);
		ctx->dst_queue_cnt++;
		spin_unlock_irqrestore(&dev->irqlock, flags);
		if (dec->dst_memtype == V4L2_MEMORY_USERPTR &&
				ctx->dst_queue_cnt == dec->total_dpb_count)
			ctx->capture_state = QUEUE_BUFS_MMAPED;
	} else {
		mfc_err("Unsupported buffer type (%d)\n", vq->type);
	}

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	if (s5p_mfc_ctx_ready(ctx)) {
		spin_lock_irqsave(&dev->condlock, flags);
		set_bit(ctx->num, &dev->ctx_work_bits);
		spin_unlock_irqrestore(&dev->condlock, flags);
<<<<<<< HEAD
	}
	s5p_mfc_try_run(dev);
}

static struct vb2_ops s5p_mfc_dec_qops = {
	.queue_setup		= s5p_mfc_queue_setup,
	.wait_prepare		= s5p_mfc_unlock,
	.wait_finish		= s5p_mfc_lock,
	.buf_init		= s5p_mfc_buf_init,
	.start_streaming	= s5p_mfc_start_streaming,
	.stop_streaming		= s5p_mfc_stop_streaming,
	.buf_queue		= s5p_mfc_buf_queue,
};

struct s5p_mfc_codec_ops *get_dec_codec_ops(void)
{
	return &decoder_codec_ops;
}

struct vb2_ops *get_dec_queue_ops(void)
{
	return &s5p_mfc_dec_qops;
}

=======
		if (ctx->state == MFCINST_HEAD_PARSED)
			wait_flag = 1;
	}
	s5p_mfc_try_run(dev);
	if (wait_flag) {
		s5p_mfc_wait_for_done_ctx(ctx,
				S5P_FIMV_R2H_CMD_INIT_BUFFERS_RET, 1);
	}

	mfc_debug_leave();
}

static struct vb2_ops s5p_mfc_dec_qops = {
	.queue_setup	= s5p_mfc_queue_setup,
	.wait_prepare	= s5p_mfc_unlock,
	.wait_finish	= s5p_mfc_lock,
	.buf_init	= s5p_mfc_buf_init,
	.buf_prepare	= s5p_mfc_buf_prepare,
	.buf_finish	= s5p_mfc_buf_finish,
	.buf_cleanup	= s5p_mfc_buf_cleanup,
	.start_streaming= s5p_mfc_start_streaming,
	.stop_streaming = s5p_mfc_stop_streaming,
	.buf_queue	= s5p_mfc_buf_queue,
};

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
const struct v4l2_ioctl_ops *get_dec_v4l2_ioctl_ops(void)
{
	return &s5p_mfc_dec_ioctl_ops;
}

<<<<<<< HEAD
#define IS_MFC51_PRIV(x) ((V4L2_CTRL_ID2CLASS(x) == V4L2_CTRL_CLASS_MPEG) \
						&& V4L2_CTRL_DRIVER_PRIV(x))

int s5p_mfc_dec_ctrls_setup(struct s5p_mfc_ctx *ctx)
{
	struct v4l2_ctrl_config cfg;
	int i;

	v4l2_ctrl_handler_init(&ctx->ctrl_handler, NUM_CTRLS);
	if (ctx->ctrl_handler.error) {
		mfc_err("v4l2_ctrl_handler_init failed\n");
		return ctx->ctrl_handler.error;
	}

	for (i = 0; i < NUM_CTRLS; i++) {
		if (IS_MFC51_PRIV(controls[i].id)) {
			cfg.ops = &s5p_mfc_dec_ctrl_ops;
			cfg.id = controls[i].id;
			cfg.min = controls[i].minimum;
			cfg.max = controls[i].maximum;
			cfg.def = controls[i].default_value;
			cfg.name = controls[i].name;
			cfg.type = controls[i].type;

			cfg.step = controls[i].step;
			cfg.menu_skip_mask = 0;

			ctx->ctrls[i] = v4l2_ctrl_new_custom(&ctx->ctrl_handler,
					&cfg, NULL);
		} else {
			ctx->ctrls[i] = v4l2_ctrl_new_std(&ctx->ctrl_handler,
					&s5p_mfc_dec_ctrl_ops,
					controls[i].id, controls[i].minimum,
					controls[i].maximum, controls[i].step,
					controls[i].default_value);
		}
		if (ctx->ctrl_handler.error) {
			mfc_err("Adding control (%d) failed\n", i);
			return ctx->ctrl_handler.error;
		}
		if (controls[i].is_volatile && ctx->ctrls[i])
			ctx->ctrls[i]->flags |= V4L2_CTRL_FLAG_VOLATILE;
	}
	return 0;
}

void s5p_mfc_dec_ctrls_delete(struct s5p_mfc_ctx *ctx)
{
	int i;

	v4l2_ctrl_handler_free(&ctx->ctrl_handler);
	for (i = 0; i < NUM_CTRLS; i++)
		ctx->ctrls[i] = NULL;
}

=======
int s5p_mfc_init_dec_ctx(struct s5p_mfc_ctx *ctx)
{
	struct s5p_mfc_dec *dec;
	int i;
	int ret = 0;

	dec = kzalloc(sizeof(struct s5p_mfc_dec), GFP_KERNEL);
	if (!dec) {
		mfc_err("failed to allocate decoder private data\n");
		return -ENOMEM;
	}
	ctx->dec_priv = dec;

	ctx->inst_no = MFC_NO_INSTANCE_SET;

	INIT_LIST_HEAD(&ctx->src_queue);
	INIT_LIST_HEAD(&ctx->dst_queue);
	ctx->src_queue_cnt = 0;
	ctx->dst_queue_cnt = 0;

	for (i = 0; i < MFC_MAX_BUFFERS; i++) {
		ctx->src_ctrls_flag[i] = 0;
		ctx->dst_ctrls_flag[i] = 0;
	}

	ctx->capture_state = QUEUE_FREE;
	ctx->output_state = QUEUE_FREE;

	ctx->state = MFCINST_INIT;
	ctx->type = MFCINST_DECODER;
	ctx->c_ops = &decoder_codec_ops;
	ctx->src_fmt = &formats[DEF_SRC_FMT];
	ctx->dst_fmt = &formats[DEF_DST_FMT];

	INIT_LIST_HEAD(&dec->dpb_queue);
	dec->dpb_queue_cnt = 0;

	dec->display_delay = -1;
	dec->is_packedpb = 0;

	/* Init videobuf2 queue for OUTPUT */
	ctx->vq_src.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
	ctx->vq_src.drv_priv = ctx;
	ctx->vq_src.buf_struct_size = sizeof(struct s5p_mfc_buf);
	ctx->vq_src.io_modes = VB2_MMAP | VB2_USERPTR;
	ctx->vq_src.ops = &s5p_mfc_dec_qops;
	ctx->vq_src.mem_ops = s5p_mfc_mem_ops();
	ret = vb2_queue_init(&ctx->vq_src);
	if (ret) {
		mfc_err("Failed to initialize videobuf2 queue(output)\n");
		return ret;
	}
	/* Init videobuf2 queue for CAPTURE */
	ctx->vq_dst.type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	ctx->vq_dst.drv_priv = ctx;
	ctx->vq_dst.buf_struct_size = sizeof(struct s5p_mfc_buf);
	ctx->vq_dst.io_modes = VB2_MMAP | VB2_USERPTR;
	ctx->vq_dst.ops = &s5p_mfc_dec_qops;
	ctx->vq_dst.mem_ops = s5p_mfc_mem_ops();
	ret = vb2_queue_init(&ctx->vq_dst);
	if (ret) {
		mfc_err("Failed to initialize videobuf2 queue(capture)\n");
		return ret;
	}

	/* For MFC 6.x */
	dec->remained = 0;

	return ret;
}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
