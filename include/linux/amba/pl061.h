#include <linux/types.h>

/* platform data for the PL061 GPIO driver */

struct pl061_platform_data {
	/* number of the first GPIO */
	unsigned	gpio_base;

	/* number of the first IRQ.
<<<<<<< HEAD
	 * If the IRQ functionality in not desired this must be set to 0.
=======
<<<<<<< HEAD
	 * If the IRQ functionality in not desired this must be set to 0.
=======
	 * If the IRQ functionality in not desired this must be set to
	 * (unsigned) -1.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	 */
	unsigned	irq_base;

	u8		directions;	/* startup directions, 1: out, 0: in */
	u8		values;		/* startup values */
};
