include(FetchContent)
FetchContent_Declare(rerun_sdk URL
    https://github.com/rerun-io/rerun/releases/latest/download/rerun_cpp_sdk.zip
)
FetchContent_MakeAvailable(rerun_sdk)

add_executable(example
    src/example.cpp
)

target_link_libraries(example PRIVATE rerun_sdk)
target_link_libraries(example PRIVATE spdlog::spdlog)
