/*
 * movie_box.h
 *
 *  Created on: 29-Apr-2021
 *      Author: MAnsari15
 */

#ifndef MOVIE_BOX_H_
#define MOVIE_BOX_H_

#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <string>
#include "track_box.h"
#include "../io_util.h"
#include "../box_util.h"

class MovieHeaderBox: public Box {
public:
	char version;				// 1 byte
	char flags[3];				// 3 bytes

	time_t creation_time;		// 8|4 bytes
	time_t modification_time;	// 8|4 bytes
	uint64_t timescale;			// 4|4 bytes
	uint64_t duration;			// 8|4 bytes
	float rate;					// 4|4 bytes
	float volume;				// 2|2 bytes

	MovieHeaderBox(Box& box) : Box(box) {}

	virtual void parse(std::ifstream &f, int box_end, int level) {
		read_bytes(f, &version, 1);
		read_bytes(f, flags, sizeof(flags));
		if (version == 1) {
			creation_time = read_uint64(f) - 2082844800;
			modification_time = read_uint64(f) - 2082844800;
			timescale = read_uint32(f);
			duration = read_uint64(f);
		} else if (version == 0) {
			creation_time = read_uint32(f) - 2082844800;
			modification_time = read_uint32(f) - 2082844800;
			timescale = read_uint32(f);
			duration = read_uint32(f);
		}

		rate = read_uint32(f) / 65536.0;
		volume = read_uint16(f) / 256.0;
	}

	virtual void print(int l) {
		pt(l);
		printf("- creation_time=%s",
				asctime(localtime(&creation_time)));
		pt(l);
		printf("- modification_time=%s",
				asctime(localtime(&modification_time)));
		pt(l);
		printf("- timescale=%llu\n", timescale);
		pt(l);
		printf("- duration=%llu\n", duration);
		pt(l);
		printf("- rate=%9.6f\n", rate);
		pt(l);
		printf("- volume=%9.6f\n", volume);
	}
};

class MovieBox: public ContainerBox {
public:
	MovieBox(Box& box) : ContainerBox(box) {}

	virtual Box* add_child(std::ifstream &f, Box &copy_from) {
		Box *child = NULL;
		if (std::strncmp("mvhd", copy_from.type, 4) == 0) {
			child = new MovieHeaderBox(copy_from);
		} else if (std::strncmp("trak", copy_from.type, 4) == 0) {
			child = new TrackBox(copy_from);
		}
		return child;
	}
};


#endif /* MOVIE_BOX_H_ */
