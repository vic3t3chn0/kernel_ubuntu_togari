# Guest requires the device configuration and probing code.
obj-$(CONFIG_LGUEST_GUEST) += lguest_device.o

# Host requires the other files, which can be a module.
obj-$(CONFIG_LGUEST)	+= lg.o
lg-y = core.o hypercalls.o page_tables.o interrupts_and_traps.o \
	segments.o lguest_user.o

lg-$(CONFIG_X86_32) += x86/switcher_32.o x86/core.o

Preparation Preparation!: PREFIX=P
Guest: PREFIX=G
Drivers: PREFIX=D
Launcher: PREFIX=L
Host: PREFIX=H
Switcher: PREFIX=S
Mastery: PREFIX=M
Beer:
	@for f in Preparation Guest Drivers Launcher Host Switcher Mastery; do echo "{==- $$f -==}"; make -s $$f; done; echo "{==-==}"
Preparation Preparation! Guest Drivers Launcher Host Switcher Mastery:
<<<<<<< HEAD
<<<<<<< HEAD
	@sh ../../tools/lguest/extract $(PREFIX) `find ../../* -name '*.[chS]' -wholename '*lguest*'`
=======
	@sh ../../Documentation/virtual/lguest/extract $(PREFIX) `find ../../* -name '*.[chS]' -wholename '*lguest*'`
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
	@sh ../../Documentation/virtual/lguest/extract $(PREFIX) `find ../../* -name '*.[chS]' -wholename '*lguest*'`
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
Puppy:
	@clear
	@printf "      __  \n (___()'\`;\n /,    /\`\n \\\\\\\"--\\\\\\   \n"
	@sleep 2; clear; printf "\n\n   Sit!\n\n"; sleep 1; clear
	@printf "    __    \n   ()'\`;  \n   /\\|\` \n  /  |  \n(/_)_|_   \n"
	@sleep 2; clear; printf "\n\n  Stand!\n\n"; sleep 1; clear
	@printf "    __    \n   ()'\`;  \n   /\\|\` \n  /._.= \n /| /     \n(_\_)_    \n"
	@sleep 2; clear; printf "\n\n  Good puppy!\n\n"; sleep 1; clear
