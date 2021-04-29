/*
 * video_sample_entry.h
 *
 *  Created on: 30-Apr-2021
 *      Author: MAnsari15
 */

#ifndef BOXES_VIDEO_SAMPLE_ENTRY_H_
#define BOXES_VIDEO_SAMPLE_ENTRY_H_

#include <vector>
#include <string>
#include "../box_util.h"
#include "../io_util.h"
#include "../constants.h"

class VideoSampleEntry: public Box {
public:
	char reserved[6];
	uint16_t data_reference_index;

	uint16_t version;
	uint16_t revision_level;
	uint32_t vendor;
	uint32_t temporal_quality;
	uint32_t spatial_quality;
	uint16_t width;
	uint16_t height;

	VideoSampleEntry(Box &box) :
			Box(box) {
	}
	virtual void print(int l) {
		pt(l);
		printf("- index=%d\n", data_reference_index);
		pt(l);
		printf("- vendor=%d\n", vendor);
		pt(l);
		printf("- width=%d\n", width);
		pt(l);
		printf("- height=%d\n", height);
	}

	virtual void parse(std::ifstream &f, int container_end, int level) {
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
};


#endif /* BOXES_VIDEO_SAMPLE_ENTRY_H_ */
