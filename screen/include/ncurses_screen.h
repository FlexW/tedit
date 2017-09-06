#ifndef NCURSES_SCREEN_H_
#define NCURSES_SCREEN_H_

#include <atomic>
#include <cstdlib>
#include <memory>
#include <string>
#include <ncurses.h>

#include "event/include/event.h"

//#include "screen.h"

/**
 * Represents the area in which a view can be drawn.
 */
class ncurses_screen {
public:
    ~ncurses_screen();

    struct window {
        WINDOW* win;
    };

    static ncurses_screen& get_instance() {
        static ncurses_screen instance;
        return instance;
    }

    class resize_event : public event<int> {
    public:

        /**
         * This value will be checked by watch_resize().
         * If true the execution of watch_resize will be stoped.
         */
        bool quit = false;

        /**
         * Watches if the user resizes the window.
         * Fires event.
         */
        void watch_resize();

        void set_watch_resize_status(bool b);

    private:
        void tresize();
    };
    resize_event resize;

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
        if (num_wins == 0) {
            init();
        }
        auto wp = std::make_shared<window>();
        WINDOW *nwin = newwin(y, x, starty, startx);
        wp->win = nwin;
        num_wins++;
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

    /*
     * TODO: Make this a real useful function.
     */
    void draw_border(std::shared_ptr<window> w, int chtx, int chty);

    /**
     * Deletes a window.
     * @param w Window.
     */
    void delete_window(std::shared_ptr<window> w);

    ncurses_screen(ncurses_screen const&) = delete;
    void operator=(ncurses_screen const&) = delete;

private:
    ncurses_screen();

    /** Tracks the number of open views. */
    int num_wins = 0;
};
#endif
