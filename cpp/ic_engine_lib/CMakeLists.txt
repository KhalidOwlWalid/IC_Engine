add_library(ic_engine_lib STATIC
    src/engine.cpp
    src/engine_component.cpp
)

target_include_directories(ic_engine_lib PUBLIC include)

target_link_libraries(ic_engine_lib
    PRIVATE spdlog::spdlog
    PUBLIC ice_utils
)
