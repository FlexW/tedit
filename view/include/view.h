#ifndef VIEW_H_
#define VIEW_H_

#include <vector>

//#include "screen/include/screen.h"
#include "screen/include/ncurses_screen.h"

/**
 * Represents a view that can be displayed on the screen.
 */
class view {
public:
    /**
     * @param startx View left corner x axsis.
     * @param starty View left corner y axsis.
     * @param width View percentual width.
     * @param height View percentual height.
     */
    view(int startx, int starty, int width, int height);

    virtual ~view();

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
     * Sets the percentual height of the view.
     */
    void set_height(int h);

    /**
     * Sets the percentual width of the view.
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
    void set_screen(ncurses_screen &scr) {
            //this->scr = scr;
        draw();
    }

    /**
     * Sets the window in which the view is drawn.
     * @param win Window.
     */
    void set_window(std::shared_ptr<ncurses_screen::window> win) {
        this->win = win;
        draw();
    }

    /**
     * Draws the view on screen.
     */
    void draw();

    /**
     * Returns the size of the print buffer.
     */
    int get_print_buffer_size();

    /**
     * Gets the char at position from print buffer.
     */
    char get_char_print_buffer(int x, int y);

    /**
     * Adds a char to the views print buffer.
     * @param X Position.
     * @param Y Position.
     * @param c Char.
     */
    void add_char_print_buffer(int x, int y, char c);

    std::shared_ptr<std::string> get_name() {
        return name;
    }

    void set_name(std::string &name) {
        std::shared_ptr<std::string> n(&name);
        this->name = n;
    }

    /** Delete view. */
    void delete_view();

    /** Gets called when the window gets resized. */
    void resize(int i);

protected:
    /** Name of the view. */
    std::shared_ptr<std::string> name;

    int padding_top = 0;
    int padding_bot = 0;
    int padding_left = 0;
    int padding_right = 0;

    int rpadding_top = 0;
    int rpadding_bot = 0;
    int rpadding_left = 0;
    int rpadding_right = 0;

    /** Representation of the view in memory. */
    char *print_buffer = nullptr;

    int height = 1;
    int width = 1;

    /** Real height. */
    int rheight = 0;
    /** Real width. */
    int rwidth = 0;

    /** Percentual left corner x axsis. */
    int startx = 0;
    /** Percentual left corner x axsis. */
    int starty = 0;

    /** Real left corner x axsis. */
    int rstartx = 0;
    /** Real left corner y axsis. */
    int rstarty = 0;

    /** Screen in which the view gets displayed. */
    //ncurses_screen scr;

    /** Window in which the view will be displayed. */
    std::shared_ptr<ncurses_screen::window> win;

    /**
     * Corrects the height and width of the print buffer.
     * Clears all values.
     */
    void reset_print_buffer();

    /**
     * Draws the print buffer to screen.
     */
    void draw_print_buffer();

    /**
     * Gets the print buffers height.
     */
    int get_print_buffer_height();

    /**
     * Gets the print buffers width.
     */
    int get_print_buffer_width();

    /** Gets the real width. */
    int get_rwidth();

    /** Gets the real height. */
    int get_rheight();
};

#endif
