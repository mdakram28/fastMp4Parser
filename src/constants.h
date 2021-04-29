/*
 * constants.h
 *
 *  Created on: 29-Apr-2021
 *      Author: MAnsari15
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <vector>
#include <string>

std::vector<std::string> VIDEO_FORMATS = {
		"cvid",     //Cinepak
		"jpeg",     //JPEG
		"smc ",     //Graphics
		"rle ",     //Animation
		"rpza",     //Apple video
		"kpcd",     //Kodak Photo CD
		"png ",     //Portable Network Graphics
		"mjpa",     //Motion-JPEG (format A)
		"mjpb",     //Motion-JPEG (format B)
		"SVQ1",     //Sorenson video, version 1
		"SVQ3",     //Sorenson video 3
		"mp4v",     //MPEG-4 video
		"avc1",     //H.264 video
		"dvc ",     //NTSC DV-25 video
		"dvcp",     //PAL DV-25 video
		"gif ",     //CompuServe Graphics Interchange Format
		"h263",     //H.263 video
		"tiff",     //Tagged Image File Format
		"raw ",     //Uncompressed RGB
		"2vuY",     //Uncompressed Y퀰bCr, 8-bit-per-component 4:2:2
		"yuv2",     //Uncompressed Y퀰bCr, 8-bit-per-component 4:2:2
		"v308",     //Uncompressed Y퀰bCr, 8-bit-per-component 4:4:4
		"v408",     //Uncompressed Y퀰bCr, 8-bit-per-component 4:4:4:4
		"v216",     //Uncompressed Y퀰bCr, 10, 12, 14, or 16-bit-per-component 4:2:2
		"v410",     //Uncompressed Y퀰bCr, 10-bit-per-component 4:4:4
		"v210",     //Uncompressed Y퀰bCr, 10-bit-per-component 4:2:2
};

inline bool is_video_format(string &str) {
	return std::find(VIDEO_FORMATS.begin(), VIDEO_FORMATS.end(), str)
			!= VIDEO_FORMATS.end();
}

#endif /* CONSTANTS_H_ */
