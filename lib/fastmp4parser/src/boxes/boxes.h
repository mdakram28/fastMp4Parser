#ifndef FASTMP4_BOXES_H
#define FASTMP4_BOXES_H

#include <fstream>
#include <algorithm>
#include <cstring>
#include "../io_util.h"
#include "../box_util.h"

class VideoSampleEntry: public Box {
public:
    char reserved[6];
    uint16_t data_reference_index;

    uint16_t version;
    uint16_t revision_level;
    uint32_t vendor;
    uint32_t temporal_quality;
    uint32_t spatial_quality;
    uint16_t width;
    uint16_t height;

    VideoSampleEntry(Box &box): Box(box) {}
    void print(int l);
    void parse(std::ifstream &f, int container_end, int level);
};

class AudioSampleEntry: public Box {
public:
    char reserved1[8];
    uint16_t channel_count;
    uint16_t sample_size;
    uint16_t pre_defined;
    char reserved2[2];
    uint32_t sample_rate;

    AudioSampleEntry(Box &box) : Box(box) {}
    void print(int l);
    void parse(std::ifstream &f, int container_end, int level);
};

struct TimeToSampleBoxEntry {
    uint32_t sample_count;
    uint32_t sample_delta;
};

class TimeToSampleBox: public Box {
public:
    char version;			// 1 byte
    char flags[3];			// 3 bytes
    int entry_count;
    std::vector<TimeToSampleBoxEntry> entries;

    int total_sample_count = 0;

    TimeToSampleBox(Box &box) : Box(box) {}
    void print(int l);
    void parse(std::ifstream &f, int container_end, int level);
};

class SampleSizeBox: public Box {
public:
    char version;			// 1 byte
    char flags[3];			// 3 bytes

    uint32_t sample_size;
    uint32_t sample_count;
    std::vector<uint32_t> entries;

    uint64_t total_samples_size = 0;

    SampleSizeBox(Box &box) : Box(box) {}
    void print(int l);
    void parse(std::ifstream &f, int container_end, int level);
};

class SampleDescriptionBox: public Box {
public:
    char version;			// 1 byte
    char flags[3];			// 3 bytes

    uint32_t entry_count;	// 4 bytes

    SampleDescriptionBox(Box &box) : Box(box) {}
    void print(int l);
    void parse(std::ifstream &f, int container_end, int level);
};

class SampleTableBox: public ContainerBox {
public:
    SampleTableBox(Box &box) : ContainerBox(box) {}
    Box* add_child(std::ifstream &f, Box &copy_box);
};

class MediaDataBox: public Box {
public:
    MediaDataBox(Box &box) : Box(box) {}
    virtual void parse(std::ifstream &f, int box_end, int level) {}
};

class MediaBox: public ContainerBox {
public:
    MediaBox(Box &box) : ContainerBox(box) {}
    Box* add_child(std::ifstream &f, Box &copy_box);
};

class MediaInfoBox: public ContainerBox {
public:
    MediaInfoBox(Box &box) : ContainerBox(box) {}
    Box* add_child(std::ifstream &f, Box &copy_box);
};

class MediaHeaderBox: public Box {
public:
    MediaHeaderBox(Box &box) : Box(box) {}
    void parse(std::ifstream &f, int box_end, int level);
};

class MediaHandlerBox: public Box {
public:
    uint32_t pre_defined;
    string handler_type;		// 4 bytes
    string handler_subtype;
    char reserved[12];
    string name;

    MediaHandlerBox(Box &box) : Box(box) {}
    void parse(std::ifstream &f, int box_end, int level);
    void print(int l);
};

class TrackBox: public ContainerBox {
public:
    TrackBox(Box& box): ContainerBox(box) {}
    Box* add_child(std::ifstream &f, Box &copy_from);
};

class TrackHeaderBox: public Box {
public:
    char version;			// 1 byte
    char flags[3];			// 3 bytes

    time_t creation_time;		// 8 bytes
    time_t modification_time;	// 8 bytes

    TrackHeaderBox(Box& box): Box(box) {}
    void parse(std::ifstream &f, int box_end, int level);
    void print(int level);
};

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
    void parse(std::ifstream &f, int box_end, int level);
    void print(int l);
};

class MovieBox: public ContainerBox {
public:
    MovieBox(Box& box) : ContainerBox(box) {}
    Box* add_child(std::ifstream &f, Box &copy_from);
};


class FileTypeBox: public Box {
public:
	char major_brand[4];
	uint32_t minor_version;
	string compatible_brands;

	FileTypeBox(Box& box): Box(box) {}
	void parse(std::ifstream &f, int box_end, int level);
	void print(int l);
};

class MainBox: public ContainerBox {
public:
	MainBox(): ContainerBox() {}
	Box* add_child(std::ifstream &f, Box& copy_box);
};

#endif //FASTMP4_BOXES_H
