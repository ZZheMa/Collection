set(SRCS
    shell.c
    sqlite3.c
    sqlite3.h
    sqlite3ext.h
   )
   
set(TARGET_NAME sqlite3)

add_library(${TARGET_NAME} ${SRCS})
