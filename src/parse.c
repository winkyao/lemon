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
#define YYNSTATE 493
#define YYNRULE 272
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
 /*     0 */   232,  372,  167,  144,  334,  364,   57,   56,   56,   56,
 /*    10 */    56,  438,   58,   58,   58,   58,   59,   59,   60,   60,
 /*    20 */    60,   61,   63,   58,   58,   58,   58,   59,   59,   60,
 /*    30 */    60,   60,   61,  377,   58,   58,   58,   58,   59,   59,
 /*    40 */    60,   60,   60,   61,   59,   59,   60,   60,   60,   61,
 /*    50 */    55,   53,  240,  385,  388,  382,  382,   57,   56,   56,
 /*    60 */    56,   56,  221,   58,   58,   58,   58,   59,   59,   60,
 /*    70 */    60,   60,   61,  232,  164,  236,  364,   72,  271,   57,
 /*    80 */   390,  390,   99,  308,   61,  211,  236,  449,  178,  309,
 /*    90 */   478,  479,  480,  329,  444,   18,  211,  330,  441,  312,
 /*   100 */   317,  227,    2,  162,  127,  438,  377,   62,  399,  168,
 /*   110 */    52,  129,  157,  316,  313,  766,  105,  492,  126,  459,
 /*   120 */     1,  458,  331,   55,   53,  240,  385,  388,  382,  382,
 /*   130 */    57,   56,   56,   56,   56,  446,   58,   58,   58,   58,
 /*   140 */    59,   59,   60,   60,   60,   61,  232,  355,  251,   94,
 /*   150 */   331,  162,   57,  137,  335,  187,  260,  191,  261,  148,
 /*   160 */   157,  374,  268,  141,  212,  335,  187,  260,  191,  261,
 /*   170 */   148,  315,  103,  493,    1,  212,  316,  313,  153,  377,
 /*   180 */   364,  283,  286,  287,  229,  411,  138,  374,  448,  141,
 /*   190 */   288,  484,  485,  332,  333,  355,   55,   53,  240,  385,
 /*   200 */   388,  382,  382,   57,   56,   56,   56,   56,  159,   58,
 /*   210 */    58,   58,   58,   59,   59,   60,   60,   60,   61,  232,
 /*   220 */   103,  332,  333,  153,  417,   57,  283,  286,  287,  264,
 /*   230 */   337,  338,  376,  331,  264,  288,  450,  264,  331,  484,
 /*   240 */   485,  192,   62,  355,  168,  264,  129,  264,  436,  354,
 /*   250 */    31,  364,  377,  349,  354,   30,  199,  354,   30,  445,
 /*   260 */    62,  350,  168,  358,  129,  354,   43,  354,   36,   55,
 /*   270 */    53,  240,  385,  388,  382,  382,   57,   56,   56,   56,
 /*   280 */    56,  245,   58,   58,   58,   58,   59,   59,   60,   60,
 /*   290 */    60,   61,  232,  360,  360,  360,  264,  243,   57,  530,
 /*   300 */   277,  128,  264,  198,  332,  333,  420,  275,  202,  332,
 /*   310 */   333,  396,  264,  249,  396,  153,  354,   25,  283,  286,
 /*   320 */   287,  415,  354,   30,  165,  377,  210,  288,  407,  415,
 /*   330 */   146,   49,  354,   36,  306,  119,  355,   68,   60,   60,
 /*   340 */    60,   61,   55,   53,  240,  385,  388,  382,  382,   57,
 /*   350 */    56,   56,   56,   56,  421,   58,   58,   58,   58,   59,
 /*   360 */    59,   60,   60,   60,   61,  355,  391,  472,  232,  341,
 /*   370 */   331,  291,  392,  200,   57,  264,  447,  147,  134,  395,
 /*   380 */   250,  449,  280,  184,  342,  442,  331,  460,  242,   18,
 /*   390 */    17,  239,  367,  368,  331,  354,   43,  267,  367,  368,
 /*   400 */   343,  377,  339,  143,  134,  149,  221,  188,  121,  457,
 /*   410 */    71,  425,  271,  340,  390,  390,  189,  456,   55,   53,
 /*   420 */   240,  385,  388,  382,  382,   57,   56,   56,   56,   56,
 /*   430 */   424,   58,   58,   58,   58,   59,   59,   60,   60,   60,
 /*   440 */    61,  332,  333,  248,  232,  464,  116,  281,  133,  436,
 /*   450 */    57,  364,  436,  331,  436,  166,  233,  332,  333,   10,
 /*   460 */   212,  166,  308,  264,  436,  332,  333,  354,    4,  478,
 /*   470 */   479,  480,  271,  114,  390,  390,  161,  377,  271,  331,
 /*   480 */   390,  390,  176,  354,   26,  246,  144,  247,  364,  408,
 /*   490 */   150,  151,  152,  278,   55,   53,  240,  385,  388,  382,
 /*   500 */   382,   57,   56,   56,   56,   56,  443,   58,   58,   58,
 /*   510 */    58,   59,   59,   60,   60,   60,   61,  419,   19,  378,
 /*   520 */   232,  161,  364,  264,  332,  333,   57,  210,  264,  404,
 /*   530 */   210,  406,  210,  164,   67,  264,   69,  264,  364,  380,
 /*   540 */   381,  264,  209,  354,   21,  365,  226,  264,  354,   29,
 /*   550 */   332,  333,  254,  377,  235,  354,   48,  354,   22,  364,
 /*   560 */   477,  354,   46,   20,  411,  476,  379,  354,   85,  411,
 /*   570 */    55,   53,  240,  385,  388,  382,  382,   57,   56,   56,
 /*   580 */    56,   56,  215,   58,   58,   58,   58,   59,   59,   60,
 /*   590 */    60,   60,   61,  264,  221,  264,  232,  264,  221,  264,
 /*   600 */   130,  264,   57,  204,  132,  264,  282,  300,  206,  364,
 /*   610 */   300,  264,  203,  354,   83,  354,   30,  354,   87,  354,
 /*   620 */    88,  354,   95,  264,  123,  354,   96,  406,  300,  377,
 /*   630 */   353,  354,   16,  222,  352,  355,  307,  298,  489,  221,
 /*   640 */   405,  476,  109,  354,   86,  131,   55,   53,  240,  385,
 /*   650 */   388,  382,  382,   57,   56,   56,   56,   56,  241,   58,
 /*   660 */    58,   58,   58,   59,   59,   60,   60,   60,   61,  232,
 /*   670 */   264,  177,  396,  264,  303,   57,  244,  264,  225,  386,
 /*   680 */   355,  353,  158,  264,  430,  352,  264,  486,  486,  429,
 /*   690 */   354,   47,  305,  354,   97,  264,  269,  354,   98,  370,
 /*   700 */   370,  346,  377,  354,   23,  149,  354,   32,  431,  155,
 /*   710 */   347,  265,  310,  386,  118,  354,   33,  452,  100,   55,
 /*   720 */    53,  240,  385,  388,  382,  382,   57,   56,   56,   56,
 /*   730 */    56,  264,   58,   58,   58,   58,   59,   59,   60,   60,
 /*   740 */    60,   61,  232,  264,  355,  264,  359,  264,   57,  264,
 /*   750 */     6,  354,   24,  264,  394,  397,  233,  264,  256,  264,
 /*   760 */   186,  410,  428,  354,   34,  354,   35,  354,   37,  354,
 /*   770 */    38,  264,   13,  354,   39,  377,  383,  354,   27,  354,
 /*   780 */    28,  373,  414,  208,  426,   74,  451,  427,  216,  432,
 /*   790 */   324,  354,   40,   53,  240,  385,  388,  382,  382,   57,
 /*   800 */    56,   56,   56,   56,  264,   58,   58,   58,   58,   59,
 /*   810 */    59,   60,   60,   60,   61,  232,  264,  413,  264,  433,
 /*   820 */   264,   57,  219,  190,  354,   41,  299,  422,  434,  488,
 /*   830 */   369,  214,  371,  122,  290,  145,  354,   42,  354,   44,
 /*   840 */   354,   45,  469,  470,  473,   13,  109,  193,  377,  109,
 /*   850 */   311,  273,  109,  270,  400,  403,  425,  387,  435,  437,
 /*   860 */    80,   80,  145,  482,  483,  285,  320,  240,  385,  388,
 /*   870 */   382,  382,   57,   56,   56,   56,   56,    5,   58,   58,
 /*   880 */    58,   58,   59,   59,   60,   60,   60,   61,    5,  471,
 /*   890 */   224,  319,   64,  272,  487,  322,  323,  238,    9,  327,
 /*   900 */   253,  257,  258,   64,  272,  259,  336,  344,  238,  237,
 /*   910 */   266,  345,  348,  356,  351,   74,  194,  276,  195,   73,
 /*   920 */   274,  266,  196,   51,  197,  170,  357,   70,  142,  398,
 /*   930 */   201,  171,  401,  402,  106,   75,  172,  205,  279,   90,
 /*   940 */   230,  376,  412,  207,  440,  416,  439,  453,  454,  174,
 /*   950 */   463,  455,  376,  461,  231,  175,  293,  296,  292,   66,
 /*   960 */    65,    5,  156,  465,  223,  110,  467,   64,  262,  263,
 /*   970 */    66,   65,  358,  468,  104,   11,   64,  272,   64,  262,
 /*   980 */   263,  238,  301,  358,  115,  234,  304,   84,  164,  173,
 /*   990 */    89,  318,  321,  228,  266,  185,  102,  255,  325,  326,
 /*  1000 */   328,  163,  360,  360,  360,  361,  362,  363,   12,   50,
 /*  1010 */   531,  532,  139,  360,  360,  360,  361,  362,  363,   12,
 /*  1020 */   140,    5,   54,    3,  384,  376,  366,  389,  375,  181,
 /*  1030 */   252,  169,  120,  182,  183,  217,   64,  272,  393,    7,
 /*  1040 */     8,  238,  409,   66,   65,  418,  107,  101,   14,   13,
 /*  1050 */   108,   64,  262,  263,  266,  423,  358,  135,  284,  181,
 /*  1060 */   252,   91,   92,  182,  183,  217,  213,   77,  289,   93,
 /*  1070 */   189,  154,  218,  294,  111,  113,  462,  101,  475,   76,
 /*  1080 */   466,  220,   15,  481,   78,  376,  360,  360,  360,  361,
 /*  1090 */   362,  363,   12,   79,  302,  158,  136,  117,  179,  401,
 /*  1100 */   180,   81,   82,   66,   65,  490,  314,  519,  475,  491,
 /*  1110 */   519,   64,  262,  263,  519,  519,  358,  519,  519,  519,
 /*  1120 */   519,  519,  519,  519,  297,  112,  474,  519,  519,  295,
 /*  1130 */   519,  519,  519,  519,  164,  519,  519,  519,  519,  519,
 /*  1140 */   519,  519,  519,  376,  519,  519,  360,  360,  360,  361,
 /*  1150 */   362,  363,   12,  519,  297,  112,  474,  519,  519,  295,
 /*  1160 */   519,  124,  125,  160,  164,  519,  519,  519,  519,  519,
 /*  1170 */   445,  519,  519,  519,  358,  519,  519,  519,  519,  519,
 /*  1180 */   519,  519,  519,  519,  519,  519,  519,  519,  519,  519,
 /*  1190 */   519,  519,  519,  160,  519,  519,  519,  519,  519,  519,
 /*  1200 */   519,  519,  519,  519,  360,  360,  360,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    16,   83,   84,   19,  176,   21,   22,   74,   75,   76,
 /*    10 */    77,  183,   79,   80,   81,   82,   83,   84,   85,   86,
 /*    20 */    87,   88,   78,   79,   80,   81,   82,   83,   84,   85,
 /*    30 */    86,   87,   88,   49,   79,   80,   81,   82,   83,   84,
 /*    40 */    85,   86,   87,   88,   83,   84,   85,   86,   87,   88,
 /*    50 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    60 */    76,   77,  157,   79,   80,   81,   82,   83,   84,   85,
 /*    70 */    86,   87,   88,   16,  112,   16,   92,   20,  108,   22,
 /*    80 */   110,  111,   23,  131,   88,   26,   16,  157,  136,  137,
 /*    90 */   138,  139,  140,  163,  177,  165,   26,  175,  176,  149,
 /*   100 */   150,  196,    1,  153,   20,  183,   49,  226,  227,  228,
 /*   110 */    53,  230,  162,    3,    4,  146,  147,  148,  188,  189,
 /*   120 */   151,  189,   21,   66,   67,   68,   69,   70,   71,   72,
 /*   130 */    73,   74,   75,   76,   77,  177,   79,   80,   81,   82,
 /*   140 */    83,   84,   85,   86,   87,   88,   16,  197,  150,   19,
 /*   150 */    21,  153,   22,   94,   95,   96,   97,   98,   99,  100,
 /*   160 */   162,  169,  170,  171,  105,   95,   96,   97,   98,   99,
 /*   170 */   100,  148,  222,    0,  151,  105,    3,    4,   94,   49,
 /*   180 */    21,   97,   98,   99,  166,  169,    1,  169,  170,  171,
 /*   190 */   106,  241,  242,   92,   93,  197,   66,   67,   68,   69,
 /*   200 */    70,   71,   72,   73,   74,   75,   76,   77,  162,   79,
 /*   210 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   220 */   222,   92,   93,   94,  208,   22,   97,   98,   99,  157,
 /*   230 */   193,  194,   65,   21,  157,  106,  189,  157,   21,  241,
 /*   240 */   242,  198,  226,  197,  228,  157,  230,  157,  157,  177,
 /*   250 */   178,   92,   49,   30,  177,  178,  157,  177,  178,   92,
 /*   260 */   226,   38,  228,   96,  230,  177,  178,  177,  178,   66,
 /*   270 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   280 */    77,  190,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   290 */    87,   88,   16,  126,  127,  128,  157,  220,   22,  114,
 /*   300 */   220,  162,  157,  231,   92,   93,    2,  217,  218,   92,
 /*   310 */    93,  234,  157,  225,  234,   94,  177,  178,   97,   98,
 /*   320 */    99,  157,  177,  178,  200,   49,  235,  106,  116,  157,
 /*   330 */   162,  207,  177,  178,  238,  239,  197,  134,   85,   86,
 /*   340 */    87,   88,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   350 */    74,   75,   76,   77,    2,   79,   80,   81,   82,   83,
 /*   360 */    84,   85,   86,   87,   88,  197,    2,    2,   16,   12,
 /*   370 */    21,   16,    2,  218,   22,  157,  168,  209,  210,  234,
 /*   380 */   216,  157,  214,  159,   27,  177,   21,  163,  216,  165,
 /*   390 */     1,  172,  173,  174,   21,  177,  178,  172,  173,  174,
 /*   400 */    43,   49,   45,  209,  210,   50,  157,   96,   19,  183,
 /*   410 */   134,  185,  108,   56,  110,  111,  105,  191,   66,   67,
 /*   420 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   430 */     2,   79,   80,   81,   82,   83,   84,   85,   86,   87,
 /*   440 */    88,   92,   93,  225,   16,  196,   25,  157,  157,  157,
 /*   450 */    22,   21,  157,   21,  157,  236,  101,   92,   93,    1,
 /*   460 */   105,  236,  131,  157,  157,   92,   93,  177,  178,  138,
 /*   470 */   139,  140,  108,  124,  110,  111,   70,   49,  108,   21,
 /*   480 */   110,  111,  190,  177,  178,  190,   19,  190,   21,  116,
 /*   490 */   102,  103,  104,  157,   66,   67,   68,   69,   70,   71,
 /*   500 */    72,   73,   74,   75,   76,   77,    2,   79,   80,   81,
 /*   510 */    82,   83,   84,   85,   86,   87,   88,   85,    1,   49,
 /*   520 */    16,  115,   92,  157,   92,   93,   22,  235,  157,   20,
 /*   530 */   235,   20,  235,  112,  133,  157,  135,  157,   21,   69,
 /*   540 */    70,  157,  235,  177,  178,    2,  125,  157,  177,  178,
 /*   550 */    92,   93,   21,   49,   23,  177,  178,  177,  178,   92,
 /*   560 */   130,  177,  178,   20,  169,  169,   96,  177,  178,  169,
 /*   570 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   580 */    76,   77,    2,   79,   80,   81,   82,   83,   84,   85,
 /*   590 */    86,   87,   88,  157,  157,  157,   16,  157,  157,  157,
 /*   600 */   162,  157,   22,  208,   93,  157,   85,  157,  208,   92,
 /*   610 */   157,  157,  157,  177,  178,  177,  178,  177,  178,  177,
 /*   620 */   178,  177,  178,  157,  115,  177,  178,  116,  157,   49,
 /*   630 */   109,  177,  178,  196,  113,  197,  240,  196,   93,  157,
 /*   640 */   211,  169,   20,  177,  178,  162,   66,   67,   68,   69,
 /*   650 */    70,   71,   72,   73,   74,   75,   76,   77,  220,   79,
 /*   660 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   670 */   157,  221,  234,  157,  221,   22,   25,  157,  196,   92,
 /*   680 */   197,  109,   20,  157,   33,  113,  157,  142,  143,   23,
 /*   690 */   177,  178,  221,  177,  178,  157,   16,  177,  178,  126,
 /*   700 */   127,   37,   49,  177,  178,   50,  177,  178,   57,  162,
 /*   710 */    46,  157,  240,  126,  239,  177,  178,   95,  157,   66,
 /*   720 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   730 */    77,  157,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   740 */    87,   88,   16,  157,  197,  157,  157,  157,   22,  157,
 /*   750 */   199,  177,  178,  157,    2,  157,  101,  157,   24,  157,
 /*   760 */    26,  157,   96,  177,  178,  177,  178,  177,  178,  177,
 /*   770 */   178,  157,   20,  177,  178,   49,   96,  177,  178,  177,
 /*   780 */   178,  169,  157,  157,  157,  123,  157,  186,  157,  186,
 /*   790 */   154,  177,  178,   67,   68,   69,   70,   71,   72,   73,
 /*   800 */    74,   75,   76,   77,  157,   79,   80,   81,   82,   83,
 /*   810 */    84,   85,   86,   87,   88,   16,  157,    2,  157,  186,
 /*   820 */   157,   22,  157,  180,  177,  178,  157,    2,    2,  157,
 /*   830 */   237,    2,  237,  199,    2,   20,  177,  178,  177,  178,
 /*   840 */   177,  178,    2,    2,    2,   20,   20,  201,   49,   20,
 /*   850 */   243,  233,   20,  229,  180,  180,  185,  229,  180,  180,
 /*   860 */    20,   20,   20,  169,  169,  184,   10,   68,   69,   70,
 /*   870 */    71,   72,   73,   74,   75,   76,   77,    1,   79,   80,
 /*   880 */    81,   82,   83,   84,   85,   86,   87,   88,    1,    2,
 /*   890 */   202,  152,   16,   17,  244,  152,  152,   21,   20,   22,
 /*   900 */   160,  164,  164,   16,   17,  101,  179,  179,   21,   47,
 /*   910 */    34,  187,  179,  197,  179,  123,  202,  120,  203,  121,
 /*   920 */   118,   34,  204,  122,  205,  232,  206,  133,  114,  158,
 /*   930 */    26,  219,   21,  168,  158,  101,  219,  212,  117,    1,
 /*   940 */   181,   65,  213,  212,  187,  213,  168,  179,  179,  219,
 /*   950 */    18,  179,   65,  158,  181,  219,   15,   15,  155,   83,
 /*   960 */    84,    1,  156,  158,  202,  195,  206,   91,   92,   93,
 /*   970 */    83,   84,   96,  206,    1,    1,   16,   17,   91,   92,
 /*   980 */    93,   21,  224,   96,  223,  161,  223,  167,  112,  182,
 /*   990 */   182,    2,    9,    2,   34,   25,   35,   22,   21,   21,
 /*  1000 */    21,   51,  126,  127,  128,  129,  130,  131,  132,    1,
 /*  1010 */   114,  114,  114,  126,  127,  128,  129,  130,  131,  132,
 /*  1020 */   114,    1,    1,    1,   96,   65,    2,  109,    2,    7,
 /*  1030 */     8,   67,    1,   11,   12,   13,   16,   17,   41,  119,
 /*  1040 */   119,   21,  116,   83,   84,   85,    1,   25,   20,   20,
 /*  1050 */     2,   91,   92,   93,   34,    2,   96,  114,   51,    7,
 /*  1060 */     8,    1,    1,   11,   12,   13,    2,    1,   51,    1,
 /*  1070 */   105,  100,   14,   16,  115,   25,   17,   25,   56,    1,
 /*  1080 */    17,   14,    1,  114,   22,   65,  126,  127,  128,  129,
 /*  1090 */   130,  131,  132,   22,   20,   20,   20,   25,   25,   21,
 /*  1100 */   144,   22,   22,   83,   84,    3,    5,  245,   56,    6,
 /*  1110 */   245,   91,   92,   93,  245,  245,   96,  245,  245,  245,
 /*  1120 */   245,  245,  245,  245,  102,  103,  104,  245,  245,  107,
 /*  1130 */   245,  245,  245,  245,  112,  245,  245,  245,  245,  245,
 /*  1140 */   245,  245,  245,   65,  245,  245,  126,  127,  128,  129,
 /*  1150 */   130,  131,  132,  245,  102,  103,  104,  245,  245,  107,
 /*  1160 */   245,   83,   84,  141,  112,  245,  245,  245,  245,  245,
 /*  1170 */    92,  245,  245,  245,   96,  245,  245,  245,  245,  245,
 /*  1180 */   245,  245,  245,  245,  245,  245,  245,  245,  245,  245,
 /*  1190 */   245,  245,  245,  141,  245,  245,  245,  245,  245,  245,
 /*  1200 */   245,  245,  245,  245,  126,  127,  128,
};
#define YY_SHIFT_USE_DFLT (-83)
#define YY_SHIFT_MAX 314
static const short yy_shift_ofst[] = {
 /*     0 */   110, 1022,  876, 1052,  -16,  876, 1020, 1020, 1020,  129,
 /*    10 */   -38,  887, 1020, 1020, 1020, 1020,  -56,  217,  159,  -82,
 /*    20 */   -82,   57,  130,  203,  276,  352,  428,  504,  580,  653,
 /*    30 */   653,  653,  653,  653,  653,  653,  653,  653,  653,  653,
 /*    40 */   653,  653,  653,  653,  653,  653,  726,  799,  799,  960,
 /*    50 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    60 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    70 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    80 */  1020, 1020, 1020,  -67,   59,  -45,  -45,  -39,  253,  355,
 /*    90 */   217,  217,  217,  217,  159,   -4,  -83,  -83,  -83, 1078,
 /*   100 */    70,  -48,  357,  349,  365,  173,  467,  217,  467,  217,
 /*   110 */   217,  217,  217,  217,  217,  421,  217,  217,  430,  430,
 /*   120 */   -38,  -38,  -83,  -83,  167,  167,   84,  221,  304,  101,
 /*   130 */   364,  370,  212,  373,  458,  432,  331,  217,  521,  217,
 /*   140 */   217,  517,  217,  511,  217,  217,  -30,  511,  217,  217,
 /*   150 */   651,  651,  651,  217,  217,  -30,  217,  -30,  217,  -30,
 /*   160 */   545,  217,  389,  223,  572,  509,  573,  573,  587,  587,
 /*   170 */   401,  223,  223,  655,  223,  223,  622,  662,  159,  159,
 /*   180 */   406,  856,  856,  856,  878,  877,  877,  804,  804,  862,
 /*   190 */   804,  804,  -38,  792,  797,  798,  802,  801,  794,  814,
 /*   200 */   904,  911,  904,  814,  834,  821,  834,  821,  938,  904,
 /*   210 */   904,  911,  862,  804,  804,  804,  938,  932,  941,  814,
 /*   220 */   942,  814,  792,  801,  801,  973,  974,  973,  -83,  -83,
 /*   230 */   -83,  -83,  470,  388,  531,  734,  311,  664,  185,  543,
 /*   240 */   680,  752,  815,  825,  666,  826,  829,  832,  840,  841,
 /*   250 */   842,  989,  983,  991,  975,  977,  970,  978,  979,  961,
 /*   260 */   950, 1008,  896,  897,  898,  906, 1021, 1024, 1026,  928,
 /*   270 */   964,  918, 1031,  997,  920, 1028,  921, 1029,  926, 1045,
 /*   280 */  1048,  943, 1053, 1007, 1060, 1064, 1061, 1066, 1017, 1068,
 /*   290 */   971,  965, 1058, 1057, 1059, 1067, 1063,  959, 1050, 1062,
 /*   300 */  1071, 1074, 1081, 1075, 1072, 1075, 1076, 1079,  969, 1073,
 /*   310 */  1080,  956, 1102, 1101, 1103,
};
#define YY_REDUCE_USE_DFLT (-173)
#define YY_REDUCE_MAX 231
static const short yy_reduce_ofst[] = {
 /*     0 */   -31,  -50,  438,   -2,   16,  139,   77,   90,   80,  -70,
 /*    10 */   168,   88,   72,  145,  155,  218, -119,  224,   18,  219,
 /*    20 */   225,   34,   34,   34,   34,   34,   34,   34,   34,   34,
 /*    30 */    34,   34,   34,   34,   34,   34,   34,   34,   34,   34,
 /*    40 */    34,   34,   34,   34,   34,   34,   34,   34,   34,  290,
 /*    50 */   306,  366,  371,  378,  380,  384,  390,  436,  440,  442,
 /*    60 */   444,  448,  454,  466,  513,  516,  520,  526,  529,  538,
 /*    70 */   574,  586,  588,  590,  592,  596,  600,  602,  614,  647,
 /*    80 */   659,  661,  663,   34,  -78,   34,   34,   34,   34,  226,
 /*    90 */    91,  292,  295,  297,   -8,   34,   34,   34,   34,  208,
 /*   100 */  -172,   96,   37,  -95,  164,   23,  395,  172,  400,  307,
 /*   110 */   249,  437,  441,  450,  482,   46,  453,  471,  396,  472,
 /*   120 */   483,  547,  124,  194,  -83,  -42,  -68,   47,   43,   99,
 /*   130 */    43,   43,  291,  336,  455,  554,  475,  561,  551,  554,
 /*   140 */   589,  612,  598,  429,  604,  625,   43,  429,  626,  627,
 /*   150 */   601,  603,  633,  629,  631,   43,  665,   43,  669,   43,
 /*   160 */   607,  672,  636,  643,  634,  646,  593,  595,  624,  628,
 /*   170 */   618,  674,  675,  671,  678,  679,  681,  688,  694,  695,
 /*   180 */   650,  739,  743,  744,  740,  737,  738,  727,  728,  724,
 /*   190 */   733,  735,  716,  714,  715,  718,  719,  720,  693,  771,
 /*   200 */   712,  765,  717,  776,  725,  729,  731,  732,  759,  730,
 /*   210 */   736,  778,  757,  768,  769,  772,  773,  803,  806,  795,
 /*   220 */   770,  805,  762,  760,  767,  761,  758,  763,  824,  820,
 /*   230 */   807,  808,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   500,  765,  731,  765,  614,  765,  731,  765,  731,  765,
 /*    10 */   618,  765,  727,  731,  765,  765,  701,  765,  533,  741,
 /*    20 */   741,  649,  765,  765,  765,  765,  765,  765,  765,  650,
 /*    30 */   730,  726,  722,  724,  723,  651,  638,  647,  654,  630,
 /*    40 */   656,  657,  667,  668,  748,  749,  691,  707,  690,  765,
 /*    50 */   765,  765,  765,  765,  765,  765,  765,  765,  765,  765,
 /*    60 */   765,  765,  765,  765,  765,  765,  765,  765,  765,  765,
 /*    70 */   765,  765,  765,  765,  765,  765,  765,  765,  765,  765,
 /*    80 */   765,  765,  765,  693,  526,  692,  700,  694,  695,  587,
 /*    90 */   765,  765,  765,  765,  765,  696,  697,  708,  709,  765,
 /*   100 */   765,  754,  765,  765,  765,  500,  614,  765,  614,  765,
 /*   110 */   765,  765,  765,  765,  765,  765,  765,  765,  765,  765,
 /*   120 */   765,  765,  608,  618,  765,  765,  578,  765,  765,  765,
 /*   130 */   765,  765,  765,  765,  765,  765,  754,  765,  606,  765,
 /*   140 */   765,  535,  765,  616,  765,  765,  621,  622,  765,  765,
 /*   150 */   765,  765,  765,  765,  765,  516,  765,  597,  765,  661,
 /*   160 */   762,  765,  765,  641,  606,  615,  765,  765,  765,  765,
 /*   170 */   725,  641,  641,  557,  641,  641,  560,  653,  765,  765,
 /*   180 */   763,  505,  505,  505,  577,  524,  524,  589,  589,  574,
 /*   190 */   589,  589,  765,  653,  644,  646,  634,  648,  765,  623,
 /*   200 */   642,  765,  642,  623,  631,  633,  631,  633,  732,  642,
 /*   210 */   642,  765,  574,  589,  589,  589,  732,  514,  511,  623,
 /*   220 */   596,  623,  653,  648,  648,  669,  765,  669,  519,  543,
 /*   230 */   562,  562,  765,  765,  515,  765,  765,  765,  677,  765,
 /*   240 */   765,  765,  765,  765,  765,  765,  765,  765,  765,  765,
 /*   250 */   765,  765,  765,  765,  520,  765,  765,  765,  765,  765,
 /*   260 */   765,  765,  682,  678,  765,  679,  765,  765,  765,  765,
 /*   270 */   765,  600,  765,  765,  765,  635,  765,  645,  765,  765,
 /*   280 */   765,  765,  765,  765,  765,  765,  765,  765,  765,  765,
 /*   290 */   765,  765,  765,  765,  765,  765,  765,  765,  765,  765,
 /*   300 */   765,  658,  765,  659,  765,  660,  745,  765,  765,  765,
 /*   310 */   765,  765,  765,  501,  765,  494,  498,  496,  497,  503,
 /*   320 */   506,  504,  507,  508,  509,  521,  522,  525,  523,  517,
 /*   330 */   542,  530,  531,  532,  544,  551,  552,  590,  591,  592,
 /*   340 */   593,  742,  743,  744,  553,  572,  575,  576,  554,  639,
 /*   350 */   640,  555,  604,  605,  674,  598,  599,  603,  676,  680,
 /*   360 */   681,  683,  684,  685,  529,  536,  537,  540,  541,  737,
 /*   370 */   739,  738,  740,  539,  538,  686,  689,  698,  699,  705,
 /*   380 */   711,  715,  703,  704,  706,  710,  712,  713,  714,  601,
 /*   390 */   602,  718,  720,  721,  716,  728,  729,  624,  719,  702,
 /*   400 */   636,  528,  643,  637,  607,  617,  626,  627,  628,  629,
 /*   410 */   612,  613,  619,  632,  672,  673,  620,  609,  610,  611,
 /*   420 */   717,  675,  687,  688,  556,  563,  564,  565,  568,  569,
 /*   430 */   570,  571,  566,  567,  733,  734,  736,  735,  558,  559,
 /*   440 */   573,  545,  546,  547,  548,  682,  549,  550,  534,  527,
 /*   450 */   579,  582,  561,  583,  584,  585,  586,  588,  580,  581,
 /*   460 */   518,  510,  512,  513,  594,  625,  595,  652,  655,  664,
 /*   470 */   665,  666,  670,  671,  662,  663,  755,  756,  750,  751,
 /*   480 */   752,  753,  746,  747,  757,  758,  759,  760,  764,  761,
 /*   490 */   499,  502,  495,
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
    0,  /*         LP => nothing */
    0,  /*         RP => nothing */
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
  "$",             "LP",            "RP",            "SEMI",        
  "EXPLAIN",       "QUERY",         "PLAN",          "BEGIN",       
  "START",         "TRANSACTION",   "WORK",          "COMMIT",      
  "ROLLBACK",      "CREATE",        "TABLE",         "IF",          
  "NOT",           "EXISTS",        "TEMP",          "AS",          
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
 /*   4 */ "cmdx ::= LP cmd RP",
 /*   5 */ "ecmd ::= SEMI",
 /*   6 */ "ecmd ::= explain cmdx SEMI",
 /*   7 */ "explain ::=",
 /*   8 */ "explain ::= EXPLAIN",
 /*   9 */ "explain ::= EXPLAIN QUERY PLAN",
 /*  10 */ "cmd ::= BEGIN trans_opt",
 /*  11 */ "cmd ::= START TRANSACTION",
 /*  12 */ "trans_opt ::=",
 /*  13 */ "trans_opt ::= WORK",
 /*  14 */ "cmd ::= COMMIT trans_opt",
 /*  15 */ "cmd ::= ROLLBACK trans_opt",
 /*  16 */ "cmd ::= create_table create_table_args",
 /*  17 */ "create_table ::= CREATE temp TABLE ifnotexists nm dbnm",
 /*  18 */ "ifnotexists ::=",
 /*  19 */ "ifnotexists ::= IF NOT EXISTS",
 /*  20 */ "temp ::= TEMP",
 /*  21 */ "temp ::=",
 /*  22 */ "create_table_args ::= LP columnlist conslist_opt RP table_opt",
 /*  23 */ "create_table_args ::= AS select",
 /*  24 */ "columnlist ::= columnlist COMMA column",
 /*  25 */ "columnlist ::= column",
 /*  26 */ "table_opt ::=",
 /*  27 */ "table_opt ::= table_opt ID",
 /*  28 */ "table_opt ::= table_opt ID EQ ID",
 /*  29 */ "table_opt ::= table_opt DEFAULT CHARSET SET eq_or_null ID",
 /*  30 */ "table_opt ::= table_opt DEFAULT COLLATE eq_or_null ID",
 /*  31 */ "eq_or_null ::=",
 /*  32 */ "eq_or_null ::= EQ",
 /*  33 */ "column ::= columnid type carglist",
 /*  34 */ "columnid ::= nm",
 /*  35 */ "id ::= ID",
 /*  36 */ "ids ::= ID|STRING",
 /*  37 */ "nm ::= ID",
 /*  38 */ "nm ::= STRING",
 /*  39 */ "nm ::= JOIN_KW",
 /*  40 */ "type ::=",
 /*  41 */ "type ::= typetoken",
 /*  42 */ "typetoken ::= typename",
 /*  43 */ "typetoken ::= typename LP signed RP",
 /*  44 */ "typetoken ::= typename LP signed COMMA signed RP",
 /*  45 */ "typename ::= ids",
 /*  46 */ "typename ::= typename ids",
 /*  47 */ "signed ::= plus_num",
 /*  48 */ "signed ::= minus_num",
 /*  49 */ "carglist ::= carglist carg",
 /*  50 */ "carglist ::=",
 /*  51 */ "carg ::= CONSTRAINT nm ccons",
 /*  52 */ "carg ::= ccons",
 /*  53 */ "carg ::= DEFAULT term",
 /*  54 */ "carg ::= DEFAULT LP expr RP",
 /*  55 */ "carg ::= DEFAULT PLUS term",
 /*  56 */ "carg ::= DEFAULT MINUS term",
 /*  57 */ "carg ::= DEFAULT id",
 /*  58 */ "ccons ::= AUTOINCR",
 /*  59 */ "ccons ::= NULL onconf",
 /*  60 */ "ccons ::= NOT NULL onconf",
 /*  61 */ "ccons ::= PRIMARY KEY sortorder onconf",
 /*  62 */ "ccons ::= UNIQUE onconf",
 /*  63 */ "ccons ::= CHECK LP expr RP",
 /*  64 */ "ccons ::= REFERENCES nm idxlist_opt refargs",
 /*  65 */ "ccons ::= defer_subclause",
 /*  66 */ "ccons ::= COLLATE id",
 /*  67 */ "autoinc ::=",
 /*  68 */ "autoinc ::= AUTOINCR",
 /*  69 */ "refargs ::=",
 /*  70 */ "refargs ::= refargs refarg",
 /*  71 */ "refarg ::= MATCH nm",
 /*  72 */ "refarg ::= ON DELETE refact",
 /*  73 */ "refarg ::= ON UPDATE refact",
 /*  74 */ "refarg ::= ON INSERT refact",
 /*  75 */ "refact ::= SET NULL",
 /*  76 */ "refact ::= SET DEFAULT",
 /*  77 */ "refact ::= CASCADE",
 /*  78 */ "refact ::= RESTRICT",
 /*  79 */ "defer_subclause ::= NOT DEFERRABLE init_deferred_pred_opt",
 /*  80 */ "defer_subclause ::= DEFERRABLE init_deferred_pred_opt",
 /*  81 */ "init_deferred_pred_opt ::=",
 /*  82 */ "init_deferred_pred_opt ::= INITIALLY DEFERRED",
 /*  83 */ "init_deferred_pred_opt ::= INITIALLY IMMEDIATE",
 /*  84 */ "conslist_opt ::=",
 /*  85 */ "conslist_opt ::= COMMA conslist",
 /*  86 */ "conslist ::= conslist COMMA tcons",
 /*  87 */ "conslist ::= conslist tcons",
 /*  88 */ "conslist ::= tcons",
 /*  89 */ "tcons ::= CONSTRAINT nm",
 /*  90 */ "tcons ::= PRIMARY KEY LP idxlist autoinc RP onconf",
 /*  91 */ "tcons ::= UNIQUE LP idxlist RP onconf",
 /*  92 */ "tcons ::= CHECK LP expr RP onconf",
 /*  93 */ "tcons ::= FOREIGN KEY LP idxlist RP REFERENCES nm idxlist_opt refargs defer_subclause_opt",
 /*  94 */ "defer_subclause_opt ::=",
 /*  95 */ "defer_subclause_opt ::= defer_subclause",
 /*  96 */ "onconf ::=",
 /*  97 */ "onconf ::= ON CONFLICT resolvetype",
 /*  98 */ "resolvetype ::= raisetype",
 /*  99 */ "resolvetype ::= IGNORE",
 /* 100 */ "resolvetype ::= REPLACE",
 /* 101 */ "cmd ::= DROP TABLE ifexists fullname",
 /* 102 */ "ifexists ::= IF EXISTS",
 /* 103 */ "ifexists ::=",
 /* 104 */ "cmd ::= select",
 /* 105 */ "select ::= oneselect",
 /* 106 */ "select ::= select multiselect_op oneselect",
 /* 107 */ "multiselect_op ::= UNION",
 /* 108 */ "multiselect_op ::= UNION ALL",
 /* 109 */ "multiselect_op ::= EXCEPT|INTERSECT",
 /* 110 */ "oneselect ::= SELECT distinct selcollist from where_opt groupby_opt having_opt orderby_opt limit_opt",
 /* 111 */ "distinct ::= DISTINCT",
 /* 112 */ "distinct ::= ALL",
 /* 113 */ "distinct ::=",
 /* 114 */ "sclp ::= selcollist COMMA",
 /* 115 */ "sclp ::=",
 /* 116 */ "selcollist ::= sclp expr as",
 /* 117 */ "selcollist ::= sclp STAR",
 /* 118 */ "selcollist ::= sclp nm DOT STAR",
 /* 119 */ "as ::= AS nm",
 /* 120 */ "as ::= ids",
 /* 121 */ "as ::=",
 /* 122 */ "from ::=",
 /* 123 */ "from ::= FROM seltablist",
 /* 124 */ "stl_prefix ::= seltablist joinop",
 /* 125 */ "stl_prefix ::=",
 /* 126 */ "seltablist ::= stl_prefix nm dbnm as on_opt using_opt",
 /* 127 */ "seltablist ::= stl_prefix LP seltablist_paren RP as on_opt using_opt",
 /* 128 */ "seltablist_paren ::= select",
 /* 129 */ "seltablist_paren ::= seltablist",
 /* 130 */ "dbnm ::=",
 /* 131 */ "dbnm ::= DOT nm",
 /* 132 */ "fullname ::= nm dbnm",
 /* 133 */ "joinop ::= COMMA|JOIN",
 /* 134 */ "joinop ::= JOIN_KW JOIN",
 /* 135 */ "joinop ::= JOIN_KW nm JOIN",
 /* 136 */ "joinop ::= JOIN_KW nm nm JOIN",
 /* 137 */ "on_opt ::= ON expr",
 /* 138 */ "on_opt ::=",
 /* 139 */ "using_opt ::= USING LP inscollist RP",
 /* 140 */ "using_opt ::=",
 /* 141 */ "orderby_opt ::=",
 /* 142 */ "orderby_opt ::= ORDER BY sortlist",
 /* 143 */ "sortlist ::= sortlist COMMA sortitem collate sortorder",
 /* 144 */ "sortlist ::= sortitem collate sortorder",
 /* 145 */ "sortitem ::= expr",
 /* 146 */ "sortorder ::= ASC",
 /* 147 */ "sortorder ::= DESC",
 /* 148 */ "sortorder ::=",
 /* 149 */ "collate ::=",
 /* 150 */ "collate ::= COLLATE id",
 /* 151 */ "groupby_opt ::=",
 /* 152 */ "groupby_opt ::= GROUP BY exprlist",
 /* 153 */ "having_opt ::=",
 /* 154 */ "having_opt ::= HAVING expr",
 /* 155 */ "limit_opt ::=",
 /* 156 */ "limit_opt ::= LIMIT expr",
 /* 157 */ "limit_opt ::= LIMIT expr OFFSET expr",
 /* 158 */ "limit_opt ::= LIMIT expr COMMA expr",
 /* 159 */ "cmd ::= DELETE FROM fullname where_opt limit_opt",
 /* 160 */ "where_opt ::=",
 /* 161 */ "where_opt ::= WHERE expr",
 /* 162 */ "cmd ::= UPDATE fullname SET setlist where_opt limit_opt",
 /* 163 */ "setlist ::= setlist COMMA nm EQ expr",
 /* 164 */ "setlist ::= nm EQ expr",
 /* 165 */ "cmd ::= insert_cmd INTO fullname inscollist_opt VALUES valueslist",
 /* 166 */ "cmd ::= insert_cmd INTO fullname inscollist_opt SET setlist",
 /* 167 */ "cmd ::= insert_cmd fullname inscollist_opt SET setlist",
 /* 168 */ "cmd ::= insert_cmd INTO fullname inscollist_opt select",
 /* 169 */ "insert_cmd ::= INSERT",
 /* 170 */ "insert_cmd ::= REPLACE",
 /* 171 */ "valueslist ::= valueslist COMMA LP itemlist RP",
 /* 172 */ "valueslist ::= LP itemlist RP",
 /* 173 */ "valueslist ::= LP RP",
 /* 174 */ "itemlist ::= itemlist COMMA expr",
 /* 175 */ "itemlist ::= expr",
 /* 176 */ "inscollist_opt ::=",
 /* 177 */ "inscollist_opt ::= LP RP",
 /* 178 */ "inscollist_opt ::= LP inscollist RP",
 /* 179 */ "inscollist ::= inscollist COMMA nm",
 /* 180 */ "inscollist ::= nm",
 /* 181 */ "expr ::= term",
 /* 182 */ "expr ::= LP expr RP",
 /* 183 */ "term ::= NULL",
 /* 184 */ "expr ::= ID",
 /* 185 */ "expr ::= JOIN_KW",
 /* 186 */ "expr ::= nm DOT nm",
 /* 187 */ "expr ::= nm DOT nm DOT nm",
 /* 188 */ "term ::= INTEGER|FLOAT|BLOB",
 /* 189 */ "term ::= STRING",
 /* 190 */ "expr ::= REGISTER",
 /* 191 */ "expr ::= VARIABLE",
 /* 192 */ "expr ::= VARIABLE1",
 /* 193 */ "expr ::= CAST LP expr AS typetoken RP",
 /* 194 */ "expr ::= ID LP distinct exprlist RP",
 /* 195 */ "expr ::= ID LP STAR RP",
 /* 196 */ "term ::= CTIME_KW",
 /* 197 */ "expr ::= expr AND expr",
 /* 198 */ "expr ::= expr OR expr",
 /* 199 */ "expr ::= expr LT|GT|GE|LE expr",
 /* 200 */ "expr ::= expr EQ|NE expr",
 /* 201 */ "expr ::= expr BITAND|BITOR|LSHIFT|RSHIFT expr",
 /* 202 */ "expr ::= expr PLUS|MINUS expr",
 /* 203 */ "expr ::= expr STAR|SLASH|REM expr",
 /* 204 */ "expr ::= expr CONCAT expr",
 /* 205 */ "likeop ::= LIKE_KW",
 /* 206 */ "likeop ::= NOT LIKE_KW",
 /* 207 */ "escape ::= ESCAPE expr",
 /* 208 */ "escape ::=",
 /* 209 */ "expr ::= expr likeop expr escape",
 /* 210 */ "expr ::= expr ISNULL|NOTNULL",
 /* 211 */ "expr ::= expr IS NULL",
 /* 212 */ "expr ::= expr NOT NULL",
 /* 213 */ "expr ::= expr IS NOT NULL",
 /* 214 */ "expr ::= NOT|BITNOT expr",
 /* 215 */ "expr ::= MINUS expr",
 /* 216 */ "expr ::= PLUS expr",
 /* 217 */ "between_op ::= BETWEEN",
 /* 218 */ "between_op ::= NOT BETWEEN",
 /* 219 */ "between_elem ::= INTEGER|STRING",
 /* 220 */ "expr ::= expr between_op between_elem AND between_elem",
 /* 221 */ "in_op ::= IN",
 /* 222 */ "in_op ::= NOT IN",
 /* 223 */ "expr ::= expr in_op LP exprlist RP",
 /* 224 */ "expr ::= LP select RP",
 /* 225 */ "expr ::= expr in_op LP select RP",
 /* 226 */ "expr ::= expr in_op nm dbnm",
 /* 227 */ "expr ::= EXISTS LP select RP",
 /* 228 */ "expr ::= CASE case_operand case_exprlist case_else END",
 /* 229 */ "case_exprlist ::= case_exprlist WHEN expr THEN expr",
 /* 230 */ "case_exprlist ::= WHEN expr THEN expr",
 /* 231 */ "case_else ::= ELSE expr",
 /* 232 */ "case_else ::=",
 /* 233 */ "case_operand ::= expr",
 /* 234 */ "case_operand ::=",
 /* 235 */ "exprlist ::= exprlist COMMA expritem",
 /* 236 */ "exprlist ::= expritem",
 /* 237 */ "expritem ::= expr",
 /* 238 */ "expritem ::=",
 /* 239 */ "idxlist_opt ::=",
 /* 240 */ "idxlist_opt ::= LP idxlist RP",
 /* 241 */ "idxlist ::= idxlist COMMA idxitem collate sortorder",
 /* 242 */ "idxlist ::= idxitem collate sortorder",
 /* 243 */ "idxitem ::= nm",
 /* 244 */ "plus_num ::= plus_opt number",
 /* 245 */ "minus_num ::= MINUS number",
 /* 246 */ "number ::= INTEGER|FLOAT",
 /* 247 */ "plus_opt ::= PLUS",
 /* 248 */ "plus_opt ::=",
 /* 249 */ "raisetype ::= ROLLBACK",
 /* 250 */ "raisetype ::= ABORT",
 /* 251 */ "raisetype ::= FAIL",
 /* 252 */ "cmd ::= SET variable_assignment_list",
 /* 253 */ "cmd ::= SET NAMES ids",
 /* 254 */ "cmd ::= SET CHARACTER SET ids",
 /* 255 */ "variable_assignment_list ::= variable_assignment_list COMMA scope_qualifier user_var_name EQ expr",
 /* 256 */ "variable_assignment_list ::= scope_qualifier user_var_name EQ expr",
 /* 257 */ "scope_qualifier ::= GLOBAL",
 /* 258 */ "scope_qualifier ::= LOCAL",
 /* 259 */ "scope_qualifier ::= SESSION",
 /* 260 */ "scope_qualifier ::= VARIABLE1 DOT",
 /* 261 */ "scope_qualifier ::=",
 /* 262 */ "user_var_name ::= ids",
 /* 263 */ "user_var_name ::= VARIABLE",
 /* 264 */ "cmd ::= show_databes",
 /* 265 */ "cmd ::= show_tables",
 /* 266 */ "show_databes ::= SHOW DATABASES|SCHEMAS",
 /* 267 */ "show_tables ::= SHOW full_keyword TABLES from_db",
 /* 268 */ "full_keyword ::= JOIN_KW",
 /* 269 */ "full_keyword ::=",
 /* 270 */ "from_db ::=",
 /* 271 */ "from_db ::= FROM|IN nm",
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
#line 391 "parse.y"
{sqlite3SelectDelete((yypminor->yy149));}
#line 1171 "parse.c"
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
#line 669 "parse.y"
{sqlite3ExprDelete((yypminor->yy342));}
#line 1186 "parse.c"
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
#line 913 "parse.y"
{sqlite3ExprListDelete((yypminor->yy462));}
#line 1201 "parse.c"
      break;
    case 196:
    case 201:
    case 209:
    case 210:
#line 519 "parse.y"
{sqlite3SrcListDelete((yypminor->yy287));}
#line 1209 "parse.c"
      break;
    case 206:
#line 580 "parse.y"
{
  sqlite3ExprDelete((yypminor->yy474).pLimit);
  sqlite3ExprDelete((yypminor->yy474).pOffset);
}
#line 1217 "parse.c"
      break;
    case 213:
    case 216:
    case 223:
#line 536 "parse.y"
{sqlite3IdListDelete((yypminor->yy440));}
#line 1224 "parse.c"
      break;
    case 224:
#line 640 "parse.y"
{sqlite3ValuesListDelete((yypminor->yy49));}
#line 1229 "parse.c"
      break;
    case 238:
#line 1129 "parse.y"
{ sqlite3ExprListDelete((yypminor->yy462)); }
#line 1234 "parse.c"
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
#line 1386 "parse.c"
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
  { 149, 3 },
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
      case 4:
#line 98 "parse.y"
{ sqlite3FinishCoding(pParse); }
#line 1737 "parse.c"
        break;
      case 7:
#line 102 "parse.y"
{ sqlite3BeginParse(pParse, 0); }
#line 1742 "parse.c"
        break;
      case 8:
#line 104 "parse.y"
{ sqlite3BeginParse(pParse, 1); }
#line 1747 "parse.c"
        break;
      case 9:
#line 105 "parse.y"
{ sqlite3BeginParse(pParse, 2); }
#line 1752 "parse.c"
        break;
      case 10:
#line 112 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_BEGIN);}
#line 1757 "parse.c"
        break;
      case 11:
#line 113 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_START);}
#line 1762 "parse.c"
        break;
      case 14:
#line 124 "parse.y"
{sqlite3CommitTransaction(pParse);}
#line 1767 "parse.c"
        break;
      case 15:
#line 126 "parse.y"
{sqlite3RollbackTransaction(pParse);}
#line 1772 "parse.c"
        break;
      case 17:
#line 131 "parse.y"
{
   sqlite3StartTable(pParse, 0, 0, 0, 0, 0);
}
#line 1779 "parse.c"
        break;
      case 18:
      case 21:
      case 67:
      case 81:
      case 83:
      case 94:
      case 103:
      case 112:
      case 113:
      case 217:
      case 221:
#line 136 "parse.y"
{yygotominor.yy32 = 0;}
#line 1794 "parse.c"
        break;
      case 19:
      case 20:
      case 68:
      case 82:
      case 102:
      case 111:
      case 218:
      case 222:
#line 137 "parse.y"
{yygotominor.yy32 = 1;}
#line 1806 "parse.c"
        break;
      case 22:
#line 143 "parse.y"
{
  //sqlite3EndTable(pParse,&X,&Y,0);
}
#line 1813 "parse.c"
        break;
      case 23:
#line 146 "parse.y"
{
  sqlite3EndTable(pParse,0,0,0);
  //sqlite3SelectDelete(S);
  yy_destructor(162,&yymsp[0].minor);
}
#line 1822 "parse.c"
        break;
      case 33:
#line 168 "parse.y"
{
  //A.z = X.z;
  //A.n = (pParse->sLastToken.z-X.z) + pParse->sLastToken.n;
}
#line 1830 "parse.c"
        break;
      case 34:
#line 172 "parse.y"
{
  //sqlite3AddColumn(pParse,&X);
  //A = X;
}
#line 1838 "parse.c"
        break;
      case 35:
      case 36:
      case 37:
      case 38:
      case 39:
      case 246:
#line 182 "parse.y"
{yygotominor.yy308 = yymsp[0].minor.yy0;}
#line 1848 "parse.c"
        break;
      case 41:
#line 241 "parse.y"
{ /*sqlite3AddColumnType(pParse,&X);*/ }
#line 1853 "parse.c"
        break;
      case 42:
      case 45:
      case 119:
      case 120:
      case 131:
      case 150:
      case 243:
      case 244:
      case 245:
#line 242 "parse.y"
{yygotominor.yy308 = yymsp[0].minor.yy308;}
#line 1866 "parse.c"
        break;
      case 43:
#line 243 "parse.y"
{
  yygotominor.yy308.z = yymsp[-3].minor.yy308.z;
  yygotominor.yy308.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-3].minor.yy308.z;
}
#line 1874 "parse.c"
        break;
      case 44:
#line 247 "parse.y"
{
  yygotominor.yy308.z = yymsp[-5].minor.yy308.z;
  yygotominor.yy308.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-5].minor.yy308.z;
}
#line 1882 "parse.c"
        break;
      case 46:
#line 253 "parse.y"
{yygotominor.yy308.z=yymsp[-1].minor.yy308.z; yygotominor.yy308.n=yymsp[0].minor.yy308.n+(yymsp[0].minor.yy308.z-yymsp[-1].minor.yy308.z);}
#line 1887 "parse.c"
        break;
      case 47:
#line 255 "parse.y"
{ yygotominor.yy32 = atoi((char*)yymsp[0].minor.yy308.z); }
#line 1892 "parse.c"
        break;
      case 48:
#line 256 "parse.y"
{ yygotominor.yy32 = -atoi((char*)yymsp[0].minor.yy308.z); }
#line 1897 "parse.c"
        break;
      case 53:
#line 265 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/   yy_destructor(177,&yymsp[0].minor);
}
#line 1903 "parse.c"
        break;
      case 54:
#line 266 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/ }
#line 1908 "parse.c"
        break;
      case 55:
#line 267 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/  yy_destructor(177,&yymsp[0].minor);
}
#line 1914 "parse.c"
        break;
      case 56:
#line 268 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_UMINUS, X, 0, 0);
  //sqlite3AddDefaultValue(pParse,p);
  yy_destructor(177,&yymsp[0].minor);
}
#line 1923 "parse.c"
        break;
      case 57:
#line 272 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_STRING, 0, 0, &X);
  //sqlite3AddDefaultValue(pParse,p);
}
#line 1931 "parse.c"
        break;
      case 60:
#line 282 "parse.y"
{/*sqlite3AddNotNull(pParse, R);*/}
#line 1936 "parse.c"
        break;
      case 61:
#line 284 "parse.y"
{/*sqlite3AddPrimaryKey(pParse,0,R,I,Z);*/}
#line 1941 "parse.c"
        break;
      case 62:
#line 285 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,0,R,0,0,0,0);*/}
#line 1946 "parse.c"
        break;
      case 63:
#line 286 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,X);*/  sqlite3ExprDelete(yymsp[-1].minor.yy342); }
#line 1951 "parse.c"
        break;
      case 64:
#line 288 "parse.y"
{/*sqlite3CreateForeignKey(pParse,0,&T,TA,R);*/ sqlite3ExprListDelete(yymsp[-1].minor.yy462); }
#line 1956 "parse.c"
        break;
      case 65:
#line 289 "parse.y"
{/*sqlite3DeferForeignKey(pParse,D);*/}
#line 1961 "parse.c"
        break;
      case 66:
#line 290 "parse.y"
{/*sqlite3AddCollateType(pParse, (char*)C.z, C.n);*/}
#line 1966 "parse.c"
        break;
      case 69:
#line 303 "parse.y"
{ yygotominor.yy32 = OE_Restrict * 0x010101; }
#line 1971 "parse.c"
        break;
      case 70:
#line 304 "parse.y"
{ yygotominor.yy32 = (yymsp[-1].minor.yy32 & yymsp[0].minor.yy47.mask) | yymsp[0].minor.yy47.value; }
#line 1976 "parse.c"
        break;
      case 71:
#line 306 "parse.y"
{ yygotominor.yy47.value = 0;     yygotominor.yy47.mask = 0x000000; }
#line 1981 "parse.c"
        break;
      case 72:
#line 307 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32;     yygotominor.yy47.mask = 0x0000ff; }
#line 1986 "parse.c"
        break;
      case 73:
#line 308 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32<<8;  yygotominor.yy47.mask = 0x00ff00; }
#line 1991 "parse.c"
        break;
      case 74:
#line 309 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32<<16; yygotominor.yy47.mask = 0xff0000; }
#line 1996 "parse.c"
        break;
      case 75:
#line 311 "parse.y"
{ yygotominor.yy32 = OE_SetNull; }
#line 2001 "parse.c"
        break;
      case 76:
#line 312 "parse.y"
{ yygotominor.yy32 = OE_SetDflt; }
#line 2006 "parse.c"
        break;
      case 77:
#line 313 "parse.y"
{ yygotominor.yy32 = OE_Cascade; }
#line 2011 "parse.c"
        break;
      case 78:
#line 314 "parse.y"
{ yygotominor.yy32 = OE_Restrict; }
#line 2016 "parse.c"
        break;
      case 79:
      case 80:
      case 95:
      case 97:
      case 98:
#line 316 "parse.y"
{yygotominor.yy32 = yymsp[0].minor.yy32;}
#line 2025 "parse.c"
        break;
      case 90:
#line 335 "parse.y"
{ sqlite3ExprListDelete(yymsp[-3].minor.yy462); }
#line 2030 "parse.c"
        break;
      case 91:
#line 337 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,yymsp[-2].minor.yy462,R,0,0,0,0);*/ sqlite3ExprListDelete(yymsp[-2].minor.yy462);}
#line 2035 "parse.c"
        break;
      case 92:
#line 338 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,yymsp[-2].minor.yy342);*/ sqlite3ExprDelete(yymsp[-2].minor.yy342);}
#line 2040 "parse.c"
        break;
      case 93:
#line 340 "parse.y"
{ 
        sqlite3ExprListDelete(yymsp[-6].minor.yy462);
        sqlite3ExprListDelete(yymsp[-2].minor.yy462);
 }
#line 2048 "parse.c"
        break;
      case 96:
#line 355 "parse.y"
{yygotominor.yy32 = OE_Default;}
#line 2053 "parse.c"
        break;
      case 99:
#line 360 "parse.y"
{yygotominor.yy32 = OE_Ignore;}
#line 2058 "parse.c"
        break;
      case 100:
      case 170:
#line 361 "parse.y"
{yygotominor.yy32 = OE_Replace;}
#line 2064 "parse.c"
        break;
      case 101:
#line 365 "parse.y"
{
  sqlite3DropTable(pParse, yymsp[0].minor.yy287, 0, yymsp[-1].minor.yy32);
}
#line 2071 "parse.c"
        break;
      case 104:
#line 385 "parse.y"
{
  sqlite3Select(pParse, yymsp[0].minor.yy149, SRT_Callback, 0, 0, 0, 0, 0);
  // sqlite3SelectDelete(yymsp[0].minor.yy149);
}
#line 2079 "parse.c"
        break;
      case 105:
      case 128:
#line 395 "parse.y"
{yygotominor.yy149 = yymsp[0].minor.yy149;}
#line 2085 "parse.c"
        break;
      case 106:
#line 397 "parse.y"
{
  if( yymsp[0].minor.yy149 ){
    yymsp[0].minor.yy149->op = yymsp[-1].minor.yy32;
    yymsp[0].minor.yy149->pPrior = yymsp[-2].minor.yy149;
  }
  yygotominor.yy149 = yymsp[0].minor.yy149;
}
#line 2096 "parse.c"
        break;
      case 107:
      case 109:
#line 405 "parse.y"
{yygotominor.yy32 = yymsp[0].major;}
#line 2102 "parse.c"
        break;
      case 108:
#line 406 "parse.y"
{yygotominor.yy32 = TK_ALL;}
#line 2107 "parse.c"
        break;
      case 110:
#line 410 "parse.y"
{
  yygotominor.yy149 = sqlite3SelectNew(yymsp[-6].minor.yy462,yymsp[-5].minor.yy287,yymsp[-4].minor.yy342,yymsp[-3].minor.yy462,yymsp[-2].minor.yy342,yymsp[-1].minor.yy462,yymsp[-7].minor.yy32,yymsp[0].minor.yy474.pLimit,yymsp[0].minor.yy474.pOffset);
}
#line 2114 "parse.c"
        break;
      case 114:
      case 240:
#line 431 "parse.y"
{yygotominor.yy462 = yymsp[-1].minor.yy462;}
#line 2120 "parse.c"
        break;
      case 115:
      case 141:
      case 151:
      case 239:
#line 432 "parse.y"
{yygotominor.yy462 = 0;}
#line 2128 "parse.c"
        break;
      case 116:
#line 433 "parse.y"
{
   yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-2].minor.yy462,yymsp[-1].minor.yy342,yymsp[0].minor.yy308.n?&yymsp[0].minor.yy308:0);
}
#line 2135 "parse.c"
        break;
      case 117:
#line 436 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-1].minor.yy462, sqlite3Expr(TK_ALL, 0, 0, 0), 0);
}
#line 2142 "parse.c"
        break;
      case 118:
#line 439 "parse.y"
{
  Expr *pRight = sqlite3Expr(TK_ALL, 0, 0, 0);
  Expr *pLeft = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-3].minor.yy462, sqlite3Expr(TK_DOT, pLeft, pRight, 0), 0);
}
#line 2151 "parse.c"
        break;
      case 121:
#line 451 "parse.y"
{yygotominor.yy308.n = 0;}
#line 2156 "parse.c"
        break;
      case 122:
#line 463 "parse.y"
{yygotominor.yy287 = sqliteMalloc(sizeof(*yygotominor.yy287));}
#line 2161 "parse.c"
        break;
      case 123:
#line 464 "parse.y"
{yygotominor.yy287 = yymsp[0].minor.yy287;}
#line 2166 "parse.c"
        break;
      case 124:
#line 469 "parse.y"
{
   yygotominor.yy287 = yymsp[-1].minor.yy287;
   if( yygotominor.yy287 && yygotominor.yy287->nSrc>0 ) yygotominor.yy287->a[yygotominor.yy287->nSrc-1].jointype = yymsp[0].minor.yy32;
}
#line 2174 "parse.c"
        break;
      case 125:
#line 473 "parse.y"
{yygotominor.yy287 = 0;}
#line 2179 "parse.c"
        break;
      case 126:
#line 474 "parse.y"
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
#line 2195 "parse.c"
        break;
      case 127:
#line 488 "parse.y"
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
#line 2212 "parse.c"
        break;
      case 129:
#line 509 "parse.y"
{
     yygotominor.yy149 = sqlite3SelectNew(0,yymsp[0].minor.yy287,0,0,0,0,0,0,0);
  }
#line 2219 "parse.c"
        break;
      case 130:
#line 515 "parse.y"
{yygotominor.yy308.z=0; yygotominor.yy308.n=0;}
#line 2224 "parse.c"
        break;
      case 132:
#line 520 "parse.y"
{yygotominor.yy287 = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy308,&yymsp[0].minor.yy308);}
#line 2229 "parse.c"
        break;
      case 133:
#line 524 "parse.y"
{ yygotominor.yy32 = JT_INNER; }
#line 2234 "parse.c"
        break;
      case 134:
#line 525 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-1].minor.yy0,0,0); }
#line 2239 "parse.c"
        break;
      case 135:
#line 526 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-2].minor.yy0,&yymsp[-1].minor.yy308,0); }
#line 2244 "parse.c"
        break;
      case 136:
#line 528 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-3].minor.yy0,&yymsp[-2].minor.yy308,&yymsp[-1].minor.yy308); }
#line 2249 "parse.c"
        break;
      case 137:
      case 145:
      case 154:
      case 161:
      case 181:
      case 207:
      case 231:
      case 233:
      case 237:
#line 532 "parse.y"
{yygotominor.yy342 = yymsp[0].minor.yy342;}
#line 2262 "parse.c"
        break;
      case 138:
      case 153:
      case 160:
      case 208:
      case 232:
      case 234:
      case 238:
#line 533 "parse.y"
{yygotominor.yy342 = 0;}
#line 2273 "parse.c"
        break;
      case 139:
      case 178:
#line 537 "parse.y"
{yygotominor.yy440 = yymsp[-1].minor.yy440;}
#line 2279 "parse.c"
        break;
      case 140:
      case 176:
      case 177:
#line 538 "parse.y"
{yygotominor.yy440 = 0;}
#line 2286 "parse.c"
        break;
      case 142:
      case 152:
#line 549 "parse.y"
{yygotominor.yy462 = yymsp[0].minor.yy462;}
#line 2292 "parse.c"
        break;
      case 143:
#line 550 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462,yymsp[-2].minor.yy342,yymsp[-1].minor.yy308.n>0?&yymsp[-1].minor.yy308:0);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2300 "parse.c"
        break;
      case 144:
#line 554 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[-2].minor.yy342,yymsp[-1].minor.yy308.n>0?&yymsp[-1].minor.yy308:0);
  if( yygotominor.yy462 && yygotominor.yy462->a ) yygotominor.yy462->a[0].sortOrder = yymsp[0].minor.yy32;
}
#line 2308 "parse.c"
        break;
      case 146:
      case 148:
#line 563 "parse.y"
{yygotominor.yy32 = SQLITE_SO_ASC;}
#line 2314 "parse.c"
        break;
      case 147:
#line 564 "parse.y"
{yygotominor.yy32 = SQLITE_SO_DESC;}
#line 2319 "parse.c"
        break;
      case 149:
#line 566 "parse.y"
{yygotominor.yy308.z = 0; yygotominor.yy308.n = 0;}
#line 2324 "parse.c"
        break;
      case 155:
#line 584 "parse.y"
{yygotominor.yy474.pLimit = 0; yygotominor.yy474.pOffset = 0;}
#line 2329 "parse.c"
        break;
      case 156:
#line 585 "parse.y"
{yygotominor.yy474.pLimit = yymsp[0].minor.yy342; yygotominor.yy474.pOffset = 0;}
#line 2334 "parse.c"
        break;
      case 157:
#line 587 "parse.y"
{yygotominor.yy474.pLimit = yymsp[-2].minor.yy342; yygotominor.yy474.pOffset = yymsp[0].minor.yy342;}
#line 2339 "parse.c"
        break;
      case 158:
#line 589 "parse.y"
{yygotominor.yy474.pOffset = yymsp[-2].minor.yy342; yygotominor.yy474.pLimit = yymsp[0].minor.yy342;}
#line 2344 "parse.c"
        break;
      case 159:
#line 593 "parse.y"
{sqlite3DeleteFrom(pParse,yymsp[-2].minor.yy287,yymsp[-1].minor.yy342, yymsp[0].minor.yy474.pLimit, yymsp[0].minor.yy474.pOffset);}
#line 2349 "parse.c"
        break;
      case 162:
#line 605 "parse.y"
{sqlite3Update(pParse,yymsp[-4].minor.yy287,yymsp[-2].minor.yy462,yymsp[-1].minor.yy342,OE_Default, yymsp[0].minor.yy474.pLimit, yymsp[0].minor.yy474.pOffset);}
#line 2354 "parse.c"
        break;
      case 163:
#line 611 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462,yymsp[0].minor.yy342,&yymsp[-2].minor.yy308);}
#line 2359 "parse.c"
        break;
      case 164:
#line 612 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[0].minor.yy342,&yymsp[-2].minor.yy308);}
#line 2364 "parse.c"
        break;
      case 165:
#line 621 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, 0, yymsp[0].minor.yy49, 0, yymsp[-2].minor.yy440, yymsp[-5].minor.yy32);}
#line 2369 "parse.c"
        break;
      case 166:
#line 625 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, yymsp[0].minor.yy462, 0, 0, yymsp[-2].minor.yy440, yymsp[-5].minor.yy32);}
#line 2374 "parse.c"
        break;
      case 167:
#line 629 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, yymsp[0].minor.yy462, 0, 0, yymsp[-2].minor.yy440, yymsp[-4].minor.yy32);}
#line 2379 "parse.c"
        break;
      case 168:
#line 632 "parse.y"
{sqlite3Insert(pParse, yymsp[-2].minor.yy287, 0, 0, yymsp[0].minor.yy149, yymsp[-1].minor.yy440, yymsp[-4].minor.yy32);}
#line 2384 "parse.c"
        break;
      case 169:
#line 636 "parse.y"
{ yygotominor.yy32 = OE_Default; }
#line 2389 "parse.c"
        break;
      case 171:
#line 642 "parse.y"
{ yygotominor.yy49 = sqlite3ValuesListAppend(yymsp[-4].minor.yy49, yymsp[-1].minor.yy462);}
#line 2394 "parse.c"
        break;
      case 172:
#line 643 "parse.y"
{ yygotominor.yy49 = sqlite3ValuesListAppend(0, yymsp[-1].minor.yy462); }
#line 2399 "parse.c"
        break;
      case 173:
#line 644 "parse.y"
{ yygotominor.yy49 = 0; }
#line 2404 "parse.c"
        break;
      case 174:
      case 235:
#line 649 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-2].minor.yy462,yymsp[0].minor.yy342,0);}
#line 2410 "parse.c"
        break;
      case 175:
      case 236:
#line 650 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[0].minor.yy342,0);}
#line 2416 "parse.c"
        break;
      case 179:
#line 660 "parse.y"
{yygotominor.yy440 = sqlite3IdListAppend(yymsp[-2].minor.yy440,&yymsp[0].minor.yy308);}
#line 2421 "parse.c"
        break;
      case 180:
#line 661 "parse.y"
{yygotominor.yy440 = sqlite3IdListAppend(0,&yymsp[0].minor.yy308);}
#line 2426 "parse.c"
        break;
      case 182:
#line 672 "parse.y"
{yygotominor.yy342 = yymsp[-1].minor.yy342; sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0); }
#line 2431 "parse.c"
        break;
      case 183:
      case 188:
      case 189:
#line 673 "parse.y"
{yygotominor.yy342 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0);}
#line 2438 "parse.c"
        break;
      case 184:
      case 185:
#line 674 "parse.y"
{yygotominor.yy342 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy0);}
#line 2444 "parse.c"
        break;
      case 186:
#line 676 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy308);
  yygotominor.yy342 = sqlite3Expr(TK_DOT, temp1, temp2, 0);
}
#line 2453 "parse.c"
        break;
      case 187:
#line 681 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-4].minor.yy308);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  Expr *temp3 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy308);
  Expr *temp4 = sqlite3Expr(TK_DOT, temp2, temp3, 0);
  yygotominor.yy342 = sqlite3Expr(TK_DOT, temp1, temp4, 0);
}
#line 2464 "parse.c"
        break;
      case 190:
#line 690 "parse.y"
{yygotominor.yy342 = sqlite3RegisterExpr(pParse, &yymsp[0].minor.yy0);}
#line 2469 "parse.c"
        break;
      case 191:
      case 192:
#line 691 "parse.y"
{
  Token *pToken = &yymsp[0].minor.yy0;
  Expr *pExpr = yygotominor.yy342 = sqlite3Expr(TK_VARIABLE, 0, 0, pToken);
  //sqlite3ExprAssignVarNumber(pParse, pExpr);
}
#line 2479 "parse.c"
        break;
      case 193:
#line 702 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_CAST, yymsp[-3].minor.yy342, 0, &yymsp[-1].minor.yy308);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-5].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2487 "parse.c"
        break;
      case 194:
#line 707 "parse.y"
{
  yygotominor.yy342 = sqlite3ExprFunction(yymsp[-1].minor.yy462, &yymsp[-4].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-4].minor.yy0,&yymsp[0].minor.yy0);
  if( yymsp[-2].minor.yy32 && yygotominor.yy342 ){
    yygotominor.yy342->flags |= EP_Distinct;
  }
}
#line 2498 "parse.c"
        break;
      case 195:
#line 714 "parse.y"
{
  yygotominor.yy342 = sqlite3ExprFunction(0, &yymsp[-3].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2506 "parse.c"
        break;
      case 196:
#line 718 "parse.y"
{
  /* The CURRENT_TIME, CURRENT_DATE, and CURRENT_TIMESTAMP values are
  ** treated as functions that return constants */
  yygotominor.yy342 = sqlite3ExprFunction(0,&yymsp[0].minor.yy0);
  if( yygotominor.yy342 ) yygotominor.yy342->op = TK_CONST_FUNC;  
}
#line 2516 "parse.c"
        break;
      case 197:
      case 198:
      case 199:
      case 200:
      case 201:
      case 202:
      case 203:
      case 204:
#line 724 "parse.y"
{yygotominor.yy342 = sqlite3Expr(yymsp[-1].major, yymsp[-2].minor.yy342, yymsp[0].minor.yy342, 0);}
#line 2528 "parse.c"
        break;
      case 205:
#line 734 "parse.y"
{yygotominor.yy118.eOperator = yymsp[0].minor.yy0; yygotominor.yy118.not = 0;}
#line 2533 "parse.c"
        break;
      case 206:
#line 735 "parse.y"
{yygotominor.yy118.eOperator = yymsp[0].minor.yy0; yygotominor.yy118.not = 1;}
#line 2538 "parse.c"
        break;
      case 209:
#line 740 "parse.y"
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
#line 2554 "parse.c"
        break;
      case 210:
#line 753 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(yymsp[0].major, yymsp[-1].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2562 "parse.c"
        break;
      case 211:
#line 757 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_ISNULL, yymsp[-2].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2570 "parse.c"
        break;
      case 212:
#line 761 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_NOTNULL, yymsp[-2].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2578 "parse.c"
        break;
      case 213:
#line 765 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_NOTNULL, yymsp[-3].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-3].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2586 "parse.c"
        break;
      case 214:
#line 769 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(yymsp[-1].major, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2594 "parse.c"
        break;
      case 215:
#line 773 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_UMINUS, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2602 "parse.c"
        break;
      case 216:
#line 777 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_UPLUS, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2610 "parse.c"
        break;
      case 219:
#line 788 "parse.y"
{ yygotominor.yy342 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0); }
#line 2615 "parse.c"
        break;
      case 220:
#line 791 "parse.y"
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
#line 2631 "parse.c"
        break;
      case 223:
#line 807 "parse.y"
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
#line 2645 "parse.c"
        break;
      case 224:
#line 817 "parse.y"
{
    yygotominor.yy342 = sqlite3Expr(TK_SELECT, 0, 0, 0);
    if( yygotominor.yy342 ){
      yygotominor.yy342->pSelect = yymsp[-1].minor.yy149;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy149);
    }
    sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0);
  }
#line 2658 "parse.c"
        break;
      case 225:
#line 826 "parse.y"
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
#line 2672 "parse.c"
        break;
      case 226:
#line 836 "parse.y"
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
#line 2687 "parse.c"
        break;
      case 227:
#line 847 "parse.y"
{
    Expr *p = yygotominor.yy342 = sqlite3Expr(TK_EXISTS, 0, 0, 0);
    if( p ){
      p->pSelect = yymsp[-1].minor.yy149;
      sqlite3ExprSpan(p,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy149);
    }
  }
#line 2700 "parse.c"
        break;
      case 228:
#line 859 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_CASE, yymsp[-3].minor.yy342, yymsp[-1].minor.yy342, 0);
  if( yygotominor.yy342 ){
    yygotominor.yy342->pList = yymsp[-2].minor.yy462;
  }else{
    sqlite3ExprListDelete(yymsp[-2].minor.yy462);
  }
  sqlite3ExprSpan(yygotominor.yy342, &yymsp[-4].minor.yy0, &yymsp[0].minor.yy0);
}
#line 2713 "parse.c"
        break;
      case 229:
#line 870 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462, yymsp[-2].minor.yy342, 0);
  yygotominor.yy462 = sqlite3ExprListAppend(yygotominor.yy462, yymsp[0].minor.yy342, 0);
}
#line 2721 "parse.c"
        break;
      case 230:
#line 874 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(0, yymsp[-2].minor.yy342, 0);
  yygotominor.yy462 = sqlite3ExprListAppend(yygotominor.yy462, yymsp[0].minor.yy342, 0);
}
#line 2729 "parse.c"
        break;
      case 241:
#line 918 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy308.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy308.z, yymsp[-1].minor.yy308.n);
  }
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462, p, &yymsp[-2].minor.yy308);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2742 "parse.c"
        break;
      case 242:
#line 927 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy308.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy308.z, yymsp[-1].minor.yy308.n);
  }
  yygotominor.yy462 = sqlite3ExprListAppend(0, p, &yymsp[-2].minor.yy308);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2755 "parse.c"
        break;
      case 249:
#line 1058 "parse.y"
{yygotominor.yy32 = OE_Rollback;}
#line 2760 "parse.c"
        break;
      case 250:
#line 1059 "parse.y"
{yygotominor.yy32 = OE_Abort;}
#line 2765 "parse.c"
        break;
      case 251:
#line 1060 "parse.y"
{yygotominor.yy32 = OE_Fail;}
#line 2770 "parse.c"
        break;
      case 252:
#line 1116 "parse.y"
{
    sqlite3SetStatement(pParse, yymsp[0].minor.yy462, 0, SQLTYPE_SET);
}
#line 2777 "parse.c"
        break;
      case 253:
#line 1120 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy308, SQLTYPE_SET_NAMES);   
}
#line 2784 "parse.c"
        break;
      case 254:
#line 1124 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy308, SQLTYPE_SET_CHARACTER_SET);
}
#line 2791 "parse.c"
        break;
      case 255:
#line 1130 "parse.y"
{
    yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-5].minor.yy462, yymsp[0].minor.yy342, &yymsp[-2].minor.yy308);
}
#line 2798 "parse.c"
        break;
      case 256:
#line 1134 "parse.y"
{
    yygotominor.yy462 = sqlite3ExprListAppend(0, yymsp[0].minor.yy342, &yymsp[-2].minor.yy308);                         
}
#line 2805 "parse.c"
        break;
      case 260:
#line 1142 "parse.y"
{ sqlite3CheckSetScope(pParse, &yymsp[-1].minor.yy0); }
#line 2810 "parse.c"
        break;
      case 262:
#line 1146 "parse.y"
{ yygotominor.yy308 = yymsp[0].minor.yy308; }
#line 2815 "parse.c"
        break;
      case 263:
#line 1147 "parse.y"
{ yygotominor.yy308 = yymsp[0].minor.yy0; }
#line 2820 "parse.c"
        break;
      case 266:
#line 1153 "parse.y"
{
    sqlite3ShowStatement(pParse, yymsp[0].major);
}
#line 2827 "parse.c"
        break;
      case 267:
#line 1157 "parse.y"
{
    sqlite3ShowStatement(pParse, yymsp[-1].major);
}
#line 2834 "parse.c"
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
#line 2901 "parse.c"
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
