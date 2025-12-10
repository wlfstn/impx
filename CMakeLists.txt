cmake_minimum_required(VERSION 4.1.0)
project(impx VERSION 1.0.4)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_MODULE_CACHE ${CMAKE_BINARY_DIR}/cxx_modules)

if(APPLE)
	message(STATUS "Configuring for macOS")
	set(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang)
	set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++)
	set(CMAKE_OSX_SYSROOT ${SDK_PATH})
endif()

set(SOURCE_FILES src/main.cpp) # Grab all .cpp files from src folder

add_library(impx_modules)
target_sources(impx_modules
	PUBLIC
	FILE_SET cxx_modules TYPE CXX_MODULES FILES
		src/core/lexer.cppm
		src/core/parser.cppm
		src/core/calc.cppm
		src/util/weretype.cppm
)

add_executable(impx src/main.cpp)
target_link_libraries(impx PRIVATE impx_modules)