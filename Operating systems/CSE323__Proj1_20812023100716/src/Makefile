KDIR ?= /lib/modules/$(shell uname -r)/build

obj-m += simple.o proc_jiffies.o proc_seconds.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
