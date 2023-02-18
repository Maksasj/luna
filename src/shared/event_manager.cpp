#include "event_manager.h"

std::vector<luna::Event> luna::EventManager::events;

void luna::EventManager::pushEvent(luna::Event event) {
    LUNA_LOG("[INFO][PROGRAM][EVENT_MANAGER] Pushed event to event pool\n");
    
    events.push_back(event);
}

bool luna::EventManager::pullEvent(luna::Event *event) {
    if(events.empty()) return true;

    (*event) = events[events.size() - 1];
    events.pop_back();

    return false;
}
