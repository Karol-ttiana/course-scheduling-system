#include "Lab.h"
#include <iostream>
#include <iomanip>
using namespace std;

Lab::Lab(string type, int courseId, string day, int startHour, int endHour,
    string classroom, string teacherName, int groupNumber)
    : Lesson(courseId, groupNumber, teacherName, day, startHour, endHour - startHour, "", classroom) {
}

void Lab::print() const {
    std::cout << "--- LAB - Course " << std::setw(3) << courseId 
              << " - Group " << std::setw(2) << groupId
              << " - " << std::setw(9) << day
              << " - " << (startHour < 10 ? "0" : "") << startHour << ":00-" 
              << (startHour + duration < 10 ? "0" : "") << (startHour + duration) << ":00"
              << " - " << std::setw(20) << teacherName
              << " - " << building << " " << room << std::endl;
}

std::string Lab::getType() const {
    return "Lab";
}

Lesson* Lab::clone() const {
    return new Lab("Lab", courseId, day, startHour, startHour + duration, room, teacherName, groupId);
}