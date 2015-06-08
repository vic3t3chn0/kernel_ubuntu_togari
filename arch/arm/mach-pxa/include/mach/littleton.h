#ifndef __ASM_ARCH_LITTLETON_H
#define __ASM_ARCH_LITTLETON_H

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#include <mach/gpio.h>

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define LITTLETON_ETH_PHYS	0x30000000

#define LITTLETON_GPIO_LCD_CS	(17)

<<<<<<< HEAD
#define EXT0_GPIO_BASE	(PXA_NR_BUILTIN_GPIO)
=======
<<<<<<< HEAD
#define EXT0_GPIO_BASE	(PXA_NR_BUILTIN_GPIO)
=======
#define EXT0_GPIO_BASE	(NR_BUILTIN_GPIO)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define EXT0_GPIO(x)	(EXT0_GPIO_BASE + (x))

#define LITTLETON_NR_IRQS	(IRQ_BOARD_START + 8)

#endif /* __ASM_ARCH_LITTLETON_H */
