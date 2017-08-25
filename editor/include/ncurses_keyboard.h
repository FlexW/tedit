#ifndef NCURSES_KEYBOARD_H_
#define NCURSES_KEYBOARD_H_

#include <ncurses.h>

#include "keyboard.h"

class ncurses_keyboard : public keyboard {
private:
    /** Gets a char from stdin. Dispatches a event for that.*/
    void get_key() {
        int key = getch();
        click_event.dispatch_click_event(key);
    }
};

#endif
