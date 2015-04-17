
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g")

SET(lemon_parser_sources
    parse.c
    delete.c
    insert.c
    select.c
    update.c
    util.c
    where.c
    tokenize.c
    printf.c
    expr.c
    build.c
    trigger.c
    alter.c
    os_unix.c   
    callback.c
)

ADD_LIBRARY(lemon_parser SHARED ${lemon_parser_sources})

INSTALL(TARGETS lemon_parser
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    )

INSTALL(FILES 
    sqlite3.h
    sqliteInt.h
    hash.h
    os.h
    parse.h
    os_common.h
    keywordhash.h
    DESTINATION include/lemon
    )
