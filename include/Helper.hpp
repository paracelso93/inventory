#pragma once

#include <iostream>


#define LOG(x, str) if (!x) { \
	std::cout << "Error, " << str << " failed." << std::endl; \
	return false; \
	} \
	
static inline bool pointInRectangleF(float point_x, float point_y, float pos_x, float pos_y, float size_x, float size_y) {
	return (point_x >= pos_x && point_x <= pos_x + size_x && point_y >= pos_y && point_y <= pos_y + size_y);
}

static inline bool pointInRectangleI(int point_x, int point_y, int pos_x, int pos_y, int size_x, int size_y) {
	return (point_x >= pos_x && point_x <= pos_x + size_x && point_y >= pos_y && point_y <= pos_y + size_y);
}
