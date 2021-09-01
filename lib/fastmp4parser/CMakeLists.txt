add_library(fastmp4parser STATIC 
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
    src/boxes/box_main.cpp
)