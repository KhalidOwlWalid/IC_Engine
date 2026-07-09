cmake_minimum_required(VERSION 3.20)
project(ic_engine)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third_party/spdlog)
add_subdirectory(ic_engine_lib)
add_subdirectory(visualizer)

add_executable(app main.cpp)

target_link_libraries(app PRIVATE spdlog::spdlog)
