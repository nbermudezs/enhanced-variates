cmake_minimum_required(VERSION 3.9)
project(experiments)

set(CMAKE_CXX_STANDARD 11)

include_directories(./ExternalLibraries/cereal-1.2.2/include)

add_executable(experiments main.cpp Scorer.cpp Scorer.h BracketReader.cpp BracketReader.h Bracket.cpp Bracket.h BracketGenerator.cpp BracketGenerator.h ConditionalProbabilityTable.cpp ConditionalProbabilityTable.h Simulator.cpp Simulator.h analysis/Statistics.cpp analysis/Statistics.h Constants.h output/Serializer.cpp output/Serializer.h)

find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(experiments GSL::gsl GSL::gslcblas)