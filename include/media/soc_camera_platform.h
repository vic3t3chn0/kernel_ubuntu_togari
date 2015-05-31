/*
 * Generic Platform Camera Driver Header
 *
 * Copyright (C) 2008 Magnus Damm
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __SOC_CAMERA_H__
#define __SOC_CAMERA_H__

#include <linux/videodev2.h>
#include <media/soc_camera.h>
<<<<<<< HEAD
#include <media/v4l2-mediabus.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

struct device;

struct soc_camera_platform_info {
	const char *format_name;
	unsigned long format_depth;
	struct v4l2_mbus_framefmt format;
<<<<<<< HEAD
	unsigned long mbus_param;
	enum v4l2_mbus_type mbus_type;
	struct soc_camera_device *icd;
=======
	unsigned long bus_param;
	struct device *dev;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	int (*set_capture)(struct soc_camera_platform_info *info, int enable);
};

static inline void soc_camera_platform_release(struct platform_device **pdev)
{
	*pdev = NULL;
}

<<<<<<< HEAD
static inline int soc_camera_platform_add(struct soc_camera_device *icd,
=======
static inline int soc_camera_platform_add(const struct soc_camera_link *icl,
					  struct device *dev,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
					  struct platform_device **pdev,
					  struct soc_camera_link *plink,
					  void (*release)(struct device *dev),
					  int id)
{
	struct soc_camera_platform_info *info = plink->priv;
	int ret;

<<<<<<< HEAD
	if (icd->link != plink)
=======
	if (icl != plink)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		return -ENODEV;

	if (*pdev)
		return -EBUSY;

	*pdev = platform_device_alloc("soc_camera_platform", id);
	if (!*pdev)
		return -ENOMEM;

<<<<<<< HEAD
	info->icd = icd;
=======
	info->dev = dev;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	(*pdev)->dev.platform_data = info;
	(*pdev)->dev.release = release;

	ret = platform_device_add(*pdev);
	if (ret < 0) {
		platform_device_put(*pdev);
		*pdev = NULL;
<<<<<<< HEAD
		info->icd = NULL;
=======
		info->dev = NULL;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
	}

	return ret;
}

<<<<<<< HEAD
static inline void soc_camera_platform_del(const struct soc_camera_device *icd,
					   struct platform_device *pdev,
					   const struct soc_camera_link *plink)
{
	if (icd->link != plink || !pdev)
=======
static inline void soc_camera_platform_del(const struct soc_camera_link *icl,
					   struct platform_device *pdev,
					   const struct soc_camera_link *plink)
{
	if (icl != plink || !pdev)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
		return;

	platform_device_unregister(pdev);
}

#endif /* __SOC_CAMERA_H__ */
