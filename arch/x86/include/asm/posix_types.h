#ifdef __KERNEL__
# ifdef CONFIG_X86_32
#  include "posix_types_32.h"
# else
#  include "posix_types_64.h"
# endif
#else
# ifdef __i386__
#  include "posix_types_32.h"
<<<<<<< HEAD
# elif defined(__ILP32__)
#  include "posix_types_x32.h"
=======
<<<<<<< HEAD
# elif defined(__ILP32__)
#  include "posix_types_x32.h"
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
# else
#  include "posix_types_64.h"
# endif
#endif
