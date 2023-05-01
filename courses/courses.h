#ifndef COURSES_H
#define COURSES_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

class Courses{
    public:
        Courses();
        Courses(vector<string> prefixes);
        
        void add_prefix(string prefix);
        void add_course(string course);
        void print_courses();

        string generate_random_course();


    private:
        vector<string> prefixes;
        unordered_set<string> courses;
        string generate_course_code();
};
#include "courses.cpp"

#endif