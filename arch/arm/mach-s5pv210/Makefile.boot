<<<<<<< HEAD
   zreladdr-y	+= 0x20008000
params_phys-y	:= 0x20000100
=======
<<<<<<< HEAD
   zreladdr-y	+= 0x20008000
params_phys-y	:= 0x20000100
=======
   zreladdr-y	:= 0x20008000
params_phys-y	:= 0x20000100

   zreladdr-$(CONFIG_CPU_S5PC110)       := 0x30008000
params_phys-$(CONFIG_CPU_S5PC110)       := 0x30000100
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
