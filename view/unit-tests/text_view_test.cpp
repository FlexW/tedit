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

TEST_F(TextViewTest, bla) {
        ASSERT_EQ(1, 1);
}
