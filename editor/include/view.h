#ifndef VIEW_H_
#define VIEW_H_

#include <string>

extern "C" {
        #include <ncurses.h>
}

class view {
public:
        /**
         * Initializes terminal.
         * Sets terminal in raw mode.
         */
        void init();
        /**
         * Unset raw mode.
         */
        void exit();
        /**
         * Gets a key press from the user.
         */
        int getchar();
        /**
         * Maximum number of available columns.
         */
        int wincols();
        /**
         * Maximum number of available rows.
         */
        int winrows();
        /**
         * Add char to print buffer.
         */
        void addchar(int row, int col, char c);
        /**
         * Displays the print buffer.
         */
        void display();
        /**
         * Sets the cursor position.
         */
        void setcurpos(int row, int col);
        /**
         * Clears the complete screen.
         */
        void clearscrn();
        /**
         * Adds string to print buffer.
         */
        void addstring(int row, int col, std::string &str);
        /**
         * Clears till end of line.
         */
        void clreol(int row, int col);
    /**
     * Creates a new window.
     */
    WINDOW * create_win(int rows, int cols, int parentx, int parenty);
};
#endif
