#include <chrono>
#include <thread>
#include <memory>

#include "../include/screen.h"

int main(int argc, char *argv[])
{
    screen scr;

    scr.init();
    int x = scr.get_max_x();
    int y = scr.get_max_y();

    int winx = x / 2;
    auto win1 = scr.new_window(0, 0, winx, y);
    auto win2 = scr.new_window(winx, 0, winx, y);
    scr.draw_border(win1, 0, 0);
    scr.draw_border(win2, 0, 0);
    scr.draw(win1);
    scr.draw(win2);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    scr.exit();

    return 0;
}
