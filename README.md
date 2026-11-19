# C++ Course Schedule Manager

An object-oriented C++ console application for managing university courses, lessons, and weekly schedules.

The project demonstrates practical C++ software design through inheritance, polymorphism, encapsulation, dynamic object management, CSV persistence, conflict detection, and schedule analysis.

## Features

- Load and save courses, lessons, and schedules using CSV files
- Model lectures, tutorials, and labs through a polymorphic `Lesson` hierarchy
- Create, remove, print, and update schedules
- Add lessons with time-conflict detection
- Display weekly timetable views with lesson-type formatting
- Analyze schedule workload and teacher schedules
- Find common lessons and time conflicts
- Interactive command-line interface with help and validation messages

## Technical Stack

- **Language:** C++17-compatible C++
- **Paradigms:** Object-oriented programming, inheritance, polymorphism, encapsulation
- **Persistence:** CSV files through the C++ standard library
- **IDE/project support:** Visual Studio 2022 (`.sln` and `.vcxproj`)
- **Libraries:** C++ Standard Library (`vector`, `string`, `fstream`, `sstream`, `map`, `set`)

## Architecture

| Component | Responsibility |
|---|---|
| `Course` | Stores course metadata, credits, exam dates, and lecturer |
| `Lesson` | Abstract base class for scheduled teaching sessions |
| `Lecture`, `Tutorial`, `Lab` | Specialized lesson types implementing polymorphic behavior |
| `Schedule` | Owns scheduled lesson copies and detects time conflicts |
| `System` | Loads data, handles commands, and coordinates application workflows |

## Build and Run

### Visual Studio

1. Open `Final project.sln` in Visual Studio 2022.
2. Select `Debug` or `Release`.
3. Build the solution.
4. Run the console application from the project directory so the CSV files can be found.

### Command line

On a compiler with C++17 support:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic \
  Course.cpp Lab.cpp Lecture.cpp Lesson.cpp Schedule.cpp System.cpp Tutorial.cpp main.cpp \
  -o course-schedule-manager
./course-schedule-manager
```

The application expects its CSV data files in the current working directory.

## Main Commands

Use `Help` after starting the application to display the complete command list. Common commands include:

```text
PrintCourses
PrintCourse <course_id>
PrintSchedules
PrintSchedule <schedule_id>
AddSchedule
Add <schedule_id> <course_id> <group_id>
Rm <schedule_id> <course_id> <group_id>
CheckConflicts <schedule_id>
AnalyzeWorkload <schedule_id>
AnalyzeTeacher <teacher_name>
FindTimeConflicts
Help
Exit
```

## Data Files

- `courses.csv` — course definitions and exam dates
- `lessons.csv` — lecture, tutorial, and lab sessions
- `schedules.csv` — saved schedules represented by course/group references

The application writes updated data back to these CSV files when changes are saved.

## Engineering Notes

This project was developed as an object-oriented programming project and focuses on translating a real scheduling problem into maintainable C++ classes. The abstract `Lesson` interface allows the system to handle different lesson types uniformly while preserving type-specific behavior.

## Security and Privacy

The repository contains no API keys, passwords, authentication tokens, or external service credentials. The CSV files contain synthetic academic data for demonstration purposes.

## Future Improvements

- Replace raw owning pointers with smart pointers
- Add automated unit tests for conflict detection and CSV parsing
- Separate command handling, persistence, and presentation into dedicated modules
- Add robust CSV escaping and validation for malformed input
- Add a portable build system such as CMake
