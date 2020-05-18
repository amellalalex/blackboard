CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT("sockets")

# Include headers
INCLUDE_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/../include"
)

# Normal binary
SET("BIN" "sockets")
SET("SRC" "main.c" "server.c" "client.c")
ADD_EXECUTABLE(${BIN} ${SRC})
TARGET_LINK_LIBRARIES(${BIN} "pthread")
