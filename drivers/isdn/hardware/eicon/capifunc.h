/* $Id: capifunc.h,v 1.11.4.1 2004/08/28 20:03:53 armin Exp $
 *
 * ISDN interface module for Eicon active cards DIVA.
 * CAPI Interface common functions
<<<<<<< HEAD
<<<<<<< HEAD
 *
 * Copyright 2000-2003 by Armin Schindler (mac@melware.de)
=======
 * 
 * Copyright 2000-2003 by Armin Schindler (mac@melware.de) 
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * 
 * Copyright 2000-2003 by Armin Schindler (mac@melware.de) 
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * Copyright 2000-2003 Cytronics & Melware (info@melware.de)
 *
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 */

#ifndef __CAPIFUNC_H__
#define __CAPIFUNC_H__

#define DRRELMAJOR  2
#define DRRELMINOR  0
#define DRRELEXTRA  ""

#define M_COMPANY "Eicon Networks"

extern char DRIVERRELEASE_CAPI[];

typedef struct _diva_card {
	struct list_head list;
	int remove_in_progress;
	int Id;
	struct capi_ctr capi_ctrl;
	DIVA_CAPI_ADAPTER *adapter;
	DESCRIPTOR d;
	char name[32];
} diva_card;

/*
 * prototypes
 */
int init_capifunc(void);
void finit_capifunc(void);

#endif /* __CAPIFUNC_H__ */
