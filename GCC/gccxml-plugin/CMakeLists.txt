CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(gccxml_plugin)

#SET(GCCXML_PLUGIN_VERSION_MAJOR 4)
#Set(GCCXML_PLUGIN_VERSION_MINOR 8)
#Set(GCCXML_PLUGIN_VERSION_PATCH 1)

# Tell GCC_XML that we are providing gccxml_cc1plus for it.
SET(GCCXML_NATIVE_CC1PLUS 0)

#-----------------------------------------------------------------------------
# Load the platform configuration.

IF(EXISTS "${GCCCONFIG_BINARY_DIR}/gcc_platform.cmake")
  INCLUDE("${GCCCONFIG_BINARY_DIR}/gcc_platform.cmake")
ELSE(EXISTS "${GCCCONFIG_BINARY_DIR}/gcc_platform.cmake")
  MESSAGE(FATAL_ERROR "Cannot find gcc_platform.cmake.")
ENDIF(EXISTS "${GCCCONFIG_BINARY_DIR}/gcc_platform.cmake")

#-----------------------------------------------------------------------------
# Set GCCXML plugin install name

MESSAGE("gccxml_plugin_path ${CMAKE_INSTALL_PREFIX}/lib/libgccxml${CMAKE_SHARED_LIBRARY_SUFFIX}")
SET(GCCXML_PLUGIN_PATH "${CMAKE_INSTALL_DIR}/libgccxml${CMAKE_SHARED_LIBRARY_SUFFIX}")

# Set version info
#MATH(EXPR GCC_XML_GCC_BVERSION "(${GCCXML_PLUGIN_VERSION_MAJOR} * 10000 + ${GCCXML_PLUGIN_VERSION_MINOR} * 100 + ${GCCXML_PLUGIN_VERSION_PATCH})")

#SET(GCC_XML_GCC_VERSION 0x0${GCC_XML_GCC_BVERSION})
#MESSAGE("gccxml version  ${GCC_XML_GCC_VERSION}")

#-----------------------------------------------------------------------------
# Place gccxml-plugin in lib directory
SET(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib" CACHE PATH
  "Output directory for gccxml-plugin.[so|dll]")
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH)

MESSAGE("LIBRARY OUTPUT PATH ${LIBRARY_OUTPUT_PATH}")

# Installation component names for stand-alone GCC-XML.
# SET(GCCXML_INSTALL_COMPONENT_NAME_DOCUMENTATION Documentation)
# SET(GCCXML_INSTALL_COMPONENT_NAME_RUNTIME_EXECUTABLE RuntimeExecutable)
# SET(GCCXML_INSTALL_COMPONENT_NAME_RUNTIME_LIBRARY RuntimeLibrary)

# Extra debug flags
#SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -gdwarf-3 -O0 -Wall -pedantic")
#SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer -mtune=generic -Os")

# Build plugin.
SUBDIRS(plugin)

# Test libgccxml-plugin
IF(GCCXML_ADD_TESTS)
  SUBDIRS(Testing)
ENDIF(GCCXML_ADD_TESTS)

