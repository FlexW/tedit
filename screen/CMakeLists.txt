file(GLOB SOURCES *.cpp)
set(libscreen_SRCS
  ${SOURCES}
  )

set (CMAKE_CXX_STANDARD 11)
add_library(libscreen STATIC
  ${libscreen_SRCS}
  )

add_subdirectory(unit-tests)
