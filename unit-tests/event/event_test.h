#ifndef EVENT_TEST_H_
#define EVENT_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include "../event.h"

class event_test : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(event_test);
    CPPUNIT_TEST(test_add_event_listner_new);
    CPPUNIT_TEST(test_remove_event_listner_available);
    CPPUNIT_TEST(test_dispatch_event);
    CPPUNIT_TEST_SUITE_END();

public:
    void set_up();
    void tear_down();
    void test_add_event_listner_new();
    void test_remove_event_listner_available();
    void test_dispatch_event();
private:
    event *e;
};

#endif
