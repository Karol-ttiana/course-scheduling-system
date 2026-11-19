#ifndef SYSTEM_H
#define SYSTEM_H

#include "Course.h"
#include "Schedule.h"
#include "Lesson.h"
#include "Lecture.h"
#include "Tutorial.h" 
#include "Lab.h"
#include <vector>
#include <string>

class System {
private:
    std::vector<Course> courses;
    std::vector<Lesson*> lessons;
    std::vector<Schedule> schedules;
    int lastPrintedCourseIndex;

    void loadCourses();
    void loadLessons();
    void loadSchedules();
    void saveSchedules();
    void saveCourses();
    void saveLessons();
    void reindexSchedules();
    
    // Helper methods for enhanced functionality
    void waitForUser();
    void clearScreen();
    void setConsoleSize();

public:
    System();
    ~System();

    void run();

private:
    void handlePrintCourse(const std::string& courseId);
    void handlePrintCourses();
    void handleMore();
    void handlePrintSchedule(const std::string& scheduleId);
    void handlePrintSchedules();
    void handleAddSchedule();
    void handleRemoveSchedule(const std::string& scheduleId);
    void handleAddLessonToSchedule(const std::string& scheduleId, const std::string& courseId, const std::string& groupId);
    void handleRemoveLessonFromSchedule(const std::string& scheduleId, const std::string& courseId, const std::string& groupId);
    void handleCheckConflicts(const std::string& scheduleId);
    void handleClear();
    
    // Data management functions
    void handleAddCourse();
    void handleRemoveCourse(const std::string& courseId);
    void handleAddLesson();
    void handleRemoveLesson(const std::string& courseId, const std::string& groupId);
    
    // Original functions
    void handleFindCommonLessons();
    void handlePrintCourseStatistics();
    void handleRecommendCourses(const std::string& scheduleId);
    
    // New analysis functions
    void handleFindTimeConflicts();
    void handleAnalyzeCourseWorkload(const std::string& scheduleId);
    void handleAnalyzeTeacherSchedules(const std::string& teacherName);
    
    void handleHelp();

    void printWelcomeMessage();
    Lesson* findLesson(int courseId, int groupId);
    
    // Helper method to get course name by ID
    std::string getCourseName(int courseId) const;
    
    // Helper method for workload analysis
    void analyzeScheduleWorkload(const Schedule& schedule) const;
    
    // Helper method for user confirmation
    bool getUserConfirmation(const std::string& question) const;
};

#endif // SYSTEM_H