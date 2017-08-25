#ifndef EVENT_H_
#define EVENT_H_

#include <iostream>
#include <memory>
#include <utility>
#include <vector>
#include <thread>

/**
 * Implements an event handling system.
 * Implement this class as a nested class. For each event, create
 * a nested sub class from this class.
 * Save a public variable in outer class.
 */
template<class T>
class event {
public:
    /**
     * Adds a event listener for a class member method.
     * @param instance Class instance.
     */
    template<class C, void (C::*handler)(T)>
    void add_listener(C *instance) {
        auto p = new stub(instance, &class_method_stub<C, handler>);
        event_vec.push_back(p);
    }

    /**
     * Adds a event listener for a function.
     */
    template<void (*handler)(T)>
    void add_listener(void) {
        auto p = new stub(nullptr, &function_stub<handler>);
        event_vec.push_back(p);
    }

    /**
     * Removes the given event listener.
     * @param instance Class instance.
     */
    template<class C, void (C::*handler)(T)>
    void remove_listener(C *instance) {
        int i = find_listener<C, handler>(instance);
        if (i == -1)
            return;
        //delete event_vec[i];
        event_vec.erase(event_vec.begin() + i);
    }

    /**
     * Removes the given event listener.
     */
    template<void (*handler)(T)>
    void remove_listener(void) {
        int i = find_listener<handler>();
        if (i == -1)
            return;
        delete event_vec[i];
        event_vec.erase(event_vec.begin() + i);
    }

    /**
     * Checks if the event handler is registered.
     */
    template<void (*handler)(T)>
    bool is_registered(void) {
        int i = find_listener<handler>();
        if (i == -1)
            return false;
        return true;
    }

    /**
     * Checks if the event handler is registered.
     */
    template<class C, void (C::*handler)(T)>
    bool is_registered(C* instance) {
        int i = find_listener<C, handler>(instance);
        if (i == -1)
            return false;
        return true;
    }

protected:
    event() {}
    ~event() {
        for (auto p : event_vec) {
            delete p;
        }
    }

    /**
     * Dispatches a event. Calls all event listeners.
     * Executes each event in own thread.
     * @param data Data submitted with event.
     */
    void dispatch(T data) {
        for (auto p : event_vec) {
            std::thread t(p->second, p->first, data);
            t.detach();
        }
    }

private:
    typedef void *instance_ptr;
    typedef void (*internal_function)(instance_ptr, T);
    typedef std::pair<instance_ptr, internal_function> stub;

    std::vector<stub*> event_vec;

    /** Turns a free function into internal function stub. */
    template <void (*handler)(T)>
    static __attribute__((always_inline)) void function_stub(instance_ptr, T data)
        {
            return (handler)(data);
        }

    /** Turns a member function into internal function stub. */
    template <class C, void (C::*handler)(T)>
    static __attribute__((always_inline)) void class_method_stub(instance_ptr instance, T data)
        {
            return (static_cast<C*>(instance)->*handler)(data);
        }

    /**
     * Searches for given listener.
     * @returns Index on found. -1 if not found.
     */
    template<void (*handler)(T)>
    int find_listener(void) {
        int size = event_vec.size();
        for (int i = 0; i < size; i++) {
            if (event_vec[i]->second == &function_stub<handler>)
                return i;
        }
        return -1;
    }

    /**
     * Searches for given listener.
     * @returns Index on found. -1 if not found.
     */
    template<class C, void (C::*handler)(T)>
    int find_listener(C* instance) {
        int size = event_vec.size();
        for (int i = 0; i < size; i++) {
            if (event_vec[i]->first == instance
                && event_vec[i]->second == &class_method_stub<C, handler>)
                return i;
        }
        return -1;
    }
};

#endif
