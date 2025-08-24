cmake_minimum_required(VERSION 4.1.0)
project(impx VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_MODULE_CACHE ${CMAKE_BINARY_DIR}/cxx_modules)


# UUID found from https://github.com/Kitware/CMake/blob/v4.1.0/Help/dev/experimental.rst
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "1942b4fa-b2c5-4546-9385-83f254070067")

file(GLOB SOURCE_FILES src/*.cpp) # Grab all .cpp files from src folder

set(MODULE_FILES
	src/core/lexer.cppm
	src/core/parser.cppm
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_sources(${PROJECT_NAME}
	PRIVATE
		# None
	FILE_SET cxx_modules TYPE CXX_MODULES FILES
		${MODULE_FILES}
)