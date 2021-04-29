/*
 * box_util.h
 *
 *  Created on: 29-Apr-2021
 *      Author: MAnsari15
 */

#ifndef BOX_UTIL_H_
#define BOX_UTIL_H_

#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <string.h>
#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include "io_util.h"

class Box {
public:
	uint32_t size;
	char type[4];

	std::map<std::string, std::vector<Box*>> child_map;
	std::vector<Box*> child_list;
	Box *parent;
	std::map<std::string, std::string> props;

	Box(Box &copy_box) {
		this->size = copy_box.size;
		std::strncpy(this->type, copy_box.type, 4);
		this->parent = copy_box.parent;
	}

	Box() {
	}

	virtual void print(int level) {
	}

	virtual void parse(std::ifstream &f, int box_end, int level) = 0;

	Box* get(string type) {
		std::vector<Box*> children = child_map[type];
		if (children.size() > 0) {
			return children[0];
		} else {
			return NULL;
		}
	}

	std::vector<Box*> getv(string type) {
		return child_map[type];
	}

	std::vector<Box*> getv() {
		return child_list;
	}

	std::string getp(string name) {
		if (props.find(name) != props.end()) {
			return props[name];
		} else {
			return NULL;
		}
	}
};

class BaseBox: public Box {
public:
	BaseBox(Box &box) :
			Box(box) {
	}
	BaseBox() :
			Box() {
	}
	virtual void parse(std::ifstream &f, int box_end, int level) {
		this->size = read_uint32(f);
		read_bytes(f, type, sizeof(type));
	}
};

class ContainerBox: public Box {
public:
	ContainerBox(Box &box) :
			Box(box) {
	}
	ContainerBox() :
			Box() {
	}

	virtual void parse(std::ifstream &f, int container_end, int level) {
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

	virtual Box* add_child(std::ifstream &f, Box &copy_from) = 0;
};

#endif /* BOX_UTIL_H_ */
