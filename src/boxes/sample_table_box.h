/*
 * sample_table_box.h
 *
 *  Created on: 29-Apr-2021
 *      Author: MAnsari15
 */

#ifndef SAMPLE_TABLE_BOX_H_
#define SAMPLE_TABLE_BOX_H_

#include <vector>
#include <string>
#include "../box_util.h"
#include "../io_util.h"
#include "../constants.h"
#include "video_sample_entry.h"
#include "audio_sample_entry.h"
#include "time_to_sample_box.h"
#include "sample_size_box.h"

class SampleDescriptionBox: public Box {
public:
	char version;			// 1 byte
	char flags[3];			// 3 bytes

	uint32_t entry_count;	// 4 bytes

	SampleDescriptionBox(Box &box) :
			Box(box) {
	}

	virtual void parse(std::ifstream &f, int container_end, int level) {
		BaseBox box;
		read_bytes(f, &version, 1);
		read_bytes(f, flags, sizeof(flags));

		entry_count = read_uint32(f);
		for (int i = 1;
				bool(f) && f.tellg() < container_end && i <= entry_count; i++) {
			uint32_t entry_start = f.tellg();
			box.parse(f, 0, level + 1);
			uint32_t box_end = entry_start + box.size;
			for (int i = 0; i < level; i++)
				printf("\t");
			printf("%.4s %d\n", box.type, box.size);

			box.parent = this;
			Box *child = NULL;

			string type_str(box.type, box.type + 4);
			string format = this->parent->parent->parent->get("hdlr")->getp(
					"handler_subtype");
			if (format == "vide") {
				child = new VideoSampleEntry(box);
			} else if (format == "soun") {
				child = new AudioSampleEntry(box);
			}

			if (child != NULL) {
				child->parse(f, box_end, level + 1);
				child->print(level);
			} else {
				child = new BaseBox(box);
			}

			child_map[type_str].push_back(child);
			child_list.push_back(child);

			f.seekg(box_end);
		}
	}
};

class SampleTableBox: public ContainerBox {
public:
	SampleTableBox(Box &box) :
			ContainerBox(box) {
	}
	virtual Box* add_child(std::ifstream &f, Box &copy_box) {
		Box *child = NULL;
		if (std::strncmp("stsd", copy_box.type, 4) == 0) {
			child = new SampleDescriptionBox(copy_box);
		} else if (!std::strncmp("stts", copy_box.type, 4)) {
			child = new TimeToSampleBox(copy_box);
		} else if (!std::strncmp("stsz", copy_box.type, 4)
				|| !std::strncmp("stz2", copy_box.type, 4)) {
			child = new SampleSizeBox(copy_box);
		}
		return child;
	}
};

#endif /* SAMPLE_TABLE_BOX_H_ */
