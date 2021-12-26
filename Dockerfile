# Dockerfile for OS work
# by David

# Use GCC 
FROM gcc

# Update packages and install vim, gdb, and build tools
RUN apt-get update -y
RUN apt-get install build-essential vim gdb -y

# Install additional packages as necessary
RUN apt-get install nasm -y