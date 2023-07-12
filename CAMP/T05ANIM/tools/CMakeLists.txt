set(TOOLLIST anim)

foreach(TOOL ${TOOLLIST})
  add_subdirectory(${TOOL})
  message(STATUS "Included subdirectory: ${TOOL}")
  set_target_properties(${TOOL} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                           "${CMAKE_BINARY_DIR}/bin/")
endforeach()

set(TOOLLIST
    "${TOOLLIST}"
    PARENT_SCOPE)
