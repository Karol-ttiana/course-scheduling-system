#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Lesson.h"
#include <string>

class Tutorial : public Lesson {
public:
    Tutorial(std::string type, int courseId, std::string day, int startHour, int endHour,
             std::string classroom, std::string teacherName, int groupNumber);

    void print() const override;
    std::string getType() const override;
    Lesson* clone() const override;
};

#endif // TUTORIAL_H
