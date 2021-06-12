cmake_minimum_required(VERSION 3.1)

set(PROJECT bme280TcpServer)

enable_language(C CXX)

project(${PROJECT} CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmakeTargets")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    add_definitions(-D_USE_MATH_DEFINES)
    add_definitions(-DMSVC)
	add_definitions(-DNOMINMAX) ## for avoid issue regarding std::max and std::min
else ()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wdeprecated-declarations -Wunused-parameter")
endif ()

if(UNIX)
    add_definitions(-DUNIX)
elseif(WIN32)
    add_definitions(-DWIN32)
endif()

include(cmake/3rdparty.cmake)

file(GLOB_RECURSE PROJECT_SRC_RECURSE 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.c 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.h 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp 
	${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp)
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/src PREFIX src FILES ${PROJECT_SRC_RECURSE})

add_executable(${PROJECT} ${PROJECT_SRC_RECURSE})

set_target_properties(${PROJECT} PROPERTIES OUTPUT_NAME "${PROJECT}")


include_directories(
	src
	${LIBUV_INCLUDE_DIR}
	${UV_CPP_INCLUDE_DIR}
	${BME280_INCLUDE_DIR}
	${SQLITE_INCLUDE_DIR}
)

target_link_libraries(${PROJECT} PRIVATE
	${LIBUV_LIBRARIES}
	${UV_CPP_LIBRARIES}
	${BME280_LIBRARIES}
	${SQLITE_LIBRARIES}
)

if (UNIX)
set(CMAKE_INSTALL_PREFIX "/usr/share/${PROJECT}")
install(TARGETS ${PROJECT} DESTINATION ${CMAKE_INSTALL_PREFIX})
install(FILE sripts/bme280Server.service DESTINATION "${CMAKE_SOURCE_DIR}/")
install(CODE "EXECUTE_PROCESS(COMMAND ln -s ${CMAKE_INSTALL_PREFIX}/bme280Server.service /etc/systemd/system/bme280Server.service})")
endif()

########################################################
################# BUILD INCREMENT TOOL #################
########################################################

## only for Debug
add_subdirectory(3rdparty/BuildInc)

add_custom_command(
	TARGET ${PROJECT} PRE_BUILD
	COMMAND BuildInc 100:10 $<$<CONFIG:Debug>:${CMAKE_SOURCE_DIR}/src/Build.h>
	DEPENDS ${PROJECT}
)