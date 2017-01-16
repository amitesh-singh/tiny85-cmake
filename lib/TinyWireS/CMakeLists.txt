add_library(tinyWireS  usiTwiSlave.h usiTwiSlave.c TinyWireS.h TinyWireS.cpp)
#declare the current dir as public include dir. you could have include/ dir if you want. ;0
target_include_directories(tinyWireS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})