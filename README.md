# Linux Kernel Module Development

Welcome to the **Linux Kernel Module Development** repository! This resource is dedicated to developers, system administrators, and enthusiasts keen on exploring and contributing to the Linux kernel through module development. Our goal is to provide a comprehensive learning platform for creating and managing Linux kernel modules, offering insights into kernel functionalities, and optimizing system operations.

## 🚀 Key Highlights

- **Custom Kernel Modules**: Dive into a collection of code examples and detailed guides aimed at facilitating the creation of custom kernel modules.
- **Step-by-Step Tutorials**: Detailed tutorials designed to simplify the kernel module development process, from setup to deployment.
- **Testing & Debugging Tools**: Discover tools and methodologies for effective testing and debugging of kernel modules, ensuring reliability and performance.
- **Community Contributions**: Engage with a community passionate about kernel development, sharing knowledge, and driving innovations.

## 🛠 Getting Started

### Preparations

To begin your kernel module development journey, you'll need:
- A system running a Linux distribution.
- Knowledge of C programming language.
- Basic understanding of Linux kernel architecture and module development.
- The GCC compiler and Make for building modules.
- The Linux kernel headers installed on your system.

### Installation Steps

1. **Install Required Packages**:

   On Ubuntu/Debian-based systems:
   ```bash
   sudo apt-get install build-essential linux-headers-$(uname -r)
   ```

   On CentOS/RHEL-based systems:
   ```bash
   sudo yum install gcc make kernel-devel
   ```

2. **Clone the Repository**:
   ```bash
   git clone https://github.com/Wal33D/Linux_Kernel_Module-C.git
   cd Linux_Kernel_Module-C
   ```

3. **Compile Your Module**:
   Navigate to your module's directory and initiate the compilation:
   ```bash
   make
   ```
   This places the resulting `.ko` files in the `build/` directory.
   For additional compiler warnings from the kernel build system, you can use:
   ```bash
   make W=1
   ```

4. **Insert Your Module into the Kernel**:
    Load your module into the kernel environment:
    ```bash
    sudo insmod your_module_name.ko
    ```

5. **Run Tests**:
    After building, you can run the provided test script using the Makefile. This step requires root privileges and will automatically insert and remove the sample modules:
    ```bash
    make test
    ```

### Usage Tips

After loading your module, inspect its output or interaction with the system using `dmesg`. To remove the module:
```bash
sudo rmmod your_module_name
```

### Example Module Usage

Set the timer interval when loading `kernel_timer_module`:

```bash
sudo insmod build/kernel_timer_module.ko timer_interval=2
```

Specify the requeue interval for `kernel_workqueue_module`:

```bash
sudo insmod build/kernel_workqueue_module.ko work_interval=10
```

## ⚠️ Safety

Loading kernel modules requires root privileges and can potentially crash or hang
your system. Always test new modules in a virtual machine or other
non-production environment before deploying on real hardware.

### Contributing 🤝

Contributions are the cornerstone of this project's growth and success. Whether it's adding new features, fixing bugs, or improving documentation, your help is greatly appreciated. When opening an issue, please use the templates in `.github/ISSUE_TEMPLATE`. Pull requests should follow the guidelines outlined in `.github/PULL_REQUEST_TEMPLATE`.

## Support 🤗

Encountering challenges or have questions? Open an issue in our issue tracker for support and collaboration.

**Start your kernel module development journey today—happy coding!**

## License

All source code and documentation in this repository are released under the [MIT License](LICENSE),
except for `src/kernel_workqueue_module.c` which is licensed under the GNU
General Public License (GPL) because it uses GPL-only kernel symbols.
