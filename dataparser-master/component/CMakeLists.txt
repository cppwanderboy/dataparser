CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(szDataParer)

#############################################################
SET(CMAKE_CXX_STANDARD 11)

SET(CMAKE_BUILD_TYPE "Release")

SET( CMAKE_CXX_FLAGS "-std=c++11 -O0")

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

#############################################################

INCLUDE_DIRECTORIES(inc/)

#############################################################

ADD_SUBDIRECTORY(src)
