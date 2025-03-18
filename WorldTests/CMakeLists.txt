cmake_minimum_required(VERSION 3.16)

project(worldtests LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(worldtests
    test_world.cpp
)

# Link the core library and Qt Test framework
target_link_libraries(worldtests PRIVATE GameOfLifeCore Qt${QT_VERSION_MAJOR}::Test)

add_test(NAME worldtests COMMAND worldtests)
