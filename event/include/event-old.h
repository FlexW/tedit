#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <map>
#include <list>
#include <thread>

using namespace std;

typedef const string event_type;

template <typename T>
using handler = void(*)(event_type&, T);

//typedef void (*handler)(event_type&, void *data);

class event {
public:
    ~event();

    /**
     * Adds a event listener for the given event type.
     * @param e       Event type.
     * @param handler Function that should be called,
     *                if the event occurs.
     */
     template <typename T>
     inline void add_event_listner(event_type &e, handler<T> h) {
         auto iter = event_map.find(e);
         if (iter == event_map.end()) {
             list<handler<T>> *l = new list<handler<T>>;
             l->push_back(h);
             event_map.insert(pair<event_type, list<handler<T>>*>(e, l));
             return;
         }
         iter->second->push_back(h);
     }

    /**
     * Removes the registered event handler.
     * @param e       Event type.
     * @param handler Function that should be removed.
     */
    template<typename T>
    inline void remove_event_listner(event_type &e, handler<T> h) {
        auto iter = event_map.find(e);
        if (iter != event_map.end()) {
                delete iter->second;
                event_map.erase(iter);
        }
    }

    /**
     * Checks if event listener is registered for event.
     * @param e Event type.
     * @param h Address of event handler.
     * @returns True if registered, false if not.
     */
     bool is_registered(event_type &e, handler<T> h);

    /**
     * Counts the number of registered listeners.
     * @returns Number of listener.
     */
    int num_listener(event_type &e);

protected:
    /**
     * Fires a event. Calls all registered event handler.
     * @param e    Event type.
     * @param data Data that may gets send with the event.
     */
    template <typename T>
    inline void dispatch_event(event_type &e, T data) {
            auto iter = event_map.find(e);
            if (iter != event_map.end()) {
                    for (auto f : *iter->second) {
                            //       thread t(f, e, data);
                            f(e, data);
                            //t.detach();
                    }
            }
    }

private:
    map<event_type, list<handler<int>>*> event_map;
};

#endif
