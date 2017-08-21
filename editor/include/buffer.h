#ifndef BUFFER_H_
#define BUFFER_H_

#include <string>
#include <vector>
#include <fstream>
#include <cstdarg>

#include "view.h"
#include "editor.h"
#include "buffer_container.h"

class editor;

class buffer {
public:
        buffer(editor *ed, view *win, buffer_container *c);
        void open(std::string *filename);
        void refresh_screen();
        void process_key();
        std::string * get_name() {
                return name;
        }
        ~buffer();
private:
        std::string *name = nullptr; /**< Name of the buffer */
        /**  Represents one row of text. */
        struct row {
                std::string *text = nullptr; /**< Real text */
                std::string *rtext = nullptr; /**< Text that gets displayed */
        };
        std::vector<row*> rows; /**< Holds all rows for the buffer. */
        int ty = 0; /**< Y cursor position in real text file.*/
        int tx = 0; /**< X cursor position in real text file.*/
        int rx = margin_right; /**< X cursor position in the rendered text. */
        int rowoff = 0; /**< Tracks the row user is currently scrolled to. */
        int coloff = 0; /**< Tracks the column user is currently scrolled to. */
        view *win = nullptr; /**< The view to display text. */
        editor *ed = nullptr; /**< The buffers editor. */
        int margin_bot = 2;
        int margin_right = 0;
        std::string statusmsg = "Exit: Ctrl-q | Save: Ctrl-s"; /**< Global status message buffer. */
        bool buffer_changed = false; /**< Indicates if buffer text changed */
        buffer_container *container = nullptr;

        /**
         * Draws the text on the screen.
         */
        void drawrows();
        /**
         * Refreshes the cursor position.
         */
        void setcur();
        /**
         * Moves the cursor if arrow key is given.
         */
        void movcur(int key);
        /**
         * Reads one line from a stream in a string.
         */
        std::istream& get_line(std::istream &is, std::string &t);
        /**
         * Scrolls the window if necessary.
         */
        void bufscroll();
        /**
         * Updates the text to render in the row.
         */
        void update_row(row *r);
        /**
         * Converts real cursor to render cursor.
         */
        int txtorx(row *r, int tx);
        /**
         * Maximum columns to draw text.
         */
        int scrncols();
        /**
         * Maximum rows to draw text.
         */
        int scrnrows();
        /**
         * Draws a status bar.
         */
        void drawstatus();
        /**
         * Sets the status message.
         */
        void set_status_msg(const std::string &msg);
        /**
         * Insert char.
         */
        void insert_char_row(row *r, int col, char c);
        /**
         * Insert char at current position.
         * Increments cursor.
         */
        void insert_char(char c);
        /**
         * Adds a new row to the buffer.
         */
        void addrow(int y, const std::string &s);
        /**
         * Saves buffer to disk.
         */
        void save();
        /**
         * Exits the editor/buffer.
         */
        void exit();
        /**
         * Deletes char on the position.
         */
        void del_char_row(row *r, int col);
        /**
         * Deletes char on cursor position.
         */
        void del_char();
        /**
         * Deletes a row from buffer.
         */
        void delrow(int row);
        /**
         * Frees the text from a row.
         */
        void free_row(row *r);
        /**
         * Adds a string to a row.
         */
        void row_add_str(row *r, std::string &s);
        /**
         * Inserts new line at cursor position.
         */
        void insert_new_row();
        /**
         * Prompts the user for input.
         */
        std::string * prompt(const std::string &msg);
        /**
         * Draws line numbers.
         */
        void draw_linnum();
};

#endif
