
struct kvm_timer {
	struct hrtimer timer;
	s64 period; 				/* unit: ns */
<<<<<<< HEAD
	u32 timer_mode_mask;
	u64 tscdeadline;
=======
<<<<<<< HEAD
	u32 timer_mode_mask;
	u64 tscdeadline;
=======
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
	atomic_t pending;			/* accumulated triggered timers */
	bool reinject;
	struct kvm_timer_ops *t_ops;
	struct kvm *kvm;
	struct kvm_vcpu *vcpu;
};

struct kvm_timer_ops {
	bool (*is_periodic)(struct kvm_timer *);
};

enum hrtimer_restart kvm_timer_fn(struct hrtimer *data);
