SET(EXE_DIR ".")
IF(EXECUTABLE_OUTPUT_PATH)
  SET(EXE_DIR "${EXECUTABLE_OUTPUT_PATH}")
ENDIF(EXECUTABLE_OUTPUT_PATH)

INCLUDE_DIRECTORIES(
  "${GCCXML_BINARY_DIR}/GXFront"
  "${GCCXML_SOURCE_DIR}/GXFront"
)
MESSAGE("GCCXML_BINARY_DIR: ${GCCXML_BINARY_DIR}")

SET(gccxml_dashI_args "")
GET_DIRECTORY_PROPERTY(GX_INCS INCLUDE_DIRECTORIES)
FOREACH(inc ${GX_INCS})
  SET(gccxml_dashI_args ${gccxml_dashI_args} "-I${inc}")
ENDFOREACH(inc)

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

  "${GCCXML_SOURCE_DIR}/Testing/TestFullPathInclude.cxx"
  "${GCCXML_BINARY_DIR}/Testing/TestUsualInclude.cxx"

  # "${CMAKE_CURRENT_BINARY_DIR}/TestFullPathInclude.cxx"
  # "${CMAKE_CURRENT_SOURCE_DIR}/TestUsualInclude.cxx"
)

FOREACH(test ${GX_TESTS})
  GET_FILENAME_COMPONENT(name "${test}" NAME)
  GET_FILENAME_COMPONENT(name_we "${test}" NAME_WE)
  ADD_TEST("gccxml-plugin_${name}"
    gcc${CMAKE_EXECUTABLE_SUFFIX} ${gccxml_dashI_args} ${test} 
        -fplugin=libgccxml_plugin.${CMAKE_SHARED_LIBRARY_SUFFIX}
        -fplugin-arg-libgccxml_plugin-xml=${name}.gcc.xml
  WORKING_DIRECTORY ${GCCXML_BINARY_DIR}/lib
  )
ENDFOREACH(test)

