/* linux/arch/arm/plat-samsung/include/plat/dma-s3c24xx.h
 *
 * Copyright (C) 2006 Simtec Electronics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * Samsung S3C24XX DMA support - per SoC functions
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <plat/dma-core.h>

<<<<<<< HEAD
extern struct bus_type dma_subsys;
=======
extern struct sysdev_class dma_sysclass;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
extern struct s3c2410_dma_chan s3c2410_chans[S3C_DMA_CHANNELS];

#define DMA_CH_VALID		(1<<31)
#define DMA_CH_NEVER		(1<<30)

<<<<<<< HEAD
=======
struct s3c24xx_dma_addr {
	unsigned long		from;
	unsigned long		to;
};

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
/* struct s3c24xx_dma_map
 *
 * this holds the mapping information for the channel selected
 * to be connected to the specified device
*/

struct s3c24xx_dma_map {
	const char		*name;
<<<<<<< HEAD
=======
	struct s3c24xx_dma_addr  hw_addr;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9

	unsigned long		 channels[S3C_DMA_CHANNELS];
	unsigned long		 channels_rx[S3C_DMA_CHANNELS];
};

struct s3c24xx_dma_selection {
	struct s3c24xx_dma_map	*map;
	unsigned long		 map_size;
	unsigned long		 dcon_mask;

	void	(*select)(struct s3c2410_dma_chan *chan,
			  struct s3c24xx_dma_map *map);

	void	(*direction)(struct s3c2410_dma_chan *chan,
			     struct s3c24xx_dma_map *map,
<<<<<<< HEAD
			     enum dma_data_direction dir);
=======
			     enum s3c2410_dmasrc dir);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
};

extern int s3c24xx_dma_init_map(struct s3c24xx_dma_selection *sel);

/* struct s3c24xx_dma_order_ch
 *
 * channel map for one of the `enum dma_ch` dma channels. the list
 * entry contains a set of low-level channel numbers, orred with
 * DMA_CH_VALID, which are checked in the order in the array.
*/

struct s3c24xx_dma_order_ch {
	unsigned int	list[S3C_DMA_CHANNELS];	/* list of channels */
	unsigned int	flags;				/* flags */
};

/* struct s3c24xx_dma_order
 *
 * information provided by either the core or the board to give the
 * dma system a hint on how to allocate channels
*/

struct s3c24xx_dma_order {
	struct s3c24xx_dma_order_ch	channels[DMACH_MAX];
};

extern int s3c24xx_dma_order_set(struct s3c24xx_dma_order *map);

/* DMA init code, called from the cpu support code */

extern int s3c2410_dma_init(void);

extern int s3c24xx_dma_init(unsigned int channels, unsigned int irq,
			    unsigned int stride);
