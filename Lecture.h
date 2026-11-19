#ifndef LECTURE_H
#define LECTURE_H

#include "Lesson.h"
#include <string>
#include <iostream>

class Lecture : public Lesson {
public:
   
    Lecture();
    Lecture(std::string type, int courseId, std::string day, int startHour, int endHour,
        std::string classroom, std::string teacherName, int groupNumber);

  
    std::string getType() const override;
    void print() const override;
    Lesson* clone() const override;

    friend std::ostream& operator<<(std::ostream& os, const Lecture& lecture);
};

#endif // LECTURE_H
