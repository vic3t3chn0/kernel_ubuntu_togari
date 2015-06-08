/* Configuration space parsing helpers for virtio.
 *
 * The configuration is [type][len][... len bytes ...] fields.
 *
 * Copyright 2007 Rusty Russell, IBM Corporation.
 * GPL v2 or later.
 */
#include <linux/err.h>
#include <linux/virtio.h>
#include <linux/virtio_config.h>
#include <linux/bug.h>
<<<<<<< HEAD
<<<<<<< HEAD
=======
#include <asm/system.h>
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#include <asm/system.h>
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

