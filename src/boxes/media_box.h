/*
 * media_box.h
 *
 *  Created on: 29-Apr-2021
 *      Author: MAnsari15
 */

#ifndef MEDIA_BOX_H_
#define MEDIA_BOX_H_

#include <string.h>
#include "../box_util.h"
#include "sample_table_box.h"

class MediaHandlerBox: public Box {
public:
	uint32_t pre_defined;
	string handler_type;		// 4 bytes
	string handler_subtype;
	char reserved[12];
	string name;
	MediaHandlerBox(Box &box) :
			Box(box) {
	}

	virtual void parse(std::ifstream &f, int box_end, int level) {
		pre_defined = read_uint32(f);
		read_string(f, handler_type, 4);
		read_string(f, handler_subtype, 4);
		read_bytes(f, reserved, sizeof(reserved));
		read_string(f, name);
		props["handler_subtype"] = handler_subtype;
	}

	virtual void print(int l) {
		pt(l);
		printf("- pre_defined=%d\n", pre_defined);
		pt(l);
		printf("- handler_subtype=%.4s\n", handler_subtype.c_str());
		pt(l);
		printf("- name=%s\n", name.c_str());
	}
};

class MediaHeaderBox: public Box {
public:
	MediaHeaderBox(Box &box) :
			Box(box) {
	}
	virtual void parse(std::ifstream &f, int box_end, int level) {
	}
};

class MediaInfoBox: public ContainerBox {
public:
	MediaInfoBox(Box &box) :
			ContainerBox(box) {
	}
	virtual Box* add_child(std::ifstream &f, Box &copy_box) {
		Box *child = NULL;
		if (!std::strncmp("stbl", copy_box.type, 4)) {
			child = new SampleTableBox(copy_box);
		}
		return child;
	}
};

class MediaBox: public ContainerBox {
public:
	MediaBox(Box &box) :
			ContainerBox(box) {
	}
	virtual Box* add_child(std::ifstream &f, Box &copy_box) {
		Box *child = NULL;
		if (!std::strncmp("mdhd", copy_box.type, 4)) {
			child = new MediaHeaderBox(copy_box);
		} else if (!std::strncmp("minf", copy_box.type, 4)) {
			child = new MediaInfoBox(copy_box);
		} else if (!std::strncmp("hdlr", copy_box.type, 4)) {
			child = new MediaHandlerBox(copy_box);
		}
		return child;
	}
};

#endif /* MEDIA_BOX_H_ */
