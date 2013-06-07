
# Inlucde gcc plugin directories
SET(PLUGIN_INCLUDE_DIRECTORIES
  ${GCCXML_PLUGIN_INCLUDE_DIR}/include
  ${GCCXML_PLUGIN_INCLUDE_DIR}/include/cp
)

# Path to null device (so no object output)
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
)

# C++ standard library template headers. Can use them to both
# test the code and to generate an XML schema of the C++ standard.
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
  condition_variable
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
  forward_list
  fstream
  functional
  future
  initializer_list
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
  scoped_allocator
  set
  sstream
  stack
  stdexcept
  streambuf
  string
  system_error
  tgmath.h
  thread
  tuple
  type_traits
  typeindex
  typeinfo
  unordered_map
  unordered_set
  utility
  valarray
  vector
)

# find C++ stdlib include directory
FIND_PATH(HEADER_PATH
  NAMES cstdlib
  HINTS /usr/include/c++/${GCC_VERSION_FULL}
)

# can't run tests without std library headers
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

SET(PLUGIN_PATH
  ${GCCXML_PLUGIN_OUTPUT_PATH}/gccxml_plugin${CMAKE_SHARED_LIBRARY_SUFFIX})

# run each test.
FOREACH(test ${PLUGIN_TESTS})
  GET_FILENAME_COMPONENT(name "${test}" NAME)
  ADD_TEST(NAME gccxml-plugin_${name}
    COMMAND ${CMAKE_CXX_COMPILER}
      -fplugin=${PLUGIN_PATH}
      -fplugin-arg-gccxml_plugin-xml=${name}.gcc.xml
      ${GCCXML_PLUGIN_TEST_INCLUDES}
      -c ${test} -o ${NUL})
ENDFOREACH(test)

