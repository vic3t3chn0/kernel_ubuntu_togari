#include <linux/slab.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/workqueue.h>
#include <linux/kfifo.h>
#include <linux/mutex.h>

#include "kfifo_buf.h"

<<<<<<< HEAD
struct iio_kfifo {
	struct iio_buffer buffer;
	struct kfifo kf;
	int update_needed;
};

#define iio_to_kfifo(r) container_of(r, struct iio_kfifo, buffer)
=======
#define iio_to_kfifo(r) container_of(r, struct iio_kfifo, ring)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

static inline int __iio_allocate_kfifo(struct iio_kfifo *buf,
				int bytes_per_datum, int length)
{
	if ((length == 0) || (bytes_per_datum == 0))
		return -EINVAL;

<<<<<<< HEAD
	__iio_update_buffer(&buf->buffer, bytes_per_datum, length);
	return kfifo_alloc(&buf->kf, bytes_per_datum*length, GFP_KERNEL);
}

static int iio_request_update_kfifo(struct iio_buffer *r)
=======
	__iio_update_ring_buffer(&buf->ring, bytes_per_datum, length);
	return kfifo_alloc(&buf->kf, bytes_per_datum*length, GFP_KERNEL);
}

static int iio_request_update_kfifo(struct iio_ring_buffer *r)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
{
	int ret = 0;
	struct iio_kfifo *buf = iio_to_kfifo(r);

<<<<<<< HEAD
	if (!buf->update_needed)
		goto error_ret;
	kfifo_free(&buf->kf);
	ret = __iio_allocate_kfifo(buf, buf->buffer.bytes_per_datum,
				   buf->buffer.length);
error_ret:
	return ret;
}

static int iio_get_length_kfifo(struct iio_buffer *r)
=======
	mutex_lock(&buf->use_lock);
	if (!buf->update_needed)
		goto error_ret;
	if (buf->use_count) {
		ret = -EAGAIN;
		goto error_ret;
	}
	kfifo_free(&buf->kf);
	ret = __iio_allocate_kfifo(buf, buf->ring.bytes_per_datum,
				buf->ring.length);
error_ret:
	mutex_unlock(&buf->use_lock);
	return ret;
}

static void iio_mark_kfifo_in_use(struct iio_ring_buffer *r)
{
	struct iio_kfifo *buf = iio_to_kfifo(r);
	mutex_lock(&buf->use_lock);
	buf->use_count++;
	mutex_unlock(&buf->use_lock);
}

static void iio_unmark_kfifo_in_use(struct iio_ring_buffer *r)
{
	struct iio_kfifo *buf = iio_to_kfifo(r);
	mutex_lock(&buf->use_lock);
	buf->use_count--;
	mutex_unlock(&buf->use_lock);
}

static int iio_get_length_kfifo(struct iio_ring_buffer *r)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
{
	return r->length;
}

<<<<<<< HEAD
static IIO_BUFFER_ENABLE_ATTR;
static IIO_BUFFER_LENGTH_ATTR;

static struct attribute *iio_kfifo_attributes[] = {
	&dev_attr_length.attr,
=======
static inline void __iio_init_kfifo(struct iio_kfifo *kf)
{
	mutex_init(&kf->use_lock);
}

static IIO_RING_ENABLE_ATTR;
static IIO_RING_BYTES_PER_DATUM_ATTR;
static IIO_RING_LENGTH_ATTR;

static struct attribute *iio_kfifo_attributes[] = {
	&dev_attr_length.attr,
	&dev_attr_bytes_per_datum.attr,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	&dev_attr_enable.attr,
	NULL,
};

static struct attribute_group iio_kfifo_attribute_group = {
	.attrs = iio_kfifo_attributes,
<<<<<<< HEAD
	.name = "buffer",
};

static int iio_get_bytes_per_datum_kfifo(struct iio_buffer *r)
{
	return r->bytes_per_datum;
}

static int iio_mark_update_needed_kfifo(struct iio_buffer *r)
{
	struct iio_kfifo *kf = iio_to_kfifo(r);
	kf->update_needed = true;
	return 0;
}

static int iio_set_bytes_per_datum_kfifo(struct iio_buffer *r, size_t bpd)
{
	if (r->bytes_per_datum != bpd) {
		r->bytes_per_datum = bpd;
		iio_mark_update_needed_kfifo(r);
=======
};

static const struct attribute_group *iio_kfifo_attribute_groups[] = {
	&iio_kfifo_attribute_group,
	NULL
};

static void iio_kfifo_release(struct device *dev)
{
	struct iio_ring_buffer *r = to_iio_ring_buffer(dev);
	struct iio_kfifo *kf = iio_to_kfifo(r);
	kfifo_free(&kf->kf);
	kfree(kf);
}

static struct device_type iio_kfifo_type = {
	.release = iio_kfifo_release,
	.groups = iio_kfifo_attribute_groups,
};

struct iio_ring_buffer *iio_kfifo_allocate(struct iio_dev *indio_dev)
{
	struct iio_kfifo *kf;

	kf = kzalloc(sizeof *kf, GFP_KERNEL);
	if (!kf)
		return NULL;
	kf->update_needed = true;
	iio_ring_buffer_init(&kf->ring, indio_dev);
	__iio_init_kfifo(kf);
	kf->ring.dev.type = &iio_kfifo_type;
	device_initialize(&kf->ring.dev);
	kf->ring.dev.parent = &indio_dev->dev;
	kf->ring.dev.bus = &iio_bus_type;
	dev_set_drvdata(&kf->ring.dev, (void *)&(kf->ring));

	return &kf->ring;
}
EXPORT_SYMBOL(iio_kfifo_allocate);

static int iio_get_bytes_per_datum_kfifo(struct iio_ring_buffer *r)
{
	return r->bytes_per_datum;
}

static int iio_set_bytes_per_datum_kfifo(struct iio_ring_buffer *r, size_t bpd)
{
	if (r->bytes_per_datum != bpd) {
		r->bytes_per_datum = bpd;
		if (r->access->mark_param_change)
			r->access->mark_param_change(r);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	}
	return 0;
}

<<<<<<< HEAD
static int iio_set_length_kfifo(struct iio_buffer *r, int length)
{
	if (r->length != length) {
		r->length = length;
		iio_mark_update_needed_kfifo(r);
=======
static int iio_mark_update_needed_kfifo(struct iio_ring_buffer *r)
{
	struct iio_kfifo *kf = iio_to_kfifo(r);
	kf->update_needed = true;
	return 0;
}

static int iio_set_length_kfifo(struct iio_ring_buffer *r, int length)
{
	if (r->length != length) {
		r->length = length;
		if (r->access->mark_param_change)
			r->access->mark_param_change(r);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	}
	return 0;
}

<<<<<<< HEAD
static int iio_store_to_kfifo(struct iio_buffer *r,
=======
void iio_kfifo_free(struct iio_ring_buffer *r)
{
	if (r)
		iio_put_ring_buffer(r);
}
EXPORT_SYMBOL(iio_kfifo_free);

static int iio_store_to_kfifo(struct iio_ring_buffer *r,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
			      u8 *data,
			      s64 timestamp)
{
	int ret;
	struct iio_kfifo *kf = iio_to_kfifo(r);
<<<<<<< HEAD
	ret = kfifo_in(&kf->kf, data, r->bytes_per_datum);
	if (ret != r->bytes_per_datum)
		return -EBUSY;
	return 0;
}

static int iio_read_first_n_kfifo(struct iio_buffer *r,
=======
	u8 *datal = kmalloc(r->bytes_per_datum, GFP_KERNEL);
	memcpy(datal, data, r->bytes_per_datum - sizeof(timestamp));
	memcpy(datal + r->bytes_per_datum - sizeof(timestamp),
		&timestamp, sizeof(timestamp));
	ret = kfifo_in(&kf->kf, data, r->bytes_per_datum);
	if (ret != r->bytes_per_datum) {
		kfree(datal);
		return -EBUSY;
	}
	kfree(datal);
	return 0;
}

static int iio_read_first_n_kfifo(struct iio_ring_buffer *r,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
			   size_t n, char __user *buf)
{
	int ret, copied;
	struct iio_kfifo *kf = iio_to_kfifo(r);

<<<<<<< HEAD
	if (n < r->bytes_per_datum)
		return -EINVAL;

	n = rounddown(n, r->bytes_per_datum);
	ret = kfifo_to_user(&kf->kf, buf, n, &copied);
=======
	ret = kfifo_to_user(&kf->kf, buf, r->bytes_per_datum*n, &copied);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

	return copied;
}

<<<<<<< HEAD
static const struct iio_buffer_access_funcs kfifo_access_funcs = {
	.store_to = &iio_store_to_kfifo,
	.read_first_n = &iio_read_first_n_kfifo,
=======
const struct iio_ring_access_funcs kfifo_access_funcs = {
	.mark_in_use = &iio_mark_kfifo_in_use,
	.unmark_in_use = &iio_unmark_kfifo_in_use,
	.store_to = &iio_store_to_kfifo,
	.read_first_n = &iio_read_first_n_kfifo,
	.mark_param_change = &iio_mark_update_needed_kfifo,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	.request_update = &iio_request_update_kfifo,
	.get_bytes_per_datum = &iio_get_bytes_per_datum_kfifo,
	.set_bytes_per_datum = &iio_set_bytes_per_datum_kfifo,
	.get_length = &iio_get_length_kfifo,
	.set_length = &iio_set_length_kfifo,
};
<<<<<<< HEAD

struct iio_buffer *iio_kfifo_allocate(struct iio_dev *indio_dev)
{
	struct iio_kfifo *kf;

	kf = kzalloc(sizeof *kf, GFP_KERNEL);
	if (!kf)
		return NULL;
	kf->update_needed = true;
	iio_buffer_init(&kf->buffer);
	kf->buffer.attrs = &iio_kfifo_attribute_group;
	kf->buffer.access = &kfifo_access_funcs;

	return &kf->buffer;
}
EXPORT_SYMBOL(iio_kfifo_allocate);

void iio_kfifo_free(struct iio_buffer *r)
{
	kfree(iio_to_kfifo(r));
}
EXPORT_SYMBOL(iio_kfifo_free);
=======
EXPORT_SYMBOL(kfifo_access_funcs);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0

MODULE_LICENSE("GPL");
