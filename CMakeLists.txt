cmake_minimum_required(VERSION 3.1)

set(PROJECT bme280TcpServer)

enable_language(C CXX)

project(${PROJECT} CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wdeprecated-declarations -Wunused-parameter")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -luv")

file(GLOB_RECURSE PROJECT_SRC_RECURSE 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.h 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX src FILES ${PROJECT_SRC_RECURSE})

add_executable(${PROJECT} ${PROJECT_SRC_RECURSE})

set_target_properties(${PROJECT} PROPERTIES OUTPUT_NAME "${PROJECT}")

add_subdirectory(3rdparty/uv-cpp)

include_directories(
	src
	3rdparty/uv-cpp
)

LINK_DIRECTORIES(3rdparty${PROJECT_SOURCE_DIR}/libuv1.30.0/lib/gcc8.3.0)

target_link_libraries(${PROJECT} PRIVATE
	uv_cpp
)
