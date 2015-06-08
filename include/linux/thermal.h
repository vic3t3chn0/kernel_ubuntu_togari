/*
 *  thermal.h  ($Revision: 0 $)
 *
 *  Copyright (C) 2008  Intel Corp
 *  Copyright (C) 2008  Zhang Rui <rui.zhang@intel.com>
 *  Copyright (C) 2008  Sujith Thomas <sujith.thomas@intel.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License.
 *
 *  This program is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  59 Temple Place, Suite 330, Boston, MA 02111-1307 USA.
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#ifndef __THERMAL_H__
#define __THERMAL_H__

#include <linux/idr.h>
#include <linux/device.h>
#include <linux/workqueue.h>

struct thermal_zone_device;
struct thermal_cooling_device;

enum thermal_device_mode {
	THERMAL_DEVICE_DISABLED = 0,
	THERMAL_DEVICE_ENABLED,
};

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
enum thermal_trip_activation_mode {
	THERMAL_TRIP_ACTIVATION_DISABLED = 0,
	THERMAL_TRIP_ACTIVATION_ENABLED,
};

<<<<<<< HEAD
=======
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
enum thermal_trip_type {
	THERMAL_TRIP_ACTIVE = 0,
	THERMAL_TRIP_PASSIVE,
	THERMAL_TRIP_HOT,
	THERMAL_TRIP_CRITICAL,
<<<<<<< HEAD
	THERMAL_TRIP_CONFIGURABLE_HI,
	THERMAL_TRIP_CONFIGURABLE_LOW,
	THERMAL_TRIP_CRITICAL_LOW,
=======
<<<<<<< HEAD
	THERMAL_TRIP_CONFIGURABLE_HI,
	THERMAL_TRIP_CONFIGURABLE_LOW,
	THERMAL_TRIP_CRITICAL_LOW,
=======
	THERMAL_TRIP_STATE_ACTIVE,
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};

struct thermal_zone_device_ops {
	int (*bind) (struct thermal_zone_device *,
		     struct thermal_cooling_device *);
	int (*unbind) (struct thermal_zone_device *,
		       struct thermal_cooling_device *);
	int (*get_temp) (struct thermal_zone_device *, unsigned long *);
	int (*get_mode) (struct thermal_zone_device *,
			 enum thermal_device_mode *);
	int (*set_mode) (struct thermal_zone_device *,
		enum thermal_device_mode);
	int (*get_trip_type) (struct thermal_zone_device *, int,
		enum thermal_trip_type *);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int (*activate_trip_type) (struct thermal_zone_device *, int,
		enum thermal_trip_activation_mode);
	int (*get_trip_temp) (struct thermal_zone_device *, int,
			      unsigned long *);
	int (*set_trip_temp) (struct thermal_zone_device *, int,
			      long);
<<<<<<< HEAD
=======
=======
	int (*get_trip_temp) (struct thermal_zone_device *, int,
			      unsigned long *);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	int (*get_crit_temp) (struct thermal_zone_device *, unsigned long *);
	int (*notify) (struct thermal_zone_device *, int,
		       enum thermal_trip_type);
};

struct thermal_cooling_device_ops {
	int (*get_max_state) (struct thermal_cooling_device *, unsigned long *);
	int (*get_cur_state) (struct thermal_cooling_device *, unsigned long *);
	int (*set_cur_state) (struct thermal_cooling_device *, unsigned long);
};

#define THERMAL_TRIPS_NONE -1
#define THERMAL_MAX_TRIPS 12
#define THERMAL_NAME_LENGTH 20
struct thermal_cooling_device {
	int id;
	char type[THERMAL_NAME_LENGTH];
	struct device device;
	void *devdata;
	const struct thermal_cooling_device_ops *ops;
	struct list_head node;
};

#define KELVIN_TO_CELSIUS(t)	(long)(((long)t-2732 >= 0) ?	\
				((long)t-2732+5)/10 : ((long)t-2732-5)/10)
#define CELSIUS_TO_KELVIN(t)	((t)*10+2732)

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
struct sensor_threshold {
	long temp;
	enum thermal_trip_type trip;
	int (*notify)(enum thermal_trip_type type, int temp, void *data);
	void *data;
	uint8_t active;
	struct list_head list;
};

struct sensor_info {
	uint32_t sensor_id;
	struct thermal_zone_device *tz;
	long threshold_min;
	long threshold_max;
	int max_idx;
	int min_idx;
	struct list_head sensor_list;
	struct list_head threshold_list;
	struct mutex lock;
	struct work_struct work;
};
<<<<<<< HEAD
=======
=======
#if defined(CONFIG_THERMAL_HWMON)
/* thermal zone devices with the same type share one hwmon device */
struct thermal_hwmon_device {
	char type[THERMAL_NAME_LENGTH];
	struct device *device;
	int count;
	struct list_head tz_list;
	struct list_head node;
};

struct thermal_hwmon_attr {
	struct device_attribute attr;
	char name[16];
};
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

struct thermal_zone_device {
	int id;
	char type[THERMAL_NAME_LENGTH];
	struct device device;
	void *devdata;
	int trips;
	int tc1;
	int tc2;
	int passive_delay;
	int polling_delay;
	int last_temperature;
	bool passive;
	unsigned int forced_passive;
	const struct thermal_zone_device_ops *ops;
	struct list_head cooling_devices;
	struct idr idr;
	struct mutex lock;	/* protect cooling devices list */
	struct list_head node;
	struct delayed_work poll_queue;
<<<<<<< HEAD
	struct sensor_threshold tz_threshold[2];
	struct sensor_info sensor;
=======
<<<<<<< HEAD
	struct sensor_threshold tz_threshold[2];
	struct sensor_info sensor;
=======
#if defined(CONFIG_THERMAL_HWMON)
	struct list_head hwmon_node;
	struct thermal_hwmon_device *hwmon;
	struct thermal_hwmon_attr temp_input;	/* hwmon sys attr */
	struct thermal_hwmon_attr temp_crit;	/* hwmon sys attr */
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
};
/* Adding event notification support elements */
#define THERMAL_GENL_FAMILY_NAME                "thermal_event"
#define THERMAL_GENL_VERSION                    0x01
<<<<<<< HEAD
#define THERMAL_GENL_MCAST_GROUP_NAME           "thermal_mc_group"
=======
<<<<<<< HEAD
#define THERMAL_GENL_MCAST_GROUP_NAME           "thermal_mc_group"
=======
#define THERMAL_GENL_MCAST_GROUP_NAME           "thermal_mc_grp"
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

enum events {
	THERMAL_AUX0,
	THERMAL_AUX1,
	THERMAL_CRITICAL,
	THERMAL_DEV_FAULT,
};

struct thermal_genl_event {
	u32 orig;
	enum events event;
};
/* attributes of thermal_genl_family */
enum {
	THERMAL_GENL_ATTR_UNSPEC,
	THERMAL_GENL_ATTR_EVENT,
	__THERMAL_GENL_ATTR_MAX,
};
#define THERMAL_GENL_ATTR_MAX (__THERMAL_GENL_ATTR_MAX - 1)

/* commands supported by the thermal_genl_family */
enum {
	THERMAL_GENL_CMD_UNSPEC,
	THERMAL_GENL_CMD_EVENT,
	__THERMAL_GENL_CMD_MAX,
};
#define THERMAL_GENL_CMD_MAX (__THERMAL_GENL_CMD_MAX - 1)

struct thermal_zone_device *thermal_zone_device_register(char *, int, void *,
		const struct thermal_zone_device_ops *, int tc1, int tc2,
		int passive_freq, int polling_freq);
void thermal_zone_device_unregister(struct thermal_zone_device *);

int thermal_zone_bind_cooling_device(struct thermal_zone_device *, int,
				     struct thermal_cooling_device *);
int thermal_zone_unbind_cooling_device(struct thermal_zone_device *, int,
				       struct thermal_cooling_device *);
void thermal_zone_device_update(struct thermal_zone_device *);
struct thermal_cooling_device *thermal_cooling_device_register(char *, void *,
		const struct thermal_cooling_device_ops *);
void thermal_cooling_device_unregister(struct thermal_cooling_device *);

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int sensor_get_id(char *name);
int sensor_set_trip(uint32_t sensor_id, struct sensor_threshold *threshold);
int sensor_cancel_trip(uint32_t sensor_id, struct sensor_threshold *threshold);
int sensor_activate_trip(uint32_t sensor_id, struct sensor_threshold *threshold,
			bool enable);
int thermal_sensor_trip(struct thermal_zone_device *tz,
		enum thermal_trip_type trip, long temp);

#ifdef CONFIG_NET
extern int thermal_generate_netlink_event(u32 orig, enum events event);
#else
static inline int thermal_generate_netlink_event(u32 orig, enum events event)
<<<<<<< HEAD
=======
=======
#ifdef CONFIG_NET
extern int generate_netlink_event(u32 orig, enum events event);
#else
static inline int generate_netlink_event(u32 orig, enum events event)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
{
	return 0;
}
#endif

#endif /* __THERMAL_H__ */
