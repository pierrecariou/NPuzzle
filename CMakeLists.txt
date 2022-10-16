cmake_minimum_required(VERSION 3.10)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++17")

# set the project name
project(NPuzzle)

add_subdirectory(SFML-2.5.1)

add_executable(NPuzzle
  ${CMAKE_SOURCE_DIR}/src/NPuzzleApp.cpp
  ${CMAKE_SOURCE_DIR}/src/NPuzzle.cpp
  ${CMAKE_SOURCE_DIR}/src/Node.cpp
  ${CMAKE_SOURCE_DIR}/src/Gui.cpp
)

target_link_libraries(NPuzzle PUBLIC sfml-graphics)

target_include_directories(NPuzzle PRIVATE
  ${CMAKE_SOURCE_DIR}/src
  ${CMAKE_SOURCE_DIR}/include
  ${CMAKE_SOURCE_DIR}/SFML-2.5.1/include
)
