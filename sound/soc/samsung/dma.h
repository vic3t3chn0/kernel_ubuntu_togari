/*
 *  dma.h --
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
<<<<<<< HEAD
 *  ALSA PCM interface for the Samsung SoC
=======
 *  ALSA PCM interface for the Samsung S3C24xx CPU
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
 */

#ifndef _S3C_AUDIO_H
#define _S3C_AUDIO_H

struct s3c_dma_params {
	struct s3c2410_dma_client *client;	/* stream identifier */
	int channel;				/* Channel ID */
	dma_addr_t dma_addr;
	int dma_size;			/* Size of the DMA transfer */
<<<<<<< HEAD
	unsigned ch;
	struct samsung_dma_ops *ops;
};

=======
};

#ifdef CONFIG_SND_SOC_SAMSUNG_USE_DMA_WRAPPER
extern struct snd_soc_platform_driver samsung_asoc_platform;
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif
