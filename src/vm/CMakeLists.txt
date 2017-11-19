project(vm)

file(GLOB SOURCES "*.h" "*.cpp")

add_library(vm ${SOURCES})
