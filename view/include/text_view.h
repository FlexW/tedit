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
    /**
     * @see view::view()
     */
    text_view(int startx, int starty, int width, int height);

    virtual ~text_view();

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

    virtual void on_reset_print_buffer();

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
     std::shared_ptr<row> new_row(std::string& line) {
     }

     /**
      * Adds a row to the view.
      * @param y Index of the new row.
      * @param s Text.
      */
     void add_row(int y, const std::string &s);

     /**
      * Updates the rendered row.
      * @param r row.
      */
     void update_row(std::shared_ptr<row> r);

     /**
      * Draws the rows to screen.
      */
     void draw_rows();

     void reset_print_buffer_handler();
};

#endif
