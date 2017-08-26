#include "view/include/view.h"
#include "gtest/gtest.h"

class ViewTest : public ::testing::Test {
public:
    ViewTest() {
        this->v = new view();
    }
    ~ViewTest() {
        delete v;
    }
    view *v;
};

TEST_F(ViewTest, SetMarginLegal) {
    int legal = 10;
    v->set_margin_top(legal);
    v->set_margin_bot(legal);
    v->set_margin_left(legal);
    v->set_margin_right(legal);

    ASSERT_EQ(legal, v->get_margin_top());
    ASSERT_EQ(legal, v->get_margin_bot());
    ASSERT_EQ(legal, v->get_margin_left());
    ASSERT_EQ(legal, v->get_margin_right());
}

TEST_F(ViewTest, SetMarginIllegal) {
    int illegal = -1;
    v->set_margin_top(illegal);
    v->set_margin_bot(illegal);
    v->set_margin_left(illegal);
    v->set_margin_right(illegal);

    ASSERT_EQ(0, v->get_margin_top());
    ASSERT_EQ(0, v->get_margin_bot());
    ASSERT_EQ(0, v->get_margin_left());
    ASSERT_EQ(0, v->get_margin_right());
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
