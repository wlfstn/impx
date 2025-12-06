cmake_minimum_required(VERSION 4.1.0)
project(impx VERSION 1.0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)
set(CMAKE_CXX_MODULE_CACHE ${CMAKE_BINARY_DIR}/cxx_modules)

# MACOS Specific
set(CMAKE_C_COMPILER /opt/homebrew/opt/llvm/bin/clang)
set(CMAKE_CXX_COMPILER /opt/homebrew/opt/llvm/bin/clang++)
set(CMAKE_OSX_SYSROOT ${SDK_PATH})

# UUID found from https://github.com/Kitware/CMake/blob/v4.1.0/Help/dev/experimental.rst
# set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "1942b4fa-b2c5-4546-9385-83f254070067")

set(SOURCE_FILES src/main.cpp) # Grab all .cpp files from src folder

set(MODULE_FILES
	src/core/lexer.cppm
	src/core/parser.cppm
	src/core/calc.cppm
)

add_library(core_modules)
target_sources(core_modules
	PUBLIC
	FILE_SET cxx_modules TYPE CXX_MODULES FILES
		src/core/lexer.cppm
		src/core/parser.cppm
		src/core/calc.cppm
)
add_executable(impx src/main.cpp)
target_link_libraries(impx PRIVATE core_modules)