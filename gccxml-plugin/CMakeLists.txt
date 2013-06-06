CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(gccxml_plugin)

# Tell GCC_XML that we are providing gccxml_cc1plus for it.
SET(GCCXML_NATIVE_CC1PLUS 0)

#-----------------------------------------------------------------------------
# Load the platform configuration.

#IF(EXISTS "${GCCCONFIG_BINARY_DIR}/gcc_platform.cmake")
#  INCLUDE("${GCCCONFIG_BINARY_DIR}/gcc_platform.cmake")
#ELSE(EXISTS "${GCCCONFIG_BINARY_DIR}/gcc_platform.cmake")
#  #MESSAGE(FATAL_ERROR "Cannot find gcc_platform.cmake.")
#ENDIF(EXISTS "${GCCCONFIG_BINARY_DIR}/gcc_platform.cmake")

# Get base plugin dir for installed gcc.
EXEC_PROGRAM(${CMAKE_C_COMPILER}
  ARGS "-print-file-name=plugin"
  OUTPUT_VARIABLE GCCXML_PLUGIN_INCLUDE_DIR
)

# get system GCC version
EXEC_PROGRAM(${CMAKE_C_COMPILER}
  ARGS "-dumpversion"
  OUTPUT_VARIABLE GCC_VERSION_FULL)

#-----------------------------------------------------------------------------
# Set GCCXML plugin install name

SET(GCCXML_PLUGIN_PATH "${CMAKE_INSTALL_DIR}/gccxml${CMAKE_SHARED_LIBRARY_SUFFIX}")

#-----------------------------------------------------------------------------
# Place gccxml-plugin in lib directory
SET(GCCXML_PLUGIN_OUTPUT_PATH "${CMAKE_BINARY_DIR}" CACHE PATH
  "Output directory for gccxml-plugin.${CMAKE_SHARED_LIBRARY_SUFFIX}")
MARK_AS_ADVANCED(GCCXML_PLUGIN_OUTPUT_PATH)

MESSAGE("GCCXML PLUGIN OUTPUT PATH ${GCCXML_PLUGIN_OUTPUT_PATH}")

# Build plugin.
SUBDIRS(plugin)

# Test libgccxml-plugin
IF(GCCXML_ADD_TESTS)
  SUBDIRS(Testing)
ENDIF(GCCXML_ADD_TESTS)

