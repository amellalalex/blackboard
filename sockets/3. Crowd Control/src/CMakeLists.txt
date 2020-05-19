CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT("sockets")

# Header files
INCLUDE_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/../include"
)

# IPC binary
SET("BIN_IPC" "ipc")
SET("SRC_IPC" "ipc.c")
ADD_EXECUTABLE(${BIN_IPC} ${SRC_IPC})

# Client binary
SET("BIN_CLI" "client")
SET("SRC_CLI" "client.c")
ADD_EXECUTABLE(${BIN_CLI} ${SRC_CLI})
