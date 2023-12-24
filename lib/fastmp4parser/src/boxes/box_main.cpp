#include <fstream>
#include <algorithm>
#include <cstring>
#include "../io_util.hpp"
#include "../box_util.hpp"
#include "boxes.hpp"

using std::string;

void FileTypeBox::parse(std::ifstream &f, int box_end, int level) {
	read_bytes(f, major_brand, sizeof(major_brand));
	minor_version = read_uint32(f);
	read_string(f, compatible_brands, size-16);
}

void FileTypeBox::print(int l) {
	pt(l);
	printf("- major_brand='%.4s'\n", major_brand);
	pt(l);
	printf("- minor_version='%d'\n", minor_version);
	pt(l);
	printf("- compatible_brands='%s'\n", compatible_brands.c_str());
}

Box* MainBox::add_child(std::ifstream &f, Box& copy_box) {
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