#include "Lecture.h"
#include "Schedule.h"

#include <cassert>

int main() {
    Schedule original(1);
    original.addLesson(new Lecture(
        "Lecture", 101, "Monday", 9, 11, "E101", "Dr. Smith", 1));

    Lecture overlapping(
        "Lecture", 102, "Monday", 10, 12, "E102", "Dr. Jones", 1);
    Lecture separate(
        "Lecture", 103, "Tuesday", 10, 12, "E103", "Dr. Brown", 1);

    assert(original.hasConflict(&overlapping));
    assert(!original.hasConflict(&separate));
    assert(original.totalHours() == 2);

    Schedule copied = original;
    assert(copied.getId() == original.getId());
    assert(copied.getLessons().size() == original.getLessons().size());
    assert(copied.getLessons().front() != original.getLessons().front());

    copied.removeLesson(101, 1);
    assert(copied.getLessons().empty());
    assert(original.getLessons().size() == 1);

    return 0;
}
