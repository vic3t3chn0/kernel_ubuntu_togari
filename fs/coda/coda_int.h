#ifndef _CODA_INT_
#define _CODA_INT_

struct dentry;
struct file;

extern struct file_system_type coda_fs_type;
extern unsigned long coda_timeout;
extern int coda_hard;
extern int coda_fake_statfs;

void coda_destroy_inodecache(void);
int coda_init_inodecache(void);
<<<<<<< HEAD
int coda_fsync(struct file *coda_file, loff_t start, loff_t end, int datasync);
=======
<<<<<<< HEAD
int coda_fsync(struct file *coda_file, loff_t start, loff_t end, int datasync);
=======
int coda_fsync(struct file *coda_file, int datasync);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void coda_sysctl_init(void);
void coda_sysctl_clean(void);

#endif  /*  _CODA_INT_  */


