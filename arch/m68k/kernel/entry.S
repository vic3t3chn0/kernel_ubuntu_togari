<<<<<<< HEAD
#if defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
=======
#ifdef CONFIG_MMU
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#include "entry_mm.S"
#else
#include "entry_no.S"
#endif
