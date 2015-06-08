# Makefile for USB tools

CC = $(CROSS_COMPILE)gcc
PTHREAD_LIBS = -lpthread
WARNINGS = -Wall -Wextra
<<<<<<< HEAD
CFLAGS = $(WARNINGS) -g $(PTHREAD_LIBS) -I../include
=======
<<<<<<< HEAD
CFLAGS = $(WARNINGS) -g $(PTHREAD_LIBS) -I../include
=======
CFLAGS = $(WARNINGS) -g $(PTHREAD_LIBS)
>>>>>>> 58a75b6a81be54a8b491263ca1af243e9d8617b9
>>>>>>> ae1773bb70f3d7cf73324ce8fba787e01d8fa9f2

all: testusb ffs-test
%: %.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	$(RM) testusb ffs-test
