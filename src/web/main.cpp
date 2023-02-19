#include "luna.h"


u32 pixels[800*600];

int render() {
    luna::Program program(800, 600);

    program.Render(pixels);

    //memset(pixels, 0xFFBBBBBB, 800*600*sizeof(u32));

    return 69;
}