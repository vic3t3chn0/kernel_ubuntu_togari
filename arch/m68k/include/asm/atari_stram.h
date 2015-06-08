#ifndef _M68K_ATARI_STRAM_H
#define _M68K_ATARI_STRAM_H

/*
 * Functions for Atari ST-RAM management
 */

/* public interface */
<<<<<<< HEAD
void *atari_stram_alloc(unsigned long size, const char *owner);
=======
<<<<<<< HEAD
void *atari_stram_alloc(unsigned long size, const char *owner);
=======
void *atari_stram_alloc(long size, const char *owner);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void atari_stram_free(void *);

/* functions called internally by other parts of the kernel */
void atari_stram_init(void);
void atari_stram_reserve_pages(void *start_mem);
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
void atari_stram_mem_init_hook (void);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /*_M68K_ATARI_STRAM_H */
