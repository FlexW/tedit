#ifndef SCREEN_H_
#define SCREEN_H_

#include <memory>

template<class T>
class my_screen {
public:
    virtual ~my_screen() {}
    virtual int get_max_x() = 0;
    virtual int get_max_y() = 0;
    virtual void add_char(std::shared_ptr<T> w, int x, int y, char c) = 0;
    virtual void add_string(std::shared_ptr<T> w, int x, int y, std::string s) = 0;
    virtual void draw(std::shared_ptr<T> w) = 0;
    virtual void draw() = 0;
    virtual void set_size(std::shared_ptr<T> w, int x, int y) = 0;
    virtual void set_pos(std::shared_ptr<T> w, int startx, int starty) = 0;
    virtual std::shared_ptr<T> new_window(int startx, int starty, int x, int y) = 0;
    virtual void init() = 0;
    virtual void exit() = 0;
};

#endif
