## Compiling/starting from /build ##

* Compiling `CMakeLists.txt` via `cmake .` command

* Compiling the source code via the `make` command

* Starting tests with the `make test` command

* Generation of documentation via the `make doc` command which also includes a general description of the project in the `index.html` file

* Starting the valgrind tool with the `make valgrind` command

* Starting the interpreter with the `./Interpreter` command



## What the project includes ##

* `CMakeLists.txt`
     - compilation with warnings
     - RELEASE and DEBUG mode
     - valgrind (`make valgrind`)
     - test (`make test`)
     - clean (`make clean`)
     -doc (`make doc`)

* `AbstractInterval` Class:
     - specialization in the .cpp file
     - abstract class
     - polymorphic class
     - virtual methods
     - final methods
     - methods const

* `Bound` Class:
     - specialization in the .cpp file
     - method with templates
     - methods const
     - constructor overloading
     - override `operator+` `operator-` `operator*` `operator/`
     - override `operator<` `operator<=` `operator>` `operator>=` `operator==` `operator!=`

* `FloatingPointAbstractInterval` Class & IntegerPointAbstractInterval` Class:
     - subclass of `AbstractInterval`
     - specialization in the .cpp file
     - methods const
     - override `operator+` `operator-` `operator*` `operator/` `operator==`
     - method overrides `isFinite()` `intersects()` `width()` `isContainedIn()`

* `Infinity` Class:
     - specialization in the .cpp file
     - methods const
     - override `operator+` `operator-` `operator*` `operator/`
     - override `operator<` `operator<=` `operator>` `operator>=` `operator==` `operator!=`
     - operator overloading

* `UndefinedOperationException` Class:
     - subclass of `std::exception`
     - override `what()` method

* `Test` files:
     - test of the functionality on the methods of the classes created

* `Interpreter`:
     - use of the container map
     - use of an iterator to iterate the elements of the map
     - reading from the `input.txt` file
     - practical use of the implemented library for the analysis of a program

* Other notes:
     - code inside `namespace`
     - constructors marked `explicit`
     - `catch2` library for testing
     - methods marked `const`
     - Doxygen for documentation
