#ifndef LAB_H
#define LAB_H

#include "Lesson.h"
#include <string>
using namespace std;

class Lab : public Lesson {
public:
    Lab(string type, int courseId, string day, int startHour, int endHour,
        string classroom, string teacherName, int groupNumber);

    void print() const override;
    std::string getType() const override; // Declare the overridden method
    Lesson* clone() const override; // Add clone method
};

#endif