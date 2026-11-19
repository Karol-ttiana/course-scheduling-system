#include "Lecture.h"
#include <iostream>
#include <iomanip>
using namespace std;

// Default constructor: Initializes a Lecture by calling the base Lesson constructor.
Lecture::Lecture() : Lesson() {}

// Parameterized constructor: Initializes a Lecture using the base class constructor for inherited members.
Lecture::Lecture(string type, int courseId, string day, int startHour, int endHour,
    string classroom, string teacherName, int groupNumber)
    : Lesson(courseId, groupNumber, teacherName, day, startHour, endHour - startHour, "", classroom) {
    (void)type;
}

// Returns the type of the lesson, which is "Lecture".
std::string Lecture::getType() const {
    return "Lecture";
}

// Prints the details of the lecture to the console.
void Lecture::print() const {
    std::cout << "--- LECTURE - Course " << std::setw(3) << courseId 
              << " - Group " << std::setw(2) << groupId
              << " - " << std::setw(9) << day
              << " - " << (startHour < 10 ? "0" : "") << startHour << ":00-" 
              << (startHour + duration < 10 ? "0" : "") << (startHour + duration) << ":00"
              << " - " << std::setw(20) << teacherName
              << " - " << building << " " << room << std::endl;
}

// Clone method implementation
Lesson* Lecture::clone() const {
    return new Lecture("Lecture", courseId, day, startHour, startHour + duration, room, teacherName, groupId);
}

// Overloaded stream insertion operator to print Lecture details.
std::ostream& operator<<(std::ostream& os, const Lecture& lecture) {
    os << "Type: Lecture, "
       << "Course ID: " << lecture.getCourseId()
       << ", Group: " << lecture.getGroupId()
       << ", Day: " << lecture.getDay()
       << ", Time: " << lecture.getStartHour() << ":00"
       << ", Duration: " << lecture.getDuration() << " hours"
       << ", Teacher: " << lecture.getTeacherName()
       << ", Location: " << lecture.getBuilding() << " " << lecture.getRoom();
    return os;
}