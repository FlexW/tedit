#include <thread>
#include <chrono>

#include "event/include/event.h"
#include "gtest/gtest.h"

class event_holder {
public:
    class action_event : public event<int> {
    public:
        void fire_event() {
            dispatch(1);
        }
    };

    action_event action;
};

bool listener_called = false;
void listener(int i) {
    listener_called = true;
}

bool listener2_called = false;
void listener2(int i) {
    listener2_called = true;
}

class EventTest : public ::testing::Test {
public:
    EventTest() : mlistener_called(false), mlistener2_called(false) {
        listener_called = false;
        listener2_called = false;
        this->e = new event_holder();
    }

    ~EventTest() {
        delete e;
    }

    void mlistener(int i) {
        mlistener_called = true;
    }
    void mlistener2(int i) {
        mlistener2_called = true;
    }

    event_holder *e;
    bool mlistener_called = false;
    bool mlistener2_called = false;
};

TEST_F(EventTest, AddNewFreeFuncListner) {
    e->action.add_listener<listener>();
    EXPECT_TRUE(e->action.is_registered<listener>());
}

TEST_F(EventTest, AddNewMemFuncListner) {
    e->action.add_listener<EventTest, &EventTest::mlistener>(this);
    bool b = e->action.is_registered<EventTest, &EventTest::mlistener>(this);
    EXPECT_TRUE(b);
}

TEST_F(EventTest, RemoveFreeFuncListener) {
    e->action.add_listener<listener>();
    bool b = e->action.is_registered<listener>();
    EXPECT_TRUE(b);

    e->action.remove_listener<listener>();
    b = e->action.is_registered<listener>();
    EXPECT_FALSE(b);
}


TEST_F(EventTest, RemoveMemFuncListener) {
    e->action.add_listener<EventTest, &EventTest::mlistener>(this);
    bool b = e->action.is_registered<EventTest, &EventTest::mlistener>(this);
    EXPECT_TRUE(b);

    e->action.remove_listener<EventTest, &EventTest::mlistener>(this);
    b = e->action.is_registered<EventTest, &EventTest::mlistener>(this);
    EXPECT_FALSE(b);
}

TEST_F(EventTest, DispatchFreeFunc) {
    e->action.add_listener<listener>();
    EXPECT_TRUE(e->action.is_registered<listener>());

    e->action.fire_event();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_TRUE(listener_called);
}

TEST_F(EventTest, DispatchMemFunc) {
    e->action.add_listener<EventTest, &EventTest::mlistener>(this);
    bool b = e->action.is_registered<EventTest, &EventTest::mlistener>(this);
    EXPECT_TRUE(b);

    e->action.fire_event();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_TRUE(mlistener_called);
}


TEST_F(EventTest, DispatchTwoListnerFreeFunc) {
    e->action.add_listener<listener>();
    e->action.add_listener<listener2>();
    EXPECT_TRUE(e->action.is_registered<listener>());
    EXPECT_TRUE(e->action.is_registered<listener2>());

    e->action.fire_event();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_TRUE(listener_called);
    EXPECT_TRUE(listener2_called);
}

TEST_F(EventTest, DispatchTwoListnerMemFunc) {
    e->action.add_listener<EventTest, &EventTest::mlistener>(this);
    e->action.add_listener<EventTest, &EventTest::mlistener2>(this);

    bool b = e->action.is_registered<EventTest, &EventTest::mlistener>(this);
    EXPECT_TRUE(b);
    b = e->action.is_registered<EventTest, &EventTest::mlistener2>(this);
    EXPECT_TRUE(b);

    e->action.fire_event();
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_TRUE(mlistener_called);
    EXPECT_TRUE(mlistener2_called);
}
