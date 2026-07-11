include(FetchContent)
FetchContent_Declare(rerun_sdk URL
    https://github.com/rerun-io/rerun/releases/latest/download/rerun_cpp_sdk.zip
)
FetchContent_MakeAvailable(rerun_sdk)

# Build the rerun examples directory
# add_executable(example
#     ${CMAKE_CURRENT_SOURCE_DIR}/example/rerun/time_series_example.cpp
# )

# target_link_libraries(example PRIVATE rerun_sdk spdlog::spdlog)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples)

file(GLOB_RECURSE RERUN_EXAMPLES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/example/rerun/*.cpp)

foreach(source ${RERUN_EXAMPLES})
    get_filename_component(target_name ${source} NAME_WE)
    message(STATUS "Example found, target name is ${target_name}")
    add_executable(${target_name} ${source})
    target_link_libraries(${target_name} PRIVATE rerun_sdk spdlog::spdlog)
endforeach()
