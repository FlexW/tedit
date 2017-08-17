find_package(Curses REQUIRED)

file(GLOB SOURCES *.cpp)
set(libeditor_SRCS
  ${SOURCES}
)

# Declare the library
set (CMAKE_CXX_STANDARD 11)
add_library(libeditor STATIC
  ${libeditor_SRCS}
  )

target_link_libraries(libeditor ${CURSES_LIBRARIES})

include_directories(${tedit_SOURCE_DIR})
include_directories(${CURSES_INCLUDE_DIR})
