#!/bin/bash
insmod switch_dev.ko
mknod -m 666 /dev/switch_dev c 240 0
