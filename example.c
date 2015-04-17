#include "src/sqliteInt.h"
#include <string.h>

int main(int argc, char* argv[]) {
    Parse parseObj;
    char *errMsg = 0;
    memset(&parseObj, 0, sizeof(parseObj));
    
    sqlite3RunParser(&parseObj, "select * from test where id > 100 and id < 200 or id between 300 and 400 or id = 1000;", &errMsg);
    //sqlite3RunParser(&parseObj, "select count(*) from test union select id from test where id IN (select id from test1);", &errMsg);
    if( sqlite3MallocFailed()  ){
        parseObj.rc = SQLITE_NOMEM;
    }
    if( parseObj.rc==SQLITE_DONE ) parseObj.rc = SQLITE_OK;
    if (errMsg != NULL) {
        printf("error: %s, error_code:%d \n", errMsg, parseObj.rc);
    }

    /* if (parseObj.sqlType == SQLTYPE_SELECT && parseObj.sql.selectObj) { */
    /*     sqlite3SelectDelete(parseObj.sql.selectObj); */
    /* } */
    return 0;
}
