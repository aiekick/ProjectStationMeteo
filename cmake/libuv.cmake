set(LIBUV_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/libuv)

set(BUILD_TESTING OFF)
add_subdirectory(3rdparty/libuv)
    
set_target_properties(uv PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(uv PROPERTIES FOLDER 3rdparty)

set(LIBUV_LIBRARIES uv)

