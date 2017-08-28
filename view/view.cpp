#include <cstdlib>
#include <cstring>

#include "include/view.h"

view::view() {
    scr = std::make_shared<screen>();
    win = std::make_shared<screen::window>();
    reset_print_buffer();
}

view::~view() {
    free(print_buffer);
}

void view::set_padding_top(int p) {
    if ((height - padding_bot) >= p) {
        padding_top = p;
        reset_print_buffer();
        draw();
    }
}

void view::set_padding_bot(int p) {
    if ((height - padding_top) >= p) {
        padding_bot = p;
        reset_print_buffer();
        draw();
    }
}

void view::set_padding_left(int p) {
    if ((width - padding_right) >= p) {
        padding_left = p;
        reset_print_buffer();
        draw();
    }
}

void view::set_padding_right(int p) {
    if ((width - padding_left) >= p) {
        padding_right = p;
        reset_print_buffer();
        draw();
    }
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
    reset_print_buffer();
    draw();
}

void view::set_width(int w) {
    width = w;
    reset_print_buffer();
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

    //if(draw_hook())
        ;//scr->draw(win);
}

void view::reset_print_buffer() {
    int ph = height - padding_top - padding_bot;
    int pw = width - padding_left - padding_right;
    char *tmp_pb = (char*)malloc(sizeof(char) * (ph * pw));
    if (print_buffer != nullptr) {
        memcpy(tmp_pb, print_buffer, sizeof(char));
        free(print_buffer);
    }
    print_buffer = tmp_pb;
}

void view::add_char_print_buffer(int x, int y, char c) {
    int pos = y * width + x;
    *(print_buffer + pos) = c;
}

int view::get_print_buffer_size() {
    int ph = height - padding_top - padding_bot;
    int pw = width - padding_left - padding_right;

    return (ph * pw);
}

char view::get_char_print_buffer(int x, int y) {
    int pos = y * width + x;
    return *(print_buffer + pos);
}
