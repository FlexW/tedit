#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <map>
#include <list>

using namespace std;

typedef const string event_type;
typedef void (*handler)(event_type&, void*);

class event {
public:
    ~event();

    /**
     * Adds a event listener for the given event type.
     * @param e       Event type.
     * @param handler Function that should be called,
     *                if the event occurs.
     */
    void add_event_listner(event_type &e, handler h);

    /**
     * Removes the registered event handler.
     * @param e       Event type.
     * @param handler Function that should be removed.
     */
    void remove_event_listner(event_type &e, handler h);

    /**
     * Checks if event listener is registered for event.
     * @param e Event type.
     * @param h Address of event handler.
     * @returns True if registered, false if not.
     */
    bool is_registered(event_type &e, handler h);

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
    void dispatch_event(event_type &e, void *data);

private:
    map<event_type, list<handler>*> event_map;
};

#endif
