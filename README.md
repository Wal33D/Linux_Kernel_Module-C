# LinuxKernelModule

#### Purpose
The LinuxKernelModule project aims to provide hands-on examples and tutorials for creating and interacting with Linux Kernel Modules. This project serves as a practical resource for learning the basics of kernel module development and understanding how to extend the Linux kernel's functionalities.

#### Main Features
- **Hello World Module**: A simple module to demonstrate the basics of loading and unloading kernel modules.
- **Character Device Module**: Shows how to create a character device to allow user-space applications to communicate with the kernel module.
- **Proc Filesystem Module**: Illustrates the creation of proc files for interacting with kernel modules through the /proc filesystem.
- **Netfilter Hooks Module**: Demonstrates how to use netfilter hooks to intercept and modify network packets.
- **System Call Interception Module**: A guide on how to intercept and replace system calls.
- **Kernel Timers Module**: Explains how to use kernel timers within modules for timed operations.
- **Workqueues Module**: Provides examples on using workqueues for deferred work.
- **Custom IOCTLs Module**: Shows how to implement custom IOCTLs for device-specific operations.
- **Parameter Passing Module**: Demonstrates passing parameters to kernel modules at load time.

#### Setup and Usage

##### Prerequisites
- Linux environment with kernel development tools installed (`build-essential`, `linux-headers-$(uname -r)`)
- Basic knowledge of C programming and Linux command line

##### Compiling Modules
1. Navigate to the module directory you wish to compile.
   ```
   cd LinuxKernelModule/<module_name>
   ```
2. Use the Makefile provided in each module directory to compile the module. Simply run:
   ```
   make
   ```
   This will create a `.ko` file, which is the loadable kernel module.

##### Loading Modules
1. Load your compiled module into the kernel using `insmod`:
   ```
   sudo insmod <module_name>.ko
   ```
2. Check if the module is loaded successfully:
   ```
   lsmod | grep <module_name>
   ```

##### Unloading Modules
1. Remove your module from the kernel using `rmmod`:
   ```
   sudo rmmod <module_name>
   ```

##### Viewing Module Output
- For most modules, output can be viewed with `dmesg`:
   ```
   dmesg | tail
   ```

#### Contributing
Contributions are welcome! If you have improvements, bug fixes, or additional examples, please feel free to open a pull request or issue.

#### License
This project is licensed under the MIT License - see the LICENSE file for details.

Enjoy exploring Linux Kernel Module development!