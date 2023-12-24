/*
 * box_util.hpp
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
#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include <map>

class Box {
public:
	uint32_t size;
	char type[4];

	std::map< std::string, std::vector< Box* > > child_map;
	std::vector<Box*> child_list;
	Box *parent;
	std::map<std::string, std::string> props;

	Box(Box &copy_box);
	Box();

	virtual void print(int level);

	virtual void parse(std::ifstream &f, int box_end, int level) = 0;

	Box* get(std::string type);

	std::vector<Box*> getv(std::string type);

	std::vector<Box*> getv();

	std::string getp(std::string name);
};

class BaseBox: public Box {
public:
	BaseBox(Box &box);
	BaseBox();

	virtual void parse(std::ifstream &f, int box_end, int level);
};

class ContainerBox: public Box {
public:
	ContainerBox(Box &box);
	ContainerBox();

	virtual void parse(std::ifstream &f, int container_end, int level);

	virtual Box* add_child(std::ifstream &f, Box &copy_from) = 0;
};

#endif /* BOX_UTIL_H_ */
