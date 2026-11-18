# UML Class Diagram - Library Management System

```
 +---------------------------+        +------------------------------+
 |   <<abstract>>            |        |  LibraryError                |
 |   LibraryItem             |        |  (derives runtime_error)     |
 |---------------------------|        +------------------------------+
 | # id : int                |                      ^ throws
 | # title : string          |                      |
 |---------------------------|        +------------------------------+
 | + display() = 0           |        |  Library                     |
 | + getId(), getTitle()     |        |------------------------------|
 +---------------------------+        | - books : map<int, Book>     |
              ^                       | - fileName : string          |
              | inherits              |------------------------------|
 +---------------------------+  1   * | + load() / save()            |
 |   Book                    |<>------| + addBook(id, title, author) |
 |---------------------------|        | + find(id) : Book&           |
 | - author : string         |        | + searchByTitle(word)        |
 | - available : bool        |        | + listAll()                  |
 |---------------------------|        +------------------------------+
 | + display() override      |
 | + issue(), giveBack()     |
 | + toCSV()                 |
 +---------------------------+
```
