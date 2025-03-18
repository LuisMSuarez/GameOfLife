cmake_minimum_required(VERSION 3.16)

project(sharktests LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Test)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sharktests
    test_shark.cpp
)

# Link the core library and Qt Test framework
target_link_libraries(sharktests PRIVATE GameOfLifeCore Qt${QT_VERSION_MAJOR}::Test)

add_test(NAME sharktests COMMAND sharktests)