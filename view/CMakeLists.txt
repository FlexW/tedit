file(GLOB SOURCES *.cpp)
set(libview_SRCS
  ${SOURCES}
  )

set (CMAKE_CXX_STANDARD 11)
add_library(libview STATIC
  ${libview_SRCS}
  )

add_subdirectory(unit-tests)
