cmake_minimum_required(VERSION 3.9)
project(experiments)

set(CMAKE_CXX_STANDARD 11)

include_directories(./ExternalLibraries/cereal-1.2.2/include)

add_executable(experiments main.cpp Scorer.cpp Scorer.h BracketReader.cpp BracketReader.h Bracket.cpp Bracket.h BracketGenerator.cpp BracketGenerator.h cpt/BackwardCPT.cpp cpt/BackwardCPT.h Simulator.cpp Simulator.h analysis/Statistics.cpp analysis/Statistics.h Constants.h output/Serializer.cpp output/Serializer.h GeneratorConfig.cpp GeneratorConfig.h analysis/Misc.cpp analysis/Misc.h utils/PrintUtils.h utils/FileSystem.h cpt/BaseCPT.cpp cpt/BaseCPT.h cpt/ForwardCPT.cpp cpt/ForwardCPT.h)
add_executable(ml Scorer.cpp Scorer.h BracketReader.cpp BracketReader.h Bracket.cpp Bracket.h BracketGenerator.cpp BracketGenerator.h cpt/BackwardCPT.cpp cpt/BackwardCPT.h Simulator.cpp Simulator.h analysis/Statistics.cpp analysis/Statistics.h Constants.h output/Serializer.cpp output/Serializer.h GeneratorConfig.cpp GeneratorConfig.h analysis/Misc.cpp analysis/Misc.h utils/PrintUtils.h utils/FileSystem.h cpt/BaseCPT.cpp cpt/BaseCPT.h cpt/ForwardCPT.cpp cpt/ForwardCPT.h ml/main.cpp ml/DataGenerator.cpp ml/DataGenerator.h)


find_package(GSL REQUIRED)    # See below (2)
target_link_libraries(experiments GSL::gsl GSL::gslcblas)
target_link_libraries(ml GSL::gsl GSL::gslcblas)

add_executable(experimentsTests Scorer.cpp Scorer.h BracketReader.cpp BracketReader.h Bracket.cpp Bracket.h BracketGenerator.cpp BracketGenerator.h cpt/BackwardCPT.cpp cpt/BackwardCPT.h Simulator.cpp Simulator.h analysis/Statistics.cpp analysis/Statistics.h Constants.h output/Serializer.cpp output/Serializer.h GeneratorConfig.cpp GeneratorConfig.h test/ScorerTest.cpp test/ScorerTest.h test/test.cpp test/BitsetTest.cpp test/BitsetTest.h test/SmoothingTest.cpp test/SmoothingTest.h test/ConditionalProbabilityTableTest.cpp test/ConditionalProbabilityTableTest.h)
target_link_libraries(experimentsTests GSL::gsl GSL::gslcblas)