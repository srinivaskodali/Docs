obj-m :=myfilter.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean: 
	rm -rf $(wildcard *.o *.ko *.mod*   Mo* *.order)

