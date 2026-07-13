add_library(rerun_wrapper INTERFACE)

target_include_directories(rerun_wrapper INTERFACE include)

target_link_libraries(rerun_wrapper INTERFACE rerun_sdk)
