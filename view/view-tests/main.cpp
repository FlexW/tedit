#include <iostream>
#include <chrono>
#include <thread>

#include "include/log.h"
#include "../include/text_view.h"

void init_logging() {
    char name[] = "a.out.log";
    remove (name);
    FILE* file = fopen(name, "a");
    Output2FILE::Stream() = file;
    //Log<Output2FILE>::FromString("DEBUG");
    FILE_LOG(logINFO) << "Logger initialized";
}

void open_views(std::string& s, std::string& s2) {
    text_view tv(0, 0, 50, 50);
    text_view tv2(50, 0, 50, 50);
    text_view tv3(0, 50, 50, 50);
    text_view tv4(50, 50, 50, 50);
    tv.open(s);
    tv2.open(s2);
    tv3.open(s2);
    tv4.open(s);
    //std::this_thread::sleep_for(std::chrono::seconds(15));
    while(getchar() != 'q') {
      ;
    }
    tv.delete_view();
    tv2.delete_view();
    tv3.delete_view();
    tv4.delete_view();
}

int main(int argc, char *argv[]) {
    init_logging();
    if(argc != 3)
        return 1;
    char *c = argv[1];
    std::string s(c);
    c = argv[2];
    std::string s2(c);
    open_views(s, s2);
    return 0;
}
