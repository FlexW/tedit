find_package(Curses REQUIRED)

file(GLOB SOURCES *.cpp)
set(libscreen_SRCS
  ${SOURCES}
  )

set (CMAKE_CXX_STANDARD 11)
add_library(libscreen STATIC
  ${libscreen_SRCS}
  )

target_link_libraries(libscreen ${CURSES_LIBRARIES})

add_subdirectory(unit-tests)
