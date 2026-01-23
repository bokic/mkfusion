cmake_minimum_required (VERSION 3.22.3)
project (mkfusion)

set(CMAKE_VERBOSE_NINJA ON)
set(CMAKE_VERBOSE_CMAKE ON)
#set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)

#add_compile_options(-fsanitize=address)
#add_link_options(-fsanitize=address)

set(CMAKE_CXX_CPPCHECK "cppcheck")
set(CMAKE_C_CPPCHECK "cppcheck")
list(APPEND CMAKE_CXX_CPPCHECK "--enable=all")
list(APPEND CMAKE_CXX_CPPCHECK "--std=c++11")
#set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
#set(CMAKE_C_CLANG_TIDY "clang-tidy")

add_subdirectory (mkfusion)
add_subdirectory (tests)
