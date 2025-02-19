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

set(SOURCES
    ../fish.h ../fish.cpp
    ../shark.h ../shark.cpp
    ../world.h ../world.cpp
    ../creature.h ../creature.cpp
    ../cell.h ../cell.cpp
    ../creatureType.h
    ../creaturefactory.h ../creaturefactory.cpp
)

add_executable(worldtests
    ${SOURCES}
    test_world.cpp
)
add_test(NAME worldtests COMMAND worldtests)
target_link_libraries(worldtests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
