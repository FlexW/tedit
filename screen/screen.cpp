#include "include/screen.h"

screen::screen() {
    init();
}

screen::~screen() {
}

int screen::get_max_x() {
    int x, y;
    getmaxyx(stdscr, y, x);
    return x;
}

int screen::get_max_y() {
    int x, y;
    getmaxyx(stdscr, y, x);
    return y;
}

void screen::add_char(std::shared_ptr<window> w, int x, int y, char c) {
    mvwaddch(w->win, y, x, c);
}

void screen::add_string(std::shared_ptr<window> w, int x, int y, std::string s) {
    mvwprintw(w->win, y, x, s.c_str());
}

void screen::draw(std::shared_ptr<window> w) {
    curs_set(0);
    wrefresh(w->win);
    curs_set(1);
}

void screen::draw() {
    curs_set(0);
    refresh();
    curs_set(1);
}

void screen::set_size(std::shared_ptr<window> w, int x, int y) {
    wresize(w->win, y, x);
}

void screen::set_pos(std::shared_ptr<window> w, int startx, int starty) {
    mvwin(w->win, starty, startx);
}

void screen::init() {
    initscr();
    clear();
    noecho();
    cbreak();
    nonl();
    intrflush(stdscr, false);
    keypad(stdscr, true);
    raw();
    TABSIZE = 8;
    refresh();
}

void screen::exit() {
    endwin();
}

void screen::draw_border(std::shared_ptr<window> w, int chtx, int chty) {
    box(w->win, chty, chtx);
    draw(w);
}
