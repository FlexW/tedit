#include <iostream>
#include "view/include/text_view.h"
#include "gtest/gtest.h"

class TextViewTest : public ::testing::Test {
public:
    TextViewTest() {
        this->v = new text_view();
    }
    ~TextViewTest() {
        delete v;
    }
    text_view *v;
};

TEST_F(TextViewTest, SetPaddingLegal) {
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

TEST_F(TextViewTest, SetPaddingIllegal) {
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
