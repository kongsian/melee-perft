##  target operating system
SET(CMAKE_SYSTEM_NAME Linux)

##  C and C++ compilers
SET(CMAKE_C_COMPILER   /usr/local/gcc-4.7.3/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/local/gcc-4.7.3/bin/g++)

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
##  To link std::thread statically, the whole of libpthread.a 
##  must be linked in.
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mpopcnt")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "" FORCE)
