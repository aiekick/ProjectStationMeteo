include(cmake/libuv.cmake)
include(cmake/uvcpp.cmake)
include(cmake/sqlite.cmake)

if(UNIX)
	include(cmake/bme280.cmake)
endif()
