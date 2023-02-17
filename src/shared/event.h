#include <vector>

#include "types.h"

#include "logger.h"

namespace luna {
    enum EventType {
        TOUCH_EVENT,
        TOUCH_RELEASE_EVENT,
        TOUCH_MOTION_EVENT
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
    
    union Event {
        EventType eventType;
        TouchEvent touchEvent;
        TouchRreleaseEvent touchReleaseEvent;
        TouchMotionEvent touchMotionEvent;
    };
}
