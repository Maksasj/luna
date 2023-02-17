#include <string>
#include <cstring>

#include "canvas.h"
#include "renderer.h"
#include "timer.h"

#include "logger.h"

namespace luna {
    class Program {
        Canvas _mainCanvas;

        u32 _screen_width;
        u32 _screen_height;

        f32 rect2OffsetX = 0;
        f32 rect2OffsetY = 0;

        public: 
            Program(u32 width, u32 height) {
                _mainCanvas = Canvas(width, height);
                _mainCanvas.initData();

                _screen_width = width;
                _screen_height = height;

                LUNA_LOG("[INFO][PROGRAM] Initialized program\n");
            }

            void Render(u32* target) {
                auto begin = std::chrono::high_resolution_clock::now();                                                                                                                                     
                
                Renderer::fillCanvas(&_mainCanvas, 0xFF000000);
                
                Renderer::fillRect(&_mainCanvas, (_screen_width - 250) / 2, (_screen_height - 250) / 2, 250, 250, 0xFFFF0000);
                
                Renderer::fillRect(&_mainCanvas, ((_screen_width - 250) / 2) + (i32) rect2OffsetX, ((_screen_height - 250) / 2) + (i32) rect2OffsetY, 80, 80, 0xFF0000FF);

                memcpy(target, _mainCanvas.getData(), _screen_width*_screen_height*sizeof(u32));

                auto end = std::chrono::high_resolution_clock::now();                                                                
                double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count(); 
                
                LUNA_LOG("[INFO][PROGRAM] Last render frame took: " + std::to_string(duration / 1000000.0) + "ms \n");
            }

            void Update() {
                auto begin = std::chrono::high_resolution_clock::now();                                                                                                                                     
                
                static u64 tick = 0;
                tick += 1;
                rect2OffsetX = 90.0*sin(tick / 100.0);
                rect2OffsetY = 90.0*cos(tick / 100.0);

                auto end = std::chrono::high_resolution_clock::now();                                                                
                double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count(); 
                
                LUNA_LOG("[INFO][PROGRAM] Last update frame took: " + std::to_string(duration) + "ms \n");
            }
    };
}
