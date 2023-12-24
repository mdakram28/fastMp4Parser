#include <vector>
#include <string>

#include "../box_util.hpp"
#include "../io_util.hpp"
#include "boxes.hpp"

void VideoSampleEntry::print(int l) {
    pt(l);
    printf("- index=%d\n", data_reference_index);
    pt(l);
    printf("- vendor=%d\n", vendor);
    pt(l);
    printf("- width=%d\n", width);
    pt(l);
    printf("- height=%d\n", height);
}

void VideoSampleEntry::parse(std::ifstream &f, int container_end, int level) {
    read_bytes(f, reserved, sizeof(reserved));
    data_reference_index = read_uint16(f);
    version = read_uint16(f);
    revision_level = read_uint16(f);
    vendor = read_uint32(f);
    temporal_quality = read_uint32(f);
    spatial_quality = read_uint32(f);
    width = read_uint16(f);
    height = read_uint16(f);
}