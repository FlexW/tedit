#ifndef SCREEN_H_
#define SCREEN_H_

#include <cstdlib>
#include <memory>
#include <string>
#include <ncurses.h>

/**
 * Represents the area in which a view can be drawn.
 */
class screen {
public:
    screen();
    ~screen();

    struct window {
        WINDOW* win;
    };
    /**
     * Gets the maximum units in x direction.
     */
    int get_max_x();

    /**
     * Gets the maximum units in y direction.
     */
    int get_max_y();

    /**
     * Adds char to print buffer.
     * @param w Window.
     * @param x X position.
     * @param y Y position.
     * @param c Character to add.
     */
    void add_char(std::shared_ptr<window> w, int x, int y, char c);

    /**
     * Adds string to print buffer.
     * @param w Window.
     * @param x X position.
     * @param y Y position.
     * @param s String to add.
     */
    void add_string(std::shared_ptr<window> w, int x, int y, std::string s);

    /**
     * Draws the windows print buffer to screen.
     * @param w Window.
     */
    void draw(std::shared_ptr<window> w);

    /**
     * Draws the screen print buffer to screen.
     * @param w Window.
     */
    void draw();

    /**
     * Sets a windows size.
     * @param w Window.
     * @param x Width.
     * @param y Height.
     */
    void set_size(std::shared_ptr<window> w, int x, int y);

    /**
     * Sets a windows position in the screen.
     * @param startx X start position.
     * @param starty Y start position.
     */
    void set_pos(std::shared_ptr<window> w, int startx, int starty);

    /**
     * Creates a new window.
     * @param startx X position upper hand left corner of window.
     * @param startx Y position upper hand left corner of window.
     * @param x Number of columns.
     * @param y Number of rows.
     * @returns Window.
     */
    std::shared_ptr<window> new_window(int startx, int starty, int x, int y) {
        //std::shared_ptr<window> wp(std::make_shared<window>);
        auto wp = std::make_shared<window>();
        WINDOW *nwin = newwin(y, x, starty, startx);
        wp->win = nwin;
        return wp;
    }

    /**
     * Sets terminal into raw mode.
     */
    void init();

    /**
     * Sets terminal in normal mode.
     */
    void exit();

    void draw_border(std::shared_ptr<window> w, int chtx, int chty);
};
#endif
