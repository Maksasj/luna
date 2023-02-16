#ifndef _LUNA_CANVAS_H_
#define _LUNA_CANVAS_H_

#include <iostream>

#include "types.h"

namespace luna {
    class Canvas {
        private:
            u32 *_data;
            u32 _width;
            u32 _height;

        public:
            Canvas() {
                _width = 0;
                _height = 0;
                _data = NULL;
            }

            Canvas(u32 width, u32 height) {
                _width = width;
                _height = height;
                _data = NULL;
            }

            ~Canvas() {
                delete _data;
            }

            void initData() {
                _data = new u32[_width*_height]();
            }

            void setData(u32 *data) {
                _data = data;
            } 

            u32 getWidth() {
                return _width;
            }

            u32* getData() {
                return _data;
            }

            u32 getHeight() {
                return _height;
            }
    };
    
}

#endif
