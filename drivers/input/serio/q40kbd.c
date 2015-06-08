/*
 *  Copyright (c) 2000-2001 Vojtech Pavlik
 *
 *  Based on the work of:
 *	Richard Zidlicky <Richard.Zidlicky@stud.informatik.uni-erlangen.de>
 */

/*
 * Q40 PS/2 keyboard controller driver for Linux/m68k
 */

/*
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 * Should you need to contact me, the author, you can do so either by
 * e-mail - mail your message to <vojtech@ucw.cz>, or by paper mail:
 * Vojtech Pavlik, Simunkova 1594, Prague 8, 182 00 Czech Republic
 */

#include <linux/module.h>
#include <linux/init.h>
#include <linux/serio.h>
#include <linux/interrupt.h>
#include <linux/err.h>
#include <linux/bitops.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#include <asm/io.h>
#include <asm/uaccess.h>
#include <asm/q40_master.h>
#include <asm/irq.h>
#include <asm/q40ints.h>

<<<<<<< HEAD
<<<<<<< HEAD
#define DRV_NAME	"q40kbd"

MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Q40 PS/2 keyboard controller driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);

struct q40kbd {
	struct serio *port;
	spinlock_t lock;
};

static irqreturn_t q40kbd_interrupt(int irq, void *dev_id)
{
	struct q40kbd *q40kbd = dev_id;
	unsigned long flags;

	spin_lock_irqsave(&q40kbd->lock, flags);

	if (Q40_IRQ_KEYB_MASK & master_inb(INTERRUPT_REG))
		serio_interrupt(q40kbd->port, master_inb(KEYCODE_REG), 0);

	master_outb(-1, KEYBOARD_UNLOCK_REG);

	spin_unlock_irqrestore(&q40kbd->lock, flags);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
MODULE_AUTHOR("Vojtech Pavlik <vojtech@ucw.cz>");
MODULE_DESCRIPTION("Q40 PS/2 keyboard controller driver");
MODULE_LICENSE("GPL");

static DEFINE_SPINLOCK(q40kbd_lock);
static struct serio *q40kbd_port;
static struct platform_device *q40kbd_device;

static irqreturn_t q40kbd_interrupt(int irq, void *dev_id)
{
	unsigned long flags;

	spin_lock_irqsave(&q40kbd_lock, flags);

	if (Q40_IRQ_KEYB_MASK & master_inb(INTERRUPT_REG))
		serio_interrupt(q40kbd_port, master_inb(KEYCODE_REG), 0);

	master_outb(-1, KEYBOARD_UNLOCK_REG);

	spin_unlock_irqrestore(&q40kbd_lock, flags);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return IRQ_HANDLED;
}

/*
 * q40kbd_flush() flushes all data that may be in the keyboard buffers
 */

<<<<<<< HEAD
<<<<<<< HEAD
static void q40kbd_flush(struct q40kbd *q40kbd)
=======
static void q40kbd_flush(void)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static void q40kbd_flush(void)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int maxread = 100;
	unsigned long flags;

<<<<<<< HEAD
<<<<<<< HEAD
	spin_lock_irqsave(&q40kbd->lock, flags);
=======
	spin_lock_irqsave(&q40kbd_lock, flags);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	spin_lock_irqsave(&q40kbd_lock, flags);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	while (maxread-- && (Q40_IRQ_KEYB_MASK & master_inb(INTERRUPT_REG)))
		master_inb(KEYCODE_REG);

<<<<<<< HEAD
<<<<<<< HEAD
	spin_unlock_irqrestore(&q40kbd->lock, flags);
}

static void q40kbd_stop(void)
{
	master_outb(0, KEY_IRQ_ENABLE_REG);
	master_outb(-1, KEYBOARD_UNLOCK_REG);
=======
	spin_unlock_irqrestore(&q40kbd_lock, flags);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	spin_unlock_irqrestore(&q40kbd_lock, flags);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/*
 * q40kbd_open() is called when a port is open by the higher layer.
 * It allocates the interrupt and enables in in the chip.
 */

static int q40kbd_open(struct serio *port)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct q40kbd *q40kbd = port->port_data;

	q40kbd_flush(q40kbd);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	q40kbd_flush();

	if (request_irq(Q40_IRQ_KEYBOARD, q40kbd_interrupt, 0, "q40kbd", NULL)) {
		printk(KERN_ERR "q40kbd.c: Can't get irq %d.\n", Q40_IRQ_KEYBOARD);
		return -EBUSY;
	}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* off we go */
	master_outb(-1, KEYBOARD_UNLOCK_REG);
	master_outb(1, KEY_IRQ_ENABLE_REG);

	return 0;
}

static void q40kbd_close(struct serio *port)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct q40kbd *q40kbd = port->port_data;

	q40kbd_stop();
	q40kbd_flush(q40kbd);
}

static int __devinit q40kbd_probe(struct platform_device *pdev)
{
	struct q40kbd *q40kbd;
	struct serio *port;
	int error;

	q40kbd = kzalloc(sizeof(struct q40kbd), GFP_KERNEL);
	port = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!q40kbd || !port) {
		error = -ENOMEM;
		goto err_free_mem;
	}

	q40kbd->port = port;
	spin_lock_init(&q40kbd->lock);

	port->id.type = SERIO_8042;
	port->open = q40kbd_open;
	port->close = q40kbd_close;
	port->port_data = q40kbd;
	port->dev.parent = &pdev->dev;
	strlcpy(port->name, "Q40 Kbd Port", sizeof(port->name));
	strlcpy(port->phys, "Q40", sizeof(port->phys));

	q40kbd_stop();

	error = request_irq(Q40_IRQ_KEYBOARD, q40kbd_interrupt, 0,
			    DRV_NAME, q40kbd);
	if (error) {
		dev_err(&pdev->dev, "Can't get irq %d.\n", Q40_IRQ_KEYBOARD);
		goto err_free_mem;
	}

	serio_register_port(q40kbd->port);

	platform_set_drvdata(pdev, q40kbd);
	printk(KERN_INFO "serio: Q40 kbd registered\n");

	return 0;

err_free_mem:
	kfree(port);
	kfree(q40kbd);
	return error;
}

static int __devexit q40kbd_remove(struct platform_device *pdev)
{
	struct q40kbd *q40kbd = platform_get_drvdata(pdev);

	/*
	 * q40kbd_close() will be called as part of unregistering
	 * and will ensure that IRQ is turned off, so it is safe
	 * to unregister port first and free IRQ later.
	 */
	serio_unregister_port(q40kbd->port);
	free_irq(Q40_IRQ_KEYBOARD, q40kbd);
	kfree(q40kbd);

	platform_set_drvdata(pdev, NULL);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	master_outb(0, KEY_IRQ_ENABLE_REG);
	master_outb(-1, KEYBOARD_UNLOCK_REG);
	free_irq(Q40_IRQ_KEYBOARD, NULL);

	q40kbd_flush();
}

static int __devinit q40kbd_probe(struct platform_device *dev)
{
	q40kbd_port = kzalloc(sizeof(struct serio), GFP_KERNEL);
	if (!q40kbd_port)
		return -ENOMEM;

	q40kbd_port->id.type	= SERIO_8042;
	q40kbd_port->open	= q40kbd_open;
	q40kbd_port->close	= q40kbd_close;
	q40kbd_port->dev.parent	= &dev->dev;
	strlcpy(q40kbd_port->name, "Q40 Kbd Port", sizeof(q40kbd_port->name));
	strlcpy(q40kbd_port->phys, "Q40", sizeof(q40kbd_port->phys));

	serio_register_port(q40kbd_port);
	printk(KERN_INFO "serio: Q40 kbd registered\n");

	return 0;
}

static int __devexit q40kbd_remove(struct platform_device *dev)
{
	serio_unregister_port(q40kbd_port);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

static struct platform_driver q40kbd_driver = {
	.driver		= {
		.name	= "q40kbd",
		.owner	= THIS_MODULE,
	},
<<<<<<< HEAD
<<<<<<< HEAD
=======
	.probe		= q40kbd_probe,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	.probe		= q40kbd_probe,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.remove		= __devexit_p(q40kbd_remove),
};

static int __init q40kbd_init(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
	return platform_driver_probe(&q40kbd_driver, q40kbd_probe);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int error;

	if (!MACH_IS_Q40)
		return -ENODEV;

	error = platform_driver_register(&q40kbd_driver);
	if (error)
		return error;

	q40kbd_device = platform_device_alloc("q40kbd", -1);
	if (!q40kbd_device)
		goto err_unregister_driver;

	error = platform_device_add(q40kbd_device);
	if (error)
		goto err_free_device;

	return 0;

 err_free_device:
	platform_device_put(q40kbd_device);
 err_unregister_driver:
	platform_driver_unregister(&q40kbd_driver);
	return error;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static void __exit q40kbd_exit(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
	platform_device_unregister(q40kbd_device);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	platform_device_unregister(q40kbd_device);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	platform_driver_unregister(&q40kbd_driver);
}

module_init(q40kbd_init);
module_exit(q40kbd_exit);
