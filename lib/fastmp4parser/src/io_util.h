#ifndef IO_UTIL_H_
#define IO_UTIL_H_

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using std::string;

void pt(int level);

void flip_endian(uint32_t &val);

void flip_endian(uint64_t &val);

void reverse_bytes(char *start, int size);

uint64_t read_uint64(std::ifstream &f);

uint32_t read_uint32(std::ifstream &f);

uint16_t read_uint16(std::ifstream &f);

void read_string(std::ifstream &f, string &str, int size);

void read_string(std::ifstream &f, string &str);

void read_bytes(std::ifstream &f, char *arr, int size);

void print_chars(uint32_t n);

#endif /* IO_UTIL_H_ */
