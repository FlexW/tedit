#include <fstream>

#include "include/log.h"
#include "include/text_view.h"

text_view::text_view(int startx, int starty, int width, int height) :
        view(startx, starty, width, height) {
}

text_view::~text_view() {
}

bool text_view::open(std::string& filename) {
    std::ifstream *file = new std::ifstream(filename);
    if (!file)
            return false;
    std::string line;
    while (!get_line(*file, line).eof()) {
        add_row(rows.size(), line);
    }
    //set_name(filename);
    draw_rows();
    file->close();
    free(file);
    set_print_buffer_reset_handler(&view::on_reset_print_buffer);
    return true;
}

void text_view::set_text(const std::string& text) {
}

std::istream& text_view::get_line(std::istream& is, std::string& t) {
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

void text_view::add_row(int y, const std::string &s) {
    if (y < 0 || y > rows.size())
        return;
    auto r = std::make_shared<row>();
    r->text = std::make_shared<std::string>(s);
    update_row(r);
    rows.insert(rows.begin() + y, r);
}

void text_view::update_row(std::shared_ptr<row> r) {
    int tlen = r->text->length();
    auto ntext = std::make_shared<std::string>(*r->text);
    for (int i = 0, j = 0; i < tlen; i++, j++) {
        if ((*r->text)[i] == '\t') {
            int tabfeed = TABSIZE - (i % TABSIZE);
            ntext->insert(i, tabfeed, ' ');
            j += tabfeed;
        }
    }
    r->rtext = ntext;
}

void text_view::draw_rows() {
    int h = get_print_buffer_height();
    int w = get_print_buffer_width();
    int rs = rows.size();

    for (int i = 0; i < h && i < rs; i++) {
        int rw = rows[i]->rtext->length();
        for(int j = 0; j < w && j < rw; j++) {
            add_char_print_buffer(j, i, rows[i]->rtext->at(j));
        }
    }
    FILE_LOG(logINFO) << "Draw rows.";
    draw();
}

void text_view::on_reset_print_buffer() {
    FILE_LOG(logINFO) << "On reset print buffer called.";
    draw_rows();
}
