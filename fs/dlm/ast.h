/******************************************************************************
*******************************************************************************
**
**  Copyright (C) 2005-2010 Red Hat, Inc.  All rights reserved.
**
**  This copyrighted material is made available to anyone wishing to use,
**  modify, copy, or redistribute it subject to the terms and conditions
**  of the GNU General Public License v.2.
**
*******************************************************************************
******************************************************************************/

#ifndef __ASTD_DOT_H__
#define __ASTD_DOT_H__

void dlm_del_ast(struct dlm_lkb *lkb);
int dlm_add_lkb_callback(struct dlm_lkb *lkb, uint32_t flags, int mode,
                         int status, uint32_t sbflags, uint64_t seq);
int dlm_rem_lkb_callback(struct dlm_ls *ls, struct dlm_lkb *lkb,
                         struct dlm_callback *cb, int *resid);
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void dlm_add_cb(struct dlm_lkb *lkb, uint32_t flags, int mode, int status,
                uint32_t sbflags);

void dlm_callback_work(struct work_struct *work);
int dlm_callback_start(struct dlm_ls *ls);
void dlm_callback_stop(struct dlm_ls *ls);
void dlm_callback_suspend(struct dlm_ls *ls);
void dlm_callback_resume(struct dlm_ls *ls);

#endif


<<<<<<< HEAD
=======
=======
void dlm_add_ast(struct dlm_lkb *lkb, uint32_t flags, int mode, int status,
		 uint32_t sbflags);

void dlm_astd_wake(void);
int dlm_astd_start(void);
void dlm_astd_stop(void);
void dlm_astd_suspend(void);
void dlm_astd_resume(void);

#endif

>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
