<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 /*
 * Audio Codec driver supporting:
 *  AD1835A, AD1836, AD1837A, AD1838A, AD1839A
 *
 * Copyright 2009-2011 Analog Devices Inc.
 *
 * Licensed under the GPL-2 or later.
<<<<<<< HEAD
=======
=======
/*
 * File:         sound/soc/codecs/ad1836.c
 * Author:       Barry Song <Barry.Song@analog.com>
 *
 * Created:      Aug 04 2009
 * Description:  Driver for AD1836 sound chip
 *
 * Modified:
 *               Copyright 2009 Analog Devices Inc.
 *
 * Bugs:         Enter bugs at http://blackfin.uclinux.org/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 */

#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/initval.h>
#include <sound/soc.h>
#include <sound/tlv.h>
#include <linux/spi/spi.h>
#include "ad1836.h"

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
enum ad1836_type {
	AD1835,
	AD1836,
	AD1838,
};

/* codec private data */
struct ad1836_priv {
	enum ad1836_type type;
<<<<<<< HEAD
=======
=======
/* codec private data */
struct ad1836_priv {
	enum snd_soc_control_type control_type;
	void *control_data;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/*
 * AD1836 volume/mute/de-emphasis etc. controls
 */
static const char *ad1836_deemp[] = {"None", "44.1kHz", "32kHz", "48kHz"};

static const struct soc_enum ad1836_deemp_enum =
	SOC_ENUM_SINGLE(AD1836_DAC_CTRL1, 8, 4, ad1836_deemp);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define AD1836_DAC_VOLUME(x) \
	SOC_DOUBLE_R("DAC" #x " Playback Volume", AD1836_DAC_L_VOL(x), \
			AD1836_DAC_R_VOL(x), 0, 0x3FF, 0)

#define AD1836_DAC_SWITCH(x) \
	SOC_DOUBLE("DAC" #x " Playback Switch", AD1836_DAC_CTRL2, \
			AD1836_MUTE_LEFT(x), AD1836_MUTE_RIGHT(x), 1, 1)

#define AD1836_ADC_SWITCH(x) \
	SOC_DOUBLE("ADC" #x " Capture Switch", AD1836_ADC_CTRL2, \
		AD1836_MUTE_LEFT(x), AD1836_MUTE_RIGHT(x), 1, 1)

static const struct snd_kcontrol_new ad183x_dac_controls[] = {
	AD1836_DAC_VOLUME(1),
	AD1836_DAC_SWITCH(1),
	AD1836_DAC_VOLUME(2),
	AD1836_DAC_SWITCH(2),
	AD1836_DAC_VOLUME(3),
	AD1836_DAC_SWITCH(3),
	AD1836_DAC_VOLUME(4),
	AD1836_DAC_SWITCH(4),
};

static const struct snd_soc_dapm_widget ad183x_dac_dapm_widgets[] = {
	SND_SOC_DAPM_OUTPUT("DAC1OUT"),
	SND_SOC_DAPM_OUTPUT("DAC2OUT"),
	SND_SOC_DAPM_OUTPUT("DAC3OUT"),
	SND_SOC_DAPM_OUTPUT("DAC4OUT"),
};

static const struct snd_soc_dapm_route ad183x_dac_routes[] = {
	{ "DAC1OUT", NULL, "DAC" },
	{ "DAC2OUT", NULL, "DAC" },
	{ "DAC3OUT", NULL, "DAC" },
	{ "DAC4OUT", NULL, "DAC" },
};

static const struct snd_kcontrol_new ad183x_adc_controls[] = {
	AD1836_ADC_SWITCH(1),
	AD1836_ADC_SWITCH(2),
	AD1836_ADC_SWITCH(3),
};

static const struct snd_soc_dapm_widget ad183x_adc_dapm_widgets[] = {
	SND_SOC_DAPM_INPUT("ADC1IN"),
	SND_SOC_DAPM_INPUT("ADC2IN"),
};

static const struct snd_soc_dapm_route ad183x_adc_routes[] = {
	{ "ADC", NULL, "ADC1IN" },
	{ "ADC", NULL, "ADC2IN" },
};

static const struct snd_kcontrol_new ad183x_controls[] = {
<<<<<<< HEAD
=======
=======
static const struct snd_kcontrol_new ad1836_snd_controls[] = {
	/* DAC volume control */
	SOC_DOUBLE_R("DAC1 Volume", AD1836_DAC_L1_VOL,
			AD1836_DAC_R1_VOL, 0, 0x3FF, 0),
	SOC_DOUBLE_R("DAC2 Volume", AD1836_DAC_L2_VOL,
			AD1836_DAC_R2_VOL, 0, 0x3FF, 0),
	SOC_DOUBLE_R("DAC3 Volume", AD1836_DAC_L3_VOL,
			AD1836_DAC_R3_VOL, 0, 0x3FF, 0),

	/* ADC switch control */
	SOC_DOUBLE("ADC1 Switch", AD1836_ADC_CTRL2, AD1836_ADCL1_MUTE,
		AD1836_ADCR1_MUTE, 1, 1),
	SOC_DOUBLE("ADC2 Switch", AD1836_ADC_CTRL2, AD1836_ADCL2_MUTE,
		AD1836_ADCR2_MUTE, 1, 1),

	/* DAC switch control */
	SOC_DOUBLE("DAC1 Switch", AD1836_DAC_CTRL2, AD1836_DACL1_MUTE,
		AD1836_DACR1_MUTE, 1, 1),
	SOC_DOUBLE("DAC2 Switch", AD1836_DAC_CTRL2, AD1836_DACL2_MUTE,
		AD1836_DACR2_MUTE, 1, 1),
	SOC_DOUBLE("DAC3 Switch", AD1836_DAC_CTRL2, AD1836_DACL3_MUTE,
		AD1836_DACR3_MUTE, 1, 1),

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* ADC high-pass filter */
	SOC_SINGLE("ADC High Pass Filter Switch", AD1836_ADC_CTRL1,
			AD1836_ADC_HIGHPASS_FILTER, 1, 0),

	/* DAC de-emphasis */
	SOC_ENUM("Playback Deemphasis", ad1836_deemp_enum),
};

<<<<<<< HEAD
static const struct snd_soc_dapm_widget ad183x_dapm_widgets[] = {
=======
<<<<<<< HEAD
static const struct snd_soc_dapm_widget ad183x_dapm_widgets[] = {
=======
static const struct snd_soc_dapm_widget ad1836_dapm_widgets[] = {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	SND_SOC_DAPM_DAC("DAC", "Playback", AD1836_DAC_CTRL1,
				AD1836_DAC_POWERDOWN, 1),
	SND_SOC_DAPM_ADC("ADC", "Capture", SND_SOC_NOPM, 0, 0),
	SND_SOC_DAPM_SUPPLY("ADC_PWR", AD1836_ADC_CTRL1,
				AD1836_ADC_POWERDOWN, 1, NULL, 0),
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static const struct snd_soc_dapm_route ad183x_dapm_routes[] = {
	{ "DAC", NULL, "ADC_PWR" },
	{ "ADC", NULL, "ADC_PWR" },
};

static const DECLARE_TLV_DB_SCALE(ad1836_in_tlv, 0, 300, 0);

static const struct snd_kcontrol_new ad1836_controls[] = {
	SOC_DOUBLE_TLV("ADC2 Capture Volume", AD1836_ADC_CTRL1, 3, 0, 4, 0,
	    ad1836_in_tlv),
<<<<<<< HEAD
=======
=======
	SND_SOC_DAPM_OUTPUT("DAC1OUT"),
	SND_SOC_DAPM_OUTPUT("DAC2OUT"),
	SND_SOC_DAPM_OUTPUT("DAC3OUT"),
	SND_SOC_DAPM_INPUT("ADC1IN"),
	SND_SOC_DAPM_INPUT("ADC2IN"),
};

static const struct snd_soc_dapm_route audio_paths[] = {
	{ "DAC", NULL, "ADC_PWR" },
	{ "ADC", NULL, "ADC_PWR" },
	{ "DAC1OUT", "DAC1 Switch", "DAC" },
	{ "DAC2OUT", "DAC2 Switch", "DAC" },
	{ "DAC3OUT", "DAC3 Switch", "DAC" },
	{ "ADC", "ADC1 Switch", "ADC1IN" },
	{ "ADC", "ADC2 Switch", "ADC2IN" },
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

/*
 * DAI ops entries
 */

static int ad1836_set_dai_fmt(struct snd_soc_dai *codec_dai,
		unsigned int fmt)
{
	switch (fmt & SND_SOC_DAIFMT_FORMAT_MASK) {
	/* at present, we support adc aux mode to interface with
	 * blackfin sport tdm mode
	 */
	case SND_SOC_DAIFMT_DSP_A:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_INV_MASK) {
	case SND_SOC_DAIFMT_IB_IF:
		break;
	default:
		return -EINVAL;
	}

	switch (fmt & SND_SOC_DAIFMT_MASTER_MASK) {
	/* ALCLK,ABCLK are both output, AD1836 can only be master */
	case SND_SOC_DAIFMT_CBM_CFM:
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int ad1836_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params,
		struct snd_soc_dai *dai)
{
	int word_len = 0;

	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_codec *codec = rtd->codec;

	/* bit size */
	switch (params_format(params)) {
	case SNDRV_PCM_FORMAT_S16_LE:
		word_len = AD1836_WORD_LEN_16;
		break;
	case SNDRV_PCM_FORMAT_S20_3LE:
		word_len = AD1836_WORD_LEN_20;
		break;
	case SNDRV_PCM_FORMAT_S24_LE:
	case SNDRV_PCM_FORMAT_S32_LE:
		word_len = AD1836_WORD_LEN_24;
		break;
	}

	snd_soc_update_bits(codec, AD1836_DAC_CTRL1, AD1836_DAC_WORD_LEN_MASK,
		word_len << AD1836_DAC_WORD_LEN_OFFSET);

	snd_soc_update_bits(codec, AD1836_ADC_CTRL2, AD1836_ADC_WORD_LEN_MASK,
		word_len << AD1836_ADC_WORD_OFFSET);

	return 0;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static const struct snd_soc_dai_ops ad1836_dai_ops = {
	.hw_params = ad1836_hw_params,
	.set_fmt = ad1836_set_dai_fmt,
};

#define AD183X_DAI(_name, num_dacs, num_adcs) \
{ \
	.name = _name "-hifi", \
	.playback = { \
		.stream_name = "Playback", \
		.channels_min = 2, \
		.channels_max = (num_dacs) * 2, \
		.rates = SNDRV_PCM_RATE_48000,  \
		.formats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE, \
	}, \
	.capture = { \
		.stream_name = "Capture", \
		.channels_min = 2, \
		.channels_max = (num_adcs) * 2, \
		.rates = SNDRV_PCM_RATE_48000, \
		.formats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE | \
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE, \
	}, \
	.ops = &ad1836_dai_ops, \
}

static struct snd_soc_dai_driver ad183x_dais[] = {
	[AD1835] = AD183X_DAI("ad1835", 4, 1),
	[AD1836] = AD183X_DAI("ad1836", 3, 2),
	[AD1838] = AD183X_DAI("ad1838", 3, 1),
};

#ifdef CONFIG_PM
static int ad1836_suspend(struct snd_soc_codec *codec)
{
	/* reset clock control mode */
	return snd_soc_update_bits(codec, AD1836_ADC_CTRL2,
		AD1836_ADC_SERFMT_MASK, 0);
}

static int ad1836_resume(struct snd_soc_codec *codec)
{
	/* restore clock control mode */
	return snd_soc_update_bits(codec, AD1836_ADC_CTRL2,
		AD1836_ADC_SERFMT_MASK, AD1836_ADC_AUX);
}
#else
#define ad1836_suspend NULL
#define ad1836_resume  NULL
#endif

<<<<<<< HEAD
=======
=======
#ifdef CONFIG_PM
static int ad1836_soc_suspend(struct snd_soc_codec *codec,
		pm_message_t state)
{
	/* reset clock control mode */
	u16 adc_ctrl2 = snd_soc_read(codec, AD1836_ADC_CTRL2);
	adc_ctrl2 &= ~AD1836_ADC_SERFMT_MASK;

	return snd_soc_write(codec, AD1836_ADC_CTRL2, adc_ctrl2);
}

static int ad1836_soc_resume(struct snd_soc_codec *codec)
{
	/* restore clock control mode */
	u16 adc_ctrl2 = snd_soc_read(codec, AD1836_ADC_CTRL2);
	adc_ctrl2 |= AD1836_ADC_AUX;

	return snd_soc_write(codec, AD1836_ADC_CTRL2, adc_ctrl2);
}
#else
#define ad1836_soc_suspend NULL
#define ad1836_soc_resume  NULL
#endif

static struct snd_soc_dai_ops ad1836_dai_ops = {
	.hw_params = ad1836_hw_params,
	.set_fmt = ad1836_set_dai_fmt,
};

/* codec DAI instance */
static struct snd_soc_dai_driver ad1836_dai = {
	.name = "ad1836-hifi",
	.playback = {
		.stream_name = "Playback",
		.channels_min = 2,
		.channels_max = 6,
		.rates = SNDRV_PCM_RATE_48000,
		.formats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE,
	},
	.capture = {
		.stream_name = "Capture",
		.channels_min = 2,
		.channels_max = 4,
		.rates = SNDRV_PCM_RATE_48000,
		.formats = SNDRV_PCM_FMTBIT_S32_LE | SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S20_3LE | SNDRV_PCM_FMTBIT_S24_LE,
	},
	.ops = &ad1836_dai_ops,
};

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int ad1836_probe(struct snd_soc_codec *codec)
{
	struct ad1836_priv *ad1836 = snd_soc_codec_get_drvdata(codec);
	struct snd_soc_dapm_context *dapm = &codec->dapm;
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int num_dacs, num_adcs;
	int ret = 0;
	int i;

	num_dacs = ad183x_dais[ad1836->type].playback.channels_max / 2;
	num_adcs = ad183x_dais[ad1836->type].capture.channels_max / 2;

<<<<<<< HEAD
=======
=======
	int ret = 0;

	codec->control_data = ad1836->control_data;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = snd_soc_codec_set_cache_io(codec, 4, 12, SND_SOC_SPI);
	if (ret < 0) {
		dev_err(codec->dev, "failed to set cache I/O: %d\n",
				ret);
		return ret;
	}

	/* default setting for ad1836 */
	/* de-emphasis: 48kHz, power-on dac */
	snd_soc_write(codec, AD1836_DAC_CTRL1, 0x300);
	/* unmute dac channels */
	snd_soc_write(codec, AD1836_DAC_CTRL2, 0x0);
	/* high-pass filter enable, power-on adc */
	snd_soc_write(codec, AD1836_ADC_CTRL1, 0x100);
	/* unmute adc channles, adc aux mode */
	snd_soc_write(codec, AD1836_ADC_CTRL2, 0x180);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* volume */
	for (i = 1; i <= num_dacs; ++i) {
		snd_soc_write(codec, AD1836_DAC_L_VOL(i), 0x3FF);
		snd_soc_write(codec, AD1836_DAC_R_VOL(i), 0x3FF);
	}

	if (ad1836->type == AD1836) {
		/* left/right diff:PGA/MUX */
		snd_soc_write(codec, AD1836_ADC_CTRL3, 0x3A);
		ret = snd_soc_add_codec_controls(codec, ad1836_controls,
				ARRAY_SIZE(ad1836_controls));
		if (ret)
			return ret;
	} else {
		snd_soc_write(codec, AD1836_ADC_CTRL3, 0x00);
	}

	ret = snd_soc_add_codec_controls(codec, ad183x_dac_controls, num_dacs * 2);
	if (ret)
		return ret;

	ret = snd_soc_add_codec_controls(codec, ad183x_adc_controls, num_adcs);
	if (ret)
		return ret;

	ret = snd_soc_dapm_new_controls(dapm, ad183x_dac_dapm_widgets, num_dacs);
	if (ret)
		return ret;

	ret = snd_soc_dapm_new_controls(dapm, ad183x_adc_dapm_widgets, num_adcs);
	if (ret)
		return ret;

	ret = snd_soc_dapm_add_routes(dapm, ad183x_dac_routes, num_dacs);
	if (ret)
		return ret;

	ret = snd_soc_dapm_add_routes(dapm, ad183x_adc_routes, num_adcs);
	if (ret)
		return ret;
<<<<<<< HEAD
=======
=======
	/* left/right diff:PGA/MUX */
	snd_soc_write(codec, AD1836_ADC_CTRL3, 0x3A);
	/* volume */
	snd_soc_write(codec, AD1836_DAC_L1_VOL, 0x3FF);
	snd_soc_write(codec, AD1836_DAC_R1_VOL, 0x3FF);
	snd_soc_write(codec, AD1836_DAC_L2_VOL, 0x3FF);
	snd_soc_write(codec, AD1836_DAC_R2_VOL, 0x3FF);
	snd_soc_write(codec, AD1836_DAC_L3_VOL, 0x3FF);
	snd_soc_write(codec, AD1836_DAC_R3_VOL, 0x3FF);

	snd_soc_add_controls(codec, ad1836_snd_controls,
			     ARRAY_SIZE(ad1836_snd_controls));
	snd_soc_dapm_new_controls(dapm, ad1836_dapm_widgets,
				  ARRAY_SIZE(ad1836_dapm_widgets));
	snd_soc_dapm_add_routes(dapm, audio_paths, ARRAY_SIZE(audio_paths));
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return ret;
}

/* power down chip */
static int ad1836_remove(struct snd_soc_codec *codec)
{
	/* reset clock control mode */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return snd_soc_update_bits(codec, AD1836_ADC_CTRL2,
		AD1836_ADC_SERFMT_MASK, 0);
}

static struct snd_soc_codec_driver soc_codec_dev_ad1836 = {
	.probe = ad1836_probe,
	.remove = ad1836_remove,
	.suspend = ad1836_suspend,
	.resume = ad1836_resume,
	.reg_cache_size = AD1836_NUM_REGS,
	.reg_word_size = sizeof(u16),

	.controls = ad183x_controls,
	.num_controls = ARRAY_SIZE(ad183x_controls),
	.dapm_widgets = ad183x_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(ad183x_dapm_widgets),
	.dapm_routes = ad183x_dapm_routes,
	.num_dapm_routes = ARRAY_SIZE(ad183x_dapm_routes),
<<<<<<< HEAD
=======
=======
	u16 adc_ctrl2 = snd_soc_read(codec, AD1836_ADC_CTRL2);
	adc_ctrl2 &= ~AD1836_ADC_SERFMT_MASK;

	return snd_soc_write(codec, AD1836_ADC_CTRL2, adc_ctrl2);
}

static struct snd_soc_codec_driver soc_codec_dev_ad1836 = {
	.probe = 	ad1836_probe,
	.remove = 	ad1836_remove,
	.suspend =      ad1836_soc_suspend,
	.resume =       ad1836_soc_resume,
	.reg_cache_size = AD1836_NUM_REGS,
	.reg_word_size = sizeof(u16),
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static int __devinit ad1836_spi_probe(struct spi_device *spi)
{
	struct ad1836_priv *ad1836;
	int ret;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ad1836 = devm_kzalloc(&spi->dev, sizeof(struct ad1836_priv),
			      GFP_KERNEL);
	if (ad1836 == NULL)
		return -ENOMEM;

	ad1836->type = spi_get_device_id(spi)->driver_data;

	spi_set_drvdata(spi, ad1836);

	ret = snd_soc_register_codec(&spi->dev,
			&soc_codec_dev_ad1836, &ad183x_dais[ad1836->type], 1);
<<<<<<< HEAD
=======
=======
	ad1836 = kzalloc(sizeof(struct ad1836_priv), GFP_KERNEL);
	if (ad1836 == NULL)
		return -ENOMEM;

	spi_set_drvdata(spi, ad1836);
	ad1836->control_data = spi;
	ad1836->control_type = SND_SOC_SPI;

	ret = snd_soc_register_codec(&spi->dev,
			&soc_codec_dev_ad1836, &ad1836_dai, 1);
	if (ret < 0)
		kfree(ad1836);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static int __devexit ad1836_spi_remove(struct spi_device *spi)
{
	snd_soc_unregister_codec(&spi->dev);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return 0;
}

static const struct spi_device_id ad1836_ids[] = {
	{ "ad1835", AD1835 },
	{ "ad1836", AD1836 },
	{ "ad1837", AD1835 },
	{ "ad1838", AD1838 },
	{ "ad1839", AD1838 },
	{ },
};
MODULE_DEVICE_TABLE(spi, ad1836_ids);

static struct spi_driver ad1836_spi_driver = {
	.driver = {
		.name	= "ad1836",
<<<<<<< HEAD
=======
=======
	kfree(spi_get_drvdata(spi));
	return 0;
}

static struct spi_driver ad1836_spi_driver = {
	.driver = {
		.name	= "ad1836-codec",
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		.owner	= THIS_MODULE,
	},
	.probe		= ad1836_spi_probe,
	.remove		= __devexit_p(ad1836_spi_remove),
<<<<<<< HEAD
	.id_table	= ad1836_ids,
=======
<<<<<<< HEAD
	.id_table	= ad1836_ids,
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static int __init ad1836_init(void)
{
<<<<<<< HEAD
	return spi_register_driver(&ad1836_spi_driver);
=======
<<<<<<< HEAD
	return spi_register_driver(&ad1836_spi_driver);
=======
	int ret;

	ret = spi_register_driver(&ad1836_spi_driver);
	if (ret != 0) {
		printk(KERN_ERR "Failed to register ad1836 SPI driver: %d\n",
				ret);
	}

	return ret;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}
module_init(ad1836_init);

static void __exit ad1836_exit(void)
{
	spi_unregister_driver(&ad1836_spi_driver);
}
module_exit(ad1836_exit);

MODULE_DESCRIPTION("ASoC ad1836 driver");
MODULE_AUTHOR("Barry Song <21cnbao@gmail.com>");
MODULE_LICENSE("GPL");
