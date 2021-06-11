set(LIBUV_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/libuv)

set(BUILD_TESTING OFF)
add_subdirectory(3rdparty/libuv)
    
set_target_properties(uv PROPERTIES FOLDER 3rdparty)
set_target_properties(uv_a PROPERTIES FOLDER 3rdparty)

set(LIBUV_LIBRARIES uv uv_a)

