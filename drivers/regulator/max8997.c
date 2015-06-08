/*
<<<<<<< HEAD
<<<<<<< HEAD
 * max8997.c - Regulator driver for the Maxim 8997/8966
 *
 * Copyright (C) 2011 Samsung Electronics
 * MyungJoo Ham <myungjoo.ham@smasung.com>
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * max8997.c - Voltage regulator driver for the Maxim 8997
 *
 *  Copyright (C) 2009-2010 Samsung Electronics
 *
 *  based on max8998.c
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
<<<<<<< HEAD
<<<<<<< HEAD
 *
 * This driver is based on max8998.c
 */

#include <linux/bug.h>
#include <linux/delay.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/mfd/max8997.h>
#include <linux/mfd/max8997-private.h>

struct max8997_data {
	struct device *dev;
	struct max8997_dev *iodev;
	int num_regulators;
	struct regulator_dev **rdev;
	int ramp_delay; /* in mV/us */

	bool buck1_gpiodvs;
	bool buck2_gpiodvs;
	bool buck5_gpiodvs;
	u8 buck1_vol[8];
	u8 buck2_vol[8];
	u8 buck5_vol[8];
	int buck125_gpios[3];
	int buck125_gpioindex;
	bool ignore_gpiodvs_side_effect;

	u8 saved_states[MAX8997_REG_MAX];
};

static inline void max8997_set_gpio(struct max8997_data *max8997)
{
	int set3 = (max8997->buck125_gpioindex) & 0x1;
	int set2 = ((max8997->buck125_gpioindex) >> 1) & 0x1;
	int set1 = ((max8997->buck125_gpioindex) >> 2) & 0x1;

	gpio_set_value(max8997->buck125_gpios[0], set1);
	gpio_set_value(max8997->buck125_gpios[1], set2);
	gpio_set_value(max8997->buck125_gpios[2], set3);
}

struct voltage_map_desc {
	int min;
	int max;
	int step;
	unsigned int n_bits;
};

/* Voltage maps in mV */
static const struct voltage_map_desc ldo_voltage_map_desc = {
	.min = 800,	.max = 3950,	.step = 50,	.n_bits = 6,
}; /* LDO1 ~ 18, 21 all */

static const struct voltage_map_desc buck1245_voltage_map_desc = {
	.min = 650,	.max = 2225,	.step = 25,	.n_bits = 6,
}; /* Buck1, 2, 4, 5 */

static const struct voltage_map_desc buck37_voltage_map_desc = {
	.min = 750,	.max = 3900,	.step = 50,	.n_bits = 6,
}; /* Buck3, 7 */

/* current map in mA */
static const struct voltage_map_desc charger_current_map_desc = {
	.min = 200,	.max = 950,	.step = 50,	.n_bits = 4,
};

static const struct voltage_map_desc topoff_current_map_desc = {
	.min = 50,	.max = 200,	.step = 10,	.n_bits = 4,
};

static const struct voltage_map_desc *reg_voltage_map[] = {
	[MAX8997_LDO1] = &ldo_voltage_map_desc,
	[MAX8997_LDO2] = &ldo_voltage_map_desc,
	[MAX8997_LDO3] = &ldo_voltage_map_desc,
	[MAX8997_LDO4] = &ldo_voltage_map_desc,
	[MAX8997_LDO5] = &ldo_voltage_map_desc,
	[MAX8997_LDO6] = &ldo_voltage_map_desc,
	[MAX8997_LDO7] = &ldo_voltage_map_desc,
	[MAX8997_LDO8] = &ldo_voltage_map_desc,
	[MAX8997_LDO9] = &ldo_voltage_map_desc,
	[MAX8997_LDO10] = &ldo_voltage_map_desc,
	[MAX8997_LDO11] = &ldo_voltage_map_desc,
	[MAX8997_LDO12] = &ldo_voltage_map_desc,
	[MAX8997_LDO13] = &ldo_voltage_map_desc,
	[MAX8997_LDO14] = &ldo_voltage_map_desc,
	[MAX8997_LDO15] = &ldo_voltage_map_desc,
	[MAX8997_LDO16] = &ldo_voltage_map_desc,
	[MAX8997_LDO17] = &ldo_voltage_map_desc,
	[MAX8997_LDO18] = &ldo_voltage_map_desc,
	[MAX8997_LDO21] = &ldo_voltage_map_desc,
	[MAX8997_BUCK1] = &buck1245_voltage_map_desc,
	[MAX8997_BUCK2] = &buck1245_voltage_map_desc,
	[MAX8997_BUCK3] = &buck37_voltage_map_desc,
	[MAX8997_BUCK4] = &buck1245_voltage_map_desc,
	[MAX8997_BUCK5] = &buck1245_voltage_map_desc,
	[MAX8997_BUCK6] = NULL,
	[MAX8997_BUCK7] = &buck37_voltage_map_desc,
	[MAX8997_EN32KHZ_AP] = NULL,
	[MAX8997_EN32KHZ_CP] = NULL,
	[MAX8997_ENVICHG] = NULL,
	[MAX8997_ESAFEOUT1] = NULL,
	[MAX8997_ESAFEOUT2] = NULL,
	[MAX8997_CHARGER_CV] = NULL,
	[MAX8997_CHARGER] = &charger_current_map_desc,
	[MAX8997_CHARGER_TOPOFF] = &topoff_current_map_desc,
};

static int max8997_list_voltage_safeout(struct regulator_dev *rdev,
		unsigned int selector)
{
	int rid = rdev_get_id(rdev);

	if (rid == MAX8997_ESAFEOUT1 || rid == MAX8997_ESAFEOUT2) {
		switch (selector) {
		case 0:
			return 4850000;
		case 1:
			return 4900000;
		case 2:
			return 4950000;
		case 3:
			return 3300000;
		default:
			return -EINVAL;
		}
	}

	return -EINVAL;
}

static int max8997_list_voltage_charger_cv(struct regulator_dev *rdev,
		unsigned int selector)
{
	int rid = rdev_get_id(rdev);

	if (rid != MAX8997_CHARGER_CV)
		goto err;

	switch (selector) {
	case 0x00:
		return 4200000;
	case 0x01 ... 0x0E:
		return 4000000 + 20000 * (selector - 0x01);
	case 0x0F:
		return 4350000;
	default:
		return -EINVAL;
	}
err:
	return -EINVAL;
}

static int max8997_list_voltage(struct regulator_dev *rdev,
		unsigned int selector)
{
	const struct voltage_map_desc *desc;
	int rid = rdev_get_id(rdev);
	int val;

	if (rid >= ARRAY_SIZE(reg_voltage_map) ||
			rid < 0)
		return -EINVAL;

	desc = reg_voltage_map[rid];
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/gpio.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/regulator/driver.h>
#include <linux/mfd/max8997.h>
#include <linux/mfd/max8997-private.h>

#include <mach/sec_debug.h>

struct max8997_data {
	struct device		*dev;
	struct max8997_dev	*iodev;
	int			num_regulators;
	struct regulator_dev	**rdev;
	bool			buck1_gpiodvs;
	int			buck_set1;
	int			buck_set2;
	int			buck_set3;
	u8                      buck1_vol[8]; /* voltages for selection */
	unsigned int		buck1_idx; /* index to last changed voltage */
					   /* value in a set */
	bool			buck_ramp_en;
	int			buck_ramp_delay;
	struct max8997_buck1_dvs_funcs funcs;
	struct mutex		dvs_lock;
};

struct vol_cur_map_desc {
	int min;
	int max;
	int step;
};

/* Voltage maps */
static const struct vol_cur_map_desc ldos_vol_cur_map_desc = {
	.min = 800,	.step = 50,	.max = 3950,
};
static const struct vol_cur_map_desc buck1245_vol_cur_map_desc = {
	.min = 650,	.step = 25,	.max = 2225,
};
static const struct vol_cur_map_desc buck37_vol_cur_map_desc = {
	.min = 750,	.step = 50,	.max = 3900,
};

/* flash currents just aren't matching up right! */
static const struct vol_cur_map_desc flash_vol_cur_map_desc = {
	.min = 23440,	.step = 23440,	.max = 750080,
};
static const struct vol_cur_map_desc movie_vol_cur_map_desc = {
	.min = 15625,	.step = 15625,	.max = 250000,
};
#ifdef MAX8997_SUPPORT_TORCH
static const struct vol_cur_map_desc torch_vol_cur_map_desc = {
	.min = 15625,	.step = 15625,	.max = 250000,
};
#endif /* MAX8997_SUPPORT_TORCH */

static const struct vol_cur_map_desc *ldo_vol_cur_map[] = {
	NULL,
	&ldos_vol_cur_map_desc,		/* LDO1 */
	&ldos_vol_cur_map_desc,		/* LDO2 */
	&ldos_vol_cur_map_desc,		/* LDO3 */
	&ldos_vol_cur_map_desc,		/* LDO4 */
	&ldos_vol_cur_map_desc,		/* LDO5 */
	&ldos_vol_cur_map_desc,		/* LDO6 */
	&ldos_vol_cur_map_desc,		/* LDO7 */
	&ldos_vol_cur_map_desc,		/* LDO8 */
	&ldos_vol_cur_map_desc,		/* LDO9 */
	&ldos_vol_cur_map_desc,		/* LDO10 */
	&ldos_vol_cur_map_desc,		/* LDO11 */
	&ldos_vol_cur_map_desc,		/* LDO12 */
	&ldos_vol_cur_map_desc,		/* LDO13 */
	&ldos_vol_cur_map_desc,		/* LDO14 */
	&ldos_vol_cur_map_desc,		/* LDO15 */
	&ldos_vol_cur_map_desc,		/* LDO16 */
	&ldos_vol_cur_map_desc,		/* LDO17 */
	&ldos_vol_cur_map_desc,		/* LDO18 */
	&ldos_vol_cur_map_desc,		/* LDO21 */
	&buck1245_vol_cur_map_desc,	/* BUCK1 */
	&buck1245_vol_cur_map_desc,	/* BUCK2 */
	&buck37_vol_cur_map_desc,	/* BUCK3 */
	&buck1245_vol_cur_map_desc,	/* BUCK4 */
	&buck1245_vol_cur_map_desc,	/* BUCK5 */
	NULL,				/* BUCK6 */
	&buck37_vol_cur_map_desc,	/* BUCK7 */
	NULL,				/* EN32KH_AP */
	NULL,				/* EN32KH_CP */
	NULL,				/* ENVICHG */
	NULL,				/* ESAFEOUT1 */
	NULL,				/* ESAFEOUT2 */
	&flash_vol_cur_map_desc,	/* FLASH_EN */
	&movie_vol_cur_map_desc,	/* MOVIE_EN */
#ifdef MAX8997_SUPPORT_TORCH
	&torch_vol_cur_map_desc,	/* TORCH */
#endif /* MAX8997_SUPPORT_TORCH */
};

static inline int max8997_get_ldo(struct regulator_dev *rdev)
{
	return rdev_get_id(rdev);
}

static int max8997_list_voltage(struct regulator_dev *rdev,
				unsigned int selector)
{
	const struct vol_cur_map_desc *desc;
	int ldo = max8997_get_ldo(rdev);
	int val;

	if (ldo >= ARRAY_SIZE(ldo_vol_cur_map))
		return -EINVAL;

	desc = ldo_vol_cur_map[ldo];
	if (desc == NULL)
		return -EINVAL;

	val = desc->min + desc->step * selector;
	if (val > desc->max)
		return -EINVAL;

	return val * 1000;
}

static int max8997_list_current(struct regulator_dev *rdev,
				unsigned int selector)
{
	const struct vol_cur_map_desc *desc;
	int co = max8997_get_ldo(rdev);
	int val;

	if (co >= ARRAY_SIZE(ldo_vol_cur_map))
		return -EINVAL;

	desc = ldo_vol_cur_map[co];
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (desc == NULL)
		return -EINVAL;

	val = desc->min + desc->step * selector;
	if (val > desc->max)
		return -EINVAL;

<<<<<<< HEAD
<<<<<<< HEAD
	return val * 1000;
}

static int max8997_get_enable_register(struct regulator_dev *rdev,
		int *reg, int *mask, int *pattern)
{
	int rid = rdev_get_id(rdev);

	switch (rid) {
	case MAX8997_LDO1 ... MAX8997_LDO21:
		*reg = MAX8997_REG_LDO1CTRL + (rid - MAX8997_LDO1);
		*mask = 0xC0;
		*pattern = 0xC0;
		break;
	case MAX8997_BUCK1:
		*reg = MAX8997_REG_BUCK1CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		break;
	case MAX8997_BUCK2:
		*reg = MAX8997_REG_BUCK2CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		break;
	case MAX8997_BUCK3:
		*reg = MAX8997_REG_BUCK3CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		break;
	case MAX8997_BUCK4:
		*reg = MAX8997_REG_BUCK4CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		break;
	case MAX8997_BUCK5:
		*reg = MAX8997_REG_BUCK5CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		break;
	case MAX8997_BUCK6:
		*reg = MAX8997_REG_BUCK6CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		break;
	case MAX8997_BUCK7:
		*reg = MAX8997_REG_BUCK7CTRL;
		*mask = 0x01;
		*pattern = 0x01;
		break;
	case MAX8997_EN32KHZ_AP ... MAX8997_EN32KHZ_CP:
		*reg = MAX8997_REG_MAINCON1;
		*mask = 0x01 << (rid - MAX8997_EN32KHZ_AP);
		*pattern = 0x01 << (rid - MAX8997_EN32KHZ_AP);
		break;
	case MAX8997_ENVICHG:
		*reg = MAX8997_REG_MBCCTRL1;
		*mask = 0x80;
		*pattern = 0x80;
		break;
	case MAX8997_ESAFEOUT1 ... MAX8997_ESAFEOUT2:
		*reg = MAX8997_REG_SAFEOUTCTRL;
		*mask = 0x40 << (rid - MAX8997_ESAFEOUT1);
		*pattern = 0x40 << (rid - MAX8997_ESAFEOUT1);
		break;
	case MAX8997_CHARGER:
		*reg = MAX8997_REG_MBCCTRL2;
		*mask = 0x40;
		*pattern = 0x40;
		break;
	default:
		/* Not controllable or not exists */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return val;
}

static int max8997_get_enable_register(struct regulator_dev *rdev,
					int *reg, int *shift)
{
	int ldo = max8997_get_ldo(rdev);

	switch (ldo) {
	case MAX8997_LDO1 ... MAX8997_LDO21:
		*reg = MAX8997_REG_LDO1CTRL + (ldo - MAX8997_LDO1);
		*shift = 6;
		break;
	case MAX8997_BUCK1:
		*reg = MAX8997_REG_BUCK1CTRL;
		*shift = 0;
		break;
	case MAX8997_BUCK2:
		*reg = MAX8997_REG_BUCK2CTRL;
		*shift = 0;
		break;
	case MAX8997_BUCK3:
		*reg = MAX8997_REG_BUCK3CTRL;
		*shift = 0;
		break;
	case MAX8997_BUCK4:
		*reg = MAX8997_REG_BUCK4CTRL;
		*shift = 0;
		break;
	case MAX8997_BUCK5:
		*reg = MAX8997_REG_BUCK5CTRL;
		*shift = 0;
		break;
	case MAX8997_BUCK6:
		*reg = MAX8997_REG_BUCK6CTRL1;
		*shift = 0;
		break;
	case MAX8997_BUCK7:
		*reg = MAX8997_REG_BUCK7CTRL;
		*shift = 0;
		break;
	case MAX8997_EN32KHZ_AP ... MAX8997_EN32KHZ_CP:
		*reg = MAX8997_REG_CONTROL1;
		*shift = 0 + (ldo - MAX8997_EN32KHZ_AP);
		break;
	case MAX8997_ENVICHG:
		*reg = MAX8997_REG_MBCCTRL1;
		*shift = 7;
		break;
	case MAX8997_ESAFEOUT1 ... MAX8997_ESAFEOUT2:
		*reg = MAX8997_REG_SAFEOUTCTRL;
		*shift = 6 + (ldo - MAX8997_ESAFEOUT1);
		break;
	default:
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}

	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
static int max8997_reg_is_enabled(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret, reg, mask, pattern;
	u8 val;

	ret = max8997_get_enable_register(rdev, &reg, &mask, &pattern);
	if (ret == -EINVAL)
		return 1; /* "not controllable" */
	else if (ret)
		return ret;

	ret = max8997_read_reg(i2c, reg, &val);
	if (ret)
		return ret;

	return (val & mask) == pattern;
}

static int max8997_reg_enable(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret, reg, mask, pattern;

	ret = max8997_get_enable_register(rdev, &reg, &mask, &pattern);
	if (ret)
		return ret;

	return max8997_update_reg(i2c, reg, pattern, mask);
}

static int max8997_reg_disable(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret, reg, mask, pattern;

	ret = max8997_get_enable_register(rdev, &reg, &mask, &pattern);
	if (ret)
		return ret;

	return max8997_update_reg(i2c, reg, ~pattern, mask);
}

static int max8997_get_voltage_register(struct regulator_dev *rdev,
		int *_reg, int *_shift, int *_mask)
{
	int rid = rdev_get_id(rdev);
	int reg, shift = 0, mask = 0x3f;

	switch (rid) {
	case MAX8997_LDO1 ... MAX8997_LDO21:
		reg = MAX8997_REG_LDO1CTRL + (rid - MAX8997_LDO1);
		break;
	case MAX8997_BUCK1:
		reg = MAX8997_REG_BUCK1DVS1;
		break;
	case MAX8997_BUCK2:
		reg = MAX8997_REG_BUCK2DVS1;
		break;
	case MAX8997_BUCK3:
		reg = MAX8997_REG_BUCK3DVS;
		break;
	case MAX8997_BUCK4:
		reg = MAX8997_REG_BUCK4DVS;
		break;
	case MAX8997_BUCK5:
		reg = MAX8997_REG_BUCK5DVS1;
		break;
	case MAX8997_BUCK7:
		reg = MAX8997_REG_BUCK7DVS;
		break;
	case MAX8997_ESAFEOUT1 ...  MAX8997_ESAFEOUT2:
		reg = MAX8997_REG_SAFEOUTCTRL;
		shift = (rid == MAX8997_ESAFEOUT2) ? 2 : 0;
		mask = 0x3;
		break;
	case MAX8997_CHARGER_CV:
		reg = MAX8997_REG_MBCCTRL3;
		shift = 0;
		mask = 0xf;
		break;
	case MAX8997_CHARGER:
		reg = MAX8997_REG_MBCCTRL4;
		shift = 0;
		mask = 0xf;
		break;
	case MAX8997_CHARGER_TOPOFF:
		reg = MAX8997_REG_MBCCTRL5;
		shift = 0;
		mask = 0xf;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int max8997_get_enable_mask(struct regulator_dev *rdev)
{
	int ret = 0;
	int ldo = max8997_get_ldo(rdev);

	switch (ldo) {
	case MAX8997_LDO1 ... MAX8997_LDO21:
		ret = 3;
		break;
	case MAX8997_BUCK1 ... MAX8997_ESAFEOUT2:
		ret = 1;
		break;
	default:
		break;
	}

	return ret;
}

static int max8997_get_disable_val(struct regulator_dev *rdev)
{
	int ret = 0;
	int ldo = max8997_get_ldo(rdev);

	switch (ldo) {
	case MAX8997_LDO1:
	case MAX8997_LDO10:
	case MAX8997_LDO21:
		ret = 1;
		break;
	default:
		ret = 0;
		break;
	}

	return ret;
}

static int max8997_ldo_is_enabled(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret, reg, shift = 8;
	u8 val, mask;

	ret = max8997_get_enable_register(rdev, &reg, &shift);
	if (ret < 0)
		return ret;

	ret = max8997_read_reg(i2c, reg, &val);
	if (ret < 0)
		return ret;

	mask = max8997_get_enable_mask(rdev);

	return val & (mask << shift);
}

static int max8997_ldo_enable(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int reg, shift = 8, ret;
	u8 mask;

	ret = max8997_get_enable_register(rdev, &reg, &shift);
	if (ret < 0)
		return ret;

	mask = max8997_get_enable_mask(rdev);

	return max8997_update_reg(i2c, reg, mask<<shift, mask<<shift);
}

static int max8997_ldo_disable(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int reg, shift = 8, ret, val;
	u8 mask;

	ret = max8997_get_enable_register(rdev, &reg, &shift);
	if (ret < 0)
		return ret;

	mask = max8997_get_enable_mask(rdev);
	val = max8997_get_disable_val(rdev);

	return max8997_update_reg(i2c, reg, val<<shift, mask<<shift);
}

static int max8997_ldo_suspend_enable(struct regulator_dev *rdev)
{
	if (rdev->use_count > 0)
		return max8997_ldo_enable(rdev);
	else
		return max8997_ldo_disable(rdev);
}

static int max8997_get_voltage_register(struct regulator_dev *rdev,
				int *_reg, int *_shift, int *_mask)
{
	int ldo = max8997_get_ldo(rdev);
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	int reg, shift = 0, mask = 0xff;

	switch (ldo) {
	case MAX8997_LDO1 ... MAX8997_LDO21:
		reg = MAX8997_REG_LDO1CTRL + (ldo - MAX8997_LDO1);
		mask = 0x3f;
		break;
	case MAX8997_BUCK1:
		reg = MAX8997_REG_BUCK1DVSTV1 + max8997->buck1_idx;
		break;
	case MAX8997_BUCK2:
		reg = MAX8997_REG_BUCK2DVSTV1 + 1;
		break;
	case MAX8997_BUCK3:
		reg = MAX8997_REG_BUCK3DVSTV;
		break;
	case MAX8997_BUCK4:
		reg = MAX8997_REG_BUCK4DVSTV;
		break;
	case MAX8997_BUCK5:
		reg = MAX8997_REG_BUCK5DVSTV1 + 1;
		break;
	case MAX8997_BUCK7:
		reg = MAX8997_REG_BUCK7DVSTV;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		break;
	default:
		return -EINVAL;
	}

	*_reg = reg;
	*_shift = shift;
	*_mask = mask;

	return 0;
}

static int max8997_get_voltage(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
<<<<<<< HEAD
<<<<<<< HEAD
	int reg, shift, mask, ret;
	int rid = rdev_get_id(rdev);
	u8 val;

	ret = max8997_get_voltage_register(rdev, &reg, &shift, &mask);
	if (ret)
		return ret;

	if ((rid == MAX8997_BUCK1 && max8997->buck1_gpiodvs) ||
			(rid == MAX8997_BUCK2 && max8997->buck2_gpiodvs) ||
			(rid == MAX8997_BUCK5 && max8997->buck5_gpiodvs))
		reg += max8997->buck125_gpioindex;

	ret = max8997_read_reg(i2c, reg, &val);
	if (ret)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int reg, shift = 0, mask, ret;
	u8 val;

	ret = max8997_get_voltage_register(rdev, &reg, &shift, &mask);
	if (ret < 0)
		return ret;

	ret = max8997_read_reg(i2c, reg, &val);
	if (ret < 0)
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return ret;

	val >>= shift;
	val &= mask;

<<<<<<< HEAD
<<<<<<< HEAD
	if (rdev->desc && rdev->desc->ops && rdev->desc->ops->list_voltage)
		return rdev->desc->ops->list_voltage(rdev, val);

	/*
	 * max8997_list_voltage returns value for any rdev with voltage_map,
	 * which works for "CHARGER" and "CHARGER TOPOFF" that do not have
	 * list_voltage ops (they are current regulators).
	 */
	return max8997_list_voltage(rdev, val);
}

static inline int max8997_get_voltage_proper_val(
		const struct voltage_map_desc *desc,
		int min_vol, int max_vol)
{
	int i = 0;

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return max8997_list_voltage(rdev, val);
}

static int max8997_set_voltage_ldo(struct regulator_dev *rdev,
				int min_uV, int max_uV, unsigned *selector)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int min_vol = min_uV / 1000, max_vol = max_uV / 1000;
	const struct vol_cur_map_desc *desc;
	int ldo = max8997_get_ldo(rdev);
	int reg, shift = 0, mask, ret;
	int i = 0;

	if (ldo >= ARRAY_SIZE(ldo_vol_cur_map))
		return -EINVAL;

	desc = ldo_vol_cur_map[ldo];
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (desc == NULL)
		return -EINVAL;

	if (max_vol < desc->min || min_vol > desc->max)
		return -EINVAL;

<<<<<<< HEAD
<<<<<<< HEAD
	while (desc->min + desc->step * i < min_vol &&
			desc->min + desc->step * i < desc->max)
		i++;

	if (desc->min + desc->step * i > max_vol)
		return -EINVAL;

	if (i >= (1 << desc->n_bits))
		return -EINVAL;

	return i;
}

static int max8997_set_voltage_charger_cv(struct regulator_dev *rdev,
		int min_uV, int max_uV, unsigned *selector)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int rid = rdev_get_id(rdev);
	int lb, ub;
	int reg, shift = 0, mask, ret = 0;
	u8 val = 0x0;

	if (rid != MAX8997_CHARGER_CV)
		return -EINVAL;

	ret = max8997_get_voltage_register(rdev, &reg, &shift, &mask);
	if (ret)
		return ret;

	if (max_uV < 4000000 || min_uV > 4350000)
		return -EINVAL;

	if (min_uV <= 4000000) {
		if (max_uV >= 4000000)
			return -EINVAL;
		else
			val = 0x1;
	} else if (min_uV <= 4200000 && max_uV >= 4200000)
		val = 0x0;
	else {
		lb = (min_uV - 4000001) / 20000 + 2;
		ub = (max_uV - 4000000) / 20000 + 1;

		if (lb > ub)
			return -EINVAL;

		if (lb < 0xf)
			val = lb;
		else {
			if (ub >= 0xf)
				val = 0xf;
			else
				return -EINVAL;
		}
	}

	*selector = val;

	ret = max8997_update_reg(i2c, reg, val << shift, mask);

	return ret;
}

/*
 * For LDO1 ~ LDO21, BUCK1~5, BUCK7, CHARGER, CHARGER_TOPOFF
 * BUCK1, 2, and 5 are available if they are not controlled by gpio
 */
static int max8997_set_voltage_ldobuck(struct regulator_dev *rdev,
		int min_uV, int max_uV, unsigned *selector)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int min_vol = min_uV / 1000, max_vol = max_uV / 1000;
	const struct voltage_map_desc *desc;
	int rid = rdev_get_id(rdev);
	int reg, shift = 0, mask, ret;
	int i;
	u8 org;

	switch (rid) {
	case MAX8997_LDO1 ... MAX8997_LDO21:
		break;
	case MAX8997_BUCK1 ... MAX8997_BUCK5:
		break;
	case MAX8997_BUCK6:
		return -EINVAL;
	case MAX8997_BUCK7:
		break;
	case MAX8997_CHARGER:
		break;
	case MAX8997_CHARGER_TOPOFF:
		break;
	default:
		return -EINVAL;
	}

	desc = reg_voltage_map[rid];

	i = max8997_get_voltage_proper_val(desc, min_vol, max_vol);
	if (i < 0)
		return i;

	ret = max8997_get_voltage_register(rdev, &reg, &shift, &mask);
	if (ret)
		return ret;

	max8997_read_reg(i2c, reg, &org);
	org = (org & mask) >> shift;

	ret = max8997_update_reg(i2c, reg, i << shift, mask << shift);
	*selector = i;

	if (rid == MAX8997_BUCK1 || rid == MAX8997_BUCK2 ||
			rid == MAX8997_BUCK4 || rid == MAX8997_BUCK5) {
		/* If the voltage is increasing */
		if (org < i)
			udelay(DIV_ROUND_UP(desc->step * (i - org),
						max8997->ramp_delay));
	}

	return ret;
}

/*
 * Assess the damage on the voltage setting of BUCK1,2,5 by the change.
 *
 * When GPIO-DVS mode is used for multiple bucks, changing the voltage value
 * of one of the bucks may affect that of another buck, which is the side
 * effect of the change (set_voltage). This function examines the GPIO-DVS
 * configurations and checks whether such side-effect exists.
 */
static int max8997_assess_side_effect(struct regulator_dev *rdev,
		u8 new_val, int *best)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	int rid = rdev_get_id(rdev);
	u8 *buckx_val[3];
	bool buckx_gpiodvs[3];
	int side_effect[8];
	int min_side_effect = INT_MAX;
	int i;

	*best = -1;

	switch (rid) {
	case MAX8997_BUCK1:
		rid = 0;
		break;
	case MAX8997_BUCK2:
		rid = 1;
		break;
	case MAX8997_BUCK5:
		rid = 2;
		break;
	default:
		return -EINVAL;
	}

	buckx_val[0] = max8997->buck1_vol;
	buckx_val[1] = max8997->buck2_vol;
	buckx_val[2] = max8997->buck5_vol;
	buckx_gpiodvs[0] = max8997->buck1_gpiodvs;
	buckx_gpiodvs[1] = max8997->buck2_gpiodvs;
	buckx_gpiodvs[2] = max8997->buck5_gpiodvs;

	for (i = 0; i < 8; i++) {
		int others;

		if (new_val != (buckx_val[rid])[i]) {
			side_effect[i] = -1;
			continue;
		}

		side_effect[i] = 0;
		for (others = 0; others < 3; others++) {
			int diff;

			if (others == rid)
				continue;
			if (buckx_gpiodvs[others] == false)
				continue; /* Not affected */
			diff = (buckx_val[others])[i] -
				(buckx_val[others])[max8997->buck125_gpioindex];
			if (diff > 0)
				side_effect[i] += diff;
			else if (diff < 0)
				side_effect[i] -= diff;
		}
		if (side_effect[i] == 0) {
			*best = i;
			return 0; /* NO SIDE EFFECT! Use This! */
		}
		if (side_effect[i] < min_side_effect) {
			min_side_effect = side_effect[i];
			*best = i;
		}
	}

	if (*best == -1)
		return -EINVAL;

	return side_effect[*best];
}

/*
 * For Buck 1 ~ 5 and 7. If it is not controlled by GPIO, this calls
 * max8997_set_voltage_ldobuck to do the job.
 */
static int max8997_set_voltage_buck(struct regulator_dev *rdev,
		int min_uV, int max_uV, unsigned *selector)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	int rid = rdev_get_id(rdev);
	const struct voltage_map_desc *desc;
	int new_val, new_idx, damage, tmp_val, tmp_idx, tmp_dmg;
	bool gpio_dvs_mode = false;
	int min_vol = min_uV / 1000, max_vol = max_uV / 1000;

	if (rid < MAX8997_BUCK1 || rid > MAX8997_BUCK7)
		return -EINVAL;

	switch (rid) {
	case MAX8997_BUCK1:
		if (max8997->buck1_gpiodvs)
			gpio_dvs_mode = true;
		break;
	case MAX8997_BUCK2:
		if (max8997->buck2_gpiodvs)
			gpio_dvs_mode = true;
		break;
	case MAX8997_BUCK5:
		if (max8997->buck5_gpiodvs)
			gpio_dvs_mode = true;
		break;
	}

	if (!gpio_dvs_mode)
		return max8997_set_voltage_ldobuck(rdev, min_uV, max_uV,
						selector);

	desc = reg_voltage_map[rid];
	new_val = max8997_get_voltage_proper_val(desc, min_vol, max_vol);
	if (new_val < 0)
		return new_val;

	tmp_dmg = INT_MAX;
	tmp_idx = -1;
	tmp_val = -1;
	do {
		damage = max8997_assess_side_effect(rdev, new_val, &new_idx);
		if (damage == 0)
			goto out;

		if (tmp_dmg > damage) {
			tmp_idx = new_idx;
			tmp_val = new_val;
			tmp_dmg = damage;
		}

		new_val++;
	} while (desc->min + desc->step * new_val <= desc->max);

	new_idx = tmp_idx;
	new_val = tmp_val;

	if (max8997->ignore_gpiodvs_side_effect == false)
		return -EINVAL;

	dev_warn(&rdev->dev, "MAX8997 GPIO-DVS Side Effect Warning: GPIO SET:"
			" %d -> %d\n", max8997->buck125_gpioindex, tmp_idx);

out:
	if (new_idx < 0 || new_val < 0)
		return -EINVAL;

	max8997->buck125_gpioindex = new_idx;
	max8997_set_gpio(max8997);
	*selector = new_val;

	return 0;
}

static const int safeoutvolt[] = {
	3300000,
	4850000,
	4900000,
	4950000,
};

/* For SAFEOUT1 and SAFEOUT2 */
static int max8997_set_voltage_safeout(struct regulator_dev *rdev,
		int min_uV, int max_uV, unsigned *selector)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int rid = rdev_get_id(rdev);
	int reg, shift = 0, mask, ret;
	int i = 0;
	u8 val;

	if (rid != MAX8997_ESAFEOUT1 && rid != MAX8997_ESAFEOUT2)
		return -EINVAL;

	for (i = 0; i < ARRAY_SIZE(safeoutvolt); i++) {
		if (min_uV <= safeoutvolt[i] &&
				max_uV >= safeoutvolt[i])
			break;
	}

	if (i >= ARRAY_SIZE(safeoutvolt))
		return -EINVAL;

	if (i == 0)
		val = 0x3;
	else
		val = i - 1;

	ret = max8997_get_voltage_register(rdev, &reg, &shift, &mask);
	if (ret)
		return ret;

	ret = max8997_update_reg(i2c, reg, val << shift, mask << shift);
	*selector = val;

	return ret;
}

static int max8997_reg_enable_suspend(struct regulator_dev *rdev)
{
	return 0;
}

static int max8997_reg_disable_suspend(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret, reg, mask, pattern;
	int rid = rdev_get_id(rdev);

	ret = max8997_get_enable_register(rdev, &reg, &mask, &pattern);
	if (ret)
		return ret;

	max8997_read_reg(i2c, reg, &max8997->saved_states[rid]);

	if (rid == MAX8997_LDO1 ||
			rid == MAX8997_LDO10 ||
			rid == MAX8997_LDO21) {
		dev_dbg(&rdev->dev, "Conditional Power-Off for %s\n",
				rdev->desc->name);
		return max8997_update_reg(i2c, reg, 0x40, mask);
	}

	dev_dbg(&rdev->dev, "Full Power-Off for %s (%xh -> %xh)\n",
			rdev->desc->name, max8997->saved_states[rid] & mask,
			(~pattern) & mask);
	return max8997_update_reg(i2c, reg, ~pattern, mask);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	while (desc->min + desc->step*i < min_vol &&
	       desc->min + desc->step*i < desc->max)
		i++;

	if (desc->min + desc->step*i > max_vol)
		return -EINVAL;

	ret = max8997_get_voltage_register(rdev, &reg, &shift, &mask);
	if (ret < 0)
		return ret;

	ret = max8997_update_reg(i2c, reg, i<<shift, mask<<shift);
	*selector = i;

	return ret;
}

static inline void buck1_gpio_set(struct max8997_data *max8997, int v)
{
	static int prev_v = 0x1;

	int gpio1 = max8997->buck_set1;
	int gpio2 = max8997->buck_set2;
	int gpio3 = max8997->buck_set3;

	if (prev_v > v) {
		/* raise the volage */
		gpio_set_value(gpio3, (v >> 2) & 0x1);
		udelay(40);
		gpio_set_value(gpio2, (v >> 1) & 0x1);
		udelay(40);
		gpio_set_value(gpio1, v & 0x1);
	} else {
		gpio_set_value(gpio1, v & 0x1);
		udelay(40);
		gpio_set_value(gpio2, (v >> 1) & 0x1);
		udelay(40);
		gpio_set_value(gpio3, (v >> 2) & 0x1);
	}

	prev_v = v;
}

static int max8997_set_voltage_buck(struct regulator_dev *rdev,
				    int min_uV, int max_uV, unsigned *selector)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int i = 0, j, k;
	int min_vol = min_uV / 1000, max_vol = max_uV / 1000;
	const struct vol_cur_map_desc *desc;
	int buck = max8997_get_ldo(rdev);
	int reg, shift = 0, mask, ret;
	int difference = 0, previous_vol = 0, current_vol = 0;
	u8 data[7];

	mutex_lock(&max8997->dvs_lock);

	if (buck >= ARRAY_SIZE(ldo_vol_cur_map)) {
		ret = -EINVAL;
		goto out;
	}

	desc = ldo_vol_cur_map[buck];

	if (desc == NULL) {
		ret = -EINVAL;
		goto out;
	}

	if (max_vol < desc->min || min_vol > desc->max) {
		ret = -EINVAL;
		goto out;
	}

	while (desc->min + desc->step*i < min_vol &&
	       desc->min + desc->step*i < desc->max)
		i++;

	*selector = i;

	if (desc->min + desc->step*i > max_vol) {
		ret = -EINVAL;
		goto out;
	}

	ret = max8997_get_voltage_register(rdev, &reg, &shift, &mask);
	if (ret < 0)
		goto out;

	previous_vol = max8997_get_voltage(rdev);

	/* Check if voltage needs to be changed */
	/* if previous_voltage equal new voltage, return */
	if (previous_vol == max8997_list_voltage(rdev, i)) {
		dev_dbg(max8997->dev, "No voltage change, old:%d, new:%d\n",
			previous_vol, max8997_list_voltage(rdev, i));
		ret = 0;
		goto out;
	}

	switch (buck) {
	case MAX8997_BUCK1:
		sec_debug_aux_log(SEC_DEBUG_AUXLOG_CPU_BUS_CLOCK_CHANGE,
				"%s: BUCK1: min_vol=%d, max_vol=%d(%ps)",
				__func__, min_vol, max_vol,
				__builtin_return_address(0));

		if (!max8997->buck1_gpiodvs) {
			ret = max8997_write_reg(i2c, reg, i);
			break;
		}

		if (gpio_is_valid(max8997->buck_set1) &&
		    gpio_is_valid(max8997->buck_set2) &&
		    gpio_is_valid(max8997->buck_set3)) {
			/* check if requested voltage */
			/* value is already defined */
			for (j = 1; j < ARRAY_SIZE(max8997->buck1_vol); j++) {
				if (max8997->buck1_vol[j] == i) {
					max8997->buck1_idx = j;
					buck1_gpio_set(max8997, j);
					goto buck1_exit;
				}
			}

			/* no predefine regulator found */
			dev_warn(max8997->dev, "BUCK1 no predefined:%d,%d\n",
				min_vol, max_vol);
			max8997->buck1_idx = 7;
			max8997->buck1_vol[max8997->buck1_idx] = i;
			ret = max8997_get_voltage_register(rdev, &reg, &shift,
							   &mask);
			if (ret < 0)
				break;

			ret = max8997_write_reg(i2c, reg, i);
			if (ret < 0)
				break;

			buck1_gpio_set(max8997, max8997->buck1_idx);
buck1_exit:
			dev_dbg(max8997->dev, "%s: SET3:%d,SET2:%d,SET1:%d\n",
				__func__, gpio_get_value(max8997->buck_set3),
				gpio_get_value(max8997->buck_set2),
				gpio_get_value(max8997->buck_set1));
			break;
		} else
			ret = max8997_write_reg(i2c, reg, i);
		break;
	case MAX8997_BUCK2:
		sec_debug_aux_log(SEC_DEBUG_AUXLOG_CPU_BUS_CLOCK_CHANGE,
				"%s: BUCK2: min_vol=%d, max_vol=%d(%ps)",
				__func__, min_vol, max_vol,
				__builtin_return_address(0));
	case MAX8997_BUCK5:
		for (k = 0; k < 7; k++)
			data[k] = i;
		ret = max8997_bulk_write(i2c, reg, 7, data);
		break;
	case MAX8997_BUCK3:
	case MAX8997_BUCK4:
	case MAX8997_BUCK7:
		ret = max8997_write_reg(i2c, reg, i);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	if (ret < 0) {
		dev_err(max8997->dev, "Failed to write buck%d voltage"
			"register: %d\n", buck - MAX8997_BUCK1 + 1, ret);
		goto out;
	}

	if (!max8997->buck_ramp_en)
		goto out;

	current_vol = desc->min + desc->step*i;
	if (previous_vol/1000 < current_vol)
		difference = current_vol - previous_vol/1000;
	else
		difference = previous_vol/1000 - current_vol;

	udelay(difference / max8997->buck_ramp_delay);
out:
	mutex_unlock(&max8997->dvs_lock);
	return ret;
}

static int max8997_flash_is_enabled(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret;
	u8 val, mask;

	switch (max8997_get_ldo(rdev)) {
	case MAX8997_FLASH_CUR:
		mask = MAX8997_FLASH_EN_MASK;
		break;
#ifdef MAX8997_SUPPORT_TORCH
	case MAX8997_FLASH_TORCH:
#endif /* MAX8997_FLASH_TORCH */
	case MAX8997_MOVIE_CUR:
		mask = MAX8997_MOVIE_EN_MASK;
		break;
	default:
		return -EINVAL;
	}

	ret = max8997_read_reg(i2c, MAX8997_REG_LED_CNTL, &val);
	if (ret < 0)
		return ret;

	return val & mask;
}

static int max8997_flash_enable(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret;

	ret = max8997_update_reg(i2c, MAX8997_REG_BOOST_CNTL,
			1 << MAX8997_BOOST_EN_SHIFT, MAX8997_BOOST_EN_MASK);
	if (ret < 0)
		return ret;

	switch (max8997_get_ldo(rdev)) {
	case MAX8997_FLASH_CUR:
		ret = max8997_update_reg(i2c, MAX8997_REG_LED_CNTL,
			7 << MAX8997_FLASH_EN_SHIFT, MAX8997_FLASH_EN_MASK);
		break;
	case MAX8997_MOVIE_CUR:
		ret = max8997_update_reg(i2c, MAX8997_REG_LED_CNTL,
			7 << MAX8997_MOVIE_EN_SHIFT, MAX8997_MOVIE_EN_MASK);
		break;
#ifdef MAX8997_SUPPORT_TORCH
	case MAX8997_FLASH_TORCH:
		ret = max8997_update_reg(i2c, MAX8997_REG_LED_CNTL,
			3 << MAX8997_MOVIE_EN_SHIFT, MAX8997_MOVIE_EN_MASK);
		break;
#endif /* MAX8997_SUPPORT_TORCH */
	default:
		return -EINVAL;
	}

	return ret;
}

static int max8997_flash_disable(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret;

	ret = max8997_update_reg(i2c, MAX8997_REG_LED_CNTL,
			0 << MAX8997_FLASH_EN_SHIFT, MAX8997_FLASH_EN_MASK);
	if (ret < 0)
		return ret;

	switch (max8997_get_ldo(rdev)) {
	case MAX8997_FLASH_CUR:
		ret = max8997_update_reg(i2c, MAX8997_REG_LED_CNTL,
			0 << MAX8997_FLASH_EN_SHIFT, MAX8997_FLASH_EN_MASK);
		break;
#ifdef MAX8997_SUPPORT_TORCH
	case MAX8997_FLASH_TORCH:
#endif /* MAX8997_SUPPORT_TORCH */
	case MAX8997_MOVIE_CUR:
		ret = max8997_update_reg(i2c, MAX8997_REG_LED_CNTL,
			0 << MAX8997_MOVIE_EN_SHIFT, MAX8997_MOVIE_EN_MASK);
		break;
	default:
		return -EINVAL;
	}

	if (ret < 0)
		return ret;

	return max8997_update_reg(i2c, MAX8997_REG_BOOST_CNTL,
			0 << MAX8997_BOOST_EN_SHIFT, MAX8997_BOOST_EN_MASK);
}

static int max8997_flash_get_current(struct regulator_dev *rdev)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret;
	u8 val, shift = 0;

	switch (max8997_get_ldo(rdev)) {
	case MAX8997_FLASH_CUR:
		/* Assume that FLED1 and FLED2 have same current setting */
		ret = max8997_read_reg(i2c, MAX8997_REG_FLASH1_CUR, &val);
		shift = 3;
		break;
#ifdef MAX8997_SUPPORT_TORCH
	case MAX8997_FLASH_TORCH:
#endif /* MAX8997_SUPPORT_TORCH */
	case MAX8997_MOVIE_CUR:
		ret = max8997_read_reg(i2c, MAX8997_REG_MOVIE_CUR, &val);
		shift = 4;
		break;
	default:
		return -EINVAL;
	}

	if (ret < 0)
		return ret;

	val >>= shift;

	return max8997_list_current(rdev, val);
}

static int max8997_flash_set_current(struct regulator_dev *rdev,
				     int min_uA, int max_uA)
{
	struct max8997_data *max8997 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8997->iodev->i2c;
	int min_amp = min_uA, max_amp = max_uA;
	const struct vol_cur_map_desc *desc;
	int co = max8997_get_ldo(rdev);
	int ret;
	int i = 0;

	if (co >= ARRAY_SIZE(ldo_vol_cur_map))
		return -EINVAL;

	desc = ldo_vol_cur_map[co];
	if (desc == NULL)
		return -EINVAL;

	if (max_amp < desc->min || min_amp > desc->max)
		return -EINVAL;

	while (desc->min + desc->step*i < min_amp &&
	       desc->min + desc->step*i < desc->max)
		i++;

	if (desc->min + desc->step*i > max_amp)
		return -EINVAL;

	switch (co) {
	case MAX8997_FLASH_CUR:
		ret = max8997_write_reg(i2c, MAX8997_REG_FLASH1_CUR, i << 3);
		if (ret < 0)
			return ret;
		ret = max8997_write_reg(i2c, MAX8997_REG_FLASH2_CUR, i << 3);
		break;
	case MAX8997_MOVIE_CUR:
#if 0
		ret = max8997_write_reg(i2c, MAX8997_REG_MOVIE_CUR, i << 4);
#else
		/* Workaround: MOVIE_CUR setting was ignored because
		 * GSMB is always high.
		 */
		ret = max8997_update_reg(i2c, MAX8997_REG_GSMB_CUR, i << 2,
				0xf << 2);
#endif
		break;
#ifdef MAX8997_SUPPORT_TORCH
	case MAX8997_FLASH_TORCH:
		ret = max8997_write_reg(i2c, MAX8997_REG_MOVIE_CUR, i << 4);
		break;
#endif /* MAX8997_SUPPORT_TORCH */
	default:
		return -EINVAL;
	}

	return ret;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static struct regulator_ops max8997_ldo_ops = {
	.list_voltage		= max8997_list_voltage,
<<<<<<< HEAD
<<<<<<< HEAD
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.get_voltage		= max8997_get_voltage,
	.set_voltage		= max8997_set_voltage_ldobuck,
	.set_suspend_enable	= max8997_reg_enable_suspend,
	.set_suspend_disable	= max8997_reg_disable_suspend,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.is_enabled		= max8997_ldo_is_enabled,
	.enable			= max8997_ldo_enable,
	.disable		= max8997_ldo_disable,
	.get_voltage		= max8997_get_voltage,
	.set_voltage		= max8997_set_voltage_ldo,
	.set_suspend_enable	= max8997_ldo_suspend_enable,
	.set_suspend_disable	= max8997_ldo_disable,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static struct regulator_ops max8997_buck_ops = {
	.list_voltage		= max8997_list_voltage,
<<<<<<< HEAD
<<<<<<< HEAD
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.get_voltage		= max8997_get_voltage,
	.set_voltage		= max8997_set_voltage_buck,
	.set_suspend_enable	= max8997_reg_enable_suspend,
	.set_suspend_disable	= max8997_reg_disable_suspend,
};

static struct regulator_ops max8997_fixedvolt_ops = {
	.list_voltage		= max8997_list_voltage,
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.set_suspend_enable	= max8997_reg_enable_suspend,
	.set_suspend_disable	= max8997_reg_disable_suspend,
};

static struct regulator_ops max8997_safeout_ops = {
	.list_voltage		= max8997_list_voltage_safeout,
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.get_voltage		= max8997_get_voltage,
	.set_voltage		= max8997_set_voltage_safeout,
	.set_suspend_enable	= max8997_reg_enable_suspend,
	.set_suspend_disable	= max8997_reg_disable_suspend,
};

static struct regulator_ops max8997_fixedstate_ops = {
	.list_voltage		= max8997_list_voltage_charger_cv,
	.get_voltage		= max8997_get_voltage,
	.set_voltage		= max8997_set_voltage_charger_cv,
};

static int max8997_set_voltage_ldobuck_wrap(struct regulator_dev *rdev,
		int min_uV, int max_uV)
{
	unsigned dummy;

	return max8997_set_voltage_ldobuck(rdev, min_uV, max_uV, &dummy);
}


static struct regulator_ops max8997_charger_ops = {
	.is_enabled		= max8997_reg_is_enabled,
	.enable			= max8997_reg_enable,
	.disable		= max8997_reg_disable,
	.get_current_limit	= max8997_get_voltage,
	.set_current_limit	= max8997_set_voltage_ldobuck_wrap,
};

static struct regulator_ops max8997_charger_fixedstate_ops = {
	.is_enabled		= max8997_reg_is_enabled,
	.get_current_limit	= max8997_get_voltage,
	.set_current_limit	= max8997_set_voltage_ldobuck_wrap,
};

#define regulator_desc_ldo(num)		{	\
	.name		= "LDO"#num,		\
	.id		= MAX8997_LDO##num,	\
	.ops		= &max8997_ldo_ops,	\
	.type		= REGULATOR_VOLTAGE,	\
	.owner		= THIS_MODULE,		\
}
#define regulator_desc_buck(num)		{	\
	.name		= "BUCK"#num,		\
	.id		= MAX8997_BUCK##num,	\
	.ops		= &max8997_buck_ops,	\
	.type		= REGULATOR_VOLTAGE,	\
	.owner		= THIS_MODULE,		\
}

static struct regulator_desc regulators[] = {
	regulator_desc_ldo(1),
	regulator_desc_ldo(2),
	regulator_desc_ldo(3),
	regulator_desc_ldo(4),
	regulator_desc_ldo(5),
	regulator_desc_ldo(6),
	regulator_desc_ldo(7),
	regulator_desc_ldo(8),
	regulator_desc_ldo(9),
	regulator_desc_ldo(10),
	regulator_desc_ldo(11),
	regulator_desc_ldo(12),
	regulator_desc_ldo(13),
	regulator_desc_ldo(14),
	regulator_desc_ldo(15),
	regulator_desc_ldo(16),
	regulator_desc_ldo(17),
	regulator_desc_ldo(18),
	regulator_desc_ldo(21),
	regulator_desc_buck(1),
	regulator_desc_buck(2),
	regulator_desc_buck(3),
	regulator_desc_buck(4),
	regulator_desc_buck(5),
	{
		.name	= "BUCK6",
		.id	= MAX8997_BUCK6,
		.ops	= &max8997_fixedvolt_ops,
		.type	= REGULATOR_VOLTAGE,
		.owner	= THIS_MODULE,
	},
	regulator_desc_buck(7),
	{
		.name	= "EN32KHz_AP",
		.id	= MAX8997_EN32KHZ_AP,
		.ops	= &max8997_fixedvolt_ops,
		.type	= REGULATOR_VOLTAGE,
		.owner	= THIS_MODULE,
	}, {
		.name	= "EN32KHz_CP",
		.id	= MAX8997_EN32KHZ_CP,
		.ops	= &max8997_fixedvolt_ops,
		.type	= REGULATOR_VOLTAGE,
		.owner	= THIS_MODULE,
	}, {
		.name	= "ENVICHG",
		.id	= MAX8997_ENVICHG,
		.ops	= &max8997_fixedvolt_ops,
		.type	= REGULATOR_VOLTAGE,
		.owner	= THIS_MODULE,
	}, {
		.name	= "ESAFEOUT1",
		.id	= MAX8997_ESAFEOUT1,
		.ops	= &max8997_safeout_ops,
		.type	= REGULATOR_VOLTAGE,
		.owner	 = THIS_MODULE,
	}, {
		.name	= "ESAFEOUT2",
		.id	= MAX8997_ESAFEOUT2,
		.ops	= &max8997_safeout_ops,
		.type	= REGULATOR_VOLTAGE,
		.owner	 = THIS_MODULE,
	}, {
		.name	= "CHARGER_CV",
		.id	= MAX8997_CHARGER_CV,
		.ops	= &max8997_fixedstate_ops,
		.type	= REGULATOR_VOLTAGE,
		.owner	 = THIS_MODULE,
	}, {
		.name	= "CHARGER",
		.id	= MAX8997_CHARGER,
		.ops	= &max8997_charger_ops,
		.type	= REGULATOR_CURRENT,
		.owner	 = THIS_MODULE,
	}, {
		.name	= "CHARGER_TOPOFF",
		.id	= MAX8997_CHARGER_TOPOFF,
		.ops	= &max8997_charger_fixedstate_ops,
		.type	= REGULATOR_CURRENT,
		.owner	 = THIS_MODULE,
	},
};
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.is_enabled		= max8997_ldo_is_enabled,
	.enable			= max8997_ldo_enable,
	.disable		= max8997_ldo_disable,
	.get_voltage		= max8997_get_voltage,
	.set_voltage		= max8997_set_voltage_buck,
	.set_suspend_enable	= max8997_ldo_enable,
	.set_suspend_disable	= max8997_ldo_disable,
};

static struct regulator_ops max8997_flash_ops = {
	.is_enabled		= max8997_flash_is_enabled,
	.enable			= max8997_flash_enable,
	.disable		= max8997_flash_disable,
	.set_current_limit	= max8997_flash_set_current,
	.get_current_limit	= max8997_flash_get_current,
	.set_suspend_enable	= max8997_flash_enable,
	.set_suspend_disable	= max8997_flash_disable,
};

static struct regulator_ops max8997_others_ops = {
	.is_enabled		= max8997_ldo_is_enabled,
	.enable			= max8997_ldo_enable,
	.disable		= max8997_ldo_disable,
	.set_suspend_enable	= max8997_ldo_enable,
	.set_suspend_disable	= max8997_ldo_disable,
};

static struct regulator_desc regulators[] = {
	{
		.name		= "LDO1",
		.id		= MAX8997_LDO1,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO2",
		.id		= MAX8997_LDO2,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO3",
		.id		= MAX8997_LDO3,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO4",
		.id		= MAX8997_LDO4,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO5",
		.id		= MAX8997_LDO5,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO6",
		.id		= MAX8997_LDO6,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO7",
		.id		= MAX8997_LDO7,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO8",
		.id		= MAX8997_LDO8,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO9",
		.id		= MAX8997_LDO9,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO10",
		.id		= MAX8997_LDO10,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO11",
		.id		= MAX8997_LDO11,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO12",
		.id		= MAX8997_LDO12,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO13",
		.id		= MAX8997_LDO13,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO14",
		.id		= MAX8997_LDO14,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO15",
		.id		= MAX8997_LDO15,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO16",
		.id		= MAX8997_LDO16,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO17",
		.id		= MAX8997_LDO17,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO18",
		.id		= MAX8997_LDO18,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "LDO21",
		.id		= MAX8997_LDO21,
		.ops		= &max8997_ldo_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "BUCK1",
		.id		= MAX8997_BUCK1,
		.ops		= &max8997_buck_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "BUCK2",
		.id		= MAX8997_BUCK2,
		.ops		= &max8997_buck_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "BUCK3",
		.id		= MAX8997_BUCK3,
		.ops		= &max8997_buck_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "BUCK4",
		.id		= MAX8997_BUCK4,
		.ops		= &max8997_buck_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "BUCK5",
		.id		= MAX8997_BUCK5,
		.ops		= &max8997_buck_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "BUCK6",
		.id		= MAX8997_BUCK6,
		.ops		= &max8997_buck_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "BUCK7",
		.id		= MAX8997_BUCK7,
		.ops		= &max8997_buck_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "EN32KHz AP",
		.id		= MAX8997_EN32KHZ_AP,
		.ops		= &max8997_others_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "EN32KHz CP",
		.id		= MAX8997_EN32KHZ_CP,
		.ops		= &max8997_others_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "ENVICHG",
		.id		= MAX8997_ENVICHG,
		.ops		= &max8997_others_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "ESAFEOUT1",
		.id		= MAX8997_ESAFEOUT1,
		.ops		= &max8997_others_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "ESAFEOUT2",
		.id		= MAX8997_ESAFEOUT2,
		.ops		= &max8997_others_ops,
		.type		= REGULATOR_VOLTAGE,
		.owner		= THIS_MODULE,
	}, {
		.name		= "FLASH_CUR",
		.id		= MAX8997_FLASH_CUR,
		.ops		= &max8997_flash_ops,
		.type		= REGULATOR_CURRENT,
		.owner		= THIS_MODULE,
	}, {
		.name		= "MOVIE_CUR",
		.id		= MAX8997_MOVIE_CUR,
		.ops		= &max8997_flash_ops,
		.type		= REGULATOR_CURRENT,
		.owner		= THIS_MODULE,
#ifdef MAX8997_SUPPORT_TORCH
	}, {
		.name		= "FLASH_TORCH",
		.id		= MAX8997_FLASH_TORCH,
		.ops		= &max8997_flash_ops,
		.type		= REGULATOR_CURRENT,
		.owner		= THIS_MODULE,
#endif /* MAX8997_SUPPORT_TORCH */
	}
};

static int max8997_set_buck_max_voltage(struct max8997_data *max8997,
				int buck_no, unsigned int buck_max_vol)
{
	struct i2c_client *i2c;
	int i = 0, j;
	u8 reg, data[8];

	i2c = max8997->iodev->i2c;

	while (buck1245_vol_cur_map_desc.min + buck1245_vol_cur_map_desc.step*i
	       != (buck_max_vol / 1000)) {
		i++;
		if (i > 0x3f) {
			dev_err(max8997->dev, "%s: invalid voltage(%d,%d)\n",
					__func__, buck_no, buck_max_vol);
			return -EINVAL;
		}
	}

	dev_info(max8997->dev, "%s: buck%d: %d, i:%d\n", __func__, buck_no,
			buck_max_vol, i);

	switch (buck_no) {
	case 1:
		max8997->buck1_vol[0] = i;
		reg = MAX8997_REG_BUCK1DVSTV1;
		break;
	case 2:
		reg = MAX8997_REG_BUCK2DVSTV1;
		break;
	case 5:
		reg = MAX8997_REG_BUCK5DVSTV1;
		break;
	default:
		pr_err("%s: wrong BUCK number(%d)!\n", __func__, buck_no);
		return -EINVAL;
	}

	for (j = 0; j < 8; j++)
		data[j] = i;

	return max8997_bulk_write(i2c, reg, 8, data);
}

/* Set predefined value for BUCK1 registers */
static int max8997_set_buck1_voltages(struct max8997_data *max8997,
				unsigned int *buck1_voltages, int arr_size)
{
	struct i2c_client *i2c;
	int i, j, idx = 1, ret = 0;
	u8 reg;

	mutex_lock(&max8997->dvs_lock);

	if (arr_size > BUCK1_TABLE_SIZE) {
		dev_err(max8997->dev, "%s: too big voltage array!(%d)\n",
				__func__, arr_size);
		ret = -EINVAL;
		goto out;
	}

	i2c = max8997->iodev->i2c;

	for (i = 0; i < arr_size; i++) {
		if (buck1_voltages[i] == 0)
			continue;

		j = 0;
		while (buck1245_vol_cur_map_desc.min
				+ buck1245_vol_cur_map_desc.step*j
				!= (buck1_voltages[i] / 1000))
			j++;

		dev_info(max8997->dev, "%s: buck1_voltages[%d]=%d, "
				"buck1_vol[%d]=%d\n", __func__,
				i, buck1_voltages[i], idx, j);

		max8997->buck1_vol[idx] = j;
		reg = MAX8997_REG_BUCK1DVSTV1 + idx;
		ret = max8997_write_reg(i2c, reg, j);
		if (ret < 0) {
			dev_err(max8997->dev, "%s: fail to write reg(%d)!\n",
					__func__, ret);
			break;
		}
		idx++;
	}
out:
	mutex_unlock(&max8997->dvs_lock);
	return ret;
}

static void max8997_set_buckramp(struct max8997_data *max8997,
		struct max8997_platform_data *pdata)
{
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret;
	u8 val = 0;

	max8997->buck_ramp_en = pdata->buck_ramp_en;
	if (max8997->buck_ramp_en)
		val = (MAX8997_ENRAMPBUCK1 | MAX8997_ENRAMPBUCK2
			| MAX8997_ENRAMPBUCK4 | MAX8997_ENRAMPBUCK5);

	max8997->buck_ramp_delay = pdata->buck_ramp_delay;
	switch (max8997->buck_ramp_delay) {
	case 1 ... 12:
		val |= max8997->buck_ramp_delay - 1;
		break;
	case 16:
		val |= 0xc; /* 16.67mV/us */
		break;
	case 25:
		val |= 0xd;
		break;
	case 50:
		val |= 0xe;
		break;
	case 100:
		val |= 0xf;
		break;
	default:
		dev_warn(max8997->dev, "%s: invalid ramp delay, "
			"set ramp delay as 10mV/us\n", __func__);
		max8997->buck_ramp_delay = 10;
		val |= 0x9;
		break;
	}

	dev_info(max8997->dev, "RAMP REG(0x%x)\n", val);
	ret = max8997_write_reg(i2c, MAX8997_REG_BUCKRAMP, val);
	if (ret < 0)
		dev_err(max8997->dev, "failed to write RAMP REG(%d)\n", ret);
}

static int max8997_set_buck1_dvs_table(struct max8997_buck1_dvs_funcs *ptr,
				unsigned int *voltage_table, int arr_size)
{
	struct max8997_data *max8997
		= container_of(ptr, struct max8997_data, funcs);
	int ret;

	ret = max8997_set_buck1_voltages(max8997, voltage_table, arr_size);

	if (ret >= 0) {
		max8997->buck1_gpiodvs = true;
		dev_info(max8997->dev, "%s: enable BUCK1 GPIO DVS\n",
				__func__);

	}
	return ret;
}

static void max8997_set_mr_debouce_time(struct max8997_data *max8997,
					struct max8997_platform_data *pdata)
{
	struct i2c_client *i2c = max8997->iodev->i2c;
	int ret;
	u8 val = pdata->mr_debounce_time;

	if (val > 8) {
		dev_err(max8997->dev, "Invalid MR debounce time(%d)\n", val);
		return;
	}

	dev_info(max8997->dev, "manual reset debouce time: %d sec.\n", val);

	ret = max8997_write_reg(i2c, MAX8997_REG_CONTROL2, --val);
	if (ret < 0)
		dev_err(max8997->dev, "failed to write CONTROL2(%d)\n", ret);
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static __devinit int max8997_pmic_probe(struct platform_device *pdev)
{
	struct max8997_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	struct max8997_platform_data *pdata = dev_get_platdata(iodev->dev);
	struct regulator_dev **rdev;
	struct max8997_data *max8997;
	struct i2c_client *i2c;
<<<<<<< HEAD
<<<<<<< HEAD
	int i, ret, size;
	u8 max_buck1 = 0, max_buck2 = 0, max_buck5 = 0;

	if (!pdata) {
		dev_err(pdev->dev.parent, "No platform init data supplied.\n");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int i, size, ret = 0;

	if (!pdata) {
		dev_err(pdev->dev.parent, "No platform init data supplied\n");
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -ENODEV;
	}

	max8997 = kzalloc(sizeof(struct max8997_data), GFP_KERNEL);
	if (!max8997)
		return -ENOMEM;

	size = sizeof(struct regulator_dev *) * pdata->num_regulators;
	max8997->rdev = kzalloc(size, GFP_KERNEL);
	if (!max8997->rdev) {
<<<<<<< HEAD
<<<<<<< HEAD
		kfree(max8997);
		return -ENOMEM;
	}

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ret = -ENOMEM;
		goto err3;
	}

	mutex_init(&max8997->dvs_lock);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	rdev = max8997->rdev;
	max8997->dev = &pdev->dev;
	max8997->iodev = iodev;
	max8997->num_regulators = pdata->num_regulators;
	platform_set_drvdata(pdev, max8997);
	i2c = max8997->iodev->i2c;
<<<<<<< HEAD
<<<<<<< HEAD

	max8997->buck125_gpioindex = pdata->buck125_default_idx;
	max8997->buck1_gpiodvs = pdata->buck1_gpiodvs;
	max8997->buck2_gpiodvs = pdata->buck2_gpiodvs;
	max8997->buck5_gpiodvs = pdata->buck5_gpiodvs;
	memcpy(max8997->buck125_gpios, pdata->buck125_gpios, sizeof(int) * 3);
	max8997->ignore_gpiodvs_side_effect = pdata->ignore_gpiodvs_side_effect;

	for (i = 0; i < 8; i++) {
		max8997->buck1_vol[i] = ret =
			max8997_get_voltage_proper_val(
					&buck1245_voltage_map_desc,
					pdata->buck1_voltage[i] / 1000,
					pdata->buck1_voltage[i] / 1000 +
					buck1245_voltage_map_desc.step);
		if (ret < 0)
			goto err_alloc;

		max8997->buck2_vol[i] = ret =
			max8997_get_voltage_proper_val(
					&buck1245_voltage_map_desc,
					pdata->buck2_voltage[i] / 1000,
					pdata->buck2_voltage[i] / 1000 +
					buck1245_voltage_map_desc.step);
		if (ret < 0)
			goto err_alloc;

		max8997->buck5_vol[i] = ret =
			max8997_get_voltage_proper_val(
					&buck1245_voltage_map_desc,
					pdata->buck5_voltage[i] / 1000,
					pdata->buck5_voltage[i] / 1000 +
					buck1245_voltage_map_desc.step);
		if (ret < 0)
			goto err_alloc;

		if (max_buck1 < max8997->buck1_vol[i])
			max_buck1 = max8997->buck1_vol[i];
		if (max_buck2 < max8997->buck2_vol[i])
			max_buck2 = max8997->buck2_vol[i];
		if (max_buck5 < max8997->buck5_vol[i])
			max_buck5 = max8997->buck5_vol[i];
	}

	/* For the safety, set max voltage before setting up */
	for (i = 0; i < 8; i++) {
		max8997_update_reg(i2c, MAX8997_REG_BUCK1DVS1 + i,
				max_buck1, 0x3f);
		max8997_update_reg(i2c, MAX8997_REG_BUCK2DVS1 + i,
				max_buck2, 0x3f);
		max8997_update_reg(i2c, MAX8997_REG_BUCK5DVS1 + i,
				max_buck5, 0x3f);
	}

	/*
	 * If buck 1, 2, and 5 do not care DVS GPIO settings, ignore them.
	 * If at least one of them cares, set gpios.
	 */
	if (pdata->buck1_gpiodvs || pdata->buck2_gpiodvs ||
			pdata->buck5_gpiodvs) {
		bool gpio1set = false, gpio2set = false;

		if (!gpio_is_valid(pdata->buck125_gpios[0]) ||
				!gpio_is_valid(pdata->buck125_gpios[1]) ||
				!gpio_is_valid(pdata->buck125_gpios[2])) {
			dev_err(&pdev->dev, "GPIO NOT VALID\n");
			ret = -EINVAL;
			goto err_alloc;
		}

		ret = gpio_request(pdata->buck125_gpios[0],
				"MAX8997 SET1");
		if (ret == -EBUSY)
			dev_warn(&pdev->dev, "Duplicated gpio request"
					" on SET1\n");
		else if (ret)
			goto err_alloc;
		else
			gpio1set = true;

		ret = gpio_request(pdata->buck125_gpios[1],
				"MAX8997 SET2");
		if (ret == -EBUSY)
			dev_warn(&pdev->dev, "Duplicated gpio request"
					" on SET2\n");
		else if (ret) {
			if (gpio1set)
				gpio_free(pdata->buck125_gpios[0]);
			goto err_alloc;
		} else
			gpio2set = true;

		ret = gpio_request(pdata->buck125_gpios[2],
				"MAX8997 SET3");
		if (ret == -EBUSY)
			dev_warn(&pdev->dev, "Duplicated gpio request"
					" on SET3\n");
		else if (ret) {
			if (gpio1set)
				gpio_free(pdata->buck125_gpios[0]);
			if (gpio2set)
				gpio_free(pdata->buck125_gpios[1]);
			goto err_alloc;
		}

		gpio_direction_output(pdata->buck125_gpios[0],
				(max8997->buck125_gpioindex >> 2)
				& 0x1); /* SET1 */
		gpio_direction_output(pdata->buck125_gpios[1],
				(max8997->buck125_gpioindex >> 1)
				& 0x1); /* SET2 */
		gpio_direction_output(pdata->buck125_gpios[2],
				(max8997->buck125_gpioindex >> 0)
				& 0x1); /* SET3 */
		ret = 0;
	}

	/* DVS-GPIO disabled */
	max8997_update_reg(i2c, MAX8997_REG_BUCK1CTRL, (pdata->buck1_gpiodvs) ?
			(1 << 1) : (0 << 1), 1 << 1);
	max8997_update_reg(i2c, MAX8997_REG_BUCK2CTRL, (pdata->buck2_gpiodvs) ?
			(1 << 1) : (0 << 1), 1 << 1);
	max8997_update_reg(i2c, MAX8997_REG_BUCK5CTRL, (pdata->buck5_gpiodvs) ?
			(1 << 1) : (0 << 1), 1 << 1);

	/* Initialize all the DVS related BUCK registers */
	for (i = 0; i < 8; i++) {
		max8997_update_reg(i2c, MAX8997_REG_BUCK1DVS1 + i,
				max8997->buck1_vol[i],
				0x3f);
		max8997_update_reg(i2c, MAX8997_REG_BUCK2DVS1 + i,
				max8997->buck2_vol[i],
				0x3f);
		max8997_update_reg(i2c, MAX8997_REG_BUCK5DVS1 + i,
				max8997->buck5_vol[i],
				0x3f);
	}

	/* Misc Settings */
	max8997->ramp_delay = 10; /* set 10mV/us, which is the default */
	max8997_write_reg(i2c, MAX8997_REG_BUCKRAMP, (0xf << 4) | 0x9);

	for (i = 0; i < pdata->num_regulators; i++) {
		const struct voltage_map_desc *desc;
		int id = pdata->regulators[i].id;

		desc = reg_voltage_map[id];
		if (desc)
			regulators[id].n_voltages =
				(desc->max - desc->min) / desc->step + 1;
		else if (id == MAX8997_ESAFEOUT1 || id == MAX8997_ESAFEOUT2)
			regulators[id].n_voltages = 4;
		else if (id == MAX8997_CHARGER_CV)
			regulators[id].n_voltages = 16;

		rdev[i] = regulator_register(&regulators[id], max8997->dev,
				pdata->regulators[i].initdata, max8997, NULL);
		if (IS_ERR(rdev[i])) {
			ret = PTR_ERR(rdev[i]);
			dev_err(max8997->dev, "regulator init failed for %d\n",
					id);
			rdev[i] = NULL;
			goto err;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	max8997->buck1_gpiodvs = pdata->buck1_gpiodvs;
	max8997->buck_set1 = pdata->buck_set1;
	max8997->buck_set2 = pdata->buck_set2;
	max8997->buck_set3 = pdata->buck_set3;

	/* NOTE:
	 * This MAX8997 PMIC driver support only BUCK1 GPIO DVS
	 * because BUCK1(ARM clock voltage) is most frequently changed
	 */
	/* For the safety, set max voltage before DVS configuration */
	if (!pdata->buck1_max_vol || !pdata->buck2_max_vol
			|| !pdata->buck5_max_vol) {
		pr_err("MAX8997: must set buck max voltage!\n");
		goto err2;
	}

	ret = max8997_set_buck_max_voltage(max8997, 1, pdata->buck1_max_vol);
	if (ret < 0) {
		pr_err("MAX8997: fail to set buck1 max voltage!\n");
		goto err2;
	}

	ret = max8997_set_buck_max_voltage(max8997, 2, pdata->buck2_max_vol);
	if (ret < 0) {
		pr_err("MAX8997: fail to set buck2 max voltage!\n");
		goto err2;
	}

	ret = max8997_set_buck_max_voltage(max8997, 5, pdata->buck5_max_vol);
	if (ret < 0) {
		pr_err("MAX8997: fail to set buck5 max voltage!\n");
		goto err2;
	}

	/* NOTE: */
	/* For unused GPIO NOT marked as -1 (thereof equal to 0)  WARN_ON */
	/* will be displayed */
	/* Check if MAX8997 voltage selection GPIOs are defined */
	if (gpio_is_valid(max8997->buck_set1) &&
	    gpio_is_valid(max8997->buck_set2) &&
	    gpio_is_valid(max8997->buck_set3)) {
		/* Check if SET1 is not equal to 0 */
		if (!max8997->buck_set1) {
			pr_err("MAX8997 SET1 GPIO defined as 0 !\n");
			WARN_ON(!pdata->buck_set1);
			ret = -EIO;
			goto err2;
		}
		/* Check if SET2 is not equal to 0 */
		if (!max8997->buck_set2) {
			pr_err("MAX8998 SET2 GPIO defined as 0 !\n");
			WARN_ON(!pdata->buck_set2);
			ret = -EIO;
			goto err2;
		}
		/* Check if SET3 is not equal to 0 */
		if (!max8997->buck_set3) {
			pr_err("MAX8997 SET3 GPIO defined as 0 !\n");
			WARN_ON(!max8997->buck_set3);
			ret = -EIO;
			goto err2;
		}

		/* To prepare watchdog reset, index 0 of voltage table is
		 * always highest voltage.
		 * Default voltage of BUCK1,2,5 was configured by bootloader.
		 */
		max8997->buck1_idx = 1;
		gpio_request(max8997->buck_set1, "MAX8997 BUCK_SET1");
		gpio_direction_output(max8997->buck_set1, 1);
		gpio_request(max8997->buck_set2, "MAX8997 BUCK_SET2");
		gpio_direction_output(max8997->buck_set2, 0);
		gpio_request(max8997->buck_set3, "MAX8997 BUCK_SET3");
		gpio_direction_output(max8997->buck_set3, 0);

		if (max8997->buck1_gpiodvs) {
			/* Set predefined value for BUCK1 register 2 ~ 8 */
			ret = max8997_set_buck1_voltages(max8997,
				pdata->buck1_voltages, BUCK1_TABLE_SIZE);
			if (ret < 0)
				goto err2;
		}
	} else {
		pr_err("MAX8997 SETx GPIO is invalid!\n");
		goto err2;
	}

	max8997->funcs.set_buck1_dvs_table = max8997_set_buck1_dvs_table;
	if (pdata->register_buck1_dvs_funcs)
		pdata->register_buck1_dvs_funcs(&max8997->funcs);

	max8997_set_buckramp(max8997, pdata);

	if (pdata->flash_cntl_val) {
		ret =  max8997_write_reg(i2c, MAX8997_REG_FLASH_CNTL,
				pdata->flash_cntl_val);
		if (ret < 0) {
			dev_err(max8997->dev, "flash init failed: %d\n", ret);
			goto err2;
		}
	}

	if (pdata->mr_debounce_time)
		max8997_set_mr_debouce_time(max8997, pdata);

	for (i = 0; i < pdata->num_regulators; i++) {
		const struct vol_cur_map_desc *desc;
		int id = pdata->regulators[i].id;
		int index = id - MAX8997_LDO1;

		if (pdata->regulators[i].is_valid_regulator) {
			if (!pdata->regulators[i].is_valid_regulator(id,
						pdata->regulators[i].initdata))
				continue;
		}

		desc = ldo_vol_cur_map[id];
		if (desc && regulators[index].ops != &max8997_others_ops) {
			int count = (desc->max - desc->min) / desc->step + 1;
			regulators[index].n_voltages = count;
		}
		rdev[i] = regulator_register(&regulators[index], max8997->dev,
				pdata->regulators[i].initdata, max8997);
		if (IS_ERR(rdev[i])) {
			ret = PTR_ERR(rdev[i]);
			dev_err(max8997->dev, "regulator init failed\n");
			rdev[i] = NULL;
			goto err1;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		}
	}

	return 0;
<<<<<<< HEAD
<<<<<<< HEAD
err:
	for (i = 0; i < max8997->num_regulators; i++)
		if (rdev[i])
			regulator_unregister(rdev[i]);
err_alloc:
	kfree(max8997->rdev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
err1:
	for (i = 0; i < max8997->num_regulators; i++)
		if (rdev[i])
			regulator_unregister(rdev[i]);
err2:
	kfree(max8997->rdev);
err3:
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	kfree(max8997);

	return ret;
}

static int __devexit max8997_pmic_remove(struct platform_device *pdev)
{
	struct max8997_data *max8997 = platform_get_drvdata(pdev);
	struct regulator_dev **rdev = max8997->rdev;
	int i;

	for (i = 0; i < max8997->num_regulators; i++)
		if (rdev[i])
			regulator_unregister(rdev[i]);

	kfree(max8997->rdev);
	kfree(max8997);

	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
static const struct platform_device_id max8997_pmic_id[] = {
	{ "max8997-pmic", 0},
	{ },
};
MODULE_DEVICE_TABLE(platform, max8997_pmic_id);

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct platform_driver max8997_pmic_driver = {
	.driver = {
		.name = "max8997-pmic",
		.owner = THIS_MODULE,
	},
	.probe = max8997_pmic_probe,
	.remove = __devexit_p(max8997_pmic_remove),
<<<<<<< HEAD
<<<<<<< HEAD
	.id_table = max8997_pmic_id,
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static int __init max8997_pmic_init(void)
{
	return platform_driver_register(&max8997_pmic_driver);
}
subsys_initcall(max8997_pmic_init);

static void __exit max8997_pmic_cleanup(void)
{
	platform_driver_unregister(&max8997_pmic_driver);
}
module_exit(max8997_pmic_cleanup);

<<<<<<< HEAD
<<<<<<< HEAD
MODULE_DESCRIPTION("MAXIM 8997/8966 Regulator Driver");
MODULE_AUTHOR("MyungJoo Ham <myungjoo.ham@samsung.com>");
=======
MODULE_DESCRIPTION("MAXIM 8997 voltage regulator driver");
MODULE_AUTHOR("<ms925.kim@samsung.com>");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
MODULE_DESCRIPTION("MAXIM 8997 voltage regulator driver");
MODULE_AUTHOR("<ms925.kim@samsung.com>");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
MODULE_LICENSE("GPL");
