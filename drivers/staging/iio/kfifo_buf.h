
#include <linux/kfifo.h>
#include "iio.h"
<<<<<<< HEAD
<<<<<<< HEAD
#include "buffer.h"

struct iio_buffer *iio_kfifo_allocate(struct iio_dev *indio_dev);
void iio_kfifo_free(struct iio_buffer *r);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include "ring_generic.h"

struct iio_kfifo {
	struct iio_ring_buffer ring;
	struct kfifo kf;
	int use_count;
	int update_needed;
	struct mutex use_lock;
};

extern const struct iio_ring_access_funcs kfifo_access_funcs;

struct iio_ring_buffer *iio_kfifo_allocate(struct iio_dev *indio_dev);
void iio_kfifo_free(struct iio_ring_buffer *r);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

