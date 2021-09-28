# cpp-stalin (c) Nikolas Wipper 2021

# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.19)
project(cpp-stalin)

set(CMAKE_CXX_STANDARD 20)

set(STALIN_COMPILE_OPTIONS "-nostdinc++ -nodefaultlibs -pedantic -Wall -Wextra -Wpedantic")
set(STALIN_LINK_OPTIONS "-lc")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(STALIN_COMPILE_OPTIONS "${STALIN_COMPILE_OPTIONS} -lgcc")
endif ()

add_definitions(${STALIN_COMPILE_OPTIONS})
add_link_options(${STALIN_LINK_OPTIONS})

add_library(stalin
        include/__llvm/type_traits.h
        include/__config
        include/__declval
        include/__math
        include/__memory
        include/__stream_types
        include/bit
        include/bitset
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
        include/initializer_list
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
        include/source_location
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
        src/system_error.cpp
        src/typeinfo.cpp include/cstdarg)

target_include_directories(stalin PUBLIC include)

add_executable(iotest test/io.cpp)
target_link_libraries(iotest stalin)

add_executable(traits_test test/type_traits.cpp)
target_link_libraries(traits_test stalin)

add_executable(init_list_test test/initializer_list.cpp)
target_link_libraries(init_list_test stalin)

add_executable(num_limit_test test/limits.cpp)
target_link_libraries(num_limit_test stalin)

add_executable(bit_test test/bit.cpp)
target_link_libraries(bit_test stalin)

add_executable(bitset_test test/bitset.cpp)
target_link_libraries(bitset_test stalin)
