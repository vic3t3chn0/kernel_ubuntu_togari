#ifndef BCM63XX_GPIO_H
#define BCM63XX_GPIO_H

#include <linux/init.h>

int __init bcm63xx_gpio_init(void);

static inline unsigned long bcm63xx_gpio_count(void)
{
	switch (bcm63xx_get_cpu_id()) {
	case BCM6358_CPU_ID:
		return 40;
	case BCM6338_CPU_ID:
		return 8;
	case BCM6345_CPU_ID:
		return 16;
<<<<<<< HEAD
	case BCM6368_CPU_ID:
		return 38;
=======
<<<<<<< HEAD
	case BCM6368_CPU_ID:
		return 38;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	case BCM6348_CPU_ID:
	default:
		return 37;
	}
}

#define BCM63XX_GPIO_DIR_OUT	0x0
#define BCM63XX_GPIO_DIR_IN	0x1

#endif /* !BCM63XX_GPIO_H */
