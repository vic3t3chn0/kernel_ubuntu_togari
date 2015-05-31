#ifndef _H8300_BUG_H
#define _H8300_BUG_H

/* always true */
#define is_valid_bugaddr(addr) (1)

#include <asm-generic/bug.h>
<<<<<<< HEAD

struct pt_regs;
extern void die(const char *str, struct pt_regs *fp, unsigned long err);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif
