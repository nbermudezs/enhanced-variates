cmake_minimum_required(VERSION 3.9)
project(experiments)

set(CMAKE_CXX_STANDARD 11)

add_executable(experiments main.cpp Scorer.cpp Scorer.h BracketReader.cpp BracketReader.h Bracket.cpp Bracket.h BracketGenerator.cpp BracketGenerator.h ConditionalProbabilityTable.cpp ConditionalProbabilityTable.h Simulator.cpp Simulator.h analysis/Statistics.cpp analysis/Statistics.h)