#include <string.h>
#include "../box_util.hpp"
#include "boxes.hpp"

void MediaHandlerBox::parse(std::ifstream &f, int box_end, int level) {
    pre_defined = read_uint32(f);
    read_string(f, handler_type, 4);
    read_string(f, handler_subtype, 4);
    read_bytes(f, reserved, sizeof(reserved));
    read_string(f, name);
    props["handler_subtype"] = handler_subtype;
}

void MediaHandlerBox::print(int l) {
    pt(l);
    printf("- pre_defined=%d\n", pre_defined);
    pt(l);
    printf("- handler_subtype=%.4s\n", handler_subtype.c_str());
    pt(l);
    printf("- name=%s\n", name.c_str());
}

void MediaHeaderBox::parse(std::ifstream &f, int box_end, int level) {
}

Box *MediaInfoBox::add_child(std::ifstream &f, Box &copy_box) {
    Box *child = NULL;
    if (!std::strncmp("stbl", copy_box.type, 4)) {
        child = new SampleTableBox(copy_box);
    }
    return child;
}

Box *MediaBox::add_child(std::ifstream &f, Box &copy_box) {
    Box *child = NULL;
    if (!std::strncmp("mdhd", copy_box.type, 4)) {
        child = new MediaHeaderBox(copy_box);
    } else if (!std::strncmp("minf", copy_box.type, 4)) {
        child = new MediaInfoBox(copy_box);
    } else if (!std::strncmp("hdlr", copy_box.type, 4)) {
        child = new MediaHandlerBox(copy_box);
    }
    return child;
}