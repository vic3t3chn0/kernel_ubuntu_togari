/*
<<<<<<< HEAD
<<<<<<< HEAD
 * Header for M-5MOLS 8M Pixel camera sensor with ISP
=======
 * Header for M5MOLS 8M Pixel camera sensor with ISP
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Header for M5MOLS 8M Pixel camera sensor with ISP
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright (C) 2011 Samsung Electronics Co., Ltd.
 * Author: HeungJun Kim <riverful.kim@samsung.com>
 *
 * Copyright (C) 2009 Samsung Electronics Co., Ltd.
 * Author: Dongsoo Nathaniel Kim <dongsoo45.kim@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef M5MOLS_H
#define M5MOLS_H

#include <media/v4l2-subdev.h>
#include "m5mols_reg.h"

<<<<<<< HEAD
<<<<<<< HEAD
extern int m5mols_debug;

#define to_m5mols(__sd)	container_of(__sd, struct m5mols_info, sd)

#define to_sd(__ctrl) \
	(&container_of(__ctrl->handler, struct m5mols_info, handle)->sd)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define M5MO_JPEG_MAXSIZE	0x3A0000
#define M5MO_THUMB_MAXSIZE	0xFC00
#define M5MO_POST_MAXSIZE	0xBB800
#define M5MO_JPEG_MEMSIZE	M5MO_JPEG_MAXSIZE + M5MO_THUMB_MAXSIZE + M5MO_POST_MAXSIZE

#define v4l2msg(fmt, arg...)	do {				\
	v4l2_dbg(1, m5mols_debug, &info->sd, fmt, ## arg);	\
} while (0)

extern int m5mols_debug;

enum m5mols_mode {
	MODE_SYSINIT,
	MODE_PARMSET,
	MODE_MONITOR,
	MODE_CAPTURE,
	MODE_UNKNOWN,
};
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

enum m5mols_restype {
	M5MOLS_RESTYPE_MONITOR,
	M5MOLS_RESTYPE_CAPTURE,
	M5MOLS_RESTYPE_MAX,
};

<<<<<<< HEAD
<<<<<<< HEAD
/**
 * struct m5mols_resolution - structure for the resolution
 * @type: resolution type according to the pixel code
 * @width: width of the resolution
 * @height: height of the resolution
 * @reg: resolution preset register value
 */
struct m5mols_resolution {
	u8 reg;
	enum m5mols_restype type;
	u16 width;
	u16 height;
};

/**
 * struct m5mols_exif - structure for the EXIF information of M-5MOLS
 * @exposure_time: exposure time register value
 * @shutter_speed: speed of the shutter register value
 * @aperture: aperture register value
 * @exposure_bias: it calls also EV bias
 * @iso_speed: ISO register value
 * @flash: status register value of the flash
 * @sdr: status register value of the Subject Distance Range
 * @qval: not written exact meaning in document
 */
struct m5mols_exif {
	u32 exposure_time;
	u32 shutter_speed;
	u32 aperture;
	u32 brightness;
	u32 exposure_bias;
	u16 iso_speed;
	u16 flash;
	u16 sdr;
	u16 qval;
};

/**
 * struct m5mols_capture - Structure for the capture capability
 * @exif: EXIF information
 * @main: size in bytes of the main image
 * @thumb: size in bytes of the thumb image, if it was accompanied
 * @total: total size in bytes of the produced image
 */
struct m5mols_capture {
	struct m5mols_exif exif;
	u32 main;
	u32 thumb;
	u32 total;
};

/**
 * struct m5mols_scenemode - structure for the scenemode capability
 * @metering: metering light register value
 * @ev_bias: EV bias register value
 * @wb_mode: mode which means the WhiteBalance is Auto or Manual
 * @wb_preset: whitebalance preset register value in the Manual mode
 * @chroma_en: register value whether the Chroma capability is enabled or not
 * @chroma_lvl: chroma's level register value
 * @edge_en: register value Whether the Edge capability is enabled or not
 * @edge_lvl: edge's level register value
 * @af_range: Auto Focus's range
 * @fd_mode: Face Detection mode
 * @mcc: Multi-axis Color Conversion which means emotion color
 * @light: status of the Light
 * @flash: status of the Flash
 * @tone: Tone color which means Contrast
 * @iso: ISO register value
 * @capt_mode: Mode of the Image Stabilization while the camera capturing
 * @wdr: Wide Dynamic Range register value
 *
 * The each value according to each scenemode is recommended in the documents.
 */
struct m5mols_scenemode {
	u8 metering;
	u8 ev_bias;
	u8 wb_mode;
	u8 wb_preset;
	u8 chroma_en;
	u8 chroma_lvl;
	u8 edge_en;
	u8 edge_lvl;
	u8 af_range;
	u8 fd_mode;
	u8 mcc;
	u8 light;
	u8 flash;
	u8 tone;
	u8 iso;
	u8 capt_mode;
	u8 wdr;
};

/**
 * struct m5mols_version - firmware version information
 * @customer:	customer information
 * @project:	version of project information according to customer
 * @fw:		firmware revision
 * @hw:		hardware revision
 * @param:	version of the parameter
 * @awb:	Auto WhiteBalance algorithm version
 * @str:	information about manufacturer and packaging vendor
 * @af:		Auto Focus version
 *
 * The register offset starts the customer version at 0x0, and it ends
 * the awb version at 0x09. The customer, project information occupies 1 bytes
 * each. And also the fw, hw, param, awb each requires 2 bytes. The str is
 * unique string associated with firmware's version. It includes information
 * about manufacturer and the vendor of the sensor's packaging. The least
 * significant 2 bytes of the string indicate packaging manufacturer.
 */
#define VERSION_STRING_SIZE	22
struct m5mols_version {
	u8	customer;
	u8	project;
	u16	fw;
	u16	hw;
	u16	param;
	u16	awb;
	u8	str[VERSION_STRING_SIZE];
	u8	af;
};

/**
 * struct m5mols_info - M-5MOLS driver data structure
 * @pdata: platform data
 * @sd: v4l-subdev instance
 * @pad: media pad
 * @ffmt: current fmt according to resolution type
 * @res_type: current resolution type
 * @irq_waitq: waitqueue for the capture
 * @flags: state variable for the interrupt handler
 * @handle: control handler
 * @autoexposure: Auto Exposure control
 * @exposure: Exposure control
 * @autowb: Auto White Balance control
 * @colorfx: Color effect control
 * @saturation:	Saturation control
 * @zoom: Zoom control
 * @ver: information of the version
 * @cap: the capture mode attributes
 * @power: current sensor's power status
 * @isp_ready: 1 when the ISP controller has completed booting
 * @ctrl_sync: 1 when the control handler state is restored in H/W
 * @lock_ae: true means the Auto Exposure is locked
 * @lock_awb: true means the Aut WhiteBalance is locked
 * @resolution:	register value for current resolution
 * @mode: register value for current operation mode
 * @set_power: optional power callback to the board code
 */
struct m5mols_info {
	const struct m5mols_platform_data *pdata;
	struct v4l2_subdev sd;
	struct media_pad pad;
	struct v4l2_mbus_framefmt ffmt[M5MOLS_RESTYPE_MAX];
	int res_type;

	wait_queue_head_t irq_waitq;
	atomic_t irq_done;

	struct v4l2_ctrl_handler handle;

	/* Autoexposure/exposure control cluster */
	struct v4l2_ctrl *autoexposure;
	struct v4l2_ctrl *exposure;

	struct v4l2_ctrl *autowb;
	struct v4l2_ctrl *colorfx;
	struct v4l2_ctrl *saturation;
	struct v4l2_ctrl *zoom;

	struct m5mols_version ver;
	struct m5mols_capture cap;

	unsigned int isp_ready:1;
	unsigned int power:1;
	unsigned int ctrl_sync:1;

	bool lock_ae;
	bool lock_awb;
	u8 resolution;
	u8 mode;

	int (*set_power)(struct device *dev, int on);
};

#define is_available_af(__info)	(__info->ver.af)
#define is_code(__code, __type) (__code == m5mols_default_ffmt[__type].code)
#define is_manufacturer(__info, __manufacturer)	\
				(__info->ver.str[0] == __manufacturer[0] && \
				 __info->ver.str[1] == __manufacturer[1])
/*
 * I2C operation of the M-5MOLS
 *
 * The I2C read operation of the M-5MOLS requires 2 messages. The first
 * message sends the information about the command, command category, and total
 * message size. The second message is used to retrieve the data specifed in
 * the first message
 *
 *   1st message                                2nd message
 *   +-------+---+----------+-----+-------+     +------+------+------+------+
 *   | size1 | R | category | cmd | size2 |     | d[0] | d[1] | d[2] | d[3] |
 *   +-------+---+----------+-----+-------+     +------+------+------+------+
 *   - size1: message data size(5 in this case)
 *   - size2: desired buffer size of the 2nd message
 *   - d[0..3]: according to size2
 *
 * The I2C write operation needs just one message. The message includes
 * category, command, total size, and desired data.
 *
 *   1st message
 *   +-------+---+----------+-----+------+------+------+------+
 *   | size1 | W | category | cmd | d[0] | d[1] | d[2] | d[3] |
 *   +-------+---+----------+-----+------+------+------+------+
 *   - d[0..3]: according to size1
 */
int m5mols_read_u8(struct v4l2_subdev *sd, u32 reg_comb, u8 *val);
int m5mols_read_u16(struct v4l2_subdev *sd, u32 reg_comb, u16 *val);
int m5mols_read_u32(struct v4l2_subdev *sd, u32 reg_comb, u32 *val);
int m5mols_write(struct v4l2_subdev *sd, u32 reg_comb, u32 val);

int m5mols_busy_wait(struct v4l2_subdev *sd, u32 reg, u32 value, u32 mask,
		     int timeout);

/* Mask value for busy waiting until M-5MOLS I2C interface is initialized */
#define M5MOLS_I2C_RDY_WAIT_FL		(1 << 16)
/* ISP state transition timeout, in ms */
#define M5MOLS_MODE_CHANGE_TIMEOUT	200
#define M5MOLS_BUSY_WAIT_DEF_TIMEOUT	250

/*
 * Mode operation of the M-5MOLS
 *
 * Changing the mode of the M-5MOLS is needed right executing order.
 * There are three modes(PARAMETER, MONITOR, CAPTURE) which can be changed
 * by user. There are various categories associated with each mode.
 *
 * +============================================================+
 * | mode	| category					|
 * +============================================================+
 * | FLASH	| FLASH(only after Stand-by or Power-on)	|
 * | SYSTEM	| SYSTEM(only after sensor arm-booting)		|
 * | PARAMETER	| PARAMETER					|
 * | MONITOR	| MONITOR(preview), Auto Focus, Face Detection	|
 * | CAPTURE	| Single CAPTURE, Preview(recording)		|
 * +============================================================+
 *
 * The available executing order between each modes are as follows:
 *   PARAMETER <---> MONITOR <---> CAPTURE
 */
int m5mols_mode(struct m5mols_info *info, u8 mode);

int m5mols_enable_interrupt(struct v4l2_subdev *sd, u8 reg);
int m5mols_wait_interrupt(struct v4l2_subdev *sd, u8 condition, u32 timeout);
int m5mols_restore_controls(struct m5mols_info *info);
int m5mols_start_capture(struct m5mols_info *info);
int m5mols_do_scenemode(struct m5mols_info *info, u8 mode);
int m5mols_lock_3a(struct m5mols_info *info, bool lock);
int m5mols_set_ctrl(struct v4l2_ctrl *ctrl);

/* The firmware function */
int m5mols_update_fw(struct v4l2_subdev *sd,
		     int (*set_power)(struct m5mols_info *, bool));

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
enum m5mols_status {
	STATUS_SYSINIT,
	STATUS_PARMSET,
	STATUS_MONITOR,
	STATUS_AUTO_FOCUS,
	STATUS_FACE_DETECTION,
	STATUS_DUAL_CAPTURE,
	STATUS_SINGLE_CAPTURE,
	STATUS_PREVIEW,
	STATUS_UNKNOWN,
};

enum m5mols_intterrupt_bit {
	INT_BIT_MODE,
	INT_BIT_AF,
	INT_BIT_ZOOM,
	INT_BIT_CAPTURE,
	INT_BIT_FRAME_SYNC,
	INT_BIT_FD,
	INT_BIT_LENS_INIT,
	INT_BIT_SOUND,
};

enum m5mols_i2c_size {
	I2C_8BIT	= 1,
	I2C_16BIT	= 2,
	I2C_32BIT	= 4,
	I2C_MAX		= 4,
};

enum m5mols_fps {
	M5MOLS_FPS_AUTO	= 0,
	M5MOLS_FPS_10	= 10,
	M5MOLS_FPS_12	= 12,
	M5MOLS_FPS_15	= 15,
	M5MOLS_FPS_20	= 20,
	M5MOLS_FPS_21	= 21,
	M5MOLS_FPS_22	= 22,
	M5MOLS_FPS_23	= 23,
	M5MOLS_FPS_24	= 24,
	M5MOLS_FPS_30	= 30,
	M5MOLS_FPS_MAX	= M5MOLS_FPS_30,
};

enum m5mols_res_type {
	M5MOLS_RES_MON,
	/* It's not supported below yet. */
	M5MOLS_RES_CAPTURE,
	M5MOLS_RES_MAX,
};

struct m5mols_resolution {
	u8			value;
	enum m5mols_res_type	type;
	u16			width;
	u16			height;
};

struct m5mols_format {
	enum v4l2_mbus_pixelcode code;
	enum v4l2_colorspace colorspace;
};

struct m5mols_control {
	u32	id;
	s32	min;
	s32	max;
	u32	step;
	s32	def;
};

struct m5mols_exif {
	u32	exposure_time;
	u32	shutter_speed;
	u32	aperture;
	u32	brightness;
	u32	exposure_bias;
	u16	iso_speed;
	u16	flash;
	u16	sdr;		/* subject(object) distance range */
	u16	qval;		/* This is not written precisely in datasheet. */
};

struct m5mols_capture {
	struct m5mols_exif		exif;
	u32				main;
	u32				thumb;
	u32				total;
};

struct m5mols_version {
	u8	ctm_code;	/* customer code */
	u8	pj_code;	/* project code */
	u16	fw;		/* firmware version */
	u16	hw;		/* hardware version */
	u16	parm;		/* parameter version */
	u16	awb;		/* AWB version */
};

struct m5mols_info {
	struct v4l2_subdev		sd;
	struct media_pad pad;
	int res_type;
	u8 resolution;
	struct v4l2_mbus_framefmt	fmt[M5MOLS_RES_MAX];
	struct v4l2_fract		tpf;

	struct v4l2_ctrl_handler	handle;
	struct {
		/* support only AE of the Monitor Mode in this version */
		struct v4l2_ctrl	*autoexposure;
		struct v4l2_ctrl	*exposure;
		bool			is_ae_lock;
	};
	struct v4l2_ctrl		*autofocus;
	bool				is_focus;
	struct v4l2_ctrl		*autowb;
	bool				is_awb_lock;
	struct v4l2_ctrl		*colorfx;
	struct v4l2_ctrl		*saturation;
	struct v4l2_ctrl		*zoom;
	struct v4l2_ctrl		*jpeg_size;
	struct v4l2_ctrl		*encoded_size;

	enum m5mols_mode		mode;
	enum m5mols_mode		mode_backup;
	enum m5mols_status		status;
	enum v4l2_mbus_pixelcode	code;

	struct m5mols_capture		cap;
	wait_queue_head_t		cap_wait;
	bool				captured;

	const struct m5mols_platform_data	*pdata;
	struct m5mols_version		ver;
	struct work_struct		work;
	bool				power;

	/* for additional power if needed. */
	int (*set_power)(struct device *dev, int on);
};

/* control functions */
int m5mols_set_ctrl(struct v4l2_ctrl *ctrl);

/* I2C functions - referenced by below I2C helper functions */
int m5mols_read_reg(struct v4l2_subdev *sd, enum m5mols_i2c_size size,
		u8 category, u8 cmd, u32 *val);
int m5mols_write_reg(struct v4l2_subdev *sd, enum m5mols_i2c_size size,
		u8 category, u8 cmd, u32 val);
int m5mols_check_busy(struct v4l2_subdev *sd,
		u8 category, u8 cmd, u32 value);
int m5mols_set_mode(struct v4l2_subdev *sd, enum m5mols_mode mode);
enum m5mols_status m5mols_get_status(struct v4l2_subdev *sd);

/*
 * helper functions
 */
static inline struct m5mols_info *to_m5mols(struct v4l2_subdev *sd)
{
	return container_of(sd, struct m5mols_info, sd);
}

static inline struct v4l2_subdev *to_sd(struct v4l2_ctrl *ctrl)
{
	return &container_of(ctrl->handler, struct m5mols_info, handle)->sd;
}

static inline bool is_streaming(struct v4l2_subdev *sd)
{
	struct m5mols_info *info = to_m5mols(sd);
	return (info->mode == MODE_MONITOR) || (info->mode == MODE_CAPTURE);
}

static inline bool is_stoped(struct v4l2_subdev *sd)
{
	struct m5mols_info *info = to_m5mols(sd);
	return (info->mode != MODE_MONITOR) && (info->mode != MODE_CAPTURE);
}

static inline bool is_powerup(struct v4l2_subdev *sd)
{
	struct m5mols_info *info = to_m5mols(sd);
	return info->power;
}

static inline int m5mols_set_mode_backup(struct v4l2_subdev *sd,
		enum m5mols_mode mode)
{
	struct m5mols_info *info = to_m5mols(sd);

	info->mode_backup = info->mode;
	return m5mols_set_mode(sd, mode);
}

static inline int m5mols_set_mode_restore(struct v4l2_subdev *sd)
{
	struct m5mols_info *info = to_m5mols(sd);
	int ret;

	ret = m5mols_set_mode(sd, info->mode_backup);
	if (!ret)
		info->mode = info->mode_backup;
	return ret;
}

static inline int __must_check i2c_w8_system(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_8BIT, CAT_SYSTEM, cmd, val);
}

static inline int __must_check i2c_w8_param(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_8BIT, CAT_PARAM, cmd, val);
}

static inline int __must_check i2c_w8_mon(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_8BIT, CAT_MON, cmd, val);
}

static inline int __must_check i2c_w8_ae(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_8BIT, CAT_AE, cmd, val);
}

static inline int __must_check i2c_w16_ae(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_16BIT, CAT_AE, cmd, val);
}

static inline int __must_check i2c_w8_wb(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_8BIT, CAT_WB, cmd, val);
}

static inline int __must_check i2c_w8_lens(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_8BIT, CAT_LENS, cmd, val);
}

static inline int __must_check i2c_w8_capt_parm(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_8BIT, CAT_CAPTURE_PARAMETER, cmd, val);
}

static inline int __must_check i2c_w8_capt_ctrl(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_8BIT, CAT_CAPTURE_CONTROL, cmd, val);
}

static inline int __must_check i2c_w8_flash(struct v4l2_subdev *sd,
		u8 cmd, u32 val)
{
	return m5mols_write_reg(sd, I2C_8BIT, CAT_FLASH, cmd, val);
}

static inline int __must_check i2c_r8_system(struct v4l2_subdev *sd,
		u8 cmd, u32 *val)
{
	return m5mols_read_reg(sd, I2C_8BIT, CAT_SYSTEM, cmd, val);
}

static inline int __must_check i2c_r8_param(struct v4l2_subdev *sd,
		u8 cmd, u32 *val)
{
	return m5mols_read_reg(sd, I2C_8BIT, CAT_PARAM, cmd, val);
}

static inline int __must_check i2c_r8_mon(struct v4l2_subdev *sd,
		u8 cmd, u32 *val)
{
	return m5mols_read_reg(sd, I2C_8BIT, CAT_MON, cmd, val);
}

static inline int __must_check i2c_r8_ae(struct v4l2_subdev *sd,
		u8 cmd, u32 *val)
{
	return m5mols_read_reg(sd, I2C_8BIT, CAT_AE, cmd, val);
}

static inline int __must_check i2c_r16_ae(struct v4l2_subdev *sd,
		u8 cmd, u32 *val)
{
	return m5mols_read_reg(sd, I2C_16BIT, CAT_AE, cmd, val);
}

static inline int __must_check i2c_r8_lens(struct v4l2_subdev *sd,
		u8 cmd, u32 *val)
{
	return m5mols_read_reg(sd, I2C_8BIT, CAT_LENS, cmd, val);
}

static inline int __must_check i2c_r32_capt_ctrl(struct v4l2_subdev *sd,
		u8 cmd, u32 *val)
{
	return m5mols_read_reg(sd, I2C_32BIT, CAT_CAPTURE_CONTROL, cmd, val);
}

static inline int __must_check i2c_r16_exif(struct v4l2_subdev *sd,
		u8 cmd, u32 *val)
{
	return m5mols_read_reg(sd, I2C_16BIT, CAT_EXIF, cmd, val);
}

static inline int __must_check i2c_r32_exif(struct v4l2_subdev *sd,
		u8 cmd, u32 *val)
{
	return m5mols_read_reg(sd, I2C_32BIT, CAT_EXIF, cmd, val);
}

static int m5mols_set_ae_lock(struct m5mols_info *info, bool lock)
{
	struct v4l2_subdev *sd = &info->sd;

	info->is_ae_lock = lock;

	return i2c_w8_ae(sd, CAT3_AE_LOCK, !!lock);
}

static int m5mols_set_awb_lock(struct m5mols_info *info, bool lock)
{
	struct v4l2_subdev *sd = &info->sd;

	info->is_awb_lock = lock;

	return i2c_w8_wb(sd, CAT6_AWB_LOCK, !!lock);
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif	/* M5MOLS_H */
