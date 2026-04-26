cmake_minimum_required(VERSION 3.5.0)
project(GraphicEditor VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(OpenGL REQUIRED)


add_library(imgui
    src/imgui/imgui.cpp
    src/imgui/imgui_draw.cpp
    src/imgui/imgui_tables.cpp
    src/imgui/imgui_widgets.cpp
    src/imgui/imgui_stdlib.cpp
)

add_library(imgui_backends
    src/imgui/imgui_impl_glfw.cpp
    src/imgui/imgui_impl_opengl3.cpp
)

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
add_subdirectory(src/glfw)

target_include_directories(imgui_backends PUBLIC src/imgui  src/glfw/include/GLFW)



target_include_directories(myLib PUBLIC src/libs/Headers/Descriptions)
target_include_directories(myLib PUBLIC src/libs/Headers/Attributes)
target_include_directories(myLib PUBLIC src/libs/Headers/ControlComponents)
target_include_directories(myLib PUBLIC src/libs/Headers/Basic)
target_include_directories(myLib PUBLIC src/nlohmannJson)
target_include_directories(myLib PUBLIC src/imgui)


add_executable(GraphicEditor 
src/main.cpp)

target_link_libraries(imgui_backends PRIVATE glfw)
target_link_libraries(myLib PRIVATE imgui nfd)
target_link_libraries(GraphicEditor PRIVATE imgui OpenGL imgui_backends myLib)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_target_properties(myLib PROPERTIES LINKER_LANGUAGE CXX)


