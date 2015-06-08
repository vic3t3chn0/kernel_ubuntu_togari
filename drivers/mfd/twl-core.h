#ifndef __TWL_CORE_H__
#define __TWL_CORE_H__

<<<<<<< HEAD
<<<<<<< HEAD
extern int twl6030_init_irq(struct device *dev, int irq_num);
extern int twl6030_exit_irq(void);
extern int twl4030_init_irq(struct device *dev, int irq_num);
=======
extern int twl6030_init_irq(int irq_num, unsigned irq_base, unsigned irq_end);
extern int twl6030_exit_irq(void);
extern int twl4030_init_irq(int irq_num, unsigned irq_base, unsigned irq_end);
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
extern int twl6030_init_irq(int irq_num, unsigned irq_base, unsigned irq_end);
extern int twl6030_exit_irq(void);
extern int twl4030_init_irq(int irq_num, unsigned irq_base, unsigned irq_end);
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern int twl4030_exit_irq(void);
extern int twl4030_init_chip_irq(const char *chip);

#endif /*  __TWL_CORE_H__ */
