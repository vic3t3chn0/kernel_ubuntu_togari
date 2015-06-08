/*
 *
 * Intel Management Engine Interface (Intel MEI) Linux driver
<<<<<<< HEAD
<<<<<<< HEAD
 * Copyright (c) 2003-2012, Intel Corporation.
=======
 * Copyright (c) 2003-2011, Intel Corporation.
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * Copyright (c) 2003-2011, Intel Corporation.
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 */



#ifndef _MEI_INTERFACE_H_
#define _MEI_INTERFACE_H_

#include "mei.h"
#include "mei_dev.h"


<<<<<<< HEAD
<<<<<<< HEAD
#define AMT_WD_DEFAULT_TIMEOUT 120	/* seconds */
#define AMT_WD_MIN_TIMEOUT 120	/* seconds */
#define AMT_WD_MAX_TIMEOUT 65535	/* seconds */
=======
#define AMT_WD_VALUE 120	/* seconds */
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#define AMT_WD_VALUE 120	/* seconds */
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define MEI_WATCHDOG_DATA_SIZE         16
#define MEI_START_WD_DATA_SIZE         20
#define MEI_WD_PARAMS_SIZE             4


void mei_read_slots(struct mei_device *dev,
<<<<<<< HEAD
<<<<<<< HEAD
		     unsigned char *buffer,
		     unsigned long buffer_length);
=======
		     unsigned char *buffer, unsigned long buffer_length);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
		     unsigned char *buffer, unsigned long buffer_length);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

int mei_write_message(struct mei_device *dev,
			     struct mei_msg_hdr *header,
			     unsigned char *write_buffer,
			     unsigned long write_length);

int mei_host_buffer_is_empty(struct mei_device *dev);

int mei_count_full_read_slots(struct mei_device *dev);

int mei_count_empty_write_slots(struct mei_device *dev);

int mei_flow_ctrl_creds(struct mei_device *dev, struct mei_cl *cl);

int mei_wd_send(struct mei_device *dev);
int mei_wd_stop(struct mei_device *dev, bool preserve);
<<<<<<< HEAD
<<<<<<< HEAD
bool mei_wd_host_init(struct mei_device *dev);
void mei_wd_set_start_timeout(struct mei_device *dev, u16 timeout);
/*
 * mei_watchdog_register  - Registering watchdog interface
 *   once we got connection to the WD Client
 * @dev - mei device
 */
void mei_watchdog_register(struct mei_device *dev);
/*
 * mei_watchdog_unregister  - Unregistering watchdog interface
 * @dev - mei device
 */
void mei_watchdog_unregister(struct mei_device *dev);
=======
void mei_wd_host_init(struct mei_device *dev);
void mei_wd_start_setup(struct mei_device *dev);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
void mei_wd_host_init(struct mei_device *dev);
void mei_wd_start_setup(struct mei_device *dev);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

int mei_flow_ctrl_reduce(struct mei_device *dev, struct mei_cl *cl);

int mei_send_flow_control(struct mei_device *dev, struct mei_cl *cl);

int mei_disconnect(struct mei_device *dev, struct mei_cl *cl);
int mei_other_client_is_connecting(struct mei_device *dev, struct mei_cl *cl);
int mei_connect(struct mei_device *dev, struct mei_cl *cl);

#endif /* _MEI_INTERFACE_H_ */
