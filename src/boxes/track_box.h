/*
 * track_box.h
 *
 *  Created on: 29-Apr-2021
 *      Author: MAnsari15
 */

#ifndef TRACK_BOX_H_
#define TRACK_BOX_H_

#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <string.h>
#include "../io_util.h"
#include "../box_util.h"
#include "media_box.h"

class TrackHeaderBox: public Box {
public:
	char version;			// 1 byte
	char flags[3];			// 3 bytes

	time_t creation_time;		// 8 bytes
	time_t modification_time;	// 8 bytes

	TrackHeaderBox(Box& box): Box(box) {}

	virtual void parse(std::ifstream &f, int box_end, int level) {
		read_bytes(f, &version, 1);
		read_bytes(f, flags, sizeof(flags));
		if (version == 1) {
			creation_time = read_uint64(f) - 2082844800;
			modification_time = read_uint64(f) - 2082844800;
		} else if (version == 0) {
			creation_time = read_uint32(f) - 2082844800;
			modification_time = read_uint32(f) - 2082844800;
		}
	}

	virtual void print(int level) {
		pt(level);
		printf("- creation_time=%s",
				asctime(localtime(&creation_time)));
		pt(level);
		printf("- modification_time=%s",
				asctime(localtime(&modification_time)));
	}
};

class TrackBox: public ContainerBox {
public:
	TrackBox(Box& box): ContainerBox(box) {}
	virtual Box* add_child(std::ifstream &f, Box &copy_from) {
		Box *child = NULL;
		if (!std::strncmp("tkhd", copy_from.type, 4)) {
			child = new TrackHeaderBox(copy_from);
		} else if (!std::strncmp("mdia", copy_from.type, 4)) {
			child = new MediaBox(copy_from);
		}
		return child;
	}
};

#endif /* TRACK_BOX_H_ */
