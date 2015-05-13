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
#define YYNOCODE 251
#define YYACTIONTYPE unsigned short int
#define sqlite3ParserTOKENTYPE Token
typedef union {
  sqlite3ParserTOKENTYPE yy0;
  struct LimitVal yy64;
  Expr* yy122;
  ValuesList* yy139;
  Select* yy159;
  IdList* yy180;
  struct {int value; int mask;} yy207;
  Token yy278;
  struct LikeOp yy318;
  SrcList* yy347;
  int yy392;
  ExprList* yy442;
  int yy501;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define sqlite3ParserARG_SDECL Parse *pParse;
#define sqlite3ParserARG_PDECL ,Parse *pParse
#define sqlite3ParserARG_FETCH Parse *pParse = yypParser->pParse
#define sqlite3ParserARG_STORE yypParser->pParse = pParse
#define YYNSTATE 507
#define YYNRULE 278
#define YYERRORSYMBOL 147
#define YYERRSYMDT yy501
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
 /*     0 */   237,  324,  321,  149,  342,  372,   57,   56,   56,   56,
 /*    10 */    56,  446,   58,   58,   58,   58,   59,   59,   60,   60,
 /*    20 */    60,   61,   63,   58,   58,   58,   58,   59,   59,   60,
 /*    30 */    60,   60,   61,  385,   58,   58,   58,   58,   59,   59,
 /*    40 */    60,   60,   60,   61,   59,   59,   60,   60,   60,   61,
 /*    50 */    55,   53,  245,  393,  396,  390,  390,   57,   56,   56,
 /*    60 */    56,   56,  168,   58,   58,   58,   58,   59,   59,   60,
 /*    70 */    60,   60,   61,  237,  226,  241,  372,   72,  277,   57,
 /*    80 */   398,  398,   99,  314,  154,  216,  241,  457,  182,  315,
 /*    90 */   486,  487,  488,  337,    3,   18,  216,  338,  449,  320,
 /*   100 */   325,  270,   61,  166,  132,  446,  385,   62,  407,  172,
 /*   110 */    52,  134,  162,  232,  339,  786,  106,  506,  131,  467,
 /*   120 */     1,  362,   36,   55,   53,  245,  393,  396,  390,  390,
 /*   130 */    57,   56,   56,   56,   56,  238,   58,   58,   58,   58,
 /*   140 */    59,   59,   60,   60,   60,   61,  237,  363,  257,   94,
 /*   150 */   339,  166,   57,  142,  343,  192,  266,  196,  267,  153,
 /*   160 */   162,  281,  207,  466,  217,  343,  192,  266,  196,  267,
 /*   170 */   153,  323,  104,  507,    1,  217,  324,  321,  158,  385,
 /*   180 */   318,  289,  292,  293,  234,  340,  341,  382,  456,  146,
 /*   190 */   294,  492,  493,  494,  495,  363,   55,   53,  245,  393,
 /*   200 */   396,  390,  390,   57,   56,   56,   56,   56,  437,   58,
 /*   210 */    58,   58,   58,   59,   59,   60,   60,   60,   61,  237,
 /*   220 */   104,  340,  341,  158,  163,   57,  289,  292,  293,  149,
 /*   230 */   270,  372,   62,  384,  172,  294,  134,  270,  444,  492,
 /*   240 */   493,  494,  495,  158,  455,  270,  289,  292,  293,  372,
 /*   250 */   362,   30,  385,  450,  419,  294,  452,  362,   30,  503,
 /*   260 */   453,  382,  274,  146,  366,  362,   31,  380,  171,   55,
 /*   270 */    53,  245,  393,  396,  390,  390,   57,   56,   56,   56,
 /*   280 */    56,  436,   58,   58,   58,   58,   59,   59,   60,   60,
 /*   290 */    60,   61,  237,  425,  368,  368,  368,  314,   57,  419,
 /*   300 */   248,  270,  372,  270,  486,  487,  488,  403,  121,  121,
 /*   310 */   270,   62,  768,  172,  404,  134,  214,  480,  454,  203,
 /*   320 */   372,  362,   43,  362,   30,  385,  457,   74,  189,  256,
 /*   330 */   362,   36,  468,  465,   18,  433,  339,   68,  209,  428,
 /*   340 */   151,  464,   55,   53,  245,  393,  396,  390,  390,   57,
 /*   350 */    56,   56,   56,   56,  429,   58,   58,   58,   58,   59,
 /*   360 */    59,   60,   60,   60,   61,  270,  283,  349,  237,  254,
 /*   370 */   133,  205,  297,  270,   57,  363,   60,   60,   60,   61,
 /*   380 */   404,  399,  350,  339,   10,  362,   25,  152,  139,  244,
 /*   390 */   375,  376,  286,  362,   43,  273,  375,  376,  351,  339,
 /*   400 */   347,  385,  339,   74,  339,  363,  154,  340,  341,  458,
 /*   410 */    71,  348,  419,  400,  155,  156,  157,  226,   55,   53,
 /*   420 */   245,  393,  396,  390,  390,   57,   56,   56,   56,   56,
 /*   430 */   432,   58,   58,   58,   58,   59,   59,   60,   60,   60,
 /*   440 */    61,  253,   19,  412,  237,  277,  339,  398,  398,  444,
 /*   450 */    57,  211,  339,  170,  340,  341,  472,  238,  314,  170,
 /*   460 */   287,  217,  372,  427,  270,  486,  487,  488,  345,  346,
 /*   470 */   340,  341,  270,  340,  341,  340,  341,  385,  312,  120,
 /*   480 */   362,    4,  250,  423,  362,   26,  115,  277,  498,  398,
 /*   490 */   398,  204,  362,   21,   55,   53,  245,  393,  396,  390,
 /*   500 */   390,   57,   56,   56,   56,   56,  451,   58,   58,   58,
 /*   510 */    58,   59,   59,   60,   60,   60,   61,  340,  341,  277,
 /*   520 */   237,  398,  398,  340,  341,  444,   57,  215,  270,  444,
 /*   530 */   270,  496,  414,  372,  270,  444,  270,  319,  128,  270,
 /*   540 */   197,  415,  255,  270,  317,  306,  386,  416,  362,   29,
 /*   550 */   362,   48,  423,  385,  362,   22,  362,   46,  180,  362,
 /*   560 */    85,  138,  251,  362,   83,  372,  388,  389,  252,  484,
 /*   570 */    55,   53,  245,  393,  396,  390,  390,   57,   56,   56,
 /*   580 */    56,   56,  220,   58,   58,   58,   58,   59,   59,   60,
 /*   590 */    60,   60,   61,  387,  284,  270,  237,  270,  226,  270,
 /*   600 */   135,  270,   57,  215,  270,  137,  270,  215,  208,  181,
 /*   610 */   270,  247,  270,  215,  484,  362,   30,  362,   87,  362,
 /*   620 */    88,  362,   95,  270,  362,   96,  362,   16,  414,  385,
 /*   630 */   362,   86,  362,   47,  271,  363,  372,  227,  226,  100,
 /*   640 */   313,  306,  226,  362,   97,  119,   55,   53,  245,  393,
 /*   650 */   396,  390,  390,   57,   56,   56,   56,   56,  246,   58,
 /*   660 */    58,   58,   58,   59,   59,   60,   60,   60,   61,  237,
 /*   670 */   270,  498,  404,  270,  485,   57,  270,  304,  270,  249,
 /*   680 */   270,  230,  306,  270,  117,  316,  270,  438,  270,  288,
 /*   690 */   362,   98,   17,  362,   23,    6,  362,   32,  362,   33,
 /*   700 */   362,   24,  385,  362,   34,  309,  362,   35,  362,   37,
 /*   710 */   126,  439,  498,  361,  499,  164,   67,  360,   69,   55,
 /*   720 */    53,  245,  393,  396,  390,  390,   57,   56,   56,   56,
 /*   730 */    56,  270,   58,   58,   58,   58,   59,   59,   60,   60,
 /*   740 */    60,   61,  237,  270,  498,  270,  311,  270,   57,  270,
 /*   750 */   363,  362,   38,  270,  357,  501,  270,  136,  110,  270,
 /*   760 */   275,  270,  358,  362,   39,  362,   27,  362,   28,  362,
 /*   770 */    40,  168,  367,  362,   41,  385,  362,   42,  169,  362,
 /*   780 */    44,  362,   45,  160,  231,   49,  361,  502,  148,  139,
 /*   790 */   360,  394,  363,   53,  245,  393,  396,  390,  390,   57,
 /*   800 */    56,   56,   56,   56,  165,   58,   58,   58,   58,   59,
 /*   810 */    59,   60,   60,   60,   61,  237,  378,  378,  363,  143,
 /*   820 */   354,   57,  260,  193,  240,  394,  262,  373,  191,  355,
 /*   830 */   497,  381,  194,  460,  405,  402,  421,  413,  430,  442,
 /*   840 */   391,  219,  296,  477,  478,   20,  481,  418,  385,  165,
 /*   850 */   435,  422,  213,   13,  150,  434,   13,  110,  440,  110,
 /*   860 */   110,   80,   80,  459,  150,  221,  441,  245,  393,  396,
 /*   870 */   390,  390,   57,   56,   56,   56,   56,    5,   58,   58,
 /*   880 */    58,   58,   59,   59,   60,   60,   60,   61,    5,  479,
 /*   890 */   224,  305,   64,  278,  500,  332,  195,  243,  127,  276,
 /*   900 */   377,  497,  379,   64,  278,  198,  279,  395,  243,  433,
 /*   910 */   272,  408,  411,  229,  291,  443,  490,  491,  445,  328,
 /*   920 */   327,  272,  122,  123,  330,  331,    9,  259,  263,  335,
 /*   930 */   264,  265,  544,  344,  352,  242,  353,  356,  359,  364,
 /*   940 */    74,  384,  282,  201,   73,  199,  280,  200,   51,   70,
 /*   950 */   202,  174,  384,  406,  206,  409,  365,  147,  410,   66,
 /*   960 */    65,    5,   75,  107,  210,  285,  420,   64,  268,  269,
 /*   970 */    66,   65,  366,  212,   90,  175,   64,  278,   64,  268,
 /*   980 */   269,  243,  176,  366,  424,  447,  448,  235,  168,  178,
 /*   990 */   236,  461,  462,  179,  272,  463,  471,  299,  469,  302,
 /*  1000 */   228,  105,  368,  368,  368,  369,  370,  371,   12,  298,
 /*  1010 */   111,  161,  116,  368,  368,  368,  369,  370,  371,   12,
 /*  1020 */   473,    5,   11,    2,  307,  384,  239,  475,  476,  186,
 /*  1030 */   258,  310,  326,  187,  188,  222,   64,  278,   84,  177,
 /*  1040 */    89,  243,  329,   66,   65,  426,  233,  102,  261,  333,
 /*  1050 */   190,   64,  268,  269,  272,  334,  366,  336,  103,  186,
 /*  1060 */   258,  167,   50,  187,  188,  222,  545,  546,  144,  145,
 /*  1070 */    54,  392,  374,  383,  173,  397,  125,  102,  483,   76,
 /*  1080 */   401,    7,   14,    8,   13,  384,  368,  368,  368,  369,
 /*  1090 */   370,  371,   12,  417,  108,  140,  109,  431,  290,  409,
 /*  1100 */    91,  295,  218,   66,   65,   92,   77,   93,  483,  159,
 /*  1110 */   194,   64,  268,  269,  300,  223,  366,  225,  112,  470,
 /*  1120 */    15,  114,  118,  184,  303,  113,  482,  474,  489,  301,
 /*  1130 */    78,   79,  308,  163,  168,  141,   81,  185,  504,   82,
 /*  1140 */   124,  183,  322,  384,  505,  530,  368,  368,  368,  369,
 /*  1150 */   370,  371,   12,  530,  303,  113,  482,  530,  530,  301,
 /*  1160 */   530,  129,  130,  101,  168,  530,  530,  530,  530,  530,
 /*  1170 */   453,  530,  530,  530,  366,  530,  530,  530,  530,  530,
 /*  1180 */   530,  530,  530,  530,  530,  530,  530,  530,  530,  530,
 /*  1190 */   530,  530,  530,  101,  530,  530,  530,  530,  530,  530,
 /*  1200 */   530,  530,  530,  530,  368,  368,  368,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    16,    3,    4,   19,  178,   21,   22,   74,   75,   76,
 /*    10 */    77,  185,   79,   80,   81,   82,   83,   84,   85,   86,
 /*    20 */    87,   88,   78,   79,   80,   81,   82,   83,   84,   85,
 /*    30 */    86,   87,   88,   49,   79,   80,   81,   82,   83,   84,
 /*    40 */    85,   86,   87,   88,   83,   84,   85,   86,   87,   88,
 /*    50 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    60 */    76,   77,  112,   79,   80,   81,   82,   83,   84,   85,
 /*    70 */    86,   87,   88,   16,  159,   16,   92,   20,  108,   22,
 /*    80 */   110,  111,   23,  131,   50,   26,   16,  159,  136,  137,
 /*    90 */   138,  139,  140,  165,    1,  167,   26,  177,  178,  151,
 /*   100 */   152,  159,   88,  155,   20,  185,   49,  228,  229,  230,
 /*   110 */    53,  232,  164,  198,   21,  148,  149,  150,  190,  191,
 /*   120 */   153,  179,  180,   66,   67,   68,   69,   70,   71,   72,
 /*   130 */    73,   74,   75,   76,   77,  101,   79,   80,   81,   82,
 /*   140 */    83,   84,   85,   86,   87,   88,   16,  199,  152,   19,
 /*   150 */    21,  155,   22,   94,   95,   96,   97,   98,   99,  100,
 /*   160 */   164,  219,  220,  191,  105,   95,   96,   97,   98,   99,
 /*   170 */   100,  150,  224,    0,  153,  105,    3,    4,   94,   49,
 /*   180 */    14,   97,   98,   99,  168,   92,   93,  171,  172,  173,
 /*   190 */   106,  243,  244,  245,  246,  199,   66,   67,   68,   69,
 /*   200 */    70,   71,   72,   73,   74,   75,   76,   77,   23,   79,
 /*   210 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   220 */   224,   92,   93,   94,   20,   22,   97,   98,   99,   19,
 /*   230 */   159,   21,  228,   65,  230,  106,  232,  159,  159,  243,
 /*   240 */   244,  245,  246,   94,  170,  159,   97,   98,   99,   21,
 /*   250 */   179,  180,   49,  179,  171,  106,  179,  179,  180,   93,
 /*   260 */    92,  171,  172,  173,   96,  179,  180,   83,   84,   66,
 /*   270 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   280 */    77,   96,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   290 */    87,   88,   16,  210,  126,  127,  128,  131,   22,  171,
 /*   300 */   222,  159,   92,  159,  138,  139,  140,  236,  142,  143,
 /*   310 */   159,  228,  146,  230,  236,  232,  237,    2,  179,  233,
 /*   320 */    92,  179,  180,  179,  180,   49,  159,  123,  161,   49,
 /*   330 */   179,  180,  165,  185,  167,  187,   21,  134,  210,    2,
 /*   340 */   164,  193,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   350 */    74,   75,   76,   77,    2,   79,   80,   81,   82,   83,
 /*   360 */    84,   85,   86,   87,   88,  159,  222,   12,   16,  227,
 /*   370 */   164,  220,   16,  159,   22,  199,   85,   86,   87,   88,
 /*   380 */   236,    2,   27,   21,    1,  179,  180,  211,  212,  174,
 /*   390 */   175,  176,  216,  179,  180,  174,  175,  176,   43,   21,
 /*   400 */    45,   49,   21,  123,   21,  199,   50,   92,   93,  191,
 /*   410 */   134,   56,  171,    2,  102,  103,  104,  159,   66,   67,
 /*   420 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   430 */     2,   79,   80,   81,   82,   83,   84,   85,   86,   87,
 /*   440 */    88,  227,    1,   20,   16,  108,   21,  110,  111,  159,
 /*   450 */    22,  210,   21,  238,   92,   93,  198,  101,  131,  238,
 /*   460 */   159,  105,   21,   85,  159,  138,  139,  140,  195,  196,
 /*   470 */    92,   93,  159,   92,   93,   92,   93,   49,  240,  241,
 /*   480 */   179,  180,  192,  159,  179,  180,  124,  108,  204,  110,
 /*   490 */   111,  159,  179,  180,   66,   67,   68,   69,   70,   71,
 /*   500 */    72,   73,   74,   75,   76,   77,    2,   79,   80,   81,
 /*   510 */    82,   83,   84,   85,   86,   87,   88,   92,   93,  108,
 /*   520 */    16,  110,  111,   92,   93,  159,   22,  237,  159,  159,
 /*   530 */   159,  247,   20,   92,  159,  159,  159,  241,  115,  159,
 /*   540 */   200,  116,  218,  159,  248,  159,   49,  116,  179,  180,
 /*   550 */   179,  180,  159,   49,  179,  180,  179,  180,  192,  179,
 /*   560 */   180,  159,  192,  179,  180,   21,   69,   70,  192,  171,
 /*   570 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   580 */    76,   77,    2,   79,   80,   81,   82,   83,   84,   85,
 /*   590 */    86,   87,   88,   96,  159,  159,   16,  159,  159,  159,
 /*   600 */   164,  159,   22,  237,  159,   93,  159,  237,  159,  223,
 /*   610 */   159,  218,  159,  237,  171,  179,  180,  179,  180,  179,
 /*   620 */   180,  179,  180,  159,  179,  180,  179,  180,  116,   49,
 /*   630 */   179,  180,  179,  180,  159,  199,   92,  198,  159,  159,
 /*   640 */   242,  159,  159,  179,  180,  241,   66,   67,   68,   69,
 /*   650 */    70,   71,   72,   73,   74,   75,   76,   77,  222,   79,
 /*   660 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   670 */   159,  204,  236,  159,  130,   22,  159,  198,  159,   25,
 /*   680 */   159,  198,  159,  159,   25,  242,  159,   33,  159,   85,
 /*   690 */   179,  180,    1,  179,  180,  201,  179,  180,  179,  180,
 /*   700 */   179,  180,   49,  179,  180,  223,  179,  180,  179,  180,
 /*   710 */    19,   57,  204,  109,  247,  164,  133,  113,  135,   66,
 /*   720 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   730 */    77,  159,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   740 */    87,   88,   16,  159,  204,  159,  223,  159,   22,  159,
 /*   750 */   199,  179,  180,  159,   30,  247,  159,  164,   20,  159,
 /*   760 */    16,  159,   38,  179,  180,  179,  180,  179,  180,  179,
 /*   770 */   180,  112,  159,  179,  180,   49,  179,  180,  202,  179,
 /*   780 */   180,  179,  180,  164,  125,  209,  109,  247,  211,  212,
 /*   790 */   113,   92,  199,   67,   68,   69,   70,   71,   72,   73,
 /*   800 */    74,   75,   76,   77,   70,   79,   80,   81,   82,   83,
 /*   810 */    84,   85,   86,   87,   88,   16,  126,  127,  199,    1,
 /*   820 */    37,   22,   21,   96,   23,  126,   24,    2,   26,   46,
 /*   830 */    21,  171,  105,   95,  159,    2,    2,  213,    2,    2,
 /*   840 */    96,    2,    2,    2,    2,   20,    2,  159,   49,  115,
 /*   850 */   188,  159,  159,   20,   20,  159,   20,   20,  188,   20,
 /*   860 */    20,   20,   20,  159,   20,  159,  188,   68,   69,   70,
 /*   870 */    71,   72,   73,   74,   75,   76,   77,    1,   79,   80,
 /*   880 */    81,   82,   83,   84,   85,   86,   87,   88,    1,    2,
 /*   890 */   159,  159,   16,   17,  159,  156,  182,   21,  201,  231,
 /*   900 */   239,   92,  239,   16,   17,  203,  235,  231,   21,  187,
 /*   910 */    34,  182,  182,  204,  186,  182,  171,  171,  182,   10,
 /*   920 */   154,   34,  249,  249,  154,  154,   20,  162,  166,   22,
 /*   930 */   166,  101,  114,  181,  181,   47,  189,  181,  181,  199,
 /*   940 */   123,   65,  120,  206,  121,  204,  118,  205,  122,  133,
 /*   950 */   207,  234,   65,  160,   26,   21,  208,  114,  170,   83,
 /*   960 */    84,    1,  101,  160,  214,  117,  215,   91,   92,   93,
 /*   970 */    83,   84,   96,  214,    1,  221,   16,   17,   91,   92,
 /*   980 */    93,   21,  221,   96,  215,  170,  189,  183,  112,  221,
 /*   990 */   183,  181,  181,  221,   34,  181,   18,   15,  160,   15,
 /*  1000 */   204,    1,  126,  127,  128,  129,  130,  131,  132,  157,
 /*  1010 */   197,  158,  225,  126,  127,  128,  129,  130,  131,  132,
 /*  1020 */   160,    1,    1,    1,  226,   65,  163,  208,  208,    7,
 /*  1030 */     8,  225,    2,   11,   12,   13,   16,   17,  169,  184,
 /*  1040 */   184,   21,    9,   83,   84,   85,    2,   25,   22,   21,
 /*  1050 */    25,   91,   92,   93,   34,   21,   96,   21,   35,    7,
 /*  1060 */     8,   51,    1,   11,   12,   13,  114,  114,  114,  114,
 /*  1070 */     1,   96,    2,    2,   67,  109,    1,   25,   56,    1,
 /*  1080 */    41,  119,   20,  119,   20,   65,  126,  127,  128,  129,
 /*  1090 */   130,  131,  132,  116,    1,  114,    2,    2,   51,   21,
 /*  1100 */     1,   51,    2,   83,   84,    1,    1,    1,   56,  100,
 /*  1110 */   105,   91,   92,   93,   16,   14,   96,   14,  115,   17,
 /*  1120 */     1,   25,   25,  144,  102,  103,  104,   17,  114,  107,
 /*  1130 */    22,   22,   20,   20,  112,   20,   22,  145,    3,   22,
 /*  1140 */   146,   25,    5,   65,    6,  250,  126,  127,  128,  129,
 /*  1150 */   130,  131,  132,  250,  102,  103,  104,  250,  250,  107,
 /*  1160 */   250,   83,   84,  141,  112,  250,  250,  250,  250,  250,
 /*  1170 */    92,  250,  250,  250,   96,  250,  250,  250,  250,  250,
 /*  1180 */   250,  250,  250,  250,  250,  250,  250,  250,  250,  250,
 /*  1190 */   250,  250,  250,  141,  250,  250,  250,  250,  250,  250,
 /*  1200 */   250,  250,  250,  250,  126,  127,  128,
};
#define YY_SHIFT_USE_DFLT (-68)
#define YY_SHIFT_MAX 322
static const short yy_shift_ofst[] = {
 /*     0 */    -2, 1022, 1052,  876,  -16,  876, 1020, 1020, 1020,  129,
 /*    10 */   -50,  887, 1020, 1020, 1020, 1020,  -56,  381,  228,  184,
 /*    20 */   184,   57,  130,  203,  276,  352,  428,  504,  580,  653,
 /*    30 */   653,  653,  653,  653,  653,  653,  653,  653,  653,  653,
 /*    40 */   653,  653,  653,  653,  653,  653,  726,  799,  799,  960,
 /*    50 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    60 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    70 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    80 */  1020, 1020, 1020,  -67,   59,  -45,  -45,  -39,  291,  356,
 /*    90 */   381,  381,  381,  381,  228,   14,  -68,  -68,  -68, 1078,
 /*   100 */    70,  166,  -48,  355,  362,  315,  173,  210,  381,  210,
 /*   110 */   381,  381,  381,  381,  381,  381,  659,  381,  381,  544,
 /*   120 */   544,  280,  280,  280,  280,  -50,  -50,  -68,  -68,  168,
 /*   130 */   168,   84,  149,  337,   93,  379,  411,  425,  431,  383,
 /*   140 */   378,  327,  381,  604,  381,  381,  441,  381,  512,  381,
 /*   150 */   381,  -30,  512,  381,  381,  654,  654,  654,  381,  381,
 /*   160 */   -30,  381,  -30,  381,  -30,  381,  691,  724,  677,  423,
 /*   170 */   690,  690,  699,  699,  583,  724,  724,   34,  724,  724,
 /*   180 */   738,  204,  228,  228,  734,  734,  909,  909,  909,  906,
 /*   190 */   907,  907,  830,  830,  888,  830,  830,  -50,  817,  822,
 /*   200 */   823,  828,  826,  816,  843,  928,  934,  928,  843,  861,
 /*   210 */   848,  861,  848,  973,  928,  928,  934,  888,  830,  830,
 /*   220 */   830,  973,  978,  982,  843,  984,  843,  817,  826,  826,
 /*   230 */  1000, 1021, 1000,  -68,  -68,  -68,  -68,  497,  312,  801,
 /*   240 */   802,  727,  783,  818,  825,  744,  833,  834,  836,  185,
 /*   250 */   837,  839,  840,  841,  842,  844,  809, 1030, 1033, 1044,
 /*   260 */  1026, 1028, 1025, 1034, 1036, 1023, 1010, 1061,  952,  953,
 /*   270 */   954,  955, 1069, 1070, 1071,  975, 1007,  966, 1075, 1039,
 /*   280 */   962, 1062,  964, 1064,  977, 1093, 1094,  981, 1095, 1047,
 /*   290 */  1099, 1100, 1104, 1105, 1050, 1106, 1009, 1005, 1101, 1098,
 /*   300 */  1102, 1103, 1110, 1003, 1096, 1108, 1109, 1112, 1119, 1113,
 /*   310 */  1097, 1113, 1115, 1114, 1014, 1116, 1117,  979,  992,  994,
 /*   320 */  1135, 1137, 1138,
};
#define YY_REDUCE_USE_DFLT (-175)
#define YY_REDUCE_MAX 236
static const short yy_reduce_ofst[] = {
 /*     0 */   -33,  -52,   -4,  436,   83,  206,   78,  -58,  144,  -72,
 /*    10 */   176,  142,   86,   71,  151,  214, -121,  167,   16,  215,
 /*    20 */   221,    4,    4,    4,    4,    4,    4,    4,    4,    4,
 /*    30 */     4,    4,    4,    4,    4,    4,    4,    4,    4,    4,
 /*    40 */     4,    4,    4,    4,    4,    4,    4,    4,    4,  301,
 /*    50 */   305,  313,  369,  371,  375,  377,  380,  384,  438,  440,
 /*    60 */   442,  445,  447,  451,  453,  464,  511,  514,  517,  519,
 /*    70 */   521,  524,  527,  529,  572,  584,  586,  588,  590,  594,
 /*    80 */   597,  600,  602,    4,  -80,    4,    4,    4,    4,  148,
 /*    90 */   290,  366,  370,  376,   90,    4,    4,    4,    4,   74,
 /*   100 */  -174,  296,  238,  273,  -85,  324,   21,  128,  393,  241,
 /*   110 */    79,  258,  439,  479,  386,  483,  551,  482,  523,  398,
 /*   120 */   443,  284,  467,  508,  540,  593,  619,  576,  577,   77,
 /*   130 */   139,  -28,  218,  340,  332,  340,  340,  402,  435,  449,
 /*   140 */   475,  404,  480,  494,  475,  613,  660,  675,  624,  688,
 /*   150 */   692,  340,  624,  693,  696,  662,  670,  678,  704,  706,
 /*   160 */   340,  731,  340,  732,  340,  735,  739,  714,  697,  702,
 /*   170 */   661,  663,  668,  676,  671,  729,  730,  722,  733,  736,
 /*   180 */   728,  709,  745,  746,  673,  674,  766,  770,  771,  765,
 /*   190 */   762,  764,  752,  753,  747,  756,  757,  740,  741,  742,
 /*   200 */   737,  743,  748,  717,  793,  754,  788,  761,  803,  750,
 /*   210 */   751,  759,  769,  804,  768,  772,  815,  797,  810,  811,
 /*   220 */   814,  807,  852,  853,  838,  813,  860,  796,  819,  820,
 /*   230 */   787,  798,  806,  863,  869,  855,  856,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   514,  785,  785,  745,  628,  785,  745,  785,  745,  785,
 /*    10 */   632,  785,  741,  745,  785,  785,  715,  785,  547,  755,
 /*    20 */   755,  663,  785,  785,  785,  785,  785,  785,  785,  664,
 /*    30 */   744,  740,  736,  738,  737,  665,  652,  661,  668,  644,
 /*    40 */   670,  671,  681,  682,  762,  763,  705,  721,  704,  785,
 /*    50 */   785,  785,  785,  785,  785,  785,  785,  785,  785,  785,
 /*    60 */   785,  785,  785,  785,  785,  785,  785,  785,  785,  785,
 /*    70 */   785,  785,  785,  785,  785,  785,  785,  785,  785,  785,
 /*    80 */   785,  785,  785,  707,  540,  706,  714,  708,  709,  601,
 /*    90 */   785,  785,  785,  785,  785,  710,  711,  722,  723,  785,
 /*   100 */   785,  780,  768,  785,  785,  785,  514,  628,  785,  628,
 /*   110 */   785,  785,  785,  785,  785,  785,  785,  785,  785,  785,
 /*   120 */   785,  667,  667,  667,  667,  785,  785,  622,  632,  785,
 /*   130 */   785,  592,  785,  785,  785,  785,  785,  785,  785,  785,
 /*   140 */   785,  768,  785,  620,  785,  785,  549,  785,  630,  785,
 /*   150 */   785,  635,  636,  785,  785,  785,  785,  785,  785,  785,
 /*   160 */   530,  785,  611,  785,  675,  785,  785,  655,  620,  629,
 /*   170 */   785,  785,  785,  785,  739,  655,  655,  571,  655,  655,
 /*   180 */   574,  667,  785,  785,  783,  783,  519,  519,  519,  591,
 /*   190 */   538,  538,  603,  603,  588,  603,  603,  785,  667,  658,
 /*   200 */   660,  648,  662,  785,  637,  656,  785,  656,  637,  645,
 /*   210 */   647,  645,  647,  746,  656,  656,  785,  588,  603,  603,
 /*   220 */   603,  746,  528,  525,  637,  610,  637,  667,  662,  662,
 /*   230 */   683,  785,  683,  533,  557,  576,  576,  785,  785,  529,
 /*   240 */   785,  785,  785,  691,  785,  785,  785,  785,  785,  785,
 /*   250 */   785,  785,  785,  785,  785,  785,  785,  785,  785,  785,
 /*   260 */   534,  785,  785,  785,  785,  785,  785,  785,  696,  692,
 /*   270 */   785,  693,  785,  785,  785,  785,  785,  614,  785,  785,
 /*   280 */   785,  649,  785,  659,  785,  785,  785,  785,  785,  785,
 /*   290 */   785,  785,  785,  785,  785,  785,  785,  785,  785,  785,
 /*   300 */   785,  785,  785,  785,  785,  785,  785,  672,  785,  673,
 /*   310 */   785,  674,  759,  785,  785,  785,  785,  785,  785,  785,
 /*   320 */   785,  515,  785,  508,  512,  510,  511,  517,  520,  518,
 /*   330 */   521,  522,  523,  535,  536,  539,  537,  531,  556,  544,
 /*   340 */   545,  546,  558,  565,  566,  604,  605,  606,  607,  756,
 /*   350 */   757,  758,  567,  586,  589,  590,  568,  653,  654,  569,
 /*   360 */   618,  619,  688,  612,  613,  617,  690,  694,  695,  697,
 /*   370 */   698,  699,  543,  550,  551,  554,  555,  751,  753,  752,
 /*   380 */   754,  553,  552,  700,  703,  712,  713,  719,  725,  729,
 /*   390 */   717,  718,  720,  724,  726,  727,  728,  615,  616,  732,
 /*   400 */   734,  735,  730,  742,  743,  638,  733,  716,  650,  542,
 /*   410 */   657,  651,  621,  631,  640,  641,  642,  643,  626,  627,
 /*   420 */   633,  646,  686,  687,  634,  623,  624,  625,  731,  689,
 /*   430 */   701,  702,  570,  577,  578,  579,  582,  583,  584,  585,
 /*   440 */   580,  581,  747,  748,  750,  749,  572,  573,  587,  559,
 /*   450 */   560,  561,  562,  696,  563,  564,  548,  541,  593,  596,
 /*   460 */   575,  597,  598,  599,  600,  602,  594,  595,  532,  524,
 /*   470 */   526,  527,  608,  639,  609,  666,  669,  678,  679,  680,
 /*   480 */   684,  685,  676,  677,  769,  770,  764,  765,  766,  767,
 /*   490 */   760,  761,  771,  772,  773,  774,  775,  781,  782,  776,
 /*   500 */   784,  777,  778,  779,  513,  516,  509,
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
    0,  /*     STATUS => nothing */
    0,  /*  VARIABLES => nothing */
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
  "TABLES",        "STATUS",        "VARIABLES",     "error",       
  "input",         "cmdlist",       "ecmd",          "cmdx",        
  "cmd",           "explain",       "trans_opt",     "create_table",
  "create_table_args",  "temp",          "ifnotexists",   "nm",          
  "dbnm",          "columnlist",    "conslist_opt",  "table_opt",   
  "select",        "column",        "eq_or_null",    "columnid",    
  "type",          "carglist",      "id",            "ids",         
  "typetoken",     "typename",      "signed",        "plus_num",    
  "minus_num",     "carg",          "ccons",         "term",        
  "expr",          "onconf",        "sortorder",     "idxlist_opt", 
  "refargs",       "defer_subclause",  "autoinc",       "refarg",      
  "refact",        "init_deferred_pred_opt",  "conslist",      "tcons",       
  "idxlist",       "defer_subclause_opt",  "orconf",        "resolvetype", 
  "raisetype",     "ifexists",      "fullname",      "oneselect",   
  "multiselect_op",  "distinct",      "selcollist",    "from",        
  "where_opt",     "groupby_opt",   "having_opt",    "orderby_opt", 
  "limit_opt",     "sclp",          "as",            "seltablist",  
  "stl_prefix",    "joinop",        "on_opt",        "using_opt",   
  "seltablist_paren",  "joinop2",       "inscollist",    "sortlist",    
  "sortitem",      "collate",       "exprlist",      "setlist",     
  "insert_cmd",    "inscollist_opt",  "valueslist",    "itemlist",    
  "likeop",        "escape",        "between_op",    "between_elem",
  "in_op",         "case_operand",  "case_exprlist",  "case_else",   
  "expritem",      "idxitem",       "plus_opt",      "number",      
  "variable_assignment_list",  "scope_qualifier",  "user_var_name",  "show_databes",
  "show_tables",   "show_table_status",  "show_variables",  "show_statement_pattern",
  "full_keyword",  "from_db",     
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
 /* 266 */ "cmd ::= show_table_status",
 /* 267 */ "cmd ::= show_variables",
 /* 268 */ "show_databes ::= SHOW DATABASES|SCHEMAS show_statement_pattern",
 /* 269 */ "show_tables ::= SHOW full_keyword TABLES from_db show_statement_pattern",
 /* 270 */ "show_table_status ::= SHOW TABLE STATUS from_db show_statement_pattern",
 /* 271 */ "show_variables ::= SHOW scope_qualifier VARIABLES show_statement_pattern",
 /* 272 */ "full_keyword ::= JOIN_KW",
 /* 273 */ "full_keyword ::=",
 /* 274 */ "show_statement_pattern ::= LIKE_KW STRING|ID",
 /* 275 */ "show_statement_pattern ::= where_opt",
 /* 276 */ "from_db ::=",
 /* 277 */ "from_db ::= FROM|IN nm",
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
    case 164:
    case 199:
    case 216:
#line 391 "parse.y"
{sqlite3SelectDelete((yypminor->yy159));}
#line 1182 "parse.c"
      break;
    case 179:
    case 180:
    case 204:
    case 206:
    case 214:
    case 220:
    case 229:
    case 231:
    case 233:
    case 235:
    case 236:
#line 669 "parse.y"
{sqlite3ExprDelete((yypminor->yy122));}
#line 1197 "parse.c"
      break;
    case 183:
    case 192:
    case 202:
    case 205:
    case 207:
    case 209:
    case 219:
    case 222:
    case 223:
    case 227:
    case 234:
#line 913 "parse.y"
{sqlite3ExprListDelete((yypminor->yy442));}
#line 1212 "parse.c"
      break;
    case 198:
    case 203:
    case 211:
    case 212:
#line 519 "parse.y"
{sqlite3SrcListDelete((yypminor->yy347));}
#line 1220 "parse.c"
      break;
    case 208:
#line 580 "parse.y"
{
  sqlite3ExprDelete((yypminor->yy64).pLimit);
  sqlite3ExprDelete((yypminor->yy64).pOffset);
}
#line 1228 "parse.c"
      break;
    case 215:
    case 218:
    case 225:
#line 536 "parse.y"
{sqlite3IdListDelete((yypminor->yy180));}
#line 1235 "parse.c"
      break;
    case 226:
#line 640 "parse.y"
{sqlite3ValuesListDelete((yypminor->yy139));}
#line 1240 "parse.c"
      break;
    case 240:
#line 1129 "parse.y"
{ sqlite3ExprListDelete((yypminor->yy442)); }
#line 1245 "parse.c"
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
#line 1397 "parse.c"
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
  { 148, 1 },
  { 149, 2 },
  { 149, 1 },
  { 151, 1 },
  { 151, 3 },
  { 150, 1 },
  { 150, 3 },
  { 153, 0 },
  { 153, 1 },
  { 153, 3 },
  { 152, 2 },
  { 152, 2 },
  { 154, 0 },
  { 154, 1 },
  { 152, 2 },
  { 152, 2 },
  { 152, 2 },
  { 155, 6 },
  { 158, 0 },
  { 158, 3 },
  { 157, 1 },
  { 157, 0 },
  { 156, 5 },
  { 156, 2 },
  { 161, 3 },
  { 161, 1 },
  { 163, 0 },
  { 163, 2 },
  { 163, 4 },
  { 163, 6 },
  { 163, 5 },
  { 166, 0 },
  { 166, 1 },
  { 165, 3 },
  { 167, 1 },
  { 170, 1 },
  { 171, 1 },
  { 159, 1 },
  { 159, 1 },
  { 159, 1 },
  { 168, 0 },
  { 168, 1 },
  { 172, 1 },
  { 172, 4 },
  { 172, 6 },
  { 173, 1 },
  { 173, 2 },
  { 174, 1 },
  { 174, 1 },
  { 169, 2 },
  { 169, 0 },
  { 177, 3 },
  { 177, 1 },
  { 177, 2 },
  { 177, 4 },
  { 177, 3 },
  { 177, 3 },
  { 177, 2 },
  { 178, 1 },
  { 178, 2 },
  { 178, 3 },
  { 178, 4 },
  { 178, 2 },
  { 178, 4 },
  { 178, 4 },
  { 178, 1 },
  { 178, 2 },
  { 186, 0 },
  { 186, 1 },
  { 184, 0 },
  { 184, 2 },
  { 187, 2 },
  { 187, 3 },
  { 187, 3 },
  { 187, 3 },
  { 188, 2 },
  { 188, 2 },
  { 188, 1 },
  { 188, 1 },
  { 185, 3 },
  { 185, 2 },
  { 189, 0 },
  { 189, 2 },
  { 189, 2 },
  { 162, 0 },
  { 162, 2 },
  { 190, 3 },
  { 190, 2 },
  { 190, 1 },
  { 191, 2 },
  { 191, 7 },
  { 191, 5 },
  { 191, 5 },
  { 191, 10 },
  { 193, 0 },
  { 193, 1 },
  { 181, 0 },
  { 181, 3 },
  { 195, 1 },
  { 195, 1 },
  { 195, 1 },
  { 152, 4 },
  { 197, 2 },
  { 197, 0 },
  { 152, 1 },
  { 164, 1 },
  { 164, 3 },
  { 200, 1 },
  { 200, 2 },
  { 200, 1 },
  { 199, 9 },
  { 201, 1 },
  { 201, 1 },
  { 201, 0 },
  { 209, 2 },
  { 209, 0 },
  { 202, 3 },
  { 202, 2 },
  { 202, 4 },
  { 210, 2 },
  { 210, 1 },
  { 210, 0 },
  { 203, 0 },
  { 203, 2 },
  { 212, 2 },
  { 212, 0 },
  { 211, 6 },
  { 211, 7 },
  { 216, 1 },
  { 216, 1 },
  { 160, 0 },
  { 160, 2 },
  { 198, 2 },
  { 213, 1 },
  { 213, 2 },
  { 213, 3 },
  { 213, 4 },
  { 214, 2 },
  { 214, 0 },
  { 215, 4 },
  { 215, 0 },
  { 207, 0 },
  { 207, 3 },
  { 219, 5 },
  { 219, 3 },
  { 220, 1 },
  { 182, 1 },
  { 182, 1 },
  { 182, 0 },
  { 221, 0 },
  { 221, 2 },
  { 205, 0 },
  { 205, 3 },
  { 206, 0 },
  { 206, 2 },
  { 208, 0 },
  { 208, 2 },
  { 208, 4 },
  { 208, 4 },
  { 152, 5 },
  { 204, 0 },
  { 204, 2 },
  { 152, 6 },
  { 223, 5 },
  { 223, 3 },
  { 152, 6 },
  { 152, 6 },
  { 152, 5 },
  { 152, 5 },
  { 224, 1 },
  { 224, 1 },
  { 226, 5 },
  { 226, 3 },
  { 226, 2 },
  { 227, 3 },
  { 227, 1 },
  { 225, 0 },
  { 225, 2 },
  { 225, 3 },
  { 218, 3 },
  { 218, 1 },
  { 180, 1 },
  { 180, 3 },
  { 179, 1 },
  { 180, 1 },
  { 180, 1 },
  { 180, 3 },
  { 180, 5 },
  { 179, 1 },
  { 179, 1 },
  { 180, 1 },
  { 180, 1 },
  { 180, 1 },
  { 180, 6 },
  { 180, 5 },
  { 180, 4 },
  { 179, 1 },
  { 180, 3 },
  { 180, 3 },
  { 180, 3 },
  { 180, 3 },
  { 180, 3 },
  { 180, 3 },
  { 180, 3 },
  { 180, 3 },
  { 228, 1 },
  { 228, 2 },
  { 229, 2 },
  { 229, 0 },
  { 180, 4 },
  { 180, 2 },
  { 180, 3 },
  { 180, 3 },
  { 180, 4 },
  { 180, 2 },
  { 180, 2 },
  { 180, 2 },
  { 230, 1 },
  { 230, 2 },
  { 231, 1 },
  { 180, 5 },
  { 232, 1 },
  { 232, 2 },
  { 180, 5 },
  { 180, 3 },
  { 180, 5 },
  { 180, 4 },
  { 180, 4 },
  { 180, 5 },
  { 234, 5 },
  { 234, 4 },
  { 235, 2 },
  { 235, 0 },
  { 233, 1 },
  { 233, 0 },
  { 222, 3 },
  { 222, 1 },
  { 236, 1 },
  { 236, 0 },
  { 183, 0 },
  { 183, 3 },
  { 192, 5 },
  { 192, 3 },
  { 237, 1 },
  { 175, 2 },
  { 176, 2 },
  { 239, 1 },
  { 238, 1 },
  { 238, 0 },
  { 196, 1 },
  { 196, 1 },
  { 196, 1 },
  { 152, 2 },
  { 152, 3 },
  { 152, 4 },
  { 240, 6 },
  { 240, 4 },
  { 241, 1 },
  { 241, 1 },
  { 241, 1 },
  { 241, 2 },
  { 241, 0 },
  { 242, 1 },
  { 242, 1 },
  { 152, 1 },
  { 152, 1 },
  { 152, 1 },
  { 152, 1 },
  { 243, 3 },
  { 244, 5 },
  { 245, 5 },
  { 246, 4 },
  { 248, 1 },
  { 248, 0 },
  { 247, 2 },
  { 247, 1 },
  { 249, 0 },
  { 249, 2 },
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
#line 1754 "parse.c"
        break;
      case 7:
#line 102 "parse.y"
{ sqlite3BeginParse(pParse, 0); }
#line 1759 "parse.c"
        break;
      case 8:
#line 104 "parse.y"
{ sqlite3BeginParse(pParse, 1); }
#line 1764 "parse.c"
        break;
      case 9:
#line 105 "parse.y"
{ sqlite3BeginParse(pParse, 2); }
#line 1769 "parse.c"
        break;
      case 10:
#line 112 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_BEGIN);}
#line 1774 "parse.c"
        break;
      case 11:
#line 113 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_START);}
#line 1779 "parse.c"
        break;
      case 14:
#line 124 "parse.y"
{sqlite3CommitTransaction(pParse);}
#line 1784 "parse.c"
        break;
      case 15:
#line 126 "parse.y"
{sqlite3RollbackTransaction(pParse);}
#line 1789 "parse.c"
        break;
      case 17:
#line 131 "parse.y"
{
   sqlite3StartTable(pParse, 0, 0, 0, 0, 0);
}
#line 1796 "parse.c"
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
{yygotominor.yy392 = 0;}
#line 1811 "parse.c"
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
{yygotominor.yy392 = 1;}
#line 1823 "parse.c"
        break;
      case 22:
#line 143 "parse.y"
{
  //sqlite3EndTable(pParse,&X,&Y,0);
}
#line 1830 "parse.c"
        break;
      case 23:
#line 146 "parse.y"
{
  sqlite3EndTable(pParse,0,0,0);
  //sqlite3SelectDelete(S);
  yy_destructor(164,&yymsp[0].minor);
}
#line 1839 "parse.c"
        break;
      case 33:
#line 168 "parse.y"
{
  //A.z = X.z;
  //A.n = (pParse->sLastToken.z-X.z) + pParse->sLastToken.n;
}
#line 1847 "parse.c"
        break;
      case 34:
#line 172 "parse.y"
{
  //sqlite3AddColumn(pParse,&X);
  //A = X;
}
#line 1855 "parse.c"
        break;
      case 35:
      case 36:
      case 37:
      case 38:
      case 39:
      case 246:
#line 182 "parse.y"
{yygotominor.yy278 = yymsp[0].minor.yy0;}
#line 1865 "parse.c"
        break;
      case 41:
#line 241 "parse.y"
{ /*sqlite3AddColumnType(pParse,&X);*/ }
#line 1870 "parse.c"
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
{yygotominor.yy278 = yymsp[0].minor.yy278;}
#line 1883 "parse.c"
        break;
      case 43:
#line 243 "parse.y"
{
  yygotominor.yy278.z = yymsp[-3].minor.yy278.z;
  yygotominor.yy278.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-3].minor.yy278.z;
}
#line 1891 "parse.c"
        break;
      case 44:
#line 247 "parse.y"
{
  yygotominor.yy278.z = yymsp[-5].minor.yy278.z;
  yygotominor.yy278.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-5].minor.yy278.z;
}
#line 1899 "parse.c"
        break;
      case 46:
#line 253 "parse.y"
{yygotominor.yy278.z=yymsp[-1].minor.yy278.z; yygotominor.yy278.n=yymsp[0].minor.yy278.n+(yymsp[0].minor.yy278.z-yymsp[-1].minor.yy278.z);}
#line 1904 "parse.c"
        break;
      case 47:
#line 255 "parse.y"
{ yygotominor.yy392 = atoi((char*)yymsp[0].minor.yy278.z); }
#line 1909 "parse.c"
        break;
      case 48:
#line 256 "parse.y"
{ yygotominor.yy392 = -atoi((char*)yymsp[0].minor.yy278.z); }
#line 1914 "parse.c"
        break;
      case 53:
#line 265 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/   yy_destructor(179,&yymsp[0].minor);
}
#line 1920 "parse.c"
        break;
      case 54:
#line 266 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/ }
#line 1925 "parse.c"
        break;
      case 55:
#line 267 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/  yy_destructor(179,&yymsp[0].minor);
}
#line 1931 "parse.c"
        break;
      case 56:
#line 268 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_UMINUS, X, 0, 0);
  //sqlite3AddDefaultValue(pParse,p);
  yy_destructor(179,&yymsp[0].minor);
}
#line 1940 "parse.c"
        break;
      case 57:
#line 272 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_STRING, 0, 0, &X);
  //sqlite3AddDefaultValue(pParse,p);
}
#line 1948 "parse.c"
        break;
      case 60:
#line 282 "parse.y"
{/*sqlite3AddNotNull(pParse, R);*/}
#line 1953 "parse.c"
        break;
      case 61:
#line 284 "parse.y"
{/*sqlite3AddPrimaryKey(pParse,0,R,I,Z);*/}
#line 1958 "parse.c"
        break;
      case 62:
#line 285 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,0,R,0,0,0,0);*/}
#line 1963 "parse.c"
        break;
      case 63:
#line 286 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,X);*/  sqlite3ExprDelete(yymsp[-1].minor.yy122); }
#line 1968 "parse.c"
        break;
      case 64:
#line 288 "parse.y"
{/*sqlite3CreateForeignKey(pParse,0,&T,TA,R);*/ sqlite3ExprListDelete(yymsp[-1].minor.yy442); }
#line 1973 "parse.c"
        break;
      case 65:
#line 289 "parse.y"
{/*sqlite3DeferForeignKey(pParse,D);*/}
#line 1978 "parse.c"
        break;
      case 66:
#line 290 "parse.y"
{/*sqlite3AddCollateType(pParse, (char*)C.z, C.n);*/}
#line 1983 "parse.c"
        break;
      case 69:
#line 303 "parse.y"
{ yygotominor.yy392 = OE_Restrict * 0x010101; }
#line 1988 "parse.c"
        break;
      case 70:
#line 304 "parse.y"
{ yygotominor.yy392 = (yymsp[-1].minor.yy392 & yymsp[0].minor.yy207.mask) | yymsp[0].minor.yy207.value; }
#line 1993 "parse.c"
        break;
      case 71:
#line 306 "parse.y"
{ yygotominor.yy207.value = 0;     yygotominor.yy207.mask = 0x000000; }
#line 1998 "parse.c"
        break;
      case 72:
#line 307 "parse.y"
{ yygotominor.yy207.value = yymsp[0].minor.yy392;     yygotominor.yy207.mask = 0x0000ff; }
#line 2003 "parse.c"
        break;
      case 73:
#line 308 "parse.y"
{ yygotominor.yy207.value = yymsp[0].minor.yy392<<8;  yygotominor.yy207.mask = 0x00ff00; }
#line 2008 "parse.c"
        break;
      case 74:
#line 309 "parse.y"
{ yygotominor.yy207.value = yymsp[0].minor.yy392<<16; yygotominor.yy207.mask = 0xff0000; }
#line 2013 "parse.c"
        break;
      case 75:
#line 311 "parse.y"
{ yygotominor.yy392 = OE_SetNull; }
#line 2018 "parse.c"
        break;
      case 76:
#line 312 "parse.y"
{ yygotominor.yy392 = OE_SetDflt; }
#line 2023 "parse.c"
        break;
      case 77:
#line 313 "parse.y"
{ yygotominor.yy392 = OE_Cascade; }
#line 2028 "parse.c"
        break;
      case 78:
#line 314 "parse.y"
{ yygotominor.yy392 = OE_Restrict; }
#line 2033 "parse.c"
        break;
      case 79:
      case 80:
      case 95:
      case 97:
      case 98:
#line 316 "parse.y"
{yygotominor.yy392 = yymsp[0].minor.yy392;}
#line 2042 "parse.c"
        break;
      case 90:
#line 335 "parse.y"
{ sqlite3ExprListDelete(yymsp[-3].minor.yy442); }
#line 2047 "parse.c"
        break;
      case 91:
#line 337 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,yymsp[-2].minor.yy442,R,0,0,0,0);*/ sqlite3ExprListDelete(yymsp[-2].minor.yy442);}
#line 2052 "parse.c"
        break;
      case 92:
#line 338 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,yymsp[-2].minor.yy122);*/ sqlite3ExprDelete(yymsp[-2].minor.yy122);}
#line 2057 "parse.c"
        break;
      case 93:
#line 340 "parse.y"
{ 
        sqlite3ExprListDelete(yymsp[-6].minor.yy442);
        sqlite3ExprListDelete(yymsp[-2].minor.yy442);
 }
#line 2065 "parse.c"
        break;
      case 96:
#line 355 "parse.y"
{yygotominor.yy392 = OE_Default;}
#line 2070 "parse.c"
        break;
      case 99:
#line 360 "parse.y"
{yygotominor.yy392 = OE_Ignore;}
#line 2075 "parse.c"
        break;
      case 100:
      case 170:
#line 361 "parse.y"
{yygotominor.yy392 = OE_Replace;}
#line 2081 "parse.c"
        break;
      case 101:
#line 365 "parse.y"
{
  sqlite3DropTable(pParse, yymsp[0].minor.yy347, 0, yymsp[-1].minor.yy392);
}
#line 2088 "parse.c"
        break;
      case 104:
#line 385 "parse.y"
{
  sqlite3Select(pParse, yymsp[0].minor.yy159, SRT_Callback, 0, 0, 0, 0, 0);
  // sqlite3SelectDelete(yymsp[0].minor.yy159);
}
#line 2096 "parse.c"
        break;
      case 105:
      case 128:
#line 395 "parse.y"
{yygotominor.yy159 = yymsp[0].minor.yy159;}
#line 2102 "parse.c"
        break;
      case 106:
#line 397 "parse.y"
{
  if( yymsp[0].minor.yy159 ){
    yymsp[0].minor.yy159->op = yymsp[-1].minor.yy392;
    yymsp[0].minor.yy159->pPrior = yymsp[-2].minor.yy159;
  }
  yygotominor.yy159 = yymsp[0].minor.yy159;
}
#line 2113 "parse.c"
        break;
      case 107:
      case 109:
#line 405 "parse.y"
{yygotominor.yy392 = yymsp[0].major;}
#line 2119 "parse.c"
        break;
      case 108:
#line 406 "parse.y"
{yygotominor.yy392 = TK_ALL;}
#line 2124 "parse.c"
        break;
      case 110:
#line 410 "parse.y"
{
  yygotominor.yy159 = sqlite3SelectNew(yymsp[-6].minor.yy442,yymsp[-5].minor.yy347,yymsp[-4].minor.yy122,yymsp[-3].minor.yy442,yymsp[-2].minor.yy122,yymsp[-1].minor.yy442,yymsp[-7].minor.yy392,yymsp[0].minor.yy64.pLimit,yymsp[0].minor.yy64.pOffset);
}
#line 2131 "parse.c"
        break;
      case 114:
      case 240:
#line 431 "parse.y"
{yygotominor.yy442 = yymsp[-1].minor.yy442;}
#line 2137 "parse.c"
        break;
      case 115:
      case 141:
      case 151:
      case 239:
#line 432 "parse.y"
{yygotominor.yy442 = 0;}
#line 2145 "parse.c"
        break;
      case 116:
#line 433 "parse.y"
{
   yygotominor.yy442 = sqlite3ExprListAppend(yymsp[-2].minor.yy442,yymsp[-1].minor.yy122,yymsp[0].minor.yy278.n?&yymsp[0].minor.yy278:0);
}
#line 2152 "parse.c"
        break;
      case 117:
#line 436 "parse.y"
{
  yygotominor.yy442 = sqlite3ExprListAppend(yymsp[-1].minor.yy442, sqlite3Expr(TK_ALL, 0, 0, 0), 0);
}
#line 2159 "parse.c"
        break;
      case 118:
#line 439 "parse.y"
{
  Expr *pRight = sqlite3Expr(TK_ALL, 0, 0, 0);
  Expr *pLeft = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy278);
  yygotominor.yy442 = sqlite3ExprListAppend(yymsp[-3].minor.yy442, sqlite3Expr(TK_DOT, pLeft, pRight, 0), 0);
}
#line 2168 "parse.c"
        break;
      case 121:
#line 451 "parse.y"
{yygotominor.yy278.n = 0;}
#line 2173 "parse.c"
        break;
      case 122:
#line 463 "parse.y"
{yygotominor.yy347 = sqliteMalloc(sizeof(*yygotominor.yy347));}
#line 2178 "parse.c"
        break;
      case 123:
#line 464 "parse.y"
{yygotominor.yy347 = yymsp[0].minor.yy347;}
#line 2183 "parse.c"
        break;
      case 124:
#line 469 "parse.y"
{
   yygotominor.yy347 = yymsp[-1].minor.yy347;
   if( yygotominor.yy347 && yygotominor.yy347->nSrc>0 ) yygotominor.yy347->a[yygotominor.yy347->nSrc-1].jointype = yymsp[0].minor.yy392;
}
#line 2191 "parse.c"
        break;
      case 125:
#line 473 "parse.y"
{yygotominor.yy347 = 0;}
#line 2196 "parse.c"
        break;
      case 126:
#line 474 "parse.y"
{
  yygotominor.yy347 = sqlite3SrcListAppend(yymsp[-5].minor.yy347,&yymsp[-4].minor.yy278,&yymsp[-3].minor.yy278);
  if( yymsp[-2].minor.yy278.n ) sqlite3SrcListAddAlias(yygotominor.yy347,&yymsp[-2].minor.yy278);
  if( yymsp[-1].minor.yy122 ){
    if( yygotominor.yy347 && yygotominor.yy347->nSrc>1 ){ yygotominor.yy347->a[yygotominor.yy347->nSrc-2].pOn = yymsp[-1].minor.yy122; }
    else { sqlite3ExprDelete(yymsp[-1].minor.yy122); }
  }
  if( yymsp[0].minor.yy180 ){
    if( yygotominor.yy347 && yygotominor.yy347->nSrc>1 ){ yygotominor.yy347->a[yygotominor.yy347->nSrc-2].pUsing = yymsp[0].minor.yy180; }
    else { sqlite3IdListDelete(yymsp[0].minor.yy180); }
  }
}
#line 2212 "parse.c"
        break;
      case 127:
#line 488 "parse.y"
{
    yygotominor.yy347 = sqlite3SrcListAppend(yymsp[-6].minor.yy347,0,0);
    yygotominor.yy347->a[yygotominor.yy347->nSrc-1].pSelect = yymsp[-4].minor.yy159;
    if( yymsp[-2].minor.yy278.n ) sqlite3SrcListAddAlias(yygotominor.yy347,&yymsp[-2].minor.yy278);
    if( yymsp[-1].minor.yy122 ){
      if( yygotominor.yy347 && yygotominor.yy347->nSrc>1 ){ yygotominor.yy347->a[yygotominor.yy347->nSrc-2].pOn = yymsp[-1].minor.yy122; }
      else { sqlite3ExprDelete(yymsp[-1].minor.yy122); }
    }
    if( yymsp[0].minor.yy180 ){
      if( yygotominor.yy347 && yygotominor.yy347->nSrc>1 ){ yygotominor.yy347->a[yygotominor.yy347->nSrc-2].pUsing = yymsp[0].minor.yy180; }
      else { sqlite3IdListDelete(yymsp[0].minor.yy180); }
    }
  }
#line 2229 "parse.c"
        break;
      case 129:
#line 509 "parse.y"
{
     yygotominor.yy159 = sqlite3SelectNew(0,yymsp[0].minor.yy347,0,0,0,0,0,0,0);
  }
#line 2236 "parse.c"
        break;
      case 130:
#line 515 "parse.y"
{yygotominor.yy278.z=0; yygotominor.yy278.n=0;}
#line 2241 "parse.c"
        break;
      case 132:
#line 520 "parse.y"
{yygotominor.yy347 = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy278,&yymsp[0].minor.yy278);}
#line 2246 "parse.c"
        break;
      case 133:
#line 524 "parse.y"
{ yygotominor.yy392 = JT_INNER; }
#line 2251 "parse.c"
        break;
      case 134:
#line 525 "parse.y"
{ yygotominor.yy392 = sqlite3JoinType(pParse,&yymsp[-1].minor.yy0,0,0); }
#line 2256 "parse.c"
        break;
      case 135:
#line 526 "parse.y"
{ yygotominor.yy392 = sqlite3JoinType(pParse,&yymsp[-2].minor.yy0,&yymsp[-1].minor.yy278,0); }
#line 2261 "parse.c"
        break;
      case 136:
#line 528 "parse.y"
{ yygotominor.yy392 = sqlite3JoinType(pParse,&yymsp[-3].minor.yy0,&yymsp[-2].minor.yy278,&yymsp[-1].minor.yy278); }
#line 2266 "parse.c"
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
{yygotominor.yy122 = yymsp[0].minor.yy122;}
#line 2279 "parse.c"
        break;
      case 138:
      case 153:
      case 160:
      case 208:
      case 232:
      case 234:
      case 238:
#line 533 "parse.y"
{yygotominor.yy122 = 0;}
#line 2290 "parse.c"
        break;
      case 139:
      case 178:
#line 537 "parse.y"
{yygotominor.yy180 = yymsp[-1].minor.yy180;}
#line 2296 "parse.c"
        break;
      case 140:
      case 176:
      case 177:
#line 538 "parse.y"
{yygotominor.yy180 = 0;}
#line 2303 "parse.c"
        break;
      case 142:
      case 152:
#line 549 "parse.y"
{yygotominor.yy442 = yymsp[0].minor.yy442;}
#line 2309 "parse.c"
        break;
      case 143:
#line 550 "parse.y"
{
  yygotominor.yy442 = sqlite3ExprListAppend(yymsp[-4].minor.yy442,yymsp[-2].minor.yy122,yymsp[-1].minor.yy278.n>0?&yymsp[-1].minor.yy278:0);
  if( yygotominor.yy442 ) yygotominor.yy442->a[yygotominor.yy442->nExpr-1].sortOrder = yymsp[0].minor.yy392;
}
#line 2317 "parse.c"
        break;
      case 144:
#line 554 "parse.y"
{
  yygotominor.yy442 = sqlite3ExprListAppend(0,yymsp[-2].minor.yy122,yymsp[-1].minor.yy278.n>0?&yymsp[-1].minor.yy278:0);
  if( yygotominor.yy442 && yygotominor.yy442->a ) yygotominor.yy442->a[0].sortOrder = yymsp[0].minor.yy392;
}
#line 2325 "parse.c"
        break;
      case 146:
      case 148:
#line 563 "parse.y"
{yygotominor.yy392 = SQLITE_SO_ASC;}
#line 2331 "parse.c"
        break;
      case 147:
#line 564 "parse.y"
{yygotominor.yy392 = SQLITE_SO_DESC;}
#line 2336 "parse.c"
        break;
      case 149:
#line 566 "parse.y"
{yygotominor.yy278.z = 0; yygotominor.yy278.n = 0;}
#line 2341 "parse.c"
        break;
      case 155:
#line 584 "parse.y"
{yygotominor.yy64.pLimit = 0; yygotominor.yy64.pOffset = 0;}
#line 2346 "parse.c"
        break;
      case 156:
#line 585 "parse.y"
{yygotominor.yy64.pLimit = yymsp[0].minor.yy122; yygotominor.yy64.pOffset = 0;}
#line 2351 "parse.c"
        break;
      case 157:
#line 587 "parse.y"
{yygotominor.yy64.pLimit = yymsp[-2].minor.yy122; yygotominor.yy64.pOffset = yymsp[0].minor.yy122;}
#line 2356 "parse.c"
        break;
      case 158:
#line 589 "parse.y"
{yygotominor.yy64.pOffset = yymsp[-2].minor.yy122; yygotominor.yy64.pLimit = yymsp[0].minor.yy122;}
#line 2361 "parse.c"
        break;
      case 159:
#line 593 "parse.y"
{sqlite3DeleteFrom(pParse,yymsp[-2].minor.yy347,yymsp[-1].minor.yy122, yymsp[0].minor.yy64.pLimit, yymsp[0].minor.yy64.pOffset);}
#line 2366 "parse.c"
        break;
      case 162:
#line 605 "parse.y"
{sqlite3Update(pParse,yymsp[-4].minor.yy347,yymsp[-2].minor.yy442,yymsp[-1].minor.yy122,OE_Default, yymsp[0].minor.yy64.pLimit, yymsp[0].minor.yy64.pOffset);}
#line 2371 "parse.c"
        break;
      case 163:
#line 611 "parse.y"
{yygotominor.yy442 = sqlite3ExprListAppend(yymsp[-4].minor.yy442,yymsp[0].minor.yy122,&yymsp[-2].minor.yy278);}
#line 2376 "parse.c"
        break;
      case 164:
#line 612 "parse.y"
{yygotominor.yy442 = sqlite3ExprListAppend(0,yymsp[0].minor.yy122,&yymsp[-2].minor.yy278);}
#line 2381 "parse.c"
        break;
      case 165:
#line 621 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy347, 0, yymsp[0].minor.yy139, 0, yymsp[-2].minor.yy180, yymsp[-5].minor.yy392);}
#line 2386 "parse.c"
        break;
      case 166:
#line 625 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy347, yymsp[0].minor.yy442, 0, 0, yymsp[-2].minor.yy180, yymsp[-5].minor.yy392);}
#line 2391 "parse.c"
        break;
      case 167:
#line 629 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy347, yymsp[0].minor.yy442, 0, 0, yymsp[-2].minor.yy180, yymsp[-4].minor.yy392);}
#line 2396 "parse.c"
        break;
      case 168:
#line 632 "parse.y"
{sqlite3Insert(pParse, yymsp[-2].minor.yy347, 0, 0, yymsp[0].minor.yy159, yymsp[-1].minor.yy180, yymsp[-4].minor.yy392);}
#line 2401 "parse.c"
        break;
      case 169:
#line 636 "parse.y"
{ yygotominor.yy392 = OE_Default; }
#line 2406 "parse.c"
        break;
      case 171:
#line 642 "parse.y"
{ yygotominor.yy139 = sqlite3ValuesListAppend(yymsp[-4].minor.yy139, yymsp[-1].minor.yy442);}
#line 2411 "parse.c"
        break;
      case 172:
#line 643 "parse.y"
{ yygotominor.yy139 = sqlite3ValuesListAppend(0, yymsp[-1].minor.yy442); }
#line 2416 "parse.c"
        break;
      case 173:
#line 644 "parse.y"
{ yygotominor.yy139 = 0; }
#line 2421 "parse.c"
        break;
      case 174:
      case 235:
#line 649 "parse.y"
{yygotominor.yy442 = sqlite3ExprListAppend(yymsp[-2].minor.yy442,yymsp[0].minor.yy122,0);}
#line 2427 "parse.c"
        break;
      case 175:
      case 236:
#line 650 "parse.y"
{yygotominor.yy442 = sqlite3ExprListAppend(0,yymsp[0].minor.yy122,0);}
#line 2433 "parse.c"
        break;
      case 179:
#line 660 "parse.y"
{yygotominor.yy180 = sqlite3IdListAppend(yymsp[-2].minor.yy180,&yymsp[0].minor.yy278);}
#line 2438 "parse.c"
        break;
      case 180:
#line 661 "parse.y"
{yygotominor.yy180 = sqlite3IdListAppend(0,&yymsp[0].minor.yy278);}
#line 2443 "parse.c"
        break;
      case 182:
#line 672 "parse.y"
{yygotominor.yy122 = yymsp[-1].minor.yy122; sqlite3ExprSpan(yygotominor.yy122,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0); }
#line 2448 "parse.c"
        break;
      case 183:
      case 188:
      case 189:
#line 673 "parse.y"
{yygotominor.yy122 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0);}
#line 2455 "parse.c"
        break;
      case 184:
      case 185:
#line 674 "parse.y"
{yygotominor.yy122 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy0);}
#line 2461 "parse.c"
        break;
      case 186:
#line 676 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy278);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy278);
  yygotominor.yy122 = sqlite3Expr(TK_DOT, temp1, temp2, 0);
}
#line 2470 "parse.c"
        break;
      case 187:
#line 681 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-4].minor.yy278);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy278);
  Expr *temp3 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy278);
  Expr *temp4 = sqlite3Expr(TK_DOT, temp2, temp3, 0);
  yygotominor.yy122 = sqlite3Expr(TK_DOT, temp1, temp4, 0);
}
#line 2481 "parse.c"
        break;
      case 190:
#line 690 "parse.y"
{yygotominor.yy122 = sqlite3RegisterExpr(pParse, &yymsp[0].minor.yy0);}
#line 2486 "parse.c"
        break;
      case 191:
      case 192:
#line 691 "parse.y"
{
  Token *pToken = &yymsp[0].minor.yy0;
  Expr *pExpr = yygotominor.yy122 = sqlite3Expr(TK_VARIABLE, 0, 0, pToken);
  //sqlite3ExprAssignVarNumber(pParse, pExpr);
}
#line 2496 "parse.c"
        break;
      case 193:
#line 702 "parse.y"
{
  yygotominor.yy122 = sqlite3Expr(TK_CAST, yymsp[-3].minor.yy122, 0, &yymsp[-1].minor.yy278);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-5].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2504 "parse.c"
        break;
      case 194:
#line 707 "parse.y"
{
  yygotominor.yy122 = sqlite3ExprFunction(yymsp[-1].minor.yy442, &yymsp[-4].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-4].minor.yy0,&yymsp[0].minor.yy0);
  if( yymsp[-2].minor.yy392 && yygotominor.yy122 ){
    yygotominor.yy122->flags |= EP_Distinct;
  }
}
#line 2515 "parse.c"
        break;
      case 195:
#line 714 "parse.y"
{
  yygotominor.yy122 = sqlite3ExprFunction(0, &yymsp[-3].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2523 "parse.c"
        break;
      case 196:
#line 718 "parse.y"
{
  /* The CURRENT_TIME, CURRENT_DATE, and CURRENT_TIMESTAMP values are
  ** treated as functions that return constants */
  yygotominor.yy122 = sqlite3ExprFunction(0,&yymsp[0].minor.yy0);
  if( yygotominor.yy122 ) yygotominor.yy122->op = TK_CONST_FUNC;  
}
#line 2533 "parse.c"
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
{yygotominor.yy122 = sqlite3Expr(yymsp[-1].major, yymsp[-2].minor.yy122, yymsp[0].minor.yy122, 0);}
#line 2545 "parse.c"
        break;
      case 205:
#line 734 "parse.y"
{yygotominor.yy318.eOperator = yymsp[0].minor.yy0; yygotominor.yy318.not = 0;}
#line 2550 "parse.c"
        break;
      case 206:
#line 735 "parse.y"
{yygotominor.yy318.eOperator = yymsp[0].minor.yy0; yygotominor.yy318.not = 1;}
#line 2555 "parse.c"
        break;
      case 209:
#line 740 "parse.y"
{
  ExprList *pList;
  pList = sqlite3ExprListAppend(0, yymsp[-3].minor.yy122, 0);
  pList = sqlite3ExprListAppend(pList, yymsp[-1].minor.yy122, 0);
  if( yymsp[0].minor.yy122 ){
    pList = sqlite3ExprListAppend(pList, yymsp[0].minor.yy122, 0);
  }
  //yygotominor.yy122 = sqlite3ExprFunction(pList, &yymsp[-2].minor.yy318.eOperator);
  yygotominor.yy122 = sqlite3ExprLikeOp(pList, &yymsp[-2].minor.yy318.eOperator);
  if( yymsp[-2].minor.yy318.not ) yygotominor.yy122 = sqlite3Expr(TK_NOT, yygotominor.yy122, 0, 0);
  sqlite3ExprSpan(yygotominor.yy122, &yymsp[-3].minor.yy122->span, &yymsp[-1].minor.yy122->span);
}
#line 2571 "parse.c"
        break;
      case 210:
#line 753 "parse.y"
{
  yygotominor.yy122 = sqlite3Expr(yymsp[0].major, yymsp[-1].minor.yy122, 0, 0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-1].minor.yy122->span,&yymsp[0].minor.yy0);
}
#line 2579 "parse.c"
        break;
      case 211:
#line 757 "parse.y"
{
  yygotominor.yy122 = sqlite3Expr(TK_ISNULL, yymsp[-2].minor.yy122, 0, 0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-2].minor.yy122->span,&yymsp[0].minor.yy0);
}
#line 2587 "parse.c"
        break;
      case 212:
#line 761 "parse.y"
{
  yygotominor.yy122 = sqlite3Expr(TK_NOTNULL, yymsp[-2].minor.yy122, 0, 0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-2].minor.yy122->span,&yymsp[0].minor.yy0);
}
#line 2595 "parse.c"
        break;
      case 213:
#line 765 "parse.y"
{
  yygotominor.yy122 = sqlite3Expr(TK_NOTNULL, yymsp[-3].minor.yy122, 0, 0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-3].minor.yy122->span,&yymsp[0].minor.yy0);
}
#line 2603 "parse.c"
        break;
      case 214:
#line 769 "parse.y"
{
  yygotominor.yy122 = sqlite3Expr(yymsp[-1].major, yymsp[0].minor.yy122, 0, 0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy122->span);
}
#line 2611 "parse.c"
        break;
      case 215:
#line 773 "parse.y"
{
  yygotominor.yy122 = sqlite3Expr(TK_UMINUS, yymsp[0].minor.yy122, 0, 0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy122->span);
}
#line 2619 "parse.c"
        break;
      case 216:
#line 777 "parse.y"
{
  yygotominor.yy122 = sqlite3Expr(TK_UPLUS, yymsp[0].minor.yy122, 0, 0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy122->span);
}
#line 2627 "parse.c"
        break;
      case 219:
#line 788 "parse.y"
{ yygotominor.yy122 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0); }
#line 2632 "parse.c"
        break;
      case 220:
#line 791 "parse.y"
{
  ExprList *pList = sqlite3ExprListAppend(0, yymsp[-2].minor.yy122, 0);
  pList = sqlite3ExprListAppend(pList, yymsp[0].minor.yy122, 0);
  yygotominor.yy122 = sqlite3Expr(TK_BETWEEN, yymsp[-4].minor.yy122, 0, 0);
  if( yygotominor.yy122 ){
    yygotominor.yy122->pList = pList;
  }else{
    sqlite3ExprListDelete(pList);
  } 
  if( yymsp[-3].minor.yy392 ) yygotominor.yy122 = sqlite3Expr(TK_NOT, yygotominor.yy122, 0, 0);
  sqlite3ExprSpan(yygotominor.yy122,&yymsp[-4].minor.yy122->span,&yymsp[0].minor.yy122->span);
}
#line 2648 "parse.c"
        break;
      case 223:
#line 807 "parse.y"
{
    yygotominor.yy122 = sqlite3Expr(TK_IN, yymsp[-4].minor.yy122, 0, 0);
    if( yygotominor.yy122 ){
      yygotominor.yy122->pList = yymsp[-1].minor.yy442;
    }else{
      sqlite3ExprListDelete(yymsp[-1].minor.yy442);
    }
    if( yymsp[-3].minor.yy392 ) yygotominor.yy122 = sqlite3Expr(TK_NOT, yygotominor.yy122, 0, 0);
    sqlite3ExprSpan(yygotominor.yy122,&yymsp[-4].minor.yy122->span,&yymsp[0].minor.yy0);
  }
#line 2662 "parse.c"
        break;
      case 224:
#line 817 "parse.y"
{
    yygotominor.yy122 = sqlite3Expr(TK_SELECT, 0, 0, 0);
    if( yygotominor.yy122 ){
      yygotominor.yy122->pSelect = yymsp[-1].minor.yy159;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy159);
    }
    sqlite3ExprSpan(yygotominor.yy122,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0);
  }
#line 2675 "parse.c"
        break;
      case 225:
#line 826 "parse.y"
{
    yygotominor.yy122 = sqlite3Expr(TK_IN, yymsp[-4].minor.yy122, 0, 0);
    if( yygotominor.yy122 ){
      yygotominor.yy122->pSelect = yymsp[-1].minor.yy159;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy159);
    }
    if( yymsp[-3].minor.yy392 ) yygotominor.yy122 = sqlite3Expr(TK_NOT, yygotominor.yy122, 0, 0);
    sqlite3ExprSpan(yygotominor.yy122,&yymsp[-4].minor.yy122->span,&yymsp[0].minor.yy0);
  }
#line 2689 "parse.c"
        break;
      case 226:
#line 836 "parse.y"
{
    SrcList *pSrc = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy278,&yymsp[0].minor.yy278);
    yygotominor.yy122 = sqlite3Expr(TK_IN, yymsp[-3].minor.yy122, 0, 0);
    if( yygotominor.yy122 ){
      yygotominor.yy122->pSelect = sqlite3SelectNew(0,pSrc,0,0,0,0,0,0,0);
    }else{
      sqlite3SrcListDelete(pSrc);
    }
    if( yymsp[-2].minor.yy392 ) yygotominor.yy122 = sqlite3Expr(TK_NOT, yygotominor.yy122, 0, 0);
    sqlite3ExprSpan(yygotominor.yy122,&yymsp[-3].minor.yy122->span,yymsp[0].minor.yy278.z?&yymsp[0].minor.yy278:&yymsp[-1].minor.yy278);
  }
#line 2704 "parse.c"
        break;
      case 227:
#line 847 "parse.y"
{
    Expr *p = yygotominor.yy122 = sqlite3Expr(TK_EXISTS, 0, 0, 0);
    if( p ){
      p->pSelect = yymsp[-1].minor.yy159;
      sqlite3ExprSpan(p,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy159);
    }
  }
#line 2717 "parse.c"
        break;
      case 228:
#line 859 "parse.y"
{
  yygotominor.yy122 = sqlite3Expr(TK_CASE, yymsp[-3].minor.yy122, yymsp[-1].minor.yy122, 0);
  if( yygotominor.yy122 ){
    yygotominor.yy122->pList = yymsp[-2].minor.yy442;
  }else{
    sqlite3ExprListDelete(yymsp[-2].minor.yy442);
  }
  sqlite3ExprSpan(yygotominor.yy122, &yymsp[-4].minor.yy0, &yymsp[0].minor.yy0);
}
#line 2730 "parse.c"
        break;
      case 229:
#line 870 "parse.y"
{
  yygotominor.yy442 = sqlite3ExprListAppend(yymsp[-4].minor.yy442, yymsp[-2].minor.yy122, 0);
  yygotominor.yy442 = sqlite3ExprListAppend(yygotominor.yy442, yymsp[0].minor.yy122, 0);
}
#line 2738 "parse.c"
        break;
      case 230:
#line 874 "parse.y"
{
  yygotominor.yy442 = sqlite3ExprListAppend(0, yymsp[-2].minor.yy122, 0);
  yygotominor.yy442 = sqlite3ExprListAppend(yygotominor.yy442, yymsp[0].minor.yy122, 0);
}
#line 2746 "parse.c"
        break;
      case 241:
#line 918 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy278.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy278.z, yymsp[-1].minor.yy278.n);
  }
  yygotominor.yy442 = sqlite3ExprListAppend(yymsp[-4].minor.yy442, p, &yymsp[-2].minor.yy278);
  if( yygotominor.yy442 ) yygotominor.yy442->a[yygotominor.yy442->nExpr-1].sortOrder = yymsp[0].minor.yy392;
}
#line 2759 "parse.c"
        break;
      case 242:
#line 927 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy278.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy278.z, yymsp[-1].minor.yy278.n);
  }
  yygotominor.yy442 = sqlite3ExprListAppend(0, p, &yymsp[-2].minor.yy278);
  if( yygotominor.yy442 ) yygotominor.yy442->a[yygotominor.yy442->nExpr-1].sortOrder = yymsp[0].minor.yy392;
}
#line 2772 "parse.c"
        break;
      case 249:
#line 1058 "parse.y"
{yygotominor.yy392 = OE_Rollback;}
#line 2777 "parse.c"
        break;
      case 250:
#line 1059 "parse.y"
{yygotominor.yy392 = OE_Abort;}
#line 2782 "parse.c"
        break;
      case 251:
#line 1060 "parse.y"
{yygotominor.yy392 = OE_Fail;}
#line 2787 "parse.c"
        break;
      case 252:
#line 1116 "parse.y"
{
    sqlite3SetStatement(pParse, yymsp[0].minor.yy442, 0, SQLTYPE_SET);
}
#line 2794 "parse.c"
        break;
      case 253:
#line 1120 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy278, SQLTYPE_SET_NAMES);   
}
#line 2801 "parse.c"
        break;
      case 254:
#line 1124 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy278, SQLTYPE_SET_CHARACTER_SET);
}
#line 2808 "parse.c"
        break;
      case 255:
#line 1130 "parse.y"
{
    yygotominor.yy442 = sqlite3ExprListAppend(yymsp[-5].minor.yy442, yymsp[0].minor.yy122, &yymsp[-2].minor.yy278);
}
#line 2815 "parse.c"
        break;
      case 256:
#line 1134 "parse.y"
{
    yygotominor.yy442 = sqlite3ExprListAppend(0, yymsp[0].minor.yy122, &yymsp[-2].minor.yy278);                         
}
#line 2822 "parse.c"
        break;
      case 260:
#line 1142 "parse.y"
{ sqlite3CheckSetScope(pParse, &yymsp[-1].minor.yy0); }
#line 2827 "parse.c"
        break;
      case 262:
#line 1146 "parse.y"
{ yygotominor.yy278 = yymsp[0].minor.yy278; }
#line 2832 "parse.c"
        break;
      case 263:
#line 1147 "parse.y"
{ yygotominor.yy278 = yymsp[0].minor.yy0; }
#line 2837 "parse.c"
        break;
      case 268:
#line 1155 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_DATABASES);
}
#line 2844 "parse.c"
        break;
      case 269:
#line 1159 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_TABLES);
}
#line 2851 "parse.c"
        break;
      case 270:
#line 1163 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_TABLE_STATUS);
}
#line 2858 "parse.c"
        break;
      case 271:
#line 1167 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_VARIABLES);
}
#line 2865 "parse.c"
        break;
      case 275:
#line 1175 "parse.y"
{
    if (yymsp[0].minor.yy122) {
        sqlite3ExprDelete(yymsp[0].minor.yy122);
    }
}
#line 2874 "parse.c"
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
#line 2941 "parse.c"
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
