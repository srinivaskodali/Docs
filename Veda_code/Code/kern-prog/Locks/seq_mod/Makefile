obj-m  :=seq_module.o
obj-m  +=seq_writer1.o
obj-m  +=seq_writer2.o
obj-m  +=seq_reader1.o
obj-m  +=seq_reader2.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf $(wildcard *.o *.ko *.mod.* .c* .t* test Module.symvers *.order *.markers)
