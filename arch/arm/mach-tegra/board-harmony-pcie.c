/*
 * arch/arm/mach-tegra/board-harmony-pcie.c
 *
 * Copyright (C) 2010 CompuLab, Ltd.
 * Mike Rapoport <mike@compulab.co.il>
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/err.h>
#include <linux/regulator/consumer.h>

#include <asm/mach-types.h>

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include "board.h"
#include "board-harmony.h"

#ifdef CONFIG_TEGRA_PCI

<<<<<<< HEAD
=======
=======
#include <mach/pinmux.h>
#include "board.h"

#ifdef CONFIG_TEGRA_PCI

/* GPIO 3 of the PMIC */
#define EN_VDD_1V05_GPIO	(TEGRA_NR_GPIOS + 2)

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int __init harmony_pcie_init(void)
{
	struct regulator *regulator = NULL;
	int err;

	if (!machine_is_harmony())
		return 0;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	err = gpio_request(TEGRA_GPIO_EN_VDD_1V05_GPIO, "EN_VDD_1V05");
	if (err)
		return err;

	gpio_direction_output(TEGRA_GPIO_EN_VDD_1V05_GPIO, 1);
<<<<<<< HEAD
=======
=======
	err = gpio_request(EN_VDD_1V05_GPIO, "EN_VDD_1V05");
	if (err)
		return err;

	gpio_direction_output(EN_VDD_1V05_GPIO, 1);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	regulator = regulator_get(NULL, "pex_clk");
	if (IS_ERR_OR_NULL(regulator))
		goto err_reg;

	regulator_enable(regulator);

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	tegra_pinmux_set_tristate(TEGRA_PINGROUP_GPV, TEGRA_TRI_NORMAL);
	tegra_pinmux_set_tristate(TEGRA_PINGROUP_SLXA, TEGRA_TRI_NORMAL);
	tegra_pinmux_set_tristate(TEGRA_PINGROUP_SLXK, TEGRA_TRI_NORMAL);

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	err = tegra_pcie_init(true, true);
	if (err)
		goto err_pcie;

	return 0;

err_pcie:
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	regulator_disable(regulator);
	regulator_put(regulator);
err_reg:
	gpio_free(TEGRA_GPIO_EN_VDD_1V05_GPIO);
<<<<<<< HEAD
=======
=======
	tegra_pinmux_set_tristate(TEGRA_PINGROUP_GPV, TEGRA_TRI_TRISTATE);
	tegra_pinmux_set_tristate(TEGRA_PINGROUP_SLXA, TEGRA_TRI_TRISTATE);
	tegra_pinmux_set_tristate(TEGRA_PINGROUP_SLXK, TEGRA_TRI_TRISTATE);

	regulator_disable(regulator);
	regulator_put(regulator);
err_reg:
	gpio_free(EN_VDD_1V05_GPIO);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return err;
}

/* PCI should be initialized after I2C, mfd and regulators */
subsys_initcall_sync(harmony_pcie_init);

#endif
