obj-m :=kboard1.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean: 
	rm -rf $(wildcard *.o *.ko mo* Mo* *.mod.c )
