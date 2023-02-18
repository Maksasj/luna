#include <string>
#include <cstring>

#include "canvas.h"

namespace luna {
    struct Renderer {
        static void fillCanvas(Canvas *canvas, u32 color);

        static void fillRect(Canvas *canvas, u32 x0, u32 y0, u32 width, u32 height, u32 color);
    };
}
