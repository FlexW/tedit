#include <cstdlib>
#include <cstring>
#include <cmath>

#include "include/log.h"
#include "include/view.h"

view::view(int startx, int starty, int width, int height) {
    win = ncurses_screen::get_instance()
            .new_window(rstartx, rstarty, rwidth, rheight);
    set_startx(startx, false);
    set_starty(starty, false);
    set_height(height, false);
    set_width(width, false);

    reset_print_buffer();
    draw();
    ncurses_screen::get_instance().resize.add_listener<view, &view::resize>(this);
    FILE_LOG(logINFO) << "Created view. x: " << startx << " y: " << starty
                      << " width: " << width << " height: " << height;
}

view::~view() {
}

void view::set_padding_top(int p, bool redraw) {
    if (p < 0 || p > (100 - padding_bot))
        return;
    padding_top = p;
    FILE_LOG(logINFO) << "Padding top set: " << padding_top;

    float rp = ((float)height / 100.) * (float)p;
    rpadding_top = int(std::round(rp));
    FILE_LOG(logINFO) << "Real padding top set: " << rpadding_top;

    if(!redraw)
        return;
    reset_print_buffer();
    draw();
}

void view::set_padding_bot(int p, bool redraw) {
    if (p < 0 || p > (100 - padding_top))
        return;
    padding_bot = p;
    FILE_LOG(logINFO) << "Padding bottom set: " << padding_bot;

    float rp = ((float)height / 100.) * (float)p;
    rpadding_bot = int(std::round(rp));
    FILE_LOG(logINFO) << "Real padding bottom set: " << rpadding_bot;

    if(!redraw)
        return;
    reset_print_buffer();
    draw();
}

void view::set_padding_left(int p, bool redraw) {
    if (p < 0 || p > (100 - padding_right))
        return;
    padding_left = p;
    FILE_LOG(logINFO) << "Padding left set: " << padding_left;

    float rp = ((float)width / 100.) * (float)p;
    rpadding_left = int(std::round(rp));
    FILE_LOG(logINFO) << "Real padding left set: " << rpadding_left;

    if(!redraw)
        return;
    reset_print_buffer();
    draw();
}

void view::set_padding_right(int p, bool redraw) {
    if (p < 0 || p > (100 - padding_left))
        return;
    padding_right = p;
    FILE_LOG(logINFO) << "Padding right set: " << padding_right;

    float rp = ((float)width / 100.) * (float)p;
    rpadding_right = int(std::round(rp));
    FILE_LOG(logINFO) << "Real padding right set: " << rpadding_right;

    if(!redraw)
        return;
    reset_print_buffer();
    draw();
}

void view::set_height(int h, bool redraw) {
   if (h >= 0 && h <= 100) {
        height = h;
        FILE_LOG(logINFO) << "Height set: " << height;

        int my = ncurses_screen::get_instance().get_max_y();
        FILE_LOG(logINFO) << "Real possible height: " << my;
        float rh = ((float)my / 100.) * (float)height;
        rheight = int(std::round(rh));
        FILE_LOG(logINFO) << "Real height set: " << rheight;

        if(!redraw)
            return;
        reset_print_buffer();
        draw();
   }
}

void view::set_width(int w, bool redraw) {
    if (w >= 0 && w <= 100) {
        width = w;
        FILE_LOG(logINFO) << "Width set: " << width;

        int mx = ncurses_screen::get_instance().get_max_x();
        FILE_LOG(logINFO) << "Real possible width: " << mx;
        float rw = ((float)mx / 100.) * (float)width;
        rwidth = int(std::round(rw));
        FILE_LOG(logINFO) << "Real width set: " << rwidth;

        if(!redraw)
            return;
        reset_print_buffer();
        draw();
    }
}

void view::set_startx(int x, bool redraw) {
    if (x >= 0 && x <= 100) {
        startx = x;
        FILE_LOG(logINFO) << "X set: " << startx;

        int maxx = ncurses_screen::get_instance().get_max_x();
        float rx = ((float)maxx / 100.) * (float)x;
        rstartx = int(std::round(rx));
        FILE_LOG(logINFO) << "Real X set: " << rstartx;

        if(!redraw)
            return;
        draw();
    }
}

void view::set_starty(int y, bool redraw) {
    if (y >= 0 && y <= 100) {
        starty = y;
        FILE_LOG(logINFO) << "Y set: " << starty;

        int maxy = ncurses_screen::get_instance().get_max_y();
        float ry = ((float)maxy / 100.) * (float)y;
        rstarty = int(std::round(ry));
        FILE_LOG(logINFO) << "Real Y set: " << rstarty;

        if(!redraw)
            return;
        draw();
    }
}

void view::draw() {
    if (rheight <= 0 || rwidth <= 0)
        return;
    ncurses_screen::get_instance().set_size(win, rwidth, rheight);
    ncurses_screen::get_instance().set_pos(win, rstartx, rstarty);
    draw_print_buffer();
    FILE_LOG(logINFO) << "Draw view.";
    ncurses_screen::get_instance().draw(win);
}

void view::reset_print_buffer() {
    int ph = rheight - rpadding_top - rpadding_bot;
    int pw = rwidth - rpadding_left - rpadding_right;

    if (pw <= 0 || ph <= 0) {
        if (print_buffer != nullptr)
            free(print_buffer);
        print_buffer = nullptr;
        return;
    }
    FILE_LOG(logINFO) << "Reset print buffer.Width: " << pw
                      << " Height: " << ph;

    char *tmp_pb = (char*)calloc((ph * pw), sizeof(char));

    for (int i = 0; i < (ph * pw); i++) {
            *(tmp_pb + i) = ' ';
    }
    if (print_buffer != nullptr) {
        //memcpy(tmp_pb, print_buffer, sizeof(char));
        free(print_buffer);
    }
    print_buffer = tmp_pb;

    if (reset_print_buffer_handler != nullptr)
        (this->*reset_print_buffer_handler)();
}

void view::add_char_print_buffer(int x, int y, char c) {
    if (print_buffer == nullptr)
        return;
    int pos = y * get_print_buffer_width() + x;
    *(print_buffer + pos) = c;
    FILE_LOG(logDEBUG1) << "Added " << c << " to print buffer. Pos: " << pos;
}

int view::get_print_buffer_size() {
    int ph = get_print_buffer_height();
    int pw = get_print_buffer_width();

    return (ph * pw);
}

char view::get_char_print_buffer(int x, int y) {
    if (print_buffer == nullptr)
      return 0;
    int pos = y * get_print_buffer_width() + x;
    return *(print_buffer + pos);
}

void view::draw_print_buffer() {
  if (print_buffer == nullptr)
      return;
  int bheight = get_print_buffer_height();
  int bwidth = get_print_buffer_width();

  for (int i = 0; i < bheight; i++) {
      for (int j = 0; j < bwidth; j++) {
        char c = get_char_print_buffer(j, i);

        int orgx = padding_left;
        int orgy = padding_top;
        ncurses_screen::get_instance().add_char(win, j + orgx, i + orgy, c);
        FILE_LOG(logDEBUG1) << "Add char to screen print buffer. Char: " << c
                            << " X: " << (j + orgx) << " Y: " << (i + orgy);
      }
  }
}

int view::get_print_buffer_height() {
    int ph = rheight - rpadding_top - rpadding_bot;
    return ph;
}

int view::get_print_buffer_width() {
    int pw = rwidth - rpadding_left - rpadding_right;
    return pw;
}

void view::delete_view() {
    ncurses_screen::get_instance().delete_window(win);
    free(print_buffer);
}

void view::resize(int i) {
    set_startx(startx, false);
    set_starty(starty, false);
    set_height(height, false);
    set_width(width, false);

    reset_print_buffer();
    draw();
}

void view::set_print_buffer_reset_handler(reset_pb pbh) {
    reset_print_buffer_handler = pbh;
}
