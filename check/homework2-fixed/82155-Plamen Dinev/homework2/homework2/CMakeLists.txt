cmake_minimum_required(VERSION 3.11)

project(homework2)
include(cmake/StandardProjectSettings.cmake)
include(cmake/PreventInSourceBuilds.cmake)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

  # Let's nicely support folders in IDEs
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)

  # Testing only available if this is the main app
  # Note this needs to be done in the main CMakeLists
  # since it calls enable_testing, which must be in the
  # main CMakeLists.
  include(CTest)

endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)
# FetchContent_MakeAvailable was not added until CMake 3.14; use our shim
if(${CMAKE_VERSION} VERSION_LESS 3.14)
  include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

include(cmake/CompilerWarnings.cmake)

# sanitizer options if supported by compiler
include(cmake/Sanitizers.cmake)

# allow for static analysis options
include(cmake/StaticAnalyzers.cmake)


add_subdirectory(src)

add_subdirectory(app)

# Testing only available if this is the main app
# Emergency override HOMEWORK1_BUILD_TESTING provided as well
if((CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME OR HOMEWORK1_BUILD_TESTING)
   AND BUILD_TESTING)
  add_subdirectory(tests)
endif()
