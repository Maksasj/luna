#include <vector>

#include "event.h"

#include "logger.h"

namespace luna {
    class EventManager {
        static std::vector<Event> events;

        public:
            static void pushEvent(Event event);

            static bool pullEvent(Event *event);
    };
}
