#ifndef TEXTBUFFER_H_
#define TEXTBUFFER_H_

#include "textview.h"

class textbuffer : public textview {
protected:
    int ty = 0; /**< Y cursor position in real text file.*/
    int tx = 0; /**< X cursor position in real text file.*/
    int rx = margin_right; /**< X cursor position in the rendered text. */
};

#endif
