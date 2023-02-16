#ifndef _LUNA_TIMER_H_
#define _LUNA_TIMER_H_

#include "types.h"

#include <chrono>

namespace luna {
    struct Timer {
        static u64 tick;

        static void Init() {
            tick = 0;
        }
        
        static void Update() {
            tick += 1;
        }
    };
}


#endif