#!/usr/bin/bash
# Compile and "deploy" a new custom kernel from source on Ubuntu Linux

# Change this if you'd like. It has no relation
# to the suffix set in the kernel config.
SUFFIX="-customkernel"

# This causes the script to exit if an error occurs
set -e

# Compile the kernel
make -j8

# Compile and install modules
make -j8 modules_install

# Install kernel image
make -j8 install

# Update the bootloader
sudo update-grub
