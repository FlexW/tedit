#include <thread>

#include "include/ncurses_screen.h"

ncurses_screen::ncurses_screen() {
}

ncurses_screen::~ncurses_screen() {
}

int ncurses_screen::get_max_x() {
    int x, y;
    getmaxyx(stdscr, y, x);
    return x;
}

int ncurses_screen::get_max_y() {
    int x, y;
    getmaxyx(stdscr, y, x);
    return y;
}

void ncurses_screen::add_char(std::shared_ptr<window> w, int x, int y, char c) {
    mvwaddch(w->win, y, x, c);
}

void ncurses_screen::add_string(std::shared_ptr<window> w, int x, int y, std::string s) {
    mvwprintw(w->win, y, x, s.c_str());
}

void ncurses_screen::draw(std::shared_ptr<window> w) {
    curs_set(0);
    wrefresh(w->win);
    curs_set(1);
}

void ncurses_screen::draw() {
    curs_set(0);
    refresh();
    curs_set(1);
}

void ncurses_screen::set_size(std::shared_ptr<window> w, int x, int y) {
    wclear(w->win);
    wborder(w->win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(w->win);
    draw(w);
    wresize(w->win, y, x);
    draw(w);
}

void ncurses_screen::set_pos(std::shared_ptr<window> w, int startx, int starty) {
    wclear(w->win);
    wborder(w->win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(w->win);
    draw(w);
    //mvwin(w->win, starty, startx);
    w->win->_begx = startx;
    w->win->_begy = starty;
    draw(w);
}

void ncurses_screen::init() {
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
    resize.watch_resize();
}

void ncurses_screen::exit() {
    endwin();
}

void ncurses_screen::draw_border(std::shared_ptr<window> w, int chtx, int chty) {
    box(w->win, chty, chtx);
    draw(w);
}

void ncurses_screen::delete_window(std::shared_ptr<window> w) {
     wborder(w->win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
     wrefresh(w->win);
     delwin(w->win);
     num_wins--;
     if (num_wins == 0) {
         exit();
         resize.set_watch_resize_status(false);
     }
}

void ncurses_screen::resize_event::watch_resize() {
    std::thread t(&resize_event::tresize, this);
    t.detach();
}

void ncurses_screen::resize_event::tresize() {
    while (!quit) {
        if (getch() == KEY_RESIZE) {
            this->dispatch(0);
        }
    }
    quit = false;
}

void ncurses_screen::resize_event::set_watch_resize_status(bool b) {
    quit = b;
}
