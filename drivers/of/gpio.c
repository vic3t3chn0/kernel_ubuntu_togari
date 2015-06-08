/*
 * OF helpers for the GPIO API
 *
 * Copyright (c) 2007-2008  MontaVista Software, Inc.
 *
 * Author: Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <linux/device.h>
#include <linux/errno.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/pinctrl/pinctrl.h>
#include <linux/slab.h>

/**
 * of_get_named_gpio_flags() - Get a GPIO number and flags to use with GPIO API
 * @np:		device node to get GPIO from
 * @propname:	property name containing gpio specifier(s)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/slab.h>

/**
 * of_get_gpio_flags - Get a GPIO number and flags to use with GPIO API
 * @np:		device node to get GPIO from
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * @index:	index of the GPIO
 * @flags:	a flags pointer to fill in
 *
 * Returns GPIO number to use with Linux generic GPIO API, or one of the errno
 * value on the error condition. If @flags is not NULL the function also fills
 * in flags for the GPIO.
 */
<<<<<<< HEAD
<<<<<<< HEAD
int of_get_named_gpio_flags(struct device_node *np, const char *propname,
                           int index, enum of_gpio_flags *flags)
{
	int ret;
	struct gpio_chip *gc;
	struct of_phandle_args gpiospec;

	ret = of_parse_phandle_with_args(np, propname, "#gpio-cells", index,
					 &gpiospec);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int of_get_gpio_flags(struct device_node *np, int index,
		      enum of_gpio_flags *flags)
{
	int ret;
	struct device_node *gpio_np;
	struct gpio_chip *gc;
	int size;
	const void *gpio_spec;
	const __be32 *gpio_cells;

	ret = of_parse_phandles_with_args(np, "gpios", "#gpio-cells", index,
					  &gpio_np, &gpio_spec);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret) {
		pr_debug("%s: can't parse gpios property\n", __func__);
		goto err0;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	gc = of_node_to_gpiochip(gpiospec.np);
	if (!gc) {
		pr_debug("%s: gpio controller %s isn't registered\n",
			 np->full_name, gpiospec.np->full_name);
		ret = -EPROBE_DEFER;
		goto err1;
	}

	if (gpiospec.args_count != gc->of_gpio_n_cells) {
		pr_debug("%s: wrong #gpio-cells for %s\n",
			 np->full_name, gpiospec.np->full_name);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	gc = of_node_to_gpiochip(gpio_np);
	if (!gc) {
		pr_debug("%s: gpio controller %s isn't registered\n",
			 np->full_name, gpio_np->full_name);
		ret = -ENODEV;
		goto err1;
	}

	gpio_cells = of_get_property(gpio_np, "#gpio-cells", &size);
	if (!gpio_cells || size != sizeof(*gpio_cells) ||
			be32_to_cpup(gpio_cells) != gc->of_gpio_n_cells) {
		pr_debug("%s: wrong #gpio-cells for %s\n",
			 np->full_name, gpio_np->full_name);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		ret = -EINVAL;
		goto err1;
	}

	/* .xlate might decide to not fill in the flags, so clear it. */
	if (flags)
		*flags = 0;

<<<<<<< HEAD
<<<<<<< HEAD
	ret = gc->of_xlate(gc, &gpiospec, flags);
=======
	ret = gc->of_xlate(gc, np, gpio_spec, flags);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	ret = gc->of_xlate(gc, np, gpio_spec, flags);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (ret < 0)
		goto err1;

	ret += gc->base;
err1:
<<<<<<< HEAD
<<<<<<< HEAD
	of_node_put(gpiospec.np);
=======
	of_node_put(gpio_np);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	of_node_put(gpio_np);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
err0:
	pr_debug("%s exited with status %d\n", __func__, ret);
	return ret;
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL(of_get_named_gpio_flags);

/**
 * of_gpio_named_count - Count GPIOs for a device
 * @np:		device node to count GPIOs for
 * @propname:	property name containing gpio specifier(s)
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
EXPORT_SYMBOL(of_get_gpio_flags);

/**
 * of_gpio_count - Count GPIOs for a device
 * @np:		device node to count GPIOs for
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * The function returns the count of GPIOs specified for a node.
 *
 * Note that the empty GPIO specifiers counts too. For example,
 *
 * gpios = <0
 *          &pio1 1 2
 *          0
 *          &pio2 3 4>;
 *
 * defines four GPIOs (so this function will return 4), two of which
 * are not specified.
 */
<<<<<<< HEAD
<<<<<<< HEAD
unsigned int of_gpio_named_count(struct device_node *np, const char* propname)
=======
unsigned int of_gpio_count(struct device_node *np)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
unsigned int of_gpio_count(struct device_node *np)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	unsigned int cnt = 0;

	do {
		int ret;

<<<<<<< HEAD
<<<<<<< HEAD
		ret = of_parse_phandle_with_args(np, propname, "#gpio-cells",
						 cnt, NULL);
=======
		ret = of_parse_phandles_with_args(np, "gpios", "#gpio-cells",
						  cnt, NULL, NULL);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		ret = of_parse_phandles_with_args(np, "gpios", "#gpio-cells",
						  cnt, NULL, NULL);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		/* A hole in the gpios = <> counts anyway. */
		if (ret < 0 && ret != -EEXIST)
			break;
	} while (++cnt);

	return cnt;
}
<<<<<<< HEAD
<<<<<<< HEAD
EXPORT_SYMBOL(of_gpio_named_count);
=======
EXPORT_SYMBOL(of_gpio_count);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
EXPORT_SYMBOL(of_gpio_count);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 * of_gpio_simple_xlate - translate gpio_spec to the GPIO number and flags
 * @gc:		pointer to the gpio_chip structure
 * @np:		device node of the GPIO chip
 * @gpio_spec:	gpio specifier as found in the device tree
 * @flags:	a flags pointer to fill in
 *
 * This is simple translation function, suitable for the most 1:1 mapped
 * gpio chips. This function performs only one sanity check: whether gpio
 * is less than ngpios (that is specified in the gpio_chip).
 */
<<<<<<< HEAD
<<<<<<< HEAD
int of_gpio_simple_xlate(struct gpio_chip *gc,
			 const struct of_phandle_args *gpiospec, u32 *flags)
{
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int of_gpio_simple_xlate(struct gpio_chip *gc, struct device_node *np,
				const void *gpio_spec, u32 *flags)
{
	const __be32 *gpio = gpio_spec;
	const u32 n = be32_to_cpup(gpio);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/*
	 * We're discouraging gpio_cells < 2, since that way you'll have to
	 * write your own xlate function (that will have to retrive the GPIO
	 * number and the flags from a single gpio cell -- this is possible,
	 * but not recommended).
	 */
	if (gc->of_gpio_n_cells < 2) {
		WARN_ON(1);
		return -EINVAL;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	if (WARN_ON(gpiospec->args_count < gc->of_gpio_n_cells))
		return -EINVAL;

	if (gpiospec->args[0] >= gc->ngpio)
		return -EINVAL;

	if (flags)
		*flags = gpiospec->args[1];

	return gpiospec->args[0];
}
EXPORT_SYMBOL(of_gpio_simple_xlate);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (n > gc->ngpio)
		return -EINVAL;

	if (flags)
		*flags = be32_to_cpu(gpio[1]);

	return n;
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 * of_mm_gpiochip_add - Add memory mapped GPIO chip (bank)
 * @np:		device node of the GPIO chip
 * @mm_gc:	pointer to the of_mm_gpio_chip allocated structure
 *
 * To use this function you should allocate and fill mm_gc with:
 *
 * 1) In the gpio_chip structure:
 *    - all the callbacks
 *    - of_gpio_n_cells
 *    - of_xlate callback (optional)
 *
 * 3) In the of_mm_gpio_chip structure:
 *    - save_regs callback (optional)
 *
 * If succeeded, this function will map bank's memory and will
 * do all necessary work for you. Then you'll able to use .regs
 * to manage GPIOs from the callbacks.
 */
int of_mm_gpiochip_add(struct device_node *np,
		       struct of_mm_gpio_chip *mm_gc)
{
	int ret = -ENOMEM;
	struct gpio_chip *gc = &mm_gc->gc;

	gc->label = kstrdup(np->full_name, GFP_KERNEL);
	if (!gc->label)
		goto err0;

	mm_gc->regs = of_iomap(np, 0);
	if (!mm_gc->regs)
		goto err1;

	gc->base = -1;

	if (mm_gc->save_regs)
		mm_gc->save_regs(mm_gc);

	mm_gc->gc.of_node = np;

	ret = gpiochip_add(gc);
	if (ret)
		goto err2;

<<<<<<< HEAD
<<<<<<< HEAD
=======
	pr_debug("%s: registered as generic GPIO chip, base is %d\n",
		 np->full_name, gc->base);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	pr_debug("%s: registered as generic GPIO chip, base is %d\n",
		 np->full_name, gc->base);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
err2:
	iounmap(mm_gc->regs);
err1:
	kfree(gc->label);
err0:
	pr_err("%s: GPIO chip registration failed with status %d\n",
	       np->full_name, ret);
	return ret;
}
EXPORT_SYMBOL(of_mm_gpiochip_add);

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_PINCTRL
void of_gpiochip_add_pin_range(struct gpio_chip *chip)
{
	struct device_node *np = chip->of_node;
	struct of_phandle_args pinspec;
	struct pinctrl_dev *pctldev;
	int index = 0, ret;

	if (!np)
		return;

	do {
		ret = of_parse_phandle_with_args(np, "gpio-ranges",
				"#gpio-range-cells", index, &pinspec);
		if (ret)
			break;

		pctldev = of_pinctrl_get(pinspec.np);
		if (!pctldev)
			break;

		ret = gpiochip_add_pin_range(chip,
					     pinctrl_dev_get_name(pctldev),
					     pinspec.args[0],
					     pinspec.args[1]);

		if (ret)
			break;

	} while (index++);
}

void of_gpiochip_remove_pin_range(struct gpio_chip *chip)
{
	struct gpio_pin_range *pin_range, *tmp;

	list_for_each_entry_safe(pin_range, tmp, &chip->pin_ranges, node) {
		list_del(&pin_range->node);
		pinctrl_remove_gpio_range(pin_range->pctldev,
				&pin_range->range);
	}
}
#else
void of_gpiochip_add_pin_range(struct gpio_chip *chip) {}
void of_gpiochip_remove_pin_range(struct gpio_chip *chip) {}
#endif

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void of_gpiochip_add(struct gpio_chip *chip)
{
	if ((!chip->of_node) && (chip->dev))
		chip->of_node = chip->dev->of_node;

	if (!chip->of_node)
		return;

	if (!chip->of_xlate) {
		chip->of_gpio_n_cells = 2;
		chip->of_xlate = of_gpio_simple_xlate;
	}

<<<<<<< HEAD
<<<<<<< HEAD
	of_gpiochip_add_pin_range(chip);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	of_node_get(chip->of_node);
}

void of_gpiochip_remove(struct gpio_chip *chip)
{
<<<<<<< HEAD
<<<<<<< HEAD
	of_gpiochip_remove_pin_range(chip);

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (chip->of_node)
		of_node_put(chip->of_node);
}

/* Private function for resolving node pointer to gpio_chip */
<<<<<<< HEAD
<<<<<<< HEAD
static int of_gpiochip_is_match(struct gpio_chip *chip, const void *data)
=======
static int of_gpiochip_is_match(struct gpio_chip *chip, void *data)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int of_gpiochip_is_match(struct gpio_chip *chip, void *data)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return chip->of_node == data;
}

struct gpio_chip *of_node_to_gpiochip(struct device_node *np)
{
	return gpiochip_find(np, of_gpiochip_is_match);
}
