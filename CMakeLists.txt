# cpp-stalin (c) Nikolas Wipper 2021

# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.19)
project(cpp-stalin)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-nostdinc++ -Wall -Wextra -Wpedantic)

add_library(stalin
        include/__declval
        include/__stream_types
        include/cassert
        include/clocale
        include/cstddef
        include/cstdint
        include/cstdlib
        include/cstring
        include/cwchar
        include/fstream
        include/ios
        include/iosfwd
        include/iostream
        include/istream
        include/locale
        include/memory
        include/ostream
        include/streambuf
        include/string
        include/system_error
        include/type_traits
        include/utility

        src/ios.cpp
        src/ostream.cpp
        src/string.cpp)

target_include_directories(stalin PUBLIC include)

add_executable(iotest
        test/io.cpp)
target_link_libraries(iotest stalin)
