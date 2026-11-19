#ifndef LESSON_H
#define LESSON_H

#include <string>
#include <iostream>

class Lesson {
protected:
    int courseId;
    int groupId;
    std::string teacherName;
    std::string day;
    int startHour;
    int duration;
    std::string building;
    std::string room;

public:
    Lesson(); 
    Lesson(int courseId, int groupId, const std::string& teacherName, const std::string& day, int startHour, int duration, const std::string& building, const std::string& room);
    virtual ~Lesson() = default; // Virtual destructor

    int getCourseId() const;
    int getGroupId() const;
    std::string getTeacherName() const;
    std::string getDay() const;
    int getStartHour() const;
    int getDuration() const;
    std::string getBuilding() const;
    std::string getRoom() const;

    void setTeacherName(const std::string& name);
    void setDay(const std::string& newDay);
    void setStartHour(int hour);
    void setDuration(int newDuration);
    void setBuilding(const std::string& newBuilding);
    void setRoom(const std::string& newRoom);

    virtual std::string getType() const = 0;
    virtual void print() const = 0;
    virtual Lesson* clone() const = 0; // Pure virtual clone method
};

#endif // LESSON_H