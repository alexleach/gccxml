SET(EXE_DIR ".")
IF(EXECUTABLE_OUTPUT_PATH)
  SET(EXE_DIR "${EXECUTABLE_OUTPUT_PATH}")
ENDIF(EXECUTABLE_OUTPUT_PATH)

INCLUDE_DIRECTORIES(
  "${GCCXML_BINARY_DIR}/GXFront"
  "${GCCXML_SOURCE_DIR}/GXFront"
)
MESSAGE("GCCXML_BINARY_DIR: ${GCCXML_BINARY_DIR}")

SET(GCCXML_TEST_INCLUDES "")
GET_DIRECTORY_PROPERTY(GX_INCS INCLUDE_DIRECTORIES)
SET(INCLUDE_DIRECTORIES ${GX_INCS})
MESSAGE("Test includes: ${GX_INCS}")

FOREACH(inc ${GX_INCS})
  SET(GCCXML_TEST_INCLUDES "${GCCXML_TEST_INCLUDES}" "-I${inc}")
ENDFOREACH(inc)
# Add GCC_XML/ to Includes
SET(GCCXML_TEST_INCLUDES "${GCCXML_TEST_INCLUDES}" "-I${GCCXML_BINARY_DIR}")

SET(GX_TESTS
  "${GCCXML_SOURCE_DIR}/GXFront/gxConfiguration.cxx"
  "${GCCXML_SOURCE_DIR}/GXFront/gxConfiguration.h"
  "${GCCXML_SOURCE_DIR}/GXFront/gxDocumentation.cxx"
  "${GCCXML_SOURCE_DIR}/GXFront/gxDocumentation.h"
  "${GCCXML_SOURCE_DIR}/GXFront/gxFlagsParser.cxx"
  "${GCCXML_SOURCE_DIR}/GXFront/gxFlagsParser.h"
  "${GCCXML_SOURCE_DIR}/GXFront/gxFront.cxx"
  "${GCCXML_SOURCE_DIR}/GXFront/gxSystemTools.cxx"
  "${GCCXML_SOURCE_DIR}/GXFront/gxSystemTools.h"

  "${GCCXML_BINARY_DIR}/Testing/TestFullPathInclude.cxx"
  "${GCCXML_SOURCE_DIR}/Testing/TestUsualInclude.cxx"

  # "${CMAKE_CURRENT_BINARY_DIR}/TestFullPathInclude.cxx"
  # "${CMAKE_CURRENT_SOURCE_DIR}/TestUsualInclude.cxx"
)

FOREACH(test ${GX_TESTS})
  GET_FILENAME_COMPONENT(name "${test}" NAME)
  GET_FILENAME_COMPONENT(name_we "${test}" NAME_WE)

  ADD_TEST(NAME gccxml-plugin_${name}
           WORKING_DIRECTORY ${GCCXML_PLUGIN_OUTPUT_PATH}
           COMMAND ${CMAKE_CXX_COMPILER} ${GCCXML_TEST_INCLUDES}
                   -fplugin=./gccxml_plugin${CMAKE_SHARED_LIBRARY_SUFFIX}
                   -fplugin-arg-gccxml_plugin-xml=${name}.gcc.xml
                   -c  ${test})
ENDFOREACH(test)

