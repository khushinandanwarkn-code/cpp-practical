# Student Portal (C++ mini project)
Khushboo Nandanwar | Roll No. 49 | AIDS-C

A simple console app for a class teacher. You can add students, see the
whole class with grades and the class average, and search a student by ID.
Everything is saved in students_data.csv, so the data is still there the
next time you open the program.

## Features
- Add a student (ID, name, course, marks)
- Show all students with their grade and the class average
- Search a student by ID
- Saves to students_data.csv and loads it again on start
- Checks wrong input: repeated ID, marks outside 0-100, empty name,
  letters where a number is expected, unknown ID

## Grades
A = 75 and above, B = 60-74, C = 50-59, D = 40-49, F = below 40

## Build and run
    g++ -std=c++17 -Wall -o portal student_portal.cpp
    ./portal        (on Windows: portal.exe)

## Files
- student_portal.cpp - full source code
- students_data.csv - sample data (id,name,course,marks)
- UML.md - class diagram
