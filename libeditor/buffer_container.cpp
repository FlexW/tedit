#include <string>

#include "include/buffer_container.h"
#include "include/log.h"

buffer_container::buffer_container(editor *ed, view *win) {
        this->ed = ed;
        this->win = win;
}

buffer * buffer_container::open_buffer(const std::string &name) {
        auto ibuf = find(name);
        if (ibuf == -1) {
                buffer *buf = new buffer(ed, win, this);
                if (name == "") {
                        no_name_cnt++;
                        auto *p = new pair<string, buffer*>(
                                "noname" + to_string(no_name_cnt),
                                buf);
                        buffer_vec.insert(buffer_vec.begin(), p);
                        FILE_LOG(logINFO) << "Insert no name buffer";
                } else {
                        buf->open(new string(name));
                        auto *p = new pair<string, buffer*>(name, buf);
                        buffer_vec.insert(buffer_vec.begin(), p);
                }
                FILE_LOG(logINFO) << "New buffer " << name;
                return (*buffer_vec.begin())->second;
        }
        swap(ibuf, 0);
        FILE_LOG(logINFO) << "Changed buffer " << name;
        return (*buffer_vec.begin())->second;
}

buffer * buffer_container::active() {
        if (buffer_vec.size() == 0) {
                return nullptr;
        }
        FILE_LOG(logINFO) << "Active buffer "
                          << (*buffer_vec.begin())->first;
        return (*buffer_vec.begin())->second;
}

void buffer_container::change_buffer_name(const std::string &name) {
        FILE_LOG(logINFO) << "Change buffer name: " << name;
        if (buffer_vec.size() == 0)
                return;
        buffer_vec[0]->first = name;
}

int buffer_container::find(const string &name) {
        int len = buffer_vec.size();
        for (int i = 0; i < len; i++) {
                if (buffer_vec[i]->first == name)
                        return i;
        }
        return -1;
}

void buffer_container::next_buffer() {
        int size = buffer_vec.size();
        for (int i = 0; i < size; i++) {
                swap(i, size - 1);
        }
}

void buffer_container::prev_buffer() {
        int size = buffer_vec.size();
        for (int i = size - 1; i > 0; i--) {
                swap(0, i);
        }
}

void buffer_container::swap(int x, int y) {
        auto tmp = buffer_vec[x];
        buffer_vec[x] = buffer_vec[y];
        buffer_vec[y] = tmp;
}
