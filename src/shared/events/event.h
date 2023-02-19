#include <vector>

#include "utils\types.h"

#include "utils\logger.h"

namespace luna {
    enum EventType {
        LUNA_TOUCH_EVENT,
        LUNA_TOUCH_RELEASE_EVENT,
        LUNA_TOUCH_MOTION_EVENT,

        LUNA_QUIT_EVENT,
    };

    struct TouchEvent
    {
        EventType eventType;
        i32 x0;
        i32 y0;
    };

    struct TouchRreleaseEvent
    {
        EventType eventType;
        i32 x0;
        i32 y0;
    };

    struct TouchMotionEvent
    {
        EventType eventType;
        i32 x0;
        i32 y0;
    };
    
    struct QuitEvent
    {
        EventType eventType;
    };

    union Event {
        EventType eventType;
        TouchEvent touchEvent;
        TouchRreleaseEvent touchReleaseEvent;
        TouchMotionEvent touchMotionEvent;
    };
}
