#ifndef _LUNA_EDITOR_H_
#define _LUNA_EDITOR_H_

#include "utils/logger.h"

#include "utils/types.h"

#include "rendering/canvas.h"

namespace luna {
    class Editor {
        public:
        Canvas canvas;
        
        Editor() {
            canvas = Canvas();
        }

        Editor(u32 width, u32 height) {
            canvas = Canvas(width, height);

            LUNA_LOG("[INFO][PROGRAM] Initialized editor\n");
        }
    };
}

#endif