#ifndef EDITOR_H_
#define EDITOR_H_

#include "buffer.h"
#include "buffer_container.h"
#include "view.h"

class buffer;
class buffer_container;

class editor {
public:
        editor();
        /**
         * Initializes the editor.
         */
        void init();
        /**
         * Opens a file.
         */
        void open(std::string *filename);
        /**
         * Runs the editor.
         */
        void run();
        /**
         * Exits the editor.
         */
        void exit();
private:
        view win;
        buffer_container *container = nullptr; /**< Holds all buffers. */
};

#endif
