cmake_minimum_required(VERSION 3.16)

project(course_schedule_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(course-schedule-manager
    Course.cpp
    Lab.cpp
    Lecture.cpp
    Lesson.cpp
    Schedule.cpp
    System.cpp
    Tutorial.cpp
    main.cpp
)

if (MSVC)
    target_compile_options(course-schedule-manager PRIVATE /W4 /permissive-)
else()
    target_compile_options(course-schedule-manager PRIVATE -Wall -Wextra -Wpedantic)
endif()

file(COPY
    courses.csv
    lessons.csv
    schedules.csv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
