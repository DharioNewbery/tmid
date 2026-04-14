cmake_minimum_required(VERSION 3.16)

project(TMID VERSION 0.0.1 LANGUAGES CXX)

# Standard C++ settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Yaml-cpp
FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.9.0
)

FetchContent_MakeAvailable(yaml-cpp)

include_directories(include)

# Project files
set(SOURCES
    src/main.cpp
)

set(HEADERS
    include/cppfile.hpp
    include/cppheader.hpp
    include/cppsocket.hpp
    include/server.hpp
    include/includes.hpp
)

# Executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        yaml-cpp::yaml-cpp
)