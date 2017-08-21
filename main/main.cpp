#include "editor/include/editor.h"
#include "editor/include/log.h"

void init_logging() {
    remove ("~/.tedit.log");
    //remove ("tedit.log");
    FILE* file = fopen("~/.tedit.log", "a");
    //FILE* file = fopen("tedit.log", "a");
    Output2FILE::Stream() = file;
    FILE_LOG(logINFO) << "Logger initialized";
}

int main(int argc, char *argv[])
{
        init_logging();
        editor e;
        e.init();
        if (argc == 2)
                e.open(new std::string(argv[1]));
        e.run();
        return 0;
}
