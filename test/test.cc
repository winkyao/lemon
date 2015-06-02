#include "gtest/gtest.h"
#include "../src/sqliteInt.h"
#include <string.h>

class LemonTest : public testing::Test {
    protected:
        virtual void SetUp() {
            parseObj_ = sqlite3ParseNew();
        }
    
        virtual void TearDown() {
            sqlite3ParseDelete(parseObj_);
        }
        
        /* static void SetUpTestCase() { */
        /*     resetParseObject(&parseObj_); */
        /* } */

        /* static void TearDownTestCase() {} */

        void dup2token_(const unsigned char * src, size_t len) {
            assert(len < 512);
            strncpy(token_, (const char*)src, len);
            token_[len] = 0;
        }

        void dupToken2token_(Token token) {
            dup2token_(token.z, token.n);
        }

        void printExpr_(Expr* expr) {
            if (!expr) { 
                printf("empty\n"); 
                return; 
            }

            dup2token_(expr->span.z, expr->span.n);
            printf("op:%d span:%s\n", expr->op, token_);
            printf("left expr:\n\n");
            printExpr_(expr->pLeft);
            printf("\nright expr:");    
            printExpr_(expr->pRight);
        }
    protected:
        Parse *parseObj_;
        char token_[512];
};

//Parse LemonTest::parseObj_;

TEST_F(LemonTest, testSelectSimple) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    Select* selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(TK_SELECT, selectObj->op);
    EXPECT_EQ(TK_ALL, selectObj->pEList->a[0].pExpr->op);
    EXPECT_STREQ("test", selectObj->pSrc->a[0].zName);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT id, name FROM testdb.test WHERE id = 100", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(TK_SELECT, selectObj->op);
    
    /* from */
    EXPECT_EQ(2, selectObj->pEList->nExpr);
    EXPECT_EQ(TK_ID, selectObj->pEList->a[0].pExpr->op);
    memset(token_, 0, sizeof(token_));
    dup2token_(selectObj->pEList->a[0].pExpr->token.z, selectObj->pEList->a[0].pExpr->token.n);
    EXPECT_STREQ("id", token_) << "len:" << selectObj->pEList->a[0].pExpr->token.n;
    EXPECT_EQ(TK_ID, selectObj->pEList->a[1].pExpr->op);
    dup2token_(selectObj->pEList->a[1].pExpr->token.z, selectObj->pEList->a[1].pExpr->token.n);
    EXPECT_STREQ("name", token_);

    EXPECT_STREQ("testdb", selectObj->pSrc->a[0].zDatabase);
    EXPECT_STREQ("test", selectObj->pSrc->a[0].zName);
    
    /*where*/
    EXPECT_EQ(TK_EQ, selectObj->pWhere->op);
    dup2token_(selectObj->pWhere->span.z, selectObj->pWhere->span.n);
    EXPECT_STREQ("id = 100", token_);
    EXPECT_TRUE(selectObj->pWhere->pLeft && selectObj->pWhere->pRight);
    EXPECT_EQ(TK_ID, selectObj->pWhere->pLeft->op);
    dup2token_(selectObj->pWhere->pLeft->token.z, selectObj->pWhere->pLeft->token.n);
    EXPECT_STREQ("id", token_);

    EXPECT_EQ(TK_INTEGER, selectObj->pWhere->pRight->op);
    dup2token_(selectObj->pWhere->pRight->token.z, selectObj->pWhere->pRight->token.n);
    EXPECT_STREQ("100", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT DATABASE()", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(TK_SELECT, selectObj->op);
    
    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT SLEEP(5)", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(TK_SELECT, selectObj->op);
    ExprList *paramList = selectObj->pEList->a[0].pExpr->pList;
    EXPECT_TRUE(strncmp("5", (const char*)paramList->a[0].pExpr->token.z, paramList->a[0].pExpr->token.n) == 0);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT * FROM nosharding_test WHERE id = 1 AND (id < 50 OR id > 200)", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    selectObj = parseObj_->parsed.array[0].result.selectObj;

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "select @@version_comment limit 1;", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "(SELECT * FROM test WHERE id = 0);", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testMysqlSyntax) {
    char *errMsg = 0;

    int errNum = sqlite3RunParser(parseObj_, "show databases", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SHOW);
    int showtype = parseObj_->parsed.array[0].result.showType;
    EXPECT_EQ(SHOWTYPE_SHOW_DATABASES, showtype);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "show tables;", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SHOW);
    showtype = parseObj_->parsed.array[0].result.showType;
    EXPECT_EQ(SHOWTYPE_SHOW_TABLES, showtype);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "show full tables from test_db;", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SHOW);
    showtype = parseObj_->parsed.array[0].result.showType;
    EXPECT_EQ(SHOWTYPE_SHOW_TABLES, showtype);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testSelectError) {
    char *errMsg = 0;

    int errNum = sqlite3RunParser(parseObj_, "SELECT * FROM", &errMsg);
    EXPECT_GT(errNum, 0);
    EXPECT_TRUE(errMsg != NULL);
    EXPECT_EQ(0, parseObj_->parsed.curSize);
    sqliteFree(errMsg);
    errMsg = NULL;

    // lemon call sqlite3SelectDelete itself to free the subquery Select* object 
    errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test where id = (SELECT id FROM test) OR", &errMsg);
    EXPECT_GT(errNum, 0);
    EXPECT_TRUE(errMsg != NULL);
    EXPECT_EQ(0, parseObj_->parsed.curSize);
    sqliteFree(errMsg);
}

TEST_F(LemonTest, testSelectAlias) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "SELECT id AS id_alias FROM test AS test_alias WHERE id_alias = 1 AND id = 2", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    Select* selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(TK_SELECT, selectObj->op);
    EXPECT_STREQ("id_alias", selectObj->pEList->a[0].zName);
    EXPECT_STREQ("test", selectObj->pSrc->a[0].zName);
    EXPECT_STREQ("test_alias", selectObj->pSrc->a[0].zAlias);
    
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}


TEST_F(LemonTest, testOneSelectComplete) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "SELECT DISTINCT * FROM test AS test_alias WHERE id > 1 AND id < 100 OR id BETWEEN 200 AND 400 OR id = 1000 OR id = 2000 \
            ORDER BY id DESC, name ASC LIMIT 0, 2", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    Select* selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(TK_SELECT, selectObj->op);
    EXPECT_EQ(TK_ALL, selectObj->pEList->a[0].pExpr->op);
    EXPECT_EQ(1, selectObj->isDistinct);
    /* from */
    EXPECT_STREQ("test", selectObj->pSrc->a[0].zName);
    EXPECT_STREQ("test_alias", selectObj->pSrc->a[0].zAlias);

    /*limit*/
    EXPECT_EQ(TK_INTEGER, selectObj->pOffset->op);
    dup2token_(selectObj->pOffset->token.z, selectObj->pOffset->token.n);
    EXPECT_STREQ("0", token_);
    EXPECT_EQ(TK_INTEGER, selectObj->pLimit->op);
    dup2token_(selectObj->pLimit->token.z, selectObj->pLimit->token.n);
    EXPECT_STREQ("2", token_);
    
    /*order by*/
    EXPECT_EQ(2, selectObj->pOrderBy->nExpr);
    dup2token_(selectObj->pOrderBy->a[0].pExpr->token.z, selectObj->pOrderBy->a[0].pExpr->token.n);
    EXPECT_STREQ("id", token_);
    EXPECT_EQ(1, selectObj->pOrderBy->a[0].sortOrder);

    dup2token_(selectObj->pOrderBy->a[1].pExpr->token.z, selectObj->pOrderBy->a[1].pExpr->token.n);
    EXPECT_STREQ("name", token_);
    EXPECT_EQ(0, selectObj->pOrderBy->a[1].sortOrder);

    /* where
     * id > 1 AND id < 100 OR id BETWEEN 200 AND 400 OR id = 1000 OR id = 2000
     */
    Expr* whereExpr = selectObj->pWhere;
    //printExpr_(whereExpr);  
    EXPECT_TRUE(whereExpr->pParent == NULL);
    EXPECT_EQ(TK_OR, whereExpr->op);
    dup2token_(whereExpr->span.z, whereExpr->span.n);
    EXPECT_STREQ("id > 1 AND id < 100 OR id BETWEEN 200 AND 400 OR id = 1000 OR id = 2000", token_);
    Expr* curExpr = whereExpr->pRight, *parentExpr = whereExpr;
    EXPECT_TRUE(parentExpr == curExpr->pParent);

    /* id = 2000*/
    EXPECT_EQ(TK_EQ, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id = 2000", token_);
    parentExpr = curExpr, curExpr = curExpr->pLeft;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    
    EXPECT_EQ(TK_ID, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id", token_);

    curExpr = parentExpr->pRight;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_INTEGER, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("2000", token_);
    
    /*id > 1 AND id < 100 OR id BETWEEN 200 AND 400 OR id = 1000*/
    curExpr = whereExpr->pLeft, parentExpr = whereExpr;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_OR, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id > 1 AND id < 100 OR id BETWEEN 200 AND 400 OR id = 1000", token_);
    
    parentExpr = curExpr, curExpr = curExpr->pRight;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_EQ, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id = 1000", token_);
    
    parentExpr = curExpr, curExpr = curExpr->pLeft;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_ID, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id", token_);

    curExpr = parentExpr->pRight;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_INTEGER, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("1000", token_);

    /*id > 1 AND id < 100 OR id BETWEEN 200 AND 400*/
    curExpr = curExpr->pParent->pParent;

    parentExpr = curExpr, curExpr = curExpr->pLeft;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_OR, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id > 1 AND id < 100 OR id BETWEEN 200 AND 400", token_);
    
    /**
     *  BETWEEN
     */   
    /*id BETWEEN 200 AND 400*/
    parentExpr = curExpr, curExpr = curExpr->pRight;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_BETWEEN, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id BETWEEN 200 AND 400", token_);
    
    /* 200 AND 400 is in pList*/
    EXPECT_TRUE(curExpr->pRight == NULL && curExpr->pList != NULL);

    parentExpr = curExpr, curExpr = curExpr->pLeft;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_ID, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id", token_);
    
    ExprList* pList = curExpr->pParent->pList;
    EXPECT_EQ(2, pList->nExpr);
    dup2token_(pList->a[0].pExpr->span.z, pList->a[0].pExpr->span.n);
    EXPECT_STREQ("200", token_);

    dup2token_(pList->a[1].pExpr->span.z, pList->a[1].pExpr->span.n);
    EXPECT_STREQ("400", token_);
    
    curExpr = curExpr->pParent->pParent;

    /*id > 1 AND id < 100*/
    parentExpr = curExpr, curExpr = curExpr->pLeft;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_AND, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id > 1 AND id < 100", token_);
    
    /* id > 1*/    
    parentExpr = curExpr, curExpr = curExpr->pLeft;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    
    EXPECT_EQ(TK_GT, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id > 1", token_);

    parentExpr = curExpr, curExpr = curExpr->pLeft;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_ID, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id", token_);

    curExpr = parentExpr->pRight;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_INTEGER, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("1", token_);

    curExpr = curExpr->pParent->pParent;
    /* id < 100*/
    parentExpr = curExpr, curExpr = curExpr->pRight;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    
    EXPECT_EQ(TK_LT, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id < 100", token_);

    parentExpr = curExpr, curExpr = curExpr->pLeft;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_ID, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("id", token_);

    curExpr = parentExpr->pRight;
    EXPECT_TRUE(parentExpr == curExpr->pParent);
    EXPECT_EQ(TK_INTEGER, curExpr->op);
    dup2token_(curExpr->span.z, curExpr->span.n);
    EXPECT_STREQ("100", token_);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testSelectWhereBetweenError) {
    char *errMsg = NULL;
    int errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test_shard WHERE id BETWEEN id > 50 AND id < 250;", &errMsg);
    EXPECT_EQ(errNum, 1);
    EXPECT_TRUE(errMsg != NULL); 
    EXPECT_EQ(0, parseObj_->parsed.curSize);
}

TEST_F(LemonTest, testSelectWhereIN) {
    char *errMsg = NULL;
    int errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test WHERE id IN (1, 2, 3)", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    Select *selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(TK_IN, selectObj->pWhere->op);
    EXPECT_EQ(3, selectObj->pWhere->pList->nExpr);
    
    EXPECT_TRUE(strncmp("id", (const char*)selectObj->pWhere->pLeft->token.z, selectObj->pWhere->pLeft->token.n) == 0);
    dup2token_(selectObj->pWhere->pList->a[0].pExpr->token.z, selectObj->pWhere->pList->a[0].pExpr->token.n);
    EXPECT_STREQ("1", token_);
    dup2token_(selectObj->pWhere->pList->a[1].pExpr->token.z, selectObj->pWhere->pList->a[1].pExpr->token.n);
    EXPECT_STREQ("2", token_);
    dup2token_(selectObj->pWhere->pList->a[2].pExpr->token.z, selectObj->pWhere->pList->a[2].pExpr->token.n);
    EXPECT_STREQ("3", token_);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test WHERE id IN (SELECT id FROM test1 WHERE name = 'test')", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(TK_IN, selectObj->pWhere->op);
    EXPECT_TRUE(selectObj->pWhere->pList == NULL);
    EXPECT_TRUE(selectObj->pWhere->pSelect != NULL);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testSelectLike) {
    char *errMsg = NULL;
    int errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test WHERE name LIKE 'Hello%'", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    Select *selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(TK_LIKE_KW, selectObj->pWhere->op);
    dup2token_(selectObj->pWhere->span.z, selectObj->pWhere->span.n);
    EXPECT_STREQ("name LIKE 'Hello%'", token_);
    EXPECT_TRUE(selectObj->pWhere->pList != NULL);
    EXPECT_EQ(2, selectObj->pWhere->pList->nExpr);
    dup2token_(selectObj->pWhere->pList->a[0].pExpr->token.z, selectObj->pWhere->pList->a[0].pExpr->token.n);
    EXPECT_STREQ("name", token_);
    dup2token_(selectObj->pWhere->pList->a[1].pExpr->token.z, selectObj->pWhere->pList->a[1].pExpr->token.n);
    EXPECT_STREQ("'Hello%'", token_);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test WHERE name NOT LIKE '/Hello%' ESCAPE '/'", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    EXPECT_EQ(TK_NOT, selectObj->pWhere->op);
    dup2token_(selectObj->pWhere->span.z, selectObj->pWhere->span.n);
    EXPECT_STREQ("name NOT LIKE '/Hello%'", token_); // ESCAPE is not in the span

    Expr *likeOp = selectObj->pWhere->pLeft;
    EXPECT_EQ(TK_LIKE_KW, likeOp->op);
    dup2token_(likeOp->span.z, likeOp->span.n);
    EXPECT_TRUE(likeOp->pList != NULL);
    EXPECT_EQ(3, likeOp->pList->nExpr);
    dup2token_(likeOp->pList->a[0].pExpr->token.z, likeOp->pList->a[0].pExpr->token.n);
    EXPECT_STREQ("name", token_);
    dup2token_(likeOp->pList->a[1].pExpr->token.z, likeOp->pList->a[1].pExpr->token.n);
    EXPECT_STREQ("'/Hello%'", token_);

    dup2token_(likeOp->pList->a[2].pExpr->token.z, likeOp->pList->a[2].pExpr->token.n);
    EXPECT_STREQ("'/'", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testSelectFunction) {
    char *errMsg = NULL;
    int errNum = sqlite3RunParser(parseObj_, "SELECT COUNT(*) FROM test", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    Select *selectObj = parseObj_->parsed.array[0].result.selectObj;
    ASSERT_TRUE(selectObj != NULL);
    EXPECT_EQ(1, selectObj->pEList->nExpr);
    EXPECT_EQ(TK_FUNCTION, selectObj->pEList->a[0].pExpr->op);
    EXPECT_TRUE(selectObj->pEList->a[0].pExpr->pParent == NULL);
    Expr* funcExpr = selectObj->pEList->a[0].pExpr;
    dup2token_(funcExpr->token.z, funcExpr->token.n);
    EXPECT_STREQ("COUNT", token_);

    dup2token_(funcExpr->span.z, funcExpr->span.n);
    EXPECT_STREQ("COUNT(*)", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT COUNT(*), FAKEFUNC(id, 1) FROM test", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    EXPECT_EQ(2, selectObj->pEList->nExpr);
    EXPECT_EQ(TK_FUNCTION, selectObj->pEList->a[0].pExpr->op);
    EXPECT_TRUE(selectObj->pEList->a[0].pExpr->pParent == NULL);
    funcExpr = selectObj->pEList->a[0].pExpr;
    dup2token_(funcExpr->token.z, funcExpr->token.n);
    EXPECT_STREQ("COUNT", token_);

    dup2token_(funcExpr->span.z, funcExpr->span.n);
    EXPECT_STREQ("COUNT(*)", token_);

    EXPECT_EQ(TK_FUNCTION, selectObj->pEList->a[1].pExpr->op);
    EXPECT_TRUE(selectObj->pEList->a[1].pExpr->pParent == NULL);
    funcExpr = selectObj->pEList->a[1].pExpr;
    dup2token_(funcExpr->token.z, funcExpr->token.n);
    EXPECT_STREQ("FAKEFUNC", token_);

    dup2token_(funcExpr->span.z, funcExpr->span.n);
    EXPECT_STREQ("FAKEFUNC(id, 1)", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testSelectJoin) {
    char *errMsg = NULL;
    /* JOIN ... ON*/
    int errNum = sqlite3RunParser(parseObj_, "SELECT test.id, test1.name FROM test JOIN test1 ON (test.id = test1.id)", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    Select *selectObj = parseObj_->parsed.array[0].result.selectObj;
    
    EXPECT_EQ(2, selectObj->pSrc->nSrc);
    EXPECT_STREQ("test", selectObj->pSrc->a[0].zName);
    EXPECT_TRUE(JT_INNER & selectObj->pSrc->a[0].jointype);
    EXPECT_TRUE(selectObj->pSrc->a[0].pOn != NULL);
    Expr *onExpr = selectObj->pSrc->a[0].pOn;
    EXPECT_EQ(TK_EQ, onExpr->op);
    dup2token_(onExpr->span.z, onExpr->span.n);
    EXPECT_STREQ("(test.id = test1.id)", token_);
    EXPECT_TRUE(onExpr->pLeft->pParent == onExpr && onExpr->pRight->pParent == onExpr);
    EXPECT_EQ(TK_DOT, onExpr->pLeft->op);
    dup2token_(onExpr->pLeft->pLeft->token.z, onExpr->pLeft->pLeft->token.n);
    EXPECT_STREQ("test", token_);

    dup2token_(onExpr->pLeft->pRight->token.z, onExpr->pLeft->pRight->token.n);
    EXPECT_STREQ("id", token_);

    dup2token_(onExpr->pRight->pLeft->token.z, onExpr->pRight->pLeft->token.n);
    EXPECT_STREQ("test1", token_);

    dup2token_(onExpr->pRight->pRight->token.z, onExpr->pRight->pRight->token.n);
    EXPECT_STREQ("id", token_);

    EXPECT_STREQ("test1", selectObj->pSrc->a[1].zName);
    EXPECT_EQ(0, selectObj->pSrc->a[1].jointype); // do not have join

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    /* JOIN ... USING*/
    errNum = sqlite3RunParser(parseObj_, "SELECT test.id, test1.name FROM test JOIN test1 USING (id)", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    selectObj = parseObj_->parsed.array[0].result.selectObj;

    EXPECT_EQ(2, selectObj->pSrc->nSrc);
    EXPECT_STREQ("test", selectObj->pSrc->a[0].zName);
    EXPECT_EQ(JT_INNER, selectObj->pSrc->a[0].jointype);
    EXPECT_TRUE(selectObj->pSrc->a[0].pOn == NULL);
    EXPECT_TRUE(selectObj->pSrc->a[0].pUsing != NULL);
    IdList* usingList = selectObj->pSrc->a[0].pUsing;
    EXPECT_EQ(1, usingList->nId);
    EXPECT_STREQ("id", usingList->a[0].zName);

    EXPECT_STREQ("test1", selectObj->pSrc->a[1].zName);
    EXPECT_EQ(0, selectObj->pSrc->a[1].jointype); // do not have join
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    /* LEFT JOIN, details see sqlite3JoinType func*/
    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT test.id, test1.name FROM test LEFT JOIN test1 ON (test.id = test1.id)", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    
    EXPECT_EQ(2, selectObj->pSrc->nSrc);
    EXPECT_TRUE(JT_LEFT & selectObj->pSrc->a[0].jointype);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    /* RIGHT JOIN*/
    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT test.id, test1.name FROM test RIGHT JOIN test1 ON (test.id = test1.id)", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    
    EXPECT_EQ(2, selectObj->pSrc->nSrc);
    EXPECT_TRUE(JT_RIGHT & selectObj->pSrc->a[0].jointype);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    /* FULL JOIN*/
    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT test.id, test1.name FROM test FULL JOIN test1 ON (test.id = test1.id)", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    
    EXPECT_EQ(2, selectObj->pSrc->nSrc);
    EXPECT_TRUE(JT_FULL & selectObj->pSrc->a[0].jointype);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    /* LEFT OUTER JOIN*/
    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT test.id, test1.name FROM test LEFT OUTER JOIN test1 ON (test.id = test1.id)", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    
    EXPECT_EQ(2, selectObj->pSrc->nSrc);
    EXPECT_TRUE(((JT_OUTER | JT_LEFT) & selectObj->pSrc->a[0].jointype) == (JT_OUTER | JT_LEFT));
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    /* RIGHT OUTER JOIN*/
    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT test.id, test1.name FROM test RIGHT OUTER JOIN test1 ON (test.id = test1.id)", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    selectObj = parseObj_->parsed.array[0].result.selectObj;

    EXPECT_EQ(2, selectObj->pSrc->nSrc);
    EXPECT_TRUE(((JT_OUTER | JT_RIGHT) & selectObj->pSrc->a[0].jointype) == (JT_OUTER | JT_RIGHT));
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    /* FULL OUTER JOIN*/
    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT test.id, test1.name FROM test FULL OUTER JOIN test1 ON (test.id = test1.id)", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    selectObj = parseObj_->parsed.array[0].result.selectObj;
    
    EXPECT_EQ(2, selectObj->pSrc->nSrc);
    EXPECT_TRUE(((JT_OUTER | JT_FULL) & selectObj->pSrc->a[0].jointype) == (JT_OUTER | JT_FULL));
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testSelectSubquery) {
     char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test WHERE id = (SELECT id FROM test1 WHERE name = 'hello world')", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    Select *selectObj = parseObj_->parsed.array[0].result.selectObj;
    EXPECT_EQ(TK_SELECT, selectObj->op);
    
    EXPECT_TRUE(selectObj->pWhere->pRight->pSelect != NULL);
    EXPECT_STREQ("test1", selectObj->pWhere->pRight->pSelect->pSrc->a[0].zName);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testSelectUnion) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test UNION SELECT * FROM test1 UNION SELECT * FROM test2", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    Select* selectObj = parseObj_->parsed.array[0].result.selectObj;
    EXPECT_EQ(TK_UNION, selectObj->op);
    
    EXPECT_TRUE(selectObj->pRightmost == selectObj);
    ASSERT_TRUE(selectObj->pPrior != NULL);
    EXPECT_TRUE(selectObj->pPrior->pRightmost == selectObj);
    ASSERT_TRUE(selectObj->pPrior->pPrior != NULL);
    EXPECT_TRUE(selectObj->pPrior->pPrior->pRightmost == selectObj);
    EXPECT_STREQ("test2", selectObj->pSrc->a[0].zName);
    EXPECT_STREQ("test1", selectObj->pPrior->pSrc->a[0].zName);
    EXPECT_STREQ("test", selectObj->pPrior->pPrior->pSrc->a[0].zName);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testSelectGroupBy) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "SELECT name, AVG(price) FROM sales GROUP BY name", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
    
    Select* selectObj = parseObj_->parsed.array[0].result.selectObj;
    EXPECT_EQ(TK_SELECT, selectObj->op);
    EXPECT_EQ(1, selectObj->pGroupBy->nExpr);
    dup2token_(selectObj->pGroupBy->a[0].pExpr->token.z, selectObj->pGroupBy->a[0].pExpr->token.n);
    EXPECT_STREQ("name", token_);
    
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testSelectSQL_CALC_FOUND_ROWS) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "SELECT SQL_CALC_FOUND_ROWS * FROM test;", &errMsg);
    ASSERT_TRUE(errMsg != NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_GT(errNum, 0);
    
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
    
}

/* TEST_F(LemonTest, testSelectTableDotKey) { */
/*     Parse *parseObj = sqlite3ParseNew(); */
/*     char *errMsg = 0; */
/*     int errNum = sqlite3RunParser(parseObj, "SELECT * FROM test WHERE test.id = 1", &errMsg); */    
/*     ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc; */
/*     ASSERT_EQ(errNum, 0); */
/*     EXPECT_EQ(parseObj->parsed.array[0].sqltype, SQLTYPE_SELECT); */
    
/*     Select *selectObj = parseObj->parsed.array[0].result.selectObj; */
/*     ASSERT_TRUE(selectObj != NULL); */
/*     EXPECT_EQ(TK_SELECT, selectObj->op); */
    
/*     Expr *left_expr = selectObj->pWhere->pLeft; */


/*     sqlite3ParseDelete(parseObj); */
/* } */

TEST_F(LemonTest, testInsertValues) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "INSERT INTO testdb.test(id, name) VALUES(1, 'test')", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_INSERT, parseObj_->parsed.array[0].sqltype);

    Insert* insertObj = parseObj_->parsed.array[0].result.insertObj;
    EXPECT_EQ(1, insertObj->pTabList->nSrc);
    EXPECT_STREQ("test", insertObj->pTabList->a[0].zName);
    EXPECT_STREQ("testdb", insertObj->pTabList->a[0].zDatabase);
    
    EXPECT_EQ(2, insertObj->pColumn->nId);
    EXPECT_STREQ("id", insertObj->pColumn->a[0].zName);
    EXPECT_STREQ("name", insertObj->pColumn->a[1].zName);
    
    ValuesList *valuesList = insertObj->pValuesList;
    EXPECT_EQ(1, valuesList->nValues);
    ExprList *exprList = valuesList->a[0];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("1", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "INSERT INTO testdb.test(id, name) VALUES(1, 'test'), (2, 'test')", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_INSERT, parseObj_->parsed.array[0].sqltype);

    insertObj = parseObj_->parsed.array[0].result.insertObj;
    valuesList = insertObj->pValuesList;
    EXPECT_TRUE(valuesList != NULL);
    EXPECT_EQ(2, valuesList->nValues);
       
    exprList = valuesList->a[0];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("1", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    
    exprList = valuesList->a[1];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("2", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "INSERT INTO testdb.test(id, name) VALUES(1, 'test'), (2, 'test'), (3, 'test')", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_INSERT, parseObj_->parsed.array[0].sqltype);

    insertObj = parseObj_->parsed.array[0].result.insertObj;
    valuesList = insertObj->pValuesList;
    EXPECT_TRUE(valuesList != NULL);
    EXPECT_EQ(3, valuesList->nValues);
       
    exprList = valuesList->a[0];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("1", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    
    exprList = valuesList->a[1];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("2", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);

    exprList = valuesList->a[2];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("3", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "INSERT INTO test VALUES(1, 'test')", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_INSERT, parseObj_->parsed.array[0].sqltype);

    insertObj = parseObj_->parsed.array[0].result.insertObj;
    EXPECT_TRUE(insertObj->pColumn == NULL);

    valuesList = insertObj->pValuesList;
    EXPECT_TRUE(valuesList != NULL);
    EXPECT_EQ(1, valuesList->nValues);
       
    exprList = valuesList->a[0];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("1", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testInsertFromSelect) {
    char *errMsg = NULL;
    int errNum = sqlite3RunParser(parseObj_, "INSERT INTO testdb.test(id, name) SELECT id, name FROM test1", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_INSERT, parseObj_->parsed.array[0].sqltype);

    Insert *insertObj = parseObj_->parsed.array[0].result.insertObj;
    EXPECT_TRUE(insertObj->pSelect != NULL);
    EXPECT_STREQ("test1", insertObj->pSelect->pSrc->a[0].zName);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testInsertSetList) {
    char *errMsg = NULL;
    int errNum = sqlite3RunParser(parseObj_, "INSERT INTO testdb.test(id, name) SET id = 1, name = 'test'", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_INSERT, parseObj_->parsed.array[0].sqltype);

    Insert *insertObj = parseObj_->parsed.array[0].result.insertObj;
    EXPECT_STREQ("test", insertObj->pTabList->a[0].zName);
    EXPECT_TRUE(insertObj->pSetList != NULL);
    EXPECT_EQ(2, insertObj->pSetList->nExpr);
    EXPECT_STREQ("id", insertObj->pSetList->a[0].zName);
    EXPECT_STREQ("name", insertObj->pSetList->a[1].zName);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    /* from tcpcopy*/
    errNum = sqlite3RunParser(parseObj_, "insert yp_xiangce.xiangce_82 set xid = '37433782' ,cqid = '1453989997' ,name = 'QQ_Images' ,remark = '' ,ctime = '1429259429' , `type` = '2' ,`join` = '0' ,longitude = '0' ,latitude = '0' ,recover = '0' ,photocount = '0' ,readonly = '0' ,nearby = '0'", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testTcpCopy) {
    char *errMsg = NULL;
    int errNum = sqlite3RunParser(parseObj_, "INSERT INTO `yp_xiangce`.`xiangce_idgen` () VALUES ()", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testReplaceValues) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "REPLACE INTO testdb.test(id, name) VALUES(1, 'test')", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_REPLACE, parseObj_->parsed.array[0].sqltype);

    Insert* insertObj = parseObj_->parsed.array[0].result.insertObj;
    EXPECT_EQ(1, insertObj->pTabList->nSrc);
    EXPECT_STREQ("test", insertObj->pTabList->a[0].zName);
    EXPECT_STREQ("testdb", insertObj->pTabList->a[0].zDatabase);
    
    EXPECT_EQ(2, insertObj->pColumn->nId);
    EXPECT_STREQ("id", insertObj->pColumn->a[0].zName);
    EXPECT_STREQ("name", insertObj->pColumn->a[1].zName);
    
    ValuesList *valuesList = insertObj->pValuesList;
    EXPECT_EQ(1, valuesList->nValues);
    ExprList *exprList = valuesList->a[0];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("1", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "REPLACE INTO testdb.test(id, name) VALUES(1, 'test'), (2, 'test')", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_REPLACE, parseObj_->parsed.array[0].sqltype);

    insertObj = parseObj_->parsed.array[0].result.insertObj;
    valuesList = insertObj->pValuesList;
    EXPECT_TRUE(valuesList != NULL);
    EXPECT_EQ(2, valuesList->nValues);
       
    exprList = valuesList->a[0];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("1", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    
    exprList = valuesList->a[1];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("2", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "REPLACE INTO testdb.test(id, name) VALUES(1, 'test'), (2, 'test'), (3, 'test')", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_REPLACE, parseObj_->parsed.array[0].sqltype);

    insertObj = parseObj_->parsed.array[0].result.insertObj;
    valuesList = insertObj->pValuesList;
    EXPECT_TRUE(valuesList != NULL);
    EXPECT_EQ(3, valuesList->nValues);
       
    exprList = valuesList->a[0];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("1", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    
    exprList = valuesList->a[1];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("2", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);

    exprList = valuesList->a[2];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("3", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "REPLACE INTO test VALUES(1, 'test')", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_REPLACE, parseObj_->parsed.array[0].sqltype);

    insertObj = parseObj_->parsed.array[0].result.insertObj;
    EXPECT_TRUE(insertObj->pColumn == NULL);

    valuesList = insertObj->pValuesList;
    EXPECT_TRUE(valuesList != NULL);
    EXPECT_EQ(1, valuesList->nValues);
       
    exprList = valuesList->a[0];
    EXPECT_EQ(2, exprList->nExpr);
    EXPECT_EQ(TK_INTEGER, exprList->a[0].pExpr->op);
    EXPECT_EQ(TK_STRING, exprList->a[1].pExpr->op);
    dup2token_(exprList->a[0].pExpr->token.z, exprList->a[0].pExpr->token.n);
    EXPECT_STREQ("1", token_);

    dup2token_(exprList->a[1].pExpr->token.z, exprList->a[1].pExpr->token.n);
    EXPECT_STREQ("'test'", token_);
    
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testDelete) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "DELETE FROM test", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_DELETE);
    
    Delete *deleteObj = parseObj_->parsed.array[0].result.deleteObj;
    EXPECT_TRUE(deleteObj->pWhere == NULL);
    EXPECT_EQ(1, deleteObj->pTabList->nSrc);
    EXPECT_STREQ("test", deleteObj->pTabList->a[0].zName);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    errNum = sqlite3RunParser(parseObj_, "DELETE FROM test WHERE id = 1", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_DELETE);
    
    deleteObj = parseObj_->parsed.array[0].result.deleteObj;
    EXPECT_TRUE(deleteObj->pWhere != NULL);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "DELETE FROM test WHERE id IN (SELECT id FROM test WHERE type = 'test' LIMIT 0, 2)", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_DELETE);
    
    deleteObj = parseObj_->parsed.array[0].result.deleteObj;
    EXPECT_TRUE(deleteObj->pWhere != NULL);
    EXPECT_EQ(TK_IN, deleteObj->pWhere->op);
    EXPECT_TRUE(deleteObj->pWhere->pSelect != NULL);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testUpdate) {
    char *errMsg = NULL;
    int errNum = sqlite3RunParser(parseObj_, "UPDATE test SET name = 'world', age = 25 WHERE name = 'hello'", &errMsg);
    EXPECT_EQ(errNum, 0);
    EXPECT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_UPDATE);
    
    Update *updateObj = parseObj_->parsed.array[0].result.updateObj;
    EXPECT_STREQ("test", updateObj->pTabList->a[0].zName);
    EXPECT_STREQ("name", updateObj->pChanges->a[0].zName);
    EXPECT_STREQ("age", updateObj->pChanges->a[1].zName);
    
    dup2token_(updateObj->pChanges->a[0].pExpr->token.z, updateObj->pChanges->a[0].pExpr->token.n);
    EXPECT_STREQ("'world'", token_);
    
    dup2token_(updateObj->pChanges->a[1].pExpr->token.z, updateObj->pChanges->a[1].pExpr->token.n);
    EXPECT_STREQ("25", token_);

    dup2token_(updateObj->pWhere->pLeft->token.z, updateObj->pWhere->pLeft->token.n);
    EXPECT_STREQ("name", token_);

    dup2token_(updateObj->pWhere->pRight->token.z, updateObj->pWhere->pRight->token.n);
    EXPECT_STREQ("'hello'", token_);
    
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "UPDATE test SET name = 'world' WHERE name IN ('hello', 'test')", &errMsg);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_UPDATE);
    
    updateObj = parseObj_->parsed.array[0].result.updateObj;
    EXPECT_STREQ("test", updateObj->pTabList->a[0].zName);
    EXPECT_STREQ("name", updateObj->pChanges->a[0].zName);
    
    dup2token_(updateObj->pChanges->a[0].pExpr->token.z, updateObj->pChanges->a[0].pExpr->token.n);
    EXPECT_STREQ("'world'", token_);

    EXPECT_EQ(TK_IN, updateObj->pWhere->op);
    dup2token_(updateObj->pWhere->pLeft->token.z, updateObj->pWhere->pLeft->token.n);
    EXPECT_STREQ("name", token_);
    
    EXPECT_EQ(2, updateObj->pWhere->pList->nExpr);
    dup2token_(updateObj->pWhere->pList->a[0].pExpr->token.z, updateObj->pWhere->pList->a[0].pExpr->token.n);   
    EXPECT_STREQ("'hello'", token_);
    dup2token_(updateObj->pWhere->pList->a[1].pExpr->token.z, updateObj->pWhere->pList->a[1].pExpr->token.n);   
    EXPECT_STREQ("'test'", token_);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testUpdateLimit) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "UPDATE test SET age = 1 WHERE id > 100 LIMIT 10;", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_UPDATE);
       
    Update *updateObj = parseObj_->parsed.array[0].result.updateObj;

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testDeleteLimit) {
    char *errMsg = 0;
    
    sqlite3ParseReset(parseObj_);
    int errNum = sqlite3RunParser(parseObj_, "DELETE FROM test WHERE id > 100 LIMIT 10;", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_DELETE);
       
    Delete *deleteObj = parseObj_->parsed.array[0].result.deleteObj;

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testExpain) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "EXPLAIN SELECT * FROM test", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_SELECT);
       
    Select* selectObj = parseObj_->parsed.array[0].result.selectObj;
    EXPECT_EQ(TK_SELECT, selectObj->op);
    EXPECT_EQ(TK_ALL, selectObj->pEList->a[0].pExpr->op);
    EXPECT_STREQ("test", selectObj->pSrc->a[0].zName);
    EXPECT_EQ(1, parseObj_->explain);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "EXPLAIN QUERY PLAN SELECT * FROM test", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
       
    EXPECT_EQ(2, parseObj_->explain);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SELECT * FROM test", &errMsg);
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
       
    EXPECT_EQ(0, parseObj_->explain);

    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testTransaction) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "BEGIN;", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_TRANSACTION_BEGIN);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "START TRANSACTION;", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_TRANSACTION_START);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "BEGIN WORK;", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_TRANSACTION_BEGIN);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "COMMIT;", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_TRANSACTION_COMMIT);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "ROLLBACK;", &errMsg);
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(parseObj_->parsed.array[0].sqltype, SQLTYPE_TRANSACTION_ROLLBACK);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
}

TEST_F(LemonTest, testCreateTable) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, 
        "CREATE TABLE `sharding_test` (                         \
            `id` int(11) NOT NULL AUTO_INCREMENT,               \
            `name` char(50) COLLATE utf8_bin NOT NULL,          \
            `age` int(11) DEFAULT 1 CHECK(1),                         \
            `birthday` date DEFAULT NULL,                       \
            `nickname` char(50) COLLATE utf8_bin DEFAULT NULL,  \
            PRIMARY KEY (`id` AUTO_INCREMENT),                  \
            FOREIGN KEY(`name`) REFERENCES artist(artistid),    \
            UNIQUE (`id`)                                       \
        )DEFAULT CHARSET SET=utf8 ENGINE=InnoDB ;", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_CREATE_TABLE, parseObj_->parsed.array[0].sqltype);
}

TEST_F(LemonTest, testDropTable) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "DROP TABLE IF EXISTS sharding_test;", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_DROP_TABLE, parseObj_->parsed.array[0].sqltype);
}

TEST_F(LemonTest, testSetStatement) {
    char *errMsg = 0;
    
    int errNum = sqlite3RunParser(parseObj_, "SET NAMES utf8", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_SET_NAMES, parseObj_->parsed.array[0].sqltype);
    SetStatement *setObj = parseObj_->parsed.array[0].result.setObj;
    
    dupToken2token_(setObj->value);
    EXPECT_STREQ("utf8", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SET CHARACTER SET utf8", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_SET_CHARACTER_SET, parseObj_->parsed.array[0].sqltype);
    setObj = parseObj_->parsed.array[0].result.setObj;
    
    dupToken2token_(setObj->value);
    EXPECT_STREQ("utf8", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SET character_set_client = utf8", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_SET, parseObj_->parsed.array[0].sqltype);
    setObj = parseObj_->parsed.array[0].result.setObj;
        
    EXPECT_EQ(1, setObj->pSetList->nExpr);
    EXPECT_STREQ("character_set_client", setObj->pSetList->a[0].zName);

    dupToken2token_(setObj->pSetList->a[0].pExpr->token);
    EXPECT_STREQ("utf8", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SET @@global.character_set_client = utf8", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_SET, parseObj_->parsed.array[0].sqltype);
    setObj = parseObj_->parsed.array[0].result.setObj;
        
    EXPECT_EQ(1, setObj->pSetList->nExpr);
    EXPECT_STREQ("character_set_client", setObj->pSetList->a[0].zName);

    dupToken2token_(setObj->pSetList->a[0].pExpr->token);
    EXPECT_STREQ("utf8", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);

    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SET @@local.character_set_client = utf8", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_SET, parseObj_->parsed.array[0].sqltype);
    setObj = parseObj_->parsed.array[0].result.setObj;
        
    EXPECT_EQ(1, setObj->pSetList->nExpr);
    EXPECT_STREQ("character_set_client", setObj->pSetList->a[0].zName);

    dupToken2token_(setObj->pSetList->a[0].pExpr->token);
    EXPECT_STREQ("utf8", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
    
    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SET @@session.character_set_client = utf8", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_SET, parseObj_->parsed.array[0].sqltype);
    setObj = parseObj_->parsed.array[0].result.setObj;
        
    EXPECT_EQ(1, setObj->pSetList->nExpr);
    EXPECT_STREQ("character_set_client", setObj->pSetList->a[0].zName);

    dupToken2token_(setObj->pSetList->a[0].pExpr->token);
    EXPECT_STREQ("utf8", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
    
    resetParseObject(parseObj_);
    errNum = sqlite3RunParser(parseObj_, "SET @@error.character_set_client = utf8", &errMsg);

    ASSERT_TRUE(errMsg != NULL) ;
    ASSERT_EQ(errNum, 1);
    EXPECT_EQ(0, parseObj_->parsed.curSize);
    
    resetParseObject(parseObj_);

    // ----------------------------------------- NOTICE !!!!! ----------------------------------------------------
    // |                                                                                                         |
    // |                                                                                                         |
    // |                                 when errMsg != NULL, need to free it.                                   |
    // |                                                                                                         |
    // |                                                                                                         |
    // -----------------------------------------------------------------------------------------------------------
    sqliteFree(errMsg);
    errMsg = NULL;

    errNum = sqlite3RunParser(parseObj_, "SET @@session.character_set_client = utf8, autocommit = 0, @@session.character_set_connection = utf8", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SQLTYPE_SET, parseObj_->parsed.array[0].sqltype);
    setObj = parseObj_->parsed.array[0].result.setObj;
        
    EXPECT_EQ(3, setObj->pSetList->nExpr);
    EXPECT_STREQ("character_set_client", setObj->pSetList->a[0].zName);

    dupToken2token_(setObj->pSetList->a[0].pExpr->token);
    EXPECT_STREQ("utf8", token_);

    EXPECT_STREQ("autocommit", setObj->pSetList->a[1].zName);

    dupToken2token_(setObj->pSetList->a[1].pExpr->token);
    EXPECT_STREQ("0", token_);

    EXPECT_STREQ("character_set_connection", setObj->pSetList->a[2].zName);

    dupToken2token_(setObj->pSetList->a[2].pExpr->token);
    EXPECT_STREQ("utf8", token_);
    sqlite3ParsedResultArrayClean(&parseObj_->parsed);
} 


TEST_F(LemonTest,  testTokenArray) {
    Parse *parseObj = sqlite3ParseNew();
    char *errMsg = 0;
    int errNum = sqlite3RunParser1(parseObj, "SELECT * FROM test;", strlen("SELECT * FROM test;"), &errMsg);    
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    ASSERT_TRUE(parseObj->tokens.curSize > 0);
    EXPECT_EQ(TK_SELECT, parseObj->tokens.array[0].tokenType);
    EXPECT_EQ(TK_STAR, parseObj->tokens.array[1].tokenType);
    EXPECT_EQ(TK_FROM, parseObj->tokens.array[2].tokenType);
    EXPECT_EQ(TK_ID, parseObj->tokens.array[3].tokenType);
    
    //sqlite3SelectDelete(parseObj->parsed.array[0].result.selectObj);
    sqlite3ParsedResultArrayClean(&parseObj->parsed);

    sqlite3ParseReset(parseObj);
    errNum = sqlite3RunParser1(parseObj, "SELECT * FROM test; error", strlen("SELECT * FROM test; error"), &errMsg);    
    ASSERT_TRUE(errMsg != NULL);
    sqliteFree(errMsg);
    ASSERT_TRUE(parseObj->tokens.curSize == 6);
    EXPECT_EQ(TK_SELECT, parseObj->tokens.array[0].tokenType);
    EXPECT_EQ(TK_STAR, parseObj->tokens.array[1].tokenType);
    EXPECT_EQ(TK_FROM, parseObj->tokens.array[2].tokenType);
    EXPECT_EQ(TK_ID, parseObj->tokens.array[3].tokenType);
    EXPECT_EQ(TK_SEMI, parseObj->tokens.array[4].tokenType);
    EXPECT_EQ(TK_ID, parseObj->tokens.array[5].tokenType);

    EXPECT_EQ(1, parseObj->parsed.curSize);
    sqlite3ParsedResultArrayClean(&parseObj->parsed);
    sqlite3ParseDelete(parseObj);
}

TEST_F(LemonTest, testMultiSql) {
    Parse *parseObj = sqlite3ParseNew();
    char *errMsg = 0;
    int errNum = sqlite3RunParser1(parseObj, "SELECT * FROM test; INSERT INTO test(id, name) VALUES(1, 'test');", strlen("SELECT * FROM test; INSERT INTO test(id, name) VALUES(1, 'test');"), &errMsg);    
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    
    EXPECT_EQ(2, parseObj->parsed.curSize);
    EXPECT_TRUE(parseObj->parsed.array[0].sqltype == SQLTYPE_SELECT && parseObj->parsed.array[0].result.selectObj != NULL);
    EXPECT_TRUE(parseObj->parsed.array[1].sqltype == SQLTYPE_INSERT && parseObj->parsed.array[1].result.insertObj != NULL);
    sqlite3ParsedResultArrayClean(&parseObj->parsed);
    sqlite3ParseDelete(parseObj);
}

TEST_F(LemonTest, testShowStatement) {
    Parse *parseObj = sqlite3ParseNew();
    char *errMsg = 0;
    int errNum = sqlite3RunParser(parseObj, "SHOW TABLE STATUS LIKE 'sbtest';", &errMsg);    
    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SHOWTYPE_SHOW_TABLE_STATUS, parseObj->parsed.array[0].result.showType);
    
    resetParseObject(parseObj);
    errNum = sqlite3RunParser(parseObj, "SHOW VARIABLES", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SHOWTYPE_SHOW_VARIABLES, parseObj->parsed.array[0].result.showType);

    resetParseObject(parseObj);
    errNum = sqlite3RunParser(parseObj, "SHOW GLOBAL VARIABLES", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SHOWTYPE_SHOW_VARIABLES, parseObj->parsed.array[0].result.showType);

    resetParseObject(parseObj);
    errNum = sqlite3RunParser(parseObj, "SHOW SESSION VARIABLES LIKE 'back_log'", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SHOWTYPE_SHOW_VARIABLES, parseObj->parsed.array[0].result.showType);
    
    resetParseObject(parseObj);
    errNum = sqlite3RunParser(parseObj, "SHOW SESSION VARIABLES WHERE id = 1", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SHOWTYPE_SHOW_VARIABLES, parseObj->parsed.array[0].result.showType);

    resetParseObject(parseObj);
    errNum = sqlite3RunParser(parseObj, "SHOW COLLATION", &errMsg);

    ASSERT_TRUE(errMsg == NULL) << "error: " << errMsg << ", error_code: " << parseObj_->rc;
    ASSERT_EQ(errNum, 0);
    EXPECT_EQ(SHOWTYPE_SHOW_COLLATION, parseObj->parsed.array[0].result.showType);
    sqlite3ParseDelete(parseObj);
}


int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
