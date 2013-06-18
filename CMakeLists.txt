CMAKE_MINIMUM_REQUIRED(VERSION 2.6.3 FATAL_ERROR)
PROJECT(gccxml)

# Place both gccxml_cc1plus and the GCC_XML executables next to each
# other.
SET(EXECUTABLE_OUTPUT_PATH "${gccxml_BINARY_DIR}/bin" CACHE PATH
  "Single output directory for all executables.")
MARK_AS_ADVANCED(EXECUTABLE_OUTPUT_PATH LIBRARY_OUTPUT_PATH)

SET(LC_ALL C)
SET(LANGUAGE C)

# Extra debug flags to help with GCC debugging (lots of macros).
# Also need a debug build of GCC for debugging to work properly...
SET(CMAKE_CXX_FLAGS_DEBUG "${MAKE_CXX_FLAGS_DEBUG} -g3 -gdwarf-3 -O0 -Wall -fPIC")

# Tune for the native CPU.
# If redistributing, change -mtune=native for -mtune=generic
SET(CMAKE_CXX_FLAGS_RELEASE "${MAKE_CXX_FLAGS_DEBUG} -fomit-frame-pointer -mtune=native -O2 -Os -fPIC")

# Dashboard support
INCLUDE(CTest)

# Test GCC_XML.
ENABLE_TESTING()

# SET VERSION INFORMATION
INCLUDE(VERSION)

SUBDIRS(gccxml-plugin)

# Use CPack to build a redistributable installer.
## hmmm... looks useful..
#INCLUDE("${CMAKE_CURRENT_SOURCE_DIR}/gccxmlCPack.cmake")
