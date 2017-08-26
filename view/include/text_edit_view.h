#ifndef TEXT_EDIT_VIEW_H_
#define TEXT_EDIT_VIEW_H_

#include "text_view.h"

/**
 * Displays text.
 * Text in a text buffer is editable. It is possible to save changes.
 */
class text_edit_view : public text_view {
public:
protected:
    int ty = 0; /**< Y cursor position in real text file.*/
    int tx = 0; /**< X cursor position in real text file.*/
    int rx = margin_right; /**< X cursor position in the rendered text. */
};

#endif
