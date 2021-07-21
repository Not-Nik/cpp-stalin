# cpp-stalin (c) Nikolas Wipper 2021

# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.19)
project(cpp-stalin)

set(CMAKE_CXX_STANDARD 20)

set(STALIN_COMPILE_OPTIONS "-nostdinc++ -nodefaultlibs -pedantic -Wall -Wextra -Wpedantic")
set(STALIN_LINK_OPTIONS "-lc")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(STALIN_COMPILE_OPTIONS "${STALIN_COMPILE_OPTIONS} -lgcc")
endif()

add_definitions(${STALIN_COMPILE_OPTIONS})
add_link_options(${STALIN_LINK_OPTIONS})

add_library(stalin
        include/__config
        include/__declval
        include/__memory
        include/__stream_types
        include/cassert
        include/cerrno
        include/cfloat
        include/climits
        include/clocale
        include/cmath
        include/concepts
        include/cstddef
        include/cstdint
        include/cstdlib
        include/cstring
        include/cwchar
        include/exception
        include/fstream
        include/ios
        include/iosfwd
        include/iostream
        include/istream
        include/limits
        include/locale
        include/memory
        include/new
        include/numbers
        include/ostream
        include/stdexcept
        include/streambuf
        include/string
        include/system_error
        include/type_traits
        include/typeinfo
        include/utility

        src/exception.cpp
        src/ios.cpp
        src/new.cpp
        src/memory.cpp
        src/string.cpp
        src/system_error.cpp
        src/typeinfo.cpp)

target_include_directories(stalin PUBLIC include)

add_executable(iotest
        test/io.cpp include/source_location)
target_link_libraries(iotest stalin)
