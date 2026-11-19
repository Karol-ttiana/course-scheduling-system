#include "Lesson.h"
#include <algorithm>
#include <iostream>

Lesson::Lesson():courseId(0), groupId(0), duration(0){}

Lesson::Lesson(int courseId, int groupId, const std::string& teacherName, const std::string& day, int startHour, int duration, const std::string& building, const std::string& room)
	: courseId(courseId), groupId(groupId), teacherName(teacherName), day(day), startHour(startHour), duration(duration), building(building), room(room) {
}


int Lesson::getCourseId() const {
	return courseId;
}

int Lesson::getGroupId() const {
	return groupId;
}

std::string Lesson::getTeacherName() const {
	return teacherName;
}

std::string Lesson::getDay() const {
	return day;
}

int Lesson::getStartHour() const {
	return startHour;
}

int Lesson::getDuration() const {
	return duration;
}

std::string Lesson::getBuilding() const {
	return building;
}

std::string Lesson::getRoom() const {
	return room;
}

void Lesson::setTeacherName(const std::string& name) {
	teacherName = name;
}

void Lesson::setDay(const std::string& newDay) {
	day = newDay;
}

void Lesson::setStartHour(int hour) {
	startHour = hour;
}

void Lesson::setDuration(int newDuration) {
	duration = newDuration;
}

void Lesson::setBuilding(const std::string& newBuilding) {
	building = newBuilding;
}

void Lesson::setRoom(const std::string& newRoom) {
	room = newRoom;
}

void Lesson::print() const {
    std::cout << "Course ID: " << courseId 
              << ", Group: " << groupId
              << ", Day: " << day
              << ", Time: " << startHour << ":00"
              << ", Duration: " << duration << " hours"
              << ", Teacher: " << teacherName
              << ", Location: " << building << " " << room;
}

