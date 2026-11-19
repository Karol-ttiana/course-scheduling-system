#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <string>
#include "Lesson.h"
using namespace std;

class Schedule {
private:
    int id;  
    vector<Lesson*> lessons;  // רשימת שיעורים (הרצאות, תרגולים, מעבדות)

public:
    
    Schedule();                     
    Schedule(int id);             
    Schedule(const Schedule& other);
    Schedule& operator=(const Schedule& other);
    Schedule(Schedule&& other) noexcept;
    Schedule& operator=(Schedule&& other) noexcept;

    // Getter + Setter
    int getId() const;
    void setId(int newId);

    // ניהול שיעורים
    void addLesson(Lesson* lesson);                       
    void addLessonForce(Lesson* lesson);  // Force add lesson even with conflicts                      
    void removeLesson(int courseId, int groupId);               
    vector<Lesson*>& getLessons();
    const vector<Lesson*>& getLessons() const; // Add const version                              

    // פעולות עזר
    void printSchedule() const;                                 
    bool hasConflict(const Lesson* newLesson) const;            
    int totalHours() const;                                     
    void printConflicts() const;  // New method to show all conflicts

    // (אופציונלי) שמירה/טעינה מקובץ
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);

    // דסטרוקטור
    ~Schedule();
};

#endif // SCHEDULE_H
