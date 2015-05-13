/* Hash score: 179 */
static int keywordCode(const char *z, int n){
  static const char zText[585] =
    "ABORTABLESCAPEACHARACTERAISELECTEMPORARYAFTEREFERENCESCHEMASESSION"
    "AMESHOWHENDATABASESTARTHENATURALEFTRANSACTIONOTNULLIKEYANALYZE"
    "LSEXCEPTRIGGEREGEXPLAINITIALLYANDEFAULTATTACHARSETAUTO_INCREMENT"
    "BEFOREIGNOREINDEXCLUSIVEXISTSTATEMENTBEGINNERENAMEBETWEENBYCASCADE"
    "FERRABLECASECASTATUSINGLOBALIMITCHECKCOLLATECOMMITCONFLICTCONSTRAINT"
    "ERSECTCREATECROSSCURRENT_DATECURRENT_TIMESTAMPLANDEFERREDELETE"
    "DESCDETACHAVINGROUPDATEDISTINCTDROPRAGMATCHFAILOCALFROMFULLIF"
    "IMMEDIATEINSERTINSTEADINTOFFSETISNULLJOINORDEREPLACEOUTERESTRICT"
    "PRIMARYQUERYRIGHTROLLBACKROWHEREUNIONUNIQUEVACUUMVALUESVARIABLES"
    "VIEWORK";
  static const unsigned char aHash[127] = {
     102,  92, 116, 101,   0,   9,   0,   0, 122, 123,  95,   0,   0,
     105,  52,  83, 103,   0, 115,  18,  88, 100,  23,   8,   0,   0,
     125,   0, 119, 112,   0,  38,   0,   0,  49,   0,   0,  73,  78,
       0,  65,   5,   0, 114,  42, 113,  17, 117,  81,   0,   0,  54,
       0,  84,  64,   0,  20,   0, 124,  44,  19,   0,  86,  69,  35,
      21,   0,   0,  41,  93,  60,  40,  57,  72,  89,   0,  55,   0,
      82,  36,   0,  79,   0,   0,   6,  66,  51,  74,  45,  99,  39,
      76,  98,   0,   1,  70,  22, 110,  61,   7,   0,  68,  94, 108,
      29,  26,  71,   0,   0,  48, 104,   0, 111,   0,  97,   0,   0,
      28,   0, 118,  58,  31,   0,   2,  30,   0, 120,
  };
  static const unsigned char aNext[125] = {
       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,  14,   0,   0,   0,   0,   0,   0,   0,  11,
       0,   0,   0,  25,   0,  13,   0,   0,   0,   0,  15,  24,   0,
       0,   0,   0,   0,   0,  12,   0,   0,   0,   0,   0,   0,   0,
       0,  10,  43,   0,   0,   0,   0,   0,  59,   0,   0,   0,  53,
       0,  46,  16,   0,   0,   0,   0,  62,  47,   0,   0,   0,   0,
       0,   0,  80,  50,   0,   0,   0,   4,  63,  67,   0,   0,  33,
       0,  91,   0,   0,  75,  77,   0,  96,   0,   0,   0,   3,   0,
       0,   0, 106, 107,   0,   0, 109,   0,  34,   0,  27,  37,  87,
       0,  32,  90,  56,   0,   0,  85, 121,
  };
  static const unsigned char aLen[125] = {
       5,   5,   6,   6,   4,   9,   5,   6,   4,   9,   2,   5,  10,
       7,   7,   5,   4,   4,   3,   8,   9,   2,   5,   4,   7,   4,
      11,   2,   3,   7,   4,   4,   3,   7,   4,   6,   7,   6,   7,
       9,   3,   3,   7,   6,   7,   3,  14,   2,   6,   3,   7,   6,
       7,   9,   6,   9,   5,   5,   6,   7,   2,   7,   3,  10,   4,
       4,   6,   5,   4,   6,   5,   5,   7,   6,   8,  10,   9,   6,
       5,  12,  12,  17,   4,   8,   6,   4,   6,   6,   5,   6,   8,
       2,   4,   6,   5,   4,   5,   4,   4,   2,   9,   6,   7,   4,
       2,   6,   6,   4,   5,   7,   5,   8,   7,   5,   5,   8,   3,
       5,   5,   6,   6,   6,   9,   4,   4,
  };
  static const unsigned short int aOffset[125] = {
       0,   4,   4,   8,  13,  15,  23,  26,  31,  31,  35,  40,  44,
      53,  59,  65,  69,  72,  74,  76,  76,  81,  84,  88,  91,  97,
     100, 109, 110, 110, 113, 116, 118, 121, 127, 130, 135, 141, 144,
     149, 154, 158, 160, 167, 171, 175, 178, 183, 192, 194, 194, 198,
     202, 207, 215, 220, 229, 232, 236, 242, 249, 251, 252, 256, 266,
     270, 272, 276, 280, 280, 285, 290, 295, 302, 308, 316, 323, 332,
     338, 343, 355, 355, 371, 375, 382, 388, 392, 397, 402, 405, 411,
     412, 419, 422, 426, 431, 434, 439, 443, 447, 449, 458, 464, 471,
     474, 474, 480, 486, 490, 494, 501, 505, 513, 520, 525, 530, 538,
     540, 545, 550, 556, 562, 568, 577, 580,
  };
  static const unsigned char aCode[125] = {
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
    TK_CAST,       TK_STATUS,     TK_USING,      TK_LIKE_KW,    TK_GLOBAL,     
    TK_LIMIT,      TK_CHECK,      TK_COLLATE,    TK_COMMIT,     TK_CONFLICT,   
    TK_CONSTRAINT, TK_INTERSECT,  TK_CREATE,     TK_JOIN_KW,    TK_CTIME_KW,   
    TK_CTIME_KW,   TK_CTIME_KW,   TK_PLAN,       TK_DEFERRED,   TK_DELETE,     
    TK_DESC,       TK_DETACH,     TK_HAVING,     TK_GROUP,      TK_UPDATE,     
    TK_DISTINCT,   TK_IS,         TK_DROP,       TK_PRAGMA,     TK_MATCH,      
    TK_FAIL,       TK_LOCAL,      TK_FROM,       TK_JOIN_KW,    TK_IF,         
    TK_IMMEDIATE,  TK_INSERT,     TK_INSTEAD,    TK_INTO,       TK_OF,         
    TK_OFFSET,     TK_ISNULL,     TK_JOIN,       TK_ORDER,      TK_REPLACE,    
    TK_JOIN_KW,    TK_RESTRICT,   TK_PRIMARY,    TK_QUERY,      TK_JOIN_KW,    
    TK_ROLLBACK,   TK_ROW,        TK_WHERE,      TK_UNION,      TK_UNIQUE,     
    TK_VACUUM,     TK_VALUES,     TK_VARIABLES,  TK_VIEW,       TK_WORK,       
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
