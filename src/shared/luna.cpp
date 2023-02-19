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
    
    static u64 tick = 0;
    tick += 1;
    static i32 posX = 0;
    static i32 posY = 0;
    
    posX = 300.0*sin(tick / 100.0);
    posY = 300.0*cos(tick / 100.0);
    
    Renderer::fillRect(&_mainCanvas, 360 + 50.0*sin(tick / 10.0), 260 + 50.0*cos(tick / 10.0), 80, 80, 0xFF00FF00);
    Renderer::fillRect(&_mainCanvas, 400, 400 - 40 - posX, 80, 80, 0xFF00FFFF);

    Renderer::lineRect(&_mainCanvas, 300 + 50.0*sin(tick / 10.0), 200 - 50.0*cos(tick / 10.0), 100, 100, 0xFF0000FF);
    Renderer::lineRect(&_mainCanvas, 400 - 40 + posX, 200, 100, 100, 0xFF0000FF);

    Renderer::lineRect(&_mainCanvas, rect2PosX - 25, rect2PosY - 25, 50, 50, 0xFFFFFFFF);
    Renderer::fillRect(&_mainCanvas, rect2PosX - 5, rect2PosY - 5, 10, 10, 0xFFFFFFFF);

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
            case LUNA_TOUCH_EVENT: {
                LUNA_LOG("[INFO][PROGRAM][EVENT_MANAGER] Executing TOUCH_EVENT event\n");
                isHolding = true;
                touchPosX = event.touchEvent.x0;
                touchPosY = event.touchEvent.y0;
                break;
            }
            case LUNA_TOUCH_RELEASE_EVENT: {
                LUNA_LOG("[INFO][PROGRAM][EVENT_MANAGER] Executing TOUCH_RELEASE_EVENT event\n");
                isHolding = false;
                break;
            }
            case LUNA_TOUCH_MOTION_EVENT: {
                LUNA_LOG("[INFO][PROGRAM][EVENT_MANAGER] Executing TOUCH_MOTION_EVENT event\n");
                touchPosX = event.touchReleaseEvent.x0;
                touchPosY = event.touchReleaseEvent.y0;
                break;
            }
        }
    }

    if(isHolding) {
        rect2PosX = touchPosX;
        rect2PosY = touchPosY;
    }

    auto end = std::chrono::high_resolution_clock::now();                                                                
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count(); 
    
    LUNA_LOG("[INFO][PROGRAM] Last update frame took: " + std::to_string(duration) + "ms \n");
}
