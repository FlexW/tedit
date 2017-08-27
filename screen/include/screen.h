#ifndef SCREEN_H_
#define SCREEN_H_

#include <memory>
#include <string>
#include <ncurses.h>

/**
 * Represents the area in which a view can be drawn.
 */
class screen {
public:
    struct window {
        std::shared_ptr<WINDOW> win;
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
     * Draws the current print buffer to screen.
     * @param w Window.
     */
    void draw(std::shared_ptr<window> w);
};
#endif
