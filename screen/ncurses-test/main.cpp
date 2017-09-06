#include <chrono>
#include <thread>
#include <memory>

#include "../include/ncurses_screen.h"

int main(int argc, char *argv[])
{
    std::shared_ptr<ncurses_screen> scr;
    scr = ncurses_screen::get_instance();

    int x = scr->get_max_x() - 2;
    int y = scr->get_max_y() - 2;

    int winx = x / 2;
    auto win1 = scr->new_window(0, 0, winx, y);
    auto win2 = scr->new_window(winx, 0, winx, y);
    scr->draw_border(win1, 0, 0);
    scr->draw_border(win2, 0, 0);
    scr->add_string(win1, 3, 3, "hello");
    scr->draw(win1);
    scr->draw(win2);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    scr->set_size(win1, winx / 2, y / 2);
    scr->add_string(win1, 4, 4, "hello");
    scr->draw_border(win1, 0, 0);
    scr->draw(win1);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    scr->set_pos(win1, 4, 4);
    scr->add_string(win1, 3, 3, "hello");
    scr->draw_border(win1, 0, 0);
    scr->draw(win1);

    std::this_thread::sleep_for(std::chrono::seconds(3));

    scr->exit();

    return 0;
}
