/*
 * sample_size_box.h
 *
 *  Created on: 01-May-2021
 *      Author: MAnsari15
 */

#ifndef BOXES_SAMPLE_SIZE_BOX_H_
#define BOXES_SAMPLE_SIZE_BOX_H_

#include <vector>
#include <string>
#include "../box_util.h"
#include "../io_util.h"

class SampleSizeBox: public Box {
public:
	char version;			// 1 byte
	char flags[3];			// 3 bytes

	uint32_t sample_size;
	uint32_t sample_count;
	std::vector<uint32_t> entries;

	uint64_t total_samples_size = 0;

	SampleSizeBox(Box &box) :
			Box(box) {
	}

	virtual void print(int l) {
		pt(l);
		printf("- total_samples_size=%llu\n", total_samples_size);
	}

	virtual void parse(std::ifstream &f, int container_end, int level) {
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
};

#endif /* BOXES_SAMPLE_SIZE_BOX_H_ */
