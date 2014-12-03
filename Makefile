KBUILD_CFLAGS += -w
obj-m += Project5.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
unload:
	sudo rmmod Project5
load:
	sudo insmod Project5.ko
clear:
	sudo dmesg -c
view:
	dmesg