#ifndef VIEW_H_
#define VIEW_H_

#include <vector>

#include "screen/include/screen.h"

class view {
public:

    view();
    ~view();

    /**
     * Sets the margin of the view on top side.
     */
    void set_margin_top(int m);

    /**
     * Sets the margin of the view on bottom side.
     */
    void set_margin_bot(int m);

    /**
     * Sets the margin of the view on left side.
     */
    void set_margin_left(int m);

    /**
     * Sets the margin of the view on right side.
     */
    void set_margin_right(int m);

    /**
     * Returns the margin on top side.
     * @returns Margin top.
     */
    int get_margin_top() {
        return margin_top;
    }

    /**
     * Returns the margin on bottom side.
     * @returns Margin bottom.
     */
    int get_margin_bot() {
        return margin_bot;
    }

    /**
     * Returns the margin on left side.
     * @returns Margin left.
     */
    int get_margin_left() {
        return margin_left;
    }

    /**
     * Returns the margin on right side.
     * @returns Margin right.
     */
    int get_margin_right() {
        return margin_right;
    }

    /**
     * Sets the height of the view.
     */
    void set_height(int h);

    /**
     * Sets the width of the view.
     */
    void set_width(int w);

    /**
     * Returns the actual height of the view.
     */
    int get_height() {
        return height;
    }

    /**
     * Returns the actual width of the view.
     */
    int get_width() {
        return width;
    }

    /**
     * Start of view x position in parent screen.
     * @param x Start x position.
     */
    void set_startx(int x);

    /**
     * Start of view y position in parent screen.
     * @param x Start y position.
     */
    void set_starty(int y);

    /**
     * Gets the view start x position.
     * @returns View startx position.
     */
    int get_startx() {
        return startx;
    }

    /**
     * Gets the view start y position.
     * @returns View starty position.
     */
    int get_starty() {
        return starty;
    }

    /**
     * Sets the screen in which the view is drawn.
     * @param scr Screen.
     */
    void set_screen(std::shared_ptr<screen> scr) {
        this->scr = scr;
        draw();
    }

    /**
     * Sets the window in which the view is drawn.
     * @param win Window.
     */
    void set_window(std::shared_ptr<screen::window> win) {
        this->win = win;
        draw();
    }

    /**
     * Draws the view on screen.
     */
    void draw();

protected:
    int margin_top = 0;
    int margin_bot = 0;
    int margin_left = 0;
    int margin_right = 0;

    int height = 1;
    int width = 1;

    int startx = 0;
    int starty = 0;

    /** Screen in which the view gets displayed. */
    std::shared_ptr<screen> scr;

    /** Window in which the view will be displayed. */
    std::shared_ptr<screen::window> win;
};

#endif
