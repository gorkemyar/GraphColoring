#include "courses.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

Courses::Courses(){
    ;
}

Courses::Courses(vector<string> prefixes){
    for (auto p : prefixes) {
        add_prefix(p);
    }
}

void Courses::add_prefix(string prefix){
    prefixes.push_back(prefix);
}

void Courses::add_course(string course){
    courses.insert(course);
}

void Courses::print_courses(){
    for (auto c : courses) {
        cout << c << endl;
    }
}

string Courses::generate_course_code(){
    string number = to_string(rand() % 1000);
    if (number.size() == 1) {
        number = "00" + number;
    } else if (number.size() == 2) {
        number = "0" + number;
    }
    return number;
}


string Courses::generate_random_course(){
    string prefix = prefixes[rand() % prefixes.size()];
    string number = generate_course_code();

    string course = prefix + number;
    while (courses.find(course) != courses.end()) {
        number = generate_course_code();
        course = prefix + number;
    }
    courses.insert(course);
    return course;
}