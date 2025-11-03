cmake_minimum_required(VERSION 3.5.0)
project(ImGuiTest VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Nájdenie SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Nájdenie OpenGL
find_package(OpenGL REQUIRED)


add_library(imgui
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_stdlib.cpp
)


add_library(imgui_backends
    src/imgui/imgui_impl_sdl2.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

add_library(njson
    src/nlohmannJson/json.hpp
)



add_executable(ImGuiTest src/main.cpp)

# Prepojenie knižníc
target_link_libraries(ImGuiTest PRIVATE imgui imgui_backends SDL2 OpenGL njson)

# Zahrnutie hlavičkových súborov
target_include_directories(imgui PUBLIC src/imgui)
target_include_directories(imgui_backends PUBLIC src/imgui)
target_include_directories(njson PUBLIC src/nlohmannJson)

# Testy (ak sú zahrnuté)
include(CTest)
enable_testing()

# Nastavenie verzie balíka pre CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_target_properties(njson PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)