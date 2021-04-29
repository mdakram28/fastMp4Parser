/*
 * media_data_box.h
 *
 *  Created on: 30-Apr-2021
 *      Author: MAnsari15
 */

#ifndef BOXES_MEDIA_DATA_BOX_H_
#define BOXES_MEDIA_DATA_BOX_H_

#include "../box_util.h"

class MediaDataBox: public Box {
public:
	MediaDataBox(Box &box) :
			Box(box) {
	}

	virtual void parse(std::ifstream &f, int box_end, int level) {
	}

};

#endif /* BOXES_MEDIA_DATA_BOX_H_ */
