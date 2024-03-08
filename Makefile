KBUILD_CFLAGS += -w
# Specify the path for the modules relative to the src/ directory
obj-m += src/kernel_birthday_list_module.o src/kernel_timer_module.o src/kernel_workqueue_module.o

# Default target to compile the kernel modules
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

# Target to clean up build artifacts
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

# Targets to unload the kernel modules
unload_birthday_list:
	sudo rmmod kernel_birthday_list_module

unload_timer:
	sudo rmmod kernel_timer_module

unload_workqueue:
	sudo rmmod kernel_workqueue_module

# Targets to load the kernel modules. Adjust the path for the ko files.
load_birthday_list:
	sudo insmod src/kernel_birthday_list_module.ko

load_timer:
	sudo insmod src/kernel_timer_module.ko

load_workqueue:
	sudo insmod src/kernel_workqueue_module.ko

# Target to clear the kernel log buffer
clear:
	sudo dmesg -c

# Target to view the kernel log buffer
view:
	dmesg
