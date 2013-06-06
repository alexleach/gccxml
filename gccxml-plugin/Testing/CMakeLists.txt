#SET(EXE_DIR ".")
#IF(EXECUTABLE_OUTPUT_PATH)
#  SET(EXE_DIR "${EXECUTABLE_OUTPUT_PATH}")
#ENDIF(EXECUTABLE_OUTPUT_PATH)



# Inlucde gcc plugin directories
#SET(GCCXML_PLUGIN_TEST_INCLUDES
SET(PLUGIN_INCLUDE_DIRECTORIES
  ${GCCXML_PLUGIN_INCLUDE_DIR}/include
  ${GCCXML_PLUGIN_INCLUDE_DIR}/include/cp
)

#GET_DIRECTORY_PROPERTY(GCCXML_PLUGIN_TEST_INCLUDES INCLUDE_DIRECTORIES)
#SET(INCLUDE_DIRECTORIES ${GCCXML_PLUGIN_TEST_INCLUDES})
#MESSAGE("Test includes: ${GCCXML_PLUGIN_TEST_INCLUDES}")

IF (WIN32)
  SET(NUL NUL)
ELSE(WIN32)
  SET(NUL /dev/null)
ENDIF(WIN32)

FOREACH(inc ${PLUGIN_INCLUDE_DIRECTORIES})
  SET(GCCXML_PLUGIN_TEST_INCLUDES "${GCCXML_PLUGIN_TEST_INCLUDES}" "-I${inc}")
ENDFOREACH(inc)
 
# Don't need GXFront headers with the Plugin. But do need the GCC
# headers, so lets test them instead :)
SET(PLUGIN_TESTS
  # GCC plugin headers. These are mostly C99 I think..
  "${GCCXML_PLUGIN_INCLUDE_DIR}/include/ansidecl.h"
  "${GCCXML_PLUGIN_INCLUDE_DIR}/include/auto-host.h"

  #"${GCCXML_PLUGIN_INCLUDE_DIR}/Testing/TestFullPathInclude.cxx"
  #"${GCCXML_PLUGIN_INCLUDE_DIR}/Testing/TestUsualInclude.cxx"
)

SET(STDLIB_HEADERS
  algorithm
  array
  atomic
  bitset
  cassert
  ccomplex
  cctype
  cerrno
  cfenv
  cfloat
  chrono
  cinttypes
  ciso646
  climits
  clocale
  cmath
  complex
  complex.h
  #condition_
  csetjmp
  csignal
  cstdalign
  cstdarg
  cstdbool
  cstddef
  cstdint
  cstdio
  cstdlib
  cstring
  ctgmath
  ctime
  cwchar
  cwctype
  cxxabi.h
  deque
  exception
  fenv.h
  #forward_li
  fstream
  functional
  future
  #initialize
  iomanip
  ios
  iosfwd
  iostream
  istream
  iterator
  limits
  list
  locale
  map
  memory
  mutex
  new
  numeric
  ostream
  queue
  random
  ratio
  regex
  #scoped_all
  set
  sstream
  stack
  stdexcept
  streambuf
  string
  #system_err
  tgmath.h
  thread
  tuple
  #type_trait
  typeindex
  typeinfo
  #unordered_
  utility
  valarray
  vector
)

#FOREACH(header ${STDLIB_HEADERS})
FIND_PATH(HEADER_PATH
  NAMES cstdlib
  HINTS /usr/include/c++/${GCC_VERSION_FULL}
)

IF(${HEADER_PATH} MATCHES "NOTFOUND$")
  MESSAGE("can't find GCC's C++ headers!")
ELSE()
  MESSAGE("Found C++ headers in ${HEADER_PATH}")
ENDIF()

# Try and find full path to ${header}, storing full path in ${_HEADER}
FOREACH(header ${STDLIB_HEADERS})
  SET(PLUGIN_TESTS ${PLUGIN_TESTS} ${HEADER_PATH}/${header})
ENDFOREACH(header)
MESSAGE("PLUGIN_TESTS ${PLUGIN_TESTS}")

FOREACH(test ${PLUGIN_TESTS})
  GET_FILENAME_COMPONENT(name "${test}" NAME)
  #GET_FILENAME_COMPONENT(name_we "${test}" NAME_WE)

  ADD_TEST(NAME gccxml-plugin_${name}
           WORKING_DIRECTORY ${GCCXML_PLUGIN_OUTPUT_PATH}
           COMMAND ${CMAKE_CXX_COMPILER}
                   -fplugin=./gccxml_plugin${CMAKE_SHARED_LIBRARY_SUFFIX}
                   -fplugin-arg-gccxml_plugin-xml=${name}.gcc.xml
                   ${GCCXML_PLUGIN_TEST_INCLUDES}
                   -c  ${test} -o ${NUL})
ENDFOREACH(test)

