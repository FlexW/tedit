#ifndef TEXTVIEW_H_
#define TEXTVIEW_H_

#include <string>
#include <vector>

class textview {
public:
    textview() {}
    ~textview() {}
protected:
    struct row {
        std::string *text = nullptr; /**< Real text */
        std::string *rtext = nullptr; /**< Text that gets displayed */
    };
    std::vector<row*> rows; /**< Holds all rows for the view. */
    int rowoff = 0; /**< Tracks the row user is currently scrolled to. */
    int coloff = 0; /**< Tracks the column user is currently scrolled to. */

    int margin_top = 0;
    int margin_bot = 0;
    int margin_left = 0;
    int margin_right = 0;

    int padding_top = 0;
    int padding_bot = 0;
    int padding_left = 0;
    int padding_right = 0;
};

#endif
