cmake_minimum_required(VERSION 2.6)
project(sfml_tut)

# Set version information
set(${PROJECT_BINARY_DIR}_VERSION_MAJOR 1)
set(${PROJECT_BINARY_DIR}_VERSION_MINOR 0)

# Define sources and executable
set(EXECUTABLE_NAME "${PROJECT_NAME}")
add_executable(${EXECUTABLE_NAME} main.cc)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5 REQUIRED system window graphics network audio)
target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)

# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_BINARY_DIR}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_BINARY_DIR}_VERSION_MINOR}")
include(CPack)

