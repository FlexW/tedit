#include <iostream>
#include <chrono>
#include <thread>

#include "../include/text_view.h"

void func() {
        std::string s;
        std::cin >> s;
}

void func2(std::string& s) {
    text_view tv(0, 0, 49, 100);
    text_view tv2(51, 0, 50, 100);
    tv.open(s);
    tv2.open(s);
    //std::this_thread::sleep_for(std::chrono::seconds(15));
    while(true) {
      ;
    }
    tv.delete_view();
    tv2.delete_view();
}

int main(int argc, char *argv[])
{
    func();
    if(argc != 2)
        return 1;
    char *c = argv[1];
    std::string s(c);
    func2(s);
    return 0;
}
