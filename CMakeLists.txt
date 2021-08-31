cmake_minimum_required(VERSION 3.0.0)
project(fastmp4 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(fastmp4
        src/main.cpp
        src/box_util.cpp
        src/io_util.cpp
        # Boxes
        src/boxes/box_video_sample_entry.cpp
        src/boxes/box_audio_sample_entry.cpp
        src/boxes/box_time_to_sample.cpp
        src/boxes/box_sample_size.cpp
        src/boxes/box_sample_table.cpp
        src/boxes/box_media.cpp
        src/boxes/box_track.cpp
        src/boxes/box_movie.cpp
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
