cmake_minimum_required(VERSION 3.16)

project(course_schedule_manager LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

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

add_executable(schedule-tests
    Course.cpp
    Lab.cpp
    Lecture.cpp
    Lesson.cpp
    Schedule.cpp
    Tutorial.cpp
    tests/ScheduleTests.cpp
)

target_include_directories(schedule-tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if (MSVC)
    target_compile_options(schedule-tests PRIVATE /W4 /permissive-)
else()
    target_compile_options(schedule-tests PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_test(NAME schedule-tests COMMAND schedule-tests)

file(COPY
    courses.csv
    lessons.csv
    schedules.csv
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR}
)
