include(FetchContent)
FetchContent_Declare(rerun_sdk URL
    # Download the latest rerun_sdk if needed, my viewer is currently at 0.33.1
    # TODO: Add a macro to fetch the rerun viewer version, and then accordingly download the right sdk
    # https://github.com/rerun-io/rerun/releases/latest/download/rerun_cpp_sdk.zip
    https://github.com/rerun-io/rerun/releases/download/0.33.1/rerun_cpp_sdk.zip
)
FetchContent_MakeAvailable(rerun_sdk)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/examples)

file(GLOB_RECURSE RERUN_EXAMPLES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/example/rerun/*.cpp)

foreach(source ${RERUN_EXAMPLES})
    get_filename_component(target_name ${source} NAME_WE)
    message(STATUS "Example found, target name is ${target_name}")
    add_executable(${target_name} ${source})
    target_link_libraries(${target_name} PRIVATE rerun_sdk spdlog::spdlog)
endforeach()
