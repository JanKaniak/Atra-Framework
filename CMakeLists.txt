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

target_include_directories(imgui PUBLIC src/imgui)


add_library(imgui_backends
    src/imgui/imgui_impl_sdl2.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

target_include_directories(imgui_backends PUBLIC src/imgui)

add_library(myLib
    src/libs/Sources/Descriptions/AttributeDescription.cpp
    src/libs/Sources/Descriptions/AttributeDescriptions.cpp
    src/libs/Sources/Attributes/Attributes.cpp
    src/libs/Sources/ControlComponents/NumericInput.cpp
    src/libs/Sources/ControlComponents/Formular.cpp
    src/nlohmannJson/json.hpp
)

target_include_directories(myLib PUBLIC src/libs/Headers/Descriptions)
target_include_directories(myLib PUBLIC src/libs/Headers/Attributes)
target_include_directories(myLib PUBLIC src/libs/Headers/ControlComponents)
target_include_directories(myLib PUBLIC src/nlohmannJson)

add_executable(ImGuiTest 
    src/main.cpp)

# Prepojenie knižníc
target_link_libraries(ImGuiTest PRIVATE imgui imgui_backends SDL2 OpenGL myLib)
target_link_libraries(myLib PRIVATE imgui)



# Nastavenie verzie balíka pre CPack
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_target_properties(myLib PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)