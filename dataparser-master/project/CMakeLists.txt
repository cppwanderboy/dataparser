PROJECT(parser_demo)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#############################################################
SET(CMAKE_CXX_FLAGS "-std=c++11")

SET(CMAKE_BUILD_TYPE "Release")

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
#############################################################

INCLUDE_DIRECTORIES(/home/xinhong/parser/component/inc)
LINK_DIRECTORIES(/home/xinhong/parser/project/demo)
ADD_EXECUTABLE(runFinal main.cpp)
TARGET_LINK_LIBRARIES(runFinal libszDataParer.a)