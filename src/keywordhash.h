/* Hash score: 180 */
static int keywordCode(const char *z, int n){
  static const char zText[594] =
    "ABORTABLESCAPEACHARACTERAISELECTEMPORARYAFTEREFERENCESCHEMASESSION"
    "AMESHOWHENDATABASESTARTHENATURALEFTRANSACTIONOTNULLIKEYANALYZE"
    "LSEXCEPTRIGGEREGEXPLAINITIALLYANDEFAULTATTACHARSETAUTO_INCREMENT"
    "BEFOREIGNOREINDEXCLUSIVEXISTSTATEMENTBEGINNERENAMEBETWEENBYCASCADE"
    "FERRABLECASECASTATUSINGLOBALIMITCHECKCOLLATECOLLATIONCOMMITCONFLICT"
    "CONSTRAINTERSECTCREATECROSSCURRENT_DATECURRENT_TIMESTAMPLANDEFERRED"
    "ELETEDESCDETACHAVINGROUPDATEDISTINCTDROPRAGMATCHFAILOCALFROMFULL"
    "IFIMMEDIATEINSERTINSTEADINTOFFSETISNULLJOINORDEREPLACEOUTERESTRICT"
    "PRIMARYQUERYRIGHTROLLBACKROWHEREUNIONUNIQUEVACUUMVALUESVARIABLES"
    "VIEWORK";
  static const unsigned char aHash[127] = {
     103,  93, 117, 102,   0,   9,   0,   0, 123, 124,  96,   0,   0,
     106,  52,  84, 104,   0, 116,  18,  89, 101,  23,   8,   0,   0,
     126,   0, 120, 113,   0,  38,   0,   0,  49,   0,   0,  73,  79,
       0,  65,   5,   0, 115,  42, 114,  17, 118,  82,   0,   0,  54,
       0,  85,  64,   0,  20,   0, 125,  44,  19,   0,  87,  69,  35,
      21,   0,   0,  41,  94,  60,  40,  57,  72,  90,   0,  55,   0,
      83,  36,  74,  80,   0,   0,   6,  66,  51,  75,  45, 100,  39,
      77,  99,   0,   1,  70,  22, 111,  61,   7,   0,  68,  95, 109,
      29,  26,  71,   0,   0,  48, 105,   0, 112,   0,  98,   0,   0,
      28,   0, 119,  58,  31,   0,   2,  30,   0, 121,
  };
  static const unsigned char aNext[126] = {
       0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
       0,   0,   0,   0,  14,   0,   0,   0,   0,   0,   0,   0,  11,
       0,   0,   0,  25,   0,  13,   0,   0,   0,   0,  15,  24,   0,
       0,   0,   0,   0,   0,  12,   0,   0,   0,   0,   0,   0,   0,
       0,  10,  43,   0,   0,   0,   0,   0,  59,   0,   0,   0,  53,
       0,  46,  16,   0,   0,   0,   0,  62,   0,  47,   0,   0,   0,
       0,   0,   0,  81,  50,   0,   0,   0,   4,  63,  67,   0,   0,
      33,   0,  92,   0,   0,  76,  78,   0,  97,   0,   0,   0,   3,
       0,   0,   0, 107, 108,   0,   0, 110,   0,  34,   0,  27,  37,
      88,   0,  32,  91,  56,   0,   0,  86, 122,
  };
  static const unsigned char aLen[126] = {
       5,   5,   6,   6,   4,   9,   5,   6,   4,   9,   2,   5,  10,
       7,   7,   5,   4,   4,   3,   8,   9,   2,   5,   4,   7,   4,
      11,   2,   3,   7,   4,   4,   3,   7,   4,   6,   7,   6,   7,
       9,   3,   3,   7,   6,   7,   3,  14,   2,   6,   3,   7,   6,
       7,   9,   6,   9,   5,   5,   6,   7,   2,   7,   3,  10,   4,
       4,   6,   5,   4,   6,   5,   5,   7,   9,   6,   8,  10,   9,
       6,   5,  12,  12,  17,   4,   8,   6,   4,   6,   6,   5,   6,
       8,   2,   4,   6,   5,   4,   5,   4,   4,   2,   9,   6,   7,
       4,   2,   6,   6,   4,   5,   7,   5,   8,   7,   5,   5,   8,
       3,   5,   5,   6,   6,   6,   9,   4,   4,
  };
  static const unsigned short int aOffset[126] = {
       0,   4,   4,   8,  13,  15,  23,  26,  31,  31,  35,  40,  44,
      53,  59,  65,  69,  72,  74,  76,  76,  81,  84,  88,  91,  97,
     100, 109, 110, 110, 113, 116, 118, 121, 127, 130, 135, 141, 144,
     149, 154, 158, 160, 167, 171, 175, 178, 183, 192, 194, 194, 198,
     202, 207, 215, 220, 229, 232, 236, 242, 249, 251, 252, 256, 266,
     270, 272, 276, 280, 280, 285, 290, 295, 302, 311, 317, 325, 332,
     341, 347, 352, 364, 364, 380, 384, 391, 397, 401, 406, 411, 414,
     420, 421, 428, 431, 435, 440, 443, 448, 452, 456, 458, 467, 473,
     480, 483, 483, 489, 495, 499, 503, 510, 514, 522, 529, 534, 539,
     547, 549, 554, 559, 565, 571, 577, 586, 589,
  };
  static const unsigned char aCode[126] = {
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
    TK_LIMIT,      TK_CHECK,      TK_COLLATE,    TK_COLLATION,  TK_COMMIT,     
    TK_CONFLICT,   TK_CONSTRAINT, TK_INTERSECT,  TK_CREATE,     TK_JOIN_KW,    
    TK_CTIME_KW,   TK_CTIME_KW,   TK_CTIME_KW,   TK_PLAN,       TK_DEFERRED,   
    TK_DELETE,     TK_DESC,       TK_DETACH,     TK_HAVING,     TK_GROUP,      
    TK_UPDATE,     TK_DISTINCT,   TK_IS,         TK_DROP,       TK_PRAGMA,     
    TK_MATCH,      TK_FAIL,       TK_LOCAL,      TK_FROM,       TK_JOIN_KW,    
    TK_IF,         TK_IMMEDIATE,  TK_INSERT,     TK_INSTEAD,    TK_INTO,       
    TK_OF,         TK_OFFSET,     TK_ISNULL,     TK_JOIN,       TK_ORDER,      
    TK_REPLACE,    TK_JOIN_KW,    TK_RESTRICT,   TK_PRIMARY,    TK_QUERY,      
    TK_JOIN_KW,    TK_ROLLBACK,   TK_ROW,        TK_WHERE,      TK_UNION,      
    TK_UNIQUE,     TK_VACUUM,     TK_VALUES,     TK_VARIABLES,  TK_VIEW,       
    TK_WORK,       
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
