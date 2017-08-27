#include <cstdlib>
#include <cstring>

#include "include/text_view.h"

text_view::text_view() {
    reset_print_buffer();
}

text_view::~text_view() {
    free(print_buffer);
}

void text_view::set_padding_top(int p) {
    if ((height - padding_bot) >= p) {
        padding_top = p;
        draw();
    }
}

void text_view::set_padding_bot(int p) {
    if ((height - padding_top) >= p) {
        padding_bot = p;
        draw();
    }
}

void text_view::set_padding_left(int p) {
    if ((width - padding_right) >= p) {
        padding_left = p;
        draw();
    }
}

void text_view::set_padding_right(int p) {
    if ((width - padding_left) >= p) {
        padding_right = p;
        draw();
    }
}

void text_view::reset_print_buffer() {
    int ph = height - padding_top - padding_bot;
    int pw = width - padding_left - padding_right;
    char *tmp_pb = (char*)malloc(sizeof(char) * (ph * pw));
    if (print_buffer != nullptr) {
        memcpy(tmp_pb, print_buffer, sizeof(char));
        free(print_buffer);
    }
    print_buffer = tmp_pb;
}

void text_view::add_char_print_buffer(int x, int y, char c) {
    int pos = y * width + x;
    *(print_buffer + pos) = c;
}
