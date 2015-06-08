/*
 * cpuidle.h - The internal header file
 */

#ifndef __DRIVER_CPUIDLE_H
#define __DRIVER_CPUIDLE_H

<<<<<<< HEAD
<<<<<<< HEAD
#include <linux/device.h>
=======
#include <linux/sysdev.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <linux/sysdev.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* For internal use only */
extern struct cpuidle_governor *cpuidle_curr_governor;
extern struct list_head cpuidle_governors;
extern struct list_head cpuidle_detected_devices;
extern struct mutex cpuidle_lock;
extern spinlock_t cpuidle_driver_lock;
<<<<<<< HEAD
<<<<<<< HEAD
extern int cpuidle_disabled(void);
extern int cpuidle_enter_state(struct cpuidle_device *dev,
		struct cpuidle_driver *drv, int next_state);
=======
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* idle loop */
extern void cpuidle_install_idle_handler(void);
extern void cpuidle_uninstall_idle_handler(void);

/* governors */
extern int cpuidle_switch_governor(struct cpuidle_governor *gov);

/* sysfs */
<<<<<<< HEAD
<<<<<<< HEAD
extern int cpuidle_add_interface(struct device *dev);
extern void cpuidle_remove_interface(struct device *dev);
extern int cpuidle_add_state_sysfs(struct cpuidle_device *device);
extern void cpuidle_remove_state_sysfs(struct cpuidle_device *device);
extern int cpuidle_add_sysfs(struct device *dev);
extern void cpuidle_remove_sysfs(struct device *dev);

#ifdef CONFIG_ARCH_NEEDS_CPU_IDLE_COUPLED
bool cpuidle_state_is_coupled(struct cpuidle_device *dev,
		struct cpuidle_driver *drv, int state);
int cpuidle_enter_state_coupled(struct cpuidle_device *dev,
		struct cpuidle_driver *drv, int next_state);
int cpuidle_coupled_register_device(struct cpuidle_device *dev);
void cpuidle_coupled_unregister_device(struct cpuidle_device *dev);
#else
static inline bool cpuidle_state_is_coupled(struct cpuidle_device *dev,
		struct cpuidle_driver *drv, int state)
{
	return false;
}

static inline int cpuidle_enter_state_coupled(struct cpuidle_device *dev,
		struct cpuidle_driver *drv, int next_state)
{
	return -1;
}

static inline int cpuidle_coupled_register_device(struct cpuidle_device *dev)
{
	return 0;
}

static inline void cpuidle_coupled_unregister_device(struct cpuidle_device *dev)
{
}
#endif
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern int cpuidle_add_class_sysfs(struct sysdev_class *cls);
extern void cpuidle_remove_class_sysfs(struct sysdev_class *cls);
extern int cpuidle_add_state_sysfs(struct cpuidle_device *device);
extern void cpuidle_remove_state_sysfs(struct cpuidle_device *device);
extern int cpuidle_add_sysfs(struct sys_device *sysdev);
extern void cpuidle_remove_sysfs(struct sys_device *sysdev);
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* __DRIVER_CPUIDLE_H */
