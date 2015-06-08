/*
 * Viper/Zeus PCMCIA support
 *   Copyright 2004 Arcom Control Systems
 *
 * Maintained by Marc Zyngier <maz@misterjones.org>
 *
 * Based on:
 *   iPAQ h2200 PCMCIA support
 *   Copyright 2004 Koen Kooi <koen@vestingbar.nl>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the main directory of this archive for
 * more details.
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/errno.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>

#include <pcmcia/ss.h>

#include <asm/irq.h>

#include <mach/arcom-pcmcia.h>

#include "soc_common.h"
#include "pxa2xx_base.h"

static struct platform_device *arcom_pcmcia_dev;

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct pcmcia_irqs irqs[] = {
	{
		.sock	= 0,
		.str	= "PCMCIA_CD",
	},
};

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static inline struct arcom_pcmcia_pdata *viper_get_pdata(void)
{
	return arcom_pcmcia_dev->dev.platform_data;
}

static int viper_pcmcia_hw_init(struct soc_pcmcia_socket *skt)
{
	struct arcom_pcmcia_pdata *pdata = viper_get_pdata();
	unsigned long flags;

<<<<<<< HEAD
<<<<<<< HEAD
	skt->stat[SOC_STAT_CD].gpio = pdata->cd_gpio;
	skt->stat[SOC_STAT_CD].name = "PCMCIA_CD";
	skt->stat[SOC_STAT_RDY].gpio = pdata->rdy_gpio;
	skt->stat[SOC_STAT_RDY].name = "CF ready";
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	skt->socket.pci_irq = gpio_to_irq(pdata->rdy_gpio);
	irqs[0].irq = gpio_to_irq(pdata->cd_gpio);

	if (gpio_request(pdata->cd_gpio, "CF detect"))
		goto err_request_cd;

	if (gpio_request(pdata->rdy_gpio, "CF ready"))
		goto err_request_rdy;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (gpio_request(pdata->pwr_gpio, "CF power"))
		goto err_request_pwr;

	local_irq_save(flags);

<<<<<<< HEAD
<<<<<<< HEAD
	if (gpio_direction_output(pdata->pwr_gpio, 0)) {
=======
	if (gpio_direction_output(pdata->pwr_gpio, 0) ||
	    gpio_direction_input(pdata->cd_gpio) ||
	    gpio_direction_input(pdata->rdy_gpio)) {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	if (gpio_direction_output(pdata->pwr_gpio, 0) ||
	    gpio_direction_input(pdata->cd_gpio) ||
	    gpio_direction_input(pdata->rdy_gpio)) {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		local_irq_restore(flags);
		goto err_dir;
	}

	local_irq_restore(flags);

<<<<<<< HEAD
<<<<<<< HEAD
	return 0;
=======
	return soc_pcmcia_request_irqs(skt, irqs, ARRAY_SIZE(irqs));
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	return soc_pcmcia_request_irqs(skt, irqs, ARRAY_SIZE(irqs));
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

err_dir:
	gpio_free(pdata->pwr_gpio);
err_request_pwr:
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	gpio_free(pdata->rdy_gpio);
err_request_rdy:
	gpio_free(pdata->cd_gpio);
err_request_cd:
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	dev_err(&arcom_pcmcia_dev->dev, "Failed to setup PCMCIA GPIOs\n");
	return -1;
}

/*
 * Release all resources.
 */
static void viper_pcmcia_hw_shutdown(struct soc_pcmcia_socket *skt)
{
	struct arcom_pcmcia_pdata *pdata = viper_get_pdata();

<<<<<<< HEAD
<<<<<<< HEAD
	gpio_free(pdata->pwr_gpio);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	soc_pcmcia_free_irqs(skt, irqs, ARRAY_SIZE(irqs));
	gpio_free(pdata->pwr_gpio);
	gpio_free(pdata->rdy_gpio);
	gpio_free(pdata->cd_gpio);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void viper_pcmcia_socket_state(struct soc_pcmcia_socket *skt,
				      struct pcmcia_state *state)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct arcom_pcmcia_pdata *pdata = viper_get_pdata();

	state->detect = !gpio_get_value(pdata->cd_gpio);
	state->ready  = !!gpio_get_value(pdata->rdy_gpio);
	state->bvd1   = 1;
	state->bvd2   = 1;
	state->wrprot = 0;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	state->vs_3v  = 1; /* Can only apply 3.3V */
	state->vs_Xv  = 0;
}

static int viper_pcmcia_configure_socket(struct soc_pcmcia_socket *skt,
					 const socket_state_t *state)
{
	struct arcom_pcmcia_pdata *pdata = viper_get_pdata();

	/* Silently ignore Vpp, output enable, speaker enable. */
	pdata->reset(state->flags & SS_RESET);

	/* Apply socket voltage */
	switch (state->Vcc) {
	case 0:
		gpio_set_value(pdata->pwr_gpio, 0);
		break;
	case 33:
		gpio_set_value(pdata->pwr_gpio, 1);
		break;
	default:
		dev_err(&arcom_pcmcia_dev->dev, "Unsupported Vcc:%d\n", state->Vcc);
		return -1;
	}

	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static void viper_pcmcia_socket_init(struct soc_pcmcia_socket *skt)
{
}

static void viper_pcmcia_socket_suspend(struct soc_pcmcia_socket *skt)
{
}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct pcmcia_low_level viper_pcmcia_ops = {
	.owner          	= THIS_MODULE,
	.hw_init        	= viper_pcmcia_hw_init,
	.hw_shutdown		= viper_pcmcia_hw_shutdown,
	.socket_state		= viper_pcmcia_socket_state,
	.configure_socket	= viper_pcmcia_configure_socket,
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.socket_init		= viper_pcmcia_socket_init,
	.socket_suspend		= viper_pcmcia_socket_suspend,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.socket_init		= viper_pcmcia_socket_init,
	.socket_suspend		= viper_pcmcia_socket_suspend,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.nr         		= 1,
};

static struct platform_device *viper_pcmcia_device;

static int viper_pcmcia_probe(struct platform_device *pdev)
{
	int ret;

	/* I can't imagine more than one device, but you never know... */
	if (arcom_pcmcia_dev)
		return -EEXIST;

	if (!pdev->dev.platform_data)
		return -EINVAL;

	viper_pcmcia_device = platform_device_alloc("pxa2xx-pcmcia", -1);
	if (!viper_pcmcia_device)
		return -ENOMEM;

	arcom_pcmcia_dev = pdev;

	viper_pcmcia_device->dev.parent = &pdev->dev;

	ret = platform_device_add_data(viper_pcmcia_device,
				       &viper_pcmcia_ops,
				       sizeof(viper_pcmcia_ops));

	if (!ret)
		ret = platform_device_add(viper_pcmcia_device);

	if (ret) {
		platform_device_put(viper_pcmcia_device);
		arcom_pcmcia_dev = NULL;
	}

	return ret;
}

static int viper_pcmcia_remove(struct platform_device *pdev)
{
	platform_device_unregister(viper_pcmcia_device);
	arcom_pcmcia_dev = NULL;
	return 0;
}

static struct platform_device_id viper_pcmcia_id_table[] = {
	{ .name = "viper-pcmcia", },
	{ .name = "zeus-pcmcia",  },
	{ },
};

static struct platform_driver viper_pcmcia_driver = {
	.probe		= viper_pcmcia_probe,
	.remove		= viper_pcmcia_remove,
	.driver		= {
		.name	= "arcom-pcmcia",
		.owner	= THIS_MODULE,
	},
	.id_table	= viper_pcmcia_id_table,
};

<<<<<<< HEAD
<<<<<<< HEAD
module_platform_driver(viper_pcmcia_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init viper_pcmcia_init(void)
{
	return platform_driver_register(&viper_pcmcia_driver);
}

static void __exit viper_pcmcia_exit(void)
{
	return platform_driver_unregister(&viper_pcmcia_driver);
}

module_init(viper_pcmcia_init);
module_exit(viper_pcmcia_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_DEVICE_TABLE(platform, viper_pcmcia_id_table);
MODULE_LICENSE("GPL");
