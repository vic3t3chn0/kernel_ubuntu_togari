/*
<<<<<<< HEAD
<<<<<<< HEAD
 * Driver for the ADC on Freescale Semiconductor MC13783 and MC13892 PMICs.
=======
 * Driver for the Freescale Semiconductor MC13783 adc.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Driver for the Freescale Semiconductor MC13783 adc.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright 2004-2007 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright (C) 2009 Sascha Hauer, Pengutronix
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 51
 * Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/mfd/mc13xxx.h>
=======
#include <linux/mfd/mc13783.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <linux/mfd/mc13783.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/platform_device.h>
#include <linux/hwmon-sysfs.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/hwmon.h>
#include <linux/slab.h>
#include <linux/init.h>
#include <linux/err.h>

<<<<<<< HEAD
<<<<<<< HEAD
#define DRIVER_NAME	"mc13783-adc"

/* platform device id driver data */
#define MC13783_ADC_16CHANS	1
#define MC13783_ADC_BPDIV2	2

struct mc13783_adc_priv {
	struct mc13xxx *mc13xxx;
	struct device *hwmon_dev;
	char name[10];
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define MC13783_ADC_NAME	"mc13783-adc"

struct mc13783_adc_priv {
	struct mc13783 *mc13783;
	struct device *hwmon_dev;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static ssize_t mc13783_adc_show_name(struct device *dev, struct device_attribute
			      *devattr, char *buf)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct mc13783_adc_priv *priv = dev_get_drvdata(dev);

	return sprintf(buf, "%s\n", priv->name);
=======
	return sprintf(buf, "mc13783_adc\n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return sprintf(buf, "mc13783_adc\n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static int mc13783_adc_read(struct device *dev,
		struct device_attribute *devattr, unsigned int *val)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct mc13783_adc_priv *priv = dev_get_drvdata(dev);
=======
	struct platform_device *pdev = to_platform_device(dev);
	struct mc13783_adc_priv *priv = platform_get_drvdata(pdev);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct platform_device *pdev = to_platform_device(dev);
	struct mc13783_adc_priv *priv = platform_get_drvdata(pdev);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct sensor_device_attribute *attr = to_sensor_dev_attr(devattr);
	unsigned int channel = attr->index;
	unsigned int sample[4];
	int ret;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = mc13xxx_adc_do_conversion(priv->mc13xxx,
			MC13XXX_ADC_MODE_MULT_CHAN,
			channel, 0, 0, sample);
=======
	ret = mc13783_adc_do_conversion(priv->mc13783,
			MC13783_ADC_MODE_MULT_CHAN,
			channel, sample);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ret = mc13783_adc_do_conversion(priv->mc13783,
			MC13783_ADC_MODE_MULT_CHAN,
			channel, sample);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret)
		return ret;

	channel &= 0x7;

	*val = (sample[channel % 4] >> (channel > 3 ? 14 : 2)) & 0x3ff;

	return 0;
}

static ssize_t mc13783_adc_read_bp(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	unsigned val;
<<<<<<< HEAD
<<<<<<< HEAD
	struct platform_device *pdev = to_platform_device(dev);
	kernel_ulong_t driver_data = platform_get_device_id(pdev)->driver_data;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret = mc13783_adc_read(dev, devattr, &val);

	if (ret)
		return ret;

<<<<<<< HEAD
<<<<<<< HEAD
	if (driver_data & MC13783_ADC_BPDIV2)
		val = DIV_ROUND_CLOSEST(val * 9, 2);
	else
		/*
		 * BP (channel 2) reports with offset 2.4V to the actual value
		 * to fit the input range of the ADC.  unit = 2.25mV = 9/4 mV.
		 */
		val = DIV_ROUND_CLOSEST(val * 9, 4) + 2400;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * BP (channel 2) reports with offset 2.4V to the actual value to fit
	 * the input range of the ADC.  unit = 2.25mV = 9/4 mV.
	 */
	val = DIV_ROUND_CLOSEST(val * 9, 4) + 2400;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return sprintf(buf, "%u\n", val);
}

static ssize_t mc13783_adc_read_gp(struct device *dev,
		struct device_attribute *devattr, char *buf)
{
	unsigned val;
	int ret = mc13783_adc_read(dev, devattr, &val);

	if (ret)
		return ret;

	/*
	 * input range is [0, 2.3V], val has 10 bits, so each bit
	 * is worth 9/4 mV.
	 */
	val = DIV_ROUND_CLOSEST(val * 9, 4);

	return sprintf(buf, "%u\n", val);
}

static DEVICE_ATTR(name, S_IRUGO, mc13783_adc_show_name, NULL);
static SENSOR_DEVICE_ATTR(in2_input, S_IRUGO, mc13783_adc_read_bp, NULL, 2);
static SENSOR_DEVICE_ATTR(in5_input, S_IRUGO, mc13783_adc_read_gp, NULL, 5);
static SENSOR_DEVICE_ATTR(in6_input, S_IRUGO, mc13783_adc_read_gp, NULL, 6);
static SENSOR_DEVICE_ATTR(in7_input, S_IRUGO, mc13783_adc_read_gp, NULL, 7);
static SENSOR_DEVICE_ATTR(in8_input, S_IRUGO, mc13783_adc_read_gp, NULL, 8);
static SENSOR_DEVICE_ATTR(in9_input, S_IRUGO, mc13783_adc_read_gp, NULL, 9);
static SENSOR_DEVICE_ATTR(in10_input, S_IRUGO, mc13783_adc_read_gp, NULL, 10);
static SENSOR_DEVICE_ATTR(in11_input, S_IRUGO, mc13783_adc_read_gp, NULL, 11);
static SENSOR_DEVICE_ATTR(in12_input, S_IRUGO, mc13783_adc_read_gp, NULL, 12);
static SENSOR_DEVICE_ATTR(in13_input, S_IRUGO, mc13783_adc_read_gp, NULL, 13);
static SENSOR_DEVICE_ATTR(in14_input, S_IRUGO, mc13783_adc_read_gp, NULL, 14);
static SENSOR_DEVICE_ATTR(in15_input, S_IRUGO, mc13783_adc_read_gp, NULL, 15);

<<<<<<< HEAD
<<<<<<< HEAD
static struct attribute *mc13783_attr_base[] = {
=======
static struct attribute *mc13783_attr[] = {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static struct attribute *mc13783_attr[] = {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	&dev_attr_name.attr,
	&sensor_dev_attr_in2_input.dev_attr.attr,
	&sensor_dev_attr_in5_input.dev_attr.attr,
	&sensor_dev_attr_in6_input.dev_attr.attr,
	&sensor_dev_attr_in7_input.dev_attr.attr,
<<<<<<< HEAD
<<<<<<< HEAD
	NULL
};

static const struct attribute_group mc13783_group_base = {
	.attrs = mc13783_attr_base,
};

/* these are only used if MC13783_ADC_16CHANS is provided in driver data */
static struct attribute *mc13783_attr_16chans[] = {
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	&sensor_dev_attr_in8_input.dev_attr.attr,
	&sensor_dev_attr_in9_input.dev_attr.attr,
	&sensor_dev_attr_in10_input.dev_attr.attr,
	&sensor_dev_attr_in11_input.dev_attr.attr,
	NULL
};

<<<<<<< HEAD
<<<<<<< HEAD
static const struct attribute_group mc13783_group_16chans = {
	.attrs = mc13783_attr_16chans,
=======
static const struct attribute_group mc13783_group = {
	.attrs = mc13783_attr,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static const struct attribute_group mc13783_group = {
	.attrs = mc13783_attr,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/* last four channels may be occupied by the touchscreen */
static struct attribute *mc13783_attr_ts[] = {
	&sensor_dev_attr_in12_input.dev_attr.attr,
	&sensor_dev_attr_in13_input.dev_attr.attr,
	&sensor_dev_attr_in14_input.dev_attr.attr,
	&sensor_dev_attr_in15_input.dev_attr.attr,
	NULL
};

static const struct attribute_group mc13783_group_ts = {
	.attrs = mc13783_attr_ts,
};

static int mc13783_adc_use_touchscreen(struct platform_device *pdev)
{
	struct mc13783_adc_priv *priv = platform_get_drvdata(pdev);
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned flags = mc13xxx_get_flags(priv->mc13xxx);

	return flags & MC13XXX_USE_TOUCHSCREEN;
=======
	unsigned flags = mc13783_get_flags(priv->mc13783);

	return flags & MC13783_USE_TOUCHSCREEN;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	unsigned flags = mc13783_get_flags(priv->mc13783);

	return flags & MC13783_USE_TOUCHSCREEN;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static int __init mc13783_adc_probe(struct platform_device *pdev)
{
	struct mc13783_adc_priv *priv;
	int ret;
<<<<<<< HEAD
<<<<<<< HEAD
	const struct platform_device_id *id = platform_get_device_id(pdev);
	char *dash;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	priv = kzalloc(sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

<<<<<<< HEAD
<<<<<<< HEAD
	priv->mc13xxx = dev_get_drvdata(pdev->dev.parent);
	snprintf(priv->name, ARRAY_SIZE(priv->name), "%s", id->name);
	dash = strchr(priv->name, '-');
	if (dash)
		*dash = '\0';
=======
	priv->mc13783 = dev_get_drvdata(pdev->dev.parent);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	priv->mc13783 = dev_get_drvdata(pdev->dev.parent);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	platform_set_drvdata(pdev, priv);

	/* Register sysfs hooks */
<<<<<<< HEAD
<<<<<<< HEAD
	ret = sysfs_create_group(&pdev->dev.kobj, &mc13783_group_base);
	if (ret)
		goto out_err_create_base;

	if (id->driver_data & MC13783_ADC_16CHANS) {
		ret = sysfs_create_group(&pdev->dev.kobj,
				&mc13783_group_16chans);
		if (ret)
			goto out_err_create_16chans;
	}
=======
	ret = sysfs_create_group(&pdev->dev.kobj, &mc13783_group);
	if (ret)
		goto out_err_create1;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ret = sysfs_create_group(&pdev->dev.kobj, &mc13783_group);
	if (ret)
		goto out_err_create1;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!mc13783_adc_use_touchscreen(pdev)) {
		ret = sysfs_create_group(&pdev->dev.kobj, &mc13783_group_ts);
		if (ret)
<<<<<<< HEAD
<<<<<<< HEAD
			goto out_err_create_ts;
=======
			goto out_err_create2;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			goto out_err_create2;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	priv->hwmon_dev = hwmon_device_register(&pdev->dev);
	if (IS_ERR(priv->hwmon_dev)) {
		ret = PTR_ERR(priv->hwmon_dev);
		dev_err(&pdev->dev,
				"hwmon_device_register failed with %d.\n", ret);
		goto out_err_register;
	}

<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;

out_err_register:

	if (!mc13783_adc_use_touchscreen(pdev))
		sysfs_remove_group(&pdev->dev.kobj, &mc13783_group_ts);
<<<<<<< HEAD
<<<<<<< HEAD
out_err_create_ts:

	if (id->driver_data & MC13783_ADC_16CHANS)
		sysfs_remove_group(&pdev->dev.kobj, &mc13783_group_16chans);
out_err_create_16chans:

	sysfs_remove_group(&pdev->dev.kobj, &mc13783_group_base);
out_err_create_base:
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
out_err_create2:

	sysfs_remove_group(&pdev->dev.kobj, &mc13783_group);
out_err_create1:
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	platform_set_drvdata(pdev, NULL);
	kfree(priv);

	return ret;
}

static int __devexit mc13783_adc_remove(struct platform_device *pdev)
{
	struct mc13783_adc_priv *priv = platform_get_drvdata(pdev);
<<<<<<< HEAD
<<<<<<< HEAD
	kernel_ulong_t driver_data = platform_get_device_id(pdev)->driver_data;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	hwmon_device_unregister(priv->hwmon_dev);

	if (!mc13783_adc_use_touchscreen(pdev))
		sysfs_remove_group(&pdev->dev.kobj, &mc13783_group_ts);

<<<<<<< HEAD
<<<<<<< HEAD
	if (driver_data & MC13783_ADC_16CHANS)
		sysfs_remove_group(&pdev->dev.kobj, &mc13783_group_16chans);

	sysfs_remove_group(&pdev->dev.kobj, &mc13783_group_base);
=======
	sysfs_remove_group(&pdev->dev.kobj, &mc13783_group);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	sysfs_remove_group(&pdev->dev.kobj, &mc13783_group);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	platform_set_drvdata(pdev, NULL);
	kfree(priv);

	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
static const struct platform_device_id mc13783_adc_idtable[] = {
	{
		.name = "mc13783-adc",
		.driver_data = MC13783_ADC_16CHANS,
	}, {
		.name = "mc13892-adc",
		.driver_data = MC13783_ADC_BPDIV2,
	}, {
		/* sentinel */
	}
};
MODULE_DEVICE_TABLE(platform, mc13783_adc_idtable);

static struct platform_driver mc13783_adc_driver = {
	.remove		= __devexit_p(mc13783_adc_remove),
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= DRIVER_NAME,
	},
	.id_table	= mc13783_adc_idtable,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct platform_driver mc13783_adc_driver = {
	.remove 	= __devexit_p(mc13783_adc_remove),
	.driver		= {
		.owner	= THIS_MODULE,
		.name	= MC13783_ADC_NAME,
	},
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static int __init mc13783_adc_init(void)
{
	return platform_driver_probe(&mc13783_adc_driver, mc13783_adc_probe);
}

static void __exit mc13783_adc_exit(void)
{
	platform_driver_unregister(&mc13783_adc_driver);
}

module_init(mc13783_adc_init);
module_exit(mc13783_adc_exit);

MODULE_DESCRIPTION("MC13783 ADC driver");
MODULE_AUTHOR("Luotao Fu <l.fu@pengutronix.de>");
MODULE_LICENSE("GPL");
<<<<<<< HEAD
<<<<<<< HEAD
=======
MODULE_ALIAS("platform:" MC13783_ADC_NAME);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
MODULE_ALIAS("platform:" MC13783_ADC_NAME);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
