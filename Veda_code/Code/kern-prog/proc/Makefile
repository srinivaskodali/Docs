
obj-m  :=procfs_example.o
obj-m  +=simple_proc.o
obj-m  +=seq.o
obj-m  +=simpfs.o

KDIR= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	 rm -rf $(wildcard *.o *.ko *.mod.* .c* .t* test Module.symvers *.order *.markers)
