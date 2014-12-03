obj-m += ProjectA5.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
unload:
	sudo rmmod ProjectA5
load:
	sudo insmod ProjectA5.ko