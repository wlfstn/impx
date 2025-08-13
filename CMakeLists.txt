cmake_minimum_required(VERSION 3.31.3)
project(impx VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCE_FILES src/*.cpp) # Grab all .cpp files from src folder
file(GLOB CORE_FILES src/core/*.cpp) # Grab all .cpp files from src/core folder

add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${CORE_FILES})