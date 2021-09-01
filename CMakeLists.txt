cmake_minimum_required(VERSION 3.0.0)
project(fastmp4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(lib/fastmp4parser)
include_directories(lib/fastmp4parser/include)

add_executable(fastmp4
        src/main.cpp
)

target_link_libraries(fastmp4 fastmp4parser)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
