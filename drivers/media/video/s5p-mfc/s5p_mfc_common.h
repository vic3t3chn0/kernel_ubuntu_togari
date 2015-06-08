/*
 * Samsung S5P Multi Format Codec v 5.0
 *
 * This file contains definitions of enums and structs used by the codec
 * driver.
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
 * Kamil Debski, <k.debski@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version
 */

#ifndef S5P_MFC_COMMON_H_
#define S5P_MFC_COMMON_H_

<<<<<<< HEAD
<<<<<<< HEAD
#include "regs-mfc.h"
#include <linux/platform_device.h>
#include <linux/videodev2.h>
#include <media/v4l2-ctrls.h>
#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include <media/videobuf2-core.h>

/* Definitions related to MFC memory */

/* Offset base used to differentiate between CAPTURE and OUTPUT
*  while mmaping */
#define DST_QUEUE_OFF_BASE      (TASK_SIZE / 2)

/* Offset used by the hardware to store addresses */
#define MFC_OFFSET_SHIFT	11

#define FIRMWARE_ALIGN		0x20000		/* 128KB */
#define MFC_H264_CTX_BUF_SIZE	0x96000		/* 600KB per H264 instance */
#define MFC_CTX_BUF_SIZE	0x2800		/* 10KB per instance */
#define DESC_BUF_SIZE		0x20000		/* 128KB for DESC buffer */
#define SHARED_BUF_SIZE		0x2000		/* 8KB for shared buffer */

#define DEF_CPB_SIZE		0x40000		/* 512KB */

#define MFC_BANK1_ALLOC_CTX	0
#define MFC_BANK2_ALLOC_CTX	1

#define MFC_BANK1_ALIGN_ORDER	13
#define MFC_BANK2_ALIGN_ORDER	13
#define MFC_BASE_ALIGN_ORDER	17

#include <media/videobuf2-dma-contig.h>

static inline dma_addr_t s5p_mfc_mem_cookie(void *a, void *b)
{
	/* Same functionality as the vb2_dma_contig_plane_paddr */
	dma_addr_t *paddr = vb2_dma_contig_memops.cookie(b);

	return *paddr;
}

/* MFC definitions */
#define MFC_MAX_EXTRA_DPB       5
#define MFC_MAX_BUFFERS		32
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/videodev2.h>
#include <linux/videodev2_exynos_media.h>
#include <linux/slab.h>
#include <linux/workqueue.h>

#include <media/v4l2-device.h>
#include <media/v4l2-ioctl.h>
#include <media/v4l2-fh.h>

#include <media/videobuf2-core.h>

#if defined(CONFIG_S5P_SYSTEM_MMU)
#define SYSMMU_MFC_ON
#endif

#define MFC_MAX_EXTRA_DPB       5
#define MFC_MAX_BUFFERS		32
#define MFC_MAX_REF_BUFS	2
#define MFC_FRAME_PLANES	2

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define MFC_NUM_CONTEXTS	4
/* Interrupt timeout */
#define MFC_INT_TIMEOUT		2000
/* Busy wait timeout */
#define MFC_BW_TIMEOUT		500
/* Watchdog interval */
#define MFC_WATCHDOG_INTERVAL   1000
/* After how many executions watchdog should assume lock up */
#define MFC_WATCHDOG_CNT        10
<<<<<<< HEAD
<<<<<<< HEAD
#define MFC_NO_INSTANCE_SET	-1
#define MFC_ENC_CAP_PLANE_COUNT	1
#define MFC_ENC_OUT_PLANE_COUNT	2
#define STUFF_BYTE		4
#define MFC_MAX_CTRLS		64

#define mfc_read(dev, offset)		readl(dev->regs_base + (offset))
#define mfc_write(dev, data, offset)	writel((data), dev->regs_base + \
								(offset))

/**
 * enum s5p_mfc_fmt_type - type of the pixelformat
 */
enum s5p_mfc_fmt_type {
	MFC_FMT_DEC,
	MFC_FMT_ENC,
	MFC_FMT_RAW,
};

/**
 * enum s5p_mfc_node_type - The type of an MFC device node.
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define MFC_NO_INSTANCE_SET	-1

#define MFC_ENC_CAP_PLANE_COUNT	1
#define MFC_ENC_OUT_PLANE_COUNT	2

#define MFC_NAME_LEN		16
#define MFC_FW_NAME		"mfc_fw.bin"

#define STUFF_BYTE		4
#define MFC_WORKQUEUE_LEN	32

#define MFC_BASE_MASK		((1 << 17) - 1)
#define MFC_VER_MAJOR(ver)	((ver >> 4) & 0xF)
#define MFC_VER_MINOR(ver)	(ver & 0xF)

/**
 * enum s5p_mfc_inst_type - The type of an MFC device node.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
enum s5p_mfc_node_type {
	MFCNODE_INVALID = -1,
	MFCNODE_DECODER = 0,
	MFCNODE_ENCODER = 1,
};

/**
 * enum s5p_mfc_inst_type - The type of an MFC instance.
 */
enum s5p_mfc_inst_type {
<<<<<<< HEAD
<<<<<<< HEAD
	MFCINST_INVALID,
	MFCINST_DECODER,
	MFCINST_ENCODER,
=======
	MFCINST_INVALID = 0,
	MFCINST_DECODER = 1,
	MFCINST_ENCODER = 2,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	MFCINST_INVALID = 0,
	MFCINST_DECODER = 1,
	MFCINST_ENCODER = 2,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/**
 * enum s5p_mfc_inst_state - The state of an MFC instance.
 */
enum s5p_mfc_inst_state {
	MFCINST_FREE = 0,
	MFCINST_INIT = 100,
	MFCINST_GOT_INST,
	MFCINST_HEAD_PARSED,
	MFCINST_BUFS_SET,
	MFCINST_RUNNING,
	MFCINST_FINISHING,
	MFCINST_FINISHED,
	MFCINST_RETURN_INST,
	MFCINST_ERROR,
	MFCINST_ABORT,
	MFCINST_RES_CHANGE_INIT,
	MFCINST_RES_CHANGE_FLUSH,
	MFCINST_RES_CHANGE_END,
<<<<<<< HEAD
<<<<<<< HEAD
=======
	MFCINST_RUNNING_NO_OUTPUT,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	MFCINST_RUNNING_NO_OUTPUT,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/**
 * enum s5p_mfc_queue_state - The state of buffer queue.
 */
enum s5p_mfc_queue_state {
<<<<<<< HEAD
<<<<<<< HEAD
	QUEUE_FREE,
=======
	QUEUE_FREE = 0,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	QUEUE_FREE = 0,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	QUEUE_BUFS_REQUESTED,
	QUEUE_BUFS_QUERIED,
	QUEUE_BUFS_MMAPED,
};

/**
<<<<<<< HEAD
<<<<<<< HEAD
 * enum s5p_mfc_decode_arg - type of frame decoding
 */
enum s5p_mfc_decode_arg {
	MFC_DEC_FRAME,
	MFC_DEC_LAST_FRAME,
	MFC_DEC_RES_CHANGE,
};

struct s5p_mfc_ctx;

/**
 * struct s5p_mfc_buf - MFC buffer
 */
struct s5p_mfc_buf {
	struct list_head list;
	struct vb2_buffer *b;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * enum s5p_mfc_check_state - The state for user notification
 */
enum s5p_mfc_check_state {
	MFCSTATE_PROCESSING = 0,
	MFCSTATE_DEC_RES_DETECT,
	MFCSTATE_DEC_TERMINATING,
	MFCSTATE_ENC_NO_OUTPUT,
};

/**
 * enum s5p_mfc_buf_cacheable_mask - The mask for cacheble setting
 */
enum s5p_mfc_buf_cacheable_mask {
	MFCMASK_DST_CACHE = (1 << 0),
	MFCMASK_SRC_CACHE = (1 << 1),
};

struct s5p_mfc_ctx;
struct s5p_mfc_extra_buf;

/**
 * struct s5p_mfc_buf - MFC buffer
 *
 */
struct s5p_mfc_buf {
	struct vb2_buffer vb;
	struct list_head list;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	union {
		struct {
			size_t luma;
			size_t chroma;
		} raw;
		size_t stream;
	} cookie;
	int used;
};

<<<<<<< HEAD
<<<<<<< HEAD
/**
 * struct s5p_mfc_pm - power management data structure
 */
struct s5p_mfc_pm {
	struct clk	*clock;
	struct clk	*clock_gate;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define vb_to_mfc_buf(x)	\
	container_of(x, struct s5p_mfc_buf, vb)

struct s5p_mfc_pm {
	struct clk	*clock;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	atomic_t	power;
	struct device	*device;
};

<<<<<<< HEAD
<<<<<<< HEAD
/**
 * struct s5p_mfc_dev - The struct containing driver internal parameters.
 *
 * @v4l2_dev:		v4l2_device
 * @vfd_dec:		video device for decoding
 * @vfd_enc:		video device for encoding
 * @plat_dev:		platform device
 * @mem_dev_l:		child device of the left memory bank (0)
 * @mem_dev_r:		child device of the right memory bank (1)
 * @regs_base:		base address of the MFC hw registers
 * @irq:		irq resource
 * @mfc_mem:		MFC registers memory resource
 * @dec_ctrl_handler:	control framework handler for decoding
 * @enc_ctrl_handler:	control framework handler for encoding
 * @pm:			power management control
 * @num_inst:		couter of active MFC instances
 * @irqlock:		lock for operations on videobuf2 queues
 * @condlock:		lock for changing/checking if a context is ready to be
 *			processed
 * @mfc_mutex:		lock for video_device
 * @int_cond:		variable used by the waitqueue
 * @int_type:		type of last interrupt
 * @int_err:		error number for last interrupt
 * @queue:		waitqueue for waiting for completion of device commands
 * @fw_size:		size of firmware
 * @bank1:		address of the beggining of bank 1 memory
 * @bank2:		address of the beggining of bank 2 memory
 * @hw_lock:		used for hardware locking
 * @ctx:		array of driver contexts
 * @curr_ctx:		number of the currently running context
 * @ctx_work_bits:	used to mark which contexts are waiting for hardware
 * @watchdog_cnt:	counter for the watchdog
 * @watchdog_workqueue:	workqueue for the watchdog
 * @watchdog_work:	worker for the watchdog
 * @alloc_ctx:		videobuf2 allocator contexts for two memory banks
 * @enter_suspend:	flag set when entering suspend
 *
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct s5p_mfc_fw {
	const struct firmware	*info;
	int			state;
	int			ver;
	int			date;
};

struct s5p_mfc_buf_align {
	unsigned int mfc_base_align;
};

struct s5p_mfc_buf_size_v5 {
	unsigned int h264_ctx_buf;
	unsigned int non_h264_ctx_buf;
	unsigned int desc_buf;
	unsigned int shared_buf;
};

struct s5p_mfc_buf_size_v6 {
	unsigned int dev_ctx;
	unsigned int h264_dec_ctx;
	unsigned int other_dec_ctx;
	unsigned int h264_enc_ctx;
	unsigned int other_enc_ctx;
};

struct s5p_mfc_buf_size {
	unsigned int firmware_code;
	unsigned int cpb_buf;
	void *buf;
};

struct s5p_mfc_variant {
	unsigned int version;
	unsigned int port_num;
	struct s5p_mfc_buf_size *buf_size;
	struct s5p_mfc_buf_align *buf_align;
};

/**
 * struct s5p_mfc_extra_buf - represents internal used buffer
 * @alloc:		allocation-specific contexts for each buffer
 *			(videobuf2 allocator)
 * @ofs:		offset of each buffer, will be used for MFC
 * @virt:		kernel virtual address, only valid when the
 *			buffer accessed by driver
 * @dma:		DMA address, only valid when kernel DMA API used
 */
struct s5p_mfc_extra_buf {
	void		*alloc;
	unsigned long	ofs;
	void		*virt;
	dma_addr_t	dma;
};

/**
 * struct s5p_mfc_dev - The struct containing driver internal parameters.
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
struct s5p_mfc_dev {
	struct v4l2_device	v4l2_dev;
	struct video_device	*vfd_dec;
	struct video_device	*vfd_enc;
	struct platform_device	*plat_dev;
<<<<<<< HEAD
<<<<<<< HEAD
	struct device		*mem_dev_l;
	struct device		*mem_dev_r;
	void __iomem		*regs_base;
	int			irq;
	struct resource		*mfc_mem;
	struct v4l2_ctrl_handler dec_ctrl_handler;
	struct v4l2_ctrl_handler enc_ctrl_handler;
	struct s5p_mfc_pm	pm;
	int num_inst;
	spinlock_t irqlock;	/* lock when operating on videobuf2 queues */
	spinlock_t condlock;	/* lock when changing/checking if a context is
					ready to be processed */
	struct mutex mfc_mutex; /* video_device lock */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	void __iomem		*regs_base;
	int			irq;
	struct resource		*mfc_mem;

	struct s5p_mfc_pm	pm;
	struct s5p_mfc_fw	fw;
	struct s5p_mfc_variant	*variant;
	struct s5p_mfc_platdata	*platdata;

	int num_inst;
	spinlock_t irqlock;
	spinlock_t condlock;

	struct mutex mfc_mutex;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int int_cond;
	int int_type;
	unsigned int int_err;
	wait_queue_head_t queue;
<<<<<<< HEAD
<<<<<<< HEAD
	size_t fw_size;
	size_t bank1;
	size_t bank2;
	unsigned long hw_lock;
	struct s5p_mfc_ctx *ctx[MFC_NUM_CONTEXTS];
	int curr_ctx;
	unsigned long ctx_work_bits;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	size_t port_a;
	size_t port_b;

	unsigned long hw_lock;

	/*
	struct clk *clock1;
	struct clk *clock2;
	*/

	/* For 6.x, Added for SYS_INIT context buffer */
	struct s5p_mfc_extra_buf ctx_buf;

	struct s5p_mfc_ctx *ctx[MFC_NUM_CONTEXTS];
	int curr_ctx;
	unsigned long ctx_work_bits;

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	atomic_t watchdog_cnt;
	struct timer_list watchdog_timer;
	struct workqueue_struct *watchdog_workqueue;
	struct work_struct watchdog_work;
<<<<<<< HEAD
<<<<<<< HEAD
	void *alloc_ctx[2];
	unsigned long enter_suspend;
};

/**
 * struct s5p_mfc_h264_enc_params - encoding parameters for h264
 */
struct s5p_mfc_h264_enc_params {
	enum v4l2_mpeg_video_h264_profile profile;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	struct vb2_alloc_ctx **alloc_ctx;

#ifdef CONFIG_BUSFREQ_OPP
#ifdef CONFIG_CPU_EXYNOS5250
	struct device *bus_dev;
	atomic_t busfreq_lock;
#endif
#endif

    /* for DRM */
	int curr_ctx_drm;
	int fw_status;
	int num_drm_inst;
	struct s5p_mfc_extra_buf drm_info;
	struct vb2_alloc_ctx *alloc_ctx_fw;
	struct vb2_alloc_ctx *alloc_ctx_sh;
	struct vb2_alloc_ctx *alloc_ctx_drm;

	struct work_struct work_struct;
	struct workqueue_struct *irq_workqueue;
};

/**
 *
 */
struct s5p_mfc_h264_enc_params {
	enum v4l2_mpeg_video_h264_profile profile;
	u8 level;
	u8 interlace;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	enum v4l2_mpeg_video_h264_loop_filter_mode loop_filter_mode;
	s8 loop_filter_alpha;
	s8 loop_filter_beta;
	enum v4l2_mpeg_video_h264_entropy_mode entropy_mode;
<<<<<<< HEAD
<<<<<<< HEAD
	u8 max_ref_pic;
	u8 num_ref_pic_4p;
	int _8x8_transform;
	int rc_mb;
	int rc_mb_dark;
	int rc_mb_smooth;
	int rc_mb_static;
	int rc_mb_activity;
	int vui_sar;
	u8 vui_sar_idc;
	u16 vui_ext_sar_width;
	u16 vui_ext_sar_height;
	int open_gop;
	u16 open_gop_size;
	u8 rc_frame_qp;
	u8 rc_min_qp;
	u8 rc_max_qp;
	u8 rc_p_frame_qp;
	u8 rc_b_frame_qp;
	enum v4l2_mpeg_video_h264_level level_v4l2;
	int level;
	u16 cpb_size;
};

/**
 * struct s5p_mfc_mpeg4_enc_params - encoding parameters for h263 and mpeg4
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	u8 num_ref_pic_4p;
	u8 _8x8_transform;
	u32 rc_framerate;
	u8 rc_frame_qp;
	u8 rc_min_qp;
	u8 rc_max_qp;
	u8 rc_mb_dark;
	u8 rc_mb_smooth;
	u8 rc_mb_static;
	u8 rc_mb_activity;
	u8 rc_p_frame_qp;
	u8 rc_b_frame_qp;
	u8 ar_vui;
	enum v4l2_mpeg_video_h264_vui_sar_idc ar_vui_idc;
	u16 ext_sar_width;
	u16 ext_sar_height;
	u8 open_gop;
	u16 open_gop_size;
	u8 hier_qp;
	enum v4l2_mpeg_video_h264_hierarchical_coding_type hier_qp_type;
	u8 hier_qp_layer;
	u8 hier_qp_layer_qp[7];
	u8 sei_gen_enable;
	u8 sei_fp_curr_frame_0;
	enum v4l2_mpeg_video_h264_sei_fp_arrangement_type \
					sei_fp_arrangement_type;
	u32 fmo_enable;
	u32 fmo_slice_map_type;
	u32 fmo_slice_num_grp;
	u32 fmo_run_length[4];
	u32 fmo_sg_dir;
	u32 fmo_sg_rate;
	u32 aso_enable;
	u32 aso_slice_order[8];
};

/**
 *
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
struct s5p_mfc_mpeg4_enc_params {
	/* MPEG4 Only */
	enum v4l2_mpeg_video_mpeg4_profile profile;
<<<<<<< HEAD
<<<<<<< HEAD
	int quarter_pixel;
	/* Common for MPEG4, H263 */
	u16 vop_time_res;
	u16 vop_frm_delta;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	u8 level;
	u8 quarter_pixel; /* MFC5.x */
	u16 vop_time_res;
	u16 vop_frm_delta;
	u8 rc_b_frame_qp;
	/* Common for MPEG4, H263 */
	u32 rc_framerate;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	u8 rc_frame_qp;
	u8 rc_min_qp;
	u8 rc_max_qp;
	u8 rc_p_frame_qp;
<<<<<<< HEAD
<<<<<<< HEAD
	u8 rc_b_frame_qp;
	enum v4l2_mpeg_video_mpeg4_level level_v4l2;
	int level;
};

/**
 * struct s5p_mfc_enc_params - general encoding parameters
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/**
 *
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
struct s5p_mfc_enc_params {
	u16 width;
	u16 height;

	u16 gop_size;
	enum v4l2_mpeg_video_multi_slice_mode slice_mode;
	u16 slice_mb;
	u32 slice_bit;
	u16 intra_refresh_mb;
<<<<<<< HEAD
<<<<<<< HEAD
	int pad;
	u8 pad_luma;
	u8 pad_cb;
	u8 pad_cr;
	int rc_frame;
	u32 rc_bitrate;
	u16 rc_reaction_coeff;
	u16 vbv_size;

	enum v4l2_mpeg_video_header_mode seq_hdr_mode;
	enum v4l2_mpeg_mfc51_video_frame_skip_mode frame_skip_mode;
	int fixed_target_bit;

	u8 num_b_frame;
	u32 rc_framerate_num;
	u32 rc_framerate_denom;
	int interlace;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	u8 pad;
	u8 pad_luma;
	u8 pad_cb;
	u8 pad_cr;
	u8 rc_frame;
	u32 rc_bitrate;
	u16 rc_reaction_coeff;
	u8 frame_tag;

	u8 num_b_frame;		/* H.264/MPEG4 */
	u8 rc_mb;		/* H.264: MFCv5, MPEG4/H.263: MFCv6 */
	u16 vbv_buf_size;
	enum v4l2_mpeg_video_header_mode seq_hdr_mode;
	enum v4l2_mpeg_mfc51_video_frame_skip_mode frame_skip_mode;
	u8 fixed_target_bit;

	u16 rc_frame_delta;   /* MFC6.1 Only */
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	union {
		struct s5p_mfc_h264_enc_params h264;
		struct s5p_mfc_mpeg4_enc_params mpeg4;
	} codec;
<<<<<<< HEAD
<<<<<<< HEAD

};

/**
 * struct s5p_mfc_codec_ops - codec ops, used by encoding
 */
struct s5p_mfc_codec_ops {
	/* initialization routines */
	int (*pre_seq_start) (struct s5p_mfc_ctx *ctx);
	int (*post_seq_start) (struct s5p_mfc_ctx *ctx);
	/* execution routines */
	int (*pre_frame_start) (struct s5p_mfc_ctx *ctx);
	int (*post_frame_start) (struct s5p_mfc_ctx *ctx);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

enum s5p_mfc_ctrl_type {
	MFC_CTRL_TYPE_GET_SRC	= 0x1,
	MFC_CTRL_TYPE_GET_DST	= 0x2,
	MFC_CTRL_TYPE_SET	= 0x4,
};

#define	MFC_CTRL_TYPE_GET	(MFC_CTRL_TYPE_GET_SRC | MFC_CTRL_TYPE_GET_DST)
#define	MFC_CTRL_TYPE_SRC	(MFC_CTRL_TYPE_SET | MFC_CTRL_TYPE_GET_SRC)
#define	MFC_CTRL_TYPE_DST	(MFC_CTRL_TYPE_GET_DST)

enum s5p_mfc_ctrl_mode {
	MFC_CTRL_MODE_NONE	= 0x0,
	MFC_CTRL_MODE_SFR	= 0x1,
	MFC_CTRL_MODE_SHM	= 0x2,
	MFC_CTRL_MODE_CST	= 0x4,
};

struct s5p_mfc_ctrl_cfg {
	enum s5p_mfc_ctrl_type type;
	unsigned int id;
	/*
	unsigned int is_dynamic;
	*/
	unsigned int is_volatile;	/* only for MFC_CTRL_TYPE_SET */
	unsigned int mode;
	unsigned int addr;
	unsigned int mask;
	unsigned int shft;
	unsigned int flag_mode;		/* only for MFC_CTRL_TYPE_SET */
	unsigned int flag_addr;		/* only for MFC_CTRL_TYPE_SET */
	unsigned int flag_shft;		/* only for MFC_CTRL_TYPE_SET */
};

struct s5p_mfc_ctx_ctrl {
	struct list_head list;
	enum s5p_mfc_ctrl_type type;
	unsigned int id;
	unsigned int addr;
	/*
	unsigned int is_dynamic;
	*/
	int has_new;
	int val;
};

struct s5p_mfc_buf_ctrl {
	struct list_head list;
	unsigned int id;
	enum s5p_mfc_ctrl_type type;
	int has_new;
	int val;
	unsigned int old_val;		/* only for MFC_CTRL_TYPE_SET */
	unsigned int is_volatile;	/* only for MFC_CTRL_TYPE_SET */
	unsigned int updated;
	unsigned int mode;
	unsigned int addr;
	unsigned int mask;
	unsigned int shft;
	unsigned int flag_mode;		/* only for MFC_CTRL_TYPE_SET */
	unsigned int flag_addr;		/* only for MFC_CTRL_TYPE_SET */
	unsigned int flag_shft;		/* only for MFC_CTRL_TYPE_SET */
};

struct s5p_mfc_codec_ops {
	/* initialization routines */
	int (*alloc_ctx_buf) (struct s5p_mfc_ctx *ctx);
	int (*alloc_desc_buf) (struct s5p_mfc_ctx *ctx);
	int (*get_init_arg) (struct s5p_mfc_ctx *ctx, void *arg);
	int (*pre_seq_start) (struct s5p_mfc_ctx *ctx);
	int (*post_seq_start) (struct s5p_mfc_ctx *ctx);
	int (*set_init_arg) (struct s5p_mfc_ctx *ctx, void *arg);
	int (*set_codec_bufs) (struct s5p_mfc_ctx *ctx);
	int (*set_dpbs) (struct s5p_mfc_ctx *ctx);		/* decoder */
	/* execution routines */
	int (*get_exe_arg) (struct s5p_mfc_ctx *ctx, void *arg);
	int (*pre_frame_start) (struct s5p_mfc_ctx *ctx);
	int (*post_frame_start) (struct s5p_mfc_ctx *ctx);
	int (*multi_data_frame) (struct s5p_mfc_ctx *ctx);
	int (*set_exe_arg) (struct s5p_mfc_ctx *ctx, void *arg);
	/* configuration routines */
	int (*get_codec_cfg) (struct s5p_mfc_ctx *ctx, unsigned int type, int *value);
	int (*set_codec_cfg) (struct s5p_mfc_ctx *ctx, unsigned int type, int *value);
	/* controls per buffer */
	int (*init_ctx_ctrls) (struct s5p_mfc_ctx *ctx);
	int (*cleanup_ctx_ctrls) (struct s5p_mfc_ctx *ctx);
	int (*init_buf_ctrls) (struct s5p_mfc_ctx *ctx, enum s5p_mfc_ctrl_type type, unsigned int index);
	int (*cleanup_buf_ctrls) (struct s5p_mfc_ctx *ctx, struct list_head *head);
	int (*to_buf_ctrls) (struct s5p_mfc_ctx *ctx, struct list_head *head);
	int (*to_ctx_ctrls) (struct s5p_mfc_ctx *ctx, struct list_head *head);
	int (*set_buf_ctrls_val) (struct s5p_mfc_ctx *ctx, struct list_head *head);
	int (*get_buf_ctrls_val) (struct s5p_mfc_ctx *ctx, struct list_head *head);
	int (*recover_buf_ctrls_val) (struct s5p_mfc_ctx *ctx, struct list_head *head);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

#define call_cop(c, op, args...)				\
	(((c)->c_ops->op) ?					\
		((c)->c_ops->op(args)) : 0)

<<<<<<< HEAD
<<<<<<< HEAD
/**
 * struct s5p_mfc_ctx - This struct contains the instance context
 *
 * @dev:		pointer to the s5p_mfc_dev of the device
 * @fh:			struct v4l2_fh
 * @num:		number of the context that this structure describes
 * @int_cond:		variable used by the waitqueue
 * @int_type:		type of the last interrupt
 * @int_err:		error number received from MFC hw in the interrupt
 * @queue:		waitqueue that can be used to wait for this context to
 *			finish
 * @src_fmt:		source pixelformat information
 * @dst_fmt:		destination pixelformat information
 * @vq_src:		vb2 queue for source buffers
 * @vq_dst:		vb2 queue for destination buffers
 * @src_queue:		driver internal queue for source buffers
 * @dst_queue:		driver internal queue for destination buffers
 * @src_queue_cnt:	number of buffers queued on the source internal queue
 * @dst_queue_cnt:	number of buffers queued on the dest internal queue
 * @type:		type of the instance - decoder or encoder
 * @state:		state of the context
 * @inst_no:		number of hw instance associated with the context
 * @img_width:		width of the image that is decoded or encoded
 * @img_height:		height of the image that is decoded or encoded
 * @buf_width:		width of the buffer for processed image
 * @buf_height:		height of the buffer for processed image
 * @luma_size:		size of a luma plane
 * @chroma_size:	size of a chroma plane
 * @mv_size:		size of a motion vectors buffer
 * @consumed_stream:	number of bytes that have been used so far from the
 *			decoding buffer
 * @dpb_flush_flag:	flag used to indicate that a DPB buffers are being
 *			flushed
 * @bank1_buf:		handle to memory allocated for temporary buffers from
 *			memory bank 1
 * @bank1_phys:		address of the temporary buffers from memory bank 1
 * @bank1_size:		size of the memory allocated for temporary buffers from
 *			memory bank 1
 * @bank2_buf:		handle to memory allocated for temporary buffers from
 *			memory bank 2
 * @bank2_phys:		address of the temporary buffers from memory bank 2
 * @bank2_size:		size of the memory allocated for temporary buffers from
 *			memory bank 2
 * @capture_state:	state of the capture buffers queue
 * @output_state:	state of the output buffers queue
 * @src_bufs:		information on allocated source buffers
 * @dst_bufs:		information on allocated destination buffers
 * @sequence:		counter for the sequence number for v4l2
 * @dec_dst_flag:	flags for buffers queued in the hardware
 * @dec_src_buf_size:	size of the buffer for source buffers in decoding
 * @codec_mode:		number of codec mode used by MFC hw
 * @slice_interface:	slice interface flag
 * @loop_filter_mpeg4:	loop filter for MPEG4 flag
 * @display_delay:	value of the display delay for H264
 * @display_delay_enable:	display delay for H264 enable flag
 * @after_packed_pb:	flag used to track buffer when stream is in
 *			Packed PB format
 * @dpb_count:		count of the DPB buffers required by MFC hw
 * @total_dpb_count:	count of DPB buffers with additional buffers
 *			requested by the application
 * @ctx_buf:		handle to the memory associated with this context
 * @ctx_phys:		address of the memory associated with this context
 * @ctx_size:		size of the memory associated with this context
 * @desc_buf:		description buffer for decoding handle
 * @desc_phys:		description buffer for decoding address
 * @shm_alloc:		handle for the shared memory buffer
 * @shm:		virtual address for the shared memory buffer
 * @shm_ofs:		address offset for shared memory
 * @enc_params:		encoding parameters for MFC
 * @enc_dst_buf_size:	size of the buffers for encoder output
 * @frame_type:		used to force the type of the next encoded frame
 * @ref_queue:		list of the reference buffers for encoding
 * @ref_queue_cnt:	number of the buffers in the reference list
 * @c_ops:		ops for encoding
 * @ctrls:		array of controls, used when adding controls to the
 *			v4l2 control framework
 * @ctrl_handler:	handler for v4l2 framework
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct s5p_mfc_dec {
	int total_dpb_count;

	struct list_head dpb_queue;
	unsigned int dpb_queue_cnt;

	size_t src_buf_size;

	int loop_filter_mpeg4;
	int display_delay;
	int is_packedpb;
	int slice_enable;
	int mv_count;

	int crc_enable;
	int crc_luma0;
	int crc_chroma0;
	int crc_luma1;
	int crc_chroma1;

	struct s5p_mfc_extra_buf dsc;
	unsigned long consumed;
	unsigned long dpb_status;
	unsigned int dpb_flush;

	enum v4l2_memory dst_memtype;
	int sei_parse;

	/* For 6.x */
	int remained;
};

struct s5p_mfc_enc {
	struct s5p_mfc_enc_params params;

	size_t dst_buf_size;

	int frame_count;
	enum v4l2_mpeg_mfc51_video_frame_type frame_type;
	enum v4l2_mpeg_mfc51_video_force_frame_type force_frame_type;

	struct list_head ref_queue;
	unsigned int ref_queue_cnt;

	/* For 6.x */
	size_t luma_dpb_size;
	size_t chroma_dpb_size;
	size_t me_buffer_size;
	size_t tmv_buffer_size;

	unsigned int slice_mode;
	union {
		unsigned int mb;
		unsigned int bits;
	} slice_size;
};

/**
 * struct s5p_mfc_ctx - This struct contains the instance context
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */
struct s5p_mfc_ctx {
	struct s5p_mfc_dev *dev;
	struct v4l2_fh fh;
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int num;

	int int_cond;
	int int_type;
	unsigned int int_err;
	wait_queue_head_t queue;

	struct s5p_mfc_fmt *src_fmt;
	struct s5p_mfc_fmt *dst_fmt;

	struct vb2_queue vq_src;
	struct vb2_queue vq_dst;

	struct list_head src_queue;
	struct list_head dst_queue;

	unsigned int src_queue_cnt;
	unsigned int dst_queue_cnt;

	enum s5p_mfc_inst_type type;
	enum s5p_mfc_inst_state state;
	int inst_no;

<<<<<<< HEAD
<<<<<<< HEAD
	/* Image parameters */
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int img_width;
	int img_height;
	int buf_width;
	int buf_height;
<<<<<<< HEAD
<<<<<<< HEAD
=======
	int dpb_count;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	int dpb_count;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	int luma_size;
	int chroma_size;
	int mv_size;

<<<<<<< HEAD
<<<<<<< HEAD
	unsigned long consumed_stream;

	unsigned int dpb_flush_flag;

	/* Buffers */
	void *bank1_buf;
	size_t bank1_phys;
	size_t bank1_size;

	void *bank2_buf;
	size_t bank2_phys;
	size_t bank2_size;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Buffers */
	void *port_a_buf;
	size_t port_a_phys;
	size_t port_a_size;

	void *port_b_buf;
	size_t port_b_phys;
	size_t port_b_size;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	enum s5p_mfc_queue_state capture_state;
	enum s5p_mfc_queue_state output_state;

<<<<<<< HEAD
<<<<<<< HEAD
	struct s5p_mfc_buf src_bufs[MFC_MAX_BUFFERS];
	int src_bufs_cnt;
	struct s5p_mfc_buf dst_bufs[MFC_MAX_BUFFERS];
	int dst_bufs_cnt;

	unsigned int sequence;
	unsigned long dec_dst_flag;
	size_t dec_src_buf_size;

	/* Control values */
	int codec_mode;
	int slice_interface;
	int loop_filter_mpeg4;
	int display_delay;
	int display_delay_enable;
	int after_packed_pb;

	int dpb_count;
	int total_dpb_count;

	/* Buffers */
	void *ctx_buf;
	size_t ctx_phys;
	size_t ctx_ofs;
	size_t ctx_size;

	void *desc_buf;
	size_t desc_phys;


	void *shm_alloc;
	void *shm;
	size_t shm_ofs;

	struct s5p_mfc_enc_params enc_params;

	size_t enc_dst_buf_size;

	enum v4l2_mpeg_mfc51_video_force_frame_type force_frame_type;

	struct list_head ref_queue;
	unsigned int ref_queue_cnt;

	struct s5p_mfc_codec_ops *c_ops;

	struct v4l2_ctrl *ctrls[MFC_MAX_CTRLS];
	struct v4l2_ctrl_handler ctrl_handler;
};

/*
 * struct s5p_mfc_fmt -	structure used to store information about pixelformats
 *			used by the MFC
 */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct list_head ctrls;

	struct list_head src_ctrls[MFC_MAX_BUFFERS];
	struct list_head dst_ctrls[MFC_MAX_BUFFERS];

	int src_ctrls_flag[MFC_MAX_BUFFERS];
	int dst_ctrls_flag[MFC_MAX_BUFFERS];

	unsigned int sequence;

	/* Control values */
	int codec_mode;
	__u32 pix_format;
	int cacheable;

	/* Extra Buffers */
	unsigned int ctx_buf_size;
	struct s5p_mfc_extra_buf ctx;
	struct s5p_mfc_extra_buf shm;

	struct s5p_mfc_dec *dec_priv;
	struct s5p_mfc_enc *enc_priv;

	struct s5p_mfc_codec_ops *c_ops;

	/* For 6.x */
	size_t scratch_buf_size;

	/* for DRM */
	int is_drm;
};

#define fh_to_mfc_ctx(x)	\
	container_of(x, struct s5p_mfc_ctx, fh)

#define MFC_FMT_DEC	0
#define MFC_FMT_ENC	1
#define MFC_FMT_RAW	2

#define HAS_PORTNUM(dev)	(dev ? (dev->variant ? \
				(dev->variant->port_num ? 1 : 0) : 0 ) : 0 )
#define IS_TWOPORT(dev)		(dev->variant->port_num == 2 ? 1 : 0)
#define IS_MFCV6(dev)		(dev->variant->version >= 0x60 ? 1 : 0)

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct s5p_mfc_fmt {
	char *name;
	u32 fourcc;
	u32 codec_mode;
<<<<<<< HEAD
<<<<<<< HEAD
	enum s5p_mfc_fmt_type type;
	u32 num_planes;
};

/**
 * struct mfc_control -	structure used to store information about MFC controls
 *			it is used to initialize the control framework.
 */
struct mfc_control {
	__u32			id;
	enum v4l2_ctrl_type	type;
	__u8			name[32];  /* Whatever */
	__s32			minimum;   /* Note signedness */
	__s32			maximum;
	__s32			step;
	__u32			menu_skip_mask;
	__s32			default_value;
	__u32			flags;
	__u32			reserved[2];
	__u8			is_volatile;
};


#define fh_to_ctx(__fh) container_of(__fh, struct s5p_mfc_ctx, fh)
#define ctrl_to_ctx(__ctrl) \
	container_of((__ctrl)->handler, struct s5p_mfc_ctx, ctrl_handler)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	u32 type;
	u32 num_planes;
};

#if defined(CONFIG_S5P_MFC_V5)
#include "regs-mfc-v5.h"
#include "s5p_mfc_opr_v5.h"
#include "s5p_mfc_shm.h"
#elif defined(CONFIG_S5P_MFC_V6)
#include "regs-mfc-v6.h"
#include "s5p_mfc_opr_v6.h"
#endif
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* S5P_MFC_COMMON_H_ */
