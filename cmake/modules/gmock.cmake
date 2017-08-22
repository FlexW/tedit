# Download and compile Google Test and Google Mock
# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
  gtest
  URL https://github.com/google/googletest/archive/master.zip
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
  # Disable install step
  INSTALL_COMMAND ""
  )

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
  "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
  "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
  )

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
  "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
  "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
  )

# Create libgtest_main target to be uses as a dependency by test programs
add_library(libgtest_main IMPORTED STATIC GLOBAL)
add_dependencies(libgtest_main gtest)
# Set properties
set_target_properties(libgtest_main PROPERTIES
  "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest_main.a"
  "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
  )

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
  "${source_dir}/googlemock/include")

# add_gmock_test(<target> <sources>...)
#
#  Adds a Google Mock based test executable, <target>, built from <sources> and
#  adds the test so that CTest will run it. Both the executable and the test
#  will be named <target>.
#
function(add_gmock_test target)
  add_executable(${target} ${ARGN})
  target_link_libraries(${target} libgmock libgtest libgtest_main)

  add_test(${target} ${target})
endfunction()
