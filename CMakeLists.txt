cmake_minimum_required(VERSION 3.5.0)
project(GraphicEditor VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})


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
    src/libs/Sources/Descriptions/ImplementedAttributeDescriptions.cpp
    src/libs/Sources/Descriptions/AttributeDescriptionsContainer.cpp
    src/libs/Sources/Attributes/ImplementedAttribute.cpp
    src/libs/Sources/Attributes/AttributesContainer.cpp
    src/libs/Sources/ControlComponents/NumericInput.cpp
    src/libs/Sources/ControlComponents/Formular.cpp
    src/libs/Sources/ControlComponents/Factory.cpp
    src/libs/Sources/Attributes/AttributeFactory.cpp
    src/libs/Sources/ControlComponents/ControlComponentsContainer.cpp
    src/libs/Sources/ControlComponents/ControlComponentsCluster.cpp
    src/libs/Sources/Basic/GlobalLastIdOfObject.cpp
)

add_subdirectory(src/nativefiledialog-extended)

target_include_directories(myLib PUBLIC src/libs/Headers/Descriptions)
target_include_directories(myLib PUBLIC src/libs/Headers/Attributes)
target_include_directories(myLib PUBLIC src/libs/Headers/ControlComponents)
target_include_directories(myLib PUBLIC src/libs/Headers/Basic)
target_include_directories(myLib PUBLIC src/nlohmannJson)


add_executable(GraphicEditor 
    src/main.cpp)


target_link_libraries(GraphicEditor PRIVATE imgui imgui_backends SDL2 OpenGL myLib)
target_link_libraries(myLib PRIVATE imgui nfd)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_target_properties(myLib PROPERTIES LINKER_LANGUAGE CXX)

include(CPack)


