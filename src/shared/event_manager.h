#include <vector>

#include "event.h"

#include "logger.h"

namespace luna {
    class EventManager {
        typedef std::vector<Event> eV;
        typedef eV::iterator eVIter;

        static eV events;

        public:
            static void pushEvent(Event event) {
                LUNA_LOG("[INFO][PROGRAM][EVENT_MANAGER] Pused event to event pool\n");
                events.push_back(event);
            }

            static bool pullEvent(Event *event) {
                if(events.empty()) return true;

                (*event) = events[events.size() - 1];
                events.pop_back();

                return false;
            }
    };
}

// TODO: move this to separate cpp file
std::vector<luna::Event> luna::EventManager::events;
