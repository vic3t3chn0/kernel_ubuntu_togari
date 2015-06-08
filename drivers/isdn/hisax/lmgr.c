/* $Id: lmgr.c,v 1.7.6.2 2001/09/23 22:24:50 kai Exp $
 *
 * Layermanagement module
 *
 * Author       Karsten Keil
 * Copyright    by Karsten Keil      <keil@isdn4linux.de>
<<<<<<< HEAD
 *
=======
 * 
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#include "hisax.h"

static void
error_handling_dchan(struct PStack *st, int Error)
{
	switch (Error) {
<<<<<<< HEAD
	case 'C':
	case 'D':
	case 'G':
	case 'H':
		st->l2.l2tei(st, MDL_ERROR | REQUEST, NULL);
		break;
=======
		case 'C':
		case 'D':
		case 'G':
		case 'H':
			st->l2.l2tei(st, MDL_ERROR | REQUEST, NULL);
			break;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	}
}

static void
hisax_manager(struct PStack *st, int pr, void *arg)
{
	long Code;

	switch (pr) {
<<<<<<< HEAD
	case (MDL_ERROR | INDICATION):
		Code = (long) arg;
		HiSax_putstatus(st->l1.hardware, "manager: MDL_ERROR",
				" %c %s", (char)Code,
				test_bit(FLG_LAPD, &st->l2.flag) ?
				"D-channel" : "B-channel");
		if (test_bit(FLG_LAPD, &st->l2.flag))
			error_handling_dchan(st, Code);
		break;
=======
		case (MDL_ERROR | INDICATION):
			Code = (long) arg;
			HiSax_putstatus(st->l1.hardware, "manager: MDL_ERROR",
				" %c %s", (char)Code, 
				test_bit(FLG_LAPD, &st->l2.flag) ?
				"D-channel" : "B-channel");
			if (test_bit(FLG_LAPD, &st->l2.flag))
				error_handling_dchan(st, Code);
			break;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
	}
}

void
setstack_manager(struct PStack *st)
{
	st->ma.layer = hisax_manager;
}
