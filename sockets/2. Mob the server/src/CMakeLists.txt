CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT("sockets")

# Normal binary
SET("BIN" "sockets")
SET("SRC" "main.c")
ADD_EXECUTABLE(${BIN} ${SRC})
TARGET_LINK_LIBRARIES(${BIN} "pthread")
