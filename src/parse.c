/* Driver template for the LEMON parser generator.
** The author disclaims copyright to this source code.
*/
/* First off, code is include which follows the "include" declaration
** in the input file. */
#include <stdio.h>
#line 54 "parse.y"

#include "sqliteInt.h"
#include "parse.h"

/*
** An instance of this structure holds information about the
** LIMIT clause of a SELECT statement.
*/
struct LimitVal {
  Expr *pLimit;    /* The LIMIT expression.  NULL if there is no limit */
  Expr *pOffset;   /* The OFFSET expression.  NULL if there is none */
};

/*
** An instance of this structure is used to store the LIKE,
** GLOB, NOT LIKE, and NOT GLOB operators.
*/
struct LikeOp {
  Token eOperator;  /* "like" or "glob" or "regexp" */
  int not;         /* True if the NOT keyword is present */
};

/*
** An instance of the following structure describes the event of a
** TRIGGER.  "a" is the event type, one of TK_UPDATE, TK_INSERT,
** TK_DELETE, or TK_INSTEAD.  If the event is of the form
**
**      UPDATE ON (a,b,c)
**
** Then the "b" IdList records the list "a,b,c".
*/
struct TrigEvent { int a; IdList * b; };

/*
** An instance of this structure holds the ATTACH key and the key type.
*/
struct AttachKey { int type;  Token key; };

#line 48 "parse.c"
/* Next is all token values, in a form suitable for use by makeheaders.
** This section will be null unless lemon is run with the -m switch.
*/
/* 
** These constants (all generated automatically by the parser generator)
** specify the various kinds of tokens (terminals) that the parser
** understands. 
**
** Each symbol here is a terminal symbol in the grammar.
*/
/* Make sure the INTERFACE macro is defined.
*/
#ifndef INTERFACE
# define INTERFACE 1
#endif
/* The next thing included is series of defines which control
** various aspects of the generated parser.
**    YYCODETYPE         is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 terminals
**                       and nonterminals.  "int" is used otherwise.
**    YYNOCODE           is a number of type YYCODETYPE which corresponds
**                       to no legal terminal or nonterminal number.  This
**                       number is used to fill in empty slots of the hash 
**                       table.
**    YYFALLBACK         If defined, this indicates that one or more tokens
**                       have fall-back values which should be used if the
**                       original value of the token will not parse.
**    YYACTIONTYPE       is the data type used for storing terminal
**                       and nonterminal numbers.  "unsigned char" is
**                       used if there are fewer than 250 rules and
**                       states combined.  "int" is used otherwise.
**    sqlite3ParserTOKENTYPE     is the data type used for minor tokens given 
**                       directly to the parser from the tokenizer.
**    YYMINORTYPE        is the data type used for all minor tokens.
**                       This is typically a union of many types, one of
**                       which is sqlite3ParserTOKENTYPE.  The entry in the union
**                       for base tokens is called "yy0".
**    YYSTACKDEPTH       is the maximum depth of the parser's stack.
**    sqlite3ParserARG_SDECL     A static variable declaration for the %extra_argument
**    sqlite3ParserARG_PDECL     A parameter declaration for the %extra_argument
**    sqlite3ParserARG_STORE     Code to store %extra_argument into yypParser
**    sqlite3ParserARG_FETCH     Code to extract %extra_argument from yypParser
**    YYNSTATE           the combined number of states.
**    YYNRULE            the number of rules in the grammar
**    YYERRORSYMBOL      is the code number of the error symbol.  If not
**                       defined, then do no error processing.
*/
#define YYCODETYPE unsigned char
#define YYNOCODE 246
#define YYACTIONTYPE unsigned short int
#define sqlite3ParserTOKENTYPE Token
typedef union {
  sqlite3ParserTOKENTYPE yy0;
  int yy32;
  struct {int value; int mask;} yy47;
  ValuesList* yy49;
  struct LikeOp yy118;
  Select* yy149;
  SrcList* yy287;
  Token yy308;
  Expr* yy342;
  IdList* yy440;
  ExprList* yy462;
  struct LimitVal yy474;
  int yy491;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define sqlite3ParserARG_SDECL Parse *pParse;
#define sqlite3ParserARG_PDECL ,Parse *pParse
#define sqlite3ParserARG_FETCH Parse *pParse = yypParser->pParse
#define sqlite3ParserARG_STORE yypParser->pParse = pParse
#define YYNSTATE 488
#define YYNRULE 269
#define YYERRORSYMBOL 145
#define YYERRSYMDT yy491
#define YYFALLBACK 1
#define YY_NO_ACTION      (YYNSTATE+YYNRULE+2)
#define YY_ACCEPT_ACTION  (YYNSTATE+YYNRULE+1)
#define YY_ERROR_ACTION   (YYNSTATE+YYNRULE)

/* Next are that tables used to determine what action to take based on the
** current state and lookahead token.  These tables are used to implement
** functions that take a state number and lookahead value and return an
** action integer.  
**
** Suppose the action integer is N.  Then the action is determined as
** follows
**
**   0 <= N < YYNSTATE                  Shift N.  That is, push the lookahead
**                                      token onto the stack and goto state N.
**
**   YYNSTATE <= N < YYNSTATE+YYNRULE   Reduce by rule N-YYNSTATE.
**
**   N == YYNSTATE+YYNRULE              A syntax error has occurred.
**
**   N == YYNSTATE+YYNRULE+1            The parser accepts its input.
**
**   N == YYNSTATE+YYNRULE+2            No such action.  Denotes unused
**                                      slots in the yy_action[] table.
**
** The action table is constructed as a single large table named yy_action[].
** Given state S and lookahead X, the action is computed as
**
**      yy_action[ yy_shift_ofst[S] + X ]
**
** If the index value yy_shift_ofst[S]+X is out of range or if the value
** yy_lookahead[yy_shift_ofst[S]+X] is not equal to X or if yy_shift_ofst[S]
** is equal to YY_SHIFT_USE_DFLT, it means that the action is not in the table
** and that yy_default[S] should be used instead.  
**
** The formula above is for computing the action when the lookahead is
** a terminal symbol.  If the lookahead is a non-terminal (as occurs after
** a reduce action) then the yy_reduce_ofst[] array is used in place of
** the yy_shift_ofst[] array and YY_REDUCE_USE_DFLT is used in place of
** YY_SHIFT_USE_DFLT.
**
** The following are the tables generated in this section:
**
**  yy_action[]        A single table containing all actions.
**  yy_lookahead[]     A table containing the lookahead for each entry in
**                     yy_action.  Used to detect hash collisions.
**  yy_shift_ofst[]    For each state, the offset into yy_action for
**                     shifting terminals.
**  yy_reduce_ofst[]   For each state, the offset into yy_action for
**                     shifting non-terminals after a reduce.
**  yy_default[]       Default action for each state.
*/
static const YYACTIONTYPE yy_action[] = {
 /*     0 */   231,  758,  103,  487,  445,  143,    1,  362,   56,   55,
 /*    10 */    55,   55,   55,  440,   57,   57,   57,   57,   58,   58,
 /*    20 */    59,   59,   59,   60,   62,   57,   57,   57,   57,   58,
 /*    30 */    58,   59,   59,   59,   60,  375,   57,   57,   57,   57,
 /*    40 */    58,   58,   59,   59,   59,   60,   58,   58,   59,   59,
 /*    50 */    59,   60,   54,   52,  239,  383,  386,  380,  380,   56,
 /*    60 */    55,   55,   55,   55,  163,   57,   57,   57,   57,   58,
 /*    70 */    58,   59,   59,   59,   60,  231,   60,  263,  362,  307,
 /*    80 */   235,   71,  127,   56,  177,  308,  474,  475,  476,   98,
 /*    90 */   434,  374,  210,  235,  447,  263,  442,  352,   24,  263,
 /*   100 */   327,  270,   17,  388,  388,  210,  314,  311,  250,  315,
 /*   110 */   375,  329,  161,  126,   51,  352,   30,  353,  443,  352,
 /*   120 */    42,  156,  356,  244,  444,  125,  457,   54,   52,  239,
 /*   130 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  413,
 /*   140 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   150 */   231,  434,  358,  358,  358,   93,  353,  456,   56,  329,
 /*   160 */   136,  333,  186,  259,  190,  260,  147,  247,  209,  197,
 /*   170 */    16,  211,  120,  263,  333,  186,  259,  190,  260,  147,
 /*   180 */   448,  102,  330,  331,  211,  375,  198,  152,  409,  114,
 /*   190 */   282,  285,  286,  352,   29,  238,  365,  366,  241,  287,
 /*   200 */   480,  481,   54,   52,  239,  383,  386,  380,  380,   56,
 /*   210 */    55,   55,   55,   55,  112,   57,   57,   57,   57,   58,
 /*   220 */    58,   59,   59,   59,   60,  231,  455,  415,  423,  208,
 /*   230 */   330,  331,  152,   56,  454,  282,  285,  286,   61,  397,
 /*   240 */   167,  263,  128,  280,  287,   61,  263,  167,  351,  128,
 /*   250 */   393,  263,  350,  152,  107,  404,  282,  285,  286,  165,
 /*   260 */   375,  352,   29,  352,    3,  287,  352,   29,  145,  370,
 /*   270 */   166,  352,   35,  266,  365,  366,  163,   54,   52,  239,
 /*   280 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  225,
 /*   290 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   300 */   231,  263,  418,  353,  242,  220,  129,  389,   56,  276,
 /*   310 */   409,  274,  201,  263,  290,  146,  133,  329,  394,  263,
 /*   320 */   279,  352,   29,  394,  447,  390,  183,    2,  131,  450,
 /*   330 */   458,  329,   17,  352,   42,  375,  329,  165,    9,  352,
 /*   340 */    35,  353,  329,  228,  226,   67,  372,  446,  140,  203,
 /*   350 */   148,  404,   54,   52,  239,  383,  386,  380,  380,   56,
 /*   360 */    55,   55,   55,   55,  240,   57,   57,   57,   57,   58,
 /*   370 */    58,   59,   59,   59,   60,  231,  339,  191,  394,  419,
 /*   380 */   199,  248,  472,   56,   59,   59,   59,   60,  330,  331,
 /*   390 */   347,  329,  270,  340,  388,  388,  329,  270,  348,  388,
 /*   400 */   388,  232,  330,  331,  143,  211,  362,  330,  331,  341,
 /*   410 */   375,  337,  405,  330,  331,  270,  307,  388,  388,  434,
 /*   420 */    70,  362,  338,  474,  475,  476,  132,   54,   52,  239,
 /*   430 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  409,
 /*   440 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   450 */   231,  376,  175,  306,  422,  263,  472,   61,   56,  167,
 /*   460 */   417,  128,  330,  331,  372,  267,  140,  330,  331,  263,
 /*   470 */   277,  378,  379,  263,  202,  352,   25,  362,  205,  263,
 /*   480 */   328,  439,  488,  314,  311,  375,  406,  264,  436,  352,
 /*   490 */    20,  299,  362,  352,   28,  305,  118,  209,  377,  352,
 /*   500 */    47,  220,   54,   52,  239,  383,  386,  380,  380,   56,
 /*   510 */    55,   55,   55,   55,  263,   57,   57,   57,   57,   58,
 /*   520 */    58,   59,   59,   59,   60,  231,  263,  309,  263,  441,
 /*   530 */   263,  117,  332,   56,  352,   21,  263,  434,  263,  436,
 /*   540 */   462,  263,   66,  263,   68,  263,  352,   45,  352,   84,
 /*   550 */   352,   82,  263,  299,  263,  176,  352,   86,  352,   87,
 /*   560 */   375,  352,   94,  352,   95,  352,   15,   18,   99,  434,
 /*   570 */   245,  362,  352,   85,  352,   46,  158,   54,   52,  239,
 /*   580 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  263,
 /*   590 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   600 */   231,  263,  246,  263,  214,  263,  362,  263,   56,  352,
 /*   610 */    96,  353,  263,  335,  336,  209,  263,  302,  263,  402,
 /*   620 */   263,  352,   97,  352,   22,  352,   31,  352,   32,  263,
 /*   630 */     5,  313,  352,   23,    1,  375,  352,   33,  352,   34,
 /*   640 */   352,   36,  362,  253,  485,  234,  413,  209,  357,  352,
 /*   650 */    37,  220,   54,   52,  239,  383,  386,  380,  380,   56,
 /*   660 */    55,   55,   55,   55,  263,   57,   57,   57,   57,   58,
 /*   670 */    58,   59,   59,   59,   60,  231,  263,  362,  263,  220,
 /*   680 */   263,  220,  263,   56,  352,   38,  263,  243,  263,  281,
 /*   690 */   221,  263,  299,  482,  482,  428,  352,   26,  352,   27,
 /*   700 */   352,   39,  352,   40,  130,  249,  352,   41,  352,   43,
 /*   710 */   375,  352,   44,  351,  122,  473,  154,  350,  297,  429,
 /*   720 */   224,  149,  150,  151,  142,  133,  384,   54,   52,  239,
 /*   730 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  353,
 /*   740 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   750 */   231,  353,  164,  368,  368,  160,  304,  344,   56,   48,
 /*   760 */   384,  157,  255,  148,  185,  187,  345,  363,  137,   19,
 /*   770 */   268,  392,  371,   11,  188,  411,  420,  144,   11,  432,
 /*   780 */   395,  107,  427,  403,  213,  375,  107,  289,  467,  107,
 /*   790 */    79,  425,  468,  469,   79,  144,  408,  412,  207,  424,
 /*   800 */   160,  430,  431,   52,  239,  383,  386,  380,  380,   56,
 /*   810 */    55,   55,   55,   55,  232,   57,   57,   57,   57,   58,
 /*   820 */    58,   59,   59,   59,   60,  231,  310,  449,  215,  218,
 /*   830 */   298,  484,  322,   56,  189,  121,  192,  367,   63,  271,
 /*   840 */   269,    4,  385,  369,  398,  237,  401,  272,  423,  284,
 /*   850 */   223,  478,  381,  479,  483,  426,  433,  435,  265,  318,
 /*   860 */   375,  317,  320,  321,   73,  524,    8,  252,  256,  325,
 /*   870 */   257,  334,  258,  342,  236,  343,  346,  349,  354,  239,
 /*   880 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  374,
 /*   890 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   900 */    73,  193,  275,  194,   72,  195,  273,   65,   64,   50,
 /*   910 */   196,   63,  271,   69,    4,   63,  261,  262,  237,  169,
 /*   920 */   356,  355,   63,  271,  141,    4,  396,  200,  399,  237,
 /*   930 */   400,  265,   74,  170,  104,  171,  163,  204,  278,  410,
 /*   940 */   206,   89,  265,  414,  229,  230,  173,  437,  174,  461,
 /*   950 */   358,  358,  358,  359,  360,  361,   10,  451,  291,  180,
 /*   960 */   251,  292,  374,  181,  182,  216,  459,  108,  438,  452,
 /*   970 */   453,  155,  295,  374,  463,  222,  300,  115,  113,  100,
 /*   980 */    65,   64,  416,   14,  233,   83,  172,   88,   63,  261,
 /*   990 */   262,   65,   64,  356,  316,  465,  319,  227,   75,   63,
 /*  1000 */   261,  262,  399,  466,  356,  254,  323,  303,  324,  184,
 /*  1010 */   471,  326,  101,  162,   49,   53,  525,  526,  138,  139,
 /*  1020 */   364,  373,  382,  358,  358,  358,  359,  360,  361,   10,
 /*  1030 */   168,  387,  119,  391,  358,  358,  358,  359,  360,  361,
 /*  1040 */    10,   12,    6,   11,    7,  407,  374,  105,  134,  106,
 /*  1050 */   421,  283,   90,  153,  212,   91,  296,  110,  470,   76,
 /*  1060 */   288,  294,   92,  188,  123,  124,  163,  217,  293,  219,
 /*  1070 */   109,  460,  111,  443,  464,   77,  116,  356,  477,   13,
 /*  1080 */    78,  301,   80,  157,  135,  179,  312,  516,   81,  486,
 /*  1090 */   178,  516,  516,  516,  516,  159,  516,  516,  516,  516,
 /*  1100 */   516,  516,  516,  516,  516,  516,  516,  358,  358,  358,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    14,  146,  147,  148,  168,   19,  151,   21,   22,   74,
 /*    10 */    75,   76,   77,  177,   79,   80,   81,   82,   83,   84,
 /*    20 */    85,   86,   87,   88,   78,   79,   80,   81,   82,   83,
 /*    30 */    84,   85,   86,   87,   88,   49,   79,   80,   81,   82,
 /*    40 */    83,   84,   85,   86,   87,   88,   83,   84,   85,   86,
 /*    50 */    87,   88,   66,   67,   68,   69,   70,   71,   72,   73,
 /*    60 */    74,   75,   76,   77,  112,   79,   80,   81,   82,   83,
 /*    70 */    84,   85,   86,   87,   88,   14,   88,  157,   92,  131,
 /*    80 */    14,   20,  162,   22,  136,  137,  138,  139,  140,   23,
 /*    90 */   157,   65,   26,   14,  157,  157,  177,  177,  178,  157,
 /*   100 */   163,  108,  165,  110,  111,   26,    1,    2,  149,  150,
 /*   110 */    49,   21,  153,   20,   53,  177,  178,  197,   92,  177,
 /*   120 */   178,  162,   96,  190,  177,  188,  189,   66,   67,   68,
 /*   130 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  157,
 /*   140 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   150 */    14,  157,  126,  127,  128,   19,  197,  189,   22,   21,
 /*   160 */    94,   95,   96,   97,   98,   99,  100,  225,  235,  231,
 /*   170 */    17,  105,   19,  157,   95,   96,   97,   98,   99,  100,
 /*   180 */   189,  222,   92,   93,  105,   49,  157,   94,  169,   25,
 /*   190 */    97,   98,   99,  177,  178,  172,  173,  174,  216,  106,
 /*   200 */   241,  242,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   210 */    74,   75,   76,   77,  124,   79,   80,   81,   82,   83,
 /*   220 */    84,   85,   86,   87,   88,   14,  183,  208,  185,  235,
 /*   230 */    92,   93,   94,   22,  191,   97,   98,   99,  226,  227,
 /*   240 */   228,  157,  230,  157,  106,  226,  157,  228,  109,  230,
 /*   250 */   234,  157,  113,   94,   20,   20,   97,   98,   99,  236,
 /*   260 */    49,  177,  178,  177,  178,  106,  177,  178,  162,   83,
 /*   270 */    84,  177,  178,  172,  173,  174,  112,   66,   67,   68,
 /*   280 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  125,
 /*   290 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   300 */    14,  157,   18,  197,  220,  157,  162,   18,   22,  220,
 /*   310 */   169,  217,  218,  157,   14,  209,  210,   21,  234,  157,
 /*   320 */   214,  177,  178,  234,  157,   18,  159,   17,   93,   95,
 /*   330 */   163,   21,  165,  177,  178,   49,   21,  236,   17,  177,
 /*   340 */   178,  197,   21,  166,  196,  134,  169,  170,  171,  208,
 /*   350 */    50,  116,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   360 */    74,   75,   76,   77,  220,   79,   80,   81,   82,   83,
 /*   370 */    84,   85,   86,   87,   88,   14,   10,  198,  234,   18,
 /*   380 */   218,  225,  169,   22,   85,   86,   87,   88,   92,   93,
 /*   390 */    30,   21,  108,   27,  110,  111,   21,  108,   38,  110,
 /*   400 */   111,  101,   92,   93,   19,  105,   21,   92,   93,   43,
 /*   410 */    49,   45,  116,   92,   93,  108,  131,  110,  111,  157,
 /*   420 */   134,   21,   56,  138,  139,  140,  157,   66,   67,   68,
 /*   430 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  169,
 /*   440 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   450 */    14,   49,  190,  240,   18,  157,  169,  226,   22,  228,
 /*   460 */    85,  230,   92,   93,  169,  170,  171,   92,   93,  157,
 /*   470 */   157,   69,   70,  157,  157,  177,  178,   92,  208,  157,
 /*   480 */   175,  176,    0,    1,    2,   49,  116,  157,  183,  177,
 /*   490 */   178,  157,   92,  177,  178,  238,  239,  235,   96,  177,
 /*   500 */   178,  157,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   510 */    74,   75,   76,   77,  157,   79,   80,   81,   82,   83,
 /*   520 */    84,   85,   86,   87,   88,   14,  157,  240,  157,   18,
 /*   530 */   157,  239,  176,   22,  177,  178,  157,  157,  157,  183,
 /*   540 */   196,  157,  133,  157,  135,  157,  177,  178,  177,  178,
 /*   550 */   177,  178,  157,  157,  157,  221,  177,  178,  177,  178,
 /*   560 */    49,  177,  178,  177,  178,  177,  178,   17,  157,  157,
 /*   570 */   190,   21,  177,  178,  177,  178,  162,   66,   67,   68,
 /*   580 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  157,
 /*   590 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   600 */    14,  157,  190,  157,   18,  157,   21,  157,   22,  177,
 /*   610 */   178,  197,  157,  193,  194,  235,  157,  221,  157,   20,
 /*   620 */   157,  177,  178,  177,  178,  177,  178,  177,  178,  157,
 /*   630 */   199,  148,  177,  178,  151,   49,  177,  178,  177,  178,
 /*   640 */   177,  178,   92,   21,   93,   23,  157,  235,  157,  177,
 /*   650 */   178,  157,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   660 */    74,   75,   76,   77,  157,   79,   80,   81,   82,   83,
 /*   670 */    84,   85,   86,   87,   88,   14,  157,   92,  157,  157,
 /*   680 */   157,  157,  157,   22,  177,  178,  157,   25,  157,   85,
 /*   690 */   196,  157,  157,  142,  143,   33,  177,  178,  177,  178,
 /*   700 */   177,  178,  177,  178,  162,  216,  177,  178,  177,  178,
 /*   710 */    49,  177,  178,  109,  115,  130,  162,  113,  196,   57,
 /*   720 */   196,  102,  103,  104,  209,  210,   92,   66,   67,   68,
 /*   730 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  197,
 /*   740 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   750 */    14,  197,  200,  126,  127,   70,  221,   37,   22,  207,
 /*   760 */   126,   20,   24,   50,   26,   96,   46,   18,   17,   20,
 /*   770 */    14,   18,  169,   20,  105,   18,   18,   20,   20,   18,
 /*   780 */   157,   20,   23,  211,   18,   49,   20,   18,   18,   20,
 /*   790 */    20,  186,   18,   18,   20,   20,  157,  157,  157,  157,
 /*   800 */   115,  186,  186,   67,   68,   69,   70,   71,   72,   73,
 /*   810 */    74,   75,   76,   77,  101,   79,   80,   81,   82,   83,
 /*   820 */    84,   85,   86,   87,   88,   14,  243,  157,  157,  157,
 /*   830 */   157,  157,  154,   22,  180,  199,  201,  237,   14,   15,
 /*   840 */   229,   17,  229,  237,  180,   21,  180,  233,  185,  184,
 /*   850 */   202,  169,   96,  169,  244,   96,  180,  180,   34,    8,
 /*   860 */    49,  152,  152,  152,  123,  114,   20,  160,  164,   22,
 /*   870 */   164,  179,  101,  179,   47,  187,  179,  179,  197,   68,
 /*   880 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   65,
 /*   890 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   900 */   123,  202,  120,  203,  121,  204,  118,   83,   84,  122,
 /*   910 */   205,   14,   15,  133,   17,   91,   92,   93,   21,  232,
 /*   920 */    96,  206,   14,   15,  114,   17,  158,   26,   21,   21,
 /*   930 */   168,   34,  101,  219,  158,  219,  112,  212,  117,  213,
 /*   940 */   212,   17,   34,  213,  181,  181,  219,  168,  219,   16,
 /*   950 */   126,  127,  128,  129,  130,  131,  132,  179,  155,    5,
 /*   960 */     6,   13,   65,    9,   10,   11,  158,  195,  187,  179,
 /*   970 */   179,  156,   13,   65,  158,  202,  224,   17,  223,   25,
 /*   980 */    83,   84,   85,   17,  161,  167,  182,  182,   91,   92,
 /*   990 */    93,   83,   84,   96,    1,  206,    7,   18,   17,   91,
 /*  1000 */    92,   93,   21,  206,   96,   22,   21,  223,   21,   25,
 /*  1010 */    56,   21,   35,   51,   17,   17,  114,  114,  114,  114,
 /*  1020 */    18,   18,   96,  126,  127,  128,  129,  130,  131,  132,
 /*  1030 */    67,  109,   17,   41,  126,  127,  128,  129,  130,  131,
 /*  1040 */   132,   20,  119,   20,  119,  116,   65,   17,  114,   18,
 /*  1050 */    18,   51,   17,  100,   18,   17,  102,  103,  104,   17,
 /*  1060 */    51,  107,   17,  105,   83,   84,  112,   12,   14,   12,
 /*  1070 */   115,   15,   25,   92,   15,   22,   25,   96,  114,   17,
 /*  1080 */    22,   20,   22,   20,   20,  144,    3,  245,   22,    4,
 /*  1090 */    25,  245,  245,  245,  245,  141,  245,  245,  245,  245,
 /*  1100 */   245,  245,  245,  245,  245,  245,  245,  126,  127,  128,
};
#define YY_SHIFT_USE_DFLT (-66)
#define YY_SHIFT_MAX 312
static const short yy_shift_ofst[] = {
 /*     0 */   105,  954,  824,  -14,  824,  908,  908,  908,  138,  -48,
 /*    10 */   908,  908,  908,  908,  908,  -54,  315,  400,  186,  186,
 /*    20 */    61,  136,  211,  286,  361,  436,  511,  586,  661,  661,
 /*    30 */   661,  661,  661,  661,  661,  661,  661,  661,  661,  661,
 /*    40 */   661,  661,  661,  661,  661,  736,  811,  811,  897,  908,
 /*    50 */   908,  908,  908,  908,  908,  908,  908,  908,  908,  908,
 /*    60 */   908,  908,  908,  908,  908,  908,  908,  908,  908,  908,
 /*    70 */   908,  908,  908,  908,  908,  908,  908,  908,  908,  908,
 /*    80 */   908,  908,  -65,   66,  -43,  -43,  -37,  299,  300,  315,
 /*    90 */   315,  315,  315,  400,  -12,  -66,  -66,  -66,  981,   79,
 /*   100 */   -52,  366,   90,  482,  385,  315,  385,  315,  315,  315,
 /*   110 */   315,  315,  315,  164,  315,  315,  315,  585,  585,  -48,
 /*   120 */   -48,  -66,  -66,   26,   26,   93,  159,  284,  310,  289,
 /*   130 */   307,  296,  370,  321,  375,  285,  315,  604,  315,  315,
 /*   140 */   550,  315,  235,  315,  315,   -7,  235,  315,  315,  662,
 /*   150 */   662,  662,  315,  315,   -7,  315,   -7,  315,   -7,  551,
 /*   160 */   315,  153,  360,  139,  599,  627,  627,  634,  634,  409,
 /*   170 */   360,  360,  713,  360,  360,  234,  741,  400,  400,  685,
 /*   180 */   851,  851,  851,  846,  847,  847,  771,  771,  827,  771,
 /*   190 */   771,  -48,  777,  782,  783,  788,  787,  780,  810,  901,
 /*   200 */   907,  901,  810,  831,  821,  831,  821,  924,  901,  901,
 /*   210 */   907,  827,  771,  771,  771,  924,  933,  948,  810,  959,
 /*   220 */   810,  777,  787,  787,  960,  966,  960,  -66,  -66,  -66,
 /*   230 */   -66,  402,  619,  622,  738,  669,  720,  751,  749,  756,
 /*   240 */   753,  757,  758,  759,  761,  766,  769,  770,  774,  775,
 /*   250 */   993,  989,  979,  983,  985,  984,  987,  990,  977,  962,
 /*   260 */   997,  902,  903,  904,  905,  998, 1002, 1003,  926,  963,
 /*   270 */   922, 1015,  992,  923, 1021,  925, 1023,  929, 1030, 1031,
 /*   280 */   934, 1032, 1000, 1035, 1036, 1038, 1042, 1009, 1045,  953,
 /*   290 */   958, 1055, 1054, 1056, 1057, 1059,  955, 1047, 1053, 1058,
 /*   300 */  1061, 1062, 1063, 1051, 1063, 1064, 1060,  964, 1065, 1066,
 /*   310 */   941, 1083, 1085,
};
#define YY_REDUCE_USE_DFLT (-165)
#define YY_REDUCE_MAX 230
static const short yy_reduce_ofst[] = {
 /*     0 */  -145,  -41,  144,   19,  -80,   84,   94,   89,  -63,  106,
 /*    10 */   -62,   16,  162,  -58,  156,   12,  167,  177,   23,  101,
 /*    20 */   231,  231,  231,  231,  231,  231,  231,  231,  231,  231,
 /*    30 */   231,  231,  231,  231,  231,  231,  231,  231,  231,  231,
 /*    40 */   231,  231,  231,  231,  231,  231,  231,  231,   86,  298,
 /*    50 */   312,  316,  322,  357,  369,  371,  373,  379,  381,  384,
 /*    60 */   386,  388,  395,  397,  432,  444,  446,  448,  450,  455,
 /*    70 */   459,  461,  463,  472,  507,  519,  521,  523,  525,  529,
 /*    80 */   531,  534,  231,  305,  231,  231,  231,  231,   43,  -67,
 /*    90 */   262,  380,  412,  295,  231,  231,  231,  231, -164,  356,
 /*   100 */   257,  420,  148,  483,  141,  -18,  270,   -6,  344,  494,
 /*   110 */   522,  334,  524,  414,  396,  489,  535,  213,  287,  542,
 /*   120 */   554,  552,  515,  -81,  -53,  -32,   -9,  179,   29,  179,
 /*   130 */   179,  269,  313,  317,  330,  292,  411,  431,  330,  491,
 /*   140 */   603,  623,  572,  639,  640,  179,  572,  641,  642,  605,
 /*   150 */   615,  616,  670,  671,  179,  672,  179,  673,  179,  583,
 /*   160 */   674,  678,  654,  636,  635,  600,  606,  611,  613,  614,
 /*   170 */   664,  666,  663,  676,  677,  665,  648,  682,  684,  610,
 /*   180 */   709,  710,  711,  707,  704,  706,  692,  694,  688,  697,
 /*   190 */   698,  681,  699,  700,  701,  705,  715,  687,  768,  714,
 /*   200 */   762,  716,  776,  725,  726,  728,  730,  763,  727,  729,
 /*   210 */   779,  781,  778,  790,  791,  764,  803,  815,  808,  772,
 /*   220 */   816,  773,  789,  797,  755,  752,  784,  823,  818,  804,
 /*   230 */   805,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   494,  757,  723,  608,  757,  723,  757,  723,  757,  612,
 /*    10 */   719,  723,  757,  757,  757,  693,  757,  527,  733,  733,
 /*    20 */   643,  757,  757,  757,  757,  757,  757,  757,  644,  722,
 /*    30 */   718,  714,  716,  715,  645,  632,  641,  648,  624,  650,
 /*    40 */   651,  660,  661,  740,  741,  683,  699,  682,  757,  757,
 /*    50 */   757,  757,  757,  757,  757,  757,  757,  757,  757,  757,
 /*    60 */   757,  757,  757,  757,  757,  757,  757,  757,  757,  757,
 /*    70 */   757,  757,  757,  757,  757,  757,  757,  757,  757,  757,
 /*    80 */   757,  757,  685,  520,  684,  692,  686,  687,  581,  757,
 /*    90 */   757,  757,  757,  757,  688,  689,  700,  701,  757,  757,
 /*   100 */   746,  757,  757,  494,  608,  757,  608,  757,  757,  757,
 /*   110 */   757,  757,  757,  757,  757,  757,  757,  757,  757,  757,
 /*   120 */   757,  602,  612,  757,  757,  572,  757,  757,  757,  757,
 /*   130 */   757,  757,  757,  757,  757,  746,  757,  600,  757,  757,
 /*   140 */   529,  757,  610,  757,  757,  615,  616,  757,  757,  757,
 /*   150 */   757,  757,  757,  757,  510,  757,  591,  757,  655,  754,
 /*   160 */   757,  757,  635,  600,  609,  757,  757,  757,  757,  717,
 /*   170 */   635,  635,  551,  635,  635,  554,  647,  757,  757,  755,
 /*   180 */   499,  499,  499,  571,  518,  518,  583,  583,  568,  583,
 /*   190 */   583,  757,  647,  638,  640,  628,  642,  757,  617,  636,
 /*   200 */   757,  636,  617,  625,  627,  625,  627,  724,  636,  636,
 /*   210 */   757,  568,  583,  583,  583,  724,  508,  505,  617,  590,
 /*   220 */   617,  647,  642,  642,  662,  757,  662,  513,  537,  556,
 /*   230 */   556,  757,  757,  509,  757,  757,  757,  669,  757,  757,
 /*   240 */   757,  757,  757,  757,  757,  757,  757,  757,  757,  757,
 /*   250 */   757,  757,  757,  514,  757,  757,  757,  757,  757,  757,
 /*   260 */   757,  674,  670,  757,  671,  757,  757,  757,  757,  757,
 /*   270 */   594,  757,  757,  757,  629,  757,  639,  757,  757,  757,
 /*   280 */   757,  757,  757,  757,  757,  757,  757,  757,  757,  757,
 /*   290 */   757,  757,  757,  757,  757,  757,  757,  757,  757,  757,
 /*   300 */   652,  757,  653,  757,  654,  737,  757,  757,  757,  757,
 /*   310 */   757,  495,  757,  489,  492,  491,  493,  497,  500,  498,
 /*   320 */   501,  502,  503,  515,  516,  519,  517,  511,  536,  524,
 /*   330 */   525,  526,  538,  545,  546,  584,  585,  586,  587,  734,
 /*   340 */   735,  736,  547,  566,  569,  570,  548,  633,  634,  549,
 /*   350 */   598,  599,  666,  592,  593,  597,  668,  672,  673,  675,
 /*   360 */   676,  677,  523,  530,  531,  534,  535,  729,  731,  730,
 /*   370 */   732,  533,  532,  678,  681,  690,  691,  697,  703,  707,
 /*   380 */   695,  696,  698,  702,  704,  705,  706,  595,  596,  710,
 /*   390 */   712,  713,  708,  720,  721,  618,  711,  694,  630,  522,
 /*   400 */   637,  631,  601,  611,  620,  621,  622,  623,  606,  607,
 /*   410 */   613,  626,  664,  665,  614,  603,  604,  605,  709,  667,
 /*   420 */   679,  680,  550,  557,  558,  559,  562,  563,  564,  565,
 /*   430 */   560,  561,  725,  726,  728,  727,  552,  553,  567,  539,
 /*   440 */   540,  541,  542,  674,  543,  544,  528,  521,  573,  576,
 /*   450 */   555,  577,  578,  579,  580,  582,  574,  575,  512,  504,
 /*   460 */   506,  507,  588,  619,  589,  646,  649,  658,  659,  663,
 /*   470 */   656,  657,  747,  748,  742,  743,  744,  745,  738,  739,
 /*   480 */   749,  750,  751,  752,  756,  753,  496,  490,
};
#define YY_SZ_ACTTAB (sizeof(yy_action)/sizeof(yy_action[0]))

/* The next table maps tokens into fallback tokens.  If a construct
** like the following:
** 
**      %fallback ID X Y Z.
**
** appears in the grammer, then ID becomes a fallback token for X, Y,
** and Z.  Whenever one of the tokens X, Y, or Z is input to the parser
** but it does not parse, the type of the token is changed to ID and
** the parse is retried before an error is thrown.
*/
#ifdef YYFALLBACK
static const YYCODETYPE yyFallback[] = {
    0,  /*          $ => nothing */
    0,  /*       SEMI => nothing */
   21,  /*    EXPLAIN => ID */
   21,  /*      QUERY => ID */
   21,  /*       PLAN => ID */
   21,  /*      BEGIN => ID */
    0,  /*      START => nothing */
    0,  /* TRANSACTION => nothing */
    0,  /*       WORK => nothing */
    0,  /*     COMMIT => nothing */
    0,  /*   ROLLBACK => nothing */
    0,  /*     CREATE => nothing */
    0,  /*      TABLE => nothing */
   21,  /*         IF => ID */
    0,  /*        NOT => nothing */
    0,  /*     EXISTS => nothing */
   21,  /*       TEMP => ID */
    0,  /*         LP => nothing */
    0,  /*         RP => nothing */
    0,  /*         AS => nothing */
    0,  /*      COMMA => nothing */
    0,  /*         ID => nothing */
    0,  /*         EQ => nothing */
    0,  /*    DEFAULT => nothing */
    0,  /*    CHARSET => nothing */
    0,  /*        SET => nothing */
    0,  /*    COLLATE => nothing */
   21,  /*      ABORT => ID */
   21,  /*      AFTER => ID */
   21,  /*    ANALYZE => ID */
   21,  /*        ASC => ID */
   21,  /*     ATTACH => ID */
   21,  /*     BEFORE => ID */
   21,  /*    CASCADE => ID */
   21,  /*       CAST => ID */
   21,  /*   CONFLICT => ID */
   21,  /*   DATABASE => ID */
   21,  /*   DEFERRED => ID */
   21,  /*       DESC => ID */
   21,  /*     DETACH => ID */
   21,  /*       EACH => ID */
   21,  /*        END => ID */
   21,  /*  EXCLUSIVE => ID */
   21,  /*       FAIL => ID */
   21,  /*        FOR => ID */
   21,  /*     IGNORE => ID */
   21,  /*  IMMEDIATE => ID */
   21,  /*  INITIALLY => ID */
   21,  /*    INSTEAD => ID */
   21,  /*    LIKE_KW => ID */
   21,  /*      MATCH => ID */
   21,  /*        KEY => ID */
   21,  /*         OF => ID */
   21,  /*     OFFSET => ID */
   21,  /*     PRAGMA => ID */
   21,  /*      RAISE => ID */
   21,  /*    REPLACE => ID */
   21,  /*   RESTRICT => ID */
   21,  /*        ROW => ID */
   21,  /*  STATEMENT => ID */
   21,  /*    TRIGGER => ID */
   21,  /*     VACUUM => ID */
   21,  /*       VIEW => ID */
   21,  /*    REINDEX => ID */
   21,  /*     RENAME => ID */
   21,  /*   CTIME_KW => ID */
    0,  /*         OR => nothing */
    0,  /*        AND => nothing */
    0,  /*         IS => nothing */
    0,  /*    BETWEEN => nothing */
    0,  /*         IN => nothing */
    0,  /*     ISNULL => nothing */
    0,  /*    NOTNULL => nothing */
    0,  /*         NE => nothing */
    0,  /*         GT => nothing */
    0,  /*         LE => nothing */
    0,  /*         LT => nothing */
    0,  /*         GE => nothing */
    0,  /*     ESCAPE => nothing */
    0,  /*     BITAND => nothing */
    0,  /*      BITOR => nothing */
    0,  /*     LSHIFT => nothing */
    0,  /*     RSHIFT => nothing */
    0,  /*       PLUS => nothing */
    0,  /*      MINUS => nothing */
    0,  /*       STAR => nothing */
    0,  /*      SLASH => nothing */
    0,  /*        REM => nothing */
    0,  /*     CONCAT => nothing */
    0,  /*     UMINUS => nothing */
    0,  /*      UPLUS => nothing */
    0,  /*     BITNOT => nothing */
    0,  /*     STRING => nothing */
    0,  /*    JOIN_KW => nothing */
    0,  /* CONSTRAINT => nothing */
    0,  /*   AUTOINCR => nothing */
    0,  /*       NULL => nothing */
    0,  /*    PRIMARY => nothing */
    0,  /*     UNIQUE => nothing */
    0,  /*      CHECK => nothing */
    0,  /* REFERENCES => nothing */
    0,  /*         ON => nothing */
    0,  /*     DELETE => nothing */
    0,  /*     UPDATE => nothing */
    0,  /*     INSERT => nothing */
    0,  /* DEFERRABLE => nothing */
    0,  /*    FOREIGN => nothing */
    0,  /*       DROP => nothing */
    0,  /*      UNION => nothing */
    0,  /*        ALL => nothing */
    0,  /*     EXCEPT => nothing */
    0,  /*  INTERSECT => nothing */
    0,  /*     SELECT => nothing */
    0,  /*   DISTINCT => nothing */
    0,  /*        DOT => nothing */
    0,  /*       FROM => nothing */
    0,  /*       JOIN => nothing */
    0,  /*      USING => nothing */
    0,  /*      ORDER => nothing */
    0,  /*         BY => nothing */
    0,  /*      GROUP => nothing */
    0,  /*     HAVING => nothing */
    0,  /*      LIMIT => nothing */
    0,  /*      WHERE => nothing */
    0,  /*       INTO => nothing */
    0,  /*     VALUES => nothing */
    0,  /*    INTEGER => nothing */
    0,  /*      FLOAT => nothing */
    0,  /*       BLOB => nothing */
    0,  /*   REGISTER => nothing */
    0,  /*   VARIABLE => nothing */
    0,  /*  VARIABLE1 => nothing */
    0,  /*       CASE => nothing */
    0,  /*       WHEN => nothing */
    0,  /*       THEN => nothing */
    0,  /*       ELSE => nothing */
    0,  /*      NAMES => nothing */
    0,  /*  CHARACTER => nothing */
    0,  /*     GLOBAL => nothing */
    0,  /*      LOCAL => nothing */
    0,  /*    SESSION => nothing */
    0,  /*       SHOW => nothing */
    0,  /*  DATABASES => nothing */
    0,  /*    SCHEMAS => nothing */
    0,  /*     TABLES => nothing */
};
#endif /* YYFALLBACK */

/* The following structure represents a single element of the
** parser's stack.  Information stored includes:
**
**   +  The state number for the parser at this level of the stack.
**
**   +  The value of the token stored at this level of the stack.
**      (In other words, the "major" token.)
**
**   +  The semantic value stored at this level of the stack.  This is
**      the information used by the action routines in the grammar.
**      It is sometimes called the "minor" token.
*/
struct yyStackEntry {
  int stateno;       /* The state-number */
  int major;         /* The major token value.  This is the code
                     ** number for the token at this stack level */
  YYMINORTYPE minor; /* The user-supplied minor token value.  This
                     ** is the value of the token  */
};
typedef struct yyStackEntry yyStackEntry;

/* The state of the parser is completely contained in an instance of
** the following structure */
struct yyParser {
  int yyidx;                    /* Index of top element in stack */
  int yyerrcnt;                 /* Shifts left before out of the error */
  sqlite3ParserARG_SDECL                /* A place to hold %extra_argument */
  yyStackEntry yystack[YYSTACKDEPTH];  /* The parser's stack */
};
typedef struct yyParser yyParser;

#ifndef NDEBUG
#include <stdio.h>
static FILE *yyTraceFILE = 0;
static char *yyTracePrompt = 0;
#endif /* NDEBUG */

#ifndef NDEBUG
/* 
** Turn parser tracing on by giving a stream to which to write the trace
** and a prompt to preface each trace message.  Tracing is turned off
** by making either argument NULL 
**
** Inputs:
** <ul>
** <li> A FILE* to which trace output should be written.
**      If NULL, then tracing is turned off.
** <li> A prefix string written at the beginning of every
**      line of trace output.  If NULL, then tracing is
**      turned off.
** </ul>
**
** Outputs:
** None.
*/
void sqlite3ParserTrace(FILE *TraceFILE, char *zTracePrompt){
  yyTraceFILE = TraceFILE;
  yyTracePrompt = zTracePrompt;
  if( yyTraceFILE==0 ) yyTracePrompt = 0;
  else if( yyTracePrompt==0 ) yyTraceFILE = 0;
}
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing shifts, the names of all terminals and nonterminals
** are required.  The following table supplies these names */
static const char *const yyTokenName[] = { 
  "$",             "SEMI",          "EXPLAIN",       "QUERY",       
  "PLAN",          "BEGIN",         "START",         "TRANSACTION", 
  "WORK",          "COMMIT",        "ROLLBACK",      "CREATE",      
  "TABLE",         "IF",            "NOT",           "EXISTS",      
  "TEMP",          "LP",            "RP",            "AS",          
  "COMMA",         "ID",            "EQ",            "DEFAULT",     
  "CHARSET",       "SET",           "COLLATE",       "ABORT",       
  "AFTER",         "ANALYZE",       "ASC",           "ATTACH",      
  "BEFORE",        "CASCADE",       "CAST",          "CONFLICT",    
  "DATABASE",      "DEFERRED",      "DESC",          "DETACH",      
  "EACH",          "END",           "EXCLUSIVE",     "FAIL",        
  "FOR",           "IGNORE",        "IMMEDIATE",     "INITIALLY",   
  "INSTEAD",       "LIKE_KW",       "MATCH",         "KEY",         
  "OF",            "OFFSET",        "PRAGMA",        "RAISE",       
  "REPLACE",       "RESTRICT",      "ROW",           "STATEMENT",   
  "TRIGGER",       "VACUUM",        "VIEW",          "REINDEX",     
  "RENAME",        "CTIME_KW",      "OR",            "AND",         
  "IS",            "BETWEEN",       "IN",            "ISNULL",      
  "NOTNULL",       "NE",            "GT",            "LE",          
  "LT",            "GE",            "ESCAPE",        "BITAND",      
  "BITOR",         "LSHIFT",        "RSHIFT",        "PLUS",        
  "MINUS",         "STAR",          "SLASH",         "REM",         
  "CONCAT",        "UMINUS",        "UPLUS",         "BITNOT",      
  "STRING",        "JOIN_KW",       "CONSTRAINT",    "AUTOINCR",    
  "NULL",          "PRIMARY",       "UNIQUE",        "CHECK",       
  "REFERENCES",    "ON",            "DELETE",        "UPDATE",      
  "INSERT",        "DEFERRABLE",    "FOREIGN",       "DROP",        
  "UNION",         "ALL",           "EXCEPT",        "INTERSECT",   
  "SELECT",        "DISTINCT",      "DOT",           "FROM",        
  "JOIN",          "USING",         "ORDER",         "BY",          
  "GROUP",         "HAVING",        "LIMIT",         "WHERE",       
  "INTO",          "VALUES",        "INTEGER",       "FLOAT",       
  "BLOB",          "REGISTER",      "VARIABLE",      "VARIABLE1",   
  "CASE",          "WHEN",          "THEN",          "ELSE",        
  "NAMES",         "CHARACTER",     "GLOBAL",        "LOCAL",       
  "SESSION",       "SHOW",          "DATABASES",     "SCHEMAS",     
  "TABLES",        "error",         "input",         "cmdlist",     
  "ecmd",          "cmdx",          "cmd",           "explain",     
  "trans_opt",     "create_table",  "create_table_args",  "temp",        
  "ifnotexists",   "nm",            "dbnm",          "columnlist",  
  "conslist_opt",  "table_opt",     "select",        "column",      
  "eq_or_null",    "columnid",      "type",          "carglist",    
  "id",            "ids",           "typetoken",     "typename",    
  "signed",        "plus_num",      "minus_num",     "carg",        
  "ccons",         "term",          "expr",          "onconf",      
  "sortorder",     "idxlist_opt",   "refargs",       "defer_subclause",
  "autoinc",       "refarg",        "refact",        "init_deferred_pred_opt",
  "conslist",      "tcons",         "idxlist",       "defer_subclause_opt",
  "orconf",        "resolvetype",   "raisetype",     "ifexists",    
  "fullname",      "oneselect",     "multiselect_op",  "distinct",    
  "selcollist",    "from",          "where_opt",     "groupby_opt", 
  "having_opt",    "orderby_opt",   "limit_opt",     "sclp",        
  "as",            "seltablist",    "stl_prefix",    "joinop",      
  "on_opt",        "using_opt",     "seltablist_paren",  "joinop2",     
  "inscollist",    "sortlist",      "sortitem",      "collate",     
  "exprlist",      "setlist",       "insert_cmd",    "inscollist_opt",
  "valueslist",    "itemlist",      "likeop",        "escape",      
  "between_op",    "between_elem",  "in_op",         "case_operand",
  "case_exprlist",  "case_else",     "expritem",      "idxitem",     
  "plus_opt",      "number",        "variable_assignment_list",  "scope_qualifier",
  "user_var_name",  "show_databes",  "show_tables",   "full_keyword",
  "from_db",     
};
#endif /* NDEBUG */

#ifndef NDEBUG
/* For tracing reduce actions, the names of all rules are required.
*/
static const char *const yyRuleName[] = {
 /*   0 */ "input ::= cmdlist",
 /*   1 */ "cmdlist ::= cmdlist ecmd",
 /*   2 */ "cmdlist ::= ecmd",
 /*   3 */ "cmdx ::= cmd",
 /*   4 */ "ecmd ::= SEMI",
 /*   5 */ "ecmd ::= explain cmdx SEMI",
 /*   6 */ "explain ::=",
 /*   7 */ "explain ::= EXPLAIN",
 /*   8 */ "explain ::= EXPLAIN QUERY PLAN",
 /*   9 */ "cmd ::= BEGIN trans_opt",
 /*  10 */ "cmd ::= START TRANSACTION",
 /*  11 */ "trans_opt ::=",
 /*  12 */ "trans_opt ::= WORK",
 /*  13 */ "cmd ::= COMMIT trans_opt",
 /*  14 */ "cmd ::= ROLLBACK trans_opt",
 /*  15 */ "cmd ::= create_table create_table_args",
 /*  16 */ "create_table ::= CREATE temp TABLE ifnotexists nm dbnm",
 /*  17 */ "ifnotexists ::=",
 /*  18 */ "ifnotexists ::= IF NOT EXISTS",
 /*  19 */ "temp ::= TEMP",
 /*  20 */ "temp ::=",
 /*  21 */ "create_table_args ::= LP columnlist conslist_opt RP table_opt",
 /*  22 */ "create_table_args ::= AS select",
 /*  23 */ "columnlist ::= columnlist COMMA column",
 /*  24 */ "columnlist ::= column",
 /*  25 */ "table_opt ::=",
 /*  26 */ "table_opt ::= table_opt ID",
 /*  27 */ "table_opt ::= table_opt ID EQ ID",
 /*  28 */ "table_opt ::= table_opt DEFAULT CHARSET SET eq_or_null ID",
 /*  29 */ "table_opt ::= table_opt DEFAULT COLLATE eq_or_null ID",
 /*  30 */ "eq_or_null ::=",
 /*  31 */ "eq_or_null ::= EQ",
 /*  32 */ "column ::= columnid type carglist",
 /*  33 */ "columnid ::= nm",
 /*  34 */ "id ::= ID",
 /*  35 */ "ids ::= ID|STRING",
 /*  36 */ "nm ::= ID",
 /*  37 */ "nm ::= STRING",
 /*  38 */ "nm ::= JOIN_KW",
 /*  39 */ "type ::=",
 /*  40 */ "type ::= typetoken",
 /*  41 */ "typetoken ::= typename",
 /*  42 */ "typetoken ::= typename LP signed RP",
 /*  43 */ "typetoken ::= typename LP signed COMMA signed RP",
 /*  44 */ "typename ::= ids",
 /*  45 */ "typename ::= typename ids",
 /*  46 */ "signed ::= plus_num",
 /*  47 */ "signed ::= minus_num",
 /*  48 */ "carglist ::= carglist carg",
 /*  49 */ "carglist ::=",
 /*  50 */ "carg ::= CONSTRAINT nm ccons",
 /*  51 */ "carg ::= ccons",
 /*  52 */ "carg ::= DEFAULT term",
 /*  53 */ "carg ::= DEFAULT LP expr RP",
 /*  54 */ "carg ::= DEFAULT PLUS term",
 /*  55 */ "carg ::= DEFAULT MINUS term",
 /*  56 */ "carg ::= DEFAULT id",
 /*  57 */ "ccons ::= AUTOINCR",
 /*  58 */ "ccons ::= NULL onconf",
 /*  59 */ "ccons ::= NOT NULL onconf",
 /*  60 */ "ccons ::= PRIMARY KEY sortorder onconf",
 /*  61 */ "ccons ::= UNIQUE onconf",
 /*  62 */ "ccons ::= CHECK LP expr RP",
 /*  63 */ "ccons ::= REFERENCES nm idxlist_opt refargs",
 /*  64 */ "ccons ::= defer_subclause",
 /*  65 */ "ccons ::= COLLATE id",
 /*  66 */ "autoinc ::=",
 /*  67 */ "autoinc ::= AUTOINCR",
 /*  68 */ "refargs ::=",
 /*  69 */ "refargs ::= refargs refarg",
 /*  70 */ "refarg ::= MATCH nm",
 /*  71 */ "refarg ::= ON DELETE refact",
 /*  72 */ "refarg ::= ON UPDATE refact",
 /*  73 */ "refarg ::= ON INSERT refact",
 /*  74 */ "refact ::= SET NULL",
 /*  75 */ "refact ::= SET DEFAULT",
 /*  76 */ "refact ::= CASCADE",
 /*  77 */ "refact ::= RESTRICT",
 /*  78 */ "defer_subclause ::= NOT DEFERRABLE init_deferred_pred_opt",
 /*  79 */ "defer_subclause ::= DEFERRABLE init_deferred_pred_opt",
 /*  80 */ "init_deferred_pred_opt ::=",
 /*  81 */ "init_deferred_pred_opt ::= INITIALLY DEFERRED",
 /*  82 */ "init_deferred_pred_opt ::= INITIALLY IMMEDIATE",
 /*  83 */ "conslist_opt ::=",
 /*  84 */ "conslist_opt ::= COMMA conslist",
 /*  85 */ "conslist ::= conslist COMMA tcons",
 /*  86 */ "conslist ::= conslist tcons",
 /*  87 */ "conslist ::= tcons",
 /*  88 */ "tcons ::= CONSTRAINT nm",
 /*  89 */ "tcons ::= PRIMARY KEY LP idxlist autoinc RP onconf",
 /*  90 */ "tcons ::= UNIQUE LP idxlist RP onconf",
 /*  91 */ "tcons ::= CHECK LP expr RP onconf",
 /*  92 */ "tcons ::= FOREIGN KEY LP idxlist RP REFERENCES nm idxlist_opt refargs defer_subclause_opt",
 /*  93 */ "defer_subclause_opt ::=",
 /*  94 */ "defer_subclause_opt ::= defer_subclause",
 /*  95 */ "onconf ::=",
 /*  96 */ "onconf ::= ON CONFLICT resolvetype",
 /*  97 */ "resolvetype ::= raisetype",
 /*  98 */ "resolvetype ::= IGNORE",
 /*  99 */ "resolvetype ::= REPLACE",
 /* 100 */ "cmd ::= DROP TABLE ifexists fullname",
 /* 101 */ "ifexists ::= IF EXISTS",
 /* 102 */ "ifexists ::=",
 /* 103 */ "cmd ::= select",
 /* 104 */ "select ::= oneselect",
 /* 105 */ "select ::= select multiselect_op oneselect",
 /* 106 */ "multiselect_op ::= UNION",
 /* 107 */ "multiselect_op ::= UNION ALL",
 /* 108 */ "multiselect_op ::= EXCEPT|INTERSECT",
 /* 109 */ "oneselect ::= SELECT distinct selcollist from where_opt groupby_opt having_opt orderby_opt limit_opt",
 /* 110 */ "distinct ::= DISTINCT",
 /* 111 */ "distinct ::= ALL",
 /* 112 */ "distinct ::=",
 /* 113 */ "sclp ::= selcollist COMMA",
 /* 114 */ "sclp ::=",
 /* 115 */ "selcollist ::= sclp expr as",
 /* 116 */ "selcollist ::= sclp STAR",
 /* 117 */ "selcollist ::= sclp nm DOT STAR",
 /* 118 */ "as ::= AS nm",
 /* 119 */ "as ::= ids",
 /* 120 */ "as ::=",
 /* 121 */ "from ::=",
 /* 122 */ "from ::= FROM seltablist",
 /* 123 */ "stl_prefix ::= seltablist joinop",
 /* 124 */ "stl_prefix ::=",
 /* 125 */ "seltablist ::= stl_prefix nm dbnm as on_opt using_opt",
 /* 126 */ "seltablist ::= stl_prefix LP seltablist_paren RP as on_opt using_opt",
 /* 127 */ "seltablist_paren ::= select",
 /* 128 */ "seltablist_paren ::= seltablist",
 /* 129 */ "dbnm ::=",
 /* 130 */ "dbnm ::= DOT nm",
 /* 131 */ "fullname ::= nm dbnm",
 /* 132 */ "joinop ::= COMMA|JOIN",
 /* 133 */ "joinop ::= JOIN_KW JOIN",
 /* 134 */ "joinop ::= JOIN_KW nm JOIN",
 /* 135 */ "joinop ::= JOIN_KW nm nm JOIN",
 /* 136 */ "on_opt ::= ON expr",
 /* 137 */ "on_opt ::=",
 /* 138 */ "using_opt ::= USING LP inscollist RP",
 /* 139 */ "using_opt ::=",
 /* 140 */ "orderby_opt ::=",
 /* 141 */ "orderby_opt ::= ORDER BY sortlist",
 /* 142 */ "sortlist ::= sortlist COMMA sortitem collate sortorder",
 /* 143 */ "sortlist ::= sortitem collate sortorder",
 /* 144 */ "sortitem ::= expr",
 /* 145 */ "sortorder ::= ASC",
 /* 146 */ "sortorder ::= DESC",
 /* 147 */ "sortorder ::=",
 /* 148 */ "collate ::=",
 /* 149 */ "collate ::= COLLATE id",
 /* 150 */ "groupby_opt ::=",
 /* 151 */ "groupby_opt ::= GROUP BY exprlist",
 /* 152 */ "having_opt ::=",
 /* 153 */ "having_opt ::= HAVING expr",
 /* 154 */ "limit_opt ::=",
 /* 155 */ "limit_opt ::= LIMIT expr",
 /* 156 */ "limit_opt ::= LIMIT expr OFFSET expr",
 /* 157 */ "limit_opt ::= LIMIT expr COMMA expr",
 /* 158 */ "cmd ::= DELETE FROM fullname where_opt limit_opt",
 /* 159 */ "where_opt ::=",
 /* 160 */ "where_opt ::= WHERE expr",
 /* 161 */ "cmd ::= UPDATE fullname SET setlist where_opt limit_opt",
 /* 162 */ "setlist ::= setlist COMMA nm EQ expr",
 /* 163 */ "setlist ::= nm EQ expr",
 /* 164 */ "cmd ::= insert_cmd INTO fullname inscollist_opt VALUES valueslist",
 /* 165 */ "cmd ::= insert_cmd INTO fullname inscollist_opt SET setlist",
 /* 166 */ "cmd ::= insert_cmd fullname inscollist_opt SET setlist",
 /* 167 */ "cmd ::= insert_cmd INTO fullname inscollist_opt select",
 /* 168 */ "insert_cmd ::= INSERT",
 /* 169 */ "insert_cmd ::= REPLACE",
 /* 170 */ "valueslist ::= valueslist COMMA LP itemlist RP",
 /* 171 */ "valueslist ::= LP itemlist RP",
 /* 172 */ "itemlist ::= itemlist COMMA expr",
 /* 173 */ "itemlist ::= expr",
 /* 174 */ "inscollist_opt ::=",
 /* 175 */ "inscollist_opt ::= LP inscollist RP",
 /* 176 */ "inscollist ::= inscollist COMMA nm",
 /* 177 */ "inscollist ::= nm",
 /* 178 */ "expr ::= term",
 /* 179 */ "expr ::= LP expr RP",
 /* 180 */ "term ::= NULL",
 /* 181 */ "expr ::= ID",
 /* 182 */ "expr ::= JOIN_KW",
 /* 183 */ "expr ::= nm DOT nm",
 /* 184 */ "expr ::= nm DOT nm DOT nm",
 /* 185 */ "term ::= INTEGER|FLOAT|BLOB",
 /* 186 */ "term ::= STRING",
 /* 187 */ "expr ::= REGISTER",
 /* 188 */ "expr ::= VARIABLE",
 /* 189 */ "expr ::= VARIABLE1",
 /* 190 */ "expr ::= CAST LP expr AS typetoken RP",
 /* 191 */ "expr ::= ID LP distinct exprlist RP",
 /* 192 */ "expr ::= ID LP STAR RP",
 /* 193 */ "term ::= CTIME_KW",
 /* 194 */ "expr ::= expr AND expr",
 /* 195 */ "expr ::= expr OR expr",
 /* 196 */ "expr ::= expr LT|GT|GE|LE expr",
 /* 197 */ "expr ::= expr EQ|NE expr",
 /* 198 */ "expr ::= expr BITAND|BITOR|LSHIFT|RSHIFT expr",
 /* 199 */ "expr ::= expr PLUS|MINUS expr",
 /* 200 */ "expr ::= expr STAR|SLASH|REM expr",
 /* 201 */ "expr ::= expr CONCAT expr",
 /* 202 */ "likeop ::= LIKE_KW",
 /* 203 */ "likeop ::= NOT LIKE_KW",
 /* 204 */ "escape ::= ESCAPE expr",
 /* 205 */ "escape ::=",
 /* 206 */ "expr ::= expr likeop expr escape",
 /* 207 */ "expr ::= expr ISNULL|NOTNULL",
 /* 208 */ "expr ::= expr IS NULL",
 /* 209 */ "expr ::= expr NOT NULL",
 /* 210 */ "expr ::= expr IS NOT NULL",
 /* 211 */ "expr ::= NOT|BITNOT expr",
 /* 212 */ "expr ::= MINUS expr",
 /* 213 */ "expr ::= PLUS expr",
 /* 214 */ "between_op ::= BETWEEN",
 /* 215 */ "between_op ::= NOT BETWEEN",
 /* 216 */ "between_elem ::= INTEGER|STRING",
 /* 217 */ "expr ::= expr between_op between_elem AND between_elem",
 /* 218 */ "in_op ::= IN",
 /* 219 */ "in_op ::= NOT IN",
 /* 220 */ "expr ::= expr in_op LP exprlist RP",
 /* 221 */ "expr ::= LP select RP",
 /* 222 */ "expr ::= expr in_op LP select RP",
 /* 223 */ "expr ::= expr in_op nm dbnm",
 /* 224 */ "expr ::= EXISTS LP select RP",
 /* 225 */ "expr ::= CASE case_operand case_exprlist case_else END",
 /* 226 */ "case_exprlist ::= case_exprlist WHEN expr THEN expr",
 /* 227 */ "case_exprlist ::= WHEN expr THEN expr",
 /* 228 */ "case_else ::= ELSE expr",
 /* 229 */ "case_else ::=",
 /* 230 */ "case_operand ::= expr",
 /* 231 */ "case_operand ::=",
 /* 232 */ "exprlist ::= exprlist COMMA expritem",
 /* 233 */ "exprlist ::= expritem",
 /* 234 */ "expritem ::= expr",
 /* 235 */ "expritem ::=",
 /* 236 */ "idxlist_opt ::=",
 /* 237 */ "idxlist_opt ::= LP idxlist RP",
 /* 238 */ "idxlist ::= idxlist COMMA idxitem collate sortorder",
 /* 239 */ "idxlist ::= idxitem collate sortorder",
 /* 240 */ "idxitem ::= nm",
 /* 241 */ "plus_num ::= plus_opt number",
 /* 242 */ "minus_num ::= MINUS number",
 /* 243 */ "number ::= INTEGER|FLOAT",
 /* 244 */ "plus_opt ::= PLUS",
 /* 245 */ "plus_opt ::=",
 /* 246 */ "raisetype ::= ROLLBACK",
 /* 247 */ "raisetype ::= ABORT",
 /* 248 */ "raisetype ::= FAIL",
 /* 249 */ "cmd ::= SET variable_assignment_list",
 /* 250 */ "cmd ::= SET NAMES ids",
 /* 251 */ "cmd ::= SET CHARACTER SET ids",
 /* 252 */ "variable_assignment_list ::= variable_assignment_list COMMA scope_qualifier user_var_name EQ expr",
 /* 253 */ "variable_assignment_list ::= scope_qualifier user_var_name EQ expr",
 /* 254 */ "scope_qualifier ::= GLOBAL",
 /* 255 */ "scope_qualifier ::= LOCAL",
 /* 256 */ "scope_qualifier ::= SESSION",
 /* 257 */ "scope_qualifier ::= VARIABLE1 DOT",
 /* 258 */ "scope_qualifier ::=",
 /* 259 */ "user_var_name ::= ids",
 /* 260 */ "user_var_name ::= VARIABLE",
 /* 261 */ "cmd ::= show_databes",
 /* 262 */ "cmd ::= show_tables",
 /* 263 */ "show_databes ::= SHOW DATABASES|SCHEMAS",
 /* 264 */ "show_tables ::= SHOW full_keyword TABLES from_db",
 /* 265 */ "full_keyword ::= JOIN_KW",
 /* 266 */ "full_keyword ::=",
 /* 267 */ "from_db ::=",
 /* 268 */ "from_db ::= FROM|IN nm",
};
#endif /* NDEBUG */

/*
** This function returns the symbolic name associated with a token
** value.
*/
const char *sqlite3ParserTokenName(int tokenType){
#ifndef NDEBUG
  if( tokenType>0 && tokenType<(sizeof(yyTokenName)/sizeof(yyTokenName[0])) ){
    return yyTokenName[tokenType];
  }else{
    return "Unknown";
  }
#else
  return "";
#endif
}

/* 
** This function allocates a new parser.
** The only argument is a pointer to a function which works like
** malloc.
**
** Inputs:
** A pointer to the function used to allocate memory.
**
** Outputs:
** A pointer to a parser.  This pointer is used in subsequent calls
** to sqlite3Parser and sqlite3ParserFree.
*/
void *sqlite3ParserAlloc(void *(*mallocProc)(size_t)){
  yyParser *pParser;
  pParser = (yyParser*)(*mallocProc)( (size_t)sizeof(yyParser) );
  if( pParser ){
    pParser->yyidx = -1;
  }
  return pParser;
}

/* The following function deletes the value associated with a
** symbol.  The symbol can be either a terminal or nonterminal.
** "yymajor" is the symbol code, and "yypminor" is a pointer to
** the value.
*/
static void yy_destructor(YYCODETYPE yymajor, YYMINORTYPE *yypminor){
  switch( yymajor ){
    /* Here is inserted the actions which take place when a
    ** terminal or non-terminal is destroyed.  This can happen
    ** when the symbol is popped from the stack during a
    ** reduce or during error processing or when a parser is 
    ** being destroyed before it is finished parsing.
    **
    ** Note: during a reduce, the only symbols destroyed are those
    ** which appear on the RHS of the rule, but which are not used
    ** inside the C code.
    */
    case 162:
    case 197:
    case 214:
#line 390 "parse.y"
{sqlite3SelectDelete((yypminor->yy149));}
#line 1147 "parse.c"
      break;
    case 177:
    case 178:
    case 202:
    case 204:
    case 212:
    case 218:
    case 227:
    case 229:
    case 231:
    case 233:
    case 234:
#line 666 "parse.y"
{sqlite3ExprDelete((yypminor->yy342));}
#line 1162 "parse.c"
      break;
    case 181:
    case 190:
    case 200:
    case 203:
    case 205:
    case 207:
    case 217:
    case 220:
    case 221:
    case 225:
    case 232:
#line 910 "parse.y"
{sqlite3ExprListDelete((yypminor->yy462));}
#line 1177 "parse.c"
      break;
    case 196:
    case 201:
    case 209:
    case 210:
#line 518 "parse.y"
{sqlite3SrcListDelete((yypminor->yy287));}
#line 1185 "parse.c"
      break;
    case 206:
#line 579 "parse.y"
{
  sqlite3ExprDelete((yypminor->yy474).pLimit);
  sqlite3ExprDelete((yypminor->yy474).pOffset);
}
#line 1193 "parse.c"
      break;
    case 213:
    case 216:
    case 223:
#line 535 "parse.y"
{sqlite3IdListDelete((yypminor->yy440));}
#line 1200 "parse.c"
      break;
    case 224:
#line 639 "parse.y"
{sqlite3ValuesListDelete((yypminor->yy49));}
#line 1205 "parse.c"
      break;
    case 238:
#line 1126 "parse.y"
{ sqlite3ExprListDelete((yypminor->yy462)); }
#line 1210 "parse.c"
      break;
    default:  break;   /* If no destructor action specified: do nothing */
  }
}

/*
** Pop the parser's stack once.
**
** If there is a destructor routine associated with the token which
** is popped from the stack, then call it.
**
** Return the major token number for the symbol popped.
*/
static int yy_pop_parser_stack(yyParser *pParser){
  YYCODETYPE yymajor;
  yyStackEntry *yytos = &pParser->yystack[pParser->yyidx];

  if( pParser->yyidx<0 ) return 0;
#ifndef NDEBUG
  if( yyTraceFILE && pParser->yyidx>=0 ){
    fprintf(yyTraceFILE,"%sPopping %s\n",
      yyTracePrompt,
      yyTokenName[yytos->major]);
  }
#endif
  yymajor = yytos->major;
  yy_destructor( yymajor, &yytos->minor);
  pParser->yyidx--;
  return yymajor;
}

/* 
** Deallocate and destroy a parser.  Destructors are all called for
** all stack elements before shutting the parser down.
**
** Inputs:
** <ul>
** <li>  A pointer to the parser.  This should be a pointer
**       obtained from sqlite3ParserAlloc.
** <li>  A pointer to a function used to reclaim memory obtained
**       from malloc.
** </ul>
*/
void sqlite3ParserFree(
  void *p,                    /* The parser to be deleted */
  void (*freeProc)(void*)     /* Function used to reclaim memory */
){
  yyParser *pParser = (yyParser*)p;
  if( pParser==0 ) return;
  while( pParser->yyidx>=0 ) yy_pop_parser_stack(pParser);
  (*freeProc)((void*)pParser);
}

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(
  yyParser *pParser,        /* The parser */
  int iLookAhead            /* The look-ahead token */
){
  int i;
  int stateno = pParser->yystack[pParser->yyidx].stateno;
 
  if( stateno>YY_SHIFT_MAX || (i = yy_shift_ofst[stateno])==YY_SHIFT_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
#ifdef YYFALLBACK
    int iFallback;            /* Fallback token */
    if( iLookAhead<sizeof(yyFallback)/sizeof(yyFallback[0])
           && (iFallback = yyFallback[iLookAhead])!=0 ){
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE, "%sFALLBACK %s => %s\n",
           yyTracePrompt, yyTokenName[iLookAhead], yyTokenName[iFallback]);
      }
#endif
      return yy_find_shift_action(pParser, iFallback);
    }
#endif
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Find the appropriate action for a parser given the non-terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_reduce_action(
  int stateno,              /* Current state number */
  int iLookAhead            /* The look-ahead token */
){
  int i;
  /* int stateno = pParser->yystack[pParser->yyidx].stateno; */
 
  if( stateno>YY_REDUCE_MAX ||
      (i = yy_reduce_ofst[stateno])==YY_REDUCE_USE_DFLT ){
    return yy_default[stateno];
  }
  if( iLookAhead==YYNOCODE ){
    return YY_NO_ACTION;
  }
  i += iLookAhead;
  if( i<0 || i>=YY_SZ_ACTTAB || yy_lookahead[i]!=iLookAhead ){
    return yy_default[stateno];
  }else{
    return yy_action[i];
  }
}

/*
** Perform a shift action.
*/
static void yy_shift(
  yyParser *yypParser,          /* The parser to be shifted */
  int yyNewState,               /* The new state to shift in */
  int yyMajor,                  /* The major token to shift in */
  YYMINORTYPE *yypMinor         /* Pointer ot the minor token to shift in */
){
  yyStackEntry *yytos;
  yypParser->yyidx++;
  if( yypParser->yyidx>=YYSTACKDEPTH ){
     sqlite3ParserARG_FETCH;
     yypParser->yyidx--;
#ifndef NDEBUG
     if( yyTraceFILE ){
       fprintf(yyTraceFILE,"%sStack Overflow!\n",yyTracePrompt);
     }
#endif
     while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
     /* Here code is inserted which will execute if the parser
     ** stack every overflows */
#line 43 "parse.y"

  sqlite3ErrorMsg(pParse, "parser stack overflow");
#line 1362 "parse.c"
     sqlite3ParserARG_STORE; /* Suppress warning about unused %extra_argument var */
     return;
  }
  yytos = &yypParser->yystack[yypParser->yyidx];
  yytos->stateno = yyNewState;
  yytos->major = yyMajor;
  yytos->minor = *yypMinor;
#ifndef NDEBUG
  if( yyTraceFILE && yypParser->yyidx>0 ){
    int i;
    fprintf(yyTraceFILE,"%sShift %d\n",yyTracePrompt,yyNewState);
    fprintf(yyTraceFILE,"%sStack:",yyTracePrompt);
    for(i=1; i<=yypParser->yyidx; i++)
      fprintf(yyTraceFILE," %s",yyTokenName[yypParser->yystack[i].major]);
    fprintf(yyTraceFILE,"\n");
  }
#endif
}

/* The following table contains information about every rule that
** is used during the reduce.
*/
static const struct {
  YYCODETYPE lhs;         /* Symbol on the left-hand side of the rule */
  unsigned char nrhs;     /* Number of right-hand side symbols in the rule */
} yyRuleInfo[] = {
  { 146, 1 },
  { 147, 2 },
  { 147, 1 },
  { 149, 1 },
  { 148, 1 },
  { 148, 3 },
  { 151, 0 },
  { 151, 1 },
  { 151, 3 },
  { 150, 2 },
  { 150, 2 },
  { 152, 0 },
  { 152, 1 },
  { 150, 2 },
  { 150, 2 },
  { 150, 2 },
  { 153, 6 },
  { 156, 0 },
  { 156, 3 },
  { 155, 1 },
  { 155, 0 },
  { 154, 5 },
  { 154, 2 },
  { 159, 3 },
  { 159, 1 },
  { 161, 0 },
  { 161, 2 },
  { 161, 4 },
  { 161, 6 },
  { 161, 5 },
  { 164, 0 },
  { 164, 1 },
  { 163, 3 },
  { 165, 1 },
  { 168, 1 },
  { 169, 1 },
  { 157, 1 },
  { 157, 1 },
  { 157, 1 },
  { 166, 0 },
  { 166, 1 },
  { 170, 1 },
  { 170, 4 },
  { 170, 6 },
  { 171, 1 },
  { 171, 2 },
  { 172, 1 },
  { 172, 1 },
  { 167, 2 },
  { 167, 0 },
  { 175, 3 },
  { 175, 1 },
  { 175, 2 },
  { 175, 4 },
  { 175, 3 },
  { 175, 3 },
  { 175, 2 },
  { 176, 1 },
  { 176, 2 },
  { 176, 3 },
  { 176, 4 },
  { 176, 2 },
  { 176, 4 },
  { 176, 4 },
  { 176, 1 },
  { 176, 2 },
  { 184, 0 },
  { 184, 1 },
  { 182, 0 },
  { 182, 2 },
  { 185, 2 },
  { 185, 3 },
  { 185, 3 },
  { 185, 3 },
  { 186, 2 },
  { 186, 2 },
  { 186, 1 },
  { 186, 1 },
  { 183, 3 },
  { 183, 2 },
  { 187, 0 },
  { 187, 2 },
  { 187, 2 },
  { 160, 0 },
  { 160, 2 },
  { 188, 3 },
  { 188, 2 },
  { 188, 1 },
  { 189, 2 },
  { 189, 7 },
  { 189, 5 },
  { 189, 5 },
  { 189, 10 },
  { 191, 0 },
  { 191, 1 },
  { 179, 0 },
  { 179, 3 },
  { 193, 1 },
  { 193, 1 },
  { 193, 1 },
  { 150, 4 },
  { 195, 2 },
  { 195, 0 },
  { 150, 1 },
  { 162, 1 },
  { 162, 3 },
  { 198, 1 },
  { 198, 2 },
  { 198, 1 },
  { 197, 9 },
  { 199, 1 },
  { 199, 1 },
  { 199, 0 },
  { 207, 2 },
  { 207, 0 },
  { 200, 3 },
  { 200, 2 },
  { 200, 4 },
  { 208, 2 },
  { 208, 1 },
  { 208, 0 },
  { 201, 0 },
  { 201, 2 },
  { 210, 2 },
  { 210, 0 },
  { 209, 6 },
  { 209, 7 },
  { 214, 1 },
  { 214, 1 },
  { 158, 0 },
  { 158, 2 },
  { 196, 2 },
  { 211, 1 },
  { 211, 2 },
  { 211, 3 },
  { 211, 4 },
  { 212, 2 },
  { 212, 0 },
  { 213, 4 },
  { 213, 0 },
  { 205, 0 },
  { 205, 3 },
  { 217, 5 },
  { 217, 3 },
  { 218, 1 },
  { 180, 1 },
  { 180, 1 },
  { 180, 0 },
  { 219, 0 },
  { 219, 2 },
  { 203, 0 },
  { 203, 3 },
  { 204, 0 },
  { 204, 2 },
  { 206, 0 },
  { 206, 2 },
  { 206, 4 },
  { 206, 4 },
  { 150, 5 },
  { 202, 0 },
  { 202, 2 },
  { 150, 6 },
  { 221, 5 },
  { 221, 3 },
  { 150, 6 },
  { 150, 6 },
  { 150, 5 },
  { 150, 5 },
  { 222, 1 },
  { 222, 1 },
  { 224, 5 },
  { 224, 3 },
  { 225, 3 },
  { 225, 1 },
  { 223, 0 },
  { 223, 3 },
  { 216, 3 },
  { 216, 1 },
  { 178, 1 },
  { 178, 3 },
  { 177, 1 },
  { 178, 1 },
  { 178, 1 },
  { 178, 3 },
  { 178, 5 },
  { 177, 1 },
  { 177, 1 },
  { 178, 1 },
  { 178, 1 },
  { 178, 1 },
  { 178, 6 },
  { 178, 5 },
  { 178, 4 },
  { 177, 1 },
  { 178, 3 },
  { 178, 3 },
  { 178, 3 },
  { 178, 3 },
  { 178, 3 },
  { 178, 3 },
  { 178, 3 },
  { 178, 3 },
  { 226, 1 },
  { 226, 2 },
  { 227, 2 },
  { 227, 0 },
  { 178, 4 },
  { 178, 2 },
  { 178, 3 },
  { 178, 3 },
  { 178, 4 },
  { 178, 2 },
  { 178, 2 },
  { 178, 2 },
  { 228, 1 },
  { 228, 2 },
  { 229, 1 },
  { 178, 5 },
  { 230, 1 },
  { 230, 2 },
  { 178, 5 },
  { 178, 3 },
  { 178, 5 },
  { 178, 4 },
  { 178, 4 },
  { 178, 5 },
  { 232, 5 },
  { 232, 4 },
  { 233, 2 },
  { 233, 0 },
  { 231, 1 },
  { 231, 0 },
  { 220, 3 },
  { 220, 1 },
  { 234, 1 },
  { 234, 0 },
  { 181, 0 },
  { 181, 3 },
  { 190, 5 },
  { 190, 3 },
  { 235, 1 },
  { 173, 2 },
  { 174, 2 },
  { 237, 1 },
  { 236, 1 },
  { 236, 0 },
  { 194, 1 },
  { 194, 1 },
  { 194, 1 },
  { 150, 2 },
  { 150, 3 },
  { 150, 4 },
  { 238, 6 },
  { 238, 4 },
  { 239, 1 },
  { 239, 1 },
  { 239, 1 },
  { 239, 2 },
  { 239, 0 },
  { 240, 1 },
  { 240, 1 },
  { 150, 1 },
  { 150, 1 },
  { 241, 2 },
  { 242, 4 },
  { 243, 1 },
  { 243, 0 },
  { 244, 0 },
  { 244, 2 },
};

static void yy_accept(yyParser*);  /* Forward Declaration */

/*
** Perform a reduce action and the shift that must immediately
** follow the reduce.
*/
static void yy_reduce(
  yyParser *yypParser,         /* The parser */
  int yyruleno                 /* Number of the rule by which to reduce */
){
  int yygoto;                     /* The next state */
  int yyact;                      /* The next action */
  YYMINORTYPE yygotominor;        /* The LHS of the rule reduced */
  yyStackEntry *yymsp;            /* The top of the parser's stack */
  int yysize;                     /* Amount to pop the stack */
  sqlite3ParserARG_FETCH;
  yymsp = &yypParser->yystack[yypParser->yyidx];
#ifndef NDEBUG
  if( yyTraceFILE && yyruleno>=0 
        && yyruleno<sizeof(yyRuleName)/sizeof(yyRuleName[0]) ){
    fprintf(yyTraceFILE, "%sReduce [%s].\n", yyTracePrompt,
      yyRuleName[yyruleno]);
  }
#endif /* NDEBUG */

#ifndef NDEBUG
  /* Silence complaints from purify about yygotominor being uninitialized
  ** in some cases when it is copied into the stack after the following
  ** switch.  yygotominor is uninitialized when a rule reduces that does
  ** not set the value of its left-hand side nonterminal.  Leaving the
  ** value of the nonterminal uninitialized is utterly harmless as long
  ** as the value is never used.  So really the only thing this code
  ** accomplishes is to quieten purify.  
  */
  memset(&yygotominor, 0, sizeof(yygotominor));
#endif

  switch( yyruleno ){
  /* Beginning here are the reduction cases.  A typical example
  ** follows:
  **   case 0:
  **  #line <lineno> <grammarfile>
  **     { ... }           // User supplied code
  **  #line <lineno> <thisfile>
  **     break;
  */
      case 3:
#line 98 "parse.y"
{ sqlite3FinishCoding(pParse); }
#line 1709 "parse.c"
        break;
      case 6:
#line 101 "parse.y"
{ sqlite3BeginParse(pParse, 0); }
#line 1714 "parse.c"
        break;
      case 7:
#line 103 "parse.y"
{ sqlite3BeginParse(pParse, 1); }
#line 1719 "parse.c"
        break;
      case 8:
#line 104 "parse.y"
{ sqlite3BeginParse(pParse, 2); }
#line 1724 "parse.c"
        break;
      case 9:
#line 111 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_BEGIN);}
#line 1729 "parse.c"
        break;
      case 10:
#line 112 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_START);}
#line 1734 "parse.c"
        break;
      case 13:
#line 123 "parse.y"
{sqlite3CommitTransaction(pParse);}
#line 1739 "parse.c"
        break;
      case 14:
#line 125 "parse.y"
{sqlite3RollbackTransaction(pParse);}
#line 1744 "parse.c"
        break;
      case 16:
#line 130 "parse.y"
{
   sqlite3StartTable(pParse, 0, 0, 0, 0, 0);
}
#line 1751 "parse.c"
        break;
      case 17:
      case 20:
      case 66:
      case 80:
      case 82:
      case 93:
      case 102:
      case 111:
      case 112:
      case 214:
      case 218:
#line 135 "parse.y"
{yygotominor.yy32 = 0;}
#line 1766 "parse.c"
        break;
      case 18:
      case 19:
      case 67:
      case 81:
      case 101:
      case 110:
      case 215:
      case 219:
#line 136 "parse.y"
{yygotominor.yy32 = 1;}
#line 1778 "parse.c"
        break;
      case 21:
#line 142 "parse.y"
{
  //sqlite3EndTable(pParse,&X,&Y,0);
}
#line 1785 "parse.c"
        break;
      case 22:
#line 145 "parse.y"
{
  sqlite3EndTable(pParse,0,0,0);
  //sqlite3SelectDelete(S);
  yy_destructor(162,&yymsp[0].minor);
}
#line 1794 "parse.c"
        break;
      case 32:
#line 167 "parse.y"
{
  //A.z = X.z;
  //A.n = (pParse->sLastToken.z-X.z) + pParse->sLastToken.n;
}
#line 1802 "parse.c"
        break;
      case 33:
#line 171 "parse.y"
{
  //sqlite3AddColumn(pParse,&X);
  //A = X;
}
#line 1810 "parse.c"
        break;
      case 34:
      case 35:
      case 36:
      case 37:
      case 38:
      case 243:
#line 181 "parse.y"
{yygotominor.yy308 = yymsp[0].minor.yy0;}
#line 1820 "parse.c"
        break;
      case 40:
#line 240 "parse.y"
{ /*sqlite3AddColumnType(pParse,&X);*/ }
#line 1825 "parse.c"
        break;
      case 41:
      case 44:
      case 118:
      case 119:
      case 130:
      case 149:
      case 240:
      case 241:
      case 242:
#line 241 "parse.y"
{yygotominor.yy308 = yymsp[0].minor.yy308;}
#line 1838 "parse.c"
        break;
      case 42:
#line 242 "parse.y"
{
  yygotominor.yy308.z = yymsp[-3].minor.yy308.z;
  yygotominor.yy308.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-3].minor.yy308.z;
}
#line 1846 "parse.c"
        break;
      case 43:
#line 246 "parse.y"
{
  yygotominor.yy308.z = yymsp[-5].minor.yy308.z;
  yygotominor.yy308.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-5].minor.yy308.z;
}
#line 1854 "parse.c"
        break;
      case 45:
#line 252 "parse.y"
{yygotominor.yy308.z=yymsp[-1].minor.yy308.z; yygotominor.yy308.n=yymsp[0].minor.yy308.n+(yymsp[0].minor.yy308.z-yymsp[-1].minor.yy308.z);}
#line 1859 "parse.c"
        break;
      case 46:
#line 254 "parse.y"
{ yygotominor.yy32 = atoi((char*)yymsp[0].minor.yy308.z); }
#line 1864 "parse.c"
        break;
      case 47:
#line 255 "parse.y"
{ yygotominor.yy32 = -atoi((char*)yymsp[0].minor.yy308.z); }
#line 1869 "parse.c"
        break;
      case 52:
#line 264 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/   yy_destructor(177,&yymsp[0].minor);
}
#line 1875 "parse.c"
        break;
      case 53:
#line 265 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/ }
#line 1880 "parse.c"
        break;
      case 54:
#line 266 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/  yy_destructor(177,&yymsp[0].minor);
}
#line 1886 "parse.c"
        break;
      case 55:
#line 267 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_UMINUS, X, 0, 0);
  //sqlite3AddDefaultValue(pParse,p);
  yy_destructor(177,&yymsp[0].minor);
}
#line 1895 "parse.c"
        break;
      case 56:
#line 271 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_STRING, 0, 0, &X);
  //sqlite3AddDefaultValue(pParse,p);
}
#line 1903 "parse.c"
        break;
      case 59:
#line 281 "parse.y"
{/*sqlite3AddNotNull(pParse, R);*/}
#line 1908 "parse.c"
        break;
      case 60:
#line 283 "parse.y"
{/*sqlite3AddPrimaryKey(pParse,0,R,I,Z);*/}
#line 1913 "parse.c"
        break;
      case 61:
#line 284 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,0,R,0,0,0,0);*/}
#line 1918 "parse.c"
        break;
      case 62:
#line 285 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,X);*/  sqlite3ExprDelete(yymsp[-1].minor.yy342); }
#line 1923 "parse.c"
        break;
      case 63:
#line 287 "parse.y"
{/*sqlite3CreateForeignKey(pParse,0,&T,TA,R);*/ sqlite3ExprListDelete(yymsp[-1].minor.yy462); }
#line 1928 "parse.c"
        break;
      case 64:
#line 288 "parse.y"
{/*sqlite3DeferForeignKey(pParse,D);*/}
#line 1933 "parse.c"
        break;
      case 65:
#line 289 "parse.y"
{/*sqlite3AddCollateType(pParse, (char*)C.z, C.n);*/}
#line 1938 "parse.c"
        break;
      case 68:
#line 302 "parse.y"
{ yygotominor.yy32 = OE_Restrict * 0x010101; }
#line 1943 "parse.c"
        break;
      case 69:
#line 303 "parse.y"
{ yygotominor.yy32 = (yymsp[-1].minor.yy32 & yymsp[0].minor.yy47.mask) | yymsp[0].minor.yy47.value; }
#line 1948 "parse.c"
        break;
      case 70:
#line 305 "parse.y"
{ yygotominor.yy47.value = 0;     yygotominor.yy47.mask = 0x000000; }
#line 1953 "parse.c"
        break;
      case 71:
#line 306 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32;     yygotominor.yy47.mask = 0x0000ff; }
#line 1958 "parse.c"
        break;
      case 72:
#line 307 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32<<8;  yygotominor.yy47.mask = 0x00ff00; }
#line 1963 "parse.c"
        break;
      case 73:
#line 308 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32<<16; yygotominor.yy47.mask = 0xff0000; }
#line 1968 "parse.c"
        break;
      case 74:
#line 310 "parse.y"
{ yygotominor.yy32 = OE_SetNull; }
#line 1973 "parse.c"
        break;
      case 75:
#line 311 "parse.y"
{ yygotominor.yy32 = OE_SetDflt; }
#line 1978 "parse.c"
        break;
      case 76:
#line 312 "parse.y"
{ yygotominor.yy32 = OE_Cascade; }
#line 1983 "parse.c"
        break;
      case 77:
#line 313 "parse.y"
{ yygotominor.yy32 = OE_Restrict; }
#line 1988 "parse.c"
        break;
      case 78:
      case 79:
      case 94:
      case 96:
      case 97:
#line 315 "parse.y"
{yygotominor.yy32 = yymsp[0].minor.yy32;}
#line 1997 "parse.c"
        break;
      case 89:
#line 334 "parse.y"
{ sqlite3ExprListDelete(yymsp[-3].minor.yy462); }
#line 2002 "parse.c"
        break;
      case 90:
#line 336 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,yymsp[-2].minor.yy462,R,0,0,0,0);*/ sqlite3ExprListDelete(yymsp[-2].minor.yy462);}
#line 2007 "parse.c"
        break;
      case 91:
#line 337 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,yymsp[-2].minor.yy342);*/ sqlite3ExprDelete(yymsp[-2].minor.yy342);}
#line 2012 "parse.c"
        break;
      case 92:
#line 339 "parse.y"
{ 
        sqlite3ExprListDelete(yymsp[-6].minor.yy462);
        sqlite3ExprListDelete(yymsp[-2].minor.yy462);
 }
#line 2020 "parse.c"
        break;
      case 95:
#line 354 "parse.y"
{yygotominor.yy32 = OE_Default;}
#line 2025 "parse.c"
        break;
      case 98:
#line 359 "parse.y"
{yygotominor.yy32 = OE_Ignore;}
#line 2030 "parse.c"
        break;
      case 99:
      case 169:
#line 360 "parse.y"
{yygotominor.yy32 = OE_Replace;}
#line 2036 "parse.c"
        break;
      case 100:
#line 364 "parse.y"
{
  sqlite3DropTable(pParse, yymsp[0].minor.yy287, 0, yymsp[-1].minor.yy32);
}
#line 2043 "parse.c"
        break;
      case 103:
#line 384 "parse.y"
{
  sqlite3Select(pParse, yymsp[0].minor.yy149, SRT_Callback, 0, 0, 0, 0, 0);
  // sqlite3SelectDelete(yymsp[0].minor.yy149);
}
#line 2051 "parse.c"
        break;
      case 104:
      case 127:
#line 394 "parse.y"
{yygotominor.yy149 = yymsp[0].minor.yy149;}
#line 2057 "parse.c"
        break;
      case 105:
#line 396 "parse.y"
{
  if( yymsp[0].minor.yy149 ){
    yymsp[0].minor.yy149->op = yymsp[-1].minor.yy32;
    yymsp[0].minor.yy149->pPrior = yymsp[-2].minor.yy149;
  }
  yygotominor.yy149 = yymsp[0].minor.yy149;
}
#line 2068 "parse.c"
        break;
      case 106:
      case 108:
#line 404 "parse.y"
{yygotominor.yy32 = yymsp[0].major;}
#line 2074 "parse.c"
        break;
      case 107:
#line 405 "parse.y"
{yygotominor.yy32 = TK_ALL;}
#line 2079 "parse.c"
        break;
      case 109:
#line 409 "parse.y"
{
  yygotominor.yy149 = sqlite3SelectNew(yymsp[-6].minor.yy462,yymsp[-5].minor.yy287,yymsp[-4].minor.yy342,yymsp[-3].minor.yy462,yymsp[-2].minor.yy342,yymsp[-1].minor.yy462,yymsp[-7].minor.yy32,yymsp[0].minor.yy474.pLimit,yymsp[0].minor.yy474.pOffset);
}
#line 2086 "parse.c"
        break;
      case 113:
      case 237:
#line 430 "parse.y"
{yygotominor.yy462 = yymsp[-1].minor.yy462;}
#line 2092 "parse.c"
        break;
      case 114:
      case 140:
      case 150:
      case 236:
#line 431 "parse.y"
{yygotominor.yy462 = 0;}
#line 2100 "parse.c"
        break;
      case 115:
#line 432 "parse.y"
{
   yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-2].minor.yy462,yymsp[-1].minor.yy342,yymsp[0].minor.yy308.n?&yymsp[0].minor.yy308:0);
}
#line 2107 "parse.c"
        break;
      case 116:
#line 435 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-1].minor.yy462, sqlite3Expr(TK_ALL, 0, 0, 0), 0);
}
#line 2114 "parse.c"
        break;
      case 117:
#line 438 "parse.y"
{
  Expr *pRight = sqlite3Expr(TK_ALL, 0, 0, 0);
  Expr *pLeft = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-3].minor.yy462, sqlite3Expr(TK_DOT, pLeft, pRight, 0), 0);
}
#line 2123 "parse.c"
        break;
      case 120:
#line 450 "parse.y"
{yygotominor.yy308.n = 0;}
#line 2128 "parse.c"
        break;
      case 121:
#line 462 "parse.y"
{yygotominor.yy287 = sqliteMalloc(sizeof(*yygotominor.yy287));}
#line 2133 "parse.c"
        break;
      case 122:
#line 463 "parse.y"
{yygotominor.yy287 = yymsp[0].minor.yy287;}
#line 2138 "parse.c"
        break;
      case 123:
#line 468 "parse.y"
{
   yygotominor.yy287 = yymsp[-1].minor.yy287;
   if( yygotominor.yy287 && yygotominor.yy287->nSrc>0 ) yygotominor.yy287->a[yygotominor.yy287->nSrc-1].jointype = yymsp[0].minor.yy32;
}
#line 2146 "parse.c"
        break;
      case 124:
#line 472 "parse.y"
{yygotominor.yy287 = 0;}
#line 2151 "parse.c"
        break;
      case 125:
#line 473 "parse.y"
{
  yygotominor.yy287 = sqlite3SrcListAppend(yymsp[-5].minor.yy287,&yymsp[-4].minor.yy308,&yymsp[-3].minor.yy308);
  if( yymsp[-2].minor.yy308.n ) sqlite3SrcListAddAlias(yygotominor.yy287,&yymsp[-2].minor.yy308);
  if( yymsp[-1].minor.yy342 ){
    if( yygotominor.yy287 && yygotominor.yy287->nSrc>1 ){ yygotominor.yy287->a[yygotominor.yy287->nSrc-2].pOn = yymsp[-1].minor.yy342; }
    else { sqlite3ExprDelete(yymsp[-1].minor.yy342); }
  }
  if( yymsp[0].minor.yy440 ){
    if( yygotominor.yy287 && yygotominor.yy287->nSrc>1 ){ yygotominor.yy287->a[yygotominor.yy287->nSrc-2].pUsing = yymsp[0].minor.yy440; }
    else { sqlite3IdListDelete(yymsp[0].minor.yy440); }
  }
}
#line 2167 "parse.c"
        break;
      case 126:
#line 487 "parse.y"
{
    yygotominor.yy287 = sqlite3SrcListAppend(yymsp[-6].minor.yy287,0,0);
    yygotominor.yy287->a[yygotominor.yy287->nSrc-1].pSelect = yymsp[-4].minor.yy149;
    if( yymsp[-2].minor.yy308.n ) sqlite3SrcListAddAlias(yygotominor.yy287,&yymsp[-2].minor.yy308);
    if( yymsp[-1].minor.yy342 ){
      if( yygotominor.yy287 && yygotominor.yy287->nSrc>1 ){ yygotominor.yy287->a[yygotominor.yy287->nSrc-2].pOn = yymsp[-1].minor.yy342; }
      else { sqlite3ExprDelete(yymsp[-1].minor.yy342); }
    }
    if( yymsp[0].minor.yy440 ){
      if( yygotominor.yy287 && yygotominor.yy287->nSrc>1 ){ yygotominor.yy287->a[yygotominor.yy287->nSrc-2].pUsing = yymsp[0].minor.yy440; }
      else { sqlite3IdListDelete(yymsp[0].minor.yy440); }
    }
  }
#line 2184 "parse.c"
        break;
      case 128:
#line 508 "parse.y"
{
     yygotominor.yy149 = sqlite3SelectNew(0,yymsp[0].minor.yy287,0,0,0,0,0,0,0);
  }
#line 2191 "parse.c"
        break;
      case 129:
#line 514 "parse.y"
{yygotominor.yy308.z=0; yygotominor.yy308.n=0;}
#line 2196 "parse.c"
        break;
      case 131:
#line 519 "parse.y"
{yygotominor.yy287 = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy308,&yymsp[0].minor.yy308);}
#line 2201 "parse.c"
        break;
      case 132:
#line 523 "parse.y"
{ yygotominor.yy32 = JT_INNER; }
#line 2206 "parse.c"
        break;
      case 133:
#line 524 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-1].minor.yy0,0,0); }
#line 2211 "parse.c"
        break;
      case 134:
#line 525 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-2].minor.yy0,&yymsp[-1].minor.yy308,0); }
#line 2216 "parse.c"
        break;
      case 135:
#line 527 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-3].minor.yy0,&yymsp[-2].minor.yy308,&yymsp[-1].minor.yy308); }
#line 2221 "parse.c"
        break;
      case 136:
      case 144:
      case 153:
      case 160:
      case 178:
      case 204:
      case 228:
      case 230:
      case 234:
#line 531 "parse.y"
{yygotominor.yy342 = yymsp[0].minor.yy342;}
#line 2234 "parse.c"
        break;
      case 137:
      case 152:
      case 159:
      case 205:
      case 229:
      case 231:
      case 235:
#line 532 "parse.y"
{yygotominor.yy342 = 0;}
#line 2245 "parse.c"
        break;
      case 138:
      case 175:
#line 536 "parse.y"
{yygotominor.yy440 = yymsp[-1].minor.yy440;}
#line 2251 "parse.c"
        break;
      case 139:
      case 174:
#line 537 "parse.y"
{yygotominor.yy440 = 0;}
#line 2257 "parse.c"
        break;
      case 141:
      case 151:
#line 548 "parse.y"
{yygotominor.yy462 = yymsp[0].minor.yy462;}
#line 2263 "parse.c"
        break;
      case 142:
#line 549 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462,yymsp[-2].minor.yy342,yymsp[-1].minor.yy308.n>0?&yymsp[-1].minor.yy308:0);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2271 "parse.c"
        break;
      case 143:
#line 553 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[-2].minor.yy342,yymsp[-1].minor.yy308.n>0?&yymsp[-1].minor.yy308:0);
  if( yygotominor.yy462 && yygotominor.yy462->a ) yygotominor.yy462->a[0].sortOrder = yymsp[0].minor.yy32;
}
#line 2279 "parse.c"
        break;
      case 145:
      case 147:
#line 562 "parse.y"
{yygotominor.yy32 = SQLITE_SO_ASC;}
#line 2285 "parse.c"
        break;
      case 146:
#line 563 "parse.y"
{yygotominor.yy32 = SQLITE_SO_DESC;}
#line 2290 "parse.c"
        break;
      case 148:
#line 565 "parse.y"
{yygotominor.yy308.z = 0; yygotominor.yy308.n = 0;}
#line 2295 "parse.c"
        break;
      case 154:
#line 583 "parse.y"
{yygotominor.yy474.pLimit = 0; yygotominor.yy474.pOffset = 0;}
#line 2300 "parse.c"
        break;
      case 155:
#line 584 "parse.y"
{yygotominor.yy474.pLimit = yymsp[0].minor.yy342; yygotominor.yy474.pOffset = 0;}
#line 2305 "parse.c"
        break;
      case 156:
#line 586 "parse.y"
{yygotominor.yy474.pLimit = yymsp[-2].minor.yy342; yygotominor.yy474.pOffset = yymsp[0].minor.yy342;}
#line 2310 "parse.c"
        break;
      case 157:
#line 588 "parse.y"
{yygotominor.yy474.pOffset = yymsp[-2].minor.yy342; yygotominor.yy474.pLimit = yymsp[0].minor.yy342;}
#line 2315 "parse.c"
        break;
      case 158:
#line 592 "parse.y"
{sqlite3DeleteFrom(pParse,yymsp[-2].minor.yy287,yymsp[-1].minor.yy342, yymsp[0].minor.yy474.pLimit, yymsp[0].minor.yy474.pOffset);}
#line 2320 "parse.c"
        break;
      case 161:
#line 604 "parse.y"
{sqlite3Update(pParse,yymsp[-4].minor.yy287,yymsp[-2].minor.yy462,yymsp[-1].minor.yy342,OE_Default, yymsp[0].minor.yy474.pLimit, yymsp[0].minor.yy474.pOffset);}
#line 2325 "parse.c"
        break;
      case 162:
#line 610 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462,yymsp[0].minor.yy342,&yymsp[-2].minor.yy308);}
#line 2330 "parse.c"
        break;
      case 163:
#line 611 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[0].minor.yy342,&yymsp[-2].minor.yy308);}
#line 2335 "parse.c"
        break;
      case 164:
#line 620 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, 0, yymsp[0].minor.yy49, 0, yymsp[-2].minor.yy440, yymsp[-5].minor.yy32);}
#line 2340 "parse.c"
        break;
      case 165:
#line 624 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, yymsp[0].minor.yy462, 0, 0, yymsp[-2].minor.yy440, yymsp[-5].minor.yy32);}
#line 2345 "parse.c"
        break;
      case 166:
#line 628 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, yymsp[0].minor.yy462, 0, 0, yymsp[-2].minor.yy440, yymsp[-4].minor.yy32);}
#line 2350 "parse.c"
        break;
      case 167:
#line 631 "parse.y"
{sqlite3Insert(pParse, yymsp[-2].minor.yy287, 0, 0, yymsp[0].minor.yy149, yymsp[-1].minor.yy440, yymsp[-4].minor.yy32);}
#line 2355 "parse.c"
        break;
      case 168:
#line 635 "parse.y"
{ yygotominor.yy32 = OE_Default; }
#line 2360 "parse.c"
        break;
      case 170:
#line 641 "parse.y"
{ yygotominor.yy49 = sqlite3ValuesListAppend(yymsp[-4].minor.yy49, yymsp[-1].minor.yy462);}
#line 2365 "parse.c"
        break;
      case 171:
#line 642 "parse.y"
{ yygotominor.yy49 = sqlite3ValuesListAppend(0, yymsp[-1].minor.yy462); }
#line 2370 "parse.c"
        break;
      case 172:
      case 232:
#line 647 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-2].minor.yy462,yymsp[0].minor.yy342,0);}
#line 2376 "parse.c"
        break;
      case 173:
      case 233:
#line 648 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[0].minor.yy342,0);}
#line 2382 "parse.c"
        break;
      case 176:
#line 657 "parse.y"
{yygotominor.yy440 = sqlite3IdListAppend(yymsp[-2].minor.yy440,&yymsp[0].minor.yy308);}
#line 2387 "parse.c"
        break;
      case 177:
#line 658 "parse.y"
{yygotominor.yy440 = sqlite3IdListAppend(0,&yymsp[0].minor.yy308);}
#line 2392 "parse.c"
        break;
      case 179:
#line 669 "parse.y"
{yygotominor.yy342 = yymsp[-1].minor.yy342; sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0); }
#line 2397 "parse.c"
        break;
      case 180:
      case 185:
      case 186:
#line 670 "parse.y"
{yygotominor.yy342 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0);}
#line 2404 "parse.c"
        break;
      case 181:
      case 182:
#line 671 "parse.y"
{yygotominor.yy342 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy0);}
#line 2410 "parse.c"
        break;
      case 183:
#line 673 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy308);
  yygotominor.yy342 = sqlite3Expr(TK_DOT, temp1, temp2, 0);
}
#line 2419 "parse.c"
        break;
      case 184:
#line 678 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-4].minor.yy308);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  Expr *temp3 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy308);
  Expr *temp4 = sqlite3Expr(TK_DOT, temp2, temp3, 0);
  yygotominor.yy342 = sqlite3Expr(TK_DOT, temp1, temp4, 0);
}
#line 2430 "parse.c"
        break;
      case 187:
#line 687 "parse.y"
{yygotominor.yy342 = sqlite3RegisterExpr(pParse, &yymsp[0].minor.yy0);}
#line 2435 "parse.c"
        break;
      case 188:
      case 189:
#line 688 "parse.y"
{
  Token *pToken = &yymsp[0].minor.yy0;
  Expr *pExpr = yygotominor.yy342 = sqlite3Expr(TK_VARIABLE, 0, 0, pToken);
  //sqlite3ExprAssignVarNumber(pParse, pExpr);
}
#line 2445 "parse.c"
        break;
      case 190:
#line 699 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_CAST, yymsp[-3].minor.yy342, 0, &yymsp[-1].minor.yy308);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-5].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2453 "parse.c"
        break;
      case 191:
#line 704 "parse.y"
{
  yygotominor.yy342 = sqlite3ExprFunction(yymsp[-1].minor.yy462, &yymsp[-4].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-4].minor.yy0,&yymsp[0].minor.yy0);
  if( yymsp[-2].minor.yy32 && yygotominor.yy342 ){
    yygotominor.yy342->flags |= EP_Distinct;
  }
}
#line 2464 "parse.c"
        break;
      case 192:
#line 711 "parse.y"
{
  yygotominor.yy342 = sqlite3ExprFunction(0, &yymsp[-3].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2472 "parse.c"
        break;
      case 193:
#line 715 "parse.y"
{
  /* The CURRENT_TIME, CURRENT_DATE, and CURRENT_TIMESTAMP values are
  ** treated as functions that return constants */
  yygotominor.yy342 = sqlite3ExprFunction(0,&yymsp[0].minor.yy0);
  if( yygotominor.yy342 ) yygotominor.yy342->op = TK_CONST_FUNC;  
}
#line 2482 "parse.c"
        break;
      case 194:
      case 195:
      case 196:
      case 197:
      case 198:
      case 199:
      case 200:
      case 201:
#line 721 "parse.y"
{yygotominor.yy342 = sqlite3Expr(yymsp[-1].major, yymsp[-2].minor.yy342, yymsp[0].minor.yy342, 0);}
#line 2494 "parse.c"
        break;
      case 202:
#line 731 "parse.y"
{yygotominor.yy118.eOperator = yymsp[0].minor.yy0; yygotominor.yy118.not = 0;}
#line 2499 "parse.c"
        break;
      case 203:
#line 732 "parse.y"
{yygotominor.yy118.eOperator = yymsp[0].minor.yy0; yygotominor.yy118.not = 1;}
#line 2504 "parse.c"
        break;
      case 206:
#line 737 "parse.y"
{
  ExprList *pList;
  pList = sqlite3ExprListAppend(0, yymsp[-3].minor.yy342, 0);
  pList = sqlite3ExprListAppend(pList, yymsp[-1].minor.yy342, 0);
  if( yymsp[0].minor.yy342 ){
    pList = sqlite3ExprListAppend(pList, yymsp[0].minor.yy342, 0);
  }
  //yygotominor.yy342 = sqlite3ExprFunction(pList, &yymsp[-2].minor.yy118.eOperator);
  yygotominor.yy342 = sqlite3ExprLikeOp(pList, &yymsp[-2].minor.yy118.eOperator);
  if( yymsp[-2].minor.yy118.not ) yygotominor.yy342 = sqlite3Expr(TK_NOT, yygotominor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342, &yymsp[-3].minor.yy342->span, &yymsp[-1].minor.yy342->span);
}
#line 2520 "parse.c"
        break;
      case 207:
#line 750 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(yymsp[0].major, yymsp[-1].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2528 "parse.c"
        break;
      case 208:
#line 754 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_ISNULL, yymsp[-2].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2536 "parse.c"
        break;
      case 209:
#line 758 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_NOTNULL, yymsp[-2].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2544 "parse.c"
        break;
      case 210:
#line 762 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_NOTNULL, yymsp[-3].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-3].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2552 "parse.c"
        break;
      case 211:
#line 766 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(yymsp[-1].major, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2560 "parse.c"
        break;
      case 212:
#line 770 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_UMINUS, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2568 "parse.c"
        break;
      case 213:
#line 774 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_UPLUS, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2576 "parse.c"
        break;
      case 216:
#line 785 "parse.y"
{ yygotominor.yy342 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0); }
#line 2581 "parse.c"
        break;
      case 217:
#line 788 "parse.y"
{
  ExprList *pList = sqlite3ExprListAppend(0, yymsp[-2].minor.yy342, 0);
  pList = sqlite3ExprListAppend(pList, yymsp[0].minor.yy342, 0);
  yygotominor.yy342 = sqlite3Expr(TK_BETWEEN, yymsp[-4].minor.yy342, 0, 0);
  if( yygotominor.yy342 ){
    yygotominor.yy342->pList = pList;
  }else{
    sqlite3ExprListDelete(pList);
  } 
  if( yymsp[-3].minor.yy32 ) yygotominor.yy342 = sqlite3Expr(TK_NOT, yygotominor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-4].minor.yy342->span,&yymsp[0].minor.yy342->span);
}
#line 2597 "parse.c"
        break;
      case 220:
#line 804 "parse.y"
{
    yygotominor.yy342 = sqlite3Expr(TK_IN, yymsp[-4].minor.yy342, 0, 0);
    if( yygotominor.yy342 ){
      yygotominor.yy342->pList = yymsp[-1].minor.yy462;
    }else{
      sqlite3ExprListDelete(yymsp[-1].minor.yy462);
    }
    if( yymsp[-3].minor.yy32 ) yygotominor.yy342 = sqlite3Expr(TK_NOT, yygotominor.yy342, 0, 0);
    sqlite3ExprSpan(yygotominor.yy342,&yymsp[-4].minor.yy342->span,&yymsp[0].minor.yy0);
  }
#line 2611 "parse.c"
        break;
      case 221:
#line 814 "parse.y"
{
    yygotominor.yy342 = sqlite3Expr(TK_SELECT, 0, 0, 0);
    if( yygotominor.yy342 ){
      yygotominor.yy342->pSelect = yymsp[-1].minor.yy149;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy149);
    }
    sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0);
  }
#line 2624 "parse.c"
        break;
      case 222:
#line 823 "parse.y"
{
    yygotominor.yy342 = sqlite3Expr(TK_IN, yymsp[-4].minor.yy342, 0, 0);
    if( yygotominor.yy342 ){
      yygotominor.yy342->pSelect = yymsp[-1].minor.yy149;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy149);
    }
    if( yymsp[-3].minor.yy32 ) yygotominor.yy342 = sqlite3Expr(TK_NOT, yygotominor.yy342, 0, 0);
    sqlite3ExprSpan(yygotominor.yy342,&yymsp[-4].minor.yy342->span,&yymsp[0].minor.yy0);
  }
#line 2638 "parse.c"
        break;
      case 223:
#line 833 "parse.y"
{
    SrcList *pSrc = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy308,&yymsp[0].minor.yy308);
    yygotominor.yy342 = sqlite3Expr(TK_IN, yymsp[-3].minor.yy342, 0, 0);
    if( yygotominor.yy342 ){
      yygotominor.yy342->pSelect = sqlite3SelectNew(0,pSrc,0,0,0,0,0,0,0);
    }else{
      sqlite3SrcListDelete(pSrc);
    }
    if( yymsp[-2].minor.yy32 ) yygotominor.yy342 = sqlite3Expr(TK_NOT, yygotominor.yy342, 0, 0);
    sqlite3ExprSpan(yygotominor.yy342,&yymsp[-3].minor.yy342->span,yymsp[0].minor.yy308.z?&yymsp[0].minor.yy308:&yymsp[-1].minor.yy308);
  }
#line 2653 "parse.c"
        break;
      case 224:
#line 844 "parse.y"
{
    Expr *p = yygotominor.yy342 = sqlite3Expr(TK_EXISTS, 0, 0, 0);
    if( p ){
      p->pSelect = yymsp[-1].minor.yy149;
      sqlite3ExprSpan(p,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy149);
    }
  }
#line 2666 "parse.c"
        break;
      case 225:
#line 856 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_CASE, yymsp[-3].minor.yy342, yymsp[-1].minor.yy342, 0);
  if( yygotominor.yy342 ){
    yygotominor.yy342->pList = yymsp[-2].minor.yy462;
  }else{
    sqlite3ExprListDelete(yymsp[-2].minor.yy462);
  }
  sqlite3ExprSpan(yygotominor.yy342, &yymsp[-4].minor.yy0, &yymsp[0].minor.yy0);
}
#line 2679 "parse.c"
        break;
      case 226:
#line 867 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462, yymsp[-2].minor.yy342, 0);
  yygotominor.yy462 = sqlite3ExprListAppend(yygotominor.yy462, yymsp[0].minor.yy342, 0);
}
#line 2687 "parse.c"
        break;
      case 227:
#line 871 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(0, yymsp[-2].minor.yy342, 0);
  yygotominor.yy462 = sqlite3ExprListAppend(yygotominor.yy462, yymsp[0].minor.yy342, 0);
}
#line 2695 "parse.c"
        break;
      case 238:
#line 915 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy308.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy308.z, yymsp[-1].minor.yy308.n);
  }
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462, p, &yymsp[-2].minor.yy308);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2708 "parse.c"
        break;
      case 239:
#line 924 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy308.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy308.z, yymsp[-1].minor.yy308.n);
  }
  yygotominor.yy462 = sqlite3ExprListAppend(0, p, &yymsp[-2].minor.yy308);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2721 "parse.c"
        break;
      case 246:
#line 1055 "parse.y"
{yygotominor.yy32 = OE_Rollback;}
#line 2726 "parse.c"
        break;
      case 247:
#line 1056 "parse.y"
{yygotominor.yy32 = OE_Abort;}
#line 2731 "parse.c"
        break;
      case 248:
#line 1057 "parse.y"
{yygotominor.yy32 = OE_Fail;}
#line 2736 "parse.c"
        break;
      case 249:
#line 1113 "parse.y"
{
    sqlite3SetStatement(pParse, yymsp[0].minor.yy462, 0, SQLTYPE_SET);
}
#line 2743 "parse.c"
        break;
      case 250:
#line 1117 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy308, SQLTYPE_SET_NAMES);   
}
#line 2750 "parse.c"
        break;
      case 251:
#line 1121 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy308, SQLTYPE_SET_CHARACTER_SET);
}
#line 2757 "parse.c"
        break;
      case 252:
#line 1127 "parse.y"
{
    yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-5].minor.yy462, yymsp[0].minor.yy342, &yymsp[-2].minor.yy308);
}
#line 2764 "parse.c"
        break;
      case 253:
#line 1131 "parse.y"
{
    yygotominor.yy462 = sqlite3ExprListAppend(0, yymsp[0].minor.yy342, &yymsp[-2].minor.yy308);                         
}
#line 2771 "parse.c"
        break;
      case 257:
#line 1139 "parse.y"
{ sqlite3CheckSetScope(pParse, &yymsp[-1].minor.yy0); }
#line 2776 "parse.c"
        break;
      case 259:
#line 1143 "parse.y"
{ yygotominor.yy308 = yymsp[0].minor.yy308; }
#line 2781 "parse.c"
        break;
      case 260:
#line 1144 "parse.y"
{ yygotominor.yy308 = yymsp[0].minor.yy0; }
#line 2786 "parse.c"
        break;
      case 263:
#line 1150 "parse.y"
{
    sqlite3ShowStatement(pParse, yymsp[0].major);
}
#line 2793 "parse.c"
        break;
      case 264:
#line 1154 "parse.y"
{
    sqlite3ShowStatement(pParse, yymsp[-1].major);
}
#line 2800 "parse.c"
        break;
  };
  yygoto = yyRuleInfo[yyruleno].lhs;
  yysize = yyRuleInfo[yyruleno].nrhs;
  yypParser->yyidx -= yysize;
  yyact = yy_find_reduce_action(yymsp[-yysize].stateno,yygoto);
  if( yyact < YYNSTATE ){
#ifdef NDEBUG
    /* If we are not debugging and the reduce action popped at least
    ** one element off the stack, then we can push the new element back
    ** onto the stack here, and skip the stack overflow test in yy_shift().
    ** That gives a significant speed improvement. */
    if( yysize ){
      yypParser->yyidx++;
      yymsp -= yysize-1;
      yymsp->stateno = yyact;
      yymsp->major = yygoto;
      yymsp->minor = yygotominor;
    }else
#endif
    {
      yy_shift(yypParser,yyact,yygoto,&yygotominor);
    }
  }else if( yyact == YYNSTATE + YYNRULE + 1 ){
    yy_accept(yypParser);
  }
}

/*
** The following code executes when the parse fails
*/
static void yy_parse_failed(
  yyParser *yypParser           /* The parser */
){
  sqlite3ParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sFail!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser fails */
  sqlite3ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following code executes when a syntax error first occurs.
*/
static void yy_syntax_error(
  yyParser *yypParser,           /* The parser */
  int yymajor,                   /* The major type of the error token */
  YYMINORTYPE yyminor            /* The minor type of the error token */
){
  sqlite3ParserARG_FETCH;
#define TOKEN (yyminor.yy0)
#line 34 "parse.y"

  if( pParse->zErrMsg==0 ){
    if( TOKEN.z[0] ){
      sqlite3ErrorMsg(pParse, "near \"%T\": syntax error", &TOKEN);
    }else{
      sqlite3ErrorMsg(pParse, "incomplete SQL statement");
    }
  }
#line 2867 "parse.c"
  sqlite3ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/*
** The following is executed when the parser accepts
*/
static void yy_accept(
  yyParser *yypParser           /* The parser */
){
  sqlite3ParserARG_FETCH;
#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sAccept!\n",yyTracePrompt);
  }
#endif
  while( yypParser->yyidx>=0 ) yy_pop_parser_stack(yypParser);
  /* Here code is inserted which will be executed whenever the
  ** parser accepts */
  sqlite3ParserARG_STORE; /* Suppress warning about unused %extra_argument variable */
}

/* The main parser program.
** The first argument is a pointer to a structure obtained from
** "sqlite3ParserAlloc" which describes the current state of the parser.
** The second argument is the major token number.  The third is
** the minor token.  The fourth optional argument is whatever the
** user wants (and specified in the grammar) and is available for
** use by the action routines.
**
** Inputs:
** <ul>
** <li> A pointer to the parser (an opaque structure.)
** <li> The major token number.
** <li> The minor token number.
** <li> An option argument of a grammar-specified type.
** </ul>
**
** Outputs:
** None.
*/
void sqlite3Parser(
  void *yyp,                   /* The parser */
  int yymajor,                 /* The major token code number */
  sqlite3ParserTOKENTYPE yyminor       /* The value for the token */
  sqlite3ParserARG_PDECL               /* Optional %extra_argument parameter */
){
  YYMINORTYPE yyminorunion;
  int yyact;            /* The parser action. */
  int yyendofinput;     /* True if we are at the end of input */
  int yyerrorhit = 0;   /* True if yymajor has invoked an error */
  yyParser *yypParser;  /* The parser */

  /* (re)initialize the parser, if necessary */
  yypParser = (yyParser*)yyp;
  if( yypParser->yyidx<0 ){
    /* if( yymajor==0 ) return; // not sure why this was here... */
    yypParser->yyidx = 0;
    yypParser->yyerrcnt = -1;
    yypParser->yystack[0].stateno = 0;
    yypParser->yystack[0].major = 0;
  }
  yyminorunion.yy0 = yyminor;
  yyendofinput = (yymajor==0);
  sqlite3ParserARG_STORE;

#ifndef NDEBUG
  if( yyTraceFILE ){
    fprintf(yyTraceFILE,"%sInput %s\n",yyTracePrompt,yyTokenName[yymajor]);
  }
#endif

  do{
    yyact = yy_find_shift_action(yypParser,yymajor);
    if( yyact<YYNSTATE ){
      yy_shift(yypParser,yyact,yymajor,&yyminorunion);
      yypParser->yyerrcnt--;
      if( yyendofinput && yypParser->yyidx>=0 ){
        yymajor = 0;
      }else{
        yymajor = YYNOCODE;
      }
    }else if( yyact < YYNSTATE + YYNRULE ){
      yy_reduce(yypParser,yyact-YYNSTATE);
    }else if( yyact == YY_ERROR_ACTION ){
      int yymx;
#ifndef NDEBUG
      if( yyTraceFILE ){
        fprintf(yyTraceFILE,"%sSyntax Error!\n",yyTracePrompt);
      }
#endif
#ifdef YYERRORSYMBOL
      /* A syntax error has occurred.
      ** The response to an error depends upon whether or not the
      ** grammar defines an error token "ERROR".  
      **
      ** This is what we do if the grammar does define ERROR:
      **
      **  * Call the %syntax_error function.
      **
      **  * Begin popping the stack until we enter a state where
      **    it is legal to shift the error symbol, then shift
      **    the error symbol.
      **
      **  * Set the error count to three.
      **
      **  * Begin accepting and shifting new tokens.  No new error
      **    processing will occur until three tokens have been
      **    shifted successfully.
      **
      */
      if( yypParser->yyerrcnt<0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yymx = yypParser->yystack[yypParser->yyidx].major;
      if( yymx==YYERRORSYMBOL || yyerrorhit ){
#ifndef NDEBUG
        if( yyTraceFILE ){
          fprintf(yyTraceFILE,"%sDiscard input token %s\n",
             yyTracePrompt,yyTokenName[yymajor]);
        }
#endif
        yy_destructor(yymajor,&yyminorunion);
        yymajor = YYNOCODE;
      }else{
         while(
          yypParser->yyidx >= 0 &&
          yymx != YYERRORSYMBOL &&
          (yyact = yy_find_shift_action(yypParser,YYERRORSYMBOL)) >= YYNSTATE
        ){
          yy_pop_parser_stack(yypParser);
        }
        if( yypParser->yyidx < 0 || yymajor==0 ){
          yy_destructor(yymajor,&yyminorunion);
          yy_parse_failed(yypParser);
          yymajor = YYNOCODE;
        }else if( yymx!=YYERRORSYMBOL ){
          YYMINORTYPE u2;
          u2.YYERRSYMDT = 0;
          yy_shift(yypParser,yyact,YYERRORSYMBOL,&u2);
        }
      }
      yypParser->yyerrcnt = 3;
      yyerrorhit = 1;
#else  /* YYERRORSYMBOL is not defined */
      /* This is what we do if the grammar does not define ERROR:
      **
      **  * Report an error message, and throw away the input token.
      **
      **  * If the input token is $, then fail the parse.
      **
      ** As before, subsequent error messages are suppressed until
      ** three input tokens have been successfully shifted.
      */
      if( yypParser->yyerrcnt<=0 ){
        yy_syntax_error(yypParser,yymajor,yyminorunion);
      }
      yypParser->yyerrcnt = 3;
      yy_destructor(yymajor,&yyminorunion);
      if( yyendofinput ){
        yy_parse_failed(yypParser);
      }
      yymajor = YYNOCODE;
#endif
    }else{
      yy_accept(yypParser);
      yymajor = YYNOCODE;
    }
  }while( yymajor!=YYNOCODE && yypParser->yyidx>=0 );
  return;
}
