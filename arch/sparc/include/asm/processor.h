#ifndef ___ASM_SPARC_PROCESSOR_H
#define ___ASM_SPARC_PROCESSOR_H
#if defined(__sparc__) && defined(__arch64__)
#include <asm/processor_64.h>
#else
#include <asm/processor_32.h>
#endif
<<<<<<< HEAD

#define nop() 		__asm__ __volatile__ ("nop")

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#endif
