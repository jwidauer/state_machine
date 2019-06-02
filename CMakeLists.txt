cmake_minimum_required(VERSION 3.8.2)
project(state_machine)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/example.cc)

target_include_directories(${PROJECT_NAME} PUBLIC
  include
)