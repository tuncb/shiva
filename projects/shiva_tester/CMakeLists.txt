project(shiva_tester CXX)
cmake_minimum_required(VERSION 2.8.12)

set(SOURCE 
  ./source/BlockingSendReceiveTest.cpp
  ./source/BroadCastTest.cpp
  ./source/DistributionTest.cpp
  ./source/GatherTest.cpp
  ./source/InitializationTest.cpp
  ./source/main.cpp
  ./source/MakeMessageTest.cpp
  ./source/P2PTests.cpp
  ./source/ScatterTest.cpp
  ./source/shiva.vcxproj
  ./source/shiva.vcxproj.filters
  ./source/StaticEnvironment.cpp
  ./source/StaticEnvironment.h
)

set(SHIVA_LIBRARY 
  ../shiva/include/shiva/collective.h
  ../shiva/include/shiva/Communicator.h
  ../shiva/include/shiva/distribution.h
  ../shiva/include/shiva/Environment.h
  ../shiva/include/shiva/error.h
  ../shiva/include/shiva/group.h
  ../shiva/include/shiva/Message.h
  ../shiva/include/shiva/point2point.h
  ../shiva/include/shiva/status.h
  ../shiva/include/shiva/tagdispatcher.h
  ../shiva/include/shiva/utility.h
  ../shiva/include/shiva/Version.h
)

include(../../conan.cmake)
conan_cmake_run(BASIC_SETUP CMAKE_TARGETS CONAN_CMAKE_MULTI
  REQUIRES
    "boost/1.66.0@conan/stable"
)

add_library(shiva_tester SHARED ${SOURCE} ${SHIVA_LIBRARY})
target_include_directories(shiva_tester PRIVATE "../shiva/include/")
target_link_libraries(shiva_tester msmpi.lib)
conan_target_link_libraries(shiva_tester)

source_group("shiva_library" FILES ${SHIVA_LIBRARY})
