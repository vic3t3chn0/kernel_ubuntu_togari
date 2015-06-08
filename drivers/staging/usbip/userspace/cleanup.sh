<<<<<<< HEAD
<<<<<<< HEAD
#!/bin/sh
=======
#!/bin/sh -x

>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
#!/bin/sh -x

>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

if [ -r Makefile ]; then
	make distclean
fi

<<<<<<< HEAD
<<<<<<< HEAD
FILES="aclocal.m4 autom4te.cache compile config.guess config.h.in config.log \
       config.status config.sub configure cscope.out depcomp install-sh      \
       libsrc/Makefile libsrc/Makefile.in libtool ltmain.sh Makefile         \
       Makefile.in missing src/Makefile src/Makefile.in"

rm -vRf $FILES
=======
FILES="configure cscope.out Makefile.in depcomp compile config.guess config.sub config.h.in~ config.log config.status ltmain.sh libtool config.h.in autom4te.cache missing aclocal.m4 install-sh cmd/Makefile.in lib/Makefile.in Makefile lib/Makefile cmd/Makefile"

rm -Rf $FILES
>>>>>>> 73a10a64c2f389351ff1594d88983f47c8de08f0
=======
FILES="configure cscope.out Makefile.in depcomp compile config.guess config.sub config.h.in~ config.log config.status ltmain.sh libtool config.h.in autom4te.cache missing aclocal.m4 install-sh cmd/Makefile.in lib/Makefile.in Makefile lib/Makefile cmd/Makefile"

rm -Rf $FILES
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2
