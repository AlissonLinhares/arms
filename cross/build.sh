#! /bin/bash

INSTALL_PATH=/home/alisson/.cross
TARGET=arm-linux-eabi
PARALLEL_MAKE=-j16
BINUTILS_VERSION=binutils-2.28.1
GCC_VERSION=gcc-7.2.0

export PATH=$INSTALL_PATH/bin:$PATH

# Download packages
export http_proxy=$HTTP_PROXY https_proxy=$HTTP_PROXY ftp_proxy=$HTTP_PROXY
wget -nc https://ftp.gnu.org/gnu/binutils/$BINUTILS_VERSION.tar.gz
wget -nc https://ftp.gnu.org/gnu/gcc/$GCC_VERSION/$GCC_VERSION.tar.gz
wget -nc -O newlib-master.zip https://github.com/bminor/newlib/archive/master.zip || true

# Extract everything
for f in *.tar*; do tar xfk $f; done
unzip -qo newlib-master.zip

# Step 1. Binutils
mkdir -p build-binutils
cd build-binutils
make clean
../$BINUTILS_VERSION/configure --prefix=$INSTALL_PATH --target=$TARGET
make $PARALLEL_MAKE all
make install
cd ..

# Step 2. C/C++ Compilers
mkdir -p build-gcc
cd build-gcc
make clean
../$GCC_VERSION/configure --prefix=$INSTALL_PATH --target=$TARGET --enable-languages=c,c++ --with-newlib
make $PARALLEL_MAKE all-gcc
make install-gcc
cd ..

# Steps 3: Newlib
mkdir -p build-newlib
cd build-newlib
make clean

../newlib-master/configure --prefix=$INSTALL_PATH --target=$TARGET --disable-newlib-atexit-dynamic-alloc --disable-newlib-supplied-syscalls
make $PARALLEL_MAKE all
make install
cd ..

# Step 4. Standard C++ Library & the rest of GCC
cd build-gcc
make $PARALLEL_MAKE all
make install
cd ..
