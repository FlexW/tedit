file(GLOB SOURCES *.cpp)
set(libview_SRCS
  ${SOURCES}
  )

set (CMAKE_CXX_STANDARD 11)
add_library(libview STATIC
  ${libview_SRCS}
  )

target_link_libraries(libview libscreen)

add_subdirectory(unit-tests)
