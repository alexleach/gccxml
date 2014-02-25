ADD_DEFINITIONS(
  -DGCCXML_PLUGIN_BASEVER=\"${GCCXML_PLUGIN_BASEVER}\"
  -DGCCXML_PLUGIN_VERSION=\"${GCCXML_PLUGIN_VERSION_MAJOR}.${GCCXML_PLUGIN_VERSION_MINOR}\"
  -DGCCXML_PLUGIN_VERSION_FULL=\"${GCCXML_PLUGIN_VERSION_FULL}\"
  )

INCLUDE_DIRECTORIES(BEFORE
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${GCCXML_PLUGIN_INCLUDE_DIR}/include
  #${GCCXML_PLUGIN_INCLUDE_DIR}/include/cp
)

IF(GCCXML_INSTALL_COMPONENT_NAME_PLUGIN)
  SET(GCCXML_INSTALL_COMPONENT_PLUGIN
    COMPONENT ${GCCXML_INSTALL_COMPONENT_NAME_PLUGIN})
ENDIF(GCCXML_INSTALL_COMPONENT_NAME_PLUGIN)

# Do not inherit library building rules from the parent project.
SET(BUILD_SHARED_LIBS 1)
SET(LIBRARY_OUTPUT_PATH "${GCCXML_PLUGIN_OUTPUT_PATH}")

ADD_DEFINITIONS(-DALMOST_STDC)

ADD_LIBRARY(gccxml_plugin MODULE xml.c gccxml_plugin.c)
SET_TARGET_PROPERTIES(gccxml_plugin PROPERTIES
  PREFIX     ""     #< don't add 'lib' prefix.
  LINK_FLAGS "${FPIC_FLAG} ${CMAKE_SHARED_LINKER_FLAGS}"
  )

IF(APPLE)
  SET(CMAKE_MODULE_LINKER_FLAGS "-undefined dynamic_lookup")
ELSE(APPLE)
  SET_TARGET_PROPERTIES(gccxml_plugin PROPERTIES
    VERSION    "${GCCXML_PLUGIN_VERSION_FULL}"
    SOVERSION  "${GCCXML_PLUGIN_VERSION_FULL}"
    )
ENDIF(APPLE)

# install in standard library directory. Better place to be?
INSTALL_TARGETS(/lib gccxml_plugin)

# Version checks and warnings
IF(${GCC_VERSION_MAJOR} GREATER 3)
  # gcc-4.6 warnings
  IF(${GCC_VERSION_MINOR} EQUAL 6)
    MESSAGE(WARNING
      "GCC 4.6.4 was found - during testing on Arch Linux - to be missing "
      "c-family/c-common.h from its plugin directory. If it's missing from "
      "your installation, please copy it from your GCC 4.6 source tree."
    )
  ENDIF()

  # haven't yet tested 4.7...

  # gcc-4.8 is compiled as C++, so xml.c needs to be, too.
  IF(${GCC_VERSION_MINOR} GREATER 7)
    SET_SOURCE_FILES_PROPERTIES( xml.c PROPERTIES LANGUAGE CXX )
  ENDIF()
ENDIF()
