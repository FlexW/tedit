#ifndef VIEW_CONTAINER_H_
#define VIEW_CONTAINER_H_

#include <string>
#include <memory>
#include <vector>
#include <utility>

#include "event/include/event.h"
#include "view/include/view.h"

/**
 * Manages open and closing of views. Stores all views.
 * Handles switching between views.
 */
class view_container {
public:
    /**
     * Fires a event if a view gets closed in the container.
     * Index of the closed view will be transmitted.
     */
    class view_closed : public event<int> {};
    view_closed view_closed;
    /**
     * Creates a new view. If a view with given name exists,
     * it returns the view.
     * @param name Name of the view.
     * @returns view.
     */
    std::shared_ptr<view> open_view(const std::string &name) {
    }

    /**
     * Gets a buffer by their index.
     */
    std::shared_ptr<view> get_buffer(int index) {}

    /**
     * Changes focus to the next view.
     */
    void next_view();

    /**
     * Changes focus to the previous view.
     */
    void previous_view();

    /**
     * Closes a view in the container.
     * If successfull, it will fire the view_closed event.
     */
    void close_view();

private:
    /**
     * Stores all open views. Sorted after open time. Newest will be
     * at the highest index.
     */
    std::vector<std::pair<std::string, std::shared_ptr<view>>> view_vec;
};

#endif
