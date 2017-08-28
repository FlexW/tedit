#include "include/text_view.h"

text_view::text_view() {
    reset_print_buffer();
}

text_view::~text_view() {
    free(print_buffer);
}
