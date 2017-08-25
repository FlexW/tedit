#ifndef EDITOR_H_
#define EDITOR_H_

#include <memory>
#include <string>

#include "view_container.h"
#include "keyboard.h"
#include "screen.h"

class editor {
public:
    editor();

    /**
     * Opens initially a file.
     */
    editor(std::string *filename);

    ~editor();

    /**
     * Runs the editor.
     */
    void run();

    /**
     * Opens a file.
     */
    void open(std::string *filename);

    /**
     * Exits the editor
     */
    void exit();

private:
    std::unique_ptr<view_container> vcontainer; /**< Holds all buffers. */
    std::unique_ptr<keyboard> kboard; /**< Editors keyboard. */
    std::unique_ptr<screen> scr; /**< Screen. */

    std::shared_ptr<screen::window> std_screen; /**< Outermost window. */

    /**
     * Sets terminal into raw mode.
     */
    void init();
};

#endif
