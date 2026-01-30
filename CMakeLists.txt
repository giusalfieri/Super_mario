cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(supermario3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets Multimedia REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.h" "src/*.qrc")

add_executable(supermario3 ${SOURCES})
target_link_libraries(supermario3 Qt5::Widgets Qt5::Multimedia)

if(WIN32)
    find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${CMAKE_PREFIX_PATH}/bin")
    if(WINDEPLOYQT_EXECUTABLE)
        add_custom_command(TARGET supermario3 POST_BUILD
            COMMAND "${WINDEPLOYQT_EXECUTABLE}" "--no-compiler-runtime" "$<TARGET_FILE:supermario3>"
        )
    endif()
endif()
