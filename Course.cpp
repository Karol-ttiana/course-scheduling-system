#include "Course.h"
#include <algorithm>

Course::Course():id(0),credits(0) {}


Course::Course(int id, std::string name, int credits, std::string moedA, std::string moedB, std::string lecturer)
    : id(id), name(name), credits(credits), moedA(moedA), moedB(moedB), lecturer(lecturer) {}



int Course:: getId() const
{
	return id;
}
std::string Course::getName() const {//m7zer name shel h course
	return name;
}

int Course::getCredits() const {//m7zer crdedits shel h course
	return credits;
}

std::string Course::getMoedA() const {//m7zer moedA shel h course
	return moedA;
}

std::string Course::getMoedB() const {//m7zer moedB shel h course
	return moedB;
}

std::string Course::getLecturer() const {//m7zer lecturer shel h course
	return lecturer;
}


void Course::setName(const std::string&newNAME) {
	name = newNAME;
}

void Course:: setCredits(int newCredits) {
	credits = newCredits;
}

void Course::setMoedA(const std::string& newMOEDA) {
	moedA = newMOEDA;
}

void Course::setMoedB(const std::string& newMOEDB) {
	moedB = newMOEDB;
}

void Course::setLecturer(const std::string& newLECTURER) {
	lecturer = newLECTURER;
}

std::ostream& operator<<(std::ostream& os, const Course& course) {
    os << "Course ID: " << course.id
       << ", Name: " << course.name
       << ", Credits: " << course.credits
       << ", Moed A: " << course.moedA
       << ", Moed B: " << course.moedB
       << ", Lecturer: " << course.lecturer;
    return os;
}

