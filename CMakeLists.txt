cmake_minimum_required(VERSION 3.16)
project(TMID VERSION 0.0.1 LANGUAGES CXX)

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

# cppsocket
FetchContent_Declare(
  cppsocket
  GIT_REPOSITORY https://github.com/DharioNewbery/cppsocket.git
  GIT_TAG v0.0.1-alpha.2
)

# HeaderBuilder
FetchContent_Declare(
  HeaderBuilder
  GIT_REPOSITORY https://github.com/icaro-s16/HeaderBuilder.git
  GIT_TAG v1.0.0
)

FetchContent_MakeAvailable(yaml-cpp cppsocket HeaderBuilder)

# Project files
set(SOURCES src/main.cpp)
set(HEADERS
    include/cppfile.hpp
    include/header.hpp
    include/server.hpp
    include/client.hpp
    include/includes.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE yaml-cpp)

target_include_directories(${PROJECT_NAME} PRIVATE 
    ${cppsocket_SOURCE_DIR}/include 
    ${headerbuilder_SOURCE_DIR}/src
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif()