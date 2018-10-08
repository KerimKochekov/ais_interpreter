PROJECT(ais_interpreter)
CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
INCLUDE(CheckCXXCompilerFlag)

set(CMAKE_CACHEFILE_DIR .)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY .)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY .)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY .)


# MAKEFILE
CHECK_CXX_COMPILER_FLAG(-std=c++14 COMPILER_SUPPORTS_CXX14)
IF (COMPILER_SUPPORTS_CXX14)
    ADD_COMPILE_OPTIONS("-std=c++14")
ELSE ()
    MESSAGE(FATAL_ERROR "Compiler ${CMAKE_CXX_COMPILER} has no C++14 support.")
ENDIF ()

set(BASE_SRCS ../src/Bound.cpp ../include/Bound.hpp ../src/Infinity.cpp ../include/Infinity.hpp ../src/AbstractInterval.cpp ../include/AbstractInterval.hpp
        ../include/UndefinedOperationException.hpp ../include/IntegerAbstractInterval.hpp
        ../include/FloatingPointAbstractInterval.hpp ../src/FloatingPointAbstractInterval.cpp ../src/IntegerAbstractInterval.cpp )
include_directories(../libs/catch2)
#ADD_COMPILE_OPTIONS("-Wall" "-Wextra" "-Wpedantic" "-Werror")
ADD_LIBRARY(ais_interpreter ${BASE_SRCS})

ADD_EXECUTABLE(Interpreter ../src/Interpreter.cpp ${BASE_SRCS})


# TEST
ENABLE_TESTING()
set(EXECUTABLE_OUTPUT_PATH .)
ADD_EXECUTABLE(InfinityTest ../tests/InfinityTest.cpp ${BASE_SRCS})
ADD_TEST(NAME InfinityTest
        COMMAND InfinityTest)


ADD_EXECUTABLE(IntegerIntervalTest ../tests/IntegerIntervalTest.cpp ${BASE_SRCS})
ADD_TEST(NAME IntegerIntervalTest
        COMMAND IntegerIntervalTest)

ADD_EXECUTABLE(FloatingPointIntervalTest ../tests/FloatingPointIntervalTest.cpp ${BASE_SRCS})
ADD_TEST(NAME FloatingPointIntervalTest
        COMMAND FloatingPointIntervalTest)

ADD_EXECUTABLE(BoundTest ../tests/BoundTest.cpp ${BASE_SRCS})
ADD_TEST(NAME BoundTest
        COMMAND BoundTest)


# MODES: Release and Debug
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    ADD_COMPILE_OPTIONS("-g")
    ADD_COMPILE_OPTIONS("-O1")
    IF (CMAKE_COMPILER_IS_GNUCXX)
        ADD_COMPILE_OPTIONS("-ggdb3")
    ELSEIF (CMAKE_CXX_COMPILER_ID EQUAL "Clang")
        ADD_COMPILE_OPTIONS("-fsanitize=address")
        ADD_COMPILE_OPTIONS("-fno-omit-frame-pointer")
    ENDIF ()
ELSEIF (CMAKE_BUILD_TYPE STREQUAL "Release")
    ADD_COMPILE_OPTIONS("-O2")
ENDIF ()


# VALGRIND
find_program(VALGRIND_FOUND valgrind)
if (VALGRIND_FOUND)
    ADD_CUSTOM_TARGET(valgrind COMMAND valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes ./BoundTest ./FloatingPointIntervalTest ./InfinityTest ./IntegerIntervalTest)
ENDIF ()


# DOXYGEN
find_program(DOXYGEN_FOUND doxygen)
IF (DOXYGEN_FOUND)
    add_custom_target(doc
            COMMAND doxygen ../Doxyfile
            COMMENT "Code documentation")
ENDIF ()

