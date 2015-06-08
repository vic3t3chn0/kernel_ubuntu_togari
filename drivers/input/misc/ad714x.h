/*
 * AD714X CapTouch Programmable Controller driver (bus interfaces)
 *
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright 2009-2011 Analog Devices Inc.
=======
 * Copyright 2009 Analog Devices Inc.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Copyright 2009 Analog Devices Inc.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Licensed under the GPL-2 or later.
 */

#ifndef _AD714X_H_
#define _AD714X_H_

#include <linux/types.h>

<<<<<<< HEAD
<<<<<<< HEAD
#define STAGE_NUM              12

struct device;
struct ad714x_platform_data;
struct ad714x_driver_data;
struct ad714x_chip;

typedef int (*ad714x_read_t)(struct ad714x_chip *, unsigned short, unsigned short *, size_t);
typedef int (*ad714x_write_t)(struct ad714x_chip *, unsigned short, unsigned short);

struct ad714x_chip {
	unsigned short l_state;
	unsigned short h_state;
	unsigned short c_state;
	unsigned short adc_reg[STAGE_NUM];
	unsigned short amb_reg[STAGE_NUM];
	unsigned short sensor_val[STAGE_NUM];

	struct ad714x_platform_data *hw;
	struct ad714x_driver_data *sw;

	int irq;
	struct device *dev;
	ad714x_read_t read;
	ad714x_write_t write;

	struct mutex mutex;

	unsigned product;
	unsigned version;

	__be16 xfer_buf[16] ____cacheline_aligned;

};
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct device;
struct ad714x_chip;

typedef int (*ad714x_read_t)(struct device *, unsigned short, unsigned short *);
typedef int (*ad714x_write_t)(struct device *, unsigned short, unsigned short);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

int ad714x_disable(struct ad714x_chip *ad714x);
int ad714x_enable(struct ad714x_chip *ad714x);
struct ad714x_chip *ad714x_probe(struct device *dev, u16 bus_type, int irq,
				 ad714x_read_t read, ad714x_write_t write);
void ad714x_remove(struct ad714x_chip *ad714x);

#endif
