#ifndef NCURSES_SCREEN_H_
#define NCURSES_SCREEN_H_

#include <atomic>
#include <cstdlib>
#include <memory>
#include <mutex>
#include <string>
#include <ncurses.h>

#include "event/include/event.h"

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
         * Watches if the user resizes the window.
         * Fires event.
         */
        void watch_resize();

        /**
         * Calls all listeners. This get called from sigwinch_handler().
         * Do not call this method.
         */
        void call_listener();

        /**
         * Handler function that gets called from the OS.
         * Do not call this method.
         * @param signum Signal number
         */
        static void sigwinch_handler(int signum);

    private:
        /**
         * Mutex to lock if resizing is performed.
         */
        std::mutex resize_mutex;

        /**
         * If this flag is set and class is currently dispatching resize events,
         * it will after dispatching, again call all listeners.
         */
        std::atomic_flag not_resize_flag = ATOMIC_FLAG_INIT;
    };
    resize_event resize;

    /**
     * Gets the maximum units in x direction.
     * @returns Max X.
     */
    int get_max_x();

    /**
     * Gets the maximum units in y direction.
     * @returns Max Y.
     */
    int get_max_y();

    /**
     * Gets the maximum units in x direction.
     * @param w Window.
     * @returns Max X.
     */
    int get_max_x(std::shared_ptr<window> w);

    /**
     * Gets the maximum units in y direction.
     * @param w Window.
     * @returns Max Y.
     */
    int get_max_y(std::shared_ptr<window> w);

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

    /**
     * Mutex locks the class if someone is performing a I/O operation.
     */
    std::mutex screen_mutex;

    /** Tracks the number of open views. */
    int num_wins = 0;
};
#endif
