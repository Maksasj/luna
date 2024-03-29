#include "luna.h"

luna::Program::Program() {
    _mainCanvas = Canvas(800, 600);
    editor = Editor(400, 400);

    _screen_width = 800;
    _screen_height = 600;

    LUNA_LOG("[INFO][PROGRAM] Initialized program\n");
}

luna::Program::Program(u32 width, u32 height) {
    _mainCanvas = Canvas(width, height);
    _mainCanvas.initData();

    editor = Editor(400, 400);
    editor.canvas.initData();

    Renderer::fillCanvas(&editor.canvas, 0xFFFFAAAA);

    _screen_width = width;
    _screen_height = height;

    LUNA_LOG("[INFO][PROGRAM] Initialized program\n");
}

void luna::Program::Render(u32* target) {
    PROFILE_RECORD(RENDERING);
    
        PROFILE_RECORD(CANVAS_FILLING);
                Renderer::fillCanvas(&_mainCanvas, 0xFF222222);
        PROFILE_STOP(CANVAS_FILLING);

        PROFILE_RECORD(SUB_CANVAS_RENDERING);
            Renderer::drawCanvas(&_mainCanvas, &editor.canvas, ((_screen_width) / 2)  - 200, ((_screen_height) / 2) - 200);
        PROFILE_STOP(SUB_CANVAS_RENDERING);

        PROFILE_RECORD(FINAL_MEMCPY);
            memcpy(target, _mainCanvas.getData(), _screen_width*_screen_height*sizeof(u32));
        PROFILE_STOP(FINAL_MEMCPY);

    PROFILE_STOP(RENDERING);
}

void luna::Program::Update() {
    PROFILE_RECORD(UPDATE);
    auto begin = std::chrono::high_resolution_clock::now();                                                                                                                                     
    
    static bool isHolding = false;
    static i32 touchPosX = 0;
    static i32 touchPosY = 0;
    
    PROFILE_RECORD(EVENTS_MANAGEMENT);
    Event event;
    while(!EventManager::pullEvent(&event)) {
        switch (event.eventType) {
            case LUNA_QUIT_EVENT: {
                break;
            }
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
    PROFILE_STOP(EVENTS_MANAGEMENT);

    mousePosX = touchPosX;
    mousePosY = touchPosY;
    
    if(isHolding) {
        i32 mousePosXfromScreenCenter = mousePosX - (_screen_width / 2);
        i32 mousePosYfromScreenCenter = mousePosY - (_screen_height / 2);
        
        i32 editorRectXPos = _screen_width / 2;
        i32 editorRectYPos = _screen_height / 2;

        i32 editorRectWidth = editor.canvas.getWidth();
        i32 editorRectHeight = editor.canvas.getHeight();

        if((abs(mousePosXfromScreenCenter) < editorRectWidth / 2) &&
            abs(mousePosYfromScreenCenter) < editorRectHeight / 2) {
            
            i32 canvasPosX = mousePosXfromScreenCenter + (editorRectWidth / 2);
            i32 canvasPosY = mousePosYfromScreenCenter + (editorRectHeight / 2);

            luna::Renderer::fillCircle(&editor.canvas, canvasPosX, canvasPosY, 8, 0xFF111111);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();                                                                
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count(); 
    
    PROFILE_STOP(UPDATE);

    LUNA_LOG("[INFO][PROGRAM] Last update frame took: " + std::to_string(duration) + "ms \n");
}
