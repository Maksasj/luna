#include <string>
#include <cstring>

#include "canvas.h"
#include "renderer.h"

#include "event_manager.h"

#include "logger.h"

namespace luna {
    class Program {
        Canvas _mainCanvas;

        u32 _screen_width;
        u32 _screen_height;

        f32 rect2PosX = 0;
        f32 rect2PosY = 0;

        public: 
            Program(u32 width, u32 height);

            void Render(u32* target);
            
            void Update();
    };
}
