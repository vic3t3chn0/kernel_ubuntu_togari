#ifndef __LINUX_PWM_H
#define __LINUX_PWM_H

struct pwm_device;

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
/* Add __weak functions to support PWM */

/*
 * pwm_request - request a PWM device
 */
struct pwm_device __weak *pwm_request(int pwm_id, const char *label);
<<<<<<< HEAD
=======
=======
/*
 * pwm_request - request a PWM device
 */
struct pwm_device *pwm_request(int pwm_id, const char *label);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * pwm_free - free a PWM device
 */
<<<<<<< HEAD
void __weak pwm_free(struct pwm_device *pwm);
=======
<<<<<<< HEAD
void __weak pwm_free(struct pwm_device *pwm);
=======
void pwm_free(struct pwm_device *pwm);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * pwm_config - change a PWM device configuration
 */
<<<<<<< HEAD
int __weak pwm_config(struct pwm_device *pwm, int duty_ns, int period_ns);
=======
<<<<<<< HEAD
int __weak pwm_config(struct pwm_device *pwm, int duty_ns, int period_ns);
=======
int pwm_config(struct pwm_device *pwm, int duty_ns, int period_ns);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * pwm_enable - start a PWM output toggling
 */
<<<<<<< HEAD
int __weak pwm_enable(struct pwm_device *pwm);
=======
<<<<<<< HEAD
int __weak pwm_enable(struct pwm_device *pwm);
=======
int pwm_enable(struct pwm_device *pwm);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

/*
 * pwm_disable - stop a PWM output toggling
 */
<<<<<<< HEAD
void __weak pwm_disable(struct pwm_device *pwm);
=======
<<<<<<< HEAD
void __weak pwm_disable(struct pwm_device *pwm);
=======
void pwm_disable(struct pwm_device *pwm);
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

#endif /* __LINUX_PWM_H */
