/*  Copyright (C) 2010 Texas Instruments
    Author: Shubhrajyoti Datta <shubhrajyoti@ti.com>
    Acknowledgement: Jonathan Cameron <jic23@cam.ac.uk> for valuable inputs.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include <linux/module.h>
#include <linux/init.h>
#include <linux/i2c.h>
#include <linux/slab.h>
#include <linux/types.h>
#include "../iio.h"
#include "../sysfs.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include "magnet.h"
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include "magnet.h"
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define HMC5843_I2C_ADDRESS			0x1E

#define HMC5843_CONFIG_REG_A			0x00
#define HMC5843_CONFIG_REG_B			0x01
#define HMC5843_MODE_REG			0x02
#define HMC5843_DATA_OUT_X_MSB_REG		0x03
#define HMC5843_DATA_OUT_X_LSB_REG		0x04
#define HMC5843_DATA_OUT_Y_MSB_REG		0x05
#define HMC5843_DATA_OUT_Y_LSB_REG		0x06
#define HMC5843_DATA_OUT_Z_MSB_REG		0x07
#define HMC5843_DATA_OUT_Z_LSB_REG		0x08
#define HMC5843_STATUS_REG			0x09
#define HMC5843_ID_REG_A			0x0A
#define HMC5843_ID_REG_B			0x0B
#define HMC5843_ID_REG_C			0x0C

#define HMC5843_ID_REG_LENGTH			0x03
#define HMC5843_ID_STRING			"H43"

/*
 * Range settings in  (+-)Ga
 * */
#define RANGE_GAIN_OFFSET			0x05

#define	RANGE_0_7				0x00
#define	RANGE_1_0				0x01 /* default */
#define	RANGE_1_5				0x02
#define	RANGE_2_0				0x03
#define	RANGE_3_2				0x04
#define	RANGE_3_8				0x05
#define	RANGE_4_5				0x06
#define	RANGE_6_5				0x07 /* Not recommended */

/*
 * Device status
 */
<<<<<<< HEAD
<<<<<<< HEAD
#define	DATA_READY				0x01
#define	DATA_OUTPUT_LOCK			0x02
#define	VOLTAGE_REGULATOR_ENABLED		0x04
=======
#define	DATA_READY  				0x01
#define	DATA_OUTPUT_LOCK  			0x02
#define	VOLTAGE_REGULATOR_ENABLED  		0x04
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#define	DATA_READY  				0x01
#define	DATA_OUTPUT_LOCK  			0x02
#define	VOLTAGE_REGULATOR_ENABLED  		0x04
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * Mode register configuration
 */
#define	MODE_CONVERSION_CONTINUOUS		0x00
#define	MODE_CONVERSION_SINGLE			0x01
#define	MODE_IDLE				0x02
#define	MODE_SLEEP				0x03

/* Minimum Data Output Rate in 1/10 Hz  */
#define RATE_OFFSET				0x02
#define RATE_BITMASK				0x1C
#define	RATE_5					0x00
#define	RATE_10					0x01
#define	RATE_20					0x02
#define	RATE_50					0x03
#define	RATE_100				0x04
#define	RATE_200				0x05
#define	RATE_500				0x06
#define	RATE_NOT_USED				0x07

/*
<<<<<<< HEAD
<<<<<<< HEAD
 * Device Configuration
 */
#define	CONF_NORMAL				0x00
=======
 * Device Configutration
 */
#define	CONF_NORMAL  				0x00
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Device Configutration
 */
#define	CONF_NORMAL  				0x00
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#define	CONF_POSITIVE_BIAS			0x01
#define	CONF_NEGATIVE_BIAS			0x02
#define	CONF_NOT_USED				0x03
#define	MEAS_CONF_MASK				0x03

<<<<<<< HEAD
<<<<<<< HEAD
static int hmc5843_regval_to_nanoscale[] = {
	6173, 7692, 10309, 12821, 18868, 21739, 25641, 35714
};

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static const char *regval_to_scale[] = {
	"0.0000006173",
	"0.0000007692",
	"0.0000010309",
	"0.0000012821",
	"0.0000018868",
	"0.0000021739",
	"0.0000025641",
	"0.0000035714",
};
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static const int regval_to_input_field_mg[] = {
	700,
	1000,
	1500,
	2000,
	3200,
	3800,
	4500,
	6500
};
<<<<<<< HEAD
<<<<<<< HEAD
static const char * const regval_to_samp_freq[] = {
=======
static const char *regval_to_samp_freq[] = {
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static const char *regval_to_samp_freq[] = {
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	"0.5",
	"1",
	"2",
	"5",
	"10",
	"20",
	"50",
};

/* Addresses to scan: 0x1E */
static const unsigned short normal_i2c[] = { HMC5843_I2C_ADDRESS,
							I2C_CLIENT_END };

/* Each client has this additional data */
struct hmc5843_data {
<<<<<<< HEAD
<<<<<<< HEAD
=======
	struct iio_dev	*indio_dev;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct iio_dev	*indio_dev;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct mutex lock;
	u8		rate;
	u8		meas_conf;
	u8		operating_mode;
	u8		range;
};

static void hmc5843_init_client(struct i2c_client *client);

static s32 hmc5843_configure(struct i2c_client *client,
				       u8 operating_mode)
{
	/* The lower two bits contain the current conversion mode */
	return i2c_smbus_write_byte_data(client,
					HMC5843_MODE_REG,
					(operating_mode & 0x03));
}

<<<<<<< HEAD
<<<<<<< HEAD
/* Return the measurement value from the specified channel */
static int hmc5843_read_measurement(struct iio_dev *indio_dev,
				    int address,
				    int *val)
{
	struct i2c_client *client = to_i2c_client(indio_dev->dev.parent);
	struct hmc5843_data *data = iio_priv(indio_dev);
	s32 result;

	mutex_lock(&data->lock);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* Return the measurement value from the  specified channel */
static ssize_t hmc5843_read_measurement(struct device *dev,
		struct device_attribute *attr,
		char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct i2c_client *client = to_i2c_client(indio_dev->dev.parent);
	s16 coordinate_val;
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	struct hmc5843_data *data = indio_dev->dev_data;
	s32 result;

	mutex_lock(&data->lock);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	result = i2c_smbus_read_byte_data(client, HMC5843_STATUS_REG);
	while (!(result & DATA_READY))
		result = i2c_smbus_read_byte_data(client, HMC5843_STATUS_REG);

<<<<<<< HEAD
<<<<<<< HEAD
	result = i2c_smbus_read_word_data(client, address);
=======
	result = i2c_smbus_read_word_data(client, this_attr->address);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	result = i2c_smbus_read_word_data(client, this_attr->address);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	mutex_unlock(&data->lock);
	if (result < 0)
		return -EINVAL;

<<<<<<< HEAD
<<<<<<< HEAD
	*val	= (s16)swab16((u16)result);
	return IIO_VAL_INT;
}

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	coordinate_val	= (s16)swab16((u16)result);
	return sprintf(buf, "%d\n", coordinate_val);
}
static IIO_DEV_ATTR_MAGN_X(hmc5843_read_measurement,
		HMC5843_DATA_OUT_X_MSB_REG);
static IIO_DEV_ATTR_MAGN_Y(hmc5843_read_measurement,
		HMC5843_DATA_OUT_Y_MSB_REG);
static IIO_DEV_ATTR_MAGN_Z(hmc5843_read_measurement,
		HMC5843_DATA_OUT_Z_MSB_REG);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * From the datasheet
 * 0 - Continuous-Conversion Mode: In continuous-conversion mode, the
<<<<<<< HEAD
<<<<<<< HEAD
 * device continuously performs conversions and places the result in the
=======
 * device continuously performs conversions an places the result in the
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * device continuously performs conversions an places the result in the
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * data register.
 *
 * 1 - Single-Conversion Mode : device performs a single measurement,
 *  sets RDY high and returned to sleep mode
 *
 * 2 - Idle Mode :  Device is placed in idle mode.
 *
 * 3 - Sleep Mode. Device is placed in sleep mode.
 *
 */
static ssize_t hmc5843_show_operating_mode(struct device *dev,
					struct device_attribute *attr,
					char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
<<<<<<< HEAD
<<<<<<< HEAD
	struct hmc5843_data *data = iio_priv(indio_dev);
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return sprintf(buf, "%d\n", data->operating_mode);
}

static ssize_t hmc5843_set_operating_mode(struct device *dev,
				struct device_attribute *attr,
				const char *buf,
				size_t count)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct i2c_client *client = to_i2c_client(indio_dev->dev.parent);
<<<<<<< HEAD
<<<<<<< HEAD
	struct hmc5843_data *data = iio_priv(indio_dev);
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	unsigned long operating_mode = 0;
	s32 status;
	int error;
	mutex_lock(&data->lock);
	error = strict_strtoul(buf, 10, &operating_mode);
	if (error) {
		count = error;
		goto exit;
	}
	dev_dbg(dev, "set Conversion mode to %lu\n", operating_mode);
	if (operating_mode > MODE_SLEEP) {
		count = -EINVAL;
		goto exit;
	}

	status = i2c_smbus_write_byte_data(client, this_attr->address,
					operating_mode);
	if (status) {
		count = -EINVAL;
		goto exit;
	}
	data->operating_mode = operating_mode;

exit:
	mutex_unlock(&data->lock);
	return count;
}
static IIO_DEVICE_ATTR(operating_mode,
			S_IWUSR | S_IRUGO,
			hmc5843_show_operating_mode,
			hmc5843_set_operating_mode,
			HMC5843_MODE_REG);

/*
 * API for setting the measurement configuration to
 * Normal, Positive bias and Negative bias
 * From the datasheet
 *
 * Normal measurement configuration (default): In normal measurement
 * configuration the device follows normal measurement flow. Pins BP and BN
 * are left floating and high impedance.
 *
 * Positive bias configuration: In positive bias configuration, a positive
 * current is forced across the resistive load on pins BP and BN.
 *
 * Negative bias configuration. In negative bias configuration, a negative
 * current is forced across the resistive load on pins BP and BN.
 *
 */
static s32 hmc5843_set_meas_conf(struct i2c_client *client,
				      u8 meas_conf)
{
	struct hmc5843_data *data = i2c_get_clientdata(client);
	u8 reg_val;
	reg_val = (meas_conf & MEAS_CONF_MASK) |  (data->rate << RATE_OFFSET);
	return i2c_smbus_write_byte_data(client, HMC5843_CONFIG_REG_A, reg_val);
}

static ssize_t hmc5843_show_measurement_configuration(struct device *dev,
						struct device_attribute *attr,
						char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
<<<<<<< HEAD
<<<<<<< HEAD
	struct hmc5843_data *data = iio_priv(indio_dev);
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return sprintf(buf, "%d\n", data->meas_conf);
}

static ssize_t hmc5843_set_measurement_configuration(struct device *dev,
						struct device_attribute *attr,
						const char *buf,
						size_t count)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct i2c_client *client = to_i2c_client(indio_dev->dev.parent);
	struct hmc5843_data *data = i2c_get_clientdata(client);
	unsigned long meas_conf = 0;
	int error = strict_strtoul(buf, 10, &meas_conf);
	if (error)
		return error;
	mutex_lock(&data->lock);

	dev_dbg(dev, "set mode to %lu\n", meas_conf);
	if (hmc5843_set_meas_conf(client, meas_conf)) {
		count = -EINVAL;
		goto exit;
	}
	data->meas_conf = meas_conf;

exit:
	mutex_unlock(&data->lock);
	return count;
}
static IIO_DEVICE_ATTR(meas_conf,
			S_IWUSR | S_IRUGO,
			hmc5843_show_measurement_configuration,
			hmc5843_set_measurement_configuration,
			0);

/*
 * From Datasheet
 * The table shows the minimum data output
 * Value	| Minimum data output rate(Hz)
 * 0		| 0.5
 * 1		| 1
 * 2		| 2
 * 3		| 5
 * 4		| 10 (default)
 * 5		| 20
 * 6		| 50
 * 7		| Not used
 */
static IIO_CONST_ATTR_SAMP_FREQ_AVAIL("0.5 1 2 5 10 20 50");

static s32 hmc5843_set_rate(struct i2c_client *client,
				u8 rate)
{
	struct hmc5843_data *data = i2c_get_clientdata(client);
	u8 reg_val;

	reg_val = (data->meas_conf) |  (rate << RATE_OFFSET);
	if (rate >= RATE_NOT_USED) {
		dev_err(&client->dev,
<<<<<<< HEAD
<<<<<<< HEAD
			"This data output rate is not supported\n");
=======
			"This data output rate is not supported \n");
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
			"This data output rate is not supported \n");
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
		return -EINVAL;
	}
	return i2c_smbus_write_byte_data(client, HMC5843_CONFIG_REG_A, reg_val);
}

static ssize_t set_sampling_frequency(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t count)
{

	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct i2c_client *client = to_i2c_client(indio_dev->dev.parent);
<<<<<<< HEAD
<<<<<<< HEAD
	struct hmc5843_data *data = iio_priv(indio_dev);
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long rate = 0;

	if (strncmp(buf, "0.5" , 3) == 0)
		rate = RATE_5;
	else if (strncmp(buf, "1" , 1) == 0)
		rate = RATE_10;
	else if (strncmp(buf, "2", 1) == 0)
		rate = RATE_20;
	else if (strncmp(buf, "5", 1) == 0)
		rate = RATE_50;
	else if (strncmp(buf, "10", 2) == 0)
		rate = RATE_100;
	else if (strncmp(buf, "20" , 2) == 0)
		rate = RATE_200;
	else if (strncmp(buf, "50" , 2) == 0)
		rate = RATE_500;
	else
		return -EINVAL;

	mutex_lock(&data->lock);
	dev_dbg(dev, "set rate to %lu\n", rate);
	if (hmc5843_set_rate(client, rate)) {
		count = -EINVAL;
		goto exit;
	}
	data->rate = rate;

exit:
	mutex_unlock(&data->lock);
	return count;
}

static ssize_t show_sampling_frequency(struct device *dev,
			struct device_attribute *attr, char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct i2c_client *client = to_i2c_client(indio_dev->dev.parent);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
	s32 rate;

	rate = i2c_smbus_read_byte_data(client,  this_attr->address);
	if (rate < 0)
		return rate;
	rate = (rate & RATE_BITMASK) >> RATE_OFFSET;
	return sprintf(buf, "%s\n", regval_to_samp_freq[rate]);
}
static IIO_DEVICE_ATTR(sampling_frequency,
			S_IWUSR | S_IRUGO,
			show_sampling_frequency,
			set_sampling_frequency,
			HMC5843_CONFIG_REG_A);

/*
 * From Datasheet
 *	Nominal gain settings
 * Value	| Sensor Input Field Range(Ga)	| Gain(counts/ milli-gauss)
 *0		|(+-)0.7			|1620
 *1		|(+-)1.0			|1300
 *2		|(+-)1.5			|970
 *3		|(+-)2.0			|780
 *4		|(+-)3.2			|530
 *5		|(+-)3.8			|460
 *6		|(+-)4.5			|390
 *7		|(+-)6.5			|280
 */
static ssize_t show_range(struct device *dev,
				struct device_attribute *attr,
				char *buf)
{
	u8 range;
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
<<<<<<< HEAD
<<<<<<< HEAD
	struct hmc5843_data *data = iio_priv(indio_dev);
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	range = data->range;
	return sprintf(buf, "%d\n", regval_to_input_field_mg[range]);
}

static ssize_t set_range(struct device *dev,
			struct device_attribute *attr,
			const char *buf,
			size_t count)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct i2c_client *client = to_i2c_client(indio_dev->dev.parent);
	struct iio_dev_attr *this_attr = to_iio_dev_attr(attr);
<<<<<<< HEAD
<<<<<<< HEAD
	struct hmc5843_data *data = iio_priv(indio_dev);
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	struct hmc5843_data *data = indio_dev->dev_data;
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	unsigned long range = 0;
	int error;
	mutex_lock(&data->lock);
	error = strict_strtoul(buf, 10, &range);
	if (error) {
		count = error;
		goto exit;
	}
	dev_dbg(dev, "set range to %lu\n", range);

	if (range > RANGE_6_5) {
		count = -EINVAL;
		goto exit;
	}

	data->range = range;
	range = range << RANGE_GAIN_OFFSET;
	if (i2c_smbus_write_byte_data(client, this_attr->address, range))
		count = -EINVAL;

exit:
	mutex_unlock(&data->lock);
	return count;

}
<<<<<<< HEAD
<<<<<<< HEAD
static IIO_DEVICE_ATTR(in_magn_range,
=======
static IIO_DEVICE_ATTR(magn_range,
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
static IIO_DEVICE_ATTR(magn_range,
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			S_IWUSR | S_IRUGO,
			show_range,
			set_range,
			HMC5843_CONFIG_REG_B);

<<<<<<< HEAD
<<<<<<< HEAD
static int hmc5843_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *chan,
			    int *val, int *val2,
			    long mask)
{
	struct hmc5843_data *data = iio_priv(indio_dev);

	switch (mask) {
	case 0:
		return hmc5843_read_measurement(indio_dev,
						chan->address,
						val);
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = hmc5843_regval_to_nanoscale[data->range];
		return IIO_VAL_INT_PLUS_NANO;
	};
	return -EINVAL;
}

#define HMC5843_CHANNEL(axis, add)					\
	{								\
		.type = IIO_MAGN,					\
		.modified = 1,						\
		.channel2 = IIO_MOD_##axis,				\
		.info_mask = IIO_CHAN_INFO_SCALE_SHARED_BIT,		\
		.address = add						\
	}

static const struct iio_chan_spec hmc5843_channels[] = {
	HMC5843_CHANNEL(X, HMC5843_DATA_OUT_X_MSB_REG),
	HMC5843_CHANNEL(Y, HMC5843_DATA_OUT_Y_MSB_REG),
	HMC5843_CHANNEL(Z, HMC5843_DATA_OUT_Z_MSB_REG),
};
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static ssize_t show_scale(struct device *dev,
			struct device_attribute *attr,
			char *buf)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);
	struct hmc5843_data *data = indio_dev->dev_data;
	return strlen(strcpy(buf, regval_to_scale[data->range]));
}
static IIO_DEVICE_ATTR(magn_scale,
			S_IRUGO,
			show_scale,
			NULL , 0);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static struct attribute *hmc5843_attributes[] = {
	&iio_dev_attr_meas_conf.dev_attr.attr,
	&iio_dev_attr_operating_mode.dev_attr.attr,
	&iio_dev_attr_sampling_frequency.dev_attr.attr,
<<<<<<< HEAD
<<<<<<< HEAD
	&iio_dev_attr_in_magn_range.dev_attr.attr,
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	&iio_dev_attr_magn_range.dev_attr.attr,
	&iio_dev_attr_magn_scale.dev_attr.attr,
	&iio_dev_attr_magn_x_raw.dev_attr.attr,
	&iio_dev_attr_magn_y_raw.dev_attr.attr,
	&iio_dev_attr_magn_z_raw.dev_attr.attr,
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	&iio_const_attr_sampling_frequency_available.dev_attr.attr,
	NULL
};

static const struct attribute_group hmc5843_group = {
	.attrs = hmc5843_attributes,
};

static int hmc5843_detect(struct i2c_client *client,
			  struct i2c_board_info *info)
{
	unsigned char id_str[HMC5843_ID_REG_LENGTH];

	if (client->addr != HMC5843_I2C_ADDRESS)
		return -ENODEV;

	if (i2c_smbus_read_i2c_block_data(client, HMC5843_ID_REG_A,
				HMC5843_ID_REG_LENGTH, id_str)
			!= HMC5843_ID_REG_LENGTH)
		return -ENODEV;

	if (0 != strncmp(id_str, HMC5843_ID_STRING, HMC5843_ID_REG_LENGTH))
		return -ENODEV;

	return 0;
}

/* Called when we have found a new HMC5843. */
static void hmc5843_init_client(struct i2c_client *client)
{
	struct iio_dev *indio_dev = i2c_get_clientdata(client);
	struct hmc5843_data *data = iio_priv(indio_dev);

	hmc5843_set_meas_conf(client, data->meas_conf);
	hmc5843_set_rate(client, data->rate);
	hmc5843_configure(client, data->operating_mode);
	i2c_smbus_write_byte_data(client, HMC5843_CONFIG_REG_B, data->range);
	mutex_init(&data->lock);
	pr_info("HMC5843 initialized\n");
}

static const struct iio_info hmc5843_info = {
	.attrs = &hmc5843_group,
<<<<<<< HEAD
<<<<<<< HEAD
	.read_raw = &hmc5843_read_raw,
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.driver_module = THIS_MODULE,
};

static int hmc5843_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct hmc5843_data *data;
<<<<<<< HEAD
<<<<<<< HEAD
	struct iio_dev *indio_dev;
	int err = 0;

	indio_dev = iio_allocate_device(sizeof(*data));
	if (indio_dev == NULL) {
		err = -ENOMEM;
		goto exit;
	}
	data = iio_priv(indio_dev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int err = 0;

	data = kzalloc(sizeof(struct hmc5843_data), GFP_KERNEL);
	if (!data) {
		err = -ENOMEM;
		goto exit;
	}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	/* default settings at probe */

	data->meas_conf = CONF_NORMAL;
	data->range = RANGE_1_0;
	data->operating_mode = MODE_CONVERSION_CONTINUOUS;

<<<<<<< HEAD
<<<<<<< HEAD
	i2c_set_clientdata(client, indio_dev);
=======
	i2c_set_clientdata(client, data);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	i2c_set_clientdata(client, data);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

	/* Initialize the HMC5843 chip */
	hmc5843_init_client(client);

<<<<<<< HEAD
<<<<<<< HEAD
	indio_dev->info = &hmc5843_info;
	indio_dev->name = id->name;
	indio_dev->channels = hmc5843_channels;
	indio_dev->num_channels = ARRAY_SIZE(hmc5843_channels);
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	err = iio_device_register(indio_dev);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	data->indio_dev = iio_allocate_device(0);
	if (!data->indio_dev) {
		err = -ENOMEM;
		goto exit_free1;
	}
	data->indio_dev->info = &hmc5843_info;
	data->indio_dev->dev.parent = &client->dev;
	data->indio_dev->dev_data = (void *)(data);
	data->indio_dev->modes = INDIO_DIRECT_MODE;
	err = iio_device_register(data->indio_dev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	if (err)
		goto exit_free2;
	return 0;
exit_free2:
<<<<<<< HEAD
<<<<<<< HEAD
	iio_free_device(indio_dev);
=======
	iio_free_device(data->indio_dev);
exit_free1:
	kfree(data);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	iio_free_device(data->indio_dev);
exit_free1:
	kfree(data);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
exit:
	return err;
}

static int hmc5843_remove(struct i2c_client *client)
{
<<<<<<< HEAD
<<<<<<< HEAD
	struct iio_dev *indio_dev = i2c_get_clientdata(client);

	iio_device_unregister(indio_dev);
	 /*  sleep mode to save power */
	hmc5843_configure(client, MODE_SLEEP);
	iio_free_device(indio_dev);

	return 0;
}

#ifdef CONFIG_PM_SLEEP
static int hmc5843_suspend(struct device *dev)
{
	hmc5843_configure(to_i2c_client(dev), MODE_SLEEP);
	return 0;
}

static int hmc5843_resume(struct device *dev)
{
	struct hmc5843_data *data = i2c_get_clientdata(to_i2c_client(dev));
	hmc5843_configure(to_i2c_client(dev), data->operating_mode);
	return 0;
}

static SIMPLE_DEV_PM_OPS(hmc5843_pm_ops, hmc5843_suspend, hmc5843_resume);
#define HMC5843_PM_OPS (&hmc5843_pm_ops)
#else
#define HMC5843_PM_OPS NULL
#endif

=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	struct hmc5843_data *data = i2c_get_clientdata(client);
	 /*  sleep mode to save power */
	hmc5843_configure(client, MODE_SLEEP);
	iio_device_unregister(data->indio_dev);
	kfree(i2c_get_clientdata(client));
	return 0;
}

static int hmc5843_suspend(struct i2c_client *client, pm_message_t mesg)
{
	hmc5843_configure(client, MODE_SLEEP);
	return 0;
}

static int hmc5843_resume(struct i2c_client *client)
{
	struct hmc5843_data *data = i2c_get_clientdata(client);
	hmc5843_configure(client, data->operating_mode);
	return 0;
}

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
static const struct i2c_device_id hmc5843_id[] = {
	{ "hmc5843", 0 },
	{ }
};
<<<<<<< HEAD
<<<<<<< HEAD
MODULE_DEVICE_TABLE(i2c, hmc5843_id);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

static struct i2c_driver hmc5843_driver = {
	.driver = {
		.name	= "hmc5843",
<<<<<<< HEAD
<<<<<<< HEAD
		.pm	= HMC5843_PM_OPS,
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	},
	.id_table	= hmc5843_id,
	.probe		= hmc5843_probe,
	.remove		= hmc5843_remove,
	.detect		= hmc5843_detect,
	.address_list	= normal_i2c,
<<<<<<< HEAD
<<<<<<< HEAD
};
module_i2c_driver(hmc5843_driver);
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	.suspend	= hmc5843_suspend,
	.resume		= hmc5843_resume,
};

static int __init hmc5843_init(void)
{
	return i2c_add_driver(&hmc5843_driver);
}

static void __exit hmc5843_exit(void)
{
	i2c_del_driver(&hmc5843_driver);
}
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

MODULE_AUTHOR("Shubhrajyoti Datta <shubhrajyoti@ti.com");
MODULE_DESCRIPTION("HMC5843 driver");
MODULE_LICENSE("GPL");
<<<<<<< HEAD
<<<<<<< HEAD
=======

module_init(hmc5843_init);
module_exit(hmc5843_exit);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

module_init(hmc5843_init);
module_exit(hmc5843_exit);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
