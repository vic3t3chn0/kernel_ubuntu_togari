#include "misc.h"
<<<<<<< HEAD

int memcmp(const void *s1, const void *s2, size_t len)
{
	u8 diff;
	asm("repe; cmpsb; setnz %0"
	    : "=qm" (diff), "+D" (s1), "+S" (s2), "+c" (len));
	return diff;
}

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#include "../string.c"
