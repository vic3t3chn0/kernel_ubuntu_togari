/*
 * include/linux/mmc/sdhci-spear.h
 *
 * SDHCI declarations specific to ST SPEAr platform
 *
 * Copyright (C) 2010 ST Microelectronics
 * Viresh Kumar<viresh.kumar@st.com>
 *
 * This file is licensed under the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

<<<<<<< HEAD
#ifndef LINUX_MMC_SDHCI_SPEAR_H
#define LINUX_MMC_SDHCI_SPEAR_H
=======
<<<<<<< HEAD
#ifndef LINUX_MMC_SDHCI_SPEAR_H
#define LINUX_MMC_SDHCI_SPEAR_H
=======
#ifndef MMC_SDHCI_SPEAR_H
#define MMC_SDHCI_SPEAR_H
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <linux/platform_device.h>
/*
 * struct sdhci_plat_data: spear sdhci platform data structure
 *
 * @card_power_gpio: gpio pin for enabling/disabling power to sdhci socket
 * @power_active_high: if set, enable power to sdhci socket by setting
 *			card_power_gpio
 * @power_always_enb: If set, then enable power on probe, otherwise enable only
 *			on card insertion and disable on card removal.
 * card_int_gpio: gpio pin used for card detection
 */
struct sdhci_plat_data {
	int card_power_gpio;
	int power_active_high;
	int power_always_enb;
	int card_int_gpio;
};

/* This function is used to set platform_data field of pdev->dev */
static inline void
sdhci_set_plat_data(struct platform_device *pdev, struct sdhci_plat_data *data)
{
	pdev->dev.platform_data = data;
}

<<<<<<< HEAD
#endif /* LINUX_MMC_SDHCI_SPEAR_H */
=======
<<<<<<< HEAD
#endif /* LINUX_MMC_SDHCI_SPEAR_H */
=======
#endif /* MMC_SDHCI_SPEAR_H */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
