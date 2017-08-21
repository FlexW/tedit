#include <string>
#include <cstdlib>
#include <fstream>
#include <chrono>
#include <thread>

extern "C" {
        #include <ncurses.h>
}

#include "include/buffer.h"
#include "include/log.h"

#define WHITE_BLACK 1
#define BLACK_WHITE 2
#define RED_BLACK 3

buffer::buffer(editor *ed, view *win, buffer_container *c) {
    this->ed = ed;
    this->win = win;
    this->container = c;
    start_color();
    init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(BLACK_WHITE, COLOR_BLACK, COLOR_WHITE);
    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
}

buffer::~buffer() {
        for (row *r : rows) {
            free_row(r);
        }
        rows.clear();
        if (name != nullptr)
                free(name);
}

void buffer::open(std::string *filename) {
        std::ifstream *file = new std::ifstream(*filename);
        if (!file)
                return;
        std::string line;
        while (!get_line(*file, line).eof()) {
            addrow(rows.size(), line);
        }
        this->name = new std::string(*filename);
}

void buffer::refresh_screen() {
    win->clearscrn();
    bufscroll();
    draw_linnum();
    drawrows();
    drawstatus();
    win->display();
    setcur();
}

void buffer::process_key() {
        int key = win->getchar();
        FILE_LOG(logINFO) << "Key pressed: " << key;
        set_status_msg("");
        switch (key) {
        case 14: /* ctrl-n */
            container->next_buffer();
            break;
        case 16: /* ctrl-p */
            container->prev_buffer();
            break;
        case 15: /* ctrl-o */ {
            std::string *f = prompt("Filename: ");
            if (f == nullptr)
                return;
            ed->open(f);
        }
            break;

        case 17: /* ctrl-q */
            exit();
            break;

        case 19: /* ctrl-s */
            save();

        case KEY_UP:
        case KEY_DOWN:
        case KEY_LEFT:
        case KEY_RIGHT:
                movcur(key);
                break;

        case KEY_PPAGE:
        case KEY_NPAGE: {
                if (key == KEY_PPAGE) {
                        ty = rowoff;
                } else if (key == KEY_NPAGE) {
                    ty = rowoff + scrnrows();//win->winrows();
                        if (ty > rows.size() - 1)
                                ty = rows.size() - 1;
                }
                int times = scrnrows();//win->winrows();
                while (times-- != 0)
                        movcur(key == KEY_PPAGE ? KEY_UP : KEY_DOWN);
        }
                break;
        case 263: /* Backspace */
            del_char();
            break;
        case 330: /* Del */
            movcur(KEY_RIGHT);
            del_char();
            break;
        case '\r':
            insert_new_row();
            break;
        default:
            if(isprint(key) || key == '\t')
                insert_char(key);
        }
}

void buffer::drawrows() {
    int maxrow = scrnrows();//win->winrows();
    int maxcol = scrncols();//win->wincols();
    int bufsize = rows.size();
    for (int y = 0; y < maxrow; y++) {
        int filerow = y + rowoff;
        if (filerow >= bufsize)
            return;
        int rowlen = rows[filerow]->rtext->length() - coloff;
        int x = 0;
        for (; x < maxcol && x < rowlen; x++) {
            win->addchar(y,
                         x + margin_right,
                         (*rows[filerow]->rtext)[x + coloff]);
        }
    }
}

void buffer::setcur() {
        win->setcurpos(ty - rowoff, rx - coloff + margin_right);
}

void buffer::movcur(int key) {
        row *r = (ty >= rows.size()) ? nullptr : rows[ty];
        switch (key) {
        case KEY_LEFT:
                if (tx != 0) {
                        tx--;
                } else if (ty > 0) {
                        ty--;
                        tx = rows[ty]->text->length();
                }
                break;
        case KEY_RIGHT:
                if (r != nullptr && tx < r->text->length()) {
                        tx++;
                } else if (r != nullptr && tx == r->text->length()
                           && ty < rows.size() - 1) {
                        ty++;
                        tx = 0;
                }
                break;
        case KEY_UP:
                if (ty != 0)
                        ty--;
                break;
        case KEY_DOWN:
                if (ty < rows.size() - 1)
                        ty++;
                break;
        }
        r = (ty >= rows.size()) ? nullptr : rows[ty];
        int rowlen = r ? r->text->length() : 0;
        if (tx > rowlen)
                tx = rowlen;
}

std::istream& buffer::get_line(std::istream &is, std::string &t) {
    t.clear();
    std::istream::sentry se(is, true);
    std::streambuf* sb = is.rdbuf();

    for (;;) {
        int c = sb->sbumpc();
        switch (c) {
        case '\n':
            //t += (char)c;
            return is;
        case '\r':
            if(sb->sgetc() == '\n')
                sb->sbumpc();
            //t += '\n';
            return is;
        case EOF:
            // Also handle the case when the last line has no line ending
            if(t.empty())
                is.setstate(std::ios::eofbit);
            return is;
        default:
            t += (char)c;
        }
    }
}

void buffer::bufscroll() {
    int maxrow = scrnrows();//win->winrows();
    int maxcol = scrncols();//win->wincols();
    rx = 0;
    if (ty < rows.size())
        rx = txtorx(rows[ty], tx);
    if (ty < rowoff)
        rowoff = ty;
    if (ty >= rowoff + maxrow)
        rowoff = ty - maxrow + 1;
    if (rx < coloff) {
        coloff = rx;
    }
    if (rx >= coloff + maxcol) {
        coloff = rx - maxcol + 1;
    }
}

void buffer::update_row(row *r) {
        if (r->rtext != nullptr)
                free(r->rtext);
        int tlen = r->text->length();
        std::string *ntext = new std::string(*r->text);
        for (int i = 0, j = 0; i < tlen; i++, j++) {
                if ((*r->text)[i] == '\t') {
                        int tabfeed = TABSIZE - (i % TABSIZE);
                        ntext->insert(i, tabfeed, ' ');
                        j += tabfeed;
                }
        }
        r->rtext = ntext;
}

int buffer::txtorx(row *r, int tx) {
        int rx = 0;
        for (int i = 0; i < tx; i++) {
                if ((*r->text)[i] == '\t')
                        rx += (TABSIZE) - (i % TABSIZE);
                rx++;
        }
        return rx;
}

int buffer::scrncols() {
    return win->wincols();
}

int buffer::scrnrows() {
    return win->winrows() - margin_bot;
}

void buffer::drawstatus() {
    int y = win->winrows() - 2;
    attron(COLOR_PAIR(BLACK_WHITE));
    for (int x = 0; x < win->wincols(); x++) {
        win->addchar(y, x, ' ');
    }
    std::string status = std::to_string((ty + 1)) + "|" + std::to_string((tx + 1)) + "  ";
    if (name != nullptr) {
           status += *name;
           if (buffer_changed)
               status += "*";
    }
    win->addstring(y, 3, status);
    attroff(COLOR_PAIR(BLACK_WHITE));
    attron(COLOR_PAIR(RED_BLACK));
    win->addstring(y + 1, 3, statusmsg);
    attroff(COLOR_PAIR(RED_BLACK));
}

void buffer::set_status_msg(const std::string &msg) {
    statusmsg = msg;
    refresh_screen();
}

void buffer::insert_char_row(row *r, int col, char c) {
    if (col < 0 || col > r->text->length())
        col = r->text->length();
    r->text->insert(col, 1, c);
    buffer_changed = true;
    update_row(r);
}

void buffer::insert_char(char c) {
    if (rows.size() == 0)
        addrow(rows.size(), "");
    insert_char_row(rows[ty], tx, c);
    tx++;
}

void  buffer::addrow(int y, const std::string &s) {
    if (y < 0 || y > rows.size())
        return;
    row *r = (row*)std::malloc(sizeof(*r));
    if (r == NULL) {
        std::exit(1);
    }
    r->text = new std::string(s);
    r->rtext = nullptr;
    update_row(r);
    rows.insert(rows.begin() + y, r);
}

void buffer::save() {
    if (name == nullptr) {
        name = prompt("Save file as: ");
        if (name == nullptr)
            return;
        container->change_buffer_name(*name);
    }
    if (buffer_changed && (*name)[name->length() - 1] == '*')
        name->pop_back();
    std::ofstream file(*name);
    if (file.is_open()) {
        for (row *r : rows) {
            file << (*r->text + "\n");
        }
        file.close();
        buffer_changed = false;
        return;
    }
    set_status_msg("Saving file failed!");
    }

void buffer::exit() {
    if (buffer_changed) {
        while (true) {
            set_status_msg("Buffer is modified. Save? [y]es [n]o [c]ontinue");
            switch (win->getchar()) {
            case 'y':
                save();
                ed->exit();
                break;
            case 'c':
                set_status_msg("");
                return;
            break;
            case 'n':
                ed->exit();
            break;
            default:
                set_status_msg("");
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
    }
    ed->exit();
}

void buffer::del_char_row(row *r, int col) {
    if (col < 0 || col >= r->text->length())
        return;
    r->text->erase(col, 1);
    update_row(r);
    buffer_changed = true;
}

void buffer::del_char() {
    if (ty == rows.size() || (tx == 0 && ty == 0))
        return;
    if (tx > 0) {
        del_char_row(rows[ty], tx - 1);
        tx--;
        return;
    }
    tx = rows[ty - 1]->text->length();
    row_add_str(rows[ty - 1], *rows[ty]->text);
    delrow(ty);
    ty--;
}

void buffer::delrow(int row) {
    if (row < 0 || row >= rows.size())
        return;
    free_row(rows[row]);
    rows.erase(rows.begin() + row);
    buffer_changed = true;
}

void buffer::free_row(row *r) {
    free(r->text);
    free(r->rtext);
}

void buffer::row_add_str(row *r, std::string &s) {
    *r->text += s;
    update_row(r);
}

void buffer::insert_new_row() {
    if (tx == 0) {
        addrow(ty, "");
    } else if (tx == rows[ty]->text->length()) {
        addrow(ty + 1, "");
    } else {
        std::string *s = rows[ty]->text;
        addrow(ty + 1, s->substr(tx));
        s->erase(s->begin() + tx, s->end());
        update_row(rows[ty]);
    }
    buffer_changed = true;
    ty++;
    tx = 0;
}

std::string * buffer::prompt(const std::string &msg) {
    std::string *answ = new std::string();
    while (true) {
        set_status_msg(msg + *answ);
        int key = win->getchar();
        if (key == '\r' && answ->length() != 0) {
            set_status_msg("");
            return answ;
        } else if (key == 27) /* esc */ {
            set_status_msg("Save aborted");
            return nullptr;
        } else if (isprint(key) || key == '\t') {
            *answ += key;
        }
    }
}

void buffer::draw_linnum() {
    int maxrow = scrnrows() + rowoff;
    int maxlinum = maxrow + 1;
    margin_right = 1;
    for (int i = 0; maxlinum != 0; i++) {
        maxlinum /= 10;
        margin_right++;
    }
    attron(COLOR_PAIR(BLACK_WHITE));
    for (int y = 0; y < maxrow - rowoff; y++) {
        int linnum = y + rowoff + 1;
        for (int x = margin_right - 1; x >= 0; x--) {
            int c;
            if (x == margin_right - 1) {
                c = ' ';
            } else if (linnum != 0) {
                c = (linnum % 10) + 48;
                linnum /= 10;
            } else {
                c = ' ';
            }
            win->addchar(y, x, c);
        }
    }
    attroff(COLOR_PAIR(BLACK_WHITE));
}
