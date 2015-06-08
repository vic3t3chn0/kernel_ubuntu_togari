/*
 *  linux/fs/ext4/bitmap.c
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 */

#include <linux/buffer_head.h>
#include <linux/jbd2.h>
#include "ext4.h"

#ifdef EXT4FS_DEBUG

static const int nibblemap[] = {4, 3, 3, 2, 3, 2, 2, 1, 3, 2, 2, 1, 2, 1, 1, 0};

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
unsigned int ext4_count_free(struct buffer_head *map, unsigned int numchars)
{
	unsigned int i, sum = 0;

	if (!map)
		return 0;
	for (i = 0; i < numchars; i++)
		sum += nibblemap[map->b_data[i] & 0xf] +
			nibblemap[(map->b_data[i] >> 4) & 0xf];
<<<<<<< HEAD
=======
=======
unsigned int ext4_count_free(char *bitmap, unsigned int numchars)
{
	unsigned int i, sum = 0;

	for (i = 0; i < numchars; i++)
		sum += nibblemap[bitmap[i] & 0xf] +
			nibblemap[(bitmap[i] >> 4) & 0xf];
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	return sum;
}

#endif  /*  EXT4FS_DEBUG  */

