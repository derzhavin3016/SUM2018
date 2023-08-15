cpmaddpackage(
  NAME
  googletest
  GITHUB_REPOSITORY
  google/googletest
  GIT_TAG
  release-1.12.1
  VERSION
  1.12.1
  OPTIONS
  "INSTALL_GTEST OFF")

list_dirs(UNIT_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

set(TESTLIST)

foreach(DIR ${UNIT_DIRS})
  add_subdirectory(${DIR})
endforeach()

message(STATUS "Collected unit tests: ${TESTLIST}")

foreach(TEST ${TESTLIST})
  target_include_directories(${TEST} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(${TEST} PRIVATE gtest gtest_main)

  target_compile_features(${TEST} PRIVATE cxx_std_20)
  target_include_directories(${TEST} PRIVATE ${CMAKE_SOURCE_DIR}/include)
endforeach()

# Unit tests
foreach(TEST ${TESTLIST})
  add_test(NAME ${TEST} COMMAND ${TEST})
  set_property(TEST ${TEST} PROPERTY LABELS unit)
endforeach()
