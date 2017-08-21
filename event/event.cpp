#include <utility>
#include <thread>

#include "include/event.h"

event::~event() {
    for (auto iter : event_map) {
        auto l = iter.second;
        delete l;
    }
}

void event::add_event_listner(event_type &e, handler h) {
    auto iter = event_map.find(e);
    if (iter == event_map.end()) {
        list<handler> *l = new list<handler>;
        l->push_back(h);
        event_map.insert(pair<event_type, list<handler>*>(e, l));
        return;
    }
    iter->second->push_back(h);
}

void event::dispatch_event(event_type &e, void *data) {
    auto iter = event_map.find(e);
    if (iter != event_map.end()) {
        for (auto f : *iter->second) {
            thread t(f, e, data);
            t.detach();
        }
    }
}

void event::remove_event_listner(event_type &e, handler h) {
    auto iter = event_map.find(e);
    if (iter != event_map.end()) {
        delete iter->second;
        event_map.erase(iter);
    }
}

bool event::is_registered(event_type &e, handler h){
    auto iter = event_map.find(e);
    if (iter != event_map.end()) {
        for (auto f : *iter->second) {
            if (f == h)
                return true;
        }
    }
    return false;
}

int event::num_listener(event_type &e) {
    int cnt = 0;
    auto iter = event_map.find(e);
    if (iter != event_map.end()) {
        for (auto f : *iter->second) {
            cnt++;
        }
    }
    return cnt;
}