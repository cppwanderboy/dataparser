ADD_LIBRARY(${PROJECT_NAME} STATIC ${IO_ENGINE} file_reactor.cpp file_init.cpp)
SET(CMAKE_CXX_FLAGS_DEBUG  "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")