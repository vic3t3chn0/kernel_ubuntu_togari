<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#if defined(CONFIG_MMU) && !defined(CONFIG_COLDFIRE)
PHDRS
{
  text PT_LOAD FILEHDR PHDRS FLAGS (7);
  data PT_LOAD FLAGS (7);
}
#ifdef CONFIG_SUN3
#include "vmlinux-sun3.lds"
#else
#include "vmlinux-std.lds"
#endif
#else
#include "vmlinux-nommu.lds"
<<<<<<< HEAD
=======
=======
#ifdef CONFIG_MMU
#include "vmlinux.lds_mm.S"
#else
#include "vmlinux.lds_no.S"
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif
