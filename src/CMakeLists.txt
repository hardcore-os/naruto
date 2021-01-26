###################################################################
#SRC CMAKELISTS
###################################################################

# CMakeLists for src directory
PROJECT(kangaroo)

file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR} *.cpp )

# static library
ADD_LIBRARY(kangaroo STATIC ${srcs})
SET_TARGET_PROPERTIES(kangaroo PROPERTIES OUTPUT_NAME "kangaroo")
SET_TARGET_PROPERTIES(kangaroo PROPERTIES CLEAN_DIRECT_OUTPUT 1)
SET_TARGET_PROPERTIES(kangaroo PROPERTIES CLEAN_DIRECT_OUTPUT 1)





