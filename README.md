## Studenti ##

* Marco Colognese
    - VR423791

* Mattia Rossini
    - VR423614



## Compilazione/avvio da /build ##

* Compilazione `CMakeLists.txt` attraverso il comando `cmake .`

* Compilazione del codice sorgente attraverso il comando `make`

* Avvio dei test attraverso il comando `make test`

* Generazione della documentazione attraverso il comando `make doc` che comprende anche una descrizione genarale del progetto nel file `index.html`

* Avvio del tool valgrind attraverso il comando `make valgrind`

* Avvio dell'interprete attraverso il comando `./Interpreter`



## Cosa include il progetto ##

* `CMakeLists.txt`
    - compilazione con warning
    - modalita' RELEASE e DEBUG
    - valgrind (`make valgrind`)
    - test (`make test`)
    - clean (`make clean`)
    - doc (`make doc`)

* `AbstractInterval` Class:
    - specializzazione nel file .cpp
    - classe astratta
    - classe polimorfica
    - metodi virtual
    - metodi final
    - metodi const

* `Bound` Class:
    - specializzazione nel file .cpp
    - metodo con template
    - metodi const
    - overloading costruttore
    - override `operator+` `operator-` `operator*` `operator/`
    - override `operator<` `operator<=` `operator>` `operator>=` `operator==` `operator!=`

* `FloatingPointAbstractInterval` Class & IntegerPointAbstractInterval` Class:
    - sottoclasse di `AbstractInterval`
    - specializzazione nel file .cpp
    - metodi const
    - override `operator+` `operator-` `operator*` `operator/` `operator==`
    - override dei metodi `isFinite()` `intersects()` `width()` `isContainedIn()`

* `Infinity` Class:
    - specializzazione nel file .cpp
    - metodi const
    - override `operator+` `operator-` `operator*` `operator/`
    - override `operator<` `operator<=` `operator>` `operator>=` `operator==` `operator!=`
    - overloading operatori

* `UndefinedOperationException` Class:
    - sottoclasse di `std::exception`
    - override metodo `what()`

* `Test` files:
    - test delle funzionalita' sui metodi delle classi create

* `Intepreter`:
    - utilizzo del container map
    - utilizzo di un iteraor per scorrere gli elementi della map
    - lettura dal file `input.txt`
    - utilizzo pratico della libreria implementata per l'analisi di un programma

* Altre note:
    - codice all'interno di `namespace`
    - costruttori marcati `explicit`
    - libreria `catch2` per il testing
    - metodi marcati `const`
    - Doxygen per la documentazione# ais_interpreter
