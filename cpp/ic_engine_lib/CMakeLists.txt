add_library(ic_engine_lib STATIC
    src/engine.cpp
)

target_link_libraries(ic_engine_lib PRIVATE spdlog::spdlog)
