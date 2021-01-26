###################################################################
#TEST CMAKELISTS
###################################################################
# test directory CMakeLists.txt
ADD_EXECUTABLE(mytest console_appender_test.cpp)
TARGET_LINK_LIBRARIES(mytest kangaroo)