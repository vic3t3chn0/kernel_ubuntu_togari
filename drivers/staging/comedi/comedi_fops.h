
#ifndef _COMEDI_FOPS_H
#define _COMEDI_FOPS_H
<<<<<<< HEAD
#include <linux/types.h>

extern struct class *comedi_class;
extern const struct file_operations comedi_fops;
extern bool comedi_autoconfig;
=======

extern struct class *comedi_class;
extern const struct file_operations comedi_fops;
extern int comedi_autoconfig;
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
extern struct comedi_driver *comedi_drivers;

#endif /* _COMEDI_FOPS_H */
