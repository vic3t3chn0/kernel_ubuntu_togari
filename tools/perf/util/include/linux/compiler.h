#ifndef _PERF_LINUX_COMPILER_H_
#define _PERF_LINUX_COMPILER_H_

#ifndef __always_inline
#define __always_inline	inline
#endif
#define __user
<<<<<<< HEAD
#ifndef __attribute_const__
#define __attribute_const__
#endif
=======
<<<<<<< HEAD
#ifndef __attribute_const__
#define __attribute_const__
#endif
=======
#define __attribute_const__
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#define __used		__attribute__((__unused__))

#endif
