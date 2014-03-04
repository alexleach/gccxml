SET(gccxml_plugin_SOURCE_FILES
    xml.c
    gccxml_plugin.c
  )

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

ADD_LIBRARY(gccxml_plugin MODULE ${gccxml_plugin_SOURCE_FILES})
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

  # gcc-4.x warnings
  IF(${GCC_VERSION_MINOR} EQUAL 6)
    MESSAGE(WARNING
      "GCC 4.6.4 was found during testing, to be missing a couple of headers: "
      "c-family/c-common.h and libiberty.h from the plugin/include directory. "
      "If these are missing from your installation, please copy them from the "
      " GCC source tree, into the relevant installation location."
    )
  ELSEIF(${GCC_VERSION_MINOR} EQUAL 7)
    MESSAGE(WARNING
      "GCC 4.7.3 was found to be missing libiberty.h from its installed headers. "
      "If copied from the source tree over to the installation plugin/include "
      "directory, compilation should work fine."
    )
  ENDIF()


  # gcc-4.7 and above are compiled as C++, so xml.c needs to be, too.
  # gcc-4.7 uses cxxabi.h instead of demangle.h
  IF(${GCC_VERSION_MINOR} GREATER 6)
    SET_SOURCE_FILES_PROPERTIES(xml.c PROPERTIES LANGUAGE CXX)
  ENDIF()
ENDIF()
