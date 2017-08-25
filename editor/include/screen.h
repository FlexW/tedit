#ifndef SCREEN_H_
#define SCREEN_H_

#include <memory>
#include <ncurses.h>

class screen {
public:
    struct window {
        WINDOW *win;
        int rowoff;
        int coloff;
    };

    /**
     * Sets terminal into raw mode.
     * Returns the outermost window.
     */
    std::shared_ptr<window> init();

    /**
     * Gets the maximum columns for window.
     * @param win Window.
     * @returns Maximum columns.
     */
    int max_x(std::shared_ptr<window> win);

    /**
     * Gets the maximum rows for window.
     * @param win Window.
     * @returns Maximum rows.
     */
    int max_y(std::shared_ptr<window> win);

    /**
     * Creates a new window.
     */
    std::shared_ptr<window> new_window();

    /**
     * Draws the given area new.
     * @param xs X Start.
     * @param ys Y Start.
     * @param xe X End.
     * @param ye Y End.
     * @param win Window to draw. nullptr == stdscr.
     */
    void draw(int xs, int ys, int xe, int ye, std::shared_ptr<window> win);
};

#endif
