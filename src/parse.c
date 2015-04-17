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
#define YYNSTATE 490
#define YYNRULE 271
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
 /*     0 */   231,  762,  104,  489,  445,  143,    1,  362,   56,   55,
 /*    10 */    55,   55,   55,  440,   57,   57,   57,   57,   58,   58,
 /*    20 */    59,   59,   59,   60,   62,   57,   57,   57,   57,   58,
 /*    30 */    58,   59,   59,   59,   60,  375,   57,   57,   57,   57,
 /*    40 */    58,   58,   59,   59,   59,   60,   58,   58,   59,   59,
 /*    50 */    59,   60,   54,   52,  239,  383,  386,  380,  380,   56,
 /*    60 */    55,   55,   55,   55,  163,   57,   57,   57,   57,   58,
 /*    70 */    58,   59,   59,   59,   60,  231,   60,  263,  362,  307,
 /*    80 */   235,   71,  127,   56,  177,  308,  476,  477,  478,   98,
 /*    90 */   434,  374,  210,  235,  447,  263,  442,  352,   24,  263,
 /*   100 */   327,  270,   17,  388,  388,  210,  314,  311,  250,  315,
 /*   110 */   375,  329,  161,  126,   51,  352,   30,  353,  443,  352,
 /*   120 */    42,  156,  356,  244,  444,  125,  457,   54,   52,  239,
 /*   130 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  413,
 /*   140 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   150 */   231,  158,  358,  358,  358,   93,  353,  456,   56,  329,
 /*   160 */   136,  333,  186,  259,  190,  260,  147,  248,  209,  197,
 /*   170 */   413,  211,  347,  263,  333,  186,  259,  190,  260,  147,
 /*   180 */   348,  102,  330,  331,  211,  375,  353,  152,  409,  115,
 /*   190 */   282,  285,  286,  352,   29,  238,  365,  366,  249,  287,
 /*   200 */   482,  483,   54,   52,  239,  383,  386,  380,  380,   56,
 /*   210 */    55,   55,   55,   55,  113,   57,   57,   57,   57,   58,
 /*   220 */    58,   59,   59,   59,   60,  231,  455,  415,  423,  241,
 /*   230 */   330,  331,  152,   56,  454,  282,  285,  286,   61,  397,
 /*   240 */   167,  263,  128,  280,  287,   61,  263,  167,  332,  128,
 /*   250 */   393,  263,   16,  152,  120,  436,  282,  285,  286,  165,
 /*   260 */   375,  352,   29,  352,    3,  287,  352,   29,  145,  370,
 /*   270 */   166,  352,   35,  266,  365,  366,  163,   54,   52,  239,
 /*   280 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  225,
 /*   290 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   300 */   231,  263,  418,  353,  242,   66,  129,   68,   56,  276,
 /*   310 */   220,  274,  201,  263,  290,  146,  133,  329,  394,  263,
 /*   320 */   279,  352,   29,  394,  447,  470,  183,    2,  329,  448,
 /*   330 */   458,  329,   17,  352,   42,  375,  329,  165,    9,  352,
 /*   340 */    35,  353,  329,  228,  329,   67,  372,  446,  140,  226,
 /*   350 */   148,  198,   54,   52,  239,  383,  386,  380,  380,   56,
 /*   360 */    55,   55,   55,   55,  240,   57,   57,   57,   57,   58,
 /*   370 */    58,   59,   59,   59,   60,  231,  339,  389,  394,  419,
 /*   380 */   199,  247,  390,   56,   59,   59,   59,   60,  330,  331,
 /*   390 */   434,  329,  270,  340,  388,  388,  372,  267,  140,  330,
 /*   400 */   331,  232,  330,  331,  376,  211,  362,  330,  331,  341,
 /*   410 */   375,  337,  405,  330,  331,  330,  331,   61,  362,  167,
 /*   420 */    70,  128,  338,  175,  378,  379,  299,   54,   52,  239,
 /*   430 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  406,
 /*   440 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   450 */   231,  377,  305,  118,  422,  417,  351,  307,   56,  263,
 /*   460 */   350,  263,  330,  331,  476,  477,  478,  270,  209,  388,
 /*   470 */   388,  263,  270,  263,  388,  388,  263,  362,  191,  352,
 /*   480 */    25,  352,   20,  335,  336,  375,  132,  328,  439,  362,
 /*   490 */   176,  352,   28,  352,   47,  436,  352,   21,  434,  490,
 /*   500 */   314,  311,   54,   52,  239,  383,  386,  380,  380,   56,
 /*   510 */    55,   55,   55,   55,  263,   57,   57,   57,   57,   58,
 /*   520 */    58,   59,   59,   59,   60,  231,  263,  475,  263,  441,
 /*   530 */   263,  245,  263,   56,  352,   45,  263,  434,  263,  313,
 /*   540 */   434,  263,    1,  263,  277,  263,  352,   84,  352,   82,
 /*   550 */   352,   86,  352,   87,  142,  133,  352,   94,  352,   95,
 /*   560 */   375,  352,   15,  352,   85,  352,   46,  299,   18,  143,
 /*   570 */   246,  362,  362,  149,  150,  151,  209,   54,   52,  239,
 /*   580 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  263,
 /*   590 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   600 */   231,  263,  202,  263,  214,  263,  243,  263,   56,  352,
 /*   610 */    96,  130,  263,  154,  428,  209,  263,  281,  208,  263,
 /*   620 */   108,  352,   97,  352,   22,  352,   31,  352,   32,  263,
 /*   630 */   299,  302,  352,   23,  474,  375,  352,   33,  429,  352,
 /*   640 */    34,  351,  362,  362,  474,  350,  353,  264,  353,  352,
 /*   650 */    36,  409,   54,   52,  239,  383,  386,  380,  380,   56,
 /*   660 */    55,   55,   55,   55,  263,   57,   57,   57,   57,   58,
 /*   670 */    58,   59,   59,   59,   60,  231,  263,  409,  263,  404,
 /*   680 */   263,  220,  263,   56,  352,   37,  263,  220,  263,  402,
 /*   690 */   203,  263,  157,  263,  304,  450,  352,   38,  352,   26,
 /*   700 */   352,   27,  352,   39,  487,  306,  352,   40,  352,   41,
 /*   710 */   375,  352,   43,  352,   44,  309,  205,  220,  220,  160,
 /*   720 */   462,  368,  368,  148,  427,  117,  221,   54,   52,  239,
 /*   730 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  384,
 /*   740 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   750 */   231,  137,  131,  484,  484,  268,  297,  224,   56,  164,
 /*   760 */   253,  255,  234,  185,  160,   99,   48,  187,  344,  363,
 /*   770 */   392,   19,   12,  384,  232,  404,  188,  345,  411,  420,
 /*   780 */   144,   12,    5,  357,  122,  375,  432,  213,  108,  108,
 /*   790 */   289,  467,  108,   79,  468,   73,   79,  426,  471,  371,
 /*   800 */   144,  395,  403,   52,  239,  383,  386,  380,  380,   56,
 /*   810 */    55,   55,   55,   55,  408,   57,   57,   57,   57,   58,
 /*   820 */    58,   59,   59,   59,   60,  231,  425,  412,  430,  431,
 /*   830 */   310,  207,  424,   56,  449,  215,  218,  381,   63,  271,
 /*   840 */   298,    4,  486,  322,  189,  237,  192,  121,  526,  367,
 /*   850 */   369,  269,  385,  272,  223,  318,  398,  480,  265,  481,
 /*   860 */   375,  401,  433,  485,  435,  423,  317,  320,  321,    8,
 /*   870 */   284,  252,  325,  256,  257,  258,  334,  342,  236,  239,
 /*   880 */   383,  386,  380,  380,   56,   55,   55,   55,   55,  374,
 /*   890 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   900 */   343,  346,  349,  354,   73,  193,  275,   65,   64,   72,
 /*   910 */   194,   63,  271,  273,    4,   63,  261,  262,  237,   50,
 /*   920 */   356,  195,   63,  271,  196,    4,  469,  355,  169,  237,
 /*   930 */   141,  265,   69,  396,  399,  200,  163,  170,  400,  171,
 /*   940 */   105,   74,  265,  278,  204,   89,  410,  206,  229,  173,
 /*   950 */   358,  358,  358,  359,  360,  361,   11,  414,  437,  180,
 /*   960 */   251,  174,  374,  181,  182,  216,  438,  461,  451,  291,
 /*   970 */   452,  453,  292,  374,  230,  155,  459,  295,  109,  100,
 /*   980 */    65,   64,  416,  463,  465,  103,  222,  114,   63,  261,
 /*   990 */   262,   65,   64,  356,   10,   63,  271,  233,    4,   63,
 /*  1000 */   261,  262,  237,  172,  356,   83,  466,  316,  319,  300,
 /*  1010 */   473,   88,  227,  254,   75,  265,  323,  303,  399,  324,
 /*  1020 */   326,  184,  101,  358,  358,  358,  359,  360,  361,   11,
 /*  1030 */   162,   49,  527,  528,  358,  358,  358,  359,  360,  361,
 /*  1040 */    11,  138,   53,  139,  364,  373,  374,  168,  382,  387,
 /*  1050 */   119,  391,    6,    7,   13,   12,  296,  111,  472,  407,
 /*  1060 */   106,  294,  374,  107,   65,   64,  163,  134,  421,  283,
 /*  1070 */    90,   91,   63,  261,  262,  212,   76,  356,   92,  288,
 /*  1080 */   123,  124,  153,  188,  217,  293,  219,  110,  460,  443,
 /*  1090 */   464,  112,   77,  356,  116,  159,   14,  301,   78,  479,
 /*  1100 */   157,  135,  179,  178,   80,   81,  312,  358,  358,  358,
 /*  1110 */   359,  360,  361,   11,  488,  518,  518,  518,  518,  518,
 /*  1120 */   518,  518,  518,  358,  358,  358,
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
 /*   150 */    14,  162,  126,  127,  128,   19,  197,  189,   22,   21,
 /*   160 */    94,   95,   96,   97,   98,   99,  100,  225,  235,  231,
 /*   170 */   157,  105,   30,  157,   95,   96,   97,   98,   99,  100,
 /*   180 */    38,  222,   92,   93,  105,   49,  197,   94,  169,   25,
 /*   190 */    97,   98,   99,  177,  178,  172,  173,  174,  216,  106,
 /*   200 */   241,  242,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   210 */    74,   75,   76,   77,  124,   79,   80,   81,   82,   83,
 /*   220 */    84,   85,   86,   87,   88,   14,  183,  208,  185,  216,
 /*   230 */    92,   93,   94,   22,  191,   97,   98,   99,  226,  227,
 /*   240 */   228,  157,  230,  157,  106,  226,  157,  228,  176,  230,
 /*   250 */   234,  157,   17,   94,   19,  183,   97,   98,   99,  236,
 /*   260 */    49,  177,  178,  177,  178,  106,  177,  178,  162,   83,
 /*   270 */    84,  177,  178,  172,  173,  174,  112,   66,   67,   68,
 /*   280 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  125,
 /*   290 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   300 */    14,  157,   18,  197,  220,  133,  162,  135,   22,  220,
 /*   310 */   157,  217,  218,  157,   14,  209,  210,   21,  234,  157,
 /*   320 */   214,  177,  178,  234,  157,   18,  159,   17,   21,  189,
 /*   330 */   163,   21,  165,  177,  178,   49,   21,  236,   17,  177,
 /*   340 */   178,  197,   21,  166,   21,  134,  169,  170,  171,  196,
 /*   350 */    50,  157,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   360 */    74,   75,   76,   77,  220,   79,   80,   81,   82,   83,
 /*   370 */    84,   85,   86,   87,   88,   14,   10,   18,  234,   18,
 /*   380 */   218,  225,   18,   22,   85,   86,   87,   88,   92,   93,
 /*   390 */   157,   21,  108,   27,  110,  111,  169,  170,  171,   92,
 /*   400 */    93,  101,   92,   93,   49,  105,   21,   92,   93,   43,
 /*   410 */    49,   45,  116,   92,   93,   92,   93,  226,   21,  228,
 /*   420 */   134,  230,   56,  190,   69,   70,  157,   66,   67,   68,
 /*   430 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  116,
 /*   440 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   450 */    14,   96,  238,  239,   18,   85,  109,  131,   22,  157,
 /*   460 */   113,  157,   92,   93,  138,  139,  140,  108,  235,  110,
 /*   470 */   111,  157,  108,  157,  110,  111,  157,   92,  198,  177,
 /*   480 */   178,  177,  178,  193,  194,   49,  157,  175,  176,   92,
 /*   490 */   221,  177,  178,  177,  178,  183,  177,  178,  157,    0,
 /*   500 */     1,    2,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   510 */    74,   75,   76,   77,  157,   79,   80,   81,   82,   83,
 /*   520 */    84,   85,   86,   87,   88,   14,  157,  130,  157,   18,
 /*   530 */   157,  190,  157,   22,  177,  178,  157,  157,  157,  148,
 /*   540 */   157,  157,  151,  157,  157,  157,  177,  178,  177,  178,
 /*   550 */   177,  178,  177,  178,  209,  210,  177,  178,  177,  178,
 /*   560 */    49,  177,  178,  177,  178,  177,  178,  157,   17,   19,
 /*   570 */   190,   21,   21,  102,  103,  104,  235,   66,   67,   68,
 /*   580 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  157,
 /*   590 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   600 */    14,  157,  157,  157,   18,  157,   25,  157,   22,  177,
 /*   610 */   178,  162,  157,  162,   33,  235,  157,   85,  235,  157,
 /*   620 */    20,  177,  178,  177,  178,  177,  178,  177,  178,  157,
 /*   630 */   157,  221,  177,  178,  169,   49,  177,  178,   57,  177,
 /*   640 */   178,  109,   92,   92,  169,  113,  197,  157,  197,  177,
 /*   650 */   178,  169,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   660 */    74,   75,   76,   77,  157,   79,   80,   81,   82,   83,
 /*   670 */    84,   85,   86,   87,   88,   14,  157,  169,  157,   20,
 /*   680 */   157,  157,  157,   22,  177,  178,  157,  157,  157,   20,
 /*   690 */   208,  157,   20,  157,  221,   95,  177,  178,  177,  178,
 /*   700 */   177,  178,  177,  178,   93,  240,  177,  178,  177,  178,
 /*   710 */    49,  177,  178,  177,  178,  240,  208,  157,  157,   70,
 /*   720 */   196,  126,  127,   50,   23,  239,  196,   66,   67,   68,
 /*   730 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   92,
 /*   740 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   750 */    14,   17,   93,  142,  143,   14,  196,  196,   22,  200,
 /*   760 */    21,   24,   23,   26,  115,  157,  207,   96,   37,   18,
 /*   770 */    18,   20,   20,  126,  101,  116,  105,   46,   18,   18,
 /*   780 */    20,   20,  199,  157,  115,   49,   18,   18,   20,   20,
 /*   790 */    18,   18,   20,   20,   18,  123,   20,   96,   18,  169,
 /*   800 */    20,  157,  211,   67,   68,   69,   70,   71,   72,   73,
 /*   810 */    74,   75,   76,   77,  157,   79,   80,   81,   82,   83,
 /*   820 */    84,   85,   86,   87,   88,   14,  186,  157,  186,  186,
 /*   830 */   243,  157,  157,   22,  157,  157,  157,   96,   14,   15,
 /*   840 */   157,   17,  157,  154,  180,   21,  201,  199,  114,  237,
 /*   850 */   237,  229,  229,  233,  202,    8,  180,  169,   34,  169,
 /*   860 */    49,  180,  180,  244,  180,  185,  152,  152,  152,   20,
 /*   870 */   184,  160,   22,  164,  164,  101,  179,  179,   47,   68,
 /*   880 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   65,
 /*   890 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   900 */   187,  179,  179,  197,  123,  202,  120,   83,   84,  121,
 /*   910 */   203,   14,   15,  118,   17,   91,   92,   93,   21,  122,
 /*   920 */    96,  204,   14,   15,  205,   17,   18,  206,  232,   21,
 /*   930 */   114,   34,  133,  158,   21,   26,  112,  219,  168,  219,
 /*   940 */   158,  101,   34,  117,  212,   17,  213,  212,  181,  219,
 /*   950 */   126,  127,  128,  129,  130,  131,  132,  213,  168,    5,
 /*   960 */     6,  219,   65,    9,   10,   11,  187,   16,  179,  155,
 /*   970 */   179,  179,   13,   65,  181,  156,  158,   13,  195,   25,
 /*   980 */    83,   84,   85,  158,  206,   17,  202,  223,   91,   92,
 /*   990 */    93,   83,   84,   96,   17,   14,   15,  161,   17,   91,
 /*  1000 */    92,   93,   21,  182,   96,  167,  206,    1,    7,  224,
 /*  1010 */    56,  182,   18,   22,   17,   34,   21,  223,   21,   21,
 /*  1020 */    21,   25,   35,  126,  127,  128,  129,  130,  131,  132,
 /*  1030 */    51,   17,  114,  114,  126,  127,  128,  129,  130,  131,
 /*  1040 */   132,  114,   17,  114,   18,   18,   65,   67,   96,  109,
 /*  1050 */    17,   41,  119,  119,   20,   20,  102,  103,  104,  116,
 /*  1060 */    17,  107,   65,   18,   83,   84,  112,  114,   18,   51,
 /*  1070 */    17,   17,   91,   92,   93,   18,   17,   96,   17,   51,
 /*  1080 */    83,   84,  100,  105,   12,   14,   12,  115,   15,   92,
 /*  1090 */    15,   25,   22,   96,   25,  141,   17,   20,   22,  114,
 /*  1100 */    20,   20,  144,   25,   22,   22,    3,  126,  127,  128,
 /*  1110 */   129,  130,  131,  132,    4,  245,  245,  245,  245,  245,
 /*  1120 */   245,  245,  245,  126,  127,  128,
};
#define YY_SHIFT_USE_DFLT (-66)
#define YY_SHIFT_MAX 312
static const short yy_shift_ofst[] = {
 /*     0 */   105,  954,  824,  -14,  824,  981,  981,  981,  138,  -48,
 /*    10 */   908,  981,  981,  981,  981,  -54,  315,  385,  186,  186,
 /*    20 */    61,  136,  211,  286,  361,  436,  511,  586,  661,  661,
 /*    30 */   661,  661,  661,  661,  661,  661,  661,  661,  661,  661,
 /*    40 */   661,  661,  661,  661,  661,  736,  811,  811,  897,  981,
 /*    50 */   981,  981,  981,  981,  981,  981,  981,  981,  981,  981,
 /*    60 */   981,  981,  981,  981,  981,  981,  981,  981,  981,  981,
 /*    70 */   981,  981,  981,  981,  981,  981,  981,  981,  981,  981,
 /*    80 */   981,  981,  -65,   66,  -43,  -43,  -37,  299,  300,  315,
 /*    90 */   315,  315,  315,  385,  -12,  -66,  -66,  -66,  997,   79,
 /*   100 */   -52,  366,   90,  307,  499,  550,  315,  550,  315,  315,
 /*   110 */   315,  315,  315,  315,  164,  315,  315,  397,  397,  -48,
 /*   120 */   -48,  -66,  -66,   26,   26,   93,  159,  284,  310,  359,
 /*   130 */   364,  296,  323,  321,  370,  326,  315,  532,  315,  315,
 /*   140 */   551,  315,  659,  315,  315,   -7,  659,  315,  315,  581,
 /*   150 */   581,  581,  315,  315,   -7,  315,   -7,  315,   -7,  611,
 /*   160 */   315,  235,  142,  347,  669,  595,  595,  647,  647,  172,
 /*   170 */   142,  142,  673,  142,  142,  600,  672,  385,  385,  649,
 /*   180 */   847,  847,  847,  849,  850,  850,  774,  774,  831,  774,
 /*   190 */   774,  -48,  781,  786,  788,  795,  797,  799,  816,  909,
 /*   200 */   913,  909,  816,  840,  826,  840,  826,  928,  909,  909,
 /*   210 */   913,  831,  774,  774,  774,  928,  951,  959,  816,  964,
 /*   220 */   816,  781,  797,  797,  968,  977,  968,  -66,  -66,  -66,
 /*   230 */   -66,  355,  471,  739,  737,  671,  731,  734,  751,  741,
 /*   240 */   752,  760,  761,  701,  768,  769,  772,  773,  776,  780,
 /*   250 */  1006, 1001,  994,  991,  995,  996,  998,  999,  987,  979,
 /*   260 */  1014,  918,  919,  927,  929, 1025, 1026, 1027,  952,  980,
 /*   270 */   940, 1033, 1010,  933, 1034,  934, 1035,  943, 1043, 1045,
 /*   280 */   953, 1050, 1018, 1053, 1057, 1054, 1059, 1028, 1061,  982,
 /*   290 */   978, 1072, 1071, 1073, 1074, 1075,  972, 1066, 1070, 1076,
 /*   300 */  1077, 1079, 1080, 1069, 1080, 1081, 1082,  985, 1078, 1083,
 /*   310 */   958, 1103, 1110,
};
#define YY_REDUCE_USE_DFLT (-165)
#define YY_REDUCE_MAX 230
static const short yy_reduce_ofst[] = {
 /*     0 */  -145,  -41,  144,   19,  -80,   84,   94,   89,  -63,  106,
 /*    10 */   -58,  -62,   16,  162,  156,   12,  167,  177,   23,  101,
 /*    20 */   191,  191,  191,  191,  191,  191,  191,  191,  191,  191,
 /*    30 */   191,  191,  191,  191,  191,  191,  191,  191,  191,  191,
 /*    40 */   191,  191,  191,  191,  191,  191,  191,  191,   86,  302,
 /*    50 */   304,  314,  316,  319,  357,  369,  371,  373,  375,  379,
 /*    60 */   381,  384,  386,  388,  432,  444,  446,  448,  450,  455,
 /*    70 */   459,  462,  472,  507,  519,  521,  523,  525,  529,  531,
 /*    80 */   534,  536,  191,  312,  191,  191,  191,  191,   43,  -67,
 /*    90 */   233,  341,  380,  227,  191,  191,  191,  191, -164,   72,
 /*   100 */   214,  290,  153,  -18,  391,  482,   13,  508,  383,  524,
 /*   110 */   530,  560,  269,  561,  -11,  410,  473,  465,  475,  449,
 /*   120 */   451,  559,  345,  -81,  -53,  -32,  140,  280,  194,  280,
 /*   130 */   280,  329,  387,  445,  490,  486,  608,  583,  490,  626,
 /*   140 */   630,  644,  591,  657,  670,  280,  591,  674,  675,  640,
 /*   150 */   642,  643,  677,  678,  280,  679,  280,  683,  280,  587,
 /*   160 */   685,  689,  664,  648,  645,  612,  613,  622,  623,  620,
 /*   170 */   676,  681,  680,  682,  684,  686,  652,  688,  690,  619,
 /*   180 */   714,  715,  716,  711,  709,  710,  697,  698,  713,  722,
 /*   190 */   723,  706,  703,  707,  717,  719,  721,  696,  775,  718,
 /*   200 */   770,  720,  782,  732,  733,  735,  744,  767,  730,  742,
 /*   210 */   790,  779,  789,  791,  792,  793,  814,  819,  818,  783,
 /*   220 */   825,  784,  778,  800,  764,  785,  794,  836,  838,  821,
 /*   230 */   829,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   496,  761,  727,  610,  761,  727,  761,  727,  761,  614,
 /*    10 */   761,  723,  727,  761,  761,  697,  761,  529,  737,  737,
 /*    20 */   645,  761,  761,  761,  761,  761,  761,  761,  646,  726,
 /*    30 */   722,  718,  720,  719,  647,  634,  643,  650,  626,  652,
 /*    40 */   653,  663,  664,  744,  745,  687,  703,  686,  761,  761,
 /*    50 */   761,  761,  761,  761,  761,  761,  761,  761,  761,  761,
 /*    60 */   761,  761,  761,  761,  761,  761,  761,  761,  761,  761,
 /*    70 */   761,  761,  761,  761,  761,  761,  761,  761,  761,  761,
 /*    80 */   761,  761,  689,  522,  688,  696,  690,  691,  583,  761,
 /*    90 */   761,  761,  761,  761,  692,  693,  704,  705,  761,  761,
 /*   100 */   750,  761,  761,  761,  496,  610,  761,  610,  761,  761,
 /*   110 */   761,  761,  761,  761,  761,  761,  761,  761,  761,  761,
 /*   120 */   761,  604,  614,  761,  761,  574,  761,  761,  761,  761,
 /*   130 */   761,  761,  761,  761,  761,  750,  761,  602,  761,  761,
 /*   140 */   531,  761,  612,  761,  761,  617,  618,  761,  761,  761,
 /*   150 */   761,  761,  761,  761,  512,  761,  593,  761,  657,  758,
 /*   160 */   761,  761,  637,  602,  611,  761,  761,  761,  761,  721,
 /*   170 */   637,  637,  553,  637,  637,  556,  649,  761,  761,  759,
 /*   180 */   501,  501,  501,  573,  520,  520,  585,  585,  570,  585,
 /*   190 */   585,  761,  649,  640,  642,  630,  644,  761,  619,  638,
 /*   200 */   761,  638,  619,  627,  629,  627,  629,  728,  638,  638,
 /*   210 */   761,  570,  585,  585,  585,  728,  510,  507,  619,  592,
 /*   220 */   619,  649,  644,  644,  665,  761,  665,  515,  539,  558,
 /*   230 */   558,  761,  761,  511,  761,  761,  761,  673,  761,  761,
 /*   240 */   761,  761,  761,  761,  761,  761,  761,  761,  761,  761,
 /*   250 */   761,  761,  761,  516,  761,  761,  761,  761,  761,  761,
 /*   260 */   761,  678,  674,  761,  675,  761,  761,  761,  761,  761,
 /*   270 */   596,  761,  761,  761,  631,  761,  641,  761,  761,  761,
 /*   280 */   761,  761,  761,  761,  761,  761,  761,  761,  761,  761,
 /*   290 */   761,  761,  761,  761,  761,  761,  761,  761,  761,  761,
 /*   300 */   654,  761,  655,  761,  656,  741,  761,  761,  761,  761,
 /*   310 */   761,  497,  761,  491,  494,  493,  495,  499,  502,  500,
 /*   320 */   503,  504,  505,  517,  518,  521,  519,  513,  538,  526,
 /*   330 */   527,  528,  540,  547,  548,  586,  587,  588,  589,  738,
 /*   340 */   739,  740,  549,  568,  571,  572,  550,  635,  636,  551,
 /*   350 */   600,  601,  670,  594,  595,  599,  672,  676,  677,  679,
 /*   360 */   680,  681,  525,  532,  533,  536,  537,  733,  735,  734,
 /*   370 */   736,  535,  534,  682,  685,  694,  695,  701,  707,  711,
 /*   380 */   699,  700,  702,  706,  708,  709,  710,  597,  598,  714,
 /*   390 */   716,  717,  712,  724,  725,  620,  715,  698,  632,  524,
 /*   400 */   639,  633,  603,  613,  622,  623,  624,  625,  608,  609,
 /*   410 */   615,  628,  668,  669,  616,  605,  606,  607,  713,  671,
 /*   420 */   683,  684,  552,  559,  560,  561,  564,  565,  566,  567,
 /*   430 */   562,  563,  729,  730,  732,  731,  554,  555,  569,  541,
 /*   440 */   542,  543,  544,  678,  545,  546,  530,  523,  575,  578,
 /*   450 */   557,  579,  580,  581,  582,  584,  576,  577,  514,  506,
 /*   460 */   508,  509,  590,  621,  591,  648,  651,  660,  661,  662,
 /*   470 */   666,  667,  658,  659,  751,  752,  746,  747,  748,  749,
 /*   480 */   742,  743,  753,  754,  755,  756,  760,  757,  498,  492,
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
 /* 172 */ "valueslist ::= LP RP",
 /* 173 */ "itemlist ::= itemlist COMMA expr",
 /* 174 */ "itemlist ::= expr",
 /* 175 */ "inscollist_opt ::=",
 /* 176 */ "inscollist_opt ::= LP RP",
 /* 177 */ "inscollist_opt ::= LP inscollist RP",
 /* 178 */ "inscollist ::= inscollist COMMA nm",
 /* 179 */ "inscollist ::= nm",
 /* 180 */ "expr ::= term",
 /* 181 */ "expr ::= LP expr RP",
 /* 182 */ "term ::= NULL",
 /* 183 */ "expr ::= ID",
 /* 184 */ "expr ::= JOIN_KW",
 /* 185 */ "expr ::= nm DOT nm",
 /* 186 */ "expr ::= nm DOT nm DOT nm",
 /* 187 */ "term ::= INTEGER|FLOAT|BLOB",
 /* 188 */ "term ::= STRING",
 /* 189 */ "expr ::= REGISTER",
 /* 190 */ "expr ::= VARIABLE",
 /* 191 */ "expr ::= VARIABLE1",
 /* 192 */ "expr ::= CAST LP expr AS typetoken RP",
 /* 193 */ "expr ::= ID LP distinct exprlist RP",
 /* 194 */ "expr ::= ID LP STAR RP",
 /* 195 */ "term ::= CTIME_KW",
 /* 196 */ "expr ::= expr AND expr",
 /* 197 */ "expr ::= expr OR expr",
 /* 198 */ "expr ::= expr LT|GT|GE|LE expr",
 /* 199 */ "expr ::= expr EQ|NE expr",
 /* 200 */ "expr ::= expr BITAND|BITOR|LSHIFT|RSHIFT expr",
 /* 201 */ "expr ::= expr PLUS|MINUS expr",
 /* 202 */ "expr ::= expr STAR|SLASH|REM expr",
 /* 203 */ "expr ::= expr CONCAT expr",
 /* 204 */ "likeop ::= LIKE_KW",
 /* 205 */ "likeop ::= NOT LIKE_KW",
 /* 206 */ "escape ::= ESCAPE expr",
 /* 207 */ "escape ::=",
 /* 208 */ "expr ::= expr likeop expr escape",
 /* 209 */ "expr ::= expr ISNULL|NOTNULL",
 /* 210 */ "expr ::= expr IS NULL",
 /* 211 */ "expr ::= expr NOT NULL",
 /* 212 */ "expr ::= expr IS NOT NULL",
 /* 213 */ "expr ::= NOT|BITNOT expr",
 /* 214 */ "expr ::= MINUS expr",
 /* 215 */ "expr ::= PLUS expr",
 /* 216 */ "between_op ::= BETWEEN",
 /* 217 */ "between_op ::= NOT BETWEEN",
 /* 218 */ "between_elem ::= INTEGER|STRING",
 /* 219 */ "expr ::= expr between_op between_elem AND between_elem",
 /* 220 */ "in_op ::= IN",
 /* 221 */ "in_op ::= NOT IN",
 /* 222 */ "expr ::= expr in_op LP exprlist RP",
 /* 223 */ "expr ::= LP select RP",
 /* 224 */ "expr ::= expr in_op LP select RP",
 /* 225 */ "expr ::= expr in_op nm dbnm",
 /* 226 */ "expr ::= EXISTS LP select RP",
 /* 227 */ "expr ::= CASE case_operand case_exprlist case_else END",
 /* 228 */ "case_exprlist ::= case_exprlist WHEN expr THEN expr",
 /* 229 */ "case_exprlist ::= WHEN expr THEN expr",
 /* 230 */ "case_else ::= ELSE expr",
 /* 231 */ "case_else ::=",
 /* 232 */ "case_operand ::= expr",
 /* 233 */ "case_operand ::=",
 /* 234 */ "exprlist ::= exprlist COMMA expritem",
 /* 235 */ "exprlist ::= expritem",
 /* 236 */ "expritem ::= expr",
 /* 237 */ "expritem ::=",
 /* 238 */ "idxlist_opt ::=",
 /* 239 */ "idxlist_opt ::= LP idxlist RP",
 /* 240 */ "idxlist ::= idxlist COMMA idxitem collate sortorder",
 /* 241 */ "idxlist ::= idxitem collate sortorder",
 /* 242 */ "idxitem ::= nm",
 /* 243 */ "plus_num ::= plus_opt number",
 /* 244 */ "minus_num ::= MINUS number",
 /* 245 */ "number ::= INTEGER|FLOAT",
 /* 246 */ "plus_opt ::= PLUS",
 /* 247 */ "plus_opt ::=",
 /* 248 */ "raisetype ::= ROLLBACK",
 /* 249 */ "raisetype ::= ABORT",
 /* 250 */ "raisetype ::= FAIL",
 /* 251 */ "cmd ::= SET variable_assignment_list",
 /* 252 */ "cmd ::= SET NAMES ids",
 /* 253 */ "cmd ::= SET CHARACTER SET ids",
 /* 254 */ "variable_assignment_list ::= variable_assignment_list COMMA scope_qualifier user_var_name EQ expr",
 /* 255 */ "variable_assignment_list ::= scope_qualifier user_var_name EQ expr",
 /* 256 */ "scope_qualifier ::= GLOBAL",
 /* 257 */ "scope_qualifier ::= LOCAL",
 /* 258 */ "scope_qualifier ::= SESSION",
 /* 259 */ "scope_qualifier ::= VARIABLE1 DOT",
 /* 260 */ "scope_qualifier ::=",
 /* 261 */ "user_var_name ::= ids",
 /* 262 */ "user_var_name ::= VARIABLE",
 /* 263 */ "cmd ::= show_databes",
 /* 264 */ "cmd ::= show_tables",
 /* 265 */ "show_databes ::= SHOW DATABASES|SCHEMAS",
 /* 266 */ "show_tables ::= SHOW full_keyword TABLES from_db",
 /* 267 */ "full_keyword ::= JOIN_KW",
 /* 268 */ "full_keyword ::=",
 /* 269 */ "from_db ::=",
 /* 270 */ "from_db ::= FROM|IN nm",
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
#line 1153 "parse.c"
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
#line 668 "parse.y"
{sqlite3ExprDelete((yypminor->yy342));}
#line 1168 "parse.c"
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
#line 912 "parse.y"
{sqlite3ExprListDelete((yypminor->yy462));}
#line 1183 "parse.c"
      break;
    case 196:
    case 201:
    case 209:
    case 210:
#line 518 "parse.y"
{sqlite3SrcListDelete((yypminor->yy287));}
#line 1191 "parse.c"
      break;
    case 206:
#line 579 "parse.y"
{
  sqlite3ExprDelete((yypminor->yy474).pLimit);
  sqlite3ExprDelete((yypminor->yy474).pOffset);
}
#line 1199 "parse.c"
      break;
    case 213:
    case 216:
    case 223:
#line 535 "parse.y"
{sqlite3IdListDelete((yypminor->yy440));}
#line 1206 "parse.c"
      break;
    case 224:
#line 639 "parse.y"
{sqlite3ValuesListDelete((yypminor->yy49));}
#line 1211 "parse.c"
      break;
    case 238:
#line 1128 "parse.y"
{ sqlite3ExprListDelete((yypminor->yy462)); }
#line 1216 "parse.c"
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
#line 1368 "parse.c"
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
  { 224, 2 },
  { 225, 3 },
  { 225, 1 },
  { 223, 0 },
  { 223, 2 },
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
#line 1717 "parse.c"
        break;
      case 6:
#line 101 "parse.y"
{ sqlite3BeginParse(pParse, 0); }
#line 1722 "parse.c"
        break;
      case 7:
#line 103 "parse.y"
{ sqlite3BeginParse(pParse, 1); }
#line 1727 "parse.c"
        break;
      case 8:
#line 104 "parse.y"
{ sqlite3BeginParse(pParse, 2); }
#line 1732 "parse.c"
        break;
      case 9:
#line 111 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_BEGIN);}
#line 1737 "parse.c"
        break;
      case 10:
#line 112 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_START);}
#line 1742 "parse.c"
        break;
      case 13:
#line 123 "parse.y"
{sqlite3CommitTransaction(pParse);}
#line 1747 "parse.c"
        break;
      case 14:
#line 125 "parse.y"
{sqlite3RollbackTransaction(pParse);}
#line 1752 "parse.c"
        break;
      case 16:
#line 130 "parse.y"
{
   sqlite3StartTable(pParse, 0, 0, 0, 0, 0);
}
#line 1759 "parse.c"
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
      case 216:
      case 220:
#line 135 "parse.y"
{yygotominor.yy32 = 0;}
#line 1774 "parse.c"
        break;
      case 18:
      case 19:
      case 67:
      case 81:
      case 101:
      case 110:
      case 217:
      case 221:
#line 136 "parse.y"
{yygotominor.yy32 = 1;}
#line 1786 "parse.c"
        break;
      case 21:
#line 142 "parse.y"
{
  //sqlite3EndTable(pParse,&X,&Y,0);
}
#line 1793 "parse.c"
        break;
      case 22:
#line 145 "parse.y"
{
  sqlite3EndTable(pParse,0,0,0);
  //sqlite3SelectDelete(S);
  yy_destructor(162,&yymsp[0].minor);
}
#line 1802 "parse.c"
        break;
      case 32:
#line 167 "parse.y"
{
  //A.z = X.z;
  //A.n = (pParse->sLastToken.z-X.z) + pParse->sLastToken.n;
}
#line 1810 "parse.c"
        break;
      case 33:
#line 171 "parse.y"
{
  //sqlite3AddColumn(pParse,&X);
  //A = X;
}
#line 1818 "parse.c"
        break;
      case 34:
      case 35:
      case 36:
      case 37:
      case 38:
      case 245:
#line 181 "parse.y"
{yygotominor.yy308 = yymsp[0].minor.yy0;}
#line 1828 "parse.c"
        break;
      case 40:
#line 240 "parse.y"
{ /*sqlite3AddColumnType(pParse,&X);*/ }
#line 1833 "parse.c"
        break;
      case 41:
      case 44:
      case 118:
      case 119:
      case 130:
      case 149:
      case 242:
      case 243:
      case 244:
#line 241 "parse.y"
{yygotominor.yy308 = yymsp[0].minor.yy308;}
#line 1846 "parse.c"
        break;
      case 42:
#line 242 "parse.y"
{
  yygotominor.yy308.z = yymsp[-3].minor.yy308.z;
  yygotominor.yy308.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-3].minor.yy308.z;
}
#line 1854 "parse.c"
        break;
      case 43:
#line 246 "parse.y"
{
  yygotominor.yy308.z = yymsp[-5].minor.yy308.z;
  yygotominor.yy308.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-5].minor.yy308.z;
}
#line 1862 "parse.c"
        break;
      case 45:
#line 252 "parse.y"
{yygotominor.yy308.z=yymsp[-1].minor.yy308.z; yygotominor.yy308.n=yymsp[0].minor.yy308.n+(yymsp[0].minor.yy308.z-yymsp[-1].minor.yy308.z);}
#line 1867 "parse.c"
        break;
      case 46:
#line 254 "parse.y"
{ yygotominor.yy32 = atoi((char*)yymsp[0].minor.yy308.z); }
#line 1872 "parse.c"
        break;
      case 47:
#line 255 "parse.y"
{ yygotominor.yy32 = -atoi((char*)yymsp[0].minor.yy308.z); }
#line 1877 "parse.c"
        break;
      case 52:
#line 264 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/   yy_destructor(177,&yymsp[0].minor);
}
#line 1883 "parse.c"
        break;
      case 53:
#line 265 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/ }
#line 1888 "parse.c"
        break;
      case 54:
#line 266 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/  yy_destructor(177,&yymsp[0].minor);
}
#line 1894 "parse.c"
        break;
      case 55:
#line 267 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_UMINUS, X, 0, 0);
  //sqlite3AddDefaultValue(pParse,p);
  yy_destructor(177,&yymsp[0].minor);
}
#line 1903 "parse.c"
        break;
      case 56:
#line 271 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_STRING, 0, 0, &X);
  //sqlite3AddDefaultValue(pParse,p);
}
#line 1911 "parse.c"
        break;
      case 59:
#line 281 "parse.y"
{/*sqlite3AddNotNull(pParse, R);*/}
#line 1916 "parse.c"
        break;
      case 60:
#line 283 "parse.y"
{/*sqlite3AddPrimaryKey(pParse,0,R,I,Z);*/}
#line 1921 "parse.c"
        break;
      case 61:
#line 284 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,0,R,0,0,0,0);*/}
#line 1926 "parse.c"
        break;
      case 62:
#line 285 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,X);*/  sqlite3ExprDelete(yymsp[-1].minor.yy342); }
#line 1931 "parse.c"
        break;
      case 63:
#line 287 "parse.y"
{/*sqlite3CreateForeignKey(pParse,0,&T,TA,R);*/ sqlite3ExprListDelete(yymsp[-1].minor.yy462); }
#line 1936 "parse.c"
        break;
      case 64:
#line 288 "parse.y"
{/*sqlite3DeferForeignKey(pParse,D);*/}
#line 1941 "parse.c"
        break;
      case 65:
#line 289 "parse.y"
{/*sqlite3AddCollateType(pParse, (char*)C.z, C.n);*/}
#line 1946 "parse.c"
        break;
      case 68:
#line 302 "parse.y"
{ yygotominor.yy32 = OE_Restrict * 0x010101; }
#line 1951 "parse.c"
        break;
      case 69:
#line 303 "parse.y"
{ yygotominor.yy32 = (yymsp[-1].minor.yy32 & yymsp[0].minor.yy47.mask) | yymsp[0].minor.yy47.value; }
#line 1956 "parse.c"
        break;
      case 70:
#line 305 "parse.y"
{ yygotominor.yy47.value = 0;     yygotominor.yy47.mask = 0x000000; }
#line 1961 "parse.c"
        break;
      case 71:
#line 306 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32;     yygotominor.yy47.mask = 0x0000ff; }
#line 1966 "parse.c"
        break;
      case 72:
#line 307 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32<<8;  yygotominor.yy47.mask = 0x00ff00; }
#line 1971 "parse.c"
        break;
      case 73:
#line 308 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32<<16; yygotominor.yy47.mask = 0xff0000; }
#line 1976 "parse.c"
        break;
      case 74:
#line 310 "parse.y"
{ yygotominor.yy32 = OE_SetNull; }
#line 1981 "parse.c"
        break;
      case 75:
#line 311 "parse.y"
{ yygotominor.yy32 = OE_SetDflt; }
#line 1986 "parse.c"
        break;
      case 76:
#line 312 "parse.y"
{ yygotominor.yy32 = OE_Cascade; }
#line 1991 "parse.c"
        break;
      case 77:
#line 313 "parse.y"
{ yygotominor.yy32 = OE_Restrict; }
#line 1996 "parse.c"
        break;
      case 78:
      case 79:
      case 94:
      case 96:
      case 97:
#line 315 "parse.y"
{yygotominor.yy32 = yymsp[0].minor.yy32;}
#line 2005 "parse.c"
        break;
      case 89:
#line 334 "parse.y"
{ sqlite3ExprListDelete(yymsp[-3].minor.yy462); }
#line 2010 "parse.c"
        break;
      case 90:
#line 336 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,yymsp[-2].minor.yy462,R,0,0,0,0);*/ sqlite3ExprListDelete(yymsp[-2].minor.yy462);}
#line 2015 "parse.c"
        break;
      case 91:
#line 337 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,yymsp[-2].minor.yy342);*/ sqlite3ExprDelete(yymsp[-2].minor.yy342);}
#line 2020 "parse.c"
        break;
      case 92:
#line 339 "parse.y"
{ 
        sqlite3ExprListDelete(yymsp[-6].minor.yy462);
        sqlite3ExprListDelete(yymsp[-2].minor.yy462);
 }
#line 2028 "parse.c"
        break;
      case 95:
#line 354 "parse.y"
{yygotominor.yy32 = OE_Default;}
#line 2033 "parse.c"
        break;
      case 98:
#line 359 "parse.y"
{yygotominor.yy32 = OE_Ignore;}
#line 2038 "parse.c"
        break;
      case 99:
      case 169:
#line 360 "parse.y"
{yygotominor.yy32 = OE_Replace;}
#line 2044 "parse.c"
        break;
      case 100:
#line 364 "parse.y"
{
  sqlite3DropTable(pParse, yymsp[0].minor.yy287, 0, yymsp[-1].minor.yy32);
}
#line 2051 "parse.c"
        break;
      case 103:
#line 384 "parse.y"
{
  sqlite3Select(pParse, yymsp[0].minor.yy149, SRT_Callback, 0, 0, 0, 0, 0);
  // sqlite3SelectDelete(yymsp[0].minor.yy149);
}
#line 2059 "parse.c"
        break;
      case 104:
      case 127:
#line 394 "parse.y"
{yygotominor.yy149 = yymsp[0].minor.yy149;}
#line 2065 "parse.c"
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
#line 2076 "parse.c"
        break;
      case 106:
      case 108:
#line 404 "parse.y"
{yygotominor.yy32 = yymsp[0].major;}
#line 2082 "parse.c"
        break;
      case 107:
#line 405 "parse.y"
{yygotominor.yy32 = TK_ALL;}
#line 2087 "parse.c"
        break;
      case 109:
#line 409 "parse.y"
{
  yygotominor.yy149 = sqlite3SelectNew(yymsp[-6].minor.yy462,yymsp[-5].minor.yy287,yymsp[-4].minor.yy342,yymsp[-3].minor.yy462,yymsp[-2].minor.yy342,yymsp[-1].minor.yy462,yymsp[-7].minor.yy32,yymsp[0].minor.yy474.pLimit,yymsp[0].minor.yy474.pOffset);
}
#line 2094 "parse.c"
        break;
      case 113:
      case 239:
#line 430 "parse.y"
{yygotominor.yy462 = yymsp[-1].minor.yy462;}
#line 2100 "parse.c"
        break;
      case 114:
      case 140:
      case 150:
      case 238:
#line 431 "parse.y"
{yygotominor.yy462 = 0;}
#line 2108 "parse.c"
        break;
      case 115:
#line 432 "parse.y"
{
   yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-2].minor.yy462,yymsp[-1].minor.yy342,yymsp[0].minor.yy308.n?&yymsp[0].minor.yy308:0);
}
#line 2115 "parse.c"
        break;
      case 116:
#line 435 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-1].minor.yy462, sqlite3Expr(TK_ALL, 0, 0, 0), 0);
}
#line 2122 "parse.c"
        break;
      case 117:
#line 438 "parse.y"
{
  Expr *pRight = sqlite3Expr(TK_ALL, 0, 0, 0);
  Expr *pLeft = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-3].minor.yy462, sqlite3Expr(TK_DOT, pLeft, pRight, 0), 0);
}
#line 2131 "parse.c"
        break;
      case 120:
#line 450 "parse.y"
{yygotominor.yy308.n = 0;}
#line 2136 "parse.c"
        break;
      case 121:
#line 462 "parse.y"
{yygotominor.yy287 = sqliteMalloc(sizeof(*yygotominor.yy287));}
#line 2141 "parse.c"
        break;
      case 122:
#line 463 "parse.y"
{yygotominor.yy287 = yymsp[0].minor.yy287;}
#line 2146 "parse.c"
        break;
      case 123:
#line 468 "parse.y"
{
   yygotominor.yy287 = yymsp[-1].minor.yy287;
   if( yygotominor.yy287 && yygotominor.yy287->nSrc>0 ) yygotominor.yy287->a[yygotominor.yy287->nSrc-1].jointype = yymsp[0].minor.yy32;
}
#line 2154 "parse.c"
        break;
      case 124:
#line 472 "parse.y"
{yygotominor.yy287 = 0;}
#line 2159 "parse.c"
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
#line 2175 "parse.c"
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
#line 2192 "parse.c"
        break;
      case 128:
#line 508 "parse.y"
{
     yygotominor.yy149 = sqlite3SelectNew(0,yymsp[0].minor.yy287,0,0,0,0,0,0,0);
  }
#line 2199 "parse.c"
        break;
      case 129:
#line 514 "parse.y"
{yygotominor.yy308.z=0; yygotominor.yy308.n=0;}
#line 2204 "parse.c"
        break;
      case 131:
#line 519 "parse.y"
{yygotominor.yy287 = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy308,&yymsp[0].minor.yy308);}
#line 2209 "parse.c"
        break;
      case 132:
#line 523 "parse.y"
{ yygotominor.yy32 = JT_INNER; }
#line 2214 "parse.c"
        break;
      case 133:
#line 524 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-1].minor.yy0,0,0); }
#line 2219 "parse.c"
        break;
      case 134:
#line 525 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-2].minor.yy0,&yymsp[-1].minor.yy308,0); }
#line 2224 "parse.c"
        break;
      case 135:
#line 527 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-3].minor.yy0,&yymsp[-2].minor.yy308,&yymsp[-1].minor.yy308); }
#line 2229 "parse.c"
        break;
      case 136:
      case 144:
      case 153:
      case 160:
      case 180:
      case 206:
      case 230:
      case 232:
      case 236:
#line 531 "parse.y"
{yygotominor.yy342 = yymsp[0].minor.yy342;}
#line 2242 "parse.c"
        break;
      case 137:
      case 152:
      case 159:
      case 207:
      case 231:
      case 233:
      case 237:
#line 532 "parse.y"
{yygotominor.yy342 = 0;}
#line 2253 "parse.c"
        break;
      case 138:
      case 177:
#line 536 "parse.y"
{yygotominor.yy440 = yymsp[-1].minor.yy440;}
#line 2259 "parse.c"
        break;
      case 139:
      case 175:
      case 176:
#line 537 "parse.y"
{yygotominor.yy440 = 0;}
#line 2266 "parse.c"
        break;
      case 141:
      case 151:
#line 548 "parse.y"
{yygotominor.yy462 = yymsp[0].minor.yy462;}
#line 2272 "parse.c"
        break;
      case 142:
#line 549 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462,yymsp[-2].minor.yy342,yymsp[-1].minor.yy308.n>0?&yymsp[-1].minor.yy308:0);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2280 "parse.c"
        break;
      case 143:
#line 553 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[-2].minor.yy342,yymsp[-1].minor.yy308.n>0?&yymsp[-1].minor.yy308:0);
  if( yygotominor.yy462 && yygotominor.yy462->a ) yygotominor.yy462->a[0].sortOrder = yymsp[0].minor.yy32;
}
#line 2288 "parse.c"
        break;
      case 145:
      case 147:
#line 562 "parse.y"
{yygotominor.yy32 = SQLITE_SO_ASC;}
#line 2294 "parse.c"
        break;
      case 146:
#line 563 "parse.y"
{yygotominor.yy32 = SQLITE_SO_DESC;}
#line 2299 "parse.c"
        break;
      case 148:
#line 565 "parse.y"
{yygotominor.yy308.z = 0; yygotominor.yy308.n = 0;}
#line 2304 "parse.c"
        break;
      case 154:
#line 583 "parse.y"
{yygotominor.yy474.pLimit = 0; yygotominor.yy474.pOffset = 0;}
#line 2309 "parse.c"
        break;
      case 155:
#line 584 "parse.y"
{yygotominor.yy474.pLimit = yymsp[0].minor.yy342; yygotominor.yy474.pOffset = 0;}
#line 2314 "parse.c"
        break;
      case 156:
#line 586 "parse.y"
{yygotominor.yy474.pLimit = yymsp[-2].minor.yy342; yygotominor.yy474.pOffset = yymsp[0].minor.yy342;}
#line 2319 "parse.c"
        break;
      case 157:
#line 588 "parse.y"
{yygotominor.yy474.pOffset = yymsp[-2].minor.yy342; yygotominor.yy474.pLimit = yymsp[0].minor.yy342;}
#line 2324 "parse.c"
        break;
      case 158:
#line 592 "parse.y"
{sqlite3DeleteFrom(pParse,yymsp[-2].minor.yy287,yymsp[-1].minor.yy342, yymsp[0].minor.yy474.pLimit, yymsp[0].minor.yy474.pOffset);}
#line 2329 "parse.c"
        break;
      case 161:
#line 604 "parse.y"
{sqlite3Update(pParse,yymsp[-4].minor.yy287,yymsp[-2].minor.yy462,yymsp[-1].minor.yy342,OE_Default, yymsp[0].minor.yy474.pLimit, yymsp[0].minor.yy474.pOffset);}
#line 2334 "parse.c"
        break;
      case 162:
#line 610 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462,yymsp[0].minor.yy342,&yymsp[-2].minor.yy308);}
#line 2339 "parse.c"
        break;
      case 163:
#line 611 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[0].minor.yy342,&yymsp[-2].minor.yy308);}
#line 2344 "parse.c"
        break;
      case 164:
#line 620 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, 0, yymsp[0].minor.yy49, 0, yymsp[-2].minor.yy440, yymsp[-5].minor.yy32);}
#line 2349 "parse.c"
        break;
      case 165:
#line 624 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, yymsp[0].minor.yy462, 0, 0, yymsp[-2].minor.yy440, yymsp[-5].minor.yy32);}
#line 2354 "parse.c"
        break;
      case 166:
#line 628 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, yymsp[0].minor.yy462, 0, 0, yymsp[-2].minor.yy440, yymsp[-4].minor.yy32);}
#line 2359 "parse.c"
        break;
      case 167:
#line 631 "parse.y"
{sqlite3Insert(pParse, yymsp[-2].minor.yy287, 0, 0, yymsp[0].minor.yy149, yymsp[-1].minor.yy440, yymsp[-4].minor.yy32);}
#line 2364 "parse.c"
        break;
      case 168:
#line 635 "parse.y"
{ yygotominor.yy32 = OE_Default; }
#line 2369 "parse.c"
        break;
      case 170:
#line 641 "parse.y"
{ yygotominor.yy49 = sqlite3ValuesListAppend(yymsp[-4].minor.yy49, yymsp[-1].minor.yy462);}
#line 2374 "parse.c"
        break;
      case 171:
#line 642 "parse.y"
{ yygotominor.yy49 = sqlite3ValuesListAppend(0, yymsp[-1].minor.yy462); }
#line 2379 "parse.c"
        break;
      case 172:
#line 643 "parse.y"
{ yygotominor.yy49 = 0; }
#line 2384 "parse.c"
        break;
      case 173:
      case 234:
#line 648 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-2].minor.yy462,yymsp[0].minor.yy342,0);}
#line 2390 "parse.c"
        break;
      case 174:
      case 235:
#line 649 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[0].minor.yy342,0);}
#line 2396 "parse.c"
        break;
      case 178:
#line 659 "parse.y"
{yygotominor.yy440 = sqlite3IdListAppend(yymsp[-2].minor.yy440,&yymsp[0].minor.yy308);}
#line 2401 "parse.c"
        break;
      case 179:
#line 660 "parse.y"
{yygotominor.yy440 = sqlite3IdListAppend(0,&yymsp[0].minor.yy308);}
#line 2406 "parse.c"
        break;
      case 181:
#line 671 "parse.y"
{yygotominor.yy342 = yymsp[-1].minor.yy342; sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0); }
#line 2411 "parse.c"
        break;
      case 182:
      case 187:
      case 188:
#line 672 "parse.y"
{yygotominor.yy342 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0);}
#line 2418 "parse.c"
        break;
      case 183:
      case 184:
#line 673 "parse.y"
{yygotominor.yy342 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy0);}
#line 2424 "parse.c"
        break;
      case 185:
#line 675 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy308);
  yygotominor.yy342 = sqlite3Expr(TK_DOT, temp1, temp2, 0);
}
#line 2433 "parse.c"
        break;
      case 186:
#line 680 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-4].minor.yy308);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  Expr *temp3 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy308);
  Expr *temp4 = sqlite3Expr(TK_DOT, temp2, temp3, 0);
  yygotominor.yy342 = sqlite3Expr(TK_DOT, temp1, temp4, 0);
}
#line 2444 "parse.c"
        break;
      case 189:
#line 689 "parse.y"
{yygotominor.yy342 = sqlite3RegisterExpr(pParse, &yymsp[0].minor.yy0);}
#line 2449 "parse.c"
        break;
      case 190:
      case 191:
#line 690 "parse.y"
{
  Token *pToken = &yymsp[0].minor.yy0;
  Expr *pExpr = yygotominor.yy342 = sqlite3Expr(TK_VARIABLE, 0, 0, pToken);
  //sqlite3ExprAssignVarNumber(pParse, pExpr);
}
#line 2459 "parse.c"
        break;
      case 192:
#line 701 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_CAST, yymsp[-3].minor.yy342, 0, &yymsp[-1].minor.yy308);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-5].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2467 "parse.c"
        break;
      case 193:
#line 706 "parse.y"
{
  yygotominor.yy342 = sqlite3ExprFunction(yymsp[-1].minor.yy462, &yymsp[-4].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-4].minor.yy0,&yymsp[0].minor.yy0);
  if( yymsp[-2].minor.yy32 && yygotominor.yy342 ){
    yygotominor.yy342->flags |= EP_Distinct;
  }
}
#line 2478 "parse.c"
        break;
      case 194:
#line 713 "parse.y"
{
  yygotominor.yy342 = sqlite3ExprFunction(0, &yymsp[-3].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2486 "parse.c"
        break;
      case 195:
#line 717 "parse.y"
{
  /* The CURRENT_TIME, CURRENT_DATE, and CURRENT_TIMESTAMP values are
  ** treated as functions that return constants */
  yygotominor.yy342 = sqlite3ExprFunction(0,&yymsp[0].minor.yy0);
  if( yygotominor.yy342 ) yygotominor.yy342->op = TK_CONST_FUNC;  
}
#line 2496 "parse.c"
        break;
      case 196:
      case 197:
      case 198:
      case 199:
      case 200:
      case 201:
      case 202:
      case 203:
#line 723 "parse.y"
{yygotominor.yy342 = sqlite3Expr(yymsp[-1].major, yymsp[-2].minor.yy342, yymsp[0].minor.yy342, 0);}
#line 2508 "parse.c"
        break;
      case 204:
#line 733 "parse.y"
{yygotominor.yy118.eOperator = yymsp[0].minor.yy0; yygotominor.yy118.not = 0;}
#line 2513 "parse.c"
        break;
      case 205:
#line 734 "parse.y"
{yygotominor.yy118.eOperator = yymsp[0].minor.yy0; yygotominor.yy118.not = 1;}
#line 2518 "parse.c"
        break;
      case 208:
#line 739 "parse.y"
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
#line 2534 "parse.c"
        break;
      case 209:
#line 752 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(yymsp[0].major, yymsp[-1].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2542 "parse.c"
        break;
      case 210:
#line 756 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_ISNULL, yymsp[-2].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2550 "parse.c"
        break;
      case 211:
#line 760 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_NOTNULL, yymsp[-2].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2558 "parse.c"
        break;
      case 212:
#line 764 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_NOTNULL, yymsp[-3].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-3].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2566 "parse.c"
        break;
      case 213:
#line 768 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(yymsp[-1].major, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2574 "parse.c"
        break;
      case 214:
#line 772 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_UMINUS, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2582 "parse.c"
        break;
      case 215:
#line 776 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_UPLUS, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2590 "parse.c"
        break;
      case 218:
#line 787 "parse.y"
{ yygotominor.yy342 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0); }
#line 2595 "parse.c"
        break;
      case 219:
#line 790 "parse.y"
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
#line 2611 "parse.c"
        break;
      case 222:
#line 806 "parse.y"
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
#line 2625 "parse.c"
        break;
      case 223:
#line 816 "parse.y"
{
    yygotominor.yy342 = sqlite3Expr(TK_SELECT, 0, 0, 0);
    if( yygotominor.yy342 ){
      yygotominor.yy342->pSelect = yymsp[-1].minor.yy149;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy149);
    }
    sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0);
  }
#line 2638 "parse.c"
        break;
      case 224:
#line 825 "parse.y"
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
#line 2652 "parse.c"
        break;
      case 225:
#line 835 "parse.y"
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
#line 2667 "parse.c"
        break;
      case 226:
#line 846 "parse.y"
{
    Expr *p = yygotominor.yy342 = sqlite3Expr(TK_EXISTS, 0, 0, 0);
    if( p ){
      p->pSelect = yymsp[-1].minor.yy149;
      sqlite3ExprSpan(p,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy149);
    }
  }
#line 2680 "parse.c"
        break;
      case 227:
#line 858 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_CASE, yymsp[-3].minor.yy342, yymsp[-1].minor.yy342, 0);
  if( yygotominor.yy342 ){
    yygotominor.yy342->pList = yymsp[-2].minor.yy462;
  }else{
    sqlite3ExprListDelete(yymsp[-2].minor.yy462);
  }
  sqlite3ExprSpan(yygotominor.yy342, &yymsp[-4].minor.yy0, &yymsp[0].minor.yy0);
}
#line 2693 "parse.c"
        break;
      case 228:
#line 869 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462, yymsp[-2].minor.yy342, 0);
  yygotominor.yy462 = sqlite3ExprListAppend(yygotominor.yy462, yymsp[0].minor.yy342, 0);
}
#line 2701 "parse.c"
        break;
      case 229:
#line 873 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(0, yymsp[-2].minor.yy342, 0);
  yygotominor.yy462 = sqlite3ExprListAppend(yygotominor.yy462, yymsp[0].minor.yy342, 0);
}
#line 2709 "parse.c"
        break;
      case 240:
#line 917 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy308.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy308.z, yymsp[-1].minor.yy308.n);
  }
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462, p, &yymsp[-2].minor.yy308);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2722 "parse.c"
        break;
      case 241:
#line 926 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy308.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy308.z, yymsp[-1].minor.yy308.n);
  }
  yygotominor.yy462 = sqlite3ExprListAppend(0, p, &yymsp[-2].minor.yy308);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2735 "parse.c"
        break;
      case 248:
#line 1057 "parse.y"
{yygotominor.yy32 = OE_Rollback;}
#line 2740 "parse.c"
        break;
      case 249:
#line 1058 "parse.y"
{yygotominor.yy32 = OE_Abort;}
#line 2745 "parse.c"
        break;
      case 250:
#line 1059 "parse.y"
{yygotominor.yy32 = OE_Fail;}
#line 2750 "parse.c"
        break;
      case 251:
#line 1115 "parse.y"
{
    sqlite3SetStatement(pParse, yymsp[0].minor.yy462, 0, SQLTYPE_SET);
}
#line 2757 "parse.c"
        break;
      case 252:
#line 1119 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy308, SQLTYPE_SET_NAMES);   
}
#line 2764 "parse.c"
        break;
      case 253:
#line 1123 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy308, SQLTYPE_SET_CHARACTER_SET);
}
#line 2771 "parse.c"
        break;
      case 254:
#line 1129 "parse.y"
{
    yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-5].minor.yy462, yymsp[0].minor.yy342, &yymsp[-2].minor.yy308);
}
#line 2778 "parse.c"
        break;
      case 255:
#line 1133 "parse.y"
{
    yygotominor.yy462 = sqlite3ExprListAppend(0, yymsp[0].minor.yy342, &yymsp[-2].minor.yy308);                         
}
#line 2785 "parse.c"
        break;
      case 259:
#line 1141 "parse.y"
{ sqlite3CheckSetScope(pParse, &yymsp[-1].minor.yy0); }
#line 2790 "parse.c"
        break;
      case 261:
#line 1145 "parse.y"
{ yygotominor.yy308 = yymsp[0].minor.yy308; }
#line 2795 "parse.c"
        break;
      case 262:
#line 1146 "parse.y"
{ yygotominor.yy308 = yymsp[0].minor.yy0; }
#line 2800 "parse.c"
        break;
      case 265:
#line 1152 "parse.y"
{
    sqlite3ShowStatement(pParse, yymsp[0].major);
}
#line 2807 "parse.c"
        break;
      case 266:
#line 1156 "parse.y"
{
    sqlite3ShowStatement(pParse, yymsp[-1].major);
}
#line 2814 "parse.c"
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
#line 2881 "parse.c"
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
