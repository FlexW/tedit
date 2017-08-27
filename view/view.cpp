#include "include/view.h"

view::view() {
    auto s = std::make_shared<screen>();
    auto w = std::make_shared<screen::window>();
    //std::shared_ptr<screen> s(std::make_shared<screen>());
    //std::shared_ptr<screen::window> w(std::make_shared<screen::window>());
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

    //scr->set_size(win, wm, hm);
    //scr->set_pos(startx, starty);

    if(draw_hook())
        ;//scr->draw(win);
}
