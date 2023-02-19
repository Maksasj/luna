#ifndef _LUNA_RECTANGLE_H_
#define _LUNA_RECTANGLE_H_

#include <iostream>

#include "utils\types.h"

namespace luna {
    struct Rectangle {
        static void normalize(i32 *x0, i32 *y0, i32 *x1, i32 *y1, u32 maxWidth, u32 maxHeight) {
            if((*x0) < 0) (*x0) = 0;
            if((*y0) < 0) (*y0) = 0;

            if((*x1) < 0) (*x1) = 0;
            if((*y1) < 0) (*y1) = 0;

            if((*x0) >= (i32) maxWidth)   (*x0) = maxWidth - 1;
            if((*y0) >= (i32) maxHeight)  (*y0) = maxHeight - 1;

            if((*x1) >= (i32) maxWidth)   (*x1) = maxWidth - 1;
            if((*y1) >= (i32) maxHeight)  (*y1) = maxHeight - 1;
        }
    };
}

#endif
