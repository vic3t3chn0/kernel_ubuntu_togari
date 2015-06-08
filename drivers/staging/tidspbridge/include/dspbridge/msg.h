/*
 * msg.h
 *
 * DSP-BIOS Bridge driver support functions for TI OMAP processors.
 *
 * DSP/BIOS Bridge msg_ctrl Module.
 *
 * Copyright (C) 2005-2006 Texas Instruments, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * THIS PACKAGE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 */

#ifndef MSG_
#define MSG_

#include <dspbridge/devdefs.h>
#include <dspbridge/msgdefs.h>

/*
 *  ======== msg_create ========
 *  Purpose:
 *      Create an object to manage message queues. Only one of these objects
 *      can exist per device object. The msg_ctrl manager must be created before
 *      the IO Manager.
 *  Parameters:
 *      msg_man:            Location to store msg_ctrl manager handle on output.
 *      hdev_obj:         The device object.
 *      msg_callback:        Called whenever an RMS_EXIT message is received.
 *  Returns:
 *  Requires:
<<<<<<< HEAD
<<<<<<< HEAD
=======
 *      msg_mod_init(void) called.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 *      msg_mod_init(void) called.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *      msg_man != NULL.
 *      hdev_obj != NULL.
 *      msg_callback != NULL.
 *  Ensures:
 */
extern int msg_create(struct msg_mgr **msg_man,
			     struct dev_object *hdev_obj,
			     msg_onexit msg_callback);

/*
 *  ======== msg_delete ========
 *  Purpose:
 *      Delete a msg_ctrl manager allocated in msg_create().
 *  Parameters:
 *      hmsg_mgr:            Handle returned from msg_create().
 *  Returns:
 *  Requires:
<<<<<<< HEAD
<<<<<<< HEAD
=======
 *      msg_mod_init(void) called.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 *      msg_mod_init(void) called.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *      Valid hmsg_mgr.
 *  Ensures:
 */
extern void msg_delete(struct msg_mgr *hmsg_mgr);

<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 *  ======== msg_exit ========
 *  Purpose:
 *      Discontinue usage of msg_ctrl module.
 *  Parameters:
 *  Returns:
 *  Requires:
 *      msg_mod_init(void) successfully called before.
 *  Ensures:
 *      Any resources acquired in msg_mod_init(void) will be freed when last
 *      msg_ctrl client calls msg_exit(void).
 */
extern void msg_exit(void);

/*
 *  ======== msg_mod_init ========
 *  Purpose:
 *      Initialize the msg_ctrl module.
 *  Parameters:
 *  Returns:
 *      TRUE if initialization succeeded, FALSE otherwise.
 *  Ensures:
 */
extern bool msg_mod_init(void);

<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* MSG_ */
