###################################################################
#TEST CMAKELISTS
###################################################################
# test directory CMakeLists.txt
#nartuo test build function 
function(nartuo_test test_name)
  if(NARTUO_UNIT_TEST)
    message(STATUS "Build skunk uinit test: ${test_name}")
    set(SRCS)
    
    if(${ARGC} EQUAL 1)
      message(FATAL_ERROR "Build skunk uinit test: ${test_name} failed because of the SRC list empty")
    else()
      # loop find the unit test source file in the test dir 
      set(INDEX 1)
      while(INDEX LESS ${ARGC})
        list(APPEND SRCS ${ARGV${INDEX}})
        math(EXPR INDEX "${INDEX} + 1")
      endwhile()
      
      add_executable(${test_name} ${SRCS})
      target_link_libraries(${test_name} gtest nartuo)
    endif()
  endif()
endfunction(nartuo_test)
# Test nartuo 
nartuo_test(HelloWorld test/naruto_test.cpp)