#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include "io_util.h"
#include "box_util.h"

using namespace std;

Box::Box(Box &copy_box) {
	this->size = copy_box.size;
	std::strncpy(this->type, copy_box.type, 4);
	this->parent = copy_box.parent;
}

Box::Box() {
}

void Box::print(int level) {
}

Box* Box::get(string type) {
	std::vector<Box*> children = child_map[type];
	if (children.size() > 0) {
		return children[0];
	} else {
		return NULL;
	}
}

std::vector<Box*> Box::getv(string type) {
	return child_map[type];
}

std::vector<Box*> Box::getv() {
	return child_list;
}

std::string Box::getp(string name) {
	if (props.find(name) != props.end()) {
		return props[name];
	} else {
		return NULL;
	}
}

BaseBox::BaseBox(Box &box) :
		Box(box) {
}
BaseBox::BaseBox() :
		Box() {
}
void BaseBox::parse(std::ifstream &f, int box_end, int level) {
	this->size = read_uint32(f);
	read_bytes(f, type, sizeof(type));
}



ContainerBox::ContainerBox(Box &box) :
		Box(box) {
}
ContainerBox::ContainerBox() :
		Box() {
}

void ContainerBox::parse(std::ifstream &f, int container_end, int level) {
	BaseBox box;
	while (bool(f) && f.tellg() < container_end) {
		uint32_t box_start = f.tellg();
		box.parse(f, 0, level + 1);
		uint32_t box_end = box_start + box.size;
		if(box.size == 0) continue;
		pt(level);
		printf("%.4s %d\n", box.type, box.size);

		box.parent = this;
		Box *child = this->add_child(f, box);
		if (child != NULL) {
			child->parse(f, box_end, level + 1);
			child->print(level);
			string type_str(box.type, box.type + 4);
			child_map[type_str].push_back(child);
			child_list.push_back(child);
		}

		f.seekg(box_end);
	}
}
