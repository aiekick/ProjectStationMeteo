set(SQLITE_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/sqlite)

file(GLOB SQLITE_SRC 
	${SQLITE_INCLUDE_DIR}/*.c 
	${SQLITE_INCLUDE_DIR}/*.h
)
source_group(TREE ${SQLITE_INCLUDE_DIR} PREFIX src FILES ${SQLITE_SRC})

add_library(sqlite STATIC ${SQLITE_SRC})

set_target_properties(sqlite PROPERTIES LINKER_LANGUAGE C)
set_target_properties(sqlite PROPERTIES FOLDER 3rdparty)

set(SQLITE_LIBRARIES sqlite)

