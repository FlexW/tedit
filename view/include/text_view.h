#ifndef TEXTVIEW_H_
#define TEXTVIEW_H_

#include <string>
#include <vector>

#include "view.h"
#include "event/include/event.h"

/**
 * A text view is a view that can display text and it is possible to
 * scroll trough the text. The text is not editable.
 */
class text_view : public view {
public:
    text_view();
    ~text_view();

    class view_changed : public event<int> {
    };

    /**
     * Sets the padding of the view on top side.
     */
    void set_padding_top(int p);

    /**
     * Sets the padding of the view on bottom side.
     */
    void set_padding_bot(int p);

    /**
     * Sets the padding of the view on left side.
     */
    void set_padding_left(int p);

    /**
     * Sets the padding of the view on right side.
     */
    void set_padding_right(int p);

    /**
     * Returns the padding on top side.
     * @returns Padding top.
     */
    int get_padding_top() {
        return padding_top;
    }

    /**
     * Returns the padding on bottom side.
     * @returns Padding bottom.
     */
    int get_padding_bot() {
        return padding_bot;
    }

    /**
     * Returns the padding on left side.
     * @returns Padding left.
     */
    int get_padding_left() {
        return padding_left;
    }

    /**
     * Returns the padding on right side.
     * @returns Padding right.
     */
    int get_padding_right() {
        return padding_right;
    }

protected:
    struct row {
        std::string *text = nullptr; /**< Real text */
        std::string *rtext = nullptr; /**< Text that gets displayed */
    };
    std::vector<row*> rows; /**< Holds all rows for the view. */
    int rowoff = 0; /**< Tracks the row user is currently scrolled to. */
    int coloff = 0; /**< Tracks the column user is currently scrolled to. */

    int padding_top = 0;
    int padding_bot = 0;
    int padding_left = 0;
    int padding_right = 0;

    /** Representation of the view in memory. */
    char *print_buffer = nullptr;

    /**
     * Corrects the height and width of the print buffer.
     * Clears all values.
     */
    void reset_print_buffer();

    /**
     * Adds a char to the views print buffer.
     * @param X Position.
     * @param Y Position.
     * @param c Char.
     */
    void add_char_print_buffer(int x, int y, char c);
};

#endif
