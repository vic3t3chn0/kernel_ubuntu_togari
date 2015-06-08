#ifndef M68K_PGALLOC_H
#define M68K_PGALLOC_H

#include <linux/mm.h>
#include <linux/highmem.h>
#include <asm/setup.h>

#ifdef CONFIG_MMU
#include <asm/virtconvert.h>
<<<<<<< HEAD
#if defined(CONFIG_COLDFIRE)
#include <asm/mcf_pgalloc.h>
#elif defined(CONFIG_SUN3)
=======
<<<<<<< HEAD
#if defined(CONFIG_COLDFIRE)
#include <asm/mcf_pgalloc.h>
#elif defined(CONFIG_SUN3)
=======
#ifdef CONFIG_SUN3
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#include <asm/sun3_pgalloc.h>
#else
#include <asm/motorola_pgalloc.h>
#endif

extern void m68k_setup_node(int node);
#endif

#endif /* M68K_PGALLOC_H */
