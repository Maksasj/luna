#include "renderer.h"

void luna::Renderer::fillCanvas(Canvas *canvas, u32 color) {
    u32* canvasData = canvas->getData();
    u32 canvasWidth = canvas->getWidth();
    u32 canvasHeight = canvas->getHeight();

    memset(canvasData, color, canvasWidth*canvasHeight*sizeof(u32));
}

void luna::Renderer::fillRect(Canvas *canvas, i32 x0, i32 y0, u32 width, u32 height, u32 color) {
    u32* canvasData = canvas->getData();
    u32 canvasWidth = canvas->getWidth();
    u32 canvasHeight = canvas->getHeight();

    i32 x1 = x0 + width;
    i32 y1 = y0 + height;

    luna::Rectangle::normalize(&x0, &y0, &x1, &y1, canvasWidth, canvasHeight);

    for(i32 y = y0; y < y1; ++y) {
        for(i32 x = x0; x < x1; ++x) {
            canvasData[y * canvasWidth + x] = color;
        }
    }
} 

void luna::Renderer::lineRect(Canvas *canvas, i32 x0, i32 y0, u32 width, u32 height, u32 color) {
    u32* canvasData = canvas->getData();
    u32 canvasWidth = canvas->getWidth();
    u32 canvasHeight = canvas->getHeight();

    i32 x2 = x0;
    i32 y2 = y0;

    i32 x1 = x0 + width;
    i32 y1 = y0 + height;

    luna::Rectangle::normalize(&x0, &y0, &x1, &y1, canvasWidth, canvasHeight);

    for(i32 y = y0; y <= y1; ++y) {
        if(x0 == x2)
            canvasData[y * canvasWidth + x0] = color;

        if(x1 == x2 + width)
            canvasData[y * canvasWidth + x1] = color;
    }

    for(i32 x = x0; x <= x1; ++x) {
        if(y0 == y2)
            canvasData[y0 * canvasWidth + x] = color;

        if(y1 == y2 + height)
            canvasData[y1 * canvasWidth + x] = color;
    }
} 
