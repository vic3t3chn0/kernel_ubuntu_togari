/*
<<<<<<< HEAD
 * Copyright (C) 2006-2012 B.A.T.M.A.N. contributors:
=======
<<<<<<< HEAD
 * Copyright (C) 2006-2012 B.A.T.M.A.N. contributors:
=======
 * Copyright (C) 2006-2011 B.A.T.M.A.N. contributors:
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 *
 * Simon Wunderlich, Marek Lindner
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA
 *
 */

#ifndef _NET_BATMAN_ADV_BITARRAY_H_
#define _NET_BATMAN_ADV_BITARRAY_H_

#define WORD_BIT_SIZE (sizeof(unsigned long) * 8)

/* returns true if the corresponding bit in the given seq_bits indicates true
 * and curr_seqno is within range of last_seqno */
<<<<<<< HEAD
int get_bit_status(const unsigned long *seq_bits, uint32_t last_seqno,
		   uint32_t curr_seqno);
=======
<<<<<<< HEAD
int get_bit_status(const unsigned long *seq_bits, uint32_t last_seqno,
		   uint32_t curr_seqno);
=======
uint8_t get_bit_status(unsigned long *seq_bits, uint32_t last_seqno,
					   uint32_t curr_seqno);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/* turn corresponding bit on, so we can remember that we got the packet */
void bit_mark(unsigned long *seq_bits, int32_t n);


/* receive and process one packet, returns 1 if received seq_num is considered
 * new, 0 if old  */
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
int bit_get_packet(void *priv, unsigned long *seq_bits,
		   int32_t seq_num_diff, int set_mark);

/* count the hamming weight, how many good packets did we receive? */
int bit_packet_count(const unsigned long *seq_bits);
<<<<<<< HEAD
=======
=======
char bit_get_packet(void *priv, unsigned long *seq_bits,
		    int32_t seq_num_diff, int8_t set_mark);

/* count the hamming weight, how many good packets did we receive? */
int  bit_packet_count(unsigned long *seq_bits);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* _NET_BATMAN_ADV_BITARRAY_H_ */
