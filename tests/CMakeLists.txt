enable_testing()

include(gtest.cmake)

file(GLOB SRCS vm/*.cpp)

add_executable(tests ${SRCS})

target_link_libraries(tests vm gtest_main)

add_test(tests tests)
