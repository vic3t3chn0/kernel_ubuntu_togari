/*
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *  sound/soc/samsung/smdk_wm8994pcm.c
 *
 *  Copyright (c) 2011 Samsung Electronics Co., Ltd
 *		http://www.samsung.com
 *
 *  This program is free software; you can redistribute  it and/or  modify it
<<<<<<< HEAD
=======
=======
 *  smdk_wm8994.c
 *
 *  This program is free software; you can redistribute  it and/or modify it
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 */
<<<<<<< HEAD
#include <linux/module.h>
#include <sound/soc.h>
=======
<<<<<<< HEAD
#include <linux/module.h>
#include <sound/soc.h>
=======

#include <linux/clk.h>

#include <sound/soc.h>
#include <sound/soc-dapm.h>
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <sound/pcm.h>
#include <sound/pcm_params.h>

#include "../codecs/wm8994.h"
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include "dma.h"
#include "pcm.h"

/*
 * Board Settings:
 *  o '1' means 'ON'
 *  o '0' means 'OFF'
 *  o 'X' means 'Don't care'
 *
 * SMDKC210, SMDKV310: CFG3- 1001, CFG5-1000, CFG7-111111
 */

/*
 * Configure audio route as :-
 * $ amixer sset 'DAC1' on,on
 * $ amixer sset 'Right Headphone Mux' 'DAC'
 * $ amixer sset 'Left Headphone Mux' 'DAC'
 * $ amixer sset 'DAC1R Mixer AIF1.1' on
 * $ amixer sset 'DAC1L Mixer AIF1.1' on
 * $ amixer sset 'IN2L' on
 * $ amixer sset 'IN2L PGA IN2LN' on
 * $ amixer sset 'MIXINL IN2L' on
 * $ amixer sset 'AIF1ADC1L Mixer ADC/DMIC' on
 * $ amixer sset 'IN2R' on
 * $ amixer sset 'IN2R PGA IN2RN' on
 * $ amixer sset 'MIXINR IN2R' on
 * $ amixer sset 'AIF1ADC1R Mixer ADC/DMIC' on
 */

/* SMDK has a 16.9344MHZ crystal attached to WM8994 */
#define SMDK_WM8994_FREQ 16934400

static int smdk_wm8994_pcm_hw_params(struct snd_pcm_substream *substream,
			      struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	unsigned long mclk_freq;
	int rfs, ret;

	switch(params_rate(params)) {
	case 8000:
		rfs = 512;
		break;
	default:
		dev_err(cpu_dai->dev, "%s:%d Sampling Rate %u not supported!\n",
		__func__, __LINE__, params_rate(params));
		return -EINVAL;
	}

	mclk_freq = params_rate(params) * rfs;
<<<<<<< HEAD
=======
=======
#include "pcm.h"

 /*
  * Default CFG switch settings to use this driver:
  *	SMDKV310: CFG5-1000, CFG7-111111
  */

 /*
  * Configure audio route as :-
  * $ amixer sset 'DAC1' on,on
  * $ amixer sset 'Right Headphone Mux' 'DAC'
  * $ amixer sset 'Left Headphone Mux' 'DAC'
  * $ amixer sset 'DAC1R Mixer AIF1.1' on
  * $ amixer sset 'DAC1L Mixer AIF1.1' on
  * $ amixer sset 'IN2L' on
  * $ amixer sset 'IN2L PGA IN2LN' on
  * $ amixer sset 'MIXINL IN2L' on
  * $ amixer sset 'AIF1ADC1L Mixer ADC/DMIC' on
  * $ amixer sset 'IN2R' on
  * $ amixer sset 'IN2R PGA IN2RN' on
  * $ amixer sset 'MIXINR IN2R' on
  * $ amixer sset 'AIF1ADC1R Mixer ADC/DMIC' on
  */

/* SMDK has a 16.934MHZ crystal attached to WM8994 */
#define SMDK_WM8994_FREQ 16934000

#ifdef CONFIG_SND_SAMSUNG_PCM_USE_EPLL
static int set_epll_rate(unsigned long rate)
{
	struct clk *fout_epll;

	fout_epll = clk_get(NULL, "fout_epll");
	if (IS_ERR(fout_epll)) {
		printk(KERN_ERR "%s: failed to get fout_epll\n", __func__);
		return PTR_ERR(fout_epll);
	}

	if (rate == clk_get_rate(fout_epll))
		goto out;

	clk_set_rate(fout_epll, rate);
out:
	clk_put(fout_epll);

	return 0;
}
#endif /* CONFIG_SND_SAMSUNG_PCM_USE_EPLL */

static int smdk_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
#ifdef CONFIG_SND_SAMSUNG_PCM_USE_EPLL
	unsigned long epll_out_rate;
#endif /* CONFIG_SND_SAMSUNG_PCM_USE_EPLL */
	int rfs, ret;

#ifdef CONFIG_SND_SAMSUNG_PCM_USE_EPLL
	switch (params_rate(params)) {
	case 8000:
	case 12000:
	case 16000:
	case 24000:
	case 32000:
	case 48000:
	case 64000:
	case 96000:
		epll_out_rate = 49152000;
		break;
	case 11025:
	case 22050:
	case 44100:
	case 88200:
		epll_out_rate = 67737600;
		break;
	default:
		printk(KERN_ERR "%s:%d Sampling Rate %u not supported!\n",
			__func__, __LINE__, params_rate(params));
		return -EINVAL;
	}
#endif /* CONFIG_SND_SAMSUNG_PCM_USE_EPLL */

	switch (params_rate(params)) {
	case 16000:
	case 22050:
	case 22025:
	case 32000:
	case 44100:
	case 48000:
	case 96000:
	case 24000:
#ifdef CONFIG_SND_SAMSUNG_PCM_USE_EPLL
			rfs = 256;
#else /* CONFIG_SND_SAMSUNG_PCM_USE_EPLL */
			rfs = 384;
#endif /* CONFIG_SND_SAMSUNG_PCM_USE_EPLL */
		break;
	case 64000:
		rfs = 384;
		break;
	case 8000:
	case 11025:
	case 12000:
			rfs = 512;
		break;
	case 88200:
		rfs = 128;
		break;
	default:
		printk(KERN_ERR "%s:%d Sampling Rate %u not supported!\n",
			__func__, __LINE__, params_rate(params));
		return -EINVAL;
	}
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Set the codec DAI configuration */
	ret = snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_DSP_B
				| SND_SOC_DAIFMT_IB_NF
				| SND_SOC_DAIFMT_CBS_CFS);
	if (ret < 0)
		return ret;

	/* Set the cpu DAI configuration */
	ret = snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_DSP_B
				| SND_SOC_DAIFMT_IB_NF
				| SND_SOC_DAIFMT_CBS_CFS);
	if (ret < 0)
		return ret;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_FLL1,
					mclk_freq, SND_SOC_CLOCK_IN);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL1, WM8994_FLL_SRC_MCLK1,
					SMDK_WM8994_FREQ, mclk_freq);
	if (ret < 0)
		return ret;

	/* Set PCM source clock on CPU */
	ret = snd_soc_dai_set_sysclk(cpu_dai, S3C_PCM_CLKSRC_MUX,
					mclk_freq, SND_SOC_CLOCK_IN);
	if (ret < 0)
		return ret;

<<<<<<< HEAD
=======
=======
#ifdef CONFIG_SND_SAMSUNG_PCM_USE_EPLL
	/*
	 * Samsung SoCs PCM has no MCLK(rclk) output support, so codec
	 * should have to make its own MCLK with FLL(or PLL) from other
	 * clock source.
	 */
	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_FLL1,
				params_rate(params)*rfs,
				SND_SOC_CLOCK_IN);
	if (ret < 0)
		return ret;

	ret = snd_soc_dai_set_pll(codec_dai, WM8994_FLL1,
				WM8994_FLL_SRC_MCLK1,
				SMDK_WM8994_FREQ,
				params_rate(params)*rfs);
	if (ret < 0)
		return ret;
#endif /* CONFIG_SND_SAMSUNG_PCM_USE_EPLL */

	ret = snd_soc_dai_set_sysclk(codec_dai, WM8994_SYSCLK_MCLK1,
					params_rate(params)*rfs,
					SND_SOC_CLOCK_IN);
	if (ret < 0)
		return ret;

#ifdef CONFIG_SND_SAMSUNG_PCM_USE_EPLL
	/* Set EPLL clock rate */
	ret = set_epll_rate(epll_out_rate);
	if (ret < 0)
		return ret;
#endif /* CONFIG_SND_SAMSUNG_PCM_USE_EPLL */

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* Set SCLK_DIV for making bclk */
	ret = snd_soc_dai_set_clkdiv(cpu_dai, S3C_PCM_SCLK_PER_FS, rfs);
	if (ret < 0)
		return ret;

	return 0;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct snd_soc_ops smdk_wm8994_pcm_ops = {
	.hw_params = smdk_wm8994_pcm_hw_params,
};

static struct snd_soc_dai_link smdk_dai[] = {
	{
		.name = "WM8994 PAIF PCM",
		.stream_name = "Primary PCM",
<<<<<<< HEAD
=======
=======
/*
 * SMDK WM8994 DAI operations.
 */
static struct snd_soc_ops smdk_ops = {
	.hw_params = smdk_hw_params,
};

static struct snd_soc_dai_link smdk_dai[] = {
	{ /* Primary DAI i/f */
		.name = "WM8994 AIF1",
		.stream_name = "PCM Tx/Rx",
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		.cpu_dai_name = "samsung-pcm.0",
		.codec_dai_name = "wm8994-aif1",
		.platform_name = "samsung-audio",
		.codec_name = "wm8994-codec",
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		.ops = &smdk_wm8994_pcm_ops,
	},
};

static struct snd_soc_card smdk_pcm = {
	.name = "SMDK-PCM",
	.owner = THIS_MODULE,
	.dai_link = smdk_dai,
	.num_links = 1,
};

static int __devinit snd_smdk_probe(struct platform_device *pdev)
{
	int ret = 0;

	smdk_pcm.dev = &pdev->dev;
	ret = snd_soc_register_card(&smdk_pcm);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed %d\n", ret);
		return ret;
	}

	return 0;
}

static int __devexit snd_smdk_remove(struct platform_device *pdev)
{
	snd_soc_unregister_card(&smdk_pcm);
	platform_set_drvdata(pdev, NULL);
	return 0;
}

static struct platform_driver snd_smdk_driver = {
	.driver = {
		.owner = THIS_MODULE,
		.name = "samsung-smdk-pcm",
	},
	.probe = snd_smdk_probe,
	.remove = __devexit_p(snd_smdk_remove),
};

module_platform_driver(snd_smdk_driver);

MODULE_AUTHOR("Sangbeom Kim, <sbkim73@samsung.com>");
MODULE_DESCRIPTION("ALSA SoC SMDK WM8994 for PCM");
<<<<<<< HEAD
=======
=======
		.ops = &smdk_ops,
	},
};

static struct snd_soc_card smdk = {
	.name = "SMDK-PCM",
	.dai_link = smdk_dai,
	.num_links = ARRAY_SIZE(smdk_dai),
};

static struct platform_device *smdk_snd_device;

static int __init smdk_audio_init(void)
{
	int ret;

	smdk_snd_device = platform_device_alloc("soc-audio", -1);
	if (!smdk_snd_device)
		return -ENOMEM;

	platform_set_drvdata(smdk_snd_device, &smdk);

	ret = platform_device_add(smdk_snd_device);
	if (ret)
		platform_device_put(smdk_snd_device);

	return ret;
}
module_init(smdk_audio_init);

static void __exit smdk_audio_exit(void)
{
	platform_device_unregister(smdk_snd_device);
}
module_exit(smdk_audio_exit);

MODULE_DESCRIPTION("ALSA SoC SMDK WM8994");
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
MODULE_LICENSE("GPL");
