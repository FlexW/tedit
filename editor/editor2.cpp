#include "include/editor2.h"

editor::editor() {
    init();
}


editor::editor(std::string *filename) {
    init();
    open(filename);
}

editor::~editor() {
}

void editor::run() {
}

void editor::open(std::string* filename) {
}

void editor::exit() {
}

void editor::init() {
    vcontainer.reset(new view_container());
    kboard.reset(new keyboard());
    scr.reset(new screen());
    std_screen = scr->init();
}
