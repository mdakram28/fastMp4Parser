# Fast MP4 Parsing
Tool to parse MP4 ISOBMFF container (or container parts) and print the box header contents.

## Folder structure
The contents of mp4 files are parsed and the consolidated stats are printed at the end.
```
|
|--Data                                         # Input video files
|  |--sample-mp4-file.mp4                       # Sample input 1
|  |--file_example_MP4_480_1_5MG.mp4            # Sample input 2
|  |--segment                                   
|     |-_fileinit.mp4                           # fmp4 init
|     |-_file1.m4s                              # fmp4 segments 1-5
|     |-_file2.m4s
|     |-_file3.m4s
|     |-_file4.m4s
|     |-_file5.m4s
|--src                                          # Source Code
|  |--main.cpp                                  # Entry Point
|  |--box_util.cpp                              # Box util impl
|  |--box_util.hpp                              # Box util include
|  |--io_util.cpp                               # IO util impl
|  |--io_util.hpp                               # IO util include
|  |--boxes                                     # ISO 14486 format mp4 boxes parsing logic
|     |--box.hpp                                # ftyp
|     |--box_movie.cpp                          # moov, mvhd
|     |--box_media_data.cpp                     # mdat
|     |--box_track.cpp                          # trak, tkhd
|     |--box_media.cpp                          # mdia, minf, mdhd, hdlr
|     |--box_sample_table.cpp                   # stbl, stsd
|     |--box_time_to_sample.cpp                 # stts
|     |--box_sample_size.cpp                    # stsz, stz2
|     |--box_video_sample_entry.cpp             # Video Sample Description Entry
|     |--box_audio_sample_entry.cpp             # Audio Sample Description Entry
|
.
.
```


## Build (UNIX)
```
$ mkdir build && cd build
$ cmake ../
$ cmake --build .
```

## Run
Command: ```fastMp4 [list_of_files]```

Example for MP4 file
```
$ Debug/fastMp4 data/sample-mp4-file.mp4
```

Example for fragmented MP4 files
```
$ Debug/fastMp4 data/segment/_fileinit.mp4 data/segment/_file1.m4s data/segment/_file2.m4s data/segment/_file3.m4s data/segment/_file4.m4s data/segment/_file5.m4s
```

### Sample Output
Input File: data/sample-mp4-file.mp4
```
----------MP4 Parse (data\sample-mp4-file.mp4)------------
ftyp 32
- major_brand='isom'
- minor_version='512'
- compatible_brands='isomiso2avc1mp41'
free 8
mdat 10493268
mdat 8
moov 53304
	mvhd 108
	- creation_time=Thu Jan 01 05:30:00 1970
	- modification_time=Sat Jul 19 23:13:01 2014
	- timescale=1000
	- duration=125952
	- rate= 1.000000
	- volume= 1.000000
	trak 15760
		tkhd 92
		- creation_time=Thu Jan 01 05:30:00 1970
		- modification_time=Thu Jan 01 05:30:00 1970
		edts 36
		mdia 15624
			mdhd 32
			hdlr 45
			- pre_defined=0
			- handler_subtype=vide
			- name=VideoHandler
			minf 15539
				vmhd 20
				dinf 36
				stbl 15475
					stsd 147
						avc1 131
						- index=1
						- vendor=0
						- width=320
						- height=240
					stts 24
					- sample_count=1889, sample_delta=1024
					stss 120
					stsc 28
					stsz 7576
					- total_samples_size=4452108
					stco 7572
	trak 37332
		tkhd 92
		- creation_time=Thu Jan 01 05:30:00 1970
		- modification_time=Thu Jan 01 05:30:00 1970
		edts 36
		mdia 37196
			mdhd 32
			hdlr 45
			- pre_defined=0
			- handler_subtype=soun
			- name=SoundHandler
			minf 37111
				smhd 16
				dinf 36
				stbl 37051
					stsd 103
						mp4a 87
						- channel_count=0
						- sample_size=0
						- pre_defined=0
						- sample_rate=131088
					stts 24
					- sample_count=5904, sample_delta=1024
					stsc 5704
					stsz 23636
					- total_samples_size=6041152
					stco 7576
	udta 96


----------MP4 Info------------
Duration: 00:02:5.952
creation_time: Thu Jan 01 05:30:00 1970
modification_time: Sat Jul 19 23:13:01 2014
Bitrate: 669.88 kb/s
Total Filesize: 10546620 bytes
Track #1: 
	Format: avc1 (video)
	Frame Dimensions: 320x240
	Frame Rate: 14
	Bitrate: 282 kb/s
Track #2: 
	Format: mp4a (audio)
	Sample Rate: 131088
	Frame Rate: 46
	Bitrate: 383 kb/s
Total mdat boxes: 2

```

## References
1. ISO/IEC 14496-12: https://b.goeswhere.com/ISO_IEC_14496-12_2015.pdf
2. MP4Box: Used for generating fragments. https://github.com/gpac/gpac/wiki/MP4Box
