/*
 * Callbacks prototypes for FSM
 *
 * Copyright (C) 1996 Universidade de Lisboa
<<<<<<< HEAD
<<<<<<< HEAD
 *
 * Written by Pedro Roque Marques (roque@di.fc.ul.pt)
 *
 * This software may be used and distributed according to the terms of
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * 
 * Written by Pedro Roque Marques (roque@di.fc.ul.pt)
 *
 * This software may be used and distributed according to the terms of 
<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
 * the GNU General Public License, incorporated herein by reference.
 */

#ifndef CALLBACKS_H
#define CALLBACKS_H


<<<<<<< HEAD
<<<<<<< HEAD
extern void cb_out_1(struct pcbit_dev *dev, struct pcbit_chan *chan,
		     struct callb_data *data);

extern void cb_out_2(struct pcbit_dev *dev, struct pcbit_chan *chan,
		     struct callb_data *data);

extern void cb_in_1(struct pcbit_dev *dev, struct pcbit_chan *chan,
		    struct callb_data *data);
extern void cb_in_2(struct pcbit_dev *dev, struct pcbit_chan *chan,
		    struct callb_data *data);
extern void cb_in_3(struct pcbit_dev *dev, struct pcbit_chan *chan,
		    struct callb_data *data);

extern void cb_disc_1(struct pcbit_dev *dev, struct pcbit_chan *chan,
		      struct callb_data *data);
extern void cb_disc_2(struct pcbit_dev *dev, struct pcbit_chan *chan,
		      struct callb_data *data);
extern void cb_disc_3(struct pcbit_dev *dev, struct pcbit_chan *chan,
		      struct callb_data *data);

extern void cb_notdone(struct pcbit_dev *dev, struct pcbit_chan *chan,
		       struct callb_data *data);

extern void cb_selp_1(struct pcbit_dev *dev, struct pcbit_chan *chan,
		      struct callb_data *data);
extern void cb_open(struct pcbit_dev *dev, struct pcbit_chan *chan,
		    struct callb_data *data);

#endif
=======
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
extern void cb_out_1(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		     struct callb_data *data);

extern void cb_out_2(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		     struct callb_data *data);

extern void cb_in_1(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		    struct callb_data *data);
extern void cb_in_2(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		    struct callb_data *data);
extern void cb_in_3(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		    struct callb_data *data);

extern void cb_disc_1(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		      struct callb_data *data);
extern void cb_disc_2(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		      struct callb_data *data);
extern void cb_disc_3(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		      struct callb_data *data);

extern void cb_notdone(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		       struct callb_data *data);

extern void cb_selp_1(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		      struct callb_data *data);
extern void cb_open(struct pcbit_dev * dev, struct pcbit_chan* chan, 
		    struct callb_data *data);

#endif


<<<<<<< HEAD
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
