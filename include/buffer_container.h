#ifndef BUFFER_CONTAINER_H_
#define BUFFER_CONTAINER_H_

#include <string>
#include <vector>
#include <utility>

#include "buffer.h"
#include "editor.h"

class buffer;
class editor;

using namespace std;

class buffer_container {
public:
        buffer_container(editor *ed, view *win);
        /**
         * Opens a new buffer if not exists.
         * Returns open buffer if exists.
         */
        buffer * open_buffer(const string &name);
        /**
         * Returns the active buffer.
         */
        buffer * active();
        /**
         * Change the name of the active buffer.
         */
        void change_buffer_name(const string &name);
        /**
         * Displays the next buffer.
         */
        void next_buffer();
        /**
         * Displays the previous buffer.
         */
        void prev_buffer();
private:
        /** Stores all buffer. Uppermost is active. */
        vector<pair<string, buffer*>*> buffer_vec;
        view *win;
        editor *ed;
        int no_name_cnt = 0; /**< For unique no name file naming */

        /**
         * Searches for given buffer.
         * @returns Index if found. -1 if not.
         */
        int find(const string &name);
        /**
         * Swaps to elements in buffer_vec.
         */
        void swap(int x, int y);
};

#endif
