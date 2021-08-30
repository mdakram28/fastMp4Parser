#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "io_util.h"

using std::string;

void pt(int level) {
	for (int i = 0; i < level; i++) {
		printf("\t");
	}
}

void flip_endian(uint32_t &val) {
	val = (val << 24) | ((val << 8) & 0x00ff0000) | ((val >> 8) & 0x0000ff00)
			| (val >> 24);
}

void flip_endian(uint64_t &val) {
	val = (val << 24) | ((val << 8) & 0x00ff0000) | ((val >> 8) & 0x0000ff00)
			| (val >> 24);
}


void reverse_bytes(char *start, int size) {
	char *istart = start, *iend = istart + size;
	std::reverse(istart, iend);
}

uint64_t read_uint64(std::ifstream &f) {
	uint64_t val = 0;
	f.read((char*) &val, sizeof(val));
	reverse_bytes((char*) &val, sizeof(val));
	return val;
}

uint32_t read_uint32(std::ifstream &f) {
	uint32_t val = 0;
	f.read((char*) &val, sizeof(val));
	reverse_bytes((char*) &val, sizeof(val));
	return val;
}

uint16_t read_uint16(std::ifstream &f) {
	uint16_t val = 0;
	f.read((char*) &val, sizeof(val));
	reverse_bytes((char*) &val, sizeof(val));
	return val;
}

void read_string(std::ifstream &f, string &str, int size) {
	str.clear();
	char ch;
	for (int i = 0; i < size; i++) {
		f.read(&ch, 1);
		str += ch;
	}
}

void read_string(std::ifstream &f, string &str) {
	str.clear();
	char ch;
	do {
		f.read(&ch, 1);
		str += ch;
	} while (ch);
}

void read_bytes(std::ifstream &f, char *arr, int size) {
	f.read(arr, size);
}

void print_chars(uint32_t n) {    // assumes little-endian
	std::cout << (char) (n >> 24) << (char) (n >> 16 & 0xff)
			<< (char) (n >> 8 & 0xff) << (char) (n & 0xff);
}
