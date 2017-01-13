add_library(spiSoft spiSoft.h spiSoft.cpp)
#declare the current dir as public include dir. you could have include/ dir if you want. ;0
target_include_directories(spiSoft PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})