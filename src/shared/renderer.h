#include <string>
#include <cstring>

#include "canvas.h"

namespace luna {
    struct Renderer {
        static void fillCanvas(Canvas *canvas, u32 color) {
            u32* canvasData = canvas->getData();
            u32 canvasWidth = canvas->getWidth();
            u32 canvasHeight = canvas->getHeight();

            for(int i = 0; i < canvasWidth*canvasHeight; ++i) {
                canvasData[i] = color;
            }
        }
    };
}
