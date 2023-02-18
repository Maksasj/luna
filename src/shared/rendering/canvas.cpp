#include "canvas.h"

luna::Canvas::Canvas() {
    _width = 0;
    _height = 0;
    _data = NULL;
}

luna::Canvas::Canvas(u32 width, u32 height) {
    _width = width;
    _height = height;
    _data = NULL;
}

luna::Canvas::~Canvas() {
    delete _data;
}

void luna::Canvas::initData() {
    _data = new u32[_width*_height]();
}

void luna::Canvas::setData(u32 *data) {
    _data = data;
} 

u32 luna::Canvas::getWidth() {
    return _width;
}

u32* luna::Canvas::getData() {
    return _data;
}

u32 luna::Canvas::getHeight() {
    return _height;
}
