#include "Schedule.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

#include <sstream>  // בשביל stringstream
#include "Lecture.h"
#include "Tutorial.h"
#include "Lab.h"
#include <fstream>  // חשוב לכלול את זה
#include <utility>
Schedule::Schedule() : id(0) {}
Schedule::Schedule(int scheduleId) : id(scheduleId) {}

Schedule::Schedule(const Schedule& other) : id(other.id) {
    lessons.reserve(other.lessons.size());
    for (const auto* lesson : other.lessons) {
        lessons.push_back(lesson ? lesson->clone() : nullptr);
    }
}

Schedule& Schedule::operator=(const Schedule& other) {
    if (this == &other) {
        return *this;
    }

    vector<Lesson*> copiedLessons;
    copiedLessons.reserve(other.lessons.size());
    for (const auto* lesson : other.lessons) {
        copiedLessons.push_back(lesson ? lesson->clone() : nullptr);
    }

    for (auto* lesson : lessons) {
        delete lesson;
    }
    lessons = std::move(copiedLessons);
    id = other.id;
    return *this;
}

Schedule::Schedule(Schedule&& other) noexcept
    : id(other.id), lessons(std::move(other.lessons)) {
    other.id = 0;
}

Schedule& Schedule::operator=(Schedule&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    for (auto* lesson : lessons) {
        delete lesson;
    }
    id = other.id;
    lessons = std::move(other.lessons);
    other.id = 0;
    return *this;
}

int Schedule:: getId() const {
	return id;
}
void Schedule::setId(int newid) {
	id = newid;
}

void Schedule::addLesson(Lesson* lesson) {
	for (size_t i = 0; i < lessons.size(); i++) {
		if (lessons[i]->getDay() == lesson->getDay()) {
			int start1 = lessons[i]->getStartHour();
			int end1 = start1 + lessons[i]->getDuration();
			int start2 = lesson->getStartHour();
			int end2 = start2 + lesson->getDuration();

			if ((start1 < end2) && (start2 < end1)) {
				cout << "\n" << string(50, '=') << endl;
				cout << "            *** CONFLICT DETECTED ***" << endl;
				cout << string(50, '=') << endl;
				cout << "Cannot add lesson for Course " << lesson->getCourseId() 
					 << " (Group " << lesson->getGroupId() << ")" << endl;
				cout << "Conflicts with existing Course " << lessons[i]->getCourseId() 
					 << " (Group " << lessons[i]->getGroupId() << ")" << endl;
				cout << "\nTime conflict on " << lesson->getDay() << ":" << endl;
				cout << "  Existing lesson: " << (start1 < 10 ? "0" : "") << start1 << ":00-" 
					 << (end1 < 10 ? "0" : "") << end1 << ":00" << endl;
				cout << "  New lesson:      " << (start2 < 10 ? "0" : "") << start2 << ":00-" 
					 << (end2 < 10 ? "0" : "") << end2 << ":00" << endl;
				cout << "\nLESSON NOT ADDED due to scheduling conflict." << endl;
				cout << string(50, '=') << endl;
				return;
			}
		}
	}
	lessons.push_back(lesson);
	cout << "SUCCESS: Lesson added for Course " << lesson->getCourseId() 
		 << " (Group " << lesson->getGroupId() << ") on " << lesson->getDay() 
		 << " at " << (lesson->getStartHour() < 10 ? "0" : "") << lesson->getStartHour() 
		 << ":00-" << (lesson->getStartHour() + lesson->getDuration() < 10 ? "0" : "") 
		 << (lesson->getStartHour() + lesson->getDuration()) << ":00" << endl;
}

void Schedule::addLessonForce(Lesson* lesson) {
	// Force add lesson without conflict checking
	lessons.push_back(lesson);
	cout << "SUCCESS: Lesson FORCEFULLY added for Course " << lesson->getCourseId() 
		 << " (Group " << lesson->getGroupId() << ") on " << lesson->getDay() 
		 << " at " << (lesson->getStartHour() < 10 ? "0" : "") << lesson->getStartHour() 
		 << ":00-" << (lesson->getStartHour() + lesson->getDuration() < 10 ? "0" : "") 
		 << (lesson->getStartHour() + lesson->getDuration()) << ":00" << endl;
	cout << "\033[1;33m? WARNING: This lesson conflicts with existing lessons in your schedule!\033[0m" << endl;
}

void Schedule::removeLesson(int courseId, int groupId) {
	bool found = false;

	// לולאה לאחור כדי למחוק בלי לפגוע באינדקסים
	for (int i = lessons.size() - 1; i >= 0; --i) {
		if (lessons[i]->getCourseId() == courseId &&
			lessons[i]->getGroupId() == groupId) {

			delete lessons[i]; // שחרור זיכרון
			lessons.erase(lessons.begin() + i); // הסרה מה־vector
			found = true;
		}
	}

	if (found) {
		std::cout << "Lesson(s) removed successfully." << std::endl;
	}
	else {
		std::cout << "Lesson not found." << std::endl;
	}
}


// Implementation of the getLessons method
vector<Lesson*>& Schedule::getLessons() {
    return lessons;
}

// Implementation of the const getLessons method
const vector<Lesson*>& Schedule::getLessons() const {
    return lessons;
}

void Schedule::printSchedule() const {
	if (lessons.empty()) {
		cout << "Schedule is empty." << endl;
		return;
	}

	// ANSI Color codes for different lesson types
	const string COLOR_RESET = "\033[0m";
	const string COLOR_LECTURE = "\033[1;34m";     // Bright Blue for Lectures
	const string COLOR_TUTORIAL = "\033[1;32m";    // Bright Green for Tutorials
	const string COLOR_LAB = "\033[1;33m";         // Bright Yellow for Labs
	const string COLOR_CONFLICT = "\033[1;31m";    // Bright Red for Conflicts
	const string COLOR_HEADER = "\033[1;36m";      // Bright Cyan for Headers

	// Define days of the week
	vector<string> days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	
	// Find the time range (earliest to latest)
	int earliestHour = 24, latestHour = 0;
	for (const auto& lesson : lessons) {
		int startHour = lesson->getStartHour();
		int endHour = startHour + lesson->getDuration();
		if (startHour < earliestHour) earliestHour = startHour;
		if (endHour > latestHour) latestHour = endHour;
	}
	
	// Ensure reasonable bounds (typical academic day)
	if (earliestHour > 8) earliestHour = 8;
	if (latestHour < 18) latestHour = 18;

	// Print schedule header with statistics
	cout << "\n" << string(150, '=') << endl;
	cout << COLOR_HEADER << "                                    WEEKLY TIMETABLE - SCHEDULE " << id << COLOR_RESET << endl;
	cout << string(150, '=') << endl;

	// Calculate and display statistics
	int lectureCount = 0, tutorialCount = 0, labCount = 0;
	for (const auto& lesson : lessons) {
		if (lesson->getType() == "Lecture") lectureCount++;
		else if (lesson->getType() == "Tutorial") tutorialCount++;
		else if (lesson->getType() == "Lab") labCount++;
	}

	cout << "  " << COLOR_LECTURE << "Lectures: " << setw(3) << lectureCount << COLOR_RESET
		 << "  |  " << COLOR_TUTORIAL << "Tutorials: " << setw(3) << tutorialCount << COLOR_RESET
		 << "  |  " << COLOR_LAB << "Labs: " << setw(3) << labCount << COLOR_RESET
		 << "  |  Total Hours: " << setw(3) << totalHours() << endl;
	cout << string(150, '-') << endl;

	// Print legend with colored symbols/markers for each type
	cout << "  " << COLOR_LECTURE << "[LEC] Lectures" << COLOR_RESET 
		 << "   " << COLOR_TUTORIAL << "[TUT] Tutorials" << COLOR_RESET
		 << "   " << COLOR_LAB << "[LAB] Labs" << COLOR_RESET
		 << "   " << COLOR_CONFLICT << "[!!!] Conflicts" << COLOR_RESET << endl;
	cout << string(150, '=') << endl;

	// Fixed column widths - all day columns have exactly the same width
	const int timeColWidth = 8;
	const int dayColWidth = 18;  // Fixed width for all day columns

	// Helper function to get color for lesson type
	auto getColorForLesson = [&](const Lesson* lesson) -> string {
		if (lesson->getType() == "Lecture") return COLOR_LECTURE;
		else if (lesson->getType() == "Tutorial") return COLOR_TUTORIAL;
		else if (lesson->getType() == "Lab") return COLOR_LAB;
		return COLOR_RESET;
	};

	// Helper function to wrap text to fit in fixed width
	auto wrapText = [dayColWidth](const string& text, int maxLines = 3) -> vector<string> {
		vector<string> lines;
		if (text.empty()) {
			lines.push_back("");
			return lines;
		}
		
		string remaining = text;
		int lineCount = 0;
		
		while (!remaining.empty() && lineCount < maxLines) {
			if (remaining.length() <= dayColWidth - 1) {
				lines.push_back(remaining);
				break;
			} else {
				// Find best break point (space or punctuation)
				int breakPoint = dayColWidth - 1;
				for (int i = dayColWidth - 1; i >= dayColWidth - 5 && i >= 0; i--) {
					if (remaining[i] == ' ' || remaining[i] == ',' || remaining[i] == '.') {
						breakPoint = i;
						break;
					}
				}
				
				lines.push_back(remaining.substr(0, breakPoint));
				remaining = remaining.substr(breakPoint);
				if (!remaining.empty() && remaining[0] == ' ') {
					remaining = remaining.substr(1); // Remove leading space
				}
			}
			lineCount++;
		}
		
		// Ensure we always have at least one line
		if (lines.empty()) {
			lines.push_back("");
		}
		
		return lines;
	};

	// Print day headers with color
	cout << left << COLOR_HEADER << setw(timeColWidth) << "Time" << COLOR_RESET;
	for (const string& day : days) {
		cout << "|" << COLOR_HEADER << setw(dayColWidth) << (" " + day) << COLOR_RESET;
	}
	cout << "|" << endl;

	// Print separator line under headers
	cout << string(timeColWidth, '-') << "+";
	for (int i = 0; i < 7; i++) {
		cout << string(dayColWidth, '-');
		if (i < 6) cout << "+";
	}
	cout << "+" << endl;

	// Print each hour row with dynamic number of sub-rows based on content
	for (int hour = earliestHour; hour < latestHour; hour++) {
		string timeStr = (hour < 10 ? "0" : "") + to_string(hour) + ":00";
		
		// Collect all information for each day at this hour
		vector<vector<pair<string, string>>> dayInfoLines(7); // 7 days, pairs of (content, color)
		size_t maxLinesNeeded = 1;
		
		for (int dayIdx = 0; dayIdx < 7; dayIdx++) {
			const string& day = days[dayIdx];
			vector<pair<string, string>> allInfo; // pairs of (content, color)
			
			// Find lessons that occur on this day and time
			vector<Lesson*> lessonsAtTime;
			for (const auto& lesson : lessons) {
				if (lesson->getDay() == day && 
					lesson->getStartHour() <= hour && 
					hour < lesson->getStartHour() + lesson->getDuration()) {
					lessonsAtTime.push_back(lesson);
				}
			}
			
			if (!lessonsAtTime.empty()) {
				if (lessonsAtTime.size() > 1) {
					// Conflict detected
					allInfo.push_back(make_pair("[!!!] CONFLICT", COLOR_CONFLICT));
					allInfo.push_back(make_pair("Multiple lessons", COLOR_CONFLICT));
					allInfo.push_back(make_pair("scheduled", COLOR_CONFLICT));
				} else {
					Lesson* lesson = lessonsAtTime[0];
					string lessonColor = getColorForLesson(lesson);
					string typeSymbol = "";
					if (lesson->getType() == "Lecture") typeSymbol = "[LEC]";
					else if (lesson->getType() == "Tutorial") typeSymbol = "[TUT]";
					else if (lesson->getType() == "Lab") typeSymbol = "[LAB]";
					
					// Course info
					string courseInfo = typeSymbol + " " + to_string(lesson->getCourseId()) + 
										"-G" + to_string(lesson->getGroupId());
					allInfo.push_back(make_pair(courseInfo, lessonColor));
					
					// Teacher info
					string teacherInfo = "T: " + lesson->getTeacherName();
					allInfo.push_back(make_pair(teacherInfo, lessonColor));
					
					// Location info
					string location = lesson->getBuilding();
					if (!lesson->getRoom().empty()) {
						if (!location.empty()) location += " ";
						location += lesson->getRoom();
					}
					if (!location.empty()) {
						string locationInfo = "R: " + location;
						allInfo.push_back(make_pair(locationInfo, lessonColor));
					}
					
					// Time info
					int startH = lesson->getStartHour();
					int endH = startH + lesson->getDuration();
					string timeInfo = (startH < 10 ? "0" : "") + to_string(startH) + ":00-" +
									  (endH < 10 ? "0" : "") + to_string(endH) + ":00";
					allInfo.push_back(make_pair(timeInfo, lessonColor));
				}
			}
			
			// Wrap each piece of information and combine
			for (const auto& infoPair : allInfo) {
				vector<string> wrappedLines = wrapText(infoPair.first);
				for (const string& line : wrappedLines) {
					dayInfoLines[dayIdx].push_back(make_pair(line, infoPair.second));
				}
			}
			
			// Update max lines needed
			if (dayInfoLines[dayIdx].size() > maxLinesNeeded) {
				maxLinesNeeded = dayInfoLines[dayIdx].size();
			}
		}
		
		// Ensure all days have the same number of lines
		for (int dayIdx = 0; dayIdx < 7; dayIdx++) {
			while (dayInfoLines[dayIdx].size() < maxLinesNeeded) {
				dayInfoLines[dayIdx].push_back(make_pair("", COLOR_RESET));
			}
		}
		
		// Print all the lines for this hour
		for (size_t lineIdx = 0; lineIdx < maxLinesNeeded; lineIdx++) {
			// Print time only on first line
			if (lineIdx == 0) {
				cout << setw(timeColWidth) << timeStr;
			} else {
				cout << setw(timeColWidth) << "";
			}
			
			// Print each day's content for this line
			for (int dayIdx = 0; dayIdx < 7; dayIdx++) {
				cout << "|";
				string content = "";
				string color = COLOR_RESET;
				if (lineIdx < dayInfoLines[dayIdx].size()) {
					content = dayInfoLines[dayIdx][lineIdx].first;
					color = dayInfoLines[dayIdx][lineIdx].second;
				}
				cout << " " << color << left << setw(dayColWidth - 1) << content << COLOR_RESET;
			}
			cout << "|" << endl;
		}
		
		// Print separator between hours (except last)
		if (hour < latestHour - 1) {
			cout << string(timeColWidth, '-') << "+";
			for (int i = 0; i < 7; i++) {
				cout << string(dayColWidth, '-');
				if (i < 6) cout << "+";
			}
			cout << "+" << endl;
		}
	}
	
	// Print bottom border
	cout << string(timeColWidth, '-') << "+";
	for (int i = 0; i < 7; i++) {
		cout << string(dayColWidth, '-');
		if (i < 6) cout << "+";
	}
	cout << "+" << endl;
	
	cout << string(150, '=') << endl;
	
	// Print detailed lesson summary organized by type with colors
	cout << COLOR_HEADER << "DETAILED LESSON SUMMARY:" << COLOR_RESET << endl;
	cout << string(150, '-') << endl;
	
	// Group lessons by type for organized display
	vector<Lesson*> lectures, tutorials, labs;
	for (const auto& lesson : lessons) {
		if (lesson->getType() == "Lecture") lectures.push_back(lesson);
		else if (lesson->getType() == "Tutorial") tutorials.push_back(lesson);
		else if (lesson->getType() == "Lab") labs.push_back(lesson);
	}
	
	// Print each type with enhanced formatting and colors
	if (!lectures.empty()) {
		cout << "\n" << COLOR_LECTURE << "[LEC] LECTURES (" << lectures.size() << " total):" << COLOR_RESET << endl;
		for (const auto& lesson : lectures) {
			cout << COLOR_LECTURE << "  + Course " << setw(3) << lesson->getCourseId() 
				 << " Group " << setw(2) << lesson->getGroupId() 
				 << " | " << setw(9) << lesson->getDay() 
				 << " " << (lesson->getStartHour() < 10 ? "0" : "") << lesson->getStartHour() << ":00-" 
				 << (lesson->getStartHour() + lesson->getDuration() < 10 ? "0" : "") 
				 << (lesson->getStartHour() + lesson->getDuration()) << ":00"
				 << " | " << setw(20) << lesson->getTeacherName();
			if (!lesson->getBuilding().empty() || !lesson->getRoom().empty()) {
				cout << " | " << lesson->getBuilding() << " " << lesson->getRoom();
			}
			cout << COLOR_RESET << endl;
		}
	}
	
	if (!tutorials.empty()) {
		cout << "\n" << COLOR_TUTORIAL << "[TUT] TUTORIALS (" << tutorials.size() << " total):" << COLOR_RESET << endl;
		for (const auto& lesson : tutorials) {
			cout << COLOR_TUTORIAL << "  + Course " << setw(3) << lesson->getCourseId() 
				 << " Group " << setw(2) << lesson->getGroupId() 
				 << " | " << setw(9) << lesson->getDay() 
				 << " " << (lesson->getStartHour() < 10 ? "0" : "") << lesson->getStartHour() << ":00-" 
				 << (lesson->getStartHour() + lesson->getDuration() < 10 ? "0" : "") 
				 << (lesson->getStartHour() + lesson->getDuration()) << ":00"
				 << " | " << setw(20) << lesson->getTeacherName();
			if (!lesson->getBuilding().empty() || !lesson->getRoom().empty()) {
				cout << " | " << lesson->getBuilding() << " " << lesson->getRoom();
			}
			cout << COLOR_RESET << endl;
		}
	}
	
	if (!labs.empty()) {
		cout << "\n" << COLOR_LAB << "[LAB] LABS (" << labs.size() << " total):" << COLOR_RESET << endl;
		for (const auto& lesson : labs) {
			cout << COLOR_LAB << "  + Course " << setw(3) << lesson->getCourseId() 
				 << " Group " << setw(2) << lesson->getGroupId() 
				 << " | " << setw(9) << lesson->getDay() 
				 << " " << (lesson->getStartHour() < 10 ? "0" : "") << lesson->getStartHour() << ":00-" 
				 << (lesson->getStartHour() + lesson->getDuration() < 10 ? "0" : "") 
				 << (lesson->getStartHour() + lesson->getDuration()) << ":00"
				 << " | " << setw(20) << lesson->getTeacherName();
			if (!lesson->getBuilding().empty() || !lesson->getRoom().empty()) {
				cout << " | " << lesson->getBuilding() << " " << lesson->getRoom();
			}
			cout << COLOR_RESET << endl;
		}
	}
	
	cout << string(150, '=') << endl;
}

bool Schedule::hasConflict(const Lesson* newLesson) const {
	for (const auto& lesson : lessons) {
		if (lesson->getDay() == newLesson->getDay()) {
			int start1 = lesson->getStartHour();
			int end1 = start1 + lesson->getDuration();
			int start2 = newLesson->getStartHour();
			int end2 = start2 + newLesson->getDuration();
			if ((start1 < end2) && (start2 < end1)) {
				return true;
			}
		}
	}
	return false;
}
int Schedule::totalHours() const {
	int total = 0;
	for (size_t i = 0; i < lessons.size(); i++) {
		total += lessons[i]->getDuration();
	}
	return total;
}
////////////////////////////////////////////////////////
void Schedule::saveToFile(const  string& filename) const {
		ofstream out(filename);

		if (!out) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		// כתיבה של כל שיעור
		for (size_t i = 0; i < lessons.size(); i++) {
			out << lessons[i]->getType() << ","               // Lecture / Tutorial / Lab
				<< lessons[i]->getCourseId() << ","
				<< lessons[i]->getGroupId() << ","
				<< lessons[i]->getTeacherName() << ","
				<< lessons[i]->getDay() << ","
				<< lessons[i]->getStartHour() << ","
				<< lessons[i]->getDuration() << ","
				<< lessons[i]->getBuilding() << ","
				<< lessons[i]->getRoom() << endl;
		}

		out.close();  // סוגרים את הקובץ
		cout << "Schedule saved to " << filename << " successfully." << endl;
	}


/////////////////////////////////////////////////////
void Schedule::loadFromFile(const string& filename) {

		ifstream in(filename);
		if (!in) {
			cerr << "Error opening file: " << filename << endl;
			return;
		}

		string line;
		while (getline(in, line)) {
			stringstream ss(line);
			string type, teacherName, day, building, room;
			int courseId, groupId, startHour, duration;

			// קוראים את השדות לפי פסיקים
			getline(ss, type, ',');
			ss >> courseId;      ss.ignore();
			ss >> groupId;       ss.ignore();
			getline(ss, teacherName, ',');
			getline(ss, day, ',');
			ss >> startHour;     ss.ignore();
			ss >> duration;      ss.ignore();
			getline(ss, building, ',');
			getline(ss, room, ',');

			// יוצרים את האובייקט המתאים לפי סוג השיעור
			Lesson* lesson = nullptr;
			int endHour = startHour + duration; // Calculate endHour from startHour + duration
			if (type == "Lecture") {
				lesson = new Lecture(type, courseId, day, startHour, endHour, room, teacherName, groupId);
			}
			else if (type == "Tutorial") {
				lesson = new Tutorial(type, courseId, day, startHour, endHour, room, teacherName, groupId);
			}
			else if (type == "Lab") {
				lesson = new Lab(type, courseId, day, startHour, endHour, room, teacherName, groupId);
			}

			if (lesson != nullptr) {
				lessons.push_back(lesson);
			}
		}

		in.close();
		cout << "Schedule loaded from " << filename << " successfully." << endl;
	}

// Implementation of the destructor
Schedule::~Schedule() {
    for (auto* lesson : lessons) {
        delete lesson;
    }
    lessons.clear();
}

void Schedule::printConflicts() const {
	vector<pair<int, int>> conflictPairs; // Store pairs of conflicting lesson indices
	bool hasAnyConflicts = false;
	
	// Check all pairs of lessons for conflicts
	for (size_t i = 0; i < lessons.size(); i++) {
		for (size_t j = i + 1; j < lessons.size(); j++) {
			if (lessons[i]->getDay() == lessons[j]->getDay()) {
				int start1 = lessons[i]->getStartHour();
				int end1 = start1 + lessons[i]->getDuration();
				int start2 = lessons[j]->getStartHour();
				int end2 = start2 + lessons[j]->getDuration();
				
				if ((start1 < end2) && (start2 < end1)) {
					conflictPairs.push_back(make_pair(i, j));
					hasAnyConflicts = true;
				}
			}
		}
	}
	
	if (!hasAnyConflicts) {
		cout << "\n--- NO CONFLICTS DETECTED ---" << endl;
		cout << "All lessons in this schedule are properly scheduled without time conflicts." << endl;
		return;
	}
	
	cout << "\n" << string(70, '=') << endl;
	cout << "                    *** SCHEDULE CONFLICTS ***" << endl;
	cout << string(70, '=') << endl;
	cout << "Found " << conflictPairs.size() << " conflict(s) in this schedule:" << endl;
	
	for (size_t k = 0; k < conflictPairs.size(); k++) {
		int i = conflictPairs[k].first;
		int j = conflictPairs[k].second;
		
		cout << "\nCONFLICT #" << (k + 1) << ":" << endl;
		cout << "  Course " << lessons[i]->getCourseId() << " (Group " << lessons[i]->getGroupId() 
			 << ") vs Course " << lessons[j]->getCourseId() << " (Group " << lessons[j]->getGroupId() << ")" << endl;
		cout << "  Both scheduled on " << lessons[i]->getDay() << endl;
		
		int start1 = lessons[i]->getStartHour();
		int end1 = start1 + lessons[i]->getDuration();
		int start2 = lessons[j]->getStartHour();
		int end2 = start2 + lessons[j]->getDuration();
		
		cout << "    Course " << lessons[i]->getCourseId() << ": " 
			 << (start1 < 10 ? "0" : "") << start1 << ":00-" 
			 << (end1 < 10 ? "0" : "") << end1 << ":00" << endl;
		cout << "    Course " << lessons[j]->getCourseId() << ": " 
			 << (start2 < 10 ? "0" : "") << start2 << ":00-" 
			 << (end2 < 10 ? "0" : "") << end2 << ":00" << endl;
		
		// Calculate overlap time
		int overlapStart = max(start1, start2);
		int overlapEnd = min(end1, end2);
		cout << "    Overlap period: " 
			 << (overlapStart < 10 ? "0" : "") << overlapStart << ":00-" 
			 << (overlapEnd < 10 ? "0" : "") << overlapEnd << ":00" << endl;
	}
	
	cout << "\nRECOMMENDATION: Remove one lesson from each conflicting pair or choose different groups." << endl;
	cout << string(70, '=') << endl;
}
































