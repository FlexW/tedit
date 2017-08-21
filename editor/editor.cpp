#include <string>

#include "include/editor.h"
#include "include/view.h"

editor::editor() {
        container = new buffer_container(this, &win);
}

void editor::init() {
        win.init();
}

void editor::open(std::string *filename) {
        container->open_buffer(*filename);
}

void editor::run() {
        if (container->active() == nullptr)
                container->open_buffer("");
        while (true) {
                container->active()->refresh_screen();
                container->active()->process_key();
        }
}

void editor::exit() {
        win.exit();
        std::exit(0);
}
