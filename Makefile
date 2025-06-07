# Allow Make to emit compiler warnings by default.  Invoke 'make W=1'
# to enable additional kernel build warnings.
KBUILD_CFLAGS +=
# Specify the path for the modules relative to the src/ directory
obj-m += src/kernel_birthday_list_module.o src/kernel_timer_module.o src/kernel_workqueue_module.o

# Directory to place built kernel object files
BUILD_DIR ?= build

# Module names without extension for convenience
MODULES := kernel_birthday_list_module kernel_timer_module kernel_workqueue_module

# Default target to compile the kernel modules and place output in $(BUILD_DIR)
all:
	mkdir -p $(BUILD_DIR)
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	@for m in $(MODULES); do \
	if [ -f src/$$m.ko ]; then mv -f src/$$m.ko $(BUILD_DIR)/; fi; \
	done

# Target to clean up build artifacts
clean:
	        make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	        rm -rf $(BUILD_DIR)

# Targets to unload the kernel modules
unload_birthday_list:
	sudo rmmod kernel_birthday_list_module

unload_timer:
	sudo rmmod kernel_timer_module

unload_workqueue:
	sudo rmmod kernel_workqueue_module

# Targets to load the kernel modules. Adjust the path for the ko files.
load_birthday_list:
	        sudo insmod $(BUILD_DIR)/kernel_birthday_list_module.ko

load_timer:
	        sudo insmod $(BUILD_DIR)/kernel_timer_module.ko

load_workqueue:
	        sudo insmod $(BUILD_DIR)/kernel_workqueue_module.ko

# Target to clear the kernel log buffer
clear:
	sudo dmesg -c

# Target to view the kernel log buffer
view:
	dmesg

# Run module tests (requires root privileges)
test: all
	sudo bash tests/module_test.sh
