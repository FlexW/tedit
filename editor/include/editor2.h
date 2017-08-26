#ifndef EDITOR_H_
#define EDITOR_H_

#include <memory>
#include <string>

#include "view/include/view.h"
#include "view_container.h"
#include "keyboard.h"
#include "screen.h"

class editor {
public:
    editor();

    /**
     * Opens initially a file.
     */
    editor(std::string &filename);

    ~editor();

    /**
     * Runs the editor.
     */
    void run();

    /**
     * Opens a file.
     */
    void open(std::string &filename);

    /**
     * Exits the editor
     */
    void exit();

private:
    /**
     * Represents a buffer that the user can see.
     * If the user splits the screen there will be multiple text_buffers.
     */
    struct text_buffer {
        /** Window that displays buffer. */
        std::shared_ptr<screen::window> win;

        /** Stores the order of open buffers. */
        std::vector<int> buffer_order;
    };

    std::unique_ptr<keyboard> kboard; /**< Editors keyboard. */
    std::unique_ptr<screen> scr; /**< Screen. */
    /** Holds all open buffers. */
    std::unique_ptr<view_container> vcontainer;

    std::shared_ptr<screen::window> std_screen; /**< Outermost window. */

    /** Stores all open buffers. */
    std::vector<std::shared_ptr<text_buffer>> buffer_vec;

    /**
     * Sets terminal into raw mode.
     */
    void init();

    /**
     * Opens a new text buffer.
     * @param t Current active text buffer.
     * @param height Height of new window.
     * @param width Width of new window.
     * @param startx X Coordinate to start displaying window.
     * @param stary Y Coordinate to start displaying window.
     * @returns Text buffer.
     */
    std::shared_ptr<text_buffer> new_text_buffer(std::shared_ptr<text_buffer> t,
                                                 int height, int width,
                                                 int startx, int starty) {
        std::shared_ptr<text_buffer> tb(std::make_shared<text_buffer>());
        tb->win = scr->new_window(height, width, starty, startx);
        tb->buffer_order = t->buffer_order;
        buffer_vec.push_back(tb);
        return tb;
    }

    /**
     * Opens a new text buffer.
     * @param height Height of new window.
     * @param width Width of new window.
     * @param startx X Coordinate to start displaying window.
     * @param stary Y Coordinate to start displaying window.
     * @returns Text buffer.
     */
    std::shared_ptr<text_buffer> new_text_buffer(int height, int width,
                                                 int startx, int starty) {
        std::shared_ptr<text_buffer> tb(std::make_shared<text_buffer>());
        tb->win = scr->new_window(height, width, starty, startx);
        tb->buffer_order.push_back(0);
        buffer_vec.push_back(tb);
        return tb;
    }
};

#endif
