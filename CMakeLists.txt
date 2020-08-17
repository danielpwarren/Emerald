cmake_minimum_required (VERSION 3.14)
project(emerald)

add_subdirectory(src/external/glfw)
add_subdirectory(src/external/glad)
add_subdirectory(src/external/imgui)

file(GLOB_RECURSE EMERALD_SRC ${PROJECT_SOURCE_DIR}/src/emerald/*.cpp)

add_definitions(
    -DGLFW_INCLUDE_NONE
)

include_directories(
    src/emerald
    src/external/glad/include
    src/external/imgui
    src/external/glfw/include
    src/external/glm
    src/external/spdlog/include
)

add_library(emerald ${EMERALD_SRC})

target_link_libraries(emerald glfw imgui glad GL)

add_executable(
    sandbox
    src/sandbox/Sandbox.cpp
)

target_link_libraries(sandbox emerald)