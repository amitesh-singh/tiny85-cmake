add_library(tinySPI tinySPI.h tinySPI.cpp)
#declare the current dir as public include dir. you could have include/ dir if you want. ;0
target_include_directories(tinySPI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})