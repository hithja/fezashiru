#include <functional>
#include <unordered_map>
#include <vector>
#include <string>
#include "core/Events.hpp"

std::unordered_map<EventType, std::vector<Events::Callback>> Events::listeners;

Events::Events() {

}

void Events::subscribe(EventType type, Callback cb) {
    listeners[type].push_back(cb);
}

void Events::emit(EventType type, std::string status) {
    for (std::function<void()>& cb : listeners[type])
        cb();
}