cmake_minimum_required(VERSION 3.16)

project(StudentCourseRecommender LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# ⚠️  Point CMAKE_PREFIX_PATH to your Qt installation if CMake can’t find it automatically.
# e.g. set(CMAKE_PREFIX_PATH "C:/Qt/6.7.0/msvc2019_64/lib/cmake")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(StudentCourseRecommender
    main.cpp
    mainwindow.h
    mainwindow.cpp
)

target_link_libraries(StudentCourseRecommender Qt6::Widgets)
