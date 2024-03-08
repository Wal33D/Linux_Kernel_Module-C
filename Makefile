KBUILD_CFLAGS += -w
# Add both modules to the build line
obj-m += kernel_birthday_list_module.o kernel_timer_module.o

# Default target to compile the kernel modules
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Target to clean up build artifacts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# Targets to unload the kernel modules
unload_birthday_list:
	sudo rmmod kernel_birthday_list_module

unload_another_module:
	sudo rmmod another_kernel_module

# Targets to load the kernel modules
load_birthday_list:
	sudo insmod kernel_birthday_list_module.ko

load_another_module:
	sudo insmod another_kernel_module.ko

# Target to clear the kernel log buffer
clear:
	sudo dmesg -c

# Target to view the kernel log buffer
view:
	dmesg
