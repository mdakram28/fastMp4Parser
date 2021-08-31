#include <vector>
#include "boxes.h"

void AudioSampleEntry::print(int l) {
    pt(l);
    printf("- channel_count=%d\n", channel_count);
    pt(l);
    printf("- sample_size=%d\n", sample_size);
    pt(l);
    printf("- pre_defined=%d\n", pre_defined);
    pt(l);
    printf("- sample_rate=%d\n", sample_rate);
}

void AudioSampleEntry::parse(std::ifstream &f, int container_end, int level) {
    read_bytes(f, reserved1, sizeof(reserved1));
    channel_count = read_uint16(f);
    sample_size = read_uint16(f);
    pre_defined = read_uint16(f);
    read_bytes(f, reserved2, sizeof(reserved2));
    sample_rate = read_uint32(f);
}
