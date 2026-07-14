add_executable(engine_opchar ${CMAKE_CURRENT_SOURCE_DIR}/engine_operating_charasteristics.cpp)

target_link_libraries(engine_opchar PRIVATE
    spdlog::spdlog
    rerun_wrapper
    ic_engine_lib
    ice_utils
)
