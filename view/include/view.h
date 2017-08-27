#ifndef VIEW_H_
#define VIEW_H_

#include "screen/include/screen.h"

class view {
public:
    /**
     * Sets the margin of the view on top side.
     */
    void set_margin_top(int m) {
        if (m >= 0)
            margin_top = m;
    }

    /**
     * Sets the margin of the view on bottom side.
     */
    void set_margin_bot(int m) {
        if (m >= 0)
            margin_bot = m;
    }

    /**
     * Sets the margin of the view on left side.
     */
    void set_margin_left(int m) {
        if (m >= 0)
            margin_left = m;
    }

    /**
     * Sets the margin of the view on right side.
     */
    void set_margin_right(int m) {
        if (m >= 0)
            margin_right = m;
    }

    /**
     * Sets the padding of the view on top side.
     */
    void set_padding_top(int p);

    /**
     * Sets the padding of the view on bottom side.
     */
    void set_padding_bot(int p);

    /**
     * Sets the padding of the view on left side.
     */
    void set_padding_left(int p);

    /**
     * Sets the padding of the view on right side.
     */
    void set_padding_right(int p);

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
     * Returns the padding on top side.
     * @returns Padding top.
     */
    int get_padding_top() {
        return padding_top;
    }

    /**
     * Returns the padding on bottom side.
     * @returns Padding bottom.
     */
    int get_padding_bot() {
        return padding_bot;
    }

    /**
     * Returns the padding on left side.
     * @returns Padding left.
     */
    int get_padding_left() {
        return padding_left;
    }

    /**
     * Returns the padding on right side.
     * @returns Padding right.
     */
    int get_padding_right() {
        return padding_right;
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

private:
    int margin_top = 0;
    int margin_bot = 0;
    int margin_left = 0;
    int margin_right = 0;

    int padding_top = 0;
    int padding_bot = 0;
    int padding_left = 0;
    int padding_right = 0;

    int height = 0;
    int width = 0;

    int startx = 0;
    int starty = 0;
};

#endif
