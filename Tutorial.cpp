#include "Tutorial.h"
#include <iomanip>
#include <iostream>

Tutorial::Tutorial(std::string type, int courseId, std::string day, int startHour, int endHour,
                   std::string classroom, std::string teacherName, int groupNumber)
    : Lesson(courseId, groupNumber, teacherName, day, startHour, endHour - startHour, "", classroom) {}

void Tutorial::print() const {
    std::cout << "--- TUTORIAL - Course " << std::setw(3) << courseId
              << " - Group " << std::setw(2) << groupId
              << " - " << std::setw(9) << day
              << " - " << (startHour < 10 ? "0" : "") << startHour << ":00-"
              << (startHour + duration < 10 ? "0" : "") << (startHour + duration) << ":00"
              << " - " << std::setw(20) << teacherName
              << " - " << building << " " << room << std::endl;
}

std::string Tutorial::getType() const {
    return "Tutorial";
}

Lesson* Tutorial::clone() const {
    return new Tutorial("Tutorial", courseId, day, startHour, startHour + duration,
                        room, teacherName, groupId);
}
