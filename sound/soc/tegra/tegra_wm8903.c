/*
 * tegra_wm8903.c - Tegra machine ASoC driver for boards using WM8903 codec.
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010-2011 - NVIDIA, Inc.
 *
 * Based on code copyright/by:
 *
 * (c) 2009, 2010 Nvidia Graphics Pvt. Ltd.
 *
 * Copyright 2007 Wolfson Microelectronics PLC.
 * Author: Graeme Gregory
 *         graeme.gregory@wolfsonmicro.com or linux@wolfsonmicro.com
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301 USA
 *
 */

#include <asm/mach-types.h>

#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/gpio.h>
<<<<<<< HEAD
#include <linux/of_gpio.h>
=======
<<<<<<< HEAD
#include <linux/of_gpio.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <mach/tegra_wm8903_pdata.h>

#include <sound/core.h>
#include <sound/jack.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>

#include "../codecs/wm8903.h"

#include "tegra_das.h"
#include "tegra_i2s.h"
#include "tegra_pcm.h"
#include "tegra_asoc_utils.h"

#define DRV_NAME "tegra-snd-wm8903"

#define GPIO_SPKR_EN    BIT(0)
#define GPIO_HP_MUTE    BIT(1)
#define GPIO_INT_MIC_EN BIT(2)
#define GPIO_EXT_MIC_EN BIT(3)
#define GPIO_HP_DET     BIT(4)

struct tegra_wm8903 {
<<<<<<< HEAD
	struct tegra_wm8903_platform_data pdata;
	struct platform_device *pcm_dev;
	struct tegra_asoc_utils_data util_data;
=======
<<<<<<< HEAD
	struct tegra_wm8903_platform_data pdata;
	struct platform_device *pcm_dev;
	struct tegra_asoc_utils_data util_data;
=======
	struct tegra_asoc_utils_data util_data;
	struct tegra_wm8903_platform_data *pdata;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int gpio_requested;
};

static int tegra_wm8903_hw_params(struct snd_pcm_substream *substream,
					struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;
	struct snd_soc_codec *codec = rtd->codec;
	struct snd_soc_card *card = codec->card;
	struct tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);
	int srate, mclk;
	int err;

	srate = params_rate(params);
	switch (srate) {
	case 64000:
	case 88200:
	case 96000:
		mclk = 128 * srate;
		break;
	default:
		mclk = 256 * srate;
		break;
	}
	/* FIXME: Codec only requires >= 3MHz if OSR==0 */
	while (mclk < 6000000)
		mclk *= 2;

	err = tegra_asoc_utils_set_rate(&machine->util_data, srate, mclk);
	if (err < 0) {
		dev_err(card->dev, "Can't configure clocks\n");
		return err;
	}

	err = snd_soc_dai_set_fmt(codec_dai,
					SND_SOC_DAIFMT_I2S |
					SND_SOC_DAIFMT_NB_NF |
					SND_SOC_DAIFMT_CBS_CFS);
	if (err < 0) {
		dev_err(card->dev, "codec_dai fmt not set\n");
		return err;
	}

	err = snd_soc_dai_set_fmt(cpu_dai,
					SND_SOC_DAIFMT_I2S |
					SND_SOC_DAIFMT_NB_NF |
					SND_SOC_DAIFMT_CBS_CFS);
	if (err < 0) {
		dev_err(card->dev, "cpu_dai fmt not set\n");
		return err;
	}

	err = snd_soc_dai_set_sysclk(codec_dai, 0, mclk,
					SND_SOC_CLOCK_IN);
	if (err < 0) {
		dev_err(card->dev, "codec_dai clock not set\n");
		return err;
	}

	return 0;
}

static struct snd_soc_ops tegra_wm8903_ops = {
	.hw_params = tegra_wm8903_hw_params,
};

static struct snd_soc_jack tegra_wm8903_hp_jack;

static struct snd_soc_jack_pin tegra_wm8903_hp_jack_pins[] = {
	{
		.pin = "Headphone Jack",
		.mask = SND_JACK_HEADPHONE,
	},
};

static struct snd_soc_jack_gpio tegra_wm8903_hp_jack_gpio = {
	.name = "headphone detect",
	.report = SND_JACK_HEADPHONE,
	.debounce_time = 150,
	.invert = 1,
};

static struct snd_soc_jack tegra_wm8903_mic_jack;

static struct snd_soc_jack_pin tegra_wm8903_mic_jack_pins[] = {
	{
		.pin = "Mic Jack",
		.mask = SND_JACK_MICROPHONE,
	},
};

static int tegra_wm8903_event_int_spk(struct snd_soc_dapm_widget *w,
					struct snd_kcontrol *k, int event)
{
	struct snd_soc_dapm_context *dapm = w->dapm;
	struct snd_soc_card *card = dapm->card;
	struct tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);
<<<<<<< HEAD
	struct tegra_wm8903_platform_data *pdata = &machine->pdata;
=======
<<<<<<< HEAD
	struct tegra_wm8903_platform_data *pdata = &machine->pdata;
=======
	struct tegra_wm8903_platform_data *pdata = machine->pdata;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!(machine->gpio_requested & GPIO_SPKR_EN))
		return 0;

	gpio_set_value_cansleep(pdata->gpio_spkr_en,
				SND_SOC_DAPM_EVENT_ON(event));

	return 0;
}

static int tegra_wm8903_event_hp(struct snd_soc_dapm_widget *w,
					struct snd_kcontrol *k, int event)
{
	struct snd_soc_dapm_context *dapm = w->dapm;
	struct snd_soc_card *card = dapm->card;
	struct tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);
<<<<<<< HEAD
	struct tegra_wm8903_platform_data *pdata = &machine->pdata;
=======
<<<<<<< HEAD
	struct tegra_wm8903_platform_data *pdata = &machine->pdata;
=======
	struct tegra_wm8903_platform_data *pdata = machine->pdata;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (!(machine->gpio_requested & GPIO_HP_MUTE))
		return 0;

	gpio_set_value_cansleep(pdata->gpio_hp_mute,
				!SND_SOC_DAPM_EVENT_ON(event));

	return 0;
}

static const struct snd_soc_dapm_widget tegra_wm8903_dapm_widgets[] = {
	SND_SOC_DAPM_SPK("Int Spk", tegra_wm8903_event_int_spk),
	SND_SOC_DAPM_HP("Headphone Jack", tegra_wm8903_event_hp),
	SND_SOC_DAPM_MIC("Mic Jack", NULL),
};

static const struct snd_soc_dapm_route harmony_audio_map[] = {
	{"Headphone Jack", NULL, "HPOUTR"},
	{"Headphone Jack", NULL, "HPOUTL"},
	{"Int Spk", NULL, "ROP"},
	{"Int Spk", NULL, "RON"},
	{"Int Spk", NULL, "LOP"},
	{"Int Spk", NULL, "LON"},
<<<<<<< HEAD
	{"Mic Jack", NULL, "MICBIAS"},
	{"IN1L", NULL, "Mic Jack"},
=======
<<<<<<< HEAD
	{"Mic Jack", NULL, "MICBIAS"},
	{"IN1L", NULL, "Mic Jack"},
=======
	{"Mic Bias", NULL, "Mic Jack"},
	{"IN1L", NULL, "Mic Bias"},
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static const struct snd_soc_dapm_route seaboard_audio_map[] = {
	{"Headphone Jack", NULL, "HPOUTR"},
	{"Headphone Jack", NULL, "HPOUTL"},
	{"Int Spk", NULL, "ROP"},
	{"Int Spk", NULL, "RON"},
	{"Int Spk", NULL, "LOP"},
	{"Int Spk", NULL, "LON"},
<<<<<<< HEAD
	{"Mic Jack", NULL, "MICBIAS"},
	{"IN1R", NULL, "Mic Jack"},
=======
<<<<<<< HEAD
	{"Mic Jack", NULL, "MICBIAS"},
	{"IN1R", NULL, "Mic Jack"},
=======
	{"Mic Bias", NULL, "Mic Jack"},
	{"IN1R", NULL, "Mic Bias"},
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static const struct snd_soc_dapm_route kaen_audio_map[] = {
	{"Headphone Jack", NULL, "HPOUTR"},
	{"Headphone Jack", NULL, "HPOUTL"},
	{"Int Spk", NULL, "ROP"},
	{"Int Spk", NULL, "RON"},
	{"Int Spk", NULL, "LOP"},
	{"Int Spk", NULL, "LON"},
<<<<<<< HEAD
	{"Mic Jack", NULL, "MICBIAS"},
	{"IN2R", NULL, "Mic Jack"},
=======
<<<<<<< HEAD
	{"Mic Jack", NULL, "MICBIAS"},
	{"IN2R", NULL, "Mic Jack"},
=======
	{"Mic Bias", NULL, "Mic Jack"},
	{"IN2R", NULL, "Mic Bias"},
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static const struct snd_soc_dapm_route aebl_audio_map[] = {
	{"Headphone Jack", NULL, "HPOUTR"},
	{"Headphone Jack", NULL, "HPOUTL"},
	{"Int Spk", NULL, "LINEOUTR"},
	{"Int Spk", NULL, "LINEOUTL"},
<<<<<<< HEAD
	{"Mic Jack", NULL, "MICBIAS"},
	{"IN1R", NULL, "Mic Jack"},
=======
<<<<<<< HEAD
	{"Mic Jack", NULL, "MICBIAS"},
	{"IN1R", NULL, "Mic Jack"},
=======
	{"Mic Bias", NULL, "Mic Jack"},
	{"IN1R", NULL, "Mic Bias"},
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static const struct snd_kcontrol_new tegra_wm8903_controls[] = {
	SOC_DAPM_PIN_SWITCH("Int Spk"),
};

static int tegra_wm8903_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_codec *codec = rtd->codec;
	struct snd_soc_dapm_context *dapm = &codec->dapm;
	struct snd_soc_card *card = codec->card;
	struct tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct tegra_wm8903_platform_data *pdata = &machine->pdata;
	struct device_node *np = card->dev->of_node;
	int ret;

	if (card->dev->platform_data) {
		memcpy(pdata, card->dev->platform_data, sizeof(*pdata));
	} else if (np) {
		/*
		 * This part must be in init() rather than probe() in order to
		 * guarantee that the WM8903 has been probed, and hence its
		 * GPIO controller registered, which is a pre-condition for
		 * of_get_named_gpio() to be able to map the phandles in the
		 * properties to the controller node. Given this, all
		 * pdata handling is in init() for consistency.
		 */
		pdata->gpio_spkr_en = of_get_named_gpio(np,
						"nvidia,spkr-en-gpios", 0);
		pdata->gpio_hp_mute = of_get_named_gpio(np,
						"nvidia,hp-mute-gpios", 0);
		pdata->gpio_hp_det = of_get_named_gpio(np,
						"nvidia,hp-det-gpios", 0);
		pdata->gpio_int_mic_en = of_get_named_gpio(np,
						"nvidia,int-mic-en-gpios", 0);
		pdata->gpio_ext_mic_en = of_get_named_gpio(np,
						"nvidia,ext-mic-en-gpios", 0);
	} else {
		dev_err(card->dev, "No platform data supplied\n");
		return -EINVAL;
	}

<<<<<<< HEAD
=======
=======
	struct tegra_wm8903_platform_data *pdata = machine->pdata;
	int ret;

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (gpio_is_valid(pdata->gpio_spkr_en)) {
		ret = gpio_request(pdata->gpio_spkr_en, "spkr_en");
		if (ret) {
			dev_err(card->dev, "cannot get spkr_en gpio\n");
			return ret;
		}
		machine->gpio_requested |= GPIO_SPKR_EN;

		gpio_direction_output(pdata->gpio_spkr_en, 0);
	}

	if (gpio_is_valid(pdata->gpio_hp_mute)) {
		ret = gpio_request(pdata->gpio_hp_mute, "hp_mute");
		if (ret) {
			dev_err(card->dev, "cannot get hp_mute gpio\n");
			return ret;
		}
		machine->gpio_requested |= GPIO_HP_MUTE;

<<<<<<< HEAD
		gpio_direction_output(pdata->gpio_hp_mute, 1);
=======
<<<<<<< HEAD
		gpio_direction_output(pdata->gpio_hp_mute, 1);
=======
		gpio_direction_output(pdata->gpio_hp_mute, 0);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	}

	if (gpio_is_valid(pdata->gpio_int_mic_en)) {
		ret = gpio_request(pdata->gpio_int_mic_en, "int_mic_en");
		if (ret) {
			dev_err(card->dev, "cannot get int_mic_en gpio\n");
			return ret;
		}
		machine->gpio_requested |= GPIO_INT_MIC_EN;

		/* Disable int mic; enable signal is active-high */
		gpio_direction_output(pdata->gpio_int_mic_en, 0);
	}

	if (gpio_is_valid(pdata->gpio_ext_mic_en)) {
		ret = gpio_request(pdata->gpio_ext_mic_en, "ext_mic_en");
		if (ret) {
			dev_err(card->dev, "cannot get ext_mic_en gpio\n");
			return ret;
		}
		machine->gpio_requested |= GPIO_EXT_MIC_EN;

		/* Enable ext mic; enable signal is active-low */
		gpio_direction_output(pdata->gpio_ext_mic_en, 0);
	}

	if (gpio_is_valid(pdata->gpio_hp_det)) {
		tegra_wm8903_hp_jack_gpio.gpio = pdata->gpio_hp_det;
		snd_soc_jack_new(codec, "Headphone Jack", SND_JACK_HEADPHONE,
				&tegra_wm8903_hp_jack);
		snd_soc_jack_add_pins(&tegra_wm8903_hp_jack,
					ARRAY_SIZE(tegra_wm8903_hp_jack_pins),
					tegra_wm8903_hp_jack_pins);
		snd_soc_jack_add_gpios(&tegra_wm8903_hp_jack,
					1,
					&tegra_wm8903_hp_jack_gpio);
		machine->gpio_requested |= GPIO_HP_DET;
	}

	snd_soc_jack_new(codec, "Mic Jack", SND_JACK_MICROPHONE,
			 &tegra_wm8903_mic_jack);
	snd_soc_jack_add_pins(&tegra_wm8903_mic_jack,
			      ARRAY_SIZE(tegra_wm8903_mic_jack_pins),
			      tegra_wm8903_mic_jack_pins);
	wm8903_mic_detect(codec, &tegra_wm8903_mic_jack, SND_JACK_MICROPHONE,
				0);

<<<<<<< HEAD
	snd_soc_dapm_force_enable_pin(dapm, "MICBIAS");
=======
<<<<<<< HEAD
	snd_soc_dapm_force_enable_pin(dapm, "MICBIAS");
=======
	snd_soc_dapm_force_enable_pin(dapm, "Mic Bias");

	/* FIXME: Calculate automatically based on DAPM routes? */
	if (!machine_is_harmony() && !machine_is_ventana())
		snd_soc_dapm_nc_pin(dapm, "IN1L");
	if (!machine_is_seaboard() && !machine_is_aebl())
		snd_soc_dapm_nc_pin(dapm, "IN1R");
	snd_soc_dapm_nc_pin(dapm, "IN2L");
	if (!machine_is_kaen())
		snd_soc_dapm_nc_pin(dapm, "IN2R");
	snd_soc_dapm_nc_pin(dapm, "IN3L");
	snd_soc_dapm_nc_pin(dapm, "IN3R");

	if (machine_is_aebl()) {
		snd_soc_dapm_nc_pin(dapm, "LON");
		snd_soc_dapm_nc_pin(dapm, "RON");
		snd_soc_dapm_nc_pin(dapm, "ROP");
		snd_soc_dapm_nc_pin(dapm, "LOP");
	} else {
		snd_soc_dapm_nc_pin(dapm, "LINEOUTR");
		snd_soc_dapm_nc_pin(dapm, "LINEOUTL");
	}

	snd_soc_dapm_sync(dapm);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

static struct snd_soc_dai_link tegra_wm8903_dai = {
	.name = "WM8903",
	.stream_name = "WM8903 PCM",
	.codec_name = "wm8903.0-001a",
	.platform_name = "tegra-pcm-audio",
	.cpu_dai_name = "tegra-i2s.0",
	.codec_dai_name = "wm8903-hifi",
	.init = tegra_wm8903_init,
	.ops = &tegra_wm8903_ops,
};

static struct snd_soc_card snd_soc_tegra_wm8903 = {
	.name = "tegra-wm8903",
<<<<<<< HEAD
	.owner = THIS_MODULE,
=======
<<<<<<< HEAD
	.owner = THIS_MODULE,
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.dai_link = &tegra_wm8903_dai,
	.num_links = 1,

	.controls = tegra_wm8903_controls,
	.num_controls = ARRAY_SIZE(tegra_wm8903_controls),
	.dapm_widgets = tegra_wm8903_dapm_widgets,
	.num_dapm_widgets = ARRAY_SIZE(tegra_wm8903_dapm_widgets),
<<<<<<< HEAD
	.fully_routed = true,
=======
<<<<<<< HEAD
	.fully_routed = true,
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static __devinit int tegra_wm8903_driver_probe(struct platform_device *pdev)
{
	struct snd_soc_card *card = &snd_soc_tegra_wm8903;
	struct tegra_wm8903 *machine;
<<<<<<< HEAD
	int ret;

	if (!pdev->dev.platform_data && !pdev->dev.of_node) {
=======
<<<<<<< HEAD
	int ret;

	if (!pdev->dev.platform_data && !pdev->dev.of_node) {
=======
	struct tegra_wm8903_platform_data *pdata;
	int ret;

	pdata = pdev->dev.platform_data;
	if (!pdata) {
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		dev_err(&pdev->dev, "No platform data supplied\n");
		return -EINVAL;
	}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	machine = devm_kzalloc(&pdev->dev, sizeof(struct tegra_wm8903),
			       GFP_KERNEL);
	if (!machine) {
		dev_err(&pdev->dev, "Can't allocate tegra_wm8903 struct\n");
		ret = -ENOMEM;
		goto err;
	}
	machine->pcm_dev = ERR_PTR(-EINVAL);
<<<<<<< HEAD
=======
=======
	machine = kzalloc(sizeof(struct tegra_wm8903), GFP_KERNEL);
	if (!machine) {
		dev_err(&pdev->dev, "Can't allocate tegra_wm8903 struct\n");
		return -ENOMEM;
	}

	machine->pdata = pdata;

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
	if (ret)
		goto err_free_machine;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	card->dev = &pdev->dev;
	platform_set_drvdata(pdev, card);
	snd_soc_card_set_drvdata(card, machine);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (pdev->dev.of_node) {
		ret = snd_soc_of_parse_card_name(card, "nvidia,model");
		if (ret)
			goto err;

		ret = snd_soc_of_parse_audio_routing(card,
						     "nvidia,audio-routing");
		if (ret)
			goto err;

		tegra_wm8903_dai.codec_name = NULL;
		tegra_wm8903_dai.codec_of_node = of_parse_phandle(
				pdev->dev.of_node, "nvidia,audio-codec", 0);
		if (!tegra_wm8903_dai.codec_of_node) {
			dev_err(&pdev->dev,
				"Property 'nvidia,audio-codec' missing or invalid\n");
			ret = -EINVAL;
			goto err;
		}

		tegra_wm8903_dai.cpu_dai_name = NULL;
		tegra_wm8903_dai.cpu_dai_of_node = of_parse_phandle(
				pdev->dev.of_node, "nvidia,i2s-controller", 0);
		if (!tegra_wm8903_dai.cpu_dai_of_node) {
			dev_err(&pdev->dev,
				"Property 'nvidia,i2s-controller' missing or invalid\n");
			ret = -EINVAL;
			goto err;
		}

		machine->pcm_dev = platform_device_register_simple(
					"tegra-pcm-audio", -1, NULL, 0);
		if (IS_ERR(machine->pcm_dev)) {
			dev_err(&pdev->dev,
				"Can't instantiate tegra-pcm-audio\n");
			ret = PTR_ERR(machine->pcm_dev);
			goto err;
		}
	} else {
		if (machine_is_harmony()) {
			card->dapm_routes = harmony_audio_map;
			card->num_dapm_routes = ARRAY_SIZE(harmony_audio_map);
		} else if (machine_is_seaboard()) {
			card->dapm_routes = seaboard_audio_map;
			card->num_dapm_routes = ARRAY_SIZE(seaboard_audio_map);
		} else if (machine_is_kaen()) {
			card->dapm_routes = kaen_audio_map;
			card->num_dapm_routes = ARRAY_SIZE(kaen_audio_map);
		} else {
			card->dapm_routes = aebl_audio_map;
			card->num_dapm_routes = ARRAY_SIZE(aebl_audio_map);
		}
	}

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
	if (ret)
		goto err_unregister;

<<<<<<< HEAD
=======
=======
	if (machine_is_harmony() || machine_is_ventana()) {
		card->dapm_routes = harmony_audio_map;
		card->num_dapm_routes = ARRAY_SIZE(harmony_audio_map);
	} else if (machine_is_seaboard()) {
		card->dapm_routes = seaboard_audio_map;
		card->num_dapm_routes = ARRAY_SIZE(seaboard_audio_map);
	} else if (machine_is_kaen()) {
		card->dapm_routes = kaen_audio_map;
		card->num_dapm_routes = ARRAY_SIZE(kaen_audio_map);
	} else {
		card->dapm_routes = aebl_audio_map;
		card->num_dapm_routes = ARRAY_SIZE(aebl_audio_map);
	}

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	ret = snd_soc_register_card(card);
	if (ret) {
		dev_err(&pdev->dev, "snd_soc_register_card failed (%d)\n",
			ret);
		goto err_fini_utils;
	}

	return 0;

err_fini_utils:
	tegra_asoc_utils_fini(&machine->util_data);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
err_unregister:
	if (!IS_ERR(machine->pcm_dev))
		platform_device_unregister(machine->pcm_dev);
err:
<<<<<<< HEAD
=======
=======
err_free_machine:
	kfree(machine);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return ret;
}

static int __devexit tegra_wm8903_driver_remove(struct platform_device *pdev)
{
	struct snd_soc_card *card = platform_get_drvdata(pdev);
	struct tegra_wm8903 *machine = snd_soc_card_get_drvdata(card);
<<<<<<< HEAD
	struct tegra_wm8903_platform_data *pdata = &machine->pdata;
=======
<<<<<<< HEAD
	struct tegra_wm8903_platform_data *pdata = &machine->pdata;
=======
	struct tegra_wm8903_platform_data *pdata = machine->pdata;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	if (machine->gpio_requested & GPIO_HP_DET)
		snd_soc_jack_free_gpios(&tegra_wm8903_hp_jack,
					1,
					&tegra_wm8903_hp_jack_gpio);
	if (machine->gpio_requested & GPIO_EXT_MIC_EN)
		gpio_free(pdata->gpio_ext_mic_en);
	if (machine->gpio_requested & GPIO_INT_MIC_EN)
		gpio_free(pdata->gpio_int_mic_en);
	if (machine->gpio_requested & GPIO_HP_MUTE)
		gpio_free(pdata->gpio_hp_mute);
	if (machine->gpio_requested & GPIO_SPKR_EN)
		gpio_free(pdata->gpio_spkr_en);
	machine->gpio_requested = 0;

	snd_soc_unregister_card(card);

	tegra_asoc_utils_fini(&machine->util_data);
<<<<<<< HEAD
	if (!IS_ERR(machine->pcm_dev))
		platform_device_unregister(machine->pcm_dev);
=======
<<<<<<< HEAD
	if (!IS_ERR(machine->pcm_dev))
		platform_device_unregister(machine->pcm_dev);
=======

	kfree(machine);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static const struct of_device_id tegra_wm8903_of_match[] __devinitconst = {
	{ .compatible = "nvidia,tegra-audio-wm8903", },
	{},
};

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static struct platform_driver tegra_wm8903_driver = {
	.driver = {
		.name = DRV_NAME,
		.owner = THIS_MODULE,
		.pm = &snd_soc_pm_ops,
<<<<<<< HEAD
		.of_match_table = tegra_wm8903_of_match,
=======
<<<<<<< HEAD
		.of_match_table = tegra_wm8903_of_match,
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	},
	.probe = tegra_wm8903_driver_probe,
	.remove = __devexit_p(tegra_wm8903_driver_remove),
};
<<<<<<< HEAD
module_platform_driver(tegra_wm8903_driver);
=======
<<<<<<< HEAD
module_platform_driver(tegra_wm8903_driver);
=======

static int __init tegra_wm8903_modinit(void)
{
	return platform_driver_register(&tegra_wm8903_driver);
}
module_init(tegra_wm8903_modinit);

static void __exit tegra_wm8903_modexit(void)
{
	platform_driver_unregister(&tegra_wm8903_driver);
}
module_exit(tegra_wm8903_modexit);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra+WM8903 machine ASoC driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:" DRV_NAME);
<<<<<<< HEAD
MODULE_DEVICE_TABLE(of, tegra_wm8903_of_match);
=======
<<<<<<< HEAD
MODULE_DEVICE_TABLE(of, tegra_wm8903_of_match);
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
