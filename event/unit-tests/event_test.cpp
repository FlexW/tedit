#include <thread>
#include <chrono>

#include "event/include/event.h"
#include "gtest/gtest.h"

class event_producer : public event {
public:
     const event_type EVENT1 = "event1";
    void fire_event(event_type &e) {
        dispatch_event(e, nullptr);
    }
};

bool listner_called = false;
void listner(event_type &e, void *d) {
    listner_called = true;
}

class EventTest : public ::testing::Test {
public:
    EventTest() {
        listner_called = false;
        e = new event_producer();
    }

    ~EventTest() {
        delete e;
    }

    event_producer *e;
};

TEST_F(EventTest, AddNewEventListner) {
    e->add_event_listner(e->EVENT1, &listner);
    EXPECT_TRUE(e->is_registered(e->EVENT1, &listner));
}

TEST_F(EventTest, RemoveAvailableEventListner) {
    e->add_event_listner(e->EVENT1, &listner);
    EXPECT_TRUE(e->is_registered(e->EVENT1, &listner));

    e->remove_event_listner(e->EVENT1, &listner);
    EXPECT_FALSE(e->is_registered(e->EVENT1, &listner));
}

TEST_F(EventTest, DispatchEvent) {
    e->add_event_listner(e->EVENT1, &listner);
    EXPECT_TRUE(e->is_registered(e->EVENT1, &listner));

    e->fire_event(e->EVENT1);
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
    EXPECT_TRUE(listner_called);
}
