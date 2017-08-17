#include <cstring>

#include "include/view.h"

void view::init() {
        initscr();
        clear();
        noecho();
        cbreak();
        nonl();
        intrflush(stdscr, false);
        keypad(stdscr, true);
        raw();
        TABSIZE = 8;
}

void view::exit() {
        endwin();
}

int view::getchar() {
        return getch();
}

int view::wincols() {
        int x, y;
        getmaxyx(stdscr, y, x);
        return x;
}

int view::winrows() {
        int x, y;
        getmaxyx(stdscr, y, x);
        return y;
}

void view::addchar(int row, int col, char c) {
        mvaddch(row, col, c);
}

void view::display() {
        curs_set(0);
        refresh();
        curs_set(1);
}

void view::setcurpos(int row, int col) {
        move(row, col);
}

void view::clearscrn() {
        //clear();
        erase();
}

void view::addstring(int row, int col, std::string &str) {
        mvprintw(row, col, str.c_str());
}

void view::clreol(int row, int col) {
        move(row, col);
        clrtoeol();
}
