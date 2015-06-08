#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H
#include <asm/types.h>

<<<<<<< HEAD
#ifndef __ASSEMBLY__
=======
<<<<<<< HEAD
#ifndef __ASSEMBLY__
=======
#define pcibios_assign_all_busses() 1

#ifndef __ASSEMBLY__
extern unsigned long iop13xx_pcibios_min_io;
extern unsigned long iop13xx_pcibios_min_mem;
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern u16 iop13xx_dev_id(void);
extern void iop13xx_set_atu_mmr_bases(void);
#endif

<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
#define PCIBIOS_MIN_IO      (iop13xx_pcibios_min_io)
#define PCIBIOS_MIN_MEM     (iop13xx_pcibios_min_mem)

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/*
 * Generic chipset bits
 *
 */
#include "iop13xx.h"

/*
 * Board specific bits
 */
#include "iq81340.h"

#endif  /* _ASM_ARCH_HARDWARE_H */
