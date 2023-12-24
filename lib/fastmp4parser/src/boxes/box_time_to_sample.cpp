#include <vector>
#include "boxes.hpp"

void TimeToSampleBox::print(int l) {
    for (TimeToSampleBoxEntry entry : entries) {
        pt(l);
        printf("- sample_count=%d, sample_delta=%d\n", entry.sample_count,
                entry.sample_delta);
    }
}

void TimeToSampleBox::parse(std::ifstream &f, int container_end, int level) {
    BaseBox box;
    read_bytes(f, &version, 1);
    read_bytes(f, flags, sizeof(flags));

    entry_count = read_uint32(f);
    total_sample_count = 0;
    for (int i = 1;
            bool(f) && f.tellg() < container_end && i <= entry_count; i++) {
        entries.push_back( { read_uint32(f), read_uint32(f) });
        total_sample_count += entries[i - 1].sample_count;
    }
}