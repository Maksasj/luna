#include "renderer.h"

void luna::Renderer::fillCanvas(Canvas *canvas, u32 color) {
    u32* canvasData = canvas->getData();
    u32 canvasWidth = canvas->getWidth();
    u32 canvasHeight = canvas->getHeight();

    for(int i = 0; i < canvasWidth * canvasHeight; ++i) {
        canvasData[i] = color;
    }
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

        if(x1 == x2 + (i32) width)
            canvasData[y * canvasWidth + x1] = color;
    }

    for(i32 x = x0; x <= x1; ++x) {
        if(y0 == y2)
            canvasData[y0 * canvasWidth + x] = color;

        if(y1 == y2 + (i32) height)
            canvasData[y1 * canvasWidth + x] = color;
    }
} 

void luna::Renderer::fillCircle(Canvas *canvas, i32 x0, i32 y0, u32 radius, u32 color) {
    u32* canvasData = canvas->getData();
    u32 canvasWidth = canvas->getWidth();
    u32 canvasHeight = canvas->getHeight();

    i32 x1 = x0 + radius*2;
    i32 y1 = y0 + radius*2;

    luna::Rectangle::normalize(&x0, &y0, &x1, &y1, canvasWidth, canvasHeight);

    i32 xc = x0 + (radius / 2);
    i32 yc = y0 + (radius / 2);

    for(i32 y = 0; y < y1; ++y) {
        for(i32 x = 0; x < x1; ++x) {
            i32 dx = xc - x;
            i32 dy = yc - y;
            
            if(dx*dx + dy*dy < (i32)(radius*radius))
                canvasData[y * canvasWidth + x] = color;
        }
    }
}

void luna::Renderer::drawCanvas(Canvas *target, Canvas *source, i32 x0, i32 y0) {
    u32* targetData = target->getData();
    u32 targetWidth = target->getWidth();
    u32 targetHeight = target->getHeight();

    u32* sourceData = source->getData();
    u32 sourceWidth = source->getWidth();
    u32 sourceHeight = source->getHeight();

    i32 x1 = x0 + sourceWidth;
    i32 y1 = y0 + sourceHeight;

    luna::Rectangle::normalize(&x0, &y0, &x1, &y1, targetWidth, targetHeight);

    for(i32 y = y0; y < y1; ++y) {
        for(i32 x = x0; x < x1; ++x) {
            targetData[y * targetWidth + x] = sourceData[(y-y0) * sourceWidth + (x-x0)];
        }
    }
}
