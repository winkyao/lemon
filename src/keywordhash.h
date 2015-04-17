/* Hash score: 174 */
static int keywordCode(const char *z, int n){
  static const char zText[575] =
    "ABORTABLESCAPEACHARACTERAISELECTEMPORARYAFTEREFERENCESCHEMASESSION"
    "AMESHOWHENDATABASESTARTHENATURALEFTRANSACTIONOTNULLIKEYANALYZE"
    "LSEXCEPTRIGGEREGEXPLAINITIALLYANDEFAULTATTACHARSETAUTO_INCREMENT"
    "BEFOREIGNOREINDEXCLUSIVEXISTSTATEMENTBEGINNERENAMEBETWEENBYCASCADE"
    "FERRABLECASECASTCHECKCOLLATECOMMITCONFLICTCONSTRAINTERSECTCREATE"
    "CROSSCURRENT_DATECURRENT_TIMESTAMPLANDEFERREDELETEDESCDETACHAVING"
    "LOBALIMITDISTINCTDROPRAGMATCHFAILOCALFROMFULLGROUPDATEIFIMMEDIATE"
    "INSERTINSTEADINTOFFSETISNULLJOINORDEREPLACEOUTERESTRICTPRIMARY"
    "QUERYRIGHTROLLBACKROWHEREUNIONUNIQUEUSINGVACUUMVALUESVIEWORK";
  static const unsigned char aHash[127] = {
     100,  88, 114,  99,   0,   9,   0,   0, 121,   0,  91,   0,   0,
     103,  52,  78, 101,   0, 113,  18,  83,  98,  23,   8,   0,   0,
     123,   0, 117, 110,   0,  38,   0,   0,  49,   0,   0,  68,  73,
       0,  65,   5,   0, 112,  42, 111,  17, 115,  76,   0,   0,  54,
       0,  79,  64,   0,  20,   0, 122,  44,  19,   0,  81,  84,  35,
      21,   0,   0,  41,  89,  60,  40,  57,  67,  96,   0,  55,   0,
      77,  36,   0,  74,   0,   0,   6,  66,  51,  69,  45,  95,  39,
      71,  94,   0,   1,  85,  22, 108,  61,   7,   0, 119,  90, 106,
      29,  26,  86,   0,   0,  48, 102,   0, 109,   0,  93,   0,   0,
      28,   0, 116,  58,  31,   0,   2,  30,   0, 118,
  };
  static const unsigned char aNext[123] = {
       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,  14,   0,   0,   0,   0,   0,   0,   0,  11,
       0,   0,   0,  25,   0,  13,   0,   0,   0,   0,  15,  24,   0,
       0,   0,   0,   0,   0,  12,   0,   0,   0,   0,   0,   0,   0,
       0,  10,  43,   0,   0,   0,   0,   0,  59,   0,   0,   0,  53,
       0,   0,  62,  47,   0,   0,   0,   0,   0,   0,  75,  50,   0,
       0,   0,   4,  63,  46,   0,   0,   0,  33,   0,  87,   0,   0,
      70,  72,   0,  92,   0,   0,   0,   0,   0,   3,   0,   0,   0,
     104, 105,   0,   0, 107,   0,  34,   0,  27,  37,  82,   0,  32,
      97,  16,  56,   0,  80, 120,
  };
  static const unsigned char aLen[123] = {
       5,   5,   6,   6,   4,   9,   5,   6,   4,   9,   2,   5,  10,
       7,   7,   5,   4,   4,   3,   8,   9,   2,   5,   4,   7,   4,
      11,   2,   3,   7,   4,   4,   3,   7,   4,   6,   7,   6,   7,
       9,   3,   3,   7,   6,   7,   3,  14,   2,   6,   3,   7,   6,
       7,   9,   6,   9,   5,   5,   6,   7,   2,   7,   3,  10,   4,
       4,   5,   7,   6,   8,  10,   9,   6,   5,  12,  12,  17,   4,
       8,   6,   4,   6,   6,   4,   6,   5,   8,   2,   4,   6,   5,
       4,   5,   4,   4,   5,   6,   2,   9,   6,   7,   4,   2,   6,
       6,   4,   5,   7,   5,   8,   7,   5,   5,   8,   3,   5,   5,
       6,   5,   6,   6,   4,   4,
  };
  static const unsigned short int aOffset[123] = {
       0,   4,   4,   8,  13,  15,  23,  26,  31,  31,  35,  40,  44,
      53,  59,  65,  69,  72,  74,  76,  76,  81,  84,  88,  91,  97,
     100, 109, 110, 110, 113, 116, 118, 121, 127, 130, 135, 141, 144,
     149, 154, 158, 160, 167, 171, 175, 178, 183, 192, 194, 194, 198,
     202, 207, 215, 220, 229, 232, 236, 242, 249, 251, 252, 256, 266,
     270, 274, 279, 286, 292, 300, 307, 316, 322, 327, 339, 339, 355,
     359, 366, 372, 376, 381, 386, 386, 391, 396, 397, 404, 407, 411,
     416, 419, 424, 428, 432, 435, 441, 443, 452, 458, 465, 468, 468,
     474, 480, 484, 488, 495, 499, 507, 514, 519, 524, 532, 534, 539,
     544, 550, 555, 561, 567, 570,
  };
  static const unsigned char aCode[123] = {
    TK_ABORT,      TK_TABLE,      TK_TABLES,     TK_ESCAPE,     TK_EACH,       
    TK_CHARACTER,  TK_RAISE,      TK_SELECT,     TK_TEMP,       TK_TEMP,       
    TK_OR,         TK_AFTER,      TK_REFERENCES, TK_SCHEMAS,    TK_SESSION,    
    TK_NAMES,      TK_SHOW,       TK_WHEN,       TK_END,        TK_DATABASE,   
    TK_DATABASES,  TK_AS,         TK_START,      TK_THEN,       TK_JOIN_KW,    
    TK_JOIN_KW,    TK_TRANSACTION,TK_ON,         TK_NOT,        TK_NOTNULL,    
    TK_NULL,       TK_LIKE_KW,    TK_KEY,        TK_ANALYZE,    TK_ELSE,       
    TK_EXCEPT,     TK_TRIGGER,    TK_LIKE_KW,    TK_EXPLAIN,    TK_INITIALLY,  
    TK_ALL,        TK_AND,        TK_DEFAULT,    TK_ATTACH,     TK_CHARSET,    
    TK_SET,        TK_AUTOINCR,   TK_IN,         TK_BEFORE,     TK_FOR,        
    TK_FOREIGN,    TK_IGNORE,     TK_REINDEX,    TK_EXCLUSIVE,  TK_EXISTS,     
    TK_STATEMENT,  TK_BEGIN,      TK_JOIN_KW,    TK_RENAME,     TK_BETWEEN,    
    TK_BY,         TK_CASCADE,    TK_ASC,        TK_DEFERRABLE, TK_CASE,       
    TK_CAST,       TK_CHECK,      TK_COLLATE,    TK_COMMIT,     TK_CONFLICT,   
    TK_CONSTRAINT, TK_INTERSECT,  TK_CREATE,     TK_JOIN_KW,    TK_CTIME_KW,   
    TK_CTIME_KW,   TK_CTIME_KW,   TK_PLAN,       TK_DEFERRED,   TK_DELETE,     
    TK_DESC,       TK_DETACH,     TK_HAVING,     TK_LIKE_KW,    TK_GLOBAL,     
    TK_LIMIT,      TK_DISTINCT,   TK_IS,         TK_DROP,       TK_PRAGMA,     
    TK_MATCH,      TK_FAIL,       TK_LOCAL,      TK_FROM,       TK_JOIN_KW,    
    TK_GROUP,      TK_UPDATE,     TK_IF,         TK_IMMEDIATE,  TK_INSERT,     
    TK_INSTEAD,    TK_INTO,       TK_OF,         TK_OFFSET,     TK_ISNULL,     
    TK_JOIN,       TK_ORDER,      TK_REPLACE,    TK_JOIN_KW,    TK_RESTRICT,   
    TK_PRIMARY,    TK_QUERY,      TK_JOIN_KW,    TK_ROLLBACK,   TK_ROW,        
    TK_WHERE,      TK_UNION,      TK_UNIQUE,     TK_USING,      TK_VACUUM,     
    TK_VALUES,     TK_VIEW,       TK_WORK,       
  };
  int h, i;
  if( n<2 ) return TK_ID;
  h = ((charMap(z[0])*4) ^
      (charMap(z[n-1])*3) ^
      n) % 127;
  for(i=((int)aHash[h])-1; i>=0; i=((int)aNext[i])-1){
    if( aLen[i]==n && sqlite3StrNICmp(&zText[aOffset[i]],z,n)==0 ){
      return aCode[i];
    }
  }
  return TK_ID;
}
int sqlite3KeywordCode(const unsigned char *z, int n){
  return keywordCode((char*)z, n);
}
