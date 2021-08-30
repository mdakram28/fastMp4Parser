//============================================================================
// Name        : main.cpp
// Author      : Akram Ansari
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <fstream>
#include <string>
#include <filesystem>
#include "boxes/box.h"

using std::string;

void parse(string filename, Box *mp4box) {
	printf("\n\n----------MP4 Parse (%s)------------\n", filename.c_str());
	std::ifstream f(filename, f.in | f.binary);
	if (!f) {
		std::cerr << "Cannot open file.\n";
	} else {
		mp4box->parse(f, INT_MAX, 0);
		f.close();
	}
}

void mp4_stats(unsigned long long total_file_size, Box *mp4box) {

	printf("\n\n----------MP4 Info------------\n");
	MovieHeaderBox *mvhd_box =
			dynamic_cast<MovieHeaderBox*>(mp4box->get("moov")->get("mvhd"));

	double d = double(mvhd_box->duration) / mvhd_box->timescale;
	int hours = d / 3600;
	int minutes = (d - hours * 3600) / 60;
	double seconds = d - hours * 3600 - minutes * 60;
	printf("Duration: %.2d:%.2d:%2.3f\n", hours, minutes, seconds);
	printf("creation_time: %s", asctime(localtime(&mvhd_box->creation_time)));
	printf("modification_time: %s",
			asctime(localtime(&mvhd_box->modification_time)));
	if (d > 0) {
		printf("Bitrate: %.2f kb/s\n", (total_file_size / d) * 8.0 / 1000);
	}
	printf("Total Filesize: %llu bytes\n", total_file_size);

	std::vector<Box*> track_boxes = mp4box->get("moov")->getv("trak");
	for (int t = 1; t <= track_boxes.size(); t++) {
		printf("Track #%d: \n", t);

		std::vector<Box*> stsdEntries = track_boxes[t - 1]->get("mdia")->get(
				"minf")->get("stbl")->get("stsd")->getv();
		for (Box *entry : stsdEntries) {
			printf("\tFormat: %.4s", entry->type);
			string type_str(entry->type, entry->type + 4);
			string format = track_boxes[t - 1]->get("mdia")->get("hdlr")->getp(
					"handler_subtype");
			if (format == "vide") {
				VideoSampleEntry *vsd = dynamic_cast<VideoSampleEntry*>(entry);
				printf(" (video)\n\tFrame Dimensions: %dx%d", vsd->width, vsd->height);
			} else if (format == "soun") {
				AudioSampleEntry *asd = dynamic_cast<AudioSampleEntry*>(entry);
				printf(" (audio)\n\tSample Rate: %u", asd->sample_rate);
			}
			printf("\n");
		}

		TimeToSampleBox *stts_box = dynamic_cast<TimeToSampleBox*>(track_boxes[t
				- 1]->get("mdia")->get("minf")->get("stbl")->get("stts"));
		if (d > 0) {
			printf("\tFrame Rate: %d\n", (int) (stts_box->total_sample_count / d));
		}

		SampleSizeBox *stsz_box = dynamic_cast<SampleSizeBox*>(track_boxes[t
				- 1]->get("mdia")->get("minf")->get("stbl")->get("stsz"));
		if (d > 0) {
			printf("\tBitrate: %d kb/s\n", (int)(stsz_box->total_samples_size *8.0/ (d*1000)));
		}

	}
	printf("Total mdat boxes: %lu\n", mp4box->getv("mdat").size());
}

int main(int argc, char **argv) {

	// Print usage instructions if no arguments are passed
	if (argc < 2) {
		printf("Usage: fastMp4 [list_of_files]\n");
		return 0;
	}

	MainBox *mp4box = new MainBox();
	size_t total_file_size = 0;

	for (int i = 1; i < argc; i++) {
		parse(argv[i], mp4box);

		std::ifstream f(argv[i], f.in | f.binary);
		f.seekg(0, std::ios::end);
		total_file_size += f.tellg();
		f.close();
	}

	mp4_stats(total_file_size, mp4box);
}
