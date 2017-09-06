#include "view/include/view.h"
#include "gtest/gtest.h"

class ViewTest : public ::testing::Test {
public:
    ViewTest() {
            this->v = new view(0, 0, 100, 100);
    }
    ~ViewTest() {
        delete v;
    }
    view *v;
};

TEST_F(ViewTest, SetStartxLegal) {
    int legal = 10;
    v->set_startx(legal);
    ASSERT_EQ(legal, v->get_startx());
}

TEST_F(ViewTest, SetStartyLegal) {
    int legal = 10;
    v->set_starty(legal);
    ASSERT_EQ(legal, v->get_starty());
}

TEST_F(ViewTest, SetStartxIllegal) {
    int illegal = -1;
    v->set_startx(illegal);
    ASSERT_EQ(0, v->get_startx());
}

TEST_F(ViewTest, SetStartyIllegal) {
    int illegal = -1;
    v->set_starty(illegal);
    ASSERT_EQ(0, v->get_starty());
}

TEST_F(ViewTest, SetPaddingLegal) {
    int h = 100;
    int w = 100;
    int p = 50;

    v->set_height(h);
    v->set_width(w);

    v->set_padding_top(p);
    v->set_padding_bot(p);
    v->set_padding_left(p);
    v->set_padding_right(p);

    ASSERT_EQ(p, v->get_padding_top());
    ASSERT_EQ(p, v->get_padding_bot());
    ASSERT_EQ(p, v->get_padding_left());
    ASSERT_EQ(p, v->get_padding_right());
}

TEST_F(ViewTest, SetPaddingIllegal) {
    int p = 10;

    v->set_padding_top(p);
    v->set_padding_bot(p);
    v->set_padding_left(p);
    v->set_padding_right(p);

    ASSERT_EQ(0, v->get_padding_top());
    ASSERT_EQ(0, v->get_padding_bot());
    ASSERT_EQ(0, v->get_padding_left());
    ASSERT_EQ(0, v->get_padding_right());
}

TEST_F(ViewTest, SetPrintBufferSize) {
    int size = 10;

    v->set_height(size);
    v->set_width(size);

    ASSERT_EQ((size * size), v->get_print_buffer_size());
}

TEST_F(ViewTest, GetPrintBufferChar) {
    char c = 'c';
    int size = 10;
    int x = 5;
    int y = 0;

    v->set_height(size);
    v->set_width(size);

    v->add_char_print_buffer(x, y, c);
    ASSERT_EQ(c, v->get_char_print_buffer(x, y));
}

TEST_F(ViewTest, SetPaddingCheckPrintBufferResize) {
    int size = 10;

    v->set_height(size);
    v->set_width(size);

    ASSERT_EQ((size * size), v->get_print_buffer_size());

    v->set_padding_top(1);
    ASSERT_EQ(size * (size - 1), v->get_print_buffer_size());

    v->set_padding_bot(1);
    ASSERT_EQ(size * (size - 2), v->get_print_buffer_size());

    v->set_padding_left(1);
    ASSERT_EQ((size - 1) * (size - 2), v->get_print_buffer_size());

    v->set_padding_right(1);
    ASSERT_EQ((size - 2) * (size - 2), v->get_print_buffer_size());
}
