#ifndef SCREEN_H_
#define SCREEN_H_

#include <ncurses.h>

class screen {
public:
    struct window {
        WINDOW *win;
        int rowoff;
        int coloff;
    };
    /**
     * Draws the given area new.
     * @param xs X Start.
     * @param ys Y Start.
     * @param xe X End.
     * @param ye Y End.
     * @param win Window to draw. nullptr == stdscr.
     */
    void draw(int xs, int ys, int xe, int ye, WINDOW *win);
};

#endif
