/*
 * Gemini gpiolib specific defines
 *
 * Copyright (C) 2008-2009 Paulius Zaleckas <paulius.zaleckas@teltonika.lt>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#ifndef __MACH_GPIO_H__
#define __MACH_GPIO_H__

#include <mach/irqs.h>
<<<<<<< HEAD
=======
#include <asm-generic/gpio.h>

#define gpio_get_value	__gpio_get_value
#define gpio_set_value	__gpio_set_value
#define gpio_cansleep	__gpio_cansleep
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

#define gpio_to_irq(x)	((x) + GPIO_IRQ_BASE)
#define irq_to_gpio(x)	((x) - GPIO_IRQ_BASE)

#endif /* __MACH_GPIO_H__ */
