# UML Class Diagram - Student Portal

```
  +----------------------+
  |       Person         |
  |----------------------|
  | # name : string      |
  |----------------------|
  | + show() : virtual   |
  +----------------------+
             ^
             | inherits
  +----------------------+          +---------------------------+
  |       Student        |  stored  |   vector<Student>         |
  |----------------------|<---------|   students                |
  | + id : int           |   in     +---------------------------+
  | + marks : int        |             used by: loadFile(),
  |----------------------|             saveFile(), main()
  | + getName() : string |
  | + grade() : string   |
  | + show() override    |
  +----------------------+
```
