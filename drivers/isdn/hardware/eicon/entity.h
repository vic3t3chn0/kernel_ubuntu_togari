/* $Id: entity.h,v 1.4 2004/03/21 17:26:01 armin Exp $ */

#ifndef __DIVAS_USER_MODE_IDI_ENTITY__
#define __DIVAS_USER_MODE_IDI_ENTITY__

#define DIVA_UM_IDI_RC_PENDING      0x00000001
#define DIVA_UM_IDI_REMOVE_PENDING  0x00000002
#define DIVA_UM_IDI_TX_FLOW_CONTROL 0x00000004
#define DIVA_UM_IDI_REMOVED         0x00000008
#define DIVA_UM_IDI_ASSIGN_PENDING  0x00000010

typedef struct _divas_um_idi_entity {
	struct list_head          link;
<<<<<<< HEAD
<<<<<<< HEAD
	diva_um_idi_adapter_t *adapter; /* Back to adapter */
	ENTITY e;
	void *os_ref;
	dword status;
	void *os_context;
	int rc_count;
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	diva_um_idi_adapter_t*    adapter; /* Back to adapter */
	ENTITY                    e;
	void*                     os_ref;
	dword                     status;
	void*                     os_context;
	int                       rc_count;
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	diva_um_idi_data_queue_t  data; /* definad by user 1 ... MAX */
	diva_um_idi_data_queue_t  rc;   /* two entries */
	BUFFERS                   XData;
	BUFFERS                   RData;
<<<<<<< HEAD
<<<<<<< HEAD
	byte                      buffer[2048 + 512];
=======
	byte                      buffer[2048+512];
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	byte                      buffer[2048+512];
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
} divas_um_idi_entity_t;


#endif
