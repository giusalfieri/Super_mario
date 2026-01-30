project( supermario3 )

cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

set (CMAKE_CXX_STANDARD 17)

file(GLOB my_sources "src/*.h" "src/*.cpp" "src/*.qrc")

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

add_executable(supermario3 ${my_sources})

target_include_directories(supermario3 PRIVATE src)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Multimedia REQUIRED)

target_link_libraries(supermario3 Qt5::Widgets Qt5::Multimedia)