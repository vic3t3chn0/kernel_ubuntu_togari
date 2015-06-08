/*
 * various internal comedi functions
 */
int do_rangeinfo_ioctl(struct comedi_device *dev,
		       struct comedi_rangeinfo __user *arg);
int insn_inval(struct comedi_device *dev, struct comedi_subdevice *s,
	       struct comedi_insn *insn, unsigned int *data);
int comedi_alloc_board_minor(struct device *hardware_device);
void comedi_free_board_minor(unsigned minor);
<<<<<<< HEAD
<<<<<<< HEAD
=======
int comedi_find_board_minor(struct device *hardware_device);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
int comedi_find_board_minor(struct device *hardware_device);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
void comedi_reset_async_buf(struct comedi_async *async);
int comedi_buf_alloc(struct comedi_device *dev, struct comedi_subdevice *s,
		     unsigned long new_size);
