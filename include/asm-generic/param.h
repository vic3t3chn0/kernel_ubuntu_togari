#ifndef __ASM_GENERIC_PARAM_H
#define __ASM_GENERIC_PARAM_H

<<<<<<< HEAD
=======
#ifdef __KERNEL__
# define HZ		CONFIG_HZ	/* Internal kernel timer frequency */
# define USER_HZ	100		/* some user interfaces are */
# define CLOCKS_PER_SEC	(USER_HZ)       /* in "ticks" like times() */
#endif

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#ifndef HZ
#define HZ 100
#endif

#ifndef EXEC_PAGESIZE
#define EXEC_PAGESIZE	4096
#endif

#ifndef NOGROUP
#define NOGROUP		(-1)
#endif

#define MAXHOSTNAMELEN	64	/* max length of hostname */

<<<<<<< HEAD
#ifdef __KERNEL__
# undef HZ
# define HZ		CONFIG_HZ	/* Internal kernel timer frequency */
# define USER_HZ	100		/* some user interfaces are */
# define CLOCKS_PER_SEC	(USER_HZ)       /* in "ticks" like times() */
#endif

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif /* __ASM_GENERIC_PARAM_H */
