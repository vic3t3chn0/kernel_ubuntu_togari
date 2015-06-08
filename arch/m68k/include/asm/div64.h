#ifndef _M68K_DIV64_H
#define _M68K_DIV64_H

<<<<<<< HEAD
#ifdef CONFIG_CPU_HAS_NO_MULDIV64
#include <asm-generic/div64.h>
#else
=======
<<<<<<< HEAD
#ifdef CONFIG_CPU_HAS_NO_MULDIV64
#include <asm-generic/div64.h>
#else
=======
#ifdef CONFIG_MMU
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#include <linux/types.h>

/* n = n / base; return rem; */

#define do_div(n, base) ({					\
	union {							\
		unsigned long n32[2];				\
		unsigned long long n64;				\
	} __n;							\
	unsigned long __rem, __upper;				\
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
	unsigned long __base = (base);				\
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
								\
	__n.n64 = (n);						\
	if ((__upper = __n.n32[0])) {				\
		asm ("divul.l %2,%1:%0"				\
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
			: "=d" (__n.n32[0]), "=d" (__upper)	\
			: "d" (base), "0" (__n.n32[0]));	\
	}							\
	asm ("divu.l %2,%1:%0"					\
		: "=d" (__n.n32[1]), "=d" (__rem)		\
		: "d" (base), "1" (__upper), "0" (__n.n32[1]));	\
<<<<<<< HEAD
=======
=======
		     : "=d" (__n.n32[0]), "=d" (__upper)	\
		     : "d" (__base), "0" (__n.n32[0]));		\
	}							\
	asm ("divu.l %2,%1:%0"					\
	     : "=d" (__n.n32[1]), "=d" (__rem)			\
	     : "d" (__base), "1" (__upper), "0" (__n.n32[1]));	\
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	(n) = __n.n64;						\
	__rem;							\
})

<<<<<<< HEAD
#endif /* CONFIG_CPU_HAS_NO_MULDIV64 */
=======
<<<<<<< HEAD
#endif /* CONFIG_CPU_HAS_NO_MULDIV64 */
=======
#else
#include <asm-generic/div64.h>
#endif /* CONFIG_MMU */
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* _M68K_DIV64_H */
