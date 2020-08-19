cmake_minimum_required (VERSION 3.14)
project(emerald)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DEM_ENABLE_ASSERTS")

add_subdirectory(src/external/glfw)
add_subdirectory(src/external/glad)
add_subdirectory(src/external/imgui)

file(GLOB_RECURSE EMERALD_SRC ${PROJECT_SOURCE_DIR}/src/emerald/*.cpp)

add_definitions(
    -DGLFW_INCLUDE_NONE
)

IF (WIN32)
    add_definitions(
    -DEM_PLATFORM_WINDOWS
    )
ENDIF()

IF (APPLE AND UNIX)
    add_definitions(
    -DEM_PLATFORM_MACOS
    )
ENDIF()

IF (UNIX AND NOT APPLE)
    add_definitions(
    -DEM_PLATFORM_LINUX
    )
ENDIF()

include_directories(
    src/emerald
    src/external/glad/include
    src/external/imgui
    src/external/glfw/include
    src/external/glm
    src/external/spdlog/include
)

add_library(emerald ${EMERALD_SRC})

target_precompile_headers(emerald PRIVATE src/emerald/engine/empch.h)

target_link_libraries(emerald glfw imgui glad GL)

add_executable(
    sandbox
    src/sandbox/Sandbox.cpp
)

target_link_libraries(sandbox emerald)