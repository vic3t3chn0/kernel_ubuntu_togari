/*
 *  include/asm-s390/reset.h
 *
 *    Copyright IBM Corp. 2006
 *    Author(s): Heiko Carstens <heiko.carstens@de.ibm.com>
 */

#ifndef _ASM_S390_RESET_H
#define _ASM_S390_RESET_H

#include <linux/list.h>

struct reset_call {
	struct list_head list;
	void (*fn)(void);
};

extern void register_reset_call(struct reset_call *reset);
extern void unregister_reset_call(struct reset_call *reset);
<<<<<<< HEAD
extern void s390_reset_system(void (*func)(void *), void *data);
=======
extern void s390_reset_system(void);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif /* _ASM_S390_RESET_H */
