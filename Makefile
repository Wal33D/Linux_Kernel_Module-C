KBUILD_CFLAGS += -w
obj-m += kernel_birthday_list_module.o

# Default target to compile the kernel module
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Target to clean up build artifacts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# Target to unload the kernel module
unload:
	sudo rmmod kernel_birthday_list_module

# Target to load the kernel module
load:
	sudo insmod kernel_birthday_list_module.ko

# Target to clear the kernel log buffer
clear:
	sudo dmesg -c

# Target to view the kernel log buffer
view:
	dmesg
