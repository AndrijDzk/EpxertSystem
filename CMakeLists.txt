cmake_minimum_required(VERSION 3.9)
FUNCTION(PREPEND var prefix)
   SET(listVar "")
   FOREACH(f ${ARGN})
      LIST(APPEND listVar "${prefix}/${f}")
   ENDFOREACH(f)
   SET(${var} "${listVar}" PARENT_SCOPE)
ENDFUNCTION(PREPEND)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(NAME "expert_system")
set(SDIR "srcs")
set(SOURCES
	"ReversePolishNotation.class.coplien.cpp"
	"ReversePolishNotation.class.cpp"
    "Op.class.cpp"
    "Rule.class.coplien.cpp"
    "Rule.class.cpp"
    "Fact.class.cpp"
    "Engine.class.base.cpp"
    "Engine.class.coplien.cpp"
    "Engine.class.cpp"
    "Engine.class.init.cpp"
    "BackwardChaining.class.cpp"
    "BackwardChaining.class.coplien.cpp"
    "State.class.cpp"
    "State.class.coplien.cpp"
    "GetTargets.class.cpp"
    "Parse.cpp"
    "main.cpp")
PREPEND(SOURCES_REL ${SDIR} ${SOURCES})
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -Wextra")
message("EXECUTABLE_OUTPUT_PATH - ${EXECUTABLE_OUTPUT_PATH}")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR} CACHE PATH "Executable output dir" FORCE)
message("EXECUTABLE_OUTPUT_PATH - ${EXECUTABLE_OUTPUT_PATH}")
include_directories(${CMAKE_SOURCE_DIR}/Includes)
add_executable(${NAME} ${SOURCES_REL})