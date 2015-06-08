/*
 * sca3000_ring.c -- support VTI sca3000 series accelerometers via SPI
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * Copyright (c) 2009 Jonathan Cameron <jic23@cam.ac.uk>
 *
 */

#include <linux/interrupt.h>
<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/fs.h>
=======
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/device.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/device.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/spi/spi.h>
#include <linux/sysfs.h>
#include <linux/sched.h>
#include <linux/poll.h>

#include "../iio.h"
#include "../sysfs.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "../buffer.h"
#include "../ring_hw.h"
=======
#include "../ring_generic.h"
#include "../ring_hw.h"
#include "accel.h"
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include "../ring_generic.h"
#include "../ring_hw.h"
#include "accel.h"
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include "sca3000.h"

/* RFC / future work
 *
 * The internal ring buffer doesn't actually change what it holds depending
 * on which signals are enabled etc, merely whether you can read them.
 * As such the scan mode selection is somewhat different than for a software
 * ring buffer and changing it actually covers any data already in the buffer.
 * Currently scan elements aren't configured so it doesn't matter.
 */

static int sca3000_read_data(struct sca3000_state *st,
			    uint8_t reg_address_high,
			    u8 **rx_p,
			    int len)
{
	int ret;
	struct spi_message msg;
	struct spi_transfer xfer[2] = {
		{
			.len = 1,
			.tx_buf = st->tx,
		}, {
			.len = len,
		}
	};
	*rx_p = kmalloc(len, GFP_KERNEL);
	if (*rx_p == NULL) {
		ret = -ENOMEM;
		goto error_ret;
	}
	xfer[1].rx_buf = *rx_p;
	st->tx[0] = SCA3000_READ_REG(reg_address_high);
	spi_message_init(&msg);
	spi_message_add_tail(&xfer[0], &msg);
	spi_message_add_tail(&xfer[1], &msg);
	ret = spi_sync(st->us, &msg);
	if (ret) {
		dev_err(get_device(&st->us->dev), "problem reading register");
		goto error_free_rx;
	}

	return 0;
error_free_rx:
	kfree(*rx_p);
error_ret:
	return ret;
}

/**
 * sca3000_read_first_n_hw_rb() - main ring access, pulls data from ring
 * @r:			the ring
 * @count:		number of samples to try and pull
 * @data:		output the actual samples pulled from the hw ring
 *
 * Currently does not provide timestamps.  As the hardware doesn't add them they
 * can only be inferred approximately from ring buffer events such as 50% full
 * and knowledge of when buffer was last emptied.  This is left to userspace.
 **/
<<<<<<< HEAD
<<<<<<< HEAD
static int sca3000_read_first_n_hw_rb(struct iio_buffer *r,
				      size_t count, char __user *buf)
{
	struct iio_hw_buffer *hw_ring = iio_to_hw_buf(r);
	struct iio_dev *indio_dev = hw_ring->private;
	struct sca3000_state *st = iio_priv(indio_dev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int sca3000_read_first_n_hw_rb(struct iio_ring_buffer *r,
				      size_t count, char __user *buf)
{
	struct iio_hw_ring_buffer *hw_ring = iio_to_hw_ring_buf(r);
	struct iio_dev *indio_dev = hw_ring->private;
	struct sca3000_state *st = indio_dev->dev_data;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	u8 *rx;
	int ret, i, num_available, num_read = 0;
	int bytes_per_sample = 1;

	if (st->bpse == 11)
		bytes_per_sample = 2;

	mutex_lock(&st->lock);
	if (count % bytes_per_sample) {
		ret = -EINVAL;
		goto error_ret;
	}

	ret = sca3000_read_data_short(st, SCA3000_REG_ADDR_BUF_COUNT, 1);
	if (ret)
		goto error_ret;
	else
		num_available = st->rx[0];
	/*
	 * num_available is the total number of samples available
	 * i.e. number of time points * number of channels.
	 */
	if (count > num_available * bytes_per_sample)
		num_read = num_available*bytes_per_sample;
	else
		num_read = count;

	ret = sca3000_read_data(st,
				SCA3000_REG_ADDR_RING_OUT,
				&rx, num_read);
	if (ret)
		goto error_ret;

	for (i = 0; i < num_read; i++)
		*(((u16 *)rx) + i) = be16_to_cpup((u16 *)rx + i);

	if (copy_to_user(buf, rx, num_read))
		ret = -EFAULT;
	kfree(rx);
	r->stufftoread = 0;
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : num_read;
}

/* This is only valid with all 3 elements enabled */
<<<<<<< HEAD
<<<<<<< HEAD
static int sca3000_ring_get_length(struct iio_buffer *r)
=======
static int sca3000_ring_get_length(struct iio_ring_buffer *r)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static int sca3000_ring_get_length(struct iio_ring_buffer *r)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return 64;
}

/* only valid if resolution is kept at 11bits */
<<<<<<< HEAD
<<<<<<< HEAD
static int sca3000_ring_get_bytes_per_datum(struct iio_buffer *r)
{
	return 6;
}

static IIO_BUFFER_ENABLE_ATTR;
static IIO_BUFFER_LENGTH_ATTR;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static int sca3000_ring_get_bytes_per_datum(struct iio_ring_buffer *r)
{
	return 6;
}
static void sca3000_ring_release(struct device *dev)
{
	struct iio_ring_buffer *r = to_iio_ring_buffer(dev);
	kfree(iio_to_hw_ring_buf(r));
}

static IIO_RING_ENABLE_ATTR;
static IIO_RING_BYTES_PER_DATUM_ATTR;
static IIO_RING_LENGTH_ATTR;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 * sca3000_query_ring_int() is the hardware ring status interrupt enabled
 **/
static ssize_t sca3000_query_ring_int(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	int ret, val;
<<<<<<< HEAD
<<<<<<< HEAD
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct sca3000_state *st = iio_priv(indio_dev);
=======
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);
	struct iio_dev *indio_dev = ring->indio_dev;
	struct sca3000_state *st = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);
	struct iio_dev *indio_dev = ring->indio_dev;
	struct sca3000_state *st = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	mutex_lock(&st->lock);
	ret = sca3000_read_data_short(st, SCA3000_REG_ADDR_INT_MASK, 1);
	val = st->rx[0];
	mutex_unlock(&st->lock);
	if (ret)
		return ret;

	return sprintf(buf, "%d\n", !!(val & this_attr->address));
}

/**
 * sca3000_set_ring_int() set state of ring status interrupt
 **/
static ssize_t sca3000_set_ring_int(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf,
				      size_t len)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct sca3000_state *st = iio_priv(indio_dev);
=======
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);
	struct iio_dev *indio_dev = ring->indio_dev;
	struct sca3000_state *st = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);
	struct iio_dev *indio_dev = ring->indio_dev;
	struct sca3000_state *st = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	long val;
	int ret;

	mutex_lock(&st->lock);
	ret = strict_strtol(buf, 10, &val);
	if (ret)
		goto error_ret;
	ret = sca3000_read_data_short(st, SCA3000_REG_ADDR_INT_MASK, 1);
	if (ret)
		goto error_ret;
	if (val)
		ret = sca3000_write_reg(st,
					SCA3000_REG_ADDR_INT_MASK,
					st->rx[0] | this_attr->address);
	else
		ret = sca3000_write_reg(st,
					SCA3000_REG_ADDR_INT_MASK,
					st->rx[0] & ~this_attr->address);
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}

static IIO_DEVICE_ATTR(50_percent, S_IRUGO | S_IWUSR,
		       sca3000_query_ring_int,
		       sca3000_set_ring_int,
		       SCA3000_INT_MASK_RING_HALF);

static IIO_DEVICE_ATTR(75_percent, S_IRUGO | S_IWUSR,
		       sca3000_query_ring_int,
		       sca3000_set_ring_int,
		       SCA3000_INT_MASK_RING_THREE_QUARTER);

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/**
 * sca3000_show_ring_bpse() -sysfs function to query bits per sample from ring
 * @dev: ring buffer device
 * @attr: this device attribute
 * @buf: buffer to write to
 **/
static ssize_t sca3000_show_ring_bpse(struct device *dev,
				      struct device_attribute *attr,
				      char *buf)
{
	int len = 0, ret;
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);
	struct iio_dev *indio_dev = ring->indio_dev;
	struct sca3000_state *st = indio_dev->dev_data;

	mutex_lock(&st->lock);
	ret = sca3000_read_data_short(st, SCA3000_REG_ADDR_MODE, 1);
	if (ret)
		goto error_ret;
	if (st->rx[0] & SCA3000_RING_BUF_8BIT)
		len = sprintf(buf, "s8/8\n");
	else
		len = sprintf(buf, "s11/16\n");
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}

/**
 * sca3000_store_ring_bpse() - bits per scan element
 * @dev: ring buffer device
 * @attr: attribute called from
 * @buf: input from userspace
 * @len: length of input
 **/
static ssize_t sca3000_store_ring_bpse(struct device *dev,
				      struct device_attribute *attr,
				      const char *buf,
				      size_t len)
{
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);
	struct iio_dev *indio_dev = ring->indio_dev;
	struct sca3000_state *st = indio_dev->dev_data;
	int ret;

	mutex_lock(&st->lock);

	ret = sca3000_read_data_short(st, SCA3000_REG_ADDR_MODE, 1);
	if (ret)
		goto error_ret;
	if (sysfs_streq(buf, "s8/8")) {
		ret = sca3000_write_reg(st, SCA3000_REG_ADDR_MODE,
					st->rx[0] | SCA3000_RING_BUF_8BIT);
		st->bpse = 8;
	} else if (sysfs_streq(buf, "s11/16")) {
		ret = sca3000_write_reg(st, SCA3000_REG_ADDR_MODE,
					st->rx[0] & ~SCA3000_RING_BUF_8BIT);
		st->bpse = 11;
	} else
		ret = -EINVAL;
error_ret:
	mutex_unlock(&st->lock);

	return ret ? ret : len;
}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static ssize_t sca3000_show_buffer_scale(struct device *dev,
					 struct device_attribute *attr,
					 char *buf)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct sca3000_state *st = iio_priv(indio_dev);
=======
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);
	struct iio_dev *indio_dev = ring->indio_dev;
	struct sca3000_state *st = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct iio_ring_buffer *ring = dev_get_drvdata(dev);
	struct iio_dev *indio_dev = ring->indio_dev;
	struct sca3000_state *st = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return sprintf(buf, "0.%06d\n", 4*st->info->scale);
}

<<<<<<< HEAD
<<<<<<< HEAD
static IIO_DEVICE_ATTR(in_accel_scale,
=======
static IIO_DEVICE_ATTR(accel_scale,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static IIO_DEVICE_ATTR(accel_scale,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		       S_IRUGO,
		       sca3000_show_buffer_scale,
		       NULL,
		       0);

/*
 * Ring buffer attributes
 * This device is a bit unusual in that the sampling frequency and bpse
 * only apply to the ring buffer.  At all times full rate and accuracy
 * is available via direct reading from registers.
 */
static struct attribute *sca3000_ring_attributes[] = {
	&dev_attr_length.attr,
<<<<<<< HEAD
<<<<<<< HEAD
	&dev_attr_enable.attr,
	&iio_dev_attr_50_percent.dev_attr.attr,
	&iio_dev_attr_75_percent.dev_attr.attr,
	&iio_dev_attr_in_accel_scale.dev_attr.attr,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	&dev_attr_bytes_per_datum.attr,
	&dev_attr_enable.attr,
	&iio_dev_attr_50_percent.dev_attr.attr,
	&iio_dev_attr_75_percent.dev_attr.attr,
	&iio_dev_attr_accel_scale.dev_attr.attr,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	NULL,
};

static struct attribute_group sca3000_ring_attr = {
	.attrs = sca3000_ring_attributes,
<<<<<<< HEAD
<<<<<<< HEAD
	.name = "buffer",
};

static struct iio_buffer *sca3000_rb_allocate(struct iio_dev *indio_dev)
{
	struct iio_buffer *buf;
	struct iio_hw_buffer *ring;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

static const struct attribute_group *sca3000_ring_attr_groups[] = {
	&sca3000_ring_attr,
	NULL
};

static struct device_type sca3000_ring_type = {
	.release = sca3000_ring_release,
	.groups = sca3000_ring_attr_groups,
};

static struct iio_ring_buffer *sca3000_rb_allocate(struct iio_dev *indio_dev)
{
	struct iio_ring_buffer *buf;
	struct iio_hw_ring_buffer *ring;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	ring = kzalloc(sizeof *ring, GFP_KERNEL);
	if (!ring)
		return NULL;

	ring->private = indio_dev;
	buf = &ring->buf;
	buf->stufftoread = 0;
<<<<<<< HEAD
<<<<<<< HEAD
	buf->attrs = &sca3000_ring_attr;
	iio_buffer_init(buf);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	iio_ring_buffer_init(buf, indio_dev);
	buf->dev.type = &sca3000_ring_type;
	buf->dev.parent = &indio_dev->dev;
	dev_set_drvdata(&buf->dev, (void *)buf);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return buf;
}

<<<<<<< HEAD
<<<<<<< HEAD
static inline void sca3000_rb_free(struct iio_buffer *r)
{
	kfree(iio_to_hw_buf(r));
}

static const struct iio_buffer_access_funcs sca3000_ring_access_funcs = {
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static inline void sca3000_rb_free(struct iio_ring_buffer *r)
{
	if (r)
		iio_put_ring_buffer(r);
}

static const struct iio_ring_access_funcs sca3000_ring_access_funcs = {
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.read_first_n = &sca3000_read_first_n_hw_rb,
	.get_length = &sca3000_ring_get_length,
	.get_bytes_per_datum = &sca3000_ring_get_bytes_per_datum,
};

int sca3000_configure_ring(struct iio_dev *indio_dev)
{
<<<<<<< HEAD
<<<<<<< HEAD
	indio_dev->buffer = sca3000_rb_allocate(indio_dev);
	if (indio_dev->buffer == NULL)
		return -ENOMEM;
	indio_dev->modes |= INDIO_BUFFER_HARDWARE;

	indio_dev->buffer->access = &sca3000_ring_access_funcs;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	indio_dev->ring = sca3000_rb_allocate(indio_dev);
	if (indio_dev->ring == NULL)
		return -ENOMEM;
	indio_dev->modes |= INDIO_RING_HARDWARE_BUFFER;

	indio_dev->ring->access = &sca3000_ring_access_funcs;

	iio_scan_mask_set(indio_dev->ring, 0);
	iio_scan_mask_set(indio_dev->ring, 1);
	iio_scan_mask_set(indio_dev->ring, 2);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	return 0;
}

void sca3000_unconfigure_ring(struct iio_dev *indio_dev)
{
<<<<<<< HEAD
<<<<<<< HEAD
	sca3000_rb_free(indio_dev->buffer);
=======
	sca3000_rb_free(indio_dev->ring);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	sca3000_rb_free(indio_dev->ring);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

static inline
int __sca3000_hw_ring_state_set(struct iio_dev *indio_dev, bool state)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct sca3000_state *st = iio_priv(indio_dev);
=======
	struct sca3000_state *st = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct sca3000_state *st = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int ret;

	mutex_lock(&st->lock);
	ret = sca3000_read_data_short(st, SCA3000_REG_ADDR_MODE, 1);
	if (ret)
		goto error_ret;
	if (state) {
		printk(KERN_INFO "supposedly enabling ring buffer\n");
		ret = sca3000_write_reg(st,
					SCA3000_REG_ADDR_MODE,
					(st->rx[0] | SCA3000_RING_BUF_ENABLE));
	} else
		ret = sca3000_write_reg(st,
					SCA3000_REG_ADDR_MODE,
					(st->rx[0] & ~SCA3000_RING_BUF_ENABLE));
error_ret:
	mutex_unlock(&st->lock);

	return ret;
}
/**
 * sca3000_hw_ring_preenable() hw ring buffer preenable function
 *
 * Very simple enable function as the chip will allows normal reads
 * during ring buffer operation so as long as it is indeed running
 * before we notify the core, the precise ordering does not matter.
 **/
static int sca3000_hw_ring_preenable(struct iio_dev *indio_dev)
{
	return __sca3000_hw_ring_state_set(indio_dev, 1);
}

static int sca3000_hw_ring_postdisable(struct iio_dev *indio_dev)
{
	return __sca3000_hw_ring_state_set(indio_dev, 0);
}

<<<<<<< HEAD
<<<<<<< HEAD
static const struct iio_buffer_setup_ops sca3000_ring_setup_ops = {
=======
static const struct iio_ring_setup_ops sca3000_ring_setup_ops = {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static const struct iio_ring_setup_ops sca3000_ring_setup_ops = {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.preenable = &sca3000_hw_ring_preenable,
	.postdisable = &sca3000_hw_ring_postdisable,
};

void sca3000_register_ring_funcs(struct iio_dev *indio_dev)
{
<<<<<<< HEAD
<<<<<<< HEAD
	indio_dev->setup_ops = &sca3000_ring_setup_ops;
=======
	indio_dev->ring->setup_ops = &sca3000_ring_setup_ops;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	indio_dev->ring->setup_ops = &sca3000_ring_setup_ops;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
}

/**
 * sca3000_ring_int_process() ring specific interrupt handling.
 *
 * This is only split from the main interrupt handler so as to
 * reduce the amount of code if the ring buffer is not enabled.
 **/
<<<<<<< HEAD
<<<<<<< HEAD
void sca3000_ring_int_process(u8 val, struct iio_buffer *ring)
=======
void sca3000_ring_int_process(u8 val, struct iio_ring_buffer *ring)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
void sca3000_ring_int_process(u8 val, struct iio_ring_buffer *ring)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	if (val & (SCA3000_INT_STATUS_THREE_QUARTERS |
		   SCA3000_INT_STATUS_HALF)) {
		ring->stufftoread = true;
		wake_up_interruptible(&ring->pollq);
	}
}
