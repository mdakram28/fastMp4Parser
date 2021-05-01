/*
 * time_to_sample_box.h
 *
 *  Created on: 01-May-2021
 *      Author: MAnsari15
 */

#ifndef BOXES_TIME_TO_SAMPLE_BOX_H_
#define BOXES_TIME_TO_SAMPLE_BOX_H_

#include <vector>
#include <string>
#include "../box_util.h"
#include "../io_util.h"


struct TimeToSampleBoxEntry {
	uint32_t sample_count;
	uint32_t sample_delta;
};

class TimeToSampleBox: public Box {
public:
	char version;			// 1 byte
	char flags[3];			// 3 bytes

	int entry_count;
	std::vector<TimeToSampleBoxEntry> entries;

	int total_sample_count = 0;

	TimeToSampleBox(Box &box) :
			Box(box) {
	}

	virtual void print(int l) {
		for (TimeToSampleBoxEntry entry : entries) {
			pt(l);
			printf("- sample_count=%d, sample_delta=%d\n", entry.sample_count,
					entry.sample_delta);
		}
	}

	virtual void parse(std::ifstream &f, int container_end, int level) {
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
};



#endif /* BOXES_TIME_TO_SAMPLE_BOX_H_ */
