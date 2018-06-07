KERNELDIR = /lib/modules/$(shell uname -r)/build

obj-m := switch_dev.o

PWD := $(shell pwd)

default :
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	#gcc -o switch_dev switch_dev.c

clean :
	-rmmod -f switch_dev
	rm -rf /dev/switch_dev
	rm -rf *.ko *.o *.cmd *.order *.symvers .tmp_versions .*.cmd *.mod.*
