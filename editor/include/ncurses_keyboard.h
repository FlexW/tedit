#ifndef NCURSES_KEYBOARD_H_
#define NCURSES_KEYBOARD_H_

#include <ncurses.h>

#include "keyboard.h"

class ncurses_keyboard : public keyboard {
private:
    void get_key() {
        int key = getch();
        click_event.dispatch_click_event(key);
    }
};

#endif
