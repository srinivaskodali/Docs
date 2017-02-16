obj-m =mod.o
obj-m +=depmod.o

obj-m +=mod1.o
obj-m +=mod2.o
obj-m +=mod3.o


KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean: 
	 rm -rf $(wildcard *.o *.ko *.mod.* .c* .t* test Module.symvers *.order *.markers)
