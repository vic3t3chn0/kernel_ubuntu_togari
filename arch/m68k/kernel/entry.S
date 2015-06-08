<<<<<<< HEAD
#if defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
=======
<<<<<<< HEAD
#if defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
=======
#ifdef CONFIG_MMU
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include "entry_mm.S"
#else
#include "entry_no.S"
#endif
