set(TEST_FILES
    LZWTest.cpp
    test_main.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/googletest/googletest/include)
include_directories(${CMAKE_SOURCE_DIR}/googlemock/googlemock/include)

set(SRC_FILES
    ${CMAKE_SOURCE_DIR}/src/LZW.cpp
)

add_executable(LZWTests ${TEST_FILES} ${SRC_FILES})

set_target_properties(LZWTests PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_link_libraries(LZWTests
    ${CMAKE_SOURCE_DIR}/googletest/lib/libgtest.a
    ${CMAKE_SOURCE_DIR}/googletest/lib/libgtest_main.a
    ${CMAKE_SOURCE_DIR}/googletest/lib/libgmock.a
    ${CMAKE_SOURCE_DIR}/googletest/lib/libgmock_main.a
    pthread
)

enable_testing()
add_test(NAME LZWTests COMMAND LZWTests)