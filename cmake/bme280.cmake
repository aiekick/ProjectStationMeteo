set(BME280_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/3rdparty/BME280_driver)

file(GLOB BME280_SRC 
	${BME280_INCLUDE_DIR}/*.c 
	${BME280_INCLUDE_DIR}/*.h
)
source_group(TREE ${BME280_INCLUDE_DIR} PREFIX src FILES ${BME280_SRC})

add_library(bme280 STATIC ${BME280_SRC})

set_target_properties(bme280 PROPERTIES LINKER_LANGUAGE C)
set_target_properties(bme280 PROPERTIES FOLDER 3rdparty)

set(BME280_LIBRARIES bme280 wiringPi)

