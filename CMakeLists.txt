cmake_minimum_required(VERSION 3.21)
project(SGC
    VERSION 0.0.1
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(SGC
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/canvas.cpp
    src/canvas.h
    src/RectangleObject.h
    src/RectangleObject.cpp
    src/GraphicObject.h
    src/LineObject.h
    src/LineObject.cpp
    src/GraphicObject.cpp
)
target_link_libraries(SGC
    PRIVATE Qt6::Widgets
)