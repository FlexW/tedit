#include <cstdlib>

#include "include/view.h"

view::view() {
    std::shared_ptr<screen> s(std::make_shared<screen>());
    std::shared_ptr<screen::window> w(std::make_shared<screen::window>());
    scr = s;
    win = w;
}

view::~view() {
}

void view::set_margin_top(int m) {
    if (m >= 0) {
        margin_top = m;
        draw();
    }
}

void view::set_margin_bot(int m) {
    if (m >= 0) {
        margin_bot = m;
        draw();
    }
}

void view::set_margin_left(int m) {
    if (m >= 0) {
        margin_left = m;
        draw();
    }
}

void view::set_margin_right(int m) {
    if (m >= 0) {
        margin_right = m;
        draw();
    }
}

void view::set_padding_top(int p) {
    if ((height - padding_bot) >= p) {
        padding_top = p;
        draw();
    }
}

void view::set_padding_bot(int p) {
    if ((height - padding_top) >= p) {
        padding_bot = p;
        draw();
    }
}

void view::set_padding_left(int p) {
    if ((width - padding_right) >= p) {
        padding_left = p;
        draw();
    }
}

void view::set_padding_right(int p) {
    if ((width - padding_left) >= p) {
        padding_right = p;
        draw();
    }
}

void view::set_height(int h) {
    height = h;
    draw();
}

void view::set_width(int w) {
    width = w;
    draw();
}

void view::set_startx(int x) {
    if (x >= 0) {
        startx = x;
        draw();
    }
}

void view::set_starty(int y) {
    if (y >= 0) {
        starty = y;
        draw();
    }
}

void view::draw() {
    int wm = width + margin_left + margin_right;
    int hm = height + margin_top + margin_bot;
    scr->set_size(win, wm, hm);
    scr->set_pos(startx, starty);
}

void view::reset_print_buffer() {
    int ph = height - padding_top - padding_bot;
    int pw = width - padding_left - padding_right;
    print_buffer = (char**)malloc(sizeof(char) * (ph * pw));
}
