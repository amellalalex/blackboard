CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT("sockets")

INCLUDE_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/../include"
)

SET("BIN" "sockets")
SET("SRC_FILES" "main.c" "server.c" "client.c")

ADD_EXECUTABLE(${BIN} ${SRC_FILES})
