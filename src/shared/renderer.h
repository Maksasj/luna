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

        static void fillRect(Canvas *canvas, u32 x0, u32 y0, u32 width, u32 height, u32 color) {
            u32* canvasData = canvas->getData();
            u32 canvasWidth = canvas->getWidth();
            u32 canvasHeight = canvas->getHeight();

            for(int y = y0; y < y0 + height; ++y) {
                if(y > canvasHeight) continue;
            
                for(int x = x0; x < x0 + width; ++x) {
                    if(x > canvasWidth) continue;

                    canvasData[y * canvasWidth + x] = color;
                }
            }
        } 
    };
}
