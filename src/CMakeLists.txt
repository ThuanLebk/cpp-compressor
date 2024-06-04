set(SOURCE_FILES
    LZW.cpp
    main.cpp
)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(LZWCompressor ${SOURCE_FILES})

set_target_properties(LZWCompressor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)