#include <algorithm>
#include "../io_util.hpp"
#include "../box_util.hpp"
#include "boxes.hpp"

void MovieHeaderBox::parse(std::ifstream &f, int box_end, int level) {
    read_bytes(f, &version, 1);
    read_bytes(f, flags, sizeof(flags));
    if (version == 1) {
        creation_time = read_uint64(f) - 2082844800;
        modification_time = read_uint64(f) - 2082844800;
        timescale = read_uint32(f);
        duration = read_uint64(f);
    } else if (version == 0) {
        creation_time = read_uint32(f) - 2082844800;
        modification_time = read_uint32(f) - 2082844800;
        timescale = read_uint32(f);
        duration = read_uint32(f);
    }

    rate = read_uint32(f) / 65536.0;
    volume = read_uint16(f) / 256.0;
}

void MovieHeaderBox::print(int l) {
    pt(l);
    printf("- creation_time=%s",
           asctime(localtime(&creation_time)));
    pt(l);
    printf("- modification_time=%s",
           asctime(localtime(&modification_time)));
    pt(l);
    printf("- timescale=%llu\n", timescale);
    pt(l);
    printf("- duration=%llu\n", duration);
    pt(l);
    printf("- rate=%9.6f\n", rate);
    pt(l);
    printf("- volume=%9.6f\n", volume);
}

Box *MovieBox::add_child(std::ifstream &f, Box &copy_from) {
    Box *child = NULL;
    if (std::strncmp("mvhd", copy_from.type, 4) == 0) {
        child = new MovieHeaderBox(copy_from);
    } else if (std::strncmp("trak", copy_from.type, 4) == 0) {
        child = new TrackBox(copy_from);
    }
    return child;
}
