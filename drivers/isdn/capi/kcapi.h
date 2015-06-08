/*
 * Kernel CAPI 2.0 Module
<<<<<<< HEAD
<<<<<<< HEAD
 *
 * Copyright 1999 by Carsten Paeth <calle@calle.de>
 * Copyright 2002 by Kai Germaschewski <kai@germaschewski.name>
 *
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * 
 * Copyright 1999 by Carsten Paeth <calle@calle.de>
 * Copyright 2002 by Kai Germaschewski <kai@germaschewski.name>
 * 
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */


#include <linux/kernel.h>
#include <linux/spinlock.h>
#include <linux/list.h>
#include <linux/isdn/capilli.h>

#ifdef KCAPI_DEBUG
<<<<<<< HEAD
<<<<<<< HEAD
#define DBG(format, arg...) do {					\
		printk(KERN_DEBUG "%s: " format "\n" , __func__ , ## arg); \
	} while (0)
=======
#define DBG(format, arg...) do { \
printk(KERN_DEBUG "%s: " format "\n" , __func__ , ## arg); \
} while (0)
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#define DBG(format, arg...) do { \
printk(KERN_DEBUG "%s: " format "\n" , __func__ , ## arg); \
} while (0)
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#else
#define DBG(format, arg...) /* */
#endif

enum {
	CAPI_CTR_DETACHED = 0,
	CAPI_CTR_DETECTED = 1,
	CAPI_CTR_LOADING  = 2,
	CAPI_CTR_RUNNING  = 3,
};

extern struct list_head capi_drivers;
extern struct mutex capi_drivers_lock;

extern struct capi_ctr *capi_controller[CAPI_MAXCONTR];
extern struct mutex capi_controller_lock;

extern struct capi20_appl *capi_applications[CAPI_MAXAPPL];

#ifdef CONFIG_PROC_FS

void kcapi_proc_init(void);
void kcapi_proc_exit(void);

#else

static inline void kcapi_proc_init(void) { };
static inline void kcapi_proc_exit(void) { };

#endif
<<<<<<< HEAD
<<<<<<< HEAD
=======

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
