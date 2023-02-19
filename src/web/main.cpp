#include "luna.h"

u32 pixels[800*600];

void render() {
    luna::Program program(800, 600);
  
    program.Render(pixels);

    //for(int i = 0; i < 480; ++i) {
    //   pixels[i] = program._mainCanvas._data[i];
    //}
}

int pog() {
    return 0;
}
