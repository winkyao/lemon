
#include "gtest/gtest.h"
#include "../src/sqliteInt.h"
#include <string.h>
#include <sys/time.h>

long getTime() {
    struct timeval iTime;
    gettimeofday(&iTime, NULL);
    long lTime = ((long) iTime.tv_sec) * 1000000 + (long) iTime.tv_usec;
    return lTime;
}

Token *findKey(Expr *expr, const char *key) {
    if (!expr) { return NULL; }

    if (expr->op == TK_EQ && expr->pLeft != NULL) {
        if (strncmp((const char*)expr->pLeft->token.z, key, expr->pLeft->token.n) == 0) {
            return &expr->pLeft->token;
        }
    }

    if (expr->pLeft != NULL) {
        Token *token = findKey(expr->pLeft, key);
        if (token != NULL) { return token; }
    }

    if (expr->pRight != NULL) {
        Token *token = findKey(expr->pRight, key);
        if (token != NULL) { return token; }
    }

    return NULL;
}

TEST(LemonTest, testPerformance) {
    Parse *parseObj = sqlite3ParseNew();
    char *errMsg = 0;
    long time_start = getTime();
    for (int i = 0; i < 1000000; i++) {
        resetParseObject(parseObj);
        int errNum = sqlite3RunParser(parseObj, "SELECT id, name FROM test WHERE name = 'test' AND id = 1000;", &errMsg);
        
        Select *selectObj = parseObj->parsed.array[0].result.selectObj;
        strcmp(selectObj->pSrc->a[0].zName, "test");
        Token *pToken = findKey(selectObj->pWhere, "id");
        sqlite3SelectDelete(selectObj);
        parseObj->parsed.array[0].result.selectObj = NULL;
    }

    long time_end = getTime();

    printf("time escaped:%ld\n", time_end - time_start);
    sqlite3ParseDelete(parseObj);
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
