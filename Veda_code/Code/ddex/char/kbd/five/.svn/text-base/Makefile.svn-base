
obj-m :=kboard.o
#obj-m +=char_driver_ioctl.o
KDIR= /lib/modules/$(shell uname -r)/build
all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean: 
	   rm -rf *.o *.ko *.mod.* .c* .t*

