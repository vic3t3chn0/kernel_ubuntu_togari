/*
 * leds-max8997.c - LED class driver for MAX8997 LEDs.
 *
 * Copyright (C) 2011 Samsung Electronics
<<<<<<< HEAD
<<<<<<< HEAD
 * Donggeun Kim <dg77.kim@samsung.com>
=======
 *
 * Inspired by leds-regulator driver.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 *
 * Inspired by leds-regulator driver.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/module.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/workqueue.h>
#include <linux/leds.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/mfd/max8997.h>
#include <linux/mfd/max8997-private.h>
#include <linux/platform_device.h>

#define MAX8997_LED_FLASH_SHIFT			3
#define MAX8997_LED_FLASH_CUR_MASK		0xf8
#define MAX8997_LED_MOVIE_SHIFT			4
#define MAX8997_LED_MOVIE_CUR_MASK		0xf0

#define MAX8997_LED_FLASH_MAX_BRIGHTNESS	0x1f
#define MAX8997_LED_MOVIE_MAX_BRIGHTNESS	0xf
#define MAX8997_LED_NONE_MAX_BRIGHTNESS		0

#define MAX8997_LED0_FLASH_MASK			0x1
#define MAX8997_LED0_FLASH_PIN_MASK		0x5
#define MAX8997_LED0_MOVIE_MASK			0x8
#define MAX8997_LED0_MOVIE_PIN_MASK		0x28

#define MAX8997_LED1_FLASH_MASK			0x2
#define MAX8997_LED1_FLASH_PIN_MASK		0x6
#define MAX8997_LED1_MOVIE_MASK			0x10
#define MAX8997_LED1_MOVIE_PIN_MASK		0x30

#define MAX8997_LED_BOOST_ENABLE_MASK		(1 << 6)

struct max8997_led {
	struct max8997_dev *iodev;
	struct led_classdev cdev;
	bool enabled;
	int id;
	enum max8997_led_mode led_mode;
	struct mutex mutex;
};

static void max8997_led_clear_mode(struct max8997_led *led,
			enum max8997_led_mode mode)
{
	struct i2c_client *client = led->iodev->i2c;
	u8 val = 0, mask = 0;
	int ret;

	switch (mode) {
	case MAX8997_FLASH_MODE:
		mask = led->id ?
		      MAX8997_LED1_FLASH_MASK : MAX8997_LED0_FLASH_MASK;
		break;
	case MAX8997_MOVIE_MODE:
		mask = led->id ?
		      MAX8997_LED1_MOVIE_MASK : MAX8997_LED0_MOVIE_MASK;
		break;
	case MAX8997_FLASH_PIN_CONTROL_MODE:
		mask = led->id ?
		      MAX8997_LED1_FLASH_PIN_MASK : MAX8997_LED0_FLASH_PIN_MASK;
		break;
	case MAX8997_MOVIE_PIN_CONTROL_MODE:
		mask = led->id ?
		      MAX8997_LED1_MOVIE_PIN_MASK : MAX8997_LED0_MOVIE_PIN_MASK;
		break;
	default:
		break;
	}

	if (mask) {
		ret = max8997_update_reg(client,
				MAX8997_REG_LEN_CNTL, val, mask);
		if (ret)
			dev_err(led->iodev->dev,
				"failed to update register(%d)\n", ret);
	}
}

static void max8997_led_set_mode(struct max8997_led *led,
			enum max8997_led_mode mode)
{
	int ret;
	struct i2c_client *client = led->iodev->i2c;
	u8 mask = 0;

	/* First, clear the previous mode */
	max8997_led_clear_mode(led, led->led_mode);

	switch (mode) {
	case MAX8997_FLASH_MODE:
		mask = led->id ?
		      MAX8997_LED1_FLASH_MASK : MAX8997_LED0_FLASH_MASK;
		led->cdev.max_brightness = MAX8997_LED_FLASH_MAX_BRIGHTNESS;
		break;
	case MAX8997_MOVIE_MODE:
		mask = led->id ?
		      MAX8997_LED1_MOVIE_MASK : MAX8997_LED0_MOVIE_MASK;
		led->cdev.max_brightness = MAX8997_LED_MOVIE_MAX_BRIGHTNESS;
		break;
	case MAX8997_FLASH_PIN_CONTROL_MODE:
		mask = led->id ?
		      MAX8997_LED1_FLASH_PIN_MASK : MAX8997_LED0_FLASH_PIN_MASK;
		led->cdev.max_brightness = MAX8997_LED_FLASH_MAX_BRIGHTNESS;
		break;
	case MAX8997_MOVIE_PIN_CONTROL_MODE:
		mask = led->id ?
		      MAX8997_LED1_MOVIE_PIN_MASK : MAX8997_LED0_MOVIE_PIN_MASK;
		led->cdev.max_brightness = MAX8997_LED_MOVIE_MAX_BRIGHTNESS;
		break;
	default:
		led->cdev.max_brightness = MAX8997_LED_NONE_MAX_BRIGHTNESS;
		break;
	}

	if (mask) {
		ret = max8997_update_reg(client,
				MAX8997_REG_LEN_CNTL, mask, mask);
		if (ret)
			dev_err(led->iodev->dev,
				"failed to update register(%d)\n", ret);
	}

	led->led_mode = mode;
}

static void max8997_led_enable(struct max8997_led *led, bool enable)
{
	int ret;
	struct i2c_client *client = led->iodev->i2c;
	u8 val = 0, mask = MAX8997_LED_BOOST_ENABLE_MASK;

	if (led->enabled == enable)
		return;

	val = enable ? MAX8997_LED_BOOST_ENABLE_MASK : 0;

	ret = max8997_update_reg(client, MAX8997_REG_BOOST_CNTL, val, mask);
	if (ret)
		dev_err(led->iodev->dev,
			"failed to update register(%d)\n", ret);

	led->enabled = enable;
}

static void max8997_led_set_current(struct max8997_led *led,
				enum led_brightness value)
{
	int ret;
	struct i2c_client *client = led->iodev->i2c;
	u8 val = 0, mask = 0, reg = 0;

	switch (led->led_mode) {
	case MAX8997_FLASH_MODE:
	case MAX8997_FLASH_PIN_CONTROL_MODE:
		val = value << MAX8997_LED_FLASH_SHIFT;
		mask = MAX8997_LED_FLASH_CUR_MASK;
		reg = led->id ? MAX8997_REG_FLASH2_CUR : MAX8997_REG_FLASH1_CUR;
		break;
	case MAX8997_MOVIE_MODE:
	case MAX8997_MOVIE_PIN_CONTROL_MODE:
		val = value << MAX8997_LED_MOVIE_SHIFT;
		mask = MAX8997_LED_MOVIE_CUR_MASK;
		reg = MAX8997_REG_MOVIE_CUR;
		break;
	default:
		break;
	}

	if (mask) {
		ret = max8997_update_reg(client, reg, val, mask);
		if (ret)
			dev_err(led->iodev->dev,
				"failed to update register(%d)\n", ret);
	}
}

static void max8997_led_brightness_set(struct led_classdev *led_cdev,
				enum led_brightness value)
{
	struct max8997_led *led =
			container_of(led_cdev, struct max8997_led, cdev);

	if (value) {
		max8997_led_set_current(led, value);
		max8997_led_enable(led, true);
	} else {
		max8997_led_set_current(led, value);
		max8997_led_enable(led, false);
	}
}

static ssize_t max8997_led_show_mode(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct max8997_led *led =
			container_of(led_cdev, struct max8997_led, cdev);
	ssize_t ret = 0;

	mutex_lock(&led->mutex);

	switch (led->led_mode) {
	case MAX8997_FLASH_MODE:
		ret += sprintf(buf, "FLASH\n");
		break;
	case MAX8997_MOVIE_MODE:
		ret += sprintf(buf, "MOVIE\n");
		break;
	case MAX8997_FLASH_PIN_CONTROL_MODE:
		ret += sprintf(buf, "FLASH_PIN_CONTROL\n");
		break;
	case MAX8997_MOVIE_PIN_CONTROL_MODE:
		ret += sprintf(buf, "MOVIE_PIN_CONTROL\n");
		break;
	default:
		ret += sprintf(buf, "NONE\n");
		break;
	}

	mutex_unlock(&led->mutex);

	return ret;
}

static ssize_t max8997_led_store_mode(struct device *dev,
				struct device_attribute *attr,
				const char *buf, size_t size)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct max8997_led *led =
			container_of(led_cdev, struct max8997_led, cdev);
	enum max8997_led_mode mode;

	mutex_lock(&led->mutex);

	if (!strncmp(buf, "FLASH_PIN_CONTROL", 17))
		mode = MAX8997_FLASH_PIN_CONTROL_MODE;
	else if (!strncmp(buf, "MOVIE_PIN_CONTROL", 17))
		mode = MAX8997_MOVIE_PIN_CONTROL_MODE;
	else if (!strncmp(buf, "FLASH", 5))
		mode = MAX8997_FLASH_MODE;
	else if (!strncmp(buf, "MOVIE", 5))
		mode = MAX8997_MOVIE_MODE;
	else
		mode = MAX8997_NONE;

	max8997_led_set_mode(led, mode);

	mutex_unlock(&led->mutex);

	return size;
}

static DEVICE_ATTR(mode, 0644, max8997_led_show_mode, max8997_led_store_mode);

static int __devinit max8997_led_probe(struct platform_device *pdev)
{
	struct max8997_dev *iodev = dev_get_drvdata(pdev->dev.parent);
	struct max8997_platform_data *pdata = dev_get_platdata(iodev->dev);
	struct max8997_led *led;
	char name[20];
	int ret = 0;

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/leds-max8997.h>
#include <linux/platform_device.h>
#include <linux/regulator/consumer.h>

#define to_regulator_led(led_cdev) \
	container_of(led_cdev, struct regulator_led, cdev)

struct regulator_led {
	struct led_classdev cdev;
	enum led_brightness value;
	int enabled;
	struct mutex mutex;
	struct work_struct work;

	struct regulator *vcc;
};

static inline int led_regulator_get_max_brightness(struct regulator *supply)
{
	int ret;
	int voltage = regulator_list_voltage(supply, 0);

	/*TODO*/
#if defined(CONFIG_MACH_Q1_BD)  || defined(CONFIG_MACH_U1_NA_USCC)
	return LED_BRIGHTNESS_MAX_LEVEL;
#else
	return 1;
#endif

	if (voltage <= 0)
		return 1;

	/* even if regulator can't change voltages,
	 * we still assume it can change status
	 * and the LED can be turned on and off.
	 */
	ret = regulator_set_voltage(supply, voltage, voltage);
	if (ret < 0)
		return 1;

	return regulator_count_voltages(supply);
}

static int led_regulator_get_voltage(struct regulator *supply,
		enum led_brightness brightness)
{
	if (brightness == 0)
		return -EINVAL;

	return regulator_list_voltage(supply, brightness - 1);
}


static void regulator_led_enable(struct regulator_led *led)
{
	int ret;

	if (led->enabled)
		return;

	ret = regulator_enable(led->vcc);
	if (ret != 0) {
		dev_err(led->cdev.dev, "Failed to enable vcc: %d\n", ret);
		return;
	}

	led->enabled = 1;
}

static void regulator_led_disable(struct regulator_led *led)
{
	int ret;

	if (!led->enabled)
		return;

	ret = regulator_disable(led->vcc);
	if (ret != 0) {
		dev_err(led->cdev.dev, "Failed to disable vcc: %d\n", ret);
		return;
	}

	led->enabled = 0;
}

static void regulator_led_set_value(struct regulator_led *led)
{
	int voltage;
	int ret;
	struct regulator *movie;

	mutex_lock(&led->mutex);

	if (led->cdev.flags & LED_SUSPENDED)
		goto out;

	if (led->value == LED_OFF) {
		regulator_led_disable(led);
		goto out;
	}

	movie = regulator_get(NULL, "led_movie");
	if (IS_ERR(movie)) {
		pr_err("%s: led_movie is failed.\n", __func__);
		goto out;
	}

/* Q1 has torch light widget, and it changes */
/* its brightness level without disabling rerulator */
/* So, remove the below code for Q1 */
#if !defined(CONFIG_MACH_Q1_BD) && !defined(CONFIG_MACH_U1_NA_USCC)
	if (regulator_is_enabled(movie) > 0) {
		pr_info("%s: led_movie is enabled.\n", __func__);
		goto end;
	}
#endif

#if 0 /*TODO*/
	if (led->cdev.max_brightness > 1) {
		voltage = led_regulator_get_voltage(led->vcc, led->value);
		dev_dbg(led->cdev.dev, "brightness: %d voltage: %d\n",
				led->value, voltage);

		ret = regulator_set_voltage(led->vcc, voltage, voltage);
		if (ret != 0)
			dev_err(led->cdev.dev, "Failed to set voltage %d: %d\n",
				voltage, ret);
	}
#endif

#if defined(CONFIG_MACH_Q1_BD)  || defined(CONFIG_MACH_U1_NA_USCC)
	switch (led->value) {
	case LED_BRIGHTNESS_LEVEL1:
		regulator_set_current_limit(led->vcc, 10000, 20000);
		break;
	case LED_BRIGHTNESS_LEVEL2:
	regulator_set_current_limit(led->vcc, 90000, 110000);
		break;
	case LED_BRIGHTNESS_LEVEL3:
		regulator_set_current_limit(led->vcc, 180000, 200000);
		break;
	default:
		pr_err("%s: fail to set current, out of range\n", __func__);
		goto end;
		break;
	}
#else
	regulator_set_current_limit(led->vcc, 90000, 110000);
#endif

	regulator_led_enable(led);

end:
	regulator_put(movie);

out:
	mutex_unlock(&led->mutex);
}

static void led_work(struct work_struct *work)
{
	struct regulator_led *led;

	led = container_of(work, struct regulator_led, work);
	regulator_led_set_value(led);
}

static void regulator_led_brightness_set(struct led_classdev *led_cdev,
			   enum led_brightness value)
{
	struct regulator_led *led = to_regulator_led(led_cdev);

	led->value = value;
	schedule_work(&led->work);
}

static int __devinit regulator_led_probe(struct platform_device *pdev)
{
	struct led_max8997_platform_data *pdata = pdev->dev.platform_data;
	struct regulator_led *led;
	struct regulator *vcc;
	int ret = 0;

	pr_info("%s +\n", __func__);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (pdata == NULL) {
		dev_err(&pdev->dev, "no platform data\n");
		return -ENODEV;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	led = kzalloc(sizeof(*led), GFP_KERNEL);
	if (led == NULL) {
		ret = -ENOMEM;
		goto err_mem;
	}

	led->id = pdev->id;
	snprintf(name, sizeof(name), "max8997-led%d", pdev->id);

	led->cdev.name = name;
	led->cdev.brightness_set = max8997_led_brightness_set;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led->cdev.brightness = 0;
	led->iodev = iodev;

	/* initialize mode and brightness according to platform_data */
	if (pdata->led_pdata) {
		u8 mode = 0, brightness = 0;

		mode = pdata->led_pdata->mode[led->id];
		brightness = pdata->led_pdata->brightness[led->id];

		max8997_led_set_mode(led, pdata->led_pdata->mode[led->id]);

		if (brightness > led->cdev.max_brightness)
			brightness = led->cdev.max_brightness;
		max8997_led_set_current(led, brightness);
		led->cdev.brightness = brightness;
	} else {
		max8997_led_set_mode(led, MAX8997_NONE);
		max8997_led_set_current(led, 0);
	}

	mutex_init(&led->mutex);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	vcc = regulator_get_exclusive(&pdev->dev, "led_torch");
	if (IS_ERR(vcc)) {
		dev_err(&pdev->dev, "Cannot get vcc for %s\n", pdata->name);
		return PTR_ERR(vcc);
	}

	led = kzalloc(sizeof(*led), GFP_KERNEL);
	if (led == NULL) {
		ret = -ENOMEM;
		goto err_vcc;
	}

	led->cdev.max_brightness = led_regulator_get_max_brightness(vcc);
	if (pdata->brightness > led->cdev.max_brightness) {
		dev_err(&pdev->dev, "Invalid default brightness %d\n",
				pdata->brightness);
		ret = -EINVAL;
		goto err_led;
	}

	/* Set default brightness */
	led->value = pdata->brightness;

	led->cdev.brightness_set = regulator_led_brightness_set;
	/* Set leds name for class driver */
	led->cdev.name = pdata->name;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;
	led->vcc = vcc;

	mutex_init(&led->mutex);
	INIT_WORK(&led->work, led_work);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	platform_set_drvdata(pdev, led);

	ret = led_classdev_register(&pdev->dev, &led->cdev);
<<<<<<< HEAD
<<<<<<< HEAD
	if (ret < 0)
		goto err_led;

	ret = device_create_file(led->cdev.dev, &dev_attr_mode);
	if (ret != 0) {
		dev_err(&pdev->dev,
			"failed to create file: %d\n", ret);
		goto err_file;
	}

	return 0;

err_file:
	led_classdev_unregister(&led->cdev);
err_led:
	kfree(led);
err_mem:
	return ret;
}

static int __devexit max8997_led_remove(struct platform_device *pdev)
{
	struct max8997_led *led = platform_get_drvdata(pdev);

	device_remove_file(led->cdev.dev, &dev_attr_mode);
	led_classdev_unregister(&led->cdev);
	kfree(led);

	return 0;
}

static struct platform_driver max8997_led_driver = {
	.driver = {
		.name  = "max8997-led",
		.owner = THIS_MODULE,
	},
	.probe  = max8997_led_probe,
	.remove = __devexit_p(max8997_led_remove),
};

static int __init max8997_led_init(void)
{
	return platform_driver_register(&max8997_led_driver);
}
module_init(max8997_led_init);

static void __exit max8997_led_exit(void)
{
	platform_driver_unregister(&max8997_led_driver);
}
module_exit(max8997_led_exit);

MODULE_AUTHOR("Donggeun Kim <dg77.kim@samsung.com>");
MODULE_DESCRIPTION("MAX8997 LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:max8997-led");
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret < 0) {
		cancel_work_sync(&led->work);
		goto err_led;
	}

	/* to expose the default value to userspace */
	led->cdev.brightness = led->value;

	/* Set the default led status */
	regulator_led_set_value(led);

	pr_info("%s -\n", __func__);

	return 0;

err_led:
	kfree(led);
err_vcc:
	regulator_put(vcc);
	return ret;
}

static int __devexit regulator_led_remove(struct platform_device *pdev)
{
	struct regulator_led *led = platform_get_drvdata(pdev);

	led_classdev_unregister(&led->cdev);
	cancel_work_sync(&led->work);
	regulator_led_disable(led);
	regulator_put(led->vcc);
	kfree(led);
	return 0;
}

static void regulator_led_shutdown(struct platform_device *pdev)
{
	struct regulator_led *led = platform_get_drvdata(pdev);

	if (regulator_is_enabled(led->vcc))
		regulator_led_disable(led);

	return;
}

static struct platform_driver regulator_led_driver = {
	.driver = {
		   .name  = "leds-max8997",
		   .owner = THIS_MODULE,
		   },
	.probe  = regulator_led_probe,
	.remove = __devexit_p(regulator_led_remove),
	.shutdown = regulator_led_shutdown,
};

static int __init regulator_led_init(void)
{
	return platform_driver_register(&regulator_led_driver);
}
module_init(regulator_led_init);

static void __exit regulator_led_exit(void)
{
	platform_driver_unregister(&regulator_led_driver);
}
module_exit(regulator_led_exit);

MODULE_AUTHOR("Byun.C.W");
MODULE_DESCRIPTION("MAX8997 LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:leds-max8997");
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
