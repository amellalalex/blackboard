CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT("sockets")

INCLUDE_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/../include"
)

SET("BIN" "socket")
SET("SRC_FILES" "maindoc.c" "serverdoc.c" "clientdoc.c")

ADD_EXECUTABLE(${BIN} ${SRC_FILES})
