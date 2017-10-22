cmake_minimum_required(VERSION 3.0)

project(TQ VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

configure_file (
  "include/Config.hpp.in"
  "${PROJECT_BINARY_DIR}/Config.hpp"
  )
include_directories("${PROJECT_BINARY_DIR}")
include_directories(include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

find_package(Boost COMPONENTS iostreams REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost::iostreams.")
	return()
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

add_library(tq STATIC src/Decoder.cpp src/StrictDecoder.cpp src/StrictDecoderWithBlanks.cpp src/Utilities.cpp)
add_executable(tq-bin src/main.cpp)
install (TARGETS tq-bin DESTINATION bin)
target_link_libraries(tq-bin tq ${Boost_LIBRARIES})
set_target_properties(tq-bin PROPERTIES OUTPUT_NAME tq)
