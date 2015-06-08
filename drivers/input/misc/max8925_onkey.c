/**
<<<<<<< HEAD
<<<<<<< HEAD
 * MAX8925 ONKEY driver
=======
 * max8925_onkey.c - MAX8925 ONKEY driver
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * max8925_onkey.c - MAX8925 ONKEY driver
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Copyright (C) 2009 Marvell International Ltd.
 *      Haojian Zhuang <haojian.zhuang@marvell.com>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License. See the file "COPYING" in the main directory of this
 * archive for more details.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/interrupt.h>
#include <linux/mfd/max8925.h>
#include <linux/slab.h>

#define SW_INPUT		(1 << 7)	/* 0/1 -- up/down */
#define HARDRESET_EN		(1 << 7)
#define PWREN_EN		(1 << 7)

struct max8925_onkey_info {
	struct input_dev	*idev;
	struct i2c_client	*i2c;
	struct device		*dev;
<<<<<<< HEAD
<<<<<<< HEAD
	unsigned int		irq[2];
=======
	int			irq[2];
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	int			irq[2];
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/*
 * MAX8925 gives us an interrupt when ONKEY is pressed or released.
 * max8925_set_bits() operates I2C bus and may sleep. So implement
 * it in thread IRQ handler.
 */
static irqreturn_t max8925_onkey_handler(int irq, void *data)
{
	struct max8925_onkey_info *info = data;
<<<<<<< HEAD
<<<<<<< HEAD
	int state;

	state = max8925_reg_read(info->i2c, MAX8925_ON_OFF_STATUS);

	input_report_key(info->idev, KEY_POWER, state & SW_INPUT);
	input_sync(info->idev);

	dev_dbg(info->dev, "onkey state:%d\n", state);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret, event;

	ret = max8925_reg_read(info->i2c, MAX8925_ON_OFF_STATUS);
	if (ret & SW_INPUT)
		event = 1;
	else
		event = 0;
	input_report_key(info->idev, KEY_POWER, event);
	input_sync(info->idev);

	dev_dbg(info->dev, "onkey event:%d\n", event);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Enable hardreset to halt if system isn't shutdown on time */
	max8925_set_bits(info->i2c, MAX8925_SYSENSEL,
			 HARDRESET_EN, HARDRESET_EN);

	return IRQ_HANDLED;
}

static int __devinit max8925_onkey_probe(struct platform_device *pdev)
{
	struct max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);
	struct max8925_onkey_info *info;
<<<<<<< HEAD
<<<<<<< HEAD
	struct input_dev *input;
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int irq[2], error;

	irq[0] = platform_get_irq(pdev, 0);
	if (irq[0] < 0) {
		dev_err(&pdev->dev, "No IRQ resource!\n");
		return -EINVAL;
	}
<<<<<<< HEAD
<<<<<<< HEAD

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	irq[1] = platform_get_irq(pdev, 1);
	if (irq[1] < 0) {
		dev_err(&pdev->dev, "No IRQ resource!\n");
		return -EINVAL;
	}

	info = kzalloc(sizeof(struct max8925_onkey_info), GFP_KERNEL);
<<<<<<< HEAD
<<<<<<< HEAD
	input = input_allocate_device();
	if (!info || !input) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	info->idev = input;
	info->i2c = chip->i2c;
	info->dev = &pdev->dev;
	info->irq[0] = irq[0];
	info->irq[1] = irq[1];

	input->name = "max8925_on";
	input->phys = "max8925_on/input0";
	input->id.bustype = BUS_I2C;
	input->dev.parent = &pdev->dev;
	input_set_capability(input, EV_KEY, KEY_POWER);

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (!info)
		return -ENOMEM;

	info->i2c = chip->i2c;
	info->dev = &pdev->dev;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	irq[0] += chip->irq_base;
	irq[1] += chip->irq_base;

	error = request_threaded_irq(irq[0], NULL, max8925_onkey_handler,
				     IRQF_ONESHOT, "onkey-down", info);
	if (error < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			irq[0], error);
<<<<<<< HEAD
<<<<<<< HEAD
		goto err_free_mem;
	}

=======
		goto out;
	}
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		goto out;
	}
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	error = request_threaded_irq(irq[1], NULL, max8925_onkey_handler,
				     IRQF_ONESHOT, "onkey-up", info);
	if (error < 0) {
		dev_err(chip->dev, "Failed to request IRQ: #%d: %d\n",
			irq[1], error);
<<<<<<< HEAD
<<<<<<< HEAD
		goto err_free_irq0;
	}

	error = input_register_device(info->idev);
	if (error) {
		dev_err(chip->dev, "Can't register input device: %d\n", error);
		goto err_free_irq1;
	}

	platform_set_drvdata(pdev, info);
	device_init_wakeup(&pdev->dev, 1);

	return 0;

err_free_irq1:
	free_irq(irq[1], info);
err_free_irq0:
	free_irq(irq[0], info);
err_free_mem:
	input_free_device(input);
	kfree(info);

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		goto out_irq;
	}

	info->idev = input_allocate_device();
	if (!info->idev) {
		dev_err(chip->dev, "Failed to allocate input dev\n");
		error = -ENOMEM;
		goto out_input;
	}

	info->idev->name = "max8925_on";
	info->idev->phys = "max8925_on/input0";
	info->idev->id.bustype = BUS_I2C;
	info->idev->dev.parent = &pdev->dev;
	info->irq[0] = irq[0];
	info->irq[1] = irq[1];
	info->idev->evbit[0] = BIT_MASK(EV_KEY);
	info->idev->keybit[BIT_WORD(KEY_POWER)] = BIT_MASK(KEY_POWER);


	error = input_register_device(info->idev);
	if (error) {
		dev_err(chip->dev, "Can't register input device: %d\n", error);
		goto out_reg;
	}

	platform_set_drvdata(pdev, info);

	return 0;

out_reg:
	input_free_device(info->idev);
out_input:
	free_irq(info->irq[1], info);
out_irq:
	free_irq(info->irq[0], info);
out:
	kfree(info);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return error;
}

static int __devexit max8925_onkey_remove(struct platform_device *pdev)
{
	struct max8925_onkey_info *info = platform_get_drvdata(pdev);
<<<<<<< HEAD
<<<<<<< HEAD
	struct max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);

	free_irq(info->irq[0] + chip->irq_base, info);
	free_irq(info->irq[1] + chip->irq_base, info);
=======

	free_irq(info->irq[0], info);
	free_irq(info->irq[1], info);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

	free_irq(info->irq[0], info);
	free_irq(info->irq[1], info);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	input_unregister_device(info->idev);
	kfree(info);

	platform_set_drvdata(pdev, NULL);

	return 0;
}

<<<<<<< HEAD
<<<<<<< HEAD
#ifdef CONFIG_PM_SLEEP
static int max8925_onkey_suspend(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct max8925_onkey_info *info = platform_get_drvdata(pdev);
	struct max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);

	if (device_may_wakeup(dev)) {
		chip->wakeup_flag |= 1 << info->irq[0];
		chip->wakeup_flag |= 1 << info->irq[1];
	}

	return 0;
}

static int max8925_onkey_resume(struct device *dev)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct max8925_onkey_info *info = platform_get_drvdata(pdev);
	struct max8925_chip *chip = dev_get_drvdata(pdev->dev.parent);

	if (device_may_wakeup(dev)) {
		chip->wakeup_flag &= ~(1 << info->irq[0]);
		chip->wakeup_flag &= ~(1 << info->irq[1]);
	}

	return 0;
}
#endif

static SIMPLE_DEV_PM_OPS(max8925_onkey_pm_ops, max8925_onkey_suspend, max8925_onkey_resume);

=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct platform_driver max8925_onkey_driver = {
	.driver		= {
		.name	= "max8925-onkey",
		.owner	= THIS_MODULE,
<<<<<<< HEAD
<<<<<<< HEAD
		.pm	= &max8925_onkey_pm_ops,
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	},
	.probe		= max8925_onkey_probe,
	.remove		= __devexit_p(max8925_onkey_remove),
};
<<<<<<< HEAD
<<<<<<< HEAD
module_platform_driver(max8925_onkey_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static int __init max8925_onkey_init(void)
{
	return platform_driver_register(&max8925_onkey_driver);
}
module_init(max8925_onkey_init);

static void __exit max8925_onkey_exit(void)
{
	platform_driver_unregister(&max8925_onkey_driver);
}
module_exit(max8925_onkey_exit);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_DESCRIPTION("Maxim MAX8925 ONKEY driver");
MODULE_AUTHOR("Haojian Zhuang <haojian.zhuang@marvell.com>");
MODULE_LICENSE("GPL");
