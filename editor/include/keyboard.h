#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include "event/include/event.h"

/**
 * Handles keyboard input. Routes the input
 * to editor.
 */
class keyboard {
public:
    class click_event : public event<int> {
    public:
        void dispatch_click_event(int key) {
            dispatch(key);
        }
    };
    click_event click_event;
};

#endif
