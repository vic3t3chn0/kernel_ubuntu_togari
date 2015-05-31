#include <linux/module.h>
<<<<<<< HEAD
#include <linux/kvm_host.h>
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
#include <asm/ftrace.h>

#ifdef CONFIG_FUNCTION_TRACER
EXPORT_SYMBOL(_mcount);
#endif
<<<<<<< HEAD
#if defined(CONFIG_KVM) || defined(CONFIG_KVM_MODULE)
EXPORT_SYMBOL(sie64a);
#endif
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
