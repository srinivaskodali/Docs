
obj-m := kernl_mod.o

KERNDIR ?= /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

default :
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules

clean :
	rm -rf $(wildcard *.o *.ko *.mo* Mo* *.order)


