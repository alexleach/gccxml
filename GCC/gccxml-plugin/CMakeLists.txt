CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(gccxml_plugin)

# We are not using shared libraries.  Skip any RPATH.
SET(CMAKE_SKIP_RPATH 1)

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
MATH(EXPR GCC_XML_GCC_BVERSION "(${BUILDING_GCC_MAJOR} * 10000 + ${BUILDING_GCC_MINOR} * 100 + ${BUILDING_GCC_PATCH})")

SET(GCC_XML_GCC_VERSION 0x0${GCC_XML_GCC_BVERSION})
MESSAGE("gccxml version  ${GCC_XML_GCC_VERSION}")

#-----------------------------------------------------------------------------
# Place gccxml-plugin in lib directory
SET(LIBRARY_OUTPUT_PATH "${gccxml_plugin_BINARY_DIR}/lib" CACHE PATH
  "Output directory for gccxml-plugin.[so|dll]")
MARK_AS_ADVANCED(LIBRARY_OUTPUT_PATH)

MESSAGE("LIBRARY OUTPUT PATH ${LIBRARY_OUTPUT_PATH}")

# Installation component names for stand-alone GCC-XML.
# SET(GCCXML_INSTALL_COMPONENT_NAME_DOCUMENTATION Documentation)
# SET(GCCXML_INSTALL_COMPONENT_NAME_RUNTIME_EXECUTABLE RuntimeExecutable)
# SET(GCCXML_INSTALL_COMPONENT_NAME_RUNTIME_LIBRARY RuntimeLibrary)

# Extra debug flags
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -gdwarf-3 -O0 -Wall -pedantic")
SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer -mtune=generic -Os")

MESSAGE("CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG} -g3 -gdwarf-3 -O0 -Wall -pedantic")
MESSAGE("CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE} -fomit-frame-pointer -mtune=generic -Os")


# Dashboard support
#INCLUDE(CTest)

# Test GCC_XML.
#ENABLE_TESTING()
#SET(GCCXML_ADD_TESTS 1)

# Build plugin.
SUBDIRS(plugin)
