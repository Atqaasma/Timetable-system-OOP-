#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct TimeSlot {
    string day;
    string time;
};
class Teacher {

    string name;

	public:
		
    Teacher(string n){
		name = n;
	}
    string getName(){
        return name;
    }
};

class Course {

    string name;

	public:
    
	Course(string n){
		name = n;
	}
    string getName(){
        return name;
    }
};

class Room {

    string name;

	public:
    
	Room(string n){
		name = n;
	}
    string getName(){
        return name;
    }
};

class Student {
	
    string name;
    string section; 

	public:
    
	Student(string n, string s){
		name = n;
		section = s;
	}
    string getName(){ 
		return name; 
	}
    string getSection(){ 
		return section; 
	}
};

class TimetableEntry {

	public: //should be private as well, make a getter and then replace the direct calls with that getter and make it private
    
	Teacher* teacher;
    Course* course;
    Room* room;
    vector<Student*> students;
    TimeSlot timeslot;

	public:
		
    TimetableEntry(Teacher* t, Course* c, Room* r, TimeSlot ts){
		teacher = t;
		course = c;
		room = r;
		timeslot = ts;
	}
    void addStudent(Student* student) {
        students.push_back(student);
    }
    string getTeacherName(){
        return teacher->getName();
    }
    string getCourseName(){
        return course->getName();
    }
    string getRoomName(){
        return room->getName();
    }
    string getTimeslot(){
        return timeslot.day + " " + timeslot.time;
    }
    vector<Student*> getStudents(){
        return students;
    }
};

class Timetable {

	int maxStudents;
    vector<TimetableEntry*> entries;

public:
    Timetable(){
    	maxStudents = 5;
	}
    void addEntry(Teacher* teacher, Course* course, Room* room, TimeSlot timeslot, vector<Student*> students) {
        if (students.size() > 5) {
        	cout << "LIMIT FOR SECTION IS "<< maxStudents << endl;
        	return;
    	}

	    for (TimetableEntry* entry : entries) {
	        if (entry->timeslot.day == timeslot.day && entry->timeslot.time == timeslot.time && entry->room->getName() == room->getName() && entry->teacher->getName() == teacher->getName()) {
	            cout << "TIME SLOT IS ALREADY BOOKED :( "<< entry->timeslot.day <<" - "<<entry->timeslot.time<< endl;
	            return;
	        }
	    }
		
		TimetableEntry* entry = new TimetableEntry(teacher, course, room, timeslot);
        for (Student* student : students) {
            entry->addStudent(student);
        }
        entries.push_back(entry);
    }

    vector<string> getTeachersAtTime(string day,string time){
        vector<string> teachers;
        for (TimetableEntry* entry : entries) {
            if (entry->getTimeslot() == (day + " " + time)) {
                teachers.push_back(entry->getTeacherName());
            }
        }
        return teachers;
    }

    vector<string> getTimetableForDay(string day){
        vector<string> timetable;
        for (TimetableEntry* entry : entries) {
            if (entry->timeslot.day == day) {
                timetable.push_back(entry->getTeacherName() + " is teaching " + entry->getCourseName() + " in room " + entry->getRoomName() + " at " + entry->getTimeslot());
            }
        }
        return timetable;
    }

    map<string, vector<TimetableEntry*> > getTeacherWiseTimetable(){
        map<string, vector<TimetableEntry*>> teacherTimetable;
        for (TimetableEntry* entry : entries) {
            teacherTimetable[entry->getTeacherName()].push_back(entry);
        }
        return teacherTimetable;
    }

    map<string, vector<TimetableEntry*> > getSectionWiseTimetable(){
        map<string, vector<TimetableEntry*>> sectionTimetable;
        for (TimetableEntry* entry : entries) {
            for (Student* student : entry->getStudents()) {
                string section = student->getSection();
                sectionTimetable[section].push_back(entry);
            }
        }
        return sectionTimetable;
    }

    map<string, vector<TimetableEntry*> > getStudentWiseTimetable(){
        map<string, vector<TimetableEntry*>> studentTimetable;
        for (TimetableEntry* entry : entries) {
            for (Student* student : entry->getStudents()) {
                studentTimetable[student->getName()].push_back(entry);
            }
        }
        return studentTimetable;
    }

    map<string, vector<TimetableEntry*> > getRoomWiseTimetable(){
        map<string, vector<TimetableEntry*>> roomTimetable;
        for (TimetableEntry* entry : entries) {
            roomTimetable[entry->getRoomName()].push_back(entry);
        }
        return roomTimetable;
    }
};

int main() {

    Student* student1 = new Student("Student_Hajra","BSE-4");
    //Student student1("Student_Hajira","A");
    Student* student2 = new Student("Student_Moiza","BSE-2A");
    Student* student3 = new Student("Student_Mubrra","BSE-8");
    Student* student4 = new Student("Student_Atqa","BSE-2B");
    Student* student5 = new Student("Student_5","BSE-2B");

    Teacher* teacher1 = new Teacher("Faizan");
    Teacher* teacher2 = new Teacher("Harris");

    Course* course1 = new Course("DS");
    Course* course2 = new Course("OOP");
    Course* course3 = new Course("LA");
    Course* course4 = new Course("OOPLab");
    
	//rooms
    Room* room1 = new Room("4-17");
    Room* room2 = new Room("4-18");
   // Room* room3 = new Room("4-19");
    
    //Labs
    Room* lab1 = new Room("401");
    Room* lab2 = new Room("402");
    
    
    Timetable timetable;

    timetable.addEntry(teacher1, course1, room1, {"Monday", "8:30"}, {student1, student2});
    timetable.addEntry(teacher2, course2, room2, {"Tuesday", "10:00"}, {student1});
	timetable.addEntry(teacher1, course3, lab1, {"Wednesday", "10:00"}, {student4, student3});
	timetable.addEntry(teacher2, course2, room2, {"Monday", "10:00"}, {student1, student2});
	timetable.addEntry(teacher1, course4, lab2, {"Tuesday", "10:00"}, {student1, student2,student3, student4,student5});

	
	cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*"<<endl;
	cout << "*_*_*_*_*_  TIMETABLE FOR BAHRIA UNIVERSITY H-11 CAMPUS, ISLAMABAD  _*_*_*_*_*_*" << endl;
	cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*"<<endl;
	
	
	
	// REQUIRED QUERIES
	
	//Teacher wise time table 
    map<string, vector<TimetableEntry*>> teacherTimetable = timetable.getTeacherWiseTimetable();
    cout << "\n\nTeacher wise timetable:" << endl << endl;
    for (auto pair : teacherTimetable) {
        cout << pair.first << ":" << endl;
        for (TimetableEntry* entry : pair.second) {
            cout << "  " << entry->getTimeslot() << " - " << entry->getCourseName() << " - " << entry->getRoomName() << endl;
        }
    }

    //Section wise time table 
    map<string, vector<TimetableEntry*>> sectionTimetable = timetable.getSectionWiseTimetable();
    cout << "\n\nSection wise timetable:" << endl << endl;
    for (auto pair : sectionTimetable) {
        cout << pair.first << ":" << endl;
        for (TimetableEntry* entry : pair.second) {
            cout << "  " << entry->getTimeslot() << " - " << entry->getCourseName() << " - " << entry->getRoomName() << endl;
        }
    }

    //Student wise time table 
    map<string, vector<TimetableEntry*>> studentTimetable = timetable.getStudentWiseTimetable();
    cout << "\n\nStudent-wise timetable:" << endl << endl;
    for (auto pair : studentTimetable) {
        cout << pair.first << ":" << endl;
        for (TimetableEntry* entry : pair.second) {
            cout << "  " << entry->getTimeslot() << " - " << entry->getCourseName() << " - " << entry->getRoomName() << endl;
        }
    }

    //Room wise and Lab wise 
    map<string, vector<TimetableEntry*>> roomTimetable = timetable.getRoomWiseTimetable();
    cout << "\n\nRoom & Lab wise timetable:" << endl << endl;
    for (auto pair : roomTimetable) {
        cout << pair.first << ":" << endl;
        for (TimetableEntry* entry : pair.second) {
            cout << "  " << entry->getTimeslot() << " - " << entry->getTeacherName() << " - " << entry->getCourseName() << endl;
        }
    }

    // Who is teaching on any specific time and day (8:30 on Monday) ?
    vector<string> teachersAtTime = timetable.getTeachersAtTime("Monday", "8:30");
    cout << "\n\nTeachers teaching at 8:30 on Monday: " << endl;
    for (auto teacher : teachersAtTime) {
        cout << teacher << " ";
    }
    cout << endl;

    //What is the time table for specific day(Tuesday)?
    vector<string> timetableForTuesday = timetable.getTimetableForDay("Tuesday");
    cout << "\n\nTimetable for Tuesday:" << endl << endl;
    for (auto entry : timetableForTuesday) {
        cout << entry << endl;
    }


    delete teacher1;
    delete teacher2;
    delete course1;
    delete course2;
    delete room1;
    delete room2;
    delete student1;
    delete student2;

}

