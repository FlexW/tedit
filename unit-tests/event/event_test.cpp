#include <thread>
#include <chrono>

#include "event_test.h"

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(event_test);

event_type event1 = "event1";
bool was_event = false;

void event_test::set_up()
{
    e = new event();
    was_event = false;
}


void event_test::tear_down()
{
    delete e;
    was_event = false;
}

void taddlistner(event_type &e, void *d) {
    was_event = true;
}

void event_test::test_add_event_listner_new()
{
    set_up();
    e->add_event_listner(event1, &taddlistner);
    CPPUNIT_ASSERT(true == e->is_registered(event1, &taddlistner));
    tear_down();
}

void event_test::test_remove_event_listner_available() {
    set_up();
    e->add_event_listner(event1, &taddlistner);
    e->remove_event_listner(event1, &taddlistner);
    CPPUNIT_ASSERT(false == e->is_registered(event1, &taddlistner));
    tear_down();
}

void event_test::test_dispatch_event() {
    set_up();
    e->add_event_listner(event1, &taddlistner);
    e->dispatch_event(event1, nullptr);
    std::this_thread::sleep_for(std::chrono::milliseconds(5));
    CPPUNIT_ASSERT(true == was_event);
    tear_down();
}
