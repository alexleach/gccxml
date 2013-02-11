# Posted by Benoit RAT to cmake archives:
#  http://www.cmake.org/pipermail/cmake/2009-February/027014.html

MACRO (TODAY RESULT)
  IF (CYGWIN)
    EXECUTE_PROCESS(COMMAND "date" "/T" OUTPUT_VARIABLE ${RESULT})
    string(REGEX REPLACE "(..)/(..)/(....).*" "\\3\\2\\1"
           ${RESULT} ${${RESULT}})
  ELSEIF(UNIX)
    EXECUTE_PROCESS(COMMAND "date" "+%d/%m/%Y" OUTPUT_VARIABLE ${RESULT})
    string(REGEX REPLACE "(..)/(..)/(....).*" "\\3\\2\\1"
          ${RESULT} ${${RESULT}})
  ELSE (CYGWIN)
    MESSAGE(SEND_ERROR "date not implemented")
    SET(${RESULT} 000000)
  ENDIF (CYGWIN)
ENDMACRO (TODAY)

