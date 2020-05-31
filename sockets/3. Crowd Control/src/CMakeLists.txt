CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
PROJECT("sockets")

# Header files
INCLUDE_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/../include"
  "${PROJECT_SOURCE_DIR}/../include/cmocka"
)

# IPC client API library
SET("LIB_API" "api")
SET("SRC_API" "client_api.c" "client_api.cc")
ADD_LIBRARY(${LIB_API} ${SRC_API})

# CMocka library
SET("LIB_CMOCKA" "cmocka")
SET("SRC_CMOCKA" "cmocka/cmocka.c")
ADD_LIBRARY(${LIB_CMOCKA} STATIC ${SRC_CMOCKA})

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
  ${LIB_API}
)
TARGET_COMPILE_OPTIONS(${BIN_CLI} BEFORE PUBLIC "-g")

# Testing binary
SET("BIN_TEST" "test")
SET("SRC_TEST" "test.c")
ADD_EXECUTABLE(${BIN_TEST} ${SRC_TEST})
TARGET_LINK_LIBRARIES(${BIN_TEST}
 ${LIB_CMOCKA}
 "-Wl,--wrap=read,--wrap=write"
)

# Maps binary (TEMPORARY)
SET("BIN_MAPS" "maps")
SET("SRC_MAPS" "maps.cc")
ADD_EXECUTABLE(${BIN_MAPS} ${SRC_MAPS})
