

#ifndef BOXES_AUDIO_SAMPLE_ENTRY_H_
#define BOXES_AUDIO_SAMPLE_ENTRY_H_

#include <vector>
#include <string>
#include "../box_util.h"
#include "../io_util.h"
#include "../constants.h"

class AudioSampleEntry: public Box {
public:
	char reserved1[8];
	uint16_t channel_count;
	uint16_t sample_size;
	uint16_t pre_defined;
	char reserved2[2];
	uint32_t sample_rate;

	AudioSampleEntry(Box &box) :
	Box(box) {
	}
	virtual void print(int l) {
		pt(l);
		printf("- channel_count=%d\n", channel_count);
		pt(l);
		printf("- sample_size=%d\n", sample_size);
		pt(l);
		printf("- pre_defined=%d\n", pre_defined);
		pt(l);
		printf("- sample_rate=%d\n", sample_rate);
	}

	virtual void parse(std::ifstream &f, int container_end, int level) {
		read_bytes(f, reserved1, sizeof(reserved1));
		channel_count = read_uint16(f);
		sample_size = read_uint16(f);
		pre_defined = read_uint16(f);
		read_bytes(f, reserved2, sizeof(reserved2));
		sample_rate = read_uint32(f);
	}
};

#endif /* BOXES_AUDIO_SAMPLE_ENTRY_H_ */
