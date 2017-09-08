#include <cassert>
#include <signal.h>

#include "include/log.h"
#include "include/ncurses_screen.h"

ncurses_screen::ncurses_screen() {
}

ncurses_screen::~ncurses_screen() {
}

int ncurses_screen::get_max_x() {
    int x, y;
    getmaxyx(stdscr, y, x);
    FILE_LOG(logINFO) << "Max X: " << x;
    return x;
}

int ncurses_screen::get_max_y() {
    int x, y;
    getmaxyx(stdscr, y, x);
    FILE_LOG(logINFO) << "Max Y: " << y;
    return y;
}

int ncurses_screen::get_max_x(std::shared_ptr<window> w) {
    int x, y;
    getmaxyx(w->win, y, x);
    FILE_LOG(logINFO) << "Max X: " << x;
    return x;
}

int ncurses_screen::get_max_y(std::shared_ptr<window> w) {
    int x, y;
    getmaxyx(w->win, y, x);
    FILE_LOG(logINFO) << "Max Y: " << y;
    return y;
}

void ncurses_screen::add_char(std::shared_ptr<window> w, int x, int y, char c) {
    int maxx = get_max_x(w);
    int maxy = get_max_y(w);
    if (x >= maxx || y >= maxy) {
        FILE_LOG(logINFO) << "Add char max x or max y overflow.";
        return;
    }
    mvwaddch(w->win, y, x, c);
}

void ncurses_screen::add_string(std::shared_ptr<window> w, int x, int y, std::string s) {
    mvwprintw(w->win, y, x, s.c_str());
}

void ncurses_screen::draw(std::shared_ptr<window> w) {
    screen_mutex.lock();
    curs_set(0);
    wrefresh(w->win);
    curs_set(1);
    screen_mutex.unlock();
}

void ncurses_screen::draw() {
    screen_mutex.lock();
    curs_set(0);
    refresh();
    curs_set(1);
    screen_mutex.unlock();
}

void ncurses_screen::set_size(std::shared_ptr<window> w, int x, int y) {
    screen_mutex.lock();
    wclear(w->win);
    wborder(w->win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(w->win);
    screen_mutex.unlock();

    draw(w);

    screen_mutex.lock();
    wresize(w->win, y, x);
    screen_mutex.unlock();

    draw(w);
}

void ncurses_screen::set_pos(std::shared_ptr<window> w, int startx, int starty) {
    screen_mutex.lock();
    wclear(w->win);
    wborder(w->win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(w->win);
    screen_mutex.unlock();

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
    screen_mutex.lock();
    endwin();
    screen_mutex.unlock();
}

void ncurses_screen::draw_border(std::shared_ptr<window> w, int chtx, int chty) {
    screen_mutex.lock();
    box(w->win, chty, chtx);
    screen_mutex.unlock();
    draw(w);
}

void ncurses_screen::delete_window(std::shared_ptr<window> w) {
    screen_mutex.lock();
    wborder(w->win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(w->win);
    delwin(w->win);
    num_wins--;
    screen_mutex.unlock();
    if (num_wins == 0) {
        exit();
        //resize.set_watch_resize_status(false);
    }
}

void ncurses_screen::resize_event::watch_resize() {
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = resize_event::sigwinch_handler;

    if (sigaction(SIGWINCH, &sa, NULL) == -1) {
        assert(0);
    }
}

void ncurses_screen::resize_event::call_listener() {
    if (!resize_mutex.try_lock()) {
        not_resize_flag.clear();
        return;
    }
    do {
        ncurses_screen::get_instance().exit();
        ncurses_screen::get_instance().draw();
        FILE_LOG(logINFO) << "Window resized.";
        this->dispatch(0);
    } while (not_resize_flag.test_and_set());
    not_resize_flag.clear();
    resize_mutex.unlock();
}

void ncurses_screen::resize_event::sigwinch_handler(int signum) {
    ncurses_screen::get_instance().resize.call_listener();
}
