set(Main_SRCS
    main.cpp
)

set (CMAKE_CXX_STANDARD 11)
add_executable(tedit
    ${Main_SRCS}
    )

# Specify here the libraries this program depends on
target_link_libraries(tedit
    libeditor
)

include_directories(${tedit_SOURCE_DIR})

install(TARGETS tedit DESTINATION bin)
