#include <string>
#include <cstring>

#include "canvas.h"
#include "rectangle.h"

namespace luna {
    struct Renderer {
        static void fillCanvas(Canvas *canvas, u32 color);

        static void fillRect(Canvas *canvas, i32 x0, i32 y0, u32 width, u32 height, u32 color);
        
        static void lineRect(Canvas *canvas, i32 x0, i32 y0, u32 width, u32 height, u32 color);

        static void fillCircle(Canvas *canvas, i32 x0, i32 y0, u32 radius, u32 color);
    };
}
