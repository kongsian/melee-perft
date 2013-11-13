##  target operating system
SET(CMAKE_SYSTEM_NAME Windows)

##  C and C++ compilers
SET(CMAKE_C_COMPILER   /usr/local/mingw64/bin/x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER /usr/local/mingw64/bin/x86_64-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER  /usr/local/mingw64/bin/x86_64-w64-mingw32-windres)

##  C++ flags
SET(CMAKE_CXX_FLAGS "-pedantic")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mpopcnt")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "" FORCE)

##  target environment
SET(CMAKE_FIND_ROOT_PATH /usr/local/mingw64/x86_64-w64-mingw32)

##  adjust the default behaviour of the FIND_XXX() commands:
##  search programs in the host environment
##  search headers and libraries in the target environment
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
