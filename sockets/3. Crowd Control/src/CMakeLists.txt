CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT("sockets")

# Header files
INCLUDE_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/../include"
)

# IPC binary
SET("BIN_IPC" "ipc")
SET("SRC_IPC"
  "ipc.c"
  "client_handler.c"
)
ADD_EXECUTABLE(${BIN_IPC} ${SRC_IPC})
TARGET_LINK_LIBRARIES(${BIN_IPC}
  "pthread"
)
TARGET_COMPILE_OPTIONS(${BIN_IPC} BEFORE PUBLIC "-g")

# Client binary
SET("BIN_CLI" "client")
SET("SRC_CLI" "client.c")
ADD_EXECUTABLE(${BIN_CLI} ${SRC_CLI})
TARGET_LINK_LIBRARIES(${BIN_CLI}
  "pthread"
)
TARGET_COMPILE_OPTIONS(${BIN_CLI} BEFORE PUBLIC "-g")

# Testing binary
SET("BIN_TEST" "test")
SET("SRC_TEST" "test.c")
ADD_EXECUTABLE(${BIN_TEST} ${SRC_TEST})
TARGET_LINK_LIBRARIES(${BIN_TEST}
 "cmocka"
 "-Wl,--wrap=read,--wrap=write"
)
