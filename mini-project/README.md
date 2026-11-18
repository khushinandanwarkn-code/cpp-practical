# Student Portal (C++ mini project)
Khushboo Nandanwar | Roll No. 49 | AIDS-C

A simple console app for a class teacher. You can add students,
see all of them with grades, and search by ID. Data is saved in
students_data.csv, so it is still there the next time you run it.

## Features
- Add student (ID, name, marks)
- Show all students with grade
- Search by ID
- Save and load from students_data.csv
- Error messages for repeated ID, marks outside 0-100 and letters instead of numbers

## Grades
A = 75+, B = 60-74, C = 40-59, F = below 40

## Run
g++ student_portal.cpp -o portal
./portal
