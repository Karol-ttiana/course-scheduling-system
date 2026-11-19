#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>

class Course {
private:
    int id;
    std::string name;
    int credits;
    std::string moedA;
    std::string moedB;
    std::string lecturer;

public:

    Course();
    Course(int id, std::string name, int credits, std::string moedA, std::string moedB, std::string lecturer);

    int getId() const;
    std::string getName() const;
    int getCredits() const;
    std::string getMoedA() const;
    std::string getMoedB() const;
    std::string getLecturer() const;

    void setName(const std::string& newName);
    void setCredits(int newCredits);
    void setMoedA(const std::string& date);
    void setMoedB(const std::string& date);
    void setLecturer(const std::string& name);

    friend std::ostream& operator<<(std::ostream& os, const Course& course);
};

#endif