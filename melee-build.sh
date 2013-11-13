#!/bin/sh
##--------------------------------------------------------------------##
##
##  Melee Perft
##  Copyright (C) 2013 Chua Kong Sian.
##
##  This file is part of Melee Perft.
##
##  Melee Perft is free software: you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation, either version 3 of the License, or
##  (at your option) any later version.
##
##  Melee Perft is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with Melee Perft.  If not, see <http://www.gnu.org/licenses/>.
##
##--------------------------------------------------------------------##

##--------------------------------------------------------------------##
##  melee-build.sh
##--------------------------------------------------------------------##

##--------------------------------------------------------------------##
##  build() - function to build for a specific platform
##--------------------------------------------------------------------##

build () 
{
    CURRENT_DIR=`pwd`

    OS_BUILD_DIR=${BUILD_DIR}/$1
    if [ ! -d ${OS_BUILD_DIR} ]; then
        mkdir ${OS_BUILD_DIR}
    fi

    cd ${OS_BUILD_DIR}
    if [ -f CMakeCache.txt ]; then
        cmake ../..
    else
        cmake -DCMAKE_TOOLCHAIN_FILE=../../toolchain/$1.cmake ../..
    fi
    make

    cd ${CURRENT_DIR} 
}

##--------------------------------------------------------------------##
##  Main function starts here
##--------------------------------------------------------------------##

export LIBRARY_PATH=/usr/lib/x86_64-linux-gnu

BUILD_DIR=build
if [ ! -d ${BUILD_DIR} ]; then
    mkdir ${BUILD_DIR}    
fi

build x86_64-linux-gnu          ##  Linux 64-bit
build i386-linux-gnu            ##  Linux 32-bit
build x86_64-w64-mingw32        ##  Windows 64-bit
build i686-w64-mingw32          ##  Windows 32-bit
