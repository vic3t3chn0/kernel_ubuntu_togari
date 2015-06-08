/*
 * Copyright (c) 2002-3 Patrick Mochel
 * Copyright (c) 2002-3 Open Source Development Labs
 *
 * This file is released under the GPLv2
 */

#include <linux/device.h>
#include <linux/init.h>
#include <linux/memory.h>

#include "base.h"

/**
 * driver_init - initialize driver model.
 *
 * Call the driver model init functions to initialize their
 * subsystems. Called early from init/main.c.
 */
void __init driver_init(void)
{
	/* These are the core pieces */
	devtmpfs_init();
	devices_init();
	buses_init();
	classes_init();
	firmware_init();
	hypervisor_init();

	/* These are also core pieces, but must come after the
	 * core core pieces.
	 */
	platform_bus_init();
<<<<<<< HEAD
<<<<<<< HEAD
=======
	system_bus_init();
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	system_bus_init();
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	cpu_dev_init();
	memory_dev_init();
}
