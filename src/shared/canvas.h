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
            Canvas();

            Canvas(u32 width, u32 height);

            ~Canvas();

            void initData();

            void setData(u32 *data);

            u32 getWidth();

            u32* getData();

            u32 getHeight();
    };
    
}

#endif
