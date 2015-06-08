/* $Id: fsm.h,v 1.3.2.2 2001/09/23 22:24:47 kai Exp $
 *
 * Finite state machine
 *
 * Author       Karsten Keil
 * Copyright    by Karsten Keil      <keil@isdn4linux.de>
 *              by Kai Germaschewski <kai.germaschewski@gmx.de>
<<<<<<< HEAD
<<<<<<< HEAD
 *
=======
 * 
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
 * 
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * This software may be used and distributed according to the terms
 * of the GNU General Public License, incorporated herein by reference.
 *
 */

#ifndef __FSM_H__
#define __FSM_H__

#include <linux/timer.h>

struct FsmInst;

<<<<<<< HEAD
<<<<<<< HEAD
typedef void (*FSMFNPTR)(struct FsmInst *, int, void *);
=======
typedef void (* FSMFNPTR)(struct FsmInst *, int, void *);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
typedef void (* FSMFNPTR)(struct FsmInst *, int, void *);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

struct Fsm {
	FSMFNPTR *jumpmatrix;
	int state_count, event_count;
	char **strEvent, **strState;
};

struct FsmInst {
	struct Fsm *fsm;
	int state;
	int debug;
	void *userdata;
	int userint;
	void (*printdebug) (struct FsmInst *, char *, ...);
};

struct FsmNode {
	int state, event;
	void (*routine) (struct FsmInst *, int, void *);
};

struct FsmTimer {
	struct FsmInst *fi;
	struct timer_list tl;
	int event;
	void *arg;
};

int FsmNew(struct Fsm *fsm, struct FsmNode *fnlist, int fncount);
void FsmFree(struct Fsm *fsm);
int FsmEvent(struct FsmInst *fi, int event, void *arg);
void FsmChangeState(struct FsmInst *fi, int newstate);
void FsmInitTimer(struct FsmInst *fi, struct FsmTimer *ft);
int FsmAddTimer(struct FsmTimer *ft, int millisec, int event,
		void *arg, int where);
void FsmRestartTimer(struct FsmTimer *ft, int millisec, int event,
		     void *arg, int where);
void FsmDelTimer(struct FsmTimer *ft, int where);

#endif
