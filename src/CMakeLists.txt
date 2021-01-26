###################################################################
#SRC CMAKELISTS
###################################################################

# CMakeLists for src directory
PROJECT(naruto)

file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR} *.cpp )

# static library
ADD_LIBRARY(naruto STATIC ${srcs})
SET_TARGET_PROPERTIES(naruto PROPERTIES OUTPUT_NAME "naruto")
SET_TARGET_PROPERTIES(naruto PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(naruto PROPERTIES CLEAN_DIRECT_OUTPUT 1)





