#include <algorithm>
#include "../io_util.hpp"
#include "../box_util.hpp"
#include "boxes.hpp"

void TrackHeaderBox::parse(std::ifstream &f, int box_end, int level) {
    read_bytes(f, &version, 1);
    read_bytes(f, flags, sizeof(flags));
    if (version == 1) {
        creation_time = read_uint64(f) - 2082844800;
        modification_time = read_uint64(f) - 2082844800;
    } else if (version == 0) {
        creation_time = read_uint32(f) - 2082844800;
        modification_time = read_uint32(f) - 2082844800;
    }
}

void TrackHeaderBox::print(int level) {
    pt(level);
    printf("- creation_time=%s",
           asctime(localtime(&creation_time)));
    pt(level);
    printf("- modification_time=%s",
           asctime(localtime(&modification_time)));
}

Box *TrackBox::add_child(std::ifstream &f, Box &copy_from) {
    Box *child = NULL;
    if (!std::strncmp("tkhd", copy_from.type, 4)) {
        child = new TrackHeaderBox(copy_from);
    } else if (!std::strncmp("mdia", copy_from.type, 4)) {
        child = new MediaBox(copy_from);
    }
    return child;
}