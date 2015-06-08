/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 *
 * This copyrighted material is made available to anyone wishing to use,
 * modify, copy, or redistribute it subject to the terms and conditions
 * of the GNU General Public License version 2.
 */

#ifndef __SYS_DOT_H__
#define __SYS_DOT_H__

#include <linux/spinlock.h>
struct gfs2_sbd;

int gfs2_sys_fs_add(struct gfs2_sbd *sdp);
void gfs2_sys_fs_del(struct gfs2_sbd *sdp);

int gfs2_sys_init(void);
void gfs2_sys_uninit(void);

<<<<<<< HEAD
int gfs2_recover_set(struct gfs2_sbd *sdp, unsigned jid);

=======
<<<<<<< HEAD
int gfs2_recover_set(struct gfs2_sbd *sdp, unsigned jid);

=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
#endif /* __SYS_DOT_H__ */

