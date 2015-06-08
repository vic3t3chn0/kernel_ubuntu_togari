#ifndef ARCH_ARM_PLAT_OMAP4_KEYPAD_H
#define ARCH_ARM_PLAT_OMAP4_KEYPAD_H

<<<<<<< HEAD
extern int omap4_keyboard_init(struct omap4_keypad_platform_data *,
				struct omap_board_data *);
=======
<<<<<<< HEAD
extern int omap4_keyboard_init(struct omap4_keypad_platform_data *,
				struct omap_board_data *);
=======
#include <linux/input/matrix_keypad.h>

struct omap4_keypad_platform_data {
	const struct matrix_keymap_data *keymap_data;

	u8 rows;
	u8 cols;
};

extern int omap4_keyboard_init(struct omap4_keypad_platform_data *);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
