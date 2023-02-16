#include <string>
#include <cstring>

#include "canvas.h"
#include "renderer.h"

namespace luna {
    class Program {
        Canvas _mainCanvas;

        u32 _screen_width;
        u32 _screen_height;

        public: 
            Program(u32 width, u32 height) {
                _mainCanvas = Canvas(width, height);
                _mainCanvas.initData();

                _screen_width = width;
                _screen_height = height;
            }

            void Render(u32* target) {
                Renderer::fillCanvas(&_mainCanvas, 0xAABBCCFF);

                //Copying canvas to target bitmap texture
                memcpy(target, _mainCanvas.getData(), _screen_width*_screen_height*sizeof(u32));
            }

            void Update() {
                
            }
    };
}
