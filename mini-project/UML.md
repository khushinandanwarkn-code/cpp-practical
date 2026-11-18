# UML Class Diagram - Student Portal

```
 +--------------------------+          +-------------------------------+
 |  Person                  |          |  PortalError                  |
 |--------------------------|          |  (derives runtime_error)      |
 | # name : string          |          +-------------------------------+
 |--------------------------|                         ^ throws
 | + show() : virtual       |                         |
 +--------------------------+          +-------------------------------+
              ^                        |  Portal                       |
              | inherits               |-------------------------------|
 +--------------------------+  1    *  | - students : vector<Student>  |
 |  Student                 |<>--------| - fileName : string           |
 |--------------------------|          |-------------------------------|
 | - id : int               |          | + load()                      |
 | - course : string        |          | + save()                      |
 | - marks : int            |          | + add(id, name, course, marks)|
 |--------------------------|          | + find(id) : Student          |
 | + grade() : string       |          | + showAll()                   |
 | + show() override        |          +-------------------------------+
 | + toCSV() : string       |
 +--------------------------+
```
