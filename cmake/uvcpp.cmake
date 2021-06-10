set(UV_CPP_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/uv_cpp)

file(GLOB_RECURSE UV_CPP_SRC_RECURSE 
	${UV_CPP_INCLUDE_DIR}/uv/*.c 
	${UV_CPP_INCLUDE_DIR}/uv/*.h 
	${UV_CPP_INCLUDE_DIR}/uv/*.cpp 
	${UV_CPP_INCLUDE_DIR}/uv/*.hpp)
source_group(TREE ${UV_CPP_INCLUDE_DIR}/uv PREFIX src FILES ${UV_CPP_SRC_RECURSE})

SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11   -O2")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -O2")

ADD_LIBRARY (uv_cpp STATIC ${UV_CPP_SRC_RECURSE})
TARGET_LINK_LIBRARIES(uv_cpp uv -pthread)

INCLUDE_DIRECTORIES(
	${UV_CPP_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/3rdparty/libuv/include
)
    
set_target_properties(uv_cpp PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(uv_cpp PROPERTIES FOLDER 3rdparty)

set(UV_CPP_LIBRARIES uv_cpp)

