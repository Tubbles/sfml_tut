# add_subdirectory(SFML)
# add_subdirectory(fmt)
# add_subdirectory(imgui)
# add_subdirectory(imgui-sfml)
target_include_directories(${TARGET} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/imgui
    ${CMAKE_CURRENT_LIST_DIR}/imgui-sfml
    ${CMAKE_CURRENT_LIST_DIR}/spdlog/include
)
target_sources(${TARGET} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/imgui-sfml/imgui-SFML.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spdlog/src/async.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spdlog/src/cfg.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spdlog/src/color_sinks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spdlog/src/file_sinks.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spdlog/src/spdlog.cpp
    ${CMAKE_CURRENT_LIST_DIR}/spdlog/src/stdout_sinks.cpp
)
target_compile_definitions(${TARGET} PRIVATE
    SPDLOG_FMT_EXTERNAL
    SPDLOG_COMPILED_LIB
)
