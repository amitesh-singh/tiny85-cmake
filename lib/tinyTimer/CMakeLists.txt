add_library(tinyTimer tinyTimer.h tinyTimer.cpp)
#declare the current dir as public include dir. you could have include/ dir if you want. ;0
target_include_directories(tinyTimer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})