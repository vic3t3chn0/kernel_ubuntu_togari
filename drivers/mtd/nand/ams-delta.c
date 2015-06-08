/*
 *  drivers/mtd/nand/ams-delta.c
 *
 *  Copyright (C) 2006 Jonathan McDowell <noodles@earth.li>
 *
 *  Derived from drivers/mtd/toto.c
 *  Converted to platform driver by Janusz Krzysztofik <jkrzyszt@tis.icnet.pl>
 *  Partially stolen from drivers/mtd/nand/plat_nand.c
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 *  Overview:
 *   This is a device driver for the NAND flash device found on the
 *   Amstrad E3 (Delta).
 */

#include <linux/slab.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/partitions.h>
#include <asm/io.h>
#include <mach/hardware.h>
#include <asm/sizes.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/gpio.h>
=======
#include <mach/gpio.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <mach/gpio.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <plat/board-ams-delta.h>

/*
 * MTD structure for E3 (Delta)
 */
static struct mtd_info *ams_delta_mtd = NULL;

<<<<<<< HEAD
<<<<<<< HEAD
=======
#define NAND_MASK (AMS_DELTA_LATCH2_NAND_NRE | AMS_DELTA_LATCH2_NAND_NWE | AMS_DELTA_LATCH2_NAND_CLE | AMS_DELTA_LATCH2_NAND_ALE | AMS_DELTA_LATCH2_NAND_NCE | AMS_DELTA_LATCH2_NAND_NWP)

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#define NAND_MASK (AMS_DELTA_LATCH2_NAND_NRE | AMS_DELTA_LATCH2_NAND_NWE | AMS_DELTA_LATCH2_NAND_CLE | AMS_DELTA_LATCH2_NAND_ALE | AMS_DELTA_LATCH2_NAND_NCE | AMS_DELTA_LATCH2_NAND_NWP)

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Define partitions for flash devices
 */

static struct mtd_partition partition_info[] = {
	{ .name		= "Kernel",
	  .offset	= 0,
	  .size		= 3 * SZ_1M + SZ_512K },
	{ .name		= "u-boot",
	  .offset	= 3 * SZ_1M + SZ_512K,
	  .size		= SZ_256K },
	{ .name		= "u-boot params",
	  .offset	= 3 * SZ_1M + SZ_512K + SZ_256K,
	  .size		= SZ_256K },
	{ .name		= "Amstrad LDR",
	  .offset	= 4 * SZ_1M,
	  .size		= SZ_256K },
	{ .name		= "File system",
	  .offset	= 4 * SZ_1M + 1 * SZ_256K,
	  .size		= 27 * SZ_1M },
	{ .name		= "PBL reserved",
	  .offset	= 32 * SZ_1M - 3 * SZ_256K,
	  .size		=  3 * SZ_256K },
};

static void ams_delta_write_byte(struct mtd_info *mtd, u_char byte)
{
	struct nand_chip *this = mtd->priv;
	void __iomem *io_base = this->priv;

	writew(0, io_base + OMAP_MPUIO_IO_CNTL);
	writew(byte, this->IO_ADDR_W);
<<<<<<< HEAD
<<<<<<< HEAD
	gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_NWE, 0);
	ndelay(40);
	gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_NWE, 1);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ams_delta_latch2_write(AMS_DELTA_LATCH2_NAND_NWE, 0);
	ndelay(40);
	ams_delta_latch2_write(AMS_DELTA_LATCH2_NAND_NWE,
			       AMS_DELTA_LATCH2_NAND_NWE);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static u_char ams_delta_read_byte(struct mtd_info *mtd)
{
	u_char res;
	struct nand_chip *this = mtd->priv;
	void __iomem *io_base = this->priv;

<<<<<<< HEAD
<<<<<<< HEAD
	gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_NRE, 0);
	ndelay(40);
	writew(~0, io_base + OMAP_MPUIO_IO_CNTL);
	res = readw(this->IO_ADDR_R);
	gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_NRE, 1);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ams_delta_latch2_write(AMS_DELTA_LATCH2_NAND_NRE, 0);
	ndelay(40);
	writew(~0, io_base + OMAP_MPUIO_IO_CNTL);
	res = readw(this->IO_ADDR_R);
	ams_delta_latch2_write(AMS_DELTA_LATCH2_NAND_NRE,
			       AMS_DELTA_LATCH2_NAND_NRE);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return res;
}

static void ams_delta_write_buf(struct mtd_info *mtd, const u_char *buf,
				int len)
{
	int i;

	for (i=0; i<len; i++)
		ams_delta_write_byte(mtd, buf[i]);
}

static void ams_delta_read_buf(struct mtd_info *mtd, u_char *buf, int len)
{
	int i;

	for (i=0; i<len; i++)
		buf[i] = ams_delta_read_byte(mtd);
}

static int ams_delta_verify_buf(struct mtd_info *mtd, const u_char *buf,
				int len)
{
	int i;

	for (i=0; i<len; i++)
		if (buf[i] != ams_delta_read_byte(mtd))
			return -EFAULT;

	return 0;
}

/*
 * Command control function
 *
 * ctrl:
 * NAND_NCE: bit 0 -> bit 2
 * NAND_CLE: bit 1 -> bit 7
 * NAND_ALE: bit 2 -> bit 6
 */
static void ams_delta_hwcontrol(struct mtd_info *mtd, int cmd,
				unsigned int ctrl)
{

	if (ctrl & NAND_CTRL_CHANGE) {
<<<<<<< HEAD
<<<<<<< HEAD
		gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_NCE,
				(ctrl & NAND_NCE) == 0);
		gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_CLE,
				(ctrl & NAND_CLE) != 0);
		gpio_set_value(AMS_DELTA_GPIO_PIN_NAND_ALE,
				(ctrl & NAND_ALE) != 0);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		unsigned long bits;

		bits = (~ctrl & NAND_NCE) ? AMS_DELTA_LATCH2_NAND_NCE : 0;
		bits |= (ctrl & NAND_CLE) ? AMS_DELTA_LATCH2_NAND_CLE : 0;
		bits |= (ctrl & NAND_ALE) ? AMS_DELTA_LATCH2_NAND_ALE : 0;

		ams_delta_latch2_write(AMS_DELTA_LATCH2_NAND_CLE |
				AMS_DELTA_LATCH2_NAND_ALE |
				AMS_DELTA_LATCH2_NAND_NCE, bits);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	if (cmd != NAND_CMD_NONE)
		ams_delta_write_byte(mtd, cmd);
}

static int ams_delta_nand_ready(struct mtd_info *mtd)
{
	return gpio_get_value(AMS_DELTA_GPIO_PIN_NAND_RB);
}

<<<<<<< HEAD
<<<<<<< HEAD
static const struct gpio _mandatory_gpio[] = {
	{
		.gpio	= AMS_DELTA_GPIO_PIN_NAND_NCE,
		.flags	= GPIOF_OUT_INIT_HIGH,
		.label	= "nand_nce",
	},
	{
		.gpio	= AMS_DELTA_GPIO_PIN_NAND_NRE,
		.flags	= GPIOF_OUT_INIT_HIGH,
		.label	= "nand_nre",
	},
	{
		.gpio	= AMS_DELTA_GPIO_PIN_NAND_NWP,
		.flags	= GPIOF_OUT_INIT_HIGH,
		.label	= "nand_nwp",
	},
	{
		.gpio	= AMS_DELTA_GPIO_PIN_NAND_NWE,
		.flags	= GPIOF_OUT_INIT_HIGH,
		.label	= "nand_nwe",
	},
	{
		.gpio	= AMS_DELTA_GPIO_PIN_NAND_ALE,
		.flags	= GPIOF_OUT_INIT_LOW,
		.label	= "nand_ale",
	},
	{
		.gpio	= AMS_DELTA_GPIO_PIN_NAND_CLE,
		.flags	= GPIOF_OUT_INIT_LOW,
		.label	= "nand_cle",
	},
};

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Main initialization routine
 */
static int __devinit ams_delta_init(struct platform_device *pdev)
{
	struct nand_chip *this;
	struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	void __iomem *io_base;
	int err = 0;

	if (!res)
		return -ENXIO;

	/* Allocate memory for MTD device structure and private data */
	ams_delta_mtd = kmalloc(sizeof(struct mtd_info) +
				sizeof(struct nand_chip), GFP_KERNEL);
	if (!ams_delta_mtd) {
		printk (KERN_WARNING "Unable to allocate E3 NAND MTD device structure.\n");
		err = -ENOMEM;
		goto out;
	}

	ams_delta_mtd->owner = THIS_MODULE;

	/* Get pointer to private data */
	this = (struct nand_chip *) (&ams_delta_mtd[1]);

	/* Initialize structures */
	memset(ams_delta_mtd, 0, sizeof(struct mtd_info));
	memset(this, 0, sizeof(struct nand_chip));

	/* Link the private data with the MTD structure */
	ams_delta_mtd->priv = this;

<<<<<<< HEAD
<<<<<<< HEAD
	/*
	 * Don't try to request the memory region from here,
	 * it should have been already requested from the
	 * gpio-omap driver and requesting it again would fail.
	 */
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!request_mem_region(res->start, resource_size(res),
			dev_name(&pdev->dev))) {
		dev_err(&pdev->dev, "request_mem_region failed\n");
		err = -EBUSY;
		goto out_free;
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	io_base = ioremap(res->start, resource_size(res));
	if (io_base == NULL) {
		dev_err(&pdev->dev, "ioremap failed\n");
		err = -EIO;
<<<<<<< HEAD
<<<<<<< HEAD
		goto out_free;
=======
		goto out_release_io;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		goto out_release_io;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	this->priv = io_base;

	/* Set address of NAND IO lines */
	this->IO_ADDR_R = io_base + OMAP_MPUIO_INPUT_LATCH;
	this->IO_ADDR_W = io_base + OMAP_MPUIO_OUTPUT;
	this->read_byte = ams_delta_read_byte;
	this->write_buf = ams_delta_write_buf;
	this->read_buf = ams_delta_read_buf;
	this->verify_buf = ams_delta_verify_buf;
	this->cmd_ctrl = ams_delta_hwcontrol;
	if (gpio_request(AMS_DELTA_GPIO_PIN_NAND_RB, "nand_rdy") == 0) {
		this->dev_ready = ams_delta_nand_ready;
	} else {
		this->dev_ready = NULL;
		printk(KERN_NOTICE "Couldn't request gpio for Delta NAND ready.\n");
	}
	/* 25 us command delay time */
	this->chip_delay = 30;
	this->ecc.mode = NAND_ECC_SOFT;

	platform_set_drvdata(pdev, io_base);

	/* Set chip enabled, but  */
<<<<<<< HEAD
<<<<<<< HEAD
	err = gpio_request_array(_mandatory_gpio, ARRAY_SIZE(_mandatory_gpio));
	if (err)
		goto out_gpio;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ams_delta_latch2_write(NAND_MASK, AMS_DELTA_LATCH2_NAND_NRE |
					  AMS_DELTA_LATCH2_NAND_NWE |
					  AMS_DELTA_LATCH2_NAND_NCE |
					  AMS_DELTA_LATCH2_NAND_NWP);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Scan to find existence of the device */
	if (nand_scan(ams_delta_mtd, 1)) {
		err = -ENXIO;
		goto out_mtd;
	}

	/* Register the partitions */
	mtd_device_register(ams_delta_mtd, partition_info,
			    ARRAY_SIZE(partition_info));

	goto out;

 out_mtd:
<<<<<<< HEAD
<<<<<<< HEAD
	gpio_free_array(_mandatory_gpio, ARRAY_SIZE(_mandatory_gpio));
out_gpio:
	platform_set_drvdata(pdev, NULL);
	gpio_free(AMS_DELTA_GPIO_PIN_NAND_RB);
	iounmap(io_base);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	platform_set_drvdata(pdev, NULL);
	iounmap(io_base);
out_release_io:
	release_mem_region(res->start, resource_size(res));
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
out_free:
	kfree(ams_delta_mtd);
 out:
	return err;
}

/*
 * Clean up routine
 */
static int __devexit ams_delta_cleanup(struct platform_device *pdev)
{
	void __iomem *io_base = platform_get_drvdata(pdev);
<<<<<<< HEAD
<<<<<<< HEAD
=======
	struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct resource *res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Release resources, unregister device */
	nand_release(ams_delta_mtd);

<<<<<<< HEAD
<<<<<<< HEAD
	gpio_free_array(_mandatory_gpio, ARRAY_SIZE(_mandatory_gpio));
	gpio_free(AMS_DELTA_GPIO_PIN_NAND_RB);
	iounmap(io_base);
=======
	iounmap(io_base);
	release_mem_region(res->start, resource_size(res));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	iounmap(io_base);
	release_mem_region(res->start, resource_size(res));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Free the MTD device structure */
	kfree(ams_delta_mtd);

	return 0;
}

static struct platform_driver ams_delta_nand_driver = {
	.probe		= ams_delta_init,
	.remove		= __devexit_p(ams_delta_cleanup),
	.driver		= {
		.name	= "ams-delta-nand",
		.owner	= THIS_MODULE,
	},
};

<<<<<<< HEAD
<<<<<<< HEAD
module_platform_driver(ams_delta_nand_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init ams_delta_nand_init(void)
{
	return platform_driver_register(&ams_delta_nand_driver);
}
module_init(ams_delta_nand_init);

static void __exit ams_delta_nand_exit(void)
{
	platform_driver_unregister(&ams_delta_nand_driver);
}
module_exit(ams_delta_nand_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jonathan McDowell <noodles@earth.li>");
MODULE_DESCRIPTION("Glue layer for NAND flash on Amstrad E3 (Delta)");
