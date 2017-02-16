obj-m  :=rwsem_module.o
obj-m  +=rwsem_writer1.o
obj-m  +=rwsem_writer2.o
obj-m  +=rwsem_reader1.o
obj-m  +=rwsem_reader2.o

KDIR = /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -rf $(wildcard *.o *.ko *.mod.* .c* .t* test Module.symvers *.order *.markers)
