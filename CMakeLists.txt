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
##  CMakeLists.txt
##--------------------------------------------------------------------##

##--------------------------------------------------------------------##
##  project
##--------------------------------------------------------------------##

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Melee-Perft CXX)
SET(VERSION_MAJOR 1)
SET(VERSION_MINOR 00)

##--------------------------------------------------------------------##
##  program
##--------------------------------------------------------------------##

CONFIGURE_FILE(src/program.h.in ${CMAKE_BINARY_DIR}/gen/program.h)
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR}/gen)

##--------------------------------------------------------------------##
##  executables
##--------------------------------------------------------------------##

FILE(GLOB SOURCES src/*.cpp)
ADD_EXECUTABLE(melee-perft ${SOURCES})
