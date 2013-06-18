
# Path to null device (so no object output)
IF (WIN32)
  SET(NUL NUL)
ELSE(WIN32)
  SET(NUL /dev/null)
ENDIF(WIN32)

FOREACH(inc ${PLUGIN_INCLUDE_DIRECTORIES})
  SET(GCCXML_PLUGIN_TEST_INCLUDES "${GCCXML_PLUGIN_TEST_INCLUDES}" "-I${inc}")
ENDFOREACH(inc)

# Include gcc plugin directories
SET(PLUGIN_INCLUDE_DIRECTORIES
  ${GCCXML_PLUGIN_INCLUDE_DIR}/include
  ${GCCXML_PLUGIN_INCLUDE_DIR}/include/cp
)

# Don't need GXFront headers with the Plugin. But do need the GCC
# headers, so lets test them instead :)
SET(PLUGIN_TESTS
  # These are mostly C99 I think...
  "${GCCXML_PLUGIN_INCLUDE_DIR}/include/ansidecl.h"
  "${GCCXML_PLUGIN_INCLUDE_DIR}/include/auto-host.h"
  # ...
)


SET(PLUGIN_PATH
  ${GCCXML_PLUGIN_OUTPUT_PATH}/gccxml_plugin${CMAKE_SHARED_LIBRARY_SUFFIX})

# Test GCC plugin headers
FOREACH(test ${PLUGIN_TESTS})
  GET_FILENAME_COMPONENT(name "${test}" NAME)
  ADD_TEST(NAME gccxml-plugin_${name}
    COMMAND ${CMAKE_CXX_COMPILER}
      -fplugin=${PLUGIN_PATH}
      -fplugin-arg-gccxml_plugin-xml=plugin-${name}.xml
      ${GCCXML_PLUGIN_TEST_INCLUDES}
      -c ${test} -o ${NUL})
ENDFOREACH(test)

# create an empty test file

FILE(WRITE ${CMAKE_CURRENT_BINARY_DIR}/empty_file.cpp
  "int main(int argc, char*argv[]){return 0;}")

#### Find GCC's libstdc++ headers  ####
#######################################

# C++ stdlib include directory
#FILE(TO_CMAKE_PATH ${GCC_PREFIX}/include/c++/${GCC_VERSION_FULL} GCC_HEADER_PATH)
# Ensure it's got at least the cstdlib header in there.
#FIND_PATH(CXX_HEADER_PATH
#  NAMES cstdlib
#  HINTS ${GCC_HEADER_PATH}
#)

## can't run tests without std library headers
#IF(${CXX_HEADER_PATH} MATCHES "NOTFOUND$")
#  MESSAGE(WARNING "Can't find GCC's C++ headers. Tests won't work without them.")
#ELSE()
#  MESSAGE(STATUS "Found C++ headers in ${CXX_HEADER_PATH}") ENDIF()

# Convert STD C++98 headers #
#############################

# C++ standard library template headers. Can use them to both
# test the code and to generate an XML schema of the C++ standard.
SET(STDLIB98_HEADERS
  algorithm
  bitset
  cassert
  cctype
  cerrno
  cfloat
  ciso646
  climits
  clocale
  cmath
  complex
  complex.h
  csetjmp
  csignal
  cstdarg
  cstddef
  cstdio
  cstdlib
  cstring
  ctime
  cwchar
  cwctype
  cxxabi.h
  deque
  exception
  fenv.h
  fstream
  functional
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
  new
  numeric
  ostream
  queue
  set
  sstream
  stack
  stdexcept
  streambuf
  string
  tgmath.h
  typeinfo
  utility
  valarray
  vector
)

# Add tests for C++98 Standard library headers.
# As these have no file-name suffix, need to specify the language.
FOREACH(header ${STDLIB98_HEADERS})
  GET_FILENAME_COMPONENT(name "${header}" NAME)
  ADD_TEST(NAME stdc++98_${header}
    COMMAND ${CMAKE_CXX_COMPILER}
      -x c++
      -std=c++98
      -fplugin=${PLUGIN_PATH}
      -fplugin-arg-gccxml_plugin-xml=stdc++98-${header}.xml
      -include ${header}
      -c empty_file.cpp
      -o ${NUL}
      )
ENDFOREACH(header)

# Tests on C++11 headers #
##########################

IF(${GCC_VERSION_MINOR} GREATER 6)
  SET(STDLIB11_HEADERS
    array
    atomic
    ccomplex
    cfenv
    chrono
    cinttypes
    condition_variable
    cstdalign
    cstdbool
    cstdint
    ctgmath
    forward_list
    future
    initializer_list
    mutex
    random
    ratio
    regex
    scoped_allocator
    system_error
    thread
    tuple
    type_traits
    typeindex
    unordered_map
    unordered_set
  )

  # Tests on C++11 Standard library headers.
  # As these have no file-name suffix, need to specify the language as
  # well as the -std=c++11 flag
  FOREACH(header ${STDLIB11_HEADERS})
    GET_FILENAME_COMPONENT(name "${header}" NAME)
    ADD_TEST(NAME stdc++11_${header}
      COMMAND ${CMAKE_CXX_COMPILER}
        -fplugin=${PLUGIN_PATH}
        -fplugin-arg-gccxml_plugin-xml=stdc++11-${header}.xml
        -std=c++11
        -x c++
        -include ${header}
        -c empty_file.cpp
        -o ${NUL}
        )
  ENDFOREACH(header)
ENDIF()

