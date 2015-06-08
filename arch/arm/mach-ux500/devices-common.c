/*
 * Copyright (C) ST-Ericsson SA 2010
 *
 * Author: Rabin Vincent <rabin.vincent@stericsson.com> for ST-Ericsson
 * License terms: GNU General Public License (GPL), version 2.
 */

#include <linux/kernel.h>
#include <linux/dma-mapping.h>
#include <linux/err.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <linux/amba/bus.h>

<<<<<<< HEAD
#include <plat/gpio-nomadik.h>
=======
<<<<<<< HEAD
#include <plat/gpio-nomadik.h>
=======
#include <plat/gpio.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <mach/hardware.h>

#include "devices-common.h"

struct amba_device *
<<<<<<< HEAD
dbx500_add_amba_device(struct device *parent, const char *name,
		       resource_size_t base, int irq, void *pdata,
		       unsigned int periphid)
=======
<<<<<<< HEAD
dbx500_add_amba_device(struct device *parent, const char *name,
		       resource_size_t base, int irq, void *pdata,
		       unsigned int periphid)
=======
dbx500_add_amba_device(const char *name, resource_size_t base,
		       int irq, void *pdata, unsigned int periphid)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	struct amba_device *dev;
	int ret;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev = amba_device_alloc(name, base, SZ_4K);
	if (!dev)
		return ERR_PTR(-ENOMEM);

<<<<<<< HEAD
=======
=======
	dev = kzalloc(sizeof *dev, GFP_KERNEL);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	dev->dev.init_name = name;

	dev->res.start = base;
	dev->res.end = base + SZ_4K - 1;
	dev->res.flags = IORESOURCE_MEM;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev->dma_mask = DMA_BIT_MASK(32);
	dev->dev.coherent_dma_mask = DMA_BIT_MASK(32);

	dev->irq[0] = irq;
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	dev->irq[1] = NO_IRQ;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	dev->periphid = periphid;

	dev->dev.platform_data = pdata;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev->dev.parent = parent;

	ret = amba_device_add(dev, &iomem_resource);
	if (ret) {
		amba_device_put(dev);
<<<<<<< HEAD
=======
=======
	ret = amba_device_register(dev, &iomem_resource);
	if (ret) {
		kfree(dev);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return ERR_PTR(ret);
	}

	return dev;
}

static struct platform_device *
<<<<<<< HEAD
dbx500_add_gpio(struct device *parent, int id, resource_size_t addr, int irq,
=======
<<<<<<< HEAD
dbx500_add_gpio(struct device *parent, int id, resource_size_t addr, int irq,
=======
dbx500_add_platform_device(const char *name, int id, void *pdata,
			   struct resource *res, int resnum)
{
	struct platform_device *dev;
	int ret;

	dev = platform_device_alloc(name, id);
	if (!dev)
		return ERR_PTR(-ENOMEM);

	dev->dev.coherent_dma_mask = DMA_BIT_MASK(32);
	dev->dev.dma_mask = &dev->dev.coherent_dma_mask;

	ret = platform_device_add_resources(dev, res, resnum);
	if (ret)
		goto out_free;

	dev->dev.platform_data = pdata;

	ret = platform_device_add(dev);
	if (ret)
		goto out_free;

	return dev;

out_free:
	platform_device_put(dev);
	return ERR_PTR(ret);
}

struct platform_device *
dbx500_add_platform_device_4k1irq(const char *name, int id,
				  resource_size_t base,
				  int irq, void *pdata)
{
	struct resource resources[] = {
		[0] = {
			.start	= base,
			.end	= base + SZ_4K - 1,
			.flags	= IORESOURCE_MEM,
		},
		[1] = {
			.start	= irq,
			.end	= irq,
			.flags	= IORESOURCE_IRQ,
		}
	};

	return dbx500_add_platform_device(name, id, pdata, resources,
					  ARRAY_SIZE(resources));
}

static struct platform_device *
dbx500_add_gpio(int id, resource_size_t addr, int irq,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		struct nmk_gpio_platform_data *pdata)
{
	struct resource resources[] = {
		{
			.start	= addr,
			.end	= addr + 127,
			.flags	= IORESOURCE_MEM,
		},
		{
			.start	= irq,
			.end	= irq,
			.flags	= IORESOURCE_IRQ,
		}
	};

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return platform_device_register_resndata(
		parent,
		"gpio",
		id,
		resources,
		ARRAY_SIZE(resources),
		pdata,
		sizeof(*pdata));
}

void dbx500_add_gpios(struct device *parent, resource_size_t *base, int num,
		      int irq, struct nmk_gpio_platform_data *pdata)
<<<<<<< HEAD
=======
=======
	return platform_device_register_resndata(NULL, "gpio", id,
				resources, ARRAY_SIZE(resources),
				pdata, sizeof(*pdata));
}

void dbx500_add_gpios(resource_size_t *base, int num, int irq,
		      struct nmk_gpio_platform_data *pdata)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int first = 0;
	int i;

	for (i = 0; i < num; i++, first += 32, irq++) {
		pdata->first_gpio = first;
		pdata->first_irq = NOMADIK_GPIO_TO_IRQ(first);
		pdata->num_gpio = 32;

<<<<<<< HEAD
		dbx500_add_gpio(parent, i, base[i], irq, pdata);
=======
<<<<<<< HEAD
		dbx500_add_gpio(parent, i, base[i], irq, pdata);
=======
		dbx500_add_gpio(i, base[i], irq, pdata);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}
}
