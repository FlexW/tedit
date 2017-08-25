find_package(Threads REQUIRED)

file(GLOB SOURCES *.cpp)
set(libevent_SRCS
  ${SOURCES}
  )
set(SOURCES
  ${SOURCES}
  ${CMAKE_CURRENT_SOURCE_DIR/event.h}
  )

set (CMAKE_CXX_STANDARD 11)
add_library(libevent STATIC
  ${libevent_SRCS}
  )

set_target_properties(libevent PROPERTIES LINKER_LANGUAGE CXX)

if(THREADS_HAVE_PTHREAD_ARG)
  target_compile_options(libevent PUBLIC "-pthread")
endif()
if(CMAKE_THREAD_LIBS_INIT)
  target_link_libraries(libevent "${CMAKE_THREAD_LIBS_INIT}")
endif()

include_directories(${tedit_SOURCE_DIR})

add_subdirectory(unit-tests)
