#include "luna.h"

luna::Program::Program(u32 width, u32 height) {
    _mainCanvas = Canvas(width, height);
    _mainCanvas.initData();

    _screen_width = width;
    _screen_height = height;

    LUNA_LOG("[INFO][PROGRAM] Initialized program\n");
}

void luna::Program::Render(u32* target) {
    auto begin = std::chrono::high_resolution_clock::now();                                                                                                                                     
    
    Renderer::fillCanvas(&_mainCanvas, 0xFF000000);
    
    Renderer::fillRect(&_mainCanvas, (_screen_width - 250) / 2, (_screen_height - 250) / 2, 250, 250, 0xFFFF0000);
    
    Renderer::fillRect(&_mainCanvas, rect2PosX, rect2PosY, 80, 80, 0xFF0000FF);

    memcpy(target, _mainCanvas.getData(), _screen_width*_screen_height*sizeof(u32));

    auto end = std::chrono::high_resolution_clock::now();                                                                
    double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count(); 
    
    LUNA_LOG("[INFO][PROGRAM] Last render frame took: " + std::to_string(duration / 1000000.0) + "ms \n");
}

void luna::Program::Update() {
    auto begin = std::chrono::high_resolution_clock::now();                                                                                                                                     
    
    static bool isHolding = false;
    static i32 touchPosX = 0;
    static i32 touchPosY = 0;

    Event event;
    while(!EventManager::pullEvent(&event)) {
        switch (event.eventType) {
            case TOUCH_EVENT: {
                LUNA_LOG("[INFO][PROGRAM][EVENT_MANAGER] Executing TOUCH_EVENT event\n");
                isHolding = true;
                touchPosX = event.touchEvent.x0;
                touchPosY = event.touchEvent.y0;
                break;
            }
            case TOUCH_RELEASE_EVENT: {
                LUNA_LOG("[INFO][PROGRAM][EVENT_MANAGER] Executing TOUCH_RELEASE_EVENT event\n");
                isHolding = false;
                break;
            }
            case TOUCH_MOTION_EVENT: {
                LUNA_LOG("[INFO][PROGRAM][EVENT_MANAGER] Executing TOUCH_MOTION_EVENT event\n");
                touchPosX = event.touchReleaseEvent.x0;
                touchPosY = event.touchReleaseEvent.y0;
                break;
            }
        }
    }

    if(isHolding) {
        rect2PosX = touchPosX - 40;
        rect2PosY = touchPosY - 40;
    }

    auto end = std::chrono::high_resolution_clock::now();                                                                
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count(); 
    
    LUNA_LOG("[INFO][PROGRAM] Last update frame took: " + std::to_string(duration) + "ms \n");
}
