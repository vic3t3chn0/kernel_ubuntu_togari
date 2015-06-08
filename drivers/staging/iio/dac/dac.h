/*
 * dac.h - sysfs attributes associated with DACs
 */

#define IIO_DEV_ATTR_OUT_RAW(_num, _store, _addr)				\
<<<<<<< HEAD
	IIO_DEVICE_ATTR(out_voltage##_num##_raw, S_IWUSR, NULL, _store, _addr)
=======
	IIO_DEVICE_ATTR(out##_num##_raw, S_IWUSR, NULL, _store, _addr)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
