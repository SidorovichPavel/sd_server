cmake_minimum_required(VERSION 3.30.0)
project(sd-server VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED On)

set(SOURCES
  src/main.cpp
  src/soptions/soptions.hpp
  src/soptions/soptions.cpp)

find_package(Boost CONFIG REQUIRED filesystem system chrono program_options context)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
  Boost::headers
  Boost::program_options
  Boost::system
  Boost::filesystem
  Boost::chrono
  Boost::context)

target_compile_options(${PROJECT_NAME} PUBLIC -Wall -Werror -Wpedantic)
