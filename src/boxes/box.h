#ifndef BOX_H
#define BOX_H

#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <cstring>
#include "movie_box.h"
#include "../io_util.h"
#include "../box_util.h"
#include "media_data_box.h"

using std::string;

class FileTypeBox: public Box {
public:
	char major_brand[4];
	uint32_t minor_version;
	string compatible_brands;

	FileTypeBox(Box& box): Box(box) {}
	virtual void parse(std::ifstream &f, int box_end, int level) {
		read_bytes(f, major_brand, sizeof(major_brand));
		minor_version = read_uint32(f);
		read_string(f, compatible_brands, size-16);
	}

	virtual void print(int l) {
		pt(l);
		printf("- major_brand='%.4s'\n", major_brand);
		pt(l);
		printf("- minor_version='%d'\n", minor_version);
		pt(l);
		printf("- compatible_brands='%s'\n", compatible_brands.c_str());
	}
};

class MainBox: public ContainerBox {
public:
	MainBox(): ContainerBox() {}
	virtual Box* add_child(std::ifstream &f, Box& copy_box) {
		Box *child = NULL;
		if (std::strncmp("ftyp", copy_box.type, 4) == 0) {
			child = new FileTypeBox(copy_box);
		} else if(std::strncmp("moov", copy_box.type, 4) == 0) {
			child = new MovieBox(copy_box);
		} else if(!std::strncmp("mdat", copy_box.type, 4)) {
			child = new MediaDataBox(copy_box);
		}
		return child;
	}
};

#endif
