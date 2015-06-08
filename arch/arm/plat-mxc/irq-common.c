/*
 * Copyright (C) BitBox Ltd 2010
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA  02110-1301, USA.
 */

#include <linux/module.h>
#include <linux/irq.h>

#include "irq-common.h"

int imx_irq_set_priority(unsigned char irq, unsigned char prio)
{
<<<<<<< HEAD
	struct irq_chip_generic *gc;
	struct mxc_extra_irq *exirq;
=======
<<<<<<< HEAD
	struct irq_chip_generic *gc;
	struct mxc_extra_irq *exirq;
=======
	struct mxc_irq_chip *chip;
	struct irq_chip *base;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret;

	ret = -ENOSYS;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	gc = irq_get_chip_data(irq);
	if (gc && gc->private) {
		exirq = gc->private;
		if (exirq->set_priority)
			ret = exirq->set_priority(irq, prio);
<<<<<<< HEAD
=======
=======
	base = irq_get_chip(irq);
	if (base) {
		chip = container_of(base, struct mxc_irq_chip, base);
		if (chip->set_priority)
			ret = chip->set_priority(irq, prio);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	return ret;
}
EXPORT_SYMBOL(imx_irq_set_priority);

int mxc_set_irq_fiq(unsigned int irq, unsigned int type)
{
<<<<<<< HEAD
	struct irq_chip_generic *gc;
	struct mxc_extra_irq *exirq;
=======
<<<<<<< HEAD
	struct irq_chip_generic *gc;
	struct mxc_extra_irq *exirq;
=======
	struct mxc_irq_chip *chip;
	struct irq_chip *base;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret;

	ret = -ENOSYS;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	gc = irq_get_chip_data(irq);
	if (gc && gc->private) {
		exirq = gc->private;
		if (exirq->set_irq_fiq)
			ret = exirq->set_irq_fiq(irq, type);
<<<<<<< HEAD
=======
=======
	base = irq_get_chip(irq);
	if (base) {
		chip = container_of(base, struct mxc_irq_chip, base);
		if (chip->set_irq_fiq)
			ret = chip->set_irq_fiq(irq, type);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	return ret;
}
EXPORT_SYMBOL(mxc_set_irq_fiq);
