#include <vector>
#include <string>
#include "../box_util.h"
#include "../io_util.h"
#include "boxes.h"

void SampleSizeBox::print(int l) {
    pt(l);
    printf("- total_samples_size=%llu\n", total_samples_size);
}

void SampleSizeBox::parse(std::ifstream &f, int container_end, int level) {
    read_bytes(f, &version, 1);
    read_bytes(f, flags, sizeof(flags));

    sample_size = read_uint32(f);
    sample_count = read_uint32(f);
    total_samples_size = 0;
    for (int i = 1;
            bool(f) && f.tellg() < container_end && i <= sample_count; i++) {
        entries.push_back( read_uint32(f));
        total_samples_size += entries[i - 1];
    }
}