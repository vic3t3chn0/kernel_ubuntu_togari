/*
 *  include/asm-s390/mman.h
 *
 *  S390 version
 *
 *  Derived from "include/asm-i386/mman.h"
 */

#ifndef __S390_MMAN_H__
#define __S390_MMAN_H__

#include <asm-generic/mman.h>

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#if defined(__KERNEL__)
#if !defined(__ASSEMBLY__) && defined(CONFIG_64BIT)
int s390_mmap_check(unsigned long addr, unsigned long len);
#define arch_mmap_check(addr,len,flags)	s390_mmap_check(addr,len)
#endif
#endif
<<<<<<< HEAD
=======
=======
#if defined(__KERNEL__) && !defined(__ASSEMBLY__) && defined(CONFIG_64BIT)
int s390_mmap_check(unsigned long addr, unsigned long len);
#define arch_mmap_check(addr,len,flags)	s390_mmap_check(addr,len)
#endif
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* __S390_MMAN_H__ */
