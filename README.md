# Pong OS

 *By: David*

## Overview
This is a kernel meant to run on bare metal `x86` processors for the sole purpose of playing Pong.

## Building, Running
To build the image, stay in the root directory (containing this `README`). You can then run `make clean && make -b` in order to make the image file, which will be stored in the `images` directory. Intermediate build files will be stored in the `build` directory, including object files, binaries, and intermediate disk images.

In order to run the OS, you will need to have `QEMU` to emulate a 32-bit `x86` processor. Additionally, for building and running, you will need to have `telnet`, `gcc`, as well as `ld`.

That being said, the program can be run by running `make run`.

In order to stop/monitor the application, you can open a separate terminal to run `make monitor`. Within the monitor, you can then quit by using `quit`.