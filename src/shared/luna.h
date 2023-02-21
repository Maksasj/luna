#include "rendering\renderer.h"

#include "events\event_manager.h"

#include "editor\editor.h"

#include "utils\logger.h"

namespace luna {
    class Program {
        Canvas _mainCanvas;

        Editor editor;

        u32 _screen_width;
        u32 _screen_height;

        f32 mousePosX = 0;
        f32 mousePosY = 0;

        public: 
            Program();
            
            Program(u32 width, u32 height);

            void Render(u32* target);
            
            void Update();
    };
}
