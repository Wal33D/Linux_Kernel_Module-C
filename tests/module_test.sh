#!/bin/bash
set -e

BUILD_DIR="$(dirname "$0")/../build"
MODULES=(kernel_birthday_list_module kernel_timer_module kernel_workqueue_module)

for mod in "${MODULES[@]}"; do
    mod_ko="$BUILD_DIR/$mod.ko"
    if [ ! -f "$mod_ko" ]; then
        echo "$mod_ko not found. Run 'make' first." >&2
        exit 1
    fi
    echo "Inserting $mod_ko"
    sudo insmod "$mod_ko"
    echo "Removing $mod"
    sudo rmmod "$mod"
    echo
done
