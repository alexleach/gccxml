PROJECT(gccxml_plugin)

# --------------------------------
# Get installed gcc's plugin/ path
#  e.g. /usr/lib/gcc/x86_64-linux-gnu/4.8.1/plugin/

EXEC_PROGRAM(${CMAKE_C_COMPILER}
  ARGS "-print-file-name=plugin"
  OUTPUT_VARIABLE GCCXML_PLUGIN_INCLUDE_DIR
)

# ----------------------
# get system GCC version

EXEC_PROGRAM(${CMAKE_C_COMPILER}
  ARGS "-dumpversion"
  OUTPUT_VARIABLE GCC_VERSION_FULL)

MESSAGE("GCC VERSION ${GCC_VERSION_FULL}")

# ----------------------------------------------------
# Find the directory containing your compiler (ie. gcc)

GET_FILENAME_COMPONENT(
  GCC_BINDIR
  ${CMAKE_C_COMPILER}
  PATH
)

# -------------------------
# Compiler's install prefix

FILE(TO_CMAKE_PATH "${GCC_BINDIR}/.." GCC_PREFIX)

#----------------------------
# Set some useful Debug flags

SET(CMAKE_CXX_FLAGS_DEBUG "${MAKE_CXX_FLAGS_DEBUG} -g3 -gdwarf-3 -O0 -Wall")
SET(CMAKE_CXX_FLAGS_RELEASE "${MAKE_CXX_FLAGS_DEBUG} -fomit-frame-pointer -mtune=generic -Os")

#-----------------------------------------------------------------------------
# Set GCCXML plugin install name

SET(GCCXML_PLUGIN_PATH "${CMAKE_INSTALL_DIR}/gccxml${CMAKE_SHARED_LIBRARY_SUFFIX}")

#-----------------------------------------------------------------------------
# Place gccxml-plugin in lib directory

SET(GCCXML_PLUGIN_OUTPUT_PATH "${CMAKE_BINARY_DIR}" CACHE PATH
  "Output directory for gccxml-plugin.${CMAKE_SHARED_LIBRARY_SUFFIX}")
MARK_AS_ADVANCED(GCCXML_PLUGIN_OUTPUT_PATH)

MESSAGE("GCCXML PLUGIN OUTPUT PATH ${GCCXML_PLUGIN_OUTPUT_PATH}")

# `make build`
#############

SUBDIRS(plugin)

# `make test`
############

SUBDIRS(Testing)

