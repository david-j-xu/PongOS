# Pong OS

*By: David*

## Overview

This is a kernel meant to run on bare metal `x86` processors for the sole purpose of playing Pong.

## Building, Running

To build the image, stay in the root directory (containing this `README`). You can then run `make clean && make -b` in order to make the image file, which will be stored in the `images` directory. Intermediate build files will be stored in the `build` directory, including object files, binaries, and intermediate disk images.

In order to run the OS, you will need to have `QEMU` to emulate a 32-bit `x86` processor. Additionally, for building and running, you will need to have `telnet`, `gcc`, as well as `ld`.

That being said, the program can be run by running `make run`.

In order to stop/monitor the application, you can open a separate terminal to run `make monitor`. Within the monitor, you can then quit by using `quit`.

If you are running on OSX (like me), the make won't run. So, you'll have to open up a docker container with the GNU linker, which you can do by running `docker-compose run --rm vm`. The current directory will be linked in `/home/workspace`. You can then make from there, and run in your local machine.

## Resources

I used Nick Blundell's OS development guide, which helped a ton for getting the bootsector code to function. Additionally, jdh's Tetris OS was very helpful in figuring out creating the VGA driver and other graphical elements. Lastly, vladcc's Tetris OS helped a ton when it came to interrupt handling.
