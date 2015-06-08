#ifndef _ASM_PARAM_H
#define _ASM_PARAM_H

<<<<<<< HEAD
#define EXEC_PAGESIZE	16384

#include <asm-generic/param.h>
=======
<<<<<<< HEAD
#define EXEC_PAGESIZE	16384

#include <asm-generic/param.h>
=======
#ifdef __KERNEL__
#define HZ		CONFIG_HZ	/* Internal kernel timer frequency */
#define USER_HZ		100		/* .. some user interfaces are in "ticks" */
#define CLOCKS_PER_SEC	(USER_HZ)	/* like times() */
#endif

#ifndef HZ
#define HZ 100
#endif

#define EXEC_PAGESIZE	16384

#ifndef NOGROUP
#define NOGROUP		(-1)
#endif

#define MAXHOSTNAMELEN		64	/* max length of hostname */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* _ASM_PARAM_H */
