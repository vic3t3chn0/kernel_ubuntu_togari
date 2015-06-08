/*
 * linux/arch/arm/mach-omap2/mcbsp.c
 *
 * Copyright (C) 2008 Instituto Nokia de Tecnologia
 * Contact: Eduardo Valentin <eduardo.valentin@indt.org.br>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Multichannel mode not supported.
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/clk.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/slab.h>

#include <mach/irqs.h>
#include <plat/dma.h>
#include <plat/cpu.h>
#include <plat/mcbsp.h>
#include <plat/omap_device.h>
#include <linux/pm_runtime.h>

#include "control.h"

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * FIXME: Find a mechanism to enable/disable runtime the McBSP ICLK autoidle.
 * Sidetone needs non-gated ICLK and sidetone autoidle is broken.
 */
#include "cm2xxx_3xxx.h"
#include "cm-regbits-34xx.h"

/* McBSP1 internal signal muxing function for OMAP2/3 */
static int omap2_mcbsp1_mux_rx_clk(struct device *dev, const char *signal,
				   const char *src)
<<<<<<< HEAD
=======
=======
/* McBSP internal signal muxing functions */

void omap2_mcbsp1_mux_clkr_src(u8 mux)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	u32 v;

	v = omap_ctrl_readl(OMAP2_CONTROL_DEVCONF0);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!strcmp(signal, "clkr")) {
		if (!strcmp(src, "clkr"))
			v &= ~OMAP2_MCBSP1_CLKR_MASK;
		else if (!strcmp(src, "clkx"))
			v |= OMAP2_MCBSP1_CLKR_MASK;
		else
			return -EINVAL;
	} else if (!strcmp(signal, "fsr")) {
		if (!strcmp(src, "fsr"))
			v &= ~OMAP2_MCBSP1_FSR_MASK;
		else if (!strcmp(src, "fsx"))
			v |= OMAP2_MCBSP1_FSR_MASK;
		else
			return -EINVAL;
	} else {
		return -EINVAL;
	}

	omap_ctrl_writel(v, OMAP2_CONTROL_DEVCONF0);

	return 0;
}

/* McBSP4 internal signal muxing function for OMAP4 */
#define OMAP4_CONTROL_MCBSPLP_ALBCTRLRX_FSX	(1 << 31)
#define OMAP4_CONTROL_MCBSPLP_ALBCTRLRX_CLKX	(1 << 30)
static int omap4_mcbsp4_mux_rx_clk(struct device *dev, const char *signal,
				   const char *src)
{
	u32 v;

	/*
	 * In CONTROL_MCBSPLP register only bit 30 (CLKR mux), and bit 31 (FSR
	 * mux) is used */
	v = omap4_ctrl_pad_readl(OMAP4_CTRL_MODULE_PAD_CORE_CONTROL_MCBSPLP);

	if (!strcmp(signal, "clkr")) {
		if (!strcmp(src, "clkr"))
			v &= ~OMAP4_CONTROL_MCBSPLP_ALBCTRLRX_CLKX;
		else if (!strcmp(src, "clkx"))
			v |= OMAP4_CONTROL_MCBSPLP_ALBCTRLRX_CLKX;
		else
			return -EINVAL;
	} else if (!strcmp(signal, "fsr")) {
		if (!strcmp(src, "fsr"))
			v &= ~OMAP4_CONTROL_MCBSPLP_ALBCTRLRX_FSX;
		else if (!strcmp(src, "fsx"))
			v |= OMAP4_CONTROL_MCBSPLP_ALBCTRLRX_FSX;
		else
			return -EINVAL;
	} else {
		return -EINVAL;
	}

	omap4_ctrl_pad_writel(v, OMAP4_CTRL_MODULE_PAD_CORE_CONTROL_MCBSPLP);

	return 0;
}

/* McBSP CLKS source switching function */
static int omap2_mcbsp_set_clk_src(struct device *dev, struct clk *clk,
				   const char *src)
{
<<<<<<< HEAD
=======
=======
	if (mux == CLKR_SRC_CLKR)
		v &= ~OMAP2_MCBSP1_CLKR_MASK;
	else if (mux == CLKR_SRC_CLKX)
		v |= OMAP2_MCBSP1_CLKR_MASK;
	omap_ctrl_writel(v, OMAP2_CONTROL_DEVCONF0);
}
EXPORT_SYMBOL(omap2_mcbsp1_mux_clkr_src);

void omap2_mcbsp1_mux_fsr_src(u8 mux)
{
	u32 v;

	v = omap_ctrl_readl(OMAP2_CONTROL_DEVCONF0);
	if (mux == FSR_SRC_FSR)
		v &= ~OMAP2_MCBSP1_FSR_MASK;
	else if (mux == FSR_SRC_FSX)
		v |= OMAP2_MCBSP1_FSR_MASK;
	omap_ctrl_writel(v, OMAP2_CONTROL_DEVCONF0);
}
EXPORT_SYMBOL(omap2_mcbsp1_mux_fsr_src);

/* McBSP CLKS source switching function */

int omap2_mcbsp_set_clks_src(u8 id, u8 fck_src_id)
{
	struct omap_mcbsp *mcbsp;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct clk *fck_src;
	char *fck_src_name;
	int r;

<<<<<<< HEAD
	if (!strcmp(src, "clks_ext"))
		fck_src_name = "pad_fck";
	else if (!strcmp(src, "clks_fclk"))
=======
<<<<<<< HEAD
	if (!strcmp(src, "clks_ext"))
		fck_src_name = "pad_fck";
	else if (!strcmp(src, "clks_fclk"))
=======
	if (!omap_mcbsp_check_valid_id(id)) {
		pr_err("%s: Invalid id (%d)\n", __func__, id + 1);
		return -EINVAL;
	}
	mcbsp = id_to_mcbsp_ptr(id);

	if (fck_src_id == MCBSP_CLKS_PAD_SRC)
		fck_src_name = "pad_fck";
	else if (fck_src_id == MCBSP_CLKS_PRCM_SRC)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		fck_src_name = "prcm_fck";
	else
		return -EINVAL;

<<<<<<< HEAD
	fck_src = clk_get(dev, fck_src_name);
=======
<<<<<<< HEAD
	fck_src = clk_get(dev, fck_src_name);
=======
	fck_src = clk_get(mcbsp->dev, fck_src_name);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (IS_ERR_OR_NULL(fck_src)) {
		pr_err("omap-mcbsp: %s: could not clk_get() %s\n", "clks",
		       fck_src_name);
		return -EINVAL;
	}

<<<<<<< HEAD
	pm_runtime_put_sync(dev);

	r = clk_set_parent(clk, fck_src);
=======
<<<<<<< HEAD
	pm_runtime_put_sync(dev);

	r = clk_set_parent(clk, fck_src);
=======
	pm_runtime_put_sync(mcbsp->dev);

	r = clk_set_parent(mcbsp->fclk, fck_src);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (IS_ERR_VALUE(r)) {
		pr_err("omap-mcbsp: %s: could not clk_set_parent() to %s\n",
		       "clks", fck_src_name);
		clk_put(fck_src);
		return -EINVAL;
	}

<<<<<<< HEAD
	pm_runtime_get_sync(dev);
=======
<<<<<<< HEAD
	pm_runtime_get_sync(dev);
=======
	pm_runtime_get_sync(mcbsp->dev);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	clk_put(fck_src);

	return 0;
}
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static int omap3_enable_st_clock(unsigned int id, bool enable)
{
	unsigned int w;

	/*
	 * Sidetone uses McBSP ICLK - which must not idle when sidetones
	 * are enabled or sidetones start sounding ugly.
	 */
	w = omap2_cm_read_mod_reg(OMAP3430_PER_MOD, CM_AUTOIDLE);
	if (enable)
		w &= ~(1 << (id - 2));
	else
		w |= 1 << (id - 2);
	omap2_cm_write_mod_reg(w, OMAP3430_PER_MOD, CM_AUTOIDLE);

	return 0;
}

static int __init omap_init_mcbsp(struct omap_hwmod *oh, void *unused)
<<<<<<< HEAD
=======
=======
EXPORT_SYMBOL(omap2_mcbsp_set_clks_src);

struct omap_device_pm_latency omap2_mcbsp_latency[] = {
	{
		.deactivate_func = omap_device_idle_hwmods,
		.activate_func   = omap_device_enable_hwmods,
		.flags = OMAP_DEVICE_LATENCY_AUTO_ADJUST,
	},
};

static int omap_init_mcbsp(struct omap_hwmod *oh, void *unused)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	int id, count = 1;
	char *name = "omap-mcbsp";
	struct omap_hwmod *oh_device[2];
	struct omap_mcbsp_platform_data *pdata = NULL;
<<<<<<< HEAD
	struct platform_device *pdev;
=======
<<<<<<< HEAD
	struct platform_device *pdev;
=======
	struct omap_device *od;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	sscanf(oh->name, "mcbsp%d", &id);

	pdata = kzalloc(sizeof(struct omap_mcbsp_platform_data), GFP_KERNEL);
	if (!pdata) {
		pr_err("%s: No memory for mcbsp\n", __func__);
		return -ENOMEM;
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	pdata->reg_step = 4;
	if (oh->class->rev < MCBSP_CONFIG_TYPE2) {
		pdata->reg_size = 2;
	} else {
		pdata->reg_size = 4;
		pdata->has_ccr = true;
	}
	pdata->set_clk_src = omap2_mcbsp_set_clk_src;

	/* On OMAP2/3 the McBSP1 port has 6 pin configuration */
	if (id == 1 && oh->class->rev < MCBSP_CONFIG_TYPE4)
		pdata->mux_signal = omap2_mcbsp1_mux_rx_clk;

	/* On OMAP4 the McBSP4 port has 6 pin configuration */
	if (id == 4 && oh->class->rev == MCBSP_CONFIG_TYPE4)
		pdata->mux_signal = omap4_mcbsp4_mux_rx_clk;
<<<<<<< HEAD
=======
=======
	pdata->mcbsp_config_type = oh->class->rev;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (oh->class->rev == MCBSP_CONFIG_TYPE3) {
		if (id == 2)
			/* The FIFO has 1024 + 256 locations */
			pdata->buffer_size = 0x500;
		else
			/* The FIFO has 128 locations */
			pdata->buffer_size = 0x80;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	} else if (oh->class->rev == MCBSP_CONFIG_TYPE4) {
		/* The FIFO has 128 locations for all instances */
		pdata->buffer_size = 0x80;
	}

	if (oh->class->rev >= MCBSP_CONFIG_TYPE3)
		pdata->has_wakeup = true;

<<<<<<< HEAD
=======
=======
	}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	oh_device[0] = oh;

	if (oh->dev_attr) {
		oh_device[1] = omap_hwmod_lookup((
		(struct omap_mcbsp_dev_attr *)(oh->dev_attr))->sidetone);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		pdata->enable_st_clock = omap3_enable_st_clock;
		count++;
	}
	pdev = omap_device_build_ss(name, id, oh_device, count, pdata,
				sizeof(*pdata), NULL, 0, false);
	kfree(pdata);
	if (IS_ERR(pdev))  {
		pr_err("%s: Can't build omap_device for %s:%s.\n", __func__,
					name, oh->name);
		return PTR_ERR(pdev);
	}
<<<<<<< HEAD
=======
=======
		count++;
	}
	od = omap_device_build_ss(name, id, oh_device, count, pdata,
				sizeof(*pdata), omap2_mcbsp_latency,
				ARRAY_SIZE(omap2_mcbsp_latency), false);
	kfree(pdata);
	if (IS_ERR(od))  {
		pr_err("%s: Can't build omap_device for %s:%s.\n", __func__,
					name, oh->name);
		return PTR_ERR(od);
	}
	omap_mcbsp_count++;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

static int __init omap2_mcbsp_init(void)
{
	omap_hwmod_for_each_by_class("mcbsp", omap_init_mcbsp, NULL);

<<<<<<< HEAD
	return 0;
=======
<<<<<<< HEAD
	return 0;
=======
	mcbsp_ptr = kzalloc(omap_mcbsp_count * sizeof(struct omap_mcbsp *),
								GFP_KERNEL);
	if (!mcbsp_ptr)
		return -ENOMEM;

	return omap_mcbsp_init();
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
arch_initcall(omap2_mcbsp_init);
