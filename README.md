# Fast MP4 Parsing
The contents of mp4 files are parsed and the consolidated stats are printed at the end.

## Build
```
$ g++ -o Debug/fastMp4 src/main.cpp
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


----------MP4 Parse (data\\sample-mp4-file.mp4)------------
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
                                        stco 7576
        udta 96


----------MP4 Info------------
Duration: 00:02:5.952
creation_time: Thu Jan 01 05:30:00 1970
modification_time: Sat Jul 19 23:13:01 2014
Bitrate: 669.88 kb/s
Total Filesize: 10546620 bytes
Track #1:
        Format: avc1    size=320x240
        Frame Rate: 15.00

Total mdat boxes: 2Track #2:
        Format: mp4a    sample_rate=131088
        Frame Rate: 46.88

Total mdat boxes: 2
```

## References
1. ISO/IEC 14496-12: https://b.goeswhere.com/ISO_IEC_14496-12_2015.pdf
2. MP4Box: Used for generating fragments. https://github.com/gpac/gpac/wiki/MP4Box