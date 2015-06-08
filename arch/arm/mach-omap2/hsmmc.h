/*
 * MMC definitions for OMAP2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

struct mmc_card;

struct omap2_hsmmc_info {
	u8	mmc;		/* controller 1/2/3 */
	u32	caps;		/* 4/8 wires and any additional host
				 * capabilities OR'd (ref. linux/mmc/host.h) */
<<<<<<< HEAD
	u32	pm_caps;	/* PM capabilities */
=======
<<<<<<< HEAD
	u32	pm_caps;	/* PM capabilities */
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	bool	transceiver;	/* MMC-2 option */
	bool	ext_clock;	/* use external pin for input clock */
	bool	cover_only;	/* No card detect - just cover switch */
	bool	nonremovable;	/* Nonremovable e.g. eMMC */
	bool	power_saving;	/* Try to sleep or power off when possible */
	bool	no_off;		/* power_saving and power is not to go off */
	bool	no_off_init;	/* no power off when not in MMC sleep state */
	bool	vcc_aux_disable_is_sleep; /* Regulator off remapped to sleep */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	bool	deferred;	/* mmc needs a deferred probe */
	int	gpio_cd;	/* or -EINVAL */
	int	gpio_wp;	/* or -EINVAL */
	char	*name;		/* or NULL for default */
	struct platform_device *pdev;	/* mmc controller instance */
	int	ocr_mask;	/* temporary HACK */
	int	max_freq;	/* maximum clock, if constrained by external
				 * circuitry, or 0 for default */
<<<<<<< HEAD
=======
=======
	int	gpio_cd;	/* or -EINVAL */
	int	gpio_wp;	/* or -EINVAL */
	char	*name;		/* or NULL for default */
	struct device *dev;	/* returned: pointer to mmc adapter */
	int	ocr_mask;	/* temporary HACK */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Remux (pad configuration) when powering on/off */
	void (*remux)(struct device *dev, int slot, int power_on);
	/* init some special card */
	void (*init_card)(struct mmc_card *card);
};

#if defined(CONFIG_MMC_OMAP_HS) || defined(CONFIG_MMC_OMAP_HS_MODULE)

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void omap_hsmmc_init(struct omap2_hsmmc_info *);
void omap_hsmmc_late_init(struct omap2_hsmmc_info *);

#else

static inline void omap_hsmmc_init(struct omap2_hsmmc_info *info)
{
}

static inline void omap_hsmmc_late_init(struct omap2_hsmmc_info *info)
<<<<<<< HEAD
=======
=======
void omap2_hsmmc_init(struct omap2_hsmmc_info *);

#else

static inline void omap2_hsmmc_init(struct omap2_hsmmc_info *info)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
}

#endif
