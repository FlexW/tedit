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
     * Opens a textfile and loads it into the text view.
     * @param filename Name of the file to open.
     * @returns True on succes. False on failure.
     */
    bool open(std::string& filename);

    /**
     * Sets the textfield.
     * @param text Text.
     */
    void set_text(const std::string& text);

protected:
    /** Represents one row in the text view. */
    struct row {
        std::shared_ptr<std::string> text; /**< Real text */
        std::shared_ptr<std::string> rtext; /**< Text that gets displayed */
    };

    std::vector<std::shared_ptr<row>> rows; /**< Holds all rows for the view. */
    int rowoff = 0; /**< Tracks the row user is currently scrolled to. */
    int coloff = 0; /**< Tracks the column user is currently scrolled to. */

    /**
     * Reads one line from a stream in a string.
     * @param is Stream to read from.
     * @param t String to save the line.
     * @returns Stream. If Strem end then nullptr.
     */
    std::istream& get_line(std::istream& is, std::string& t);

    /**
     * Creates a new row from string.
     * @param line Text.
     * @returns Row.
     */
    std::shared_ptr<row> new_row(std::string& line);
};

#endif
