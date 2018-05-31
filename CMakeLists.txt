cmake_minimum_required(VERSION 3.5)

project(AhoCorasick)

set(CMAKE_CXX_STANDARD 11)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(FullSubstringSearch AhoCorasick/src/main.cpp AhoCorasick/src/AhoCorasick.cpp
AhoCorasick/src/AhoCorasick.h AhoCorasick/src/Bohr.cpp AhoCorasick/src/Bohr.h AhoCorasick/src/Unit.cpp AhoCorasick/src/Unit.h)

add_executable(WildCardSearch WildCard/src/main.cpp WildCard/src/AhoCorasick.cpp WildCard/src/AhoCorasick.h
WildCard/src/Bohr.cpp WildCard/src/Bohr.h WildCard/src/Unit.cpp WildCard/src/Unit.h)

add_executable(AhoCorasicktest test/AhoCorasicktest.cpp AhoCorasick/src/AhoCorasick.cpp AhoCorasick/src/AhoCorasick.h AhoCorasick/src/Bohr.cpp AhoCorasick/src/Bohr.h AhoCorasick/src/Unit.cpp AhoCorasick/src/Unit.h)

add_executable(WildCardSearchtest test/WildCardtest.cpp WildCard/src/AhoCorasick.cpp WildCard/src/AhoCorasick.h WildCard/src/Bohr.cpp WildCard/src/Bohr.h WildCard/src/Unit.cpp WildCard/src/Unit.h)

target_link_libraries(AhoCorasicktest ${GTEST_LIBRARIES} pthread)
target_link_libraries(WildCardSearchtest ${GTEST_LIBRARIES} pthread)

add_test(TestAhoCorasick "./AhoCorasicktest")
add_test(TestWildCardSearch "./WildCardSearchtest")
