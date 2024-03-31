#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
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

Student** read_students(string filename, int& count){
	
	fstream input_file;
	input_file.open(filename,ios::in);
	
	if(!input_file.is_open()){
		cout << "ERROR WHILE OPENING THE FILE" <<endl;
		exit(EXIT_FAILURE);;
	}
    count = 0;
    string line;
    while (getline(input_file, line)) {
        count++;
    }
    input_file.clear();   
    input_file.seekg(0);  // Stream position is resetted here to read the file from the begining 

    Student** students = new Student*[count];
	string temp; //to store the row of file
    for (int i = 0; i < count; ++i) {
        getline(input_file,temp );
		string name_section[2] = {"",""} ;
		int index = 0;
		for (int j = 0; j < temp.length( ) ;j++){ // breaking the row string to name and section
			if(temp[j] == ','){
				j++;
				index = 1;
			}
			name_section[index] +=temp[j];
		}
        students[i] = new Student(name_section[0], name_section[1]);
    }

    input_file.close();
    return students;
}
void deleteStudents(Student** students, int count) {
    for (int i = 0; i < count; ++i) {
        delete students[i];
    }
    delete[] students;
}

int main() {
int count;
    string filename = "C:/Users/Admin/Desktop/Re file handling/students.txt"; 
    Student** students = read_students(filename, count);
    

    Teacher* teacher1 = new Teacher("Tamim Ahmed");
    Teacher* teacher2 = new Teacher("Awais");
    Teacher* teacher3 = new Teacher("Adeel");
    Teacher* teacher4 = new Teacher("Sadaf");
    Teacher* teacher5 = new Teacher("Joddat Fatima");
    Teacher* teacher6 = new Teacher("Waleed");
	//Courses
    Course* course1 = new Course("OOP");
    Course* course2 = new Course("OOPLab");
    Course* course3 = new Course("DS");
    Course* course4 = new Course("ISE");
    Course* course5 = new Course("DM");
    Course* course7 = new Course("CF");
    Course* course8 = new Course("ML");
    
	//rooms
    Room* room1 = new Room("4-17");
    Room* room2 = new Room("4-18");
    Room* room3 = new Room("4-19");
    
    //Labs
    Room* lab1 = new Room("401");
    Room* lab2 = new Room("402");
    
    
    Timetable timetable;

   timetable.addEntry(teacher1, course1, room3, {"Monday", "10:30-12:25"}, {students[0], students[2],students[3]});
  timetable.addEntry(teacher1, course1, room3, {"Tuesday", "11:30-12:25"}, {students[0], students[2],students[3]});
	timetable.addEntry(teacher1, course1, room3, {"Monday", "8:30-10:25"}, {students[5],students[9]});
	timetable.addEntry(teacher1, course1, room3, {"Tuesday", "12:30-1:25"}, {students[5],students[9]});

	timetable.addEntry(teacher2, course4, room1, {"Monday", "8:30-10:25"}, {students[0], students[1],students[2], students[3],students[4]});
  timetable.addEntry(teacher2, course4, room1, {"Tuesday", "10:30-11:30"}, {students[0], students[1],students[2], students[3],students[4]});
  timetable.addEntry(teacher2, course4, room2, {"Monday", "11:30-1:30"}, {students[5], students[6],students[7], students[8],students[9]});
	timetable.addEntry(teacher2, course4, room2, {"Tuesday", "11:30-12:30"}, {students[5], students[6],students[7], students[8],students[9]});

	timetable.addEntry(teacher3, course5, room2, {"Wednesday", "8:30-9:30"}, {students[22], students[23],students[20],students[21]});
  timetable.addEntry(teacher3, course5, room2, {"Thursday", "8:30-10:30"}, {students[22], students[23],students[20],students[21]});

	timetable.addEntry(teacher4, course3, room1, {"Tuesday", "12:30-1:30"}, {students[0], students[1],students[2], students[3],students[4]});
	timetable.addEntry(teacher4, course3, room1, {"Friday", "8:30-10:30"}, {students[0], students[1],students[2], students[3],students[4]});
  timetable.addEntry(teacher4, course3, room2, {"Monday", "10:30-11:25"}, {students[5], students[6],students[7], students[8],students[9]});
	timetable.addEntry(teacher4, course3, room3, {"Tuesday", "9:30-11:25"}, {students[5], students[6],students[7], students[8],students[9]});

  timetable.addEntry(teacher5, course7, room2, {"Wednesday", "10:30-11;25"}, {students[6]});
  timetable.addEntry(teacher4, course8, room3, {"Tuesday", "2:30-4:25"}, {students[15], students[16],students[17], students[18],students[19]});

  timetable.addEntry(teacher6, course2, lab1, {"Thursday", "8:30-11:25"}, {students[0], students[2],students[3]});
	timetable.addEntry(teacher6, course2, lab2, {"Thursday", "11:30-2:25"}, {students[5],students[9]});

	
	cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*"<<endl;
	cout << "*_*_*_*_*_  TIMETABLE FOR BAHRIA UNIVERSITY H-11 CAMPUS, ISLAMABAD  _*_*_*_*_*_*" << endl;
	cout << "*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*"<<endl;
	
	
	
	// REQUIRED QUERIES
	int num;
  cout<<"\n1- Teacher wise time table.\n2- Section wise time table\n3- Student wise time table \n4- Room wise and Lab wise\n";
  cout<<"5- Who is teaching on any specific time and day (8:30 on Monday) ?\n6- What is the time table for specific day(Tuesday)?\n ENTER 0 TO EXIT.\n";

  while(1){
  cout<<"\n\nEnter choice: ";
  cin>>num;

  if(num==1){
    fstream teacherwise_file;
	teacherwise_file.open("Teacher wise Timetable.txt",ios::out);
	//Teacher wise time table 
    map<string, vector<TimetableEntry*>> teacherTimetable = timetable.getTeacherWiseTimetable();
    cout << "\n~~~Teacher wise timetable~~~" << endl << endl;
    for (auto pair : teacherTimetable) {
        cout << pair.first << ":" << endl;
        for (TimetableEntry* entry : pair.second) {
            cout << "  " << entry->getTimeslot() << " - " << entry->getCourseName() << " - " << entry->getRoomName() << endl;
        }
    }
	   cout<<"\n***********************************";
    teacherwise_file.close();
  }

	else if(num==2){  
    //Section wise time table 
    map<string, vector<TimetableEntry*>> sectionTimetable = timetable.getSectionWiseTimetable();
    cout << "\n~~~Section wise timetable~~~" << endl << endl;
    for (auto pair : sectionTimetable) {
        cout << pair.first << ":" << endl;
        for (TimetableEntry* entry : pair.second) {
            cout << "  " << entry->getTimeslot() << " - " << entry->getCourseName() << " - " << entry->getRoomName() << endl;
        }
    }
	cout<<"\n***********************************";
}

	  else if(num==3){
  fstream studentwise_file;
	studentwise_file.open("Student wise Timetable.txt",ios::out);
    //Student wise time table 
    map<string, vector<TimetableEntry*>> studentTimetable = timetable.getStudentWiseTimetable();
    cout << "\n~~~Student-wise timetable~~~" << endl << endl;
    for (auto pair : studentTimetable) {
        cout << pair.first << ":" << endl;
        for (TimetableEntry* entry : pair.second) {
            cout << "  " << entry->getTimeslot() << " - " << entry->getCourseName() << " - " << entry->getRoomName() << endl;
        }
    }
 cout<<"\n***********************************";
    studentwise_file.close();
}

	  else if(num==4){
    //Room wise and Lab wise 
    map<string, vector<TimetableEntry*>> roomTimetable = timetable.getRoomWiseTimetable();
    cout << "\n~~~Room & Lab wise timetable~~~" << endl << endl;
    for (auto pair : roomTimetable) {
        cout << pair.first << ":" << endl;
        for (TimetableEntry* entry : pair.second) {
            cout << "  " << entry->getTimeslot() << " - " << entry->getTeacherName() << " - " << entry->getCourseName() << endl;
        }
	   
}
		   cout<<"\n***********************************";
    }

	  else if(num==5){
    // Who is teaching on any specific time and day (8:30 on Monday) ?
    vector<string> teachersAtTime = timetable.getTeachersAtTime("Monday", "8:30-10:25");
    cout << "\n~~~Teachers teaching at 8:30 on Monday~~~" << endl;
    for (auto teacher : teachersAtTime) {
        cout << teacher << " "<<endl;
    }
    cout<<"\n***********************************";
	  }

	  else if(num==6){
    //What is the time table for specific day(Tuesday)?
    vector<string> timetableForTuesday = timetable.getTimetableForDay("Tuesday");
    cout << "\n~~~Timetable for Tuesday~~~" << endl << endl;
    for (auto entry : timetableForTuesday) {
        cout << entry << endl;
    }
		  cout<<"\n***********************************";
	  }
else{
cout<<"***You EXITED the timetable system***";
break;
} 
}

    delete teacher1;
    delete teacher2;
    delete teacher3;
    delete teacher4;
    delete teacher5;
    delete teacher6;
	  
    delete course1;
    delete course2;
    delete course3;
    delete course4;
    delete course5;
    delete course7;
    delete course8;
	  
    delete room1;
    delete room2;
    delete room3;
    delete lab1;
    delete lab2;
    deleteStudents(students, count);

}
