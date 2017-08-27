#include "include/view.h"

void view::set_padding_top(int p) {
    if ((height - padding_bot) >= p)
        padding_top = p;
}

void view::set_padding_bot(int p) {
    if ((height - padding_top) >= p)
        padding_bot = p;
}

void view::set_padding_left(int p) {
    if ((width - padding_right) >= p)
        padding_left = p;
}

void view::set_padding_right(int p) {
    if ((width - padding_left) >= p)
        padding_right = p;
}

void view::set_height(int h) {
    height = h;
}

void view::set_width(int w) {
    width = w;
}

void view::set_startx(int x) {
    if (x >= 0)
        startx = x;
}

void view::set_starty(int y) {
    if (y >= 0)
        starty = y;
}
