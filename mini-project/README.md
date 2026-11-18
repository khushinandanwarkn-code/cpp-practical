# Library Management System (C++ mini project)
Khushboo Nandanwar | Roll No. 49 | AIDS-C

A small console app for a college library. The librarian can add books,
list and search them, issue and return them. Data is saved in books.csv
so nothing is lost when the program closes.

## Features
- Add / list / search (case-insensitive) books
- Issue and return with proper checks (already issued, not issued, wrong ID)
- Data saved to and loaded from books.csv
- Clear error messages using a custom LibraryError exception

## Build and run
    g++ -std=c++17 -Wall -o library p12_library_system.cpp
    ./library        (on Windows: library.exe)

## Files
- p12_library_system.cpp - full source
- books.csv - sample data (id,title,author,available)
- UML.md - class diagram
