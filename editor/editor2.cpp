#include "include/editor2.h"

editor::editor() {
    init();
}


editor::editor(std::string &filename) {
    init();
    open(filename);
    //new_text_buffer(scr->max_y(), scr->max_x(), 0, 0);
}

editor::~editor() {
}

void editor::run() {
}

void editor::open(std::string &filename) {
    vcontainer->open_view(filename);
}

void editor::exit() {
}

void editor::init() {
    kboard.reset(new keyboard());
    scr.reset(new screen());
    vcontainer.reset(new view_container());
    std_screen = scr->init();
}
