#!/bin/bash
g++ main.cpp ../view.cpp ../text_view.cpp ../../event/include/event.h ../../screen/ncurses_screen.cpp -I../../ -lncurses -pthread
