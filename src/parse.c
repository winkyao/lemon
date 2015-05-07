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
#define YYNOCODE 249
#define YYACTIONTYPE unsigned short int
#define sqlite3ParserTOKENTYPE Token
typedef union {
  sqlite3ParserTOKENTYPE yy0;
  Select* yy43;
  struct LimitVal yy84;
  struct LikeOp yy86;
  Token yy178;
  struct {int value; int mask;} yy207;
  ExprList* yy242;
  int yy316;
  IdList* yy352;
  SrcList* yy419;
  ValuesList* yy447;
  Expr* yy450;
  int yy497;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define sqlite3ParserARG_SDECL Parse *pParse;
#define sqlite3ParserARG_PDECL ,Parse *pParse
#define sqlite3ParserARG_FETCH Parse *pParse = yypParser->pParse
#define sqlite3ParserARG_STORE yypParser->pParse = pParse
#define YYNSTATE 501
#define YYNRULE 276
#define YYERRORSYMBOL 146
#define YYERRSYMDT yy497
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
 /*     0 */   234,  320,  317,  146,  338,  368,   57,   56,   56,   56,
 /*    10 */    56,  442,   58,   58,   58,   58,   59,   59,   60,   60,
 /*    20 */    60,   61,   63,   58,   58,   58,   58,   59,   59,   60,
 /*    30 */    60,   60,   61,  381,   58,   58,   58,   58,   59,   59,
 /*    40 */    60,   60,   60,   61,   59,   59,   60,   60,   60,   61,
 /*    50 */    55,   53,  242,  389,  392,  386,  386,   57,   56,   56,
 /*    60 */    56,   56,  165,   58,   58,   58,   58,   59,   59,   60,
 /*    70 */    60,   60,   61,  234,   61,  238,  368,   72,  274,   57,
 /*    80 */   394,  394,   99,  311,  151,  213,  238,  453,  179,  312,
 /*    90 */   482,  483,  484,  333,  448,   18,  213,  334,  445,  316,
 /*   100 */   321,  267,  368,  163,  128,  442,  381,   62,  403,  169,
 /*   110 */    52,  130,  159,  376,  168,  778,  105,  500,  127,  463,
 /*   120 */     1,  358,   36,   55,   53,  242,  389,  392,  386,  386,
 /*   130 */    57,   56,   56,   56,   56,  235,   58,   58,   58,   58,
 /*   140 */    59,   59,   60,   60,   60,   61,  234,  359,  254,   94,
 /*   150 */   335,  163,   57,  139,  339,  189,  263,  193,  264,  150,
 /*   160 */   159,  278,  204,  253,  214,  339,  189,  263,  193,  264,
 /*   170 */   150,  451,  103,  368,    3,  214,  309,  119,  155,  381,
 /*   180 */   446,  286,  289,  290,  231,  415,  450,  378,  452,  143,
 /*   190 */   291,  488,  489,  490,  335,  359,   55,   53,  242,  389,
 /*   200 */   392,  386,  386,   57,   56,   56,   56,   56,  161,   58,
 /*   210 */    58,   58,   58,   59,   59,   60,   60,   60,   61,  234,
 /*   220 */   103,  336,  337,  155,  421,   57,  286,  289,  290,  267,
 /*   230 */   341,  342,  380,  462,  267,  291,  267,   74,  454,  488,
 /*   240 */   489,  490,   62,  359,  169,  453,  130,  186,  440,  358,
 /*   250 */    30,  464,  381,   18,  358,   30,  358,   30,   62,  449,
 /*   260 */   169,  319,  130,  362,    1,  336,  337,  148,  194,   55,
 /*   270 */    53,  242,  389,  392,  386,  386,   57,   56,   56,   56,
 /*   280 */    56,  424,   58,   58,   58,   58,   59,   59,   60,   60,
 /*   290 */    60,   61,  234,  364,  364,  364,  267,  245,   57,  280,
 /*   300 */   155,  129,  359,  286,  289,  290,  399,  267,  395,  267,
 /*   310 */   335,  400,  291,  400,  149,  135,  358,   25,  267,  283,
 /*   320 */   267,  241,  371,  372,  201,  381,  211,  358,   43,  358,
 /*   330 */    31,  270,  371,  372,  134,  335,  359,   68,  358,   36,
 /*   340 */   358,   43,   55,   53,  242,  389,  392,  386,  386,   57,
 /*   350 */    56,   56,   56,   56,  425,   58,   58,   58,   58,   59,
 /*   360 */    59,   60,   60,   60,   61,  345,  294,  476,  234,   60,
 /*   370 */    60,   60,   61,  396,   57,  251,  335,   10,  440,  202,
 /*   380 */   346,  336,  337,  200,  284,  167,  335,  274,  250,  394,
 /*   390 */   394,  335,  281,  116,  315,  167,  347,  335,  343,  423,
 /*   400 */   151,  381,  496,  335,  358,    4,  336,  337,  303,  344,
 /*   410 */    71,  247,  205,  114,  274,  415,  394,  394,   55,   53,
 /*   420 */   242,  389,  392,  386,  386,   57,   56,   56,   56,   56,
 /*   430 */   428,   58,   58,   58,   58,   59,   59,   60,   60,   60,
 /*   440 */    61,  461,  118,  429,  234,  382,  494,  336,  337,  460,
 /*   450 */    57,  235,  311,  268,  206,  214,  212,  336,  337,  482,
 /*   460 */   483,  484,  336,  337,  408,  384,  385,  267,  336,  337,
 /*   470 */   267,  411,  178,  497,  336,  337,  146,  381,  368,  274,
 /*   480 */   165,  394,  394,  378,  271,  143,  412,  358,   26,  480,
 /*   490 */   358,   21,  383,  228,   55,   53,  242,  389,  392,  386,
 /*   500 */   386,   57,   56,   56,   56,   56,  447,   58,   58,   58,
 /*   510 */    58,   59,   59,   60,   60,   60,   61,  267,  314,  267,
 /*   520 */   234,  267,  491,  491,  267,  246,   57,  267,  501,    6,
 /*   530 */   267,  320,  317,  434,  285,  267,  410,  358,   29,  358,
 /*   540 */    48,  358,   22,  267,  358,   46,  267,  358,   85,  368,
 /*   550 */   358,   83,  419,  381,  480,  358,   87,  435,  357,  124,
 /*   560 */   310,  140,  356,  358,   88,  440,  358,   95,  368,  223,
 /*   570 */    55,   53,  242,  389,  392,  386,  386,   57,   56,   56,
 /*   580 */    56,   56,  217,   58,   58,   58,   58,   59,   59,   60,
 /*   590 */    60,   60,   61,  267,  415,  267,  234,  267,  177,  267,
 /*   600 */   131,  132,   57,  267,  440,  166,  267,  409,  229,  133,
 /*   610 */   267,  252,   49,  358,   96,  358,   30,  358,   16,  358,
 /*   620 */    86,  267,  419,  358,   47,  313,  358,   97,  100,  381,
 /*   630 */   358,   98,  410,  208,  363,  359,  359,  248,  440,  368,
 /*   640 */   223,  358,   23,  212,  303,  223,   55,   53,  242,  389,
 /*   650 */   392,  386,  386,   57,   56,   56,   56,   56,  243,   58,
 /*   660 */    58,   58,   58,   59,   59,   60,   60,   60,   61,  234,
 /*   670 */   267,  249,  400,  267,  538,   57,  267,  481,  267,  468,
 /*   680 */   267,  244,  212,  267,  224,  267,  152,  153,  154,  267,
 /*   690 */   358,   32,   19,  358,   33,  303,  358,   24,  358,   34,
 /*   700 */   358,   35,  381,  358,   37,  358,   38,  223,  306,  358,
 /*   710 */    39,  223,  368,  145,  135,   67,  212,   69,  157,   55,
 /*   720 */    53,  242,  389,  392,  386,  386,   57,   56,   56,   56,
 /*   730 */    56,  267,   58,   58,   58,   58,   59,   59,   60,   60,
 /*   740 */    60,   61,  234,  267,   17,  267,  301,  267,   57,  267,
 /*   750 */   227,  358,   27,  359,  374,  374,  267,  357,  267,  308,
 /*   760 */   109,  356,  122,  358,   28,  358,   40,  358,   41,  358,
 /*   770 */    42,  369,  353,  162,  272,  381,  358,   44,  358,   45,
 /*   780 */   354,  495,  390,  368,  257,  433,  237,  160,  259,   20,
 /*   790 */   188,  377,  401,   53,  242,  389,  392,  386,  386,   57,
 /*   800 */    56,   56,   56,   56,  398,   58,   58,   58,   58,   59,
 /*   810 */    59,   60,   60,   60,   61,  234,  390,  190,  162,  417,
 /*   820 */   350,   57,   13,  426,  438,  216,  191,  293,  473,  351,
 /*   830 */   414,  474,  477,  418,  210,  456,  430,  147,  431,  436,
 /*   840 */   455,   13,  109,  109,  437,  109,   80,  218,  381,   80,
 /*   850 */   147,  221,  495,  302,  387,  493,  328,  195,  432,  123,
 /*   860 */   192,  373,  375,  273,  276,  391,  404,  242,  389,  392,
 /*   870 */   386,  386,   57,   56,   56,   56,   56,    5,   58,   58,
 /*   880 */    58,   58,   59,   59,   60,   60,   60,   61,    5,  475,
 /*   890 */    74,  407,   64,  275,  429,  439,  441,  240,  288,  226,
 /*   900 */   486,  487,  492,   64,  275,  324,  120,  323,  240,  326,
 /*   910 */   269,    9,  327,  256,  331,  260,  261,  262,  340,  348,
 /*   920 */   239,  269,  349,  360,  352,  355,   74,  196,  279,  277,
 /*   930 */    73,  197,   51,  198,   70,  199,  402,  171,  144,  361,
 /*   940 */   203,  380,  172,  405,  406,  106,   75,   90,  207,  282,
 /*   950 */   416,  420,  380,  173,  209,  232,  443,  467,  444,   66,
 /*   960 */    65,    5,  457,  233,  458,  459,  175,   64,  265,  266,
 /*   970 */    66,   65,  362,  176,  295,  110,   64,  275,   64,  265,
 /*   980 */   266,  240,  296,  362,  158,  299,  104,  465,  165,  115,
 /*   990 */   469,  225,   11,  304,  269,  307,  471,  472,  236,  322,
 /*  1000 */   230,   84,  364,  364,  364,  365,  366,  367,   12,  325,
 /*  1010 */   258,  329,  187,  364,  364,  364,  365,  366,  367,   12,
 /*  1020 */   174,    5,   89,    2,  330,  380,  332,  102,  164,  183,
 /*  1030 */   255,   50,  539,  184,  185,  219,   64,  275,  540,  141,
 /*  1040 */   142,  240,   54,   66,   65,  422,  370,  101,  379,  388,
 /*  1050 */   170,   64,  265,  266,  269,  121,  362,  393,  397,  183,
 /*  1060 */   255,    7,   14,  184,  185,  219,    8,   13,  413,  107,
 /*  1070 */   136,  108,  427,   91,  287,  215,   92,  101,  479,   76,
 /*  1080 */    77,   93,  292,  191,  156,  380,  364,  364,  364,  365,
 /*  1090 */   366,  367,   12,  297,  111,  220,  222,   15,   78,  405,
 /*  1100 */   466,  470,  181,   66,   65,  498,  305,  485,  479,   79,
 /*  1110 */   113,   64,  265,  266,  160,  117,  362,  137,  180,  182,
 /*  1120 */    81,   82,  318,  526,  300,  112,  478,  499,  526,  298,
 /*  1130 */   526,  526,  526,  526,  165,  526,  526,  526,  526,  526,
 /*  1140 */   526,  526,  526,  380,  526,  526,  364,  364,  364,  365,
 /*  1150 */   366,  367,   12,  526,  300,  112,  478,  526,  526,  298,
 /*  1160 */   526,  125,  126,  138,  165,  526,  526,  526,  526,  526,
 /*  1170 */   449,  526,  526,  526,  362,  526,  526,  526,  526,  526,
 /*  1180 */   526,  526,  526,  526,  526,  526,  526,  526,  526,  526,
 /*  1190 */   526,  526,  526,  138,  526,  526,  526,  526,  526,  526,
 /*  1200 */   526,  526,  526,  526,  364,  364,  364,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    16,    3,    4,   19,  177,   21,   22,   74,   75,   76,
 /*    10 */    77,  184,   79,   80,   81,   82,   83,   84,   85,   86,
 /*    20 */    87,   88,   78,   79,   80,   81,   82,   83,   84,   85,
 /*    30 */    86,   87,   88,   49,   79,   80,   81,   82,   83,   84,
 /*    40 */    85,   86,   87,   88,   83,   84,   85,   86,   87,   88,
 /*    50 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    60 */    76,   77,  112,   79,   80,   81,   82,   83,   84,   85,
 /*    70 */    86,   87,   88,   16,   88,   16,   92,   20,  108,   22,
 /*    80 */   110,  111,   23,  131,   50,   26,   16,  158,  136,  137,
 /*    90 */   138,  139,  140,  164,  178,  166,   26,  176,  177,  150,
 /*   100 */   151,  158,   21,  154,   20,  184,   49,  227,  228,  229,
 /*   110 */    53,  231,  163,   83,   84,  147,  148,  149,  189,  190,
 /*   120 */   152,  178,  179,   66,   67,   68,   69,   70,   71,   72,
 /*   130 */    73,   74,   75,   76,   77,  101,   79,   80,   81,   82,
 /*   140 */    83,   84,   85,   86,   87,   88,   16,  198,  151,   19,
 /*   150 */    21,  154,   22,   94,   95,   96,   97,   98,   99,  100,
 /*   160 */   163,  218,  219,   49,  105,   95,   96,   97,   98,   99,
 /*   170 */   100,  169,  223,   92,    1,  105,  239,  240,   94,   49,
 /*   180 */   178,   97,   98,   99,  167,  170,  178,  170,  171,  172,
 /*   190 */   106,  242,  243,  244,   21,  198,   66,   67,   68,   69,
 /*   200 */    70,   71,   72,   73,   74,   75,   76,   77,  163,   79,
 /*   210 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   220 */   223,   92,   93,   94,  209,   22,   97,   98,   99,  158,
 /*   230 */   194,  195,   65,  190,  158,  106,  158,  123,  190,  242,
 /*   240 */   243,  244,  227,  198,  229,  158,  231,  160,  158,  178,
 /*   250 */   179,  164,   49,  166,  178,  179,  178,  179,  227,   92,
 /*   260 */   229,  149,  231,   96,  152,   92,   93,  163,  199,   66,
 /*   270 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   280 */    77,    2,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   290 */    87,   88,   16,  126,  127,  128,  158,  221,   22,  221,
 /*   300 */    94,  163,  198,   97,   98,   99,  235,  158,    2,  158,
 /*   310 */    21,  235,  106,  235,  210,  211,  178,  179,  158,  215,
 /*   320 */   158,  173,  174,  175,  158,   49,  236,  178,  179,  178,
 /*   330 */   179,  173,  174,  175,  158,   21,  198,  134,  178,  179,
 /*   340 */   178,  179,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   350 */    74,   75,   76,   77,    2,   79,   80,   81,   82,   83,
 /*   360 */    84,   85,   86,   87,   88,   12,   16,    2,   16,   85,
 /*   370 */    86,   87,   88,    2,   22,  226,   21,    1,  158,  219,
 /*   380 */    27,   92,   93,  232,  158,  237,   21,  108,  226,  110,
 /*   390 */   111,   21,  158,   25,   14,  237,   43,   21,   45,   85,
 /*   400 */    50,   49,  203,   21,  178,  179,   92,   93,  158,   56,
 /*   410 */   134,  191,  158,  124,  108,  170,  110,  111,   66,   67,
 /*   420 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   430 */     2,   79,   80,   81,   82,   83,   84,   85,   86,   87,
 /*   440 */    88,  184,  240,  186,   16,   49,  247,   92,   93,  192,
 /*   450 */    22,  101,  131,  158,  209,  105,  236,   92,   93,  138,
 /*   460 */   139,  140,   92,   93,   20,   69,   70,  158,   92,   93,
 /*   470 */   158,  116,  222,   93,   92,   93,   19,   49,   21,  108,
 /*   480 */   112,  110,  111,  170,  171,  172,  116,  178,  179,  170,
 /*   490 */   178,  179,   96,  125,   66,   67,   68,   69,   70,   71,
 /*   500 */    72,   73,   74,   75,   76,   77,    2,   79,   80,   81,
 /*   510 */    82,   83,   84,   85,   86,   87,   88,  158,  245,  158,
 /*   520 */    16,  158,  142,  143,  158,   25,   22,  158,    0,  200,
 /*   530 */   158,    3,    4,   33,   85,  158,   20,  178,  179,  178,
 /*   540 */   179,  178,  179,  158,  178,  179,  158,  178,  179,   92,
 /*   550 */   178,  179,  158,   49,  170,  178,  179,   57,  109,  115,
 /*   560 */   241,    1,  113,  178,  179,  158,  178,  179,   21,  158,
 /*   570 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   580 */    76,   77,    2,   79,   80,   81,   82,   83,   84,   85,
 /*   590 */    86,   87,   88,  158,  170,  158,   16,  158,  191,  158,
 /*   600 */   163,  163,   22,  158,  158,  201,  158,  212,  197,   93,
 /*   610 */   158,  217,  208,  178,  179,  178,  179,  178,  179,  178,
 /*   620 */   179,  158,  158,  178,  179,  241,  178,  179,  158,   49,
 /*   630 */   178,  179,  116,  209,  158,  198,  198,  191,  158,   92,
 /*   640 */   158,  178,  179,  236,  158,  158,   66,   67,   68,   69,
 /*   650 */    70,   71,   72,   73,   74,   75,   76,   77,  221,   79,
 /*   660 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   670 */   158,  191,  235,  158,  114,   22,  158,  130,  158,  197,
 /*   680 */   158,  217,  236,  158,  197,  158,  102,  103,  104,  158,
 /*   690 */   178,  179,    1,  178,  179,  158,  178,  179,  178,  179,
 /*   700 */   178,  179,   49,  178,  179,  178,  179,  158,  222,  178,
 /*   710 */   179,  158,   21,  210,  211,  133,  236,  135,  163,   66,
 /*   720 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   730 */    77,  158,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   740 */    87,   88,   16,  158,    1,  158,  197,  158,   22,  158,
 /*   750 */   197,  178,  179,  198,  126,  127,  158,  109,  158,  222,
 /*   760 */    20,  113,   19,  178,  179,  178,  179,  178,  179,  178,
 /*   770 */   179,    2,   30,   70,   16,   49,  178,  179,  178,  179,
 /*   780 */    38,   21,   92,   92,   21,   23,   23,   20,   24,   20,
 /*   790 */    26,  170,  158,   67,   68,   69,   70,   71,   72,   73,
 /*   800 */    74,   75,   76,   77,    2,   79,   80,   81,   82,   83,
 /*   810 */    84,   85,   86,   87,   88,   16,  126,   96,  115,    2,
 /*   820 */    37,   22,   20,    2,    2,    2,  105,    2,    2,   46,
 /*   830 */   158,    2,    2,  158,  158,   95,  158,   20,  187,  187,
 /*   840 */   158,   20,   20,   20,  187,   20,   20,  158,   49,   20,
 /*   850 */    20,  158,   92,  158,   96,  158,  155,  202,   96,  200,
 /*   860 */   181,  238,  238,  230,  234,  230,  181,   68,   69,   70,
 /*   870 */    71,   72,   73,   74,   75,   76,   77,    1,   79,   80,
 /*   880 */    81,   82,   83,   84,   85,   86,   87,   88,    1,    2,
 /*   890 */   123,  181,   16,   17,  186,  181,  181,   21,  185,  203,
 /*   900 */   170,  170,  246,   16,   17,   10,  246,  153,   21,  153,
 /*   910 */    34,   20,  153,  161,   22,  165,  165,  101,  180,  180,
 /*   920 */    47,   34,  188,  198,  180,  180,  123,  203,  120,  118,
 /*   930 */   121,  204,  122,  205,  133,  206,  159,  233,  114,  207,
 /*   940 */    26,   65,  220,   21,  169,  159,  101,    1,  213,  117,
 /*   950 */   214,  214,   65,  220,  213,  182,  169,   18,  188,   83,
 /*   960 */    84,    1,  180,  182,  180,  180,  220,   91,   92,   93,
 /*   970 */    83,   84,   96,  220,  156,  196,   16,   17,   91,   92,
 /*   980 */    93,   21,   15,   96,  157,   15,    1,  159,  112,  224,
 /*   990 */   159,  203,    1,  225,   34,  224,  207,  207,  162,    2,
 /*  1000 */     2,  168,  126,  127,  128,  129,  130,  131,  132,    9,
 /*  1010 */    22,   21,   25,  126,  127,  128,  129,  130,  131,  132,
 /*  1020 */   183,    1,  183,    1,   21,   65,   21,   35,   51,    7,
 /*  1030 */     8,    1,  114,   11,   12,   13,   16,   17,  114,  114,
 /*  1040 */   114,   21,    1,   83,   84,   85,    2,   25,    2,   96,
 /*  1050 */    67,   91,   92,   93,   34,    1,   96,  109,   41,    7,
 /*  1060 */     8,  119,   20,   11,   12,   13,  119,   20,  116,    1,
 /*  1070 */   114,    2,    2,    1,   51,    2,    1,   25,   56,    1,
 /*  1080 */     1,    1,   51,  105,  100,   65,  126,  127,  128,  129,
 /*  1090 */   130,  131,  132,   16,  115,   14,   14,    1,   22,   21,
 /*  1100 */    17,   17,  144,   83,   84,    3,   20,  114,   56,   22,
 /*  1110 */    25,   91,   92,   93,   20,   25,   96,   20,   25,  145,
 /*  1120 */    22,   22,    5,  248,  102,  103,  104,    6,  248,  107,
 /*  1130 */   248,  248,  248,  248,  112,  248,  248,  248,  248,  248,
 /*  1140 */   248,  248,  248,   65,  248,  248,  126,  127,  128,  129,
 /*  1150 */   130,  131,  132,  248,  102,  103,  104,  248,  248,  107,
 /*  1160 */   248,   83,   84,  141,  112,  248,  248,  248,  248,  248,
 /*  1170 */    92,  248,  248,  248,   96,  248,  248,  248,  248,  248,
 /*  1180 */   248,  248,  248,  248,  248,  248,  248,  248,  248,  248,
 /*  1190 */   248,  248,  248,  141,  248,  248,  248,  248,  248,  248,
 /*  1200 */   248,  248,  248,  248,  126,  127,  128,
};
#define YY_SHIFT_USE_DFLT (-68)
#define YY_SHIFT_MAX 318
static const short yy_shift_ofst[] = {
 /*     0 */    -2, 1022, 1052,  876,  -16,  876, 1020, 1020, 1020,  129,
 /*    10 */   -50,  887, 1020, 1020, 1020, 1020,  -56,  382,   81,   30,
 /*    20 */    30,   57,  130,  203,  276,  352,  428,  504,  580,  653,
 /*    30 */   653,  653,  653,  653,  653,  653,  653,  653,  653,  653,
 /*    40 */   653,  653,  653,  653,  653,  653,  726,  799,  799,  960,
 /*    50 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    60 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    70 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    80 */  1020, 1020, 1020,  -67,   59,  -45,  -45,  -39,  284,  350,
 /*    90 */   382,  382,  382,  382,   81,  -14,  -68,  -68,  -68, 1078,
 /*   100 */    70,  -48,  353,  289,  365,  528,  457,  382,  457,  382,
 /*   110 */   382,  382,  382,  382,  382,  368,  382,  382,  547,  547,
 /*   120 */   114,  -50,  -50,  -68,  -68,  167,  167,   84,  206,  279,
 /*   130 */   173,  306,  371,  355,  370,  376,  314,  321,  380,  382,
 /*   140 */   449,  382,  382,  691,  382,  516,  382,  382,  -30,  516,
 /*   150 */   382,  382,  500,  500,  500,  382,  382,  -30,  382,  -30,
 /*   160 */   382,  -30,  382,  743,  742,  648,  444,  628,  628,  690,
 /*   170 */   690,  582,  742,  742,   34,  742,  742,  740,  767,   81,
 /*   180 */    81,  703,  703,  895,  895,  895,  891,  892,  892,  816,
 /*   190 */   816,  873,  816,  816,  -50,  803,  808,  809,  811,  810,
 /*   200 */   801,  824,  914,  922,  914,  824,  845,  832,  845,  832,
 /*   210 */   946,  914,  914,  922,  873,  816,  816,  816,  946,  939,
 /*   220 */   967,  824,  970,  824,  803,  810,  810,  985,  991,  985,
 /*   230 */   -68,  -68,  -68,  -68,  396,  584,  763,  764,  721,  783,
 /*   240 */   560,  769,  758,  802,  817,  821,  762,  822,  823,  825,
 /*   250 */   826,  829,  830,  760,  997, 1000,  998,  988,  990,  987,
 /*   260 */  1003, 1005,  992,  977, 1030,  918,  924,  925,  926, 1041,
 /*   270 */  1044, 1046,  953,  983,  948, 1054, 1017,  942, 1042,  947,
 /*   280 */  1047,  952, 1068, 1069,  956, 1070, 1023, 1072, 1073, 1075,
 /*   290 */  1079, 1031, 1080,  984,  978, 1081, 1077, 1083, 1082, 1084,
 /*   300 */   979, 1085, 1076, 1087, 1086, 1096, 1094, 1090, 1094, 1097,
 /*   310 */  1098,  993, 1093, 1099,  958,  974, 1102, 1117, 1121,
};
#define YY_REDUCE_USE_DFLT (-174)
#define YY_REDUCE_MAX 233
static const short yy_reduce_ofst[] = {
 /*     0 */   -32,  -51,   -3,  437,   15,  138,   76,  -57,   78,  -71,
 /*    10 */   104,  149,  151,   71,  160,  162, -120,   87,   17,  148,
 /*    20 */   158,   31,   31,   31,   31,   31,   31,   31,   31,   31,
 /*    30 */    31,   31,   31,   31,   31,   31,   31,   31,   31,   31,
 /*    40 */    31,   31,   31,   31,   31,   31,   31,   31,   31,  226,
 /*    50 */   309,  312,  359,  361,  363,  366,  369,  372,  377,  385,
 /*    60 */   388,  435,  439,  441,  445,  448,  452,  463,  512,  515,
 /*    70 */   518,  520,  522,  525,  527,  531,  573,  585,  587,  589,
 /*    80 */   591,  598,  600,   31,  -79,   31,   31,   31,   31,  257,
 /*    90 */   220,  407,  446,  480,  313,   31,   31,   31,   31,    2,
 /*   100 */  -173,  -63,   36,  411,  394,  112,  245,  464,  424,   90,
 /*   110 */   482,  487,  549,  250,  553,   45,  486,  537,  319,  384,
 /*   120 */   199,  438,  555,  404,  503,  -84,    8,   43,   48,   69,
 /*   130 */   166,   69,   69,  176,  234,  254,  295,  202,  273,  470,
 /*   140 */   329,  295,  476,  621,  634,  395,  672,  675,   69,  395,
 /*   150 */   676,  678,  651,  652,  657,  682,  689,   69,  693,   69,
 /*   160 */   695,   69,  697,  701,  679,  659,  655,  623,  624,  633,
 /*   170 */   635,  630,  685,  710,  708,  714,  715,  713,  696,  730,
 /*   180 */   731,  656,  660,  754,  756,  759,  752,  750,  751,  738,
 /*   190 */   739,  734,  744,  745,  725,  724,  727,  728,  729,  732,
 /*   200 */   704,  777,  722,  775,  733,  786,  735,  736,  741,  737,
 /*   210 */   773,  746,  753,  787,  770,  782,  784,  785,  781,  818,
 /*   220 */   827,  828,  779,  831,  788,  789,  790,  765,  768,  771,
 /*   230 */   836,  833,  837,  839,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   508,  777,  777,  739,  622,  777,  739,  777,  739,  777,
 /*    10 */   626,  777,  735,  739,  777,  777,  709,  777,  541,  749,
 /*    20 */   749,  657,  777,  777,  777,  777,  777,  777,  777,  658,
 /*    30 */   738,  734,  730,  732,  731,  659,  646,  655,  662,  638,
 /*    40 */   664,  665,  675,  676,  756,  757,  699,  715,  698,  777,
 /*    50 */   777,  777,  777,  777,  777,  777,  777,  777,  777,  777,
 /*    60 */   777,  777,  777,  777,  777,  777,  777,  777,  777,  777,
 /*    70 */   777,  777,  777,  777,  777,  777,  777,  777,  777,  777,
 /*    80 */   777,  777,  777,  701,  534,  700,  708,  702,  703,  595,
 /*    90 */   777,  777,  777,  777,  777,  704,  705,  716,  717,  777,
 /*   100 */   777,  762,  777,  777,  777,  508,  622,  777,  622,  777,
 /*   110 */   777,  777,  777,  777,  777,  777,  777,  777,  777,  777,
 /*   120 */   661,  777,  777,  616,  626,  777,  777,  586,  777,  777,
 /*   130 */   777,  777,  777,  777,  777,  777,  777,  762,  772,  777,
 /*   140 */   614,  777,  777,  543,  777,  624,  777,  777,  629,  630,
 /*   150 */   777,  777,  777,  777,  777,  777,  777,  524,  777,  605,
 /*   160 */   777,  669,  777,  777,  649,  614,  623,  777,  777,  777,
 /*   170 */   777,  733,  649,  649,  565,  649,  649,  568,  661,  777,
 /*   180 */   777,  775,  775,  513,  513,  513,  585,  532,  532,  597,
 /*   190 */   597,  582,  597,  597,  777,  661,  652,  654,  642,  656,
 /*   200 */   777,  631,  650,  777,  650,  631,  639,  641,  639,  641,
 /*   210 */   740,  650,  650,  777,  582,  597,  597,  597,  740,  522,
 /*   220 */   519,  631,  604,  631,  661,  656,  656,  677,  777,  677,
 /*   230 */   527,  551,  570,  570,  777,  777,  523,  777,  777,  777,
 /*   240 */   685,  777,  777,  777,  777,  777,  777,  777,  777,  777,
 /*   250 */   777,  777,  777,  777,  777,  777,  777,  528,  777,  777,
 /*   260 */   777,  777,  777,  777,  777,  690,  686,  777,  687,  777,
 /*   270 */   777,  777,  777,  777,  608,  777,  777,  777,  643,  777,
 /*   280 */   653,  777,  777,  777,  777,  777,  777,  777,  777,  777,
 /*   290 */   777,  777,  777,  777,  777,  777,  777,  777,  777,  777,
 /*   300 */   777,  777,  777,  777,  666,  777,  667,  777,  668,  753,
 /*   310 */   777,  777,  777,  777,  777,  777,  777,  509,  777,  502,
 /*   320 */   506,  504,  505,  511,  514,  512,  515,  516,  517,  529,
 /*   330 */   530,  533,  531,  525,  550,  538,  539,  540,  552,  559,
 /*   340 */   560,  598,  599,  600,  601,  750,  751,  752,  561,  580,
 /*   350 */   583,  584,  562,  647,  648,  563,  612,  613,  682,  606,
 /*   360 */   607,  611,  684,  688,  689,  691,  692,  693,  537,  544,
 /*   370 */   545,  548,  549,  745,  747,  746,  748,  547,  546,  694,
 /*   380 */   697,  706,  707,  713,  719,  723,  711,  712,  714,  718,
 /*   390 */   720,  721,  722,  609,  610,  726,  728,  729,  724,  736,
 /*   400 */   737,  632,  727,  710,  644,  536,  651,  645,  615,  625,
 /*   410 */   634,  635,  636,  637,  620,  621,  627,  640,  680,  681,
 /*   420 */   628,  617,  618,  619,  725,  683,  695,  696,  564,  571,
 /*   430 */   572,  573,  576,  577,  578,  579,  574,  575,  741,  742,
 /*   440 */   744,  743,  566,  567,  581,  553,  554,  555,  556,  690,
 /*   450 */   557,  558,  542,  535,  587,  590,  569,  591,  592,  593,
 /*   460 */   594,  596,  588,  589,  526,  518,  520,  521,  602,  633,
 /*   470 */   603,  660,  663,  672,  673,  674,  678,  679,  670,  671,
 /*   480 */   763,  764,  758,  759,  760,  761,  754,  755,  765,  766,
 /*   490 */   767,  768,  769,  776,  770,  773,  774,  771,  507,  510,
 /*   500 */   503,
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
  "TABLES",        "STATUS",        "error",         "input",       
  "cmdlist",       "ecmd",          "cmdx",          "cmd",         
  "explain",       "trans_opt",     "create_table",  "create_table_args",
  "temp",          "ifnotexists",   "nm",            "dbnm",        
  "columnlist",    "conslist_opt",  "table_opt",     "select",      
  "column",        "eq_or_null",    "columnid",      "type",        
  "carglist",      "id",            "ids",           "typetoken",   
  "typename",      "signed",        "plus_num",      "minus_num",   
  "carg",          "ccons",         "term",          "expr",        
  "onconf",        "sortorder",     "idxlist_opt",   "refargs",     
  "defer_subclause",  "autoinc",       "refarg",        "refact",      
  "init_deferred_pred_opt",  "conslist",      "tcons",         "idxlist",     
  "defer_subclause_opt",  "orconf",        "resolvetype",   "raisetype",   
  "ifexists",      "fullname",      "oneselect",     "multiselect_op",
  "distinct",      "selcollist",    "from",          "where_opt",   
  "groupby_opt",   "having_opt",    "orderby_opt",   "limit_opt",   
  "sclp",          "as",            "seltablist",    "stl_prefix",  
  "joinop",        "on_opt",        "using_opt",     "seltablist_paren",
  "joinop2",       "inscollist",    "sortlist",      "sortitem",    
  "collate",       "exprlist",      "setlist",       "insert_cmd",  
  "inscollist_opt",  "valueslist",    "itemlist",      "likeop",      
  "escape",        "between_op",    "between_elem",  "in_op",       
  "case_operand",  "case_exprlist",  "case_else",     "expritem",    
  "idxitem",       "plus_opt",      "number",        "variable_assignment_list",
  "scope_qualifier",  "user_var_name",  "show_databes",  "show_tables", 
  "show_table_status",  "full_keyword",  "from_db",       "show_table_status_pattern",
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
 /* 267 */ "show_databes ::= SHOW DATABASES|SCHEMAS",
 /* 268 */ "show_tables ::= SHOW full_keyword TABLES from_db",
 /* 269 */ "show_table_status ::= SHOW TABLE STATUS from_db show_table_status_pattern",
 /* 270 */ "full_keyword ::= JOIN_KW",
 /* 271 */ "full_keyword ::=",
 /* 272 */ "show_table_status_pattern ::= LIKE_KW STRING|ID",
 /* 273 */ "show_table_status_pattern ::= where_opt",
 /* 274 */ "from_db ::=",
 /* 275 */ "from_db ::= FROM|IN nm",
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
    case 163:
    case 198:
    case 215:
#line 391 "parse.y"
{sqlite3SelectDelete((yypminor->yy43));}
#line 1177 "parse.c"
      break;
    case 178:
    case 179:
    case 203:
    case 205:
    case 213:
    case 219:
    case 228:
    case 230:
    case 232:
    case 234:
    case 235:
#line 669 "parse.y"
{sqlite3ExprDelete((yypminor->yy450));}
#line 1192 "parse.c"
      break;
    case 182:
    case 191:
    case 201:
    case 204:
    case 206:
    case 208:
    case 218:
    case 221:
    case 222:
    case 226:
    case 233:
#line 913 "parse.y"
{sqlite3ExprListDelete((yypminor->yy242));}
#line 1207 "parse.c"
      break;
    case 197:
    case 202:
    case 210:
    case 211:
#line 519 "parse.y"
{sqlite3SrcListDelete((yypminor->yy419));}
#line 1215 "parse.c"
      break;
    case 207:
#line 580 "parse.y"
{
  sqlite3ExprDelete((yypminor->yy84).pLimit);
  sqlite3ExprDelete((yypminor->yy84).pOffset);
}
#line 1223 "parse.c"
      break;
    case 214:
    case 217:
    case 224:
#line 536 "parse.y"
{sqlite3IdListDelete((yypminor->yy352));}
#line 1230 "parse.c"
      break;
    case 225:
#line 640 "parse.y"
{sqlite3ValuesListDelete((yypminor->yy447));}
#line 1235 "parse.c"
      break;
    case 239:
#line 1129 "parse.y"
{ sqlite3ExprListDelete((yypminor->yy242)); }
#line 1240 "parse.c"
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
#line 1392 "parse.c"
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
  { 147, 1 },
  { 148, 2 },
  { 148, 1 },
  { 150, 1 },
  { 150, 3 },
  { 149, 1 },
  { 149, 3 },
  { 152, 0 },
  { 152, 1 },
  { 152, 3 },
  { 151, 2 },
  { 151, 2 },
  { 153, 0 },
  { 153, 1 },
  { 151, 2 },
  { 151, 2 },
  { 151, 2 },
  { 154, 6 },
  { 157, 0 },
  { 157, 3 },
  { 156, 1 },
  { 156, 0 },
  { 155, 5 },
  { 155, 2 },
  { 160, 3 },
  { 160, 1 },
  { 162, 0 },
  { 162, 2 },
  { 162, 4 },
  { 162, 6 },
  { 162, 5 },
  { 165, 0 },
  { 165, 1 },
  { 164, 3 },
  { 166, 1 },
  { 169, 1 },
  { 170, 1 },
  { 158, 1 },
  { 158, 1 },
  { 158, 1 },
  { 167, 0 },
  { 167, 1 },
  { 171, 1 },
  { 171, 4 },
  { 171, 6 },
  { 172, 1 },
  { 172, 2 },
  { 173, 1 },
  { 173, 1 },
  { 168, 2 },
  { 168, 0 },
  { 176, 3 },
  { 176, 1 },
  { 176, 2 },
  { 176, 4 },
  { 176, 3 },
  { 176, 3 },
  { 176, 2 },
  { 177, 1 },
  { 177, 2 },
  { 177, 3 },
  { 177, 4 },
  { 177, 2 },
  { 177, 4 },
  { 177, 4 },
  { 177, 1 },
  { 177, 2 },
  { 185, 0 },
  { 185, 1 },
  { 183, 0 },
  { 183, 2 },
  { 186, 2 },
  { 186, 3 },
  { 186, 3 },
  { 186, 3 },
  { 187, 2 },
  { 187, 2 },
  { 187, 1 },
  { 187, 1 },
  { 184, 3 },
  { 184, 2 },
  { 188, 0 },
  { 188, 2 },
  { 188, 2 },
  { 161, 0 },
  { 161, 2 },
  { 189, 3 },
  { 189, 2 },
  { 189, 1 },
  { 190, 2 },
  { 190, 7 },
  { 190, 5 },
  { 190, 5 },
  { 190, 10 },
  { 192, 0 },
  { 192, 1 },
  { 180, 0 },
  { 180, 3 },
  { 194, 1 },
  { 194, 1 },
  { 194, 1 },
  { 151, 4 },
  { 196, 2 },
  { 196, 0 },
  { 151, 1 },
  { 163, 1 },
  { 163, 3 },
  { 199, 1 },
  { 199, 2 },
  { 199, 1 },
  { 198, 9 },
  { 200, 1 },
  { 200, 1 },
  { 200, 0 },
  { 208, 2 },
  { 208, 0 },
  { 201, 3 },
  { 201, 2 },
  { 201, 4 },
  { 209, 2 },
  { 209, 1 },
  { 209, 0 },
  { 202, 0 },
  { 202, 2 },
  { 211, 2 },
  { 211, 0 },
  { 210, 6 },
  { 210, 7 },
  { 215, 1 },
  { 215, 1 },
  { 159, 0 },
  { 159, 2 },
  { 197, 2 },
  { 212, 1 },
  { 212, 2 },
  { 212, 3 },
  { 212, 4 },
  { 213, 2 },
  { 213, 0 },
  { 214, 4 },
  { 214, 0 },
  { 206, 0 },
  { 206, 3 },
  { 218, 5 },
  { 218, 3 },
  { 219, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 0 },
  { 220, 0 },
  { 220, 2 },
  { 204, 0 },
  { 204, 3 },
  { 205, 0 },
  { 205, 2 },
  { 207, 0 },
  { 207, 2 },
  { 207, 4 },
  { 207, 4 },
  { 151, 5 },
  { 203, 0 },
  { 203, 2 },
  { 151, 6 },
  { 222, 5 },
  { 222, 3 },
  { 151, 6 },
  { 151, 6 },
  { 151, 5 },
  { 151, 5 },
  { 223, 1 },
  { 223, 1 },
  { 225, 5 },
  { 225, 3 },
  { 225, 2 },
  { 226, 3 },
  { 226, 1 },
  { 224, 0 },
  { 224, 2 },
  { 224, 3 },
  { 217, 3 },
  { 217, 1 },
  { 179, 1 },
  { 179, 3 },
  { 178, 1 },
  { 179, 1 },
  { 179, 1 },
  { 179, 3 },
  { 179, 5 },
  { 178, 1 },
  { 178, 1 },
  { 179, 1 },
  { 179, 1 },
  { 179, 1 },
  { 179, 6 },
  { 179, 5 },
  { 179, 4 },
  { 178, 1 },
  { 179, 3 },
  { 179, 3 },
  { 179, 3 },
  { 179, 3 },
  { 179, 3 },
  { 179, 3 },
  { 179, 3 },
  { 179, 3 },
  { 227, 1 },
  { 227, 2 },
  { 228, 2 },
  { 228, 0 },
  { 179, 4 },
  { 179, 2 },
  { 179, 3 },
  { 179, 3 },
  { 179, 4 },
  { 179, 2 },
  { 179, 2 },
  { 179, 2 },
  { 229, 1 },
  { 229, 2 },
  { 230, 1 },
  { 179, 5 },
  { 231, 1 },
  { 231, 2 },
  { 179, 5 },
  { 179, 3 },
  { 179, 5 },
  { 179, 4 },
  { 179, 4 },
  { 179, 5 },
  { 233, 5 },
  { 233, 4 },
  { 234, 2 },
  { 234, 0 },
  { 232, 1 },
  { 232, 0 },
  { 221, 3 },
  { 221, 1 },
  { 235, 1 },
  { 235, 0 },
  { 182, 0 },
  { 182, 3 },
  { 191, 5 },
  { 191, 3 },
  { 236, 1 },
  { 174, 2 },
  { 175, 2 },
  { 238, 1 },
  { 237, 1 },
  { 237, 0 },
  { 195, 1 },
  { 195, 1 },
  { 195, 1 },
  { 151, 2 },
  { 151, 3 },
  { 151, 4 },
  { 239, 6 },
  { 239, 4 },
  { 240, 1 },
  { 240, 1 },
  { 240, 1 },
  { 240, 2 },
  { 240, 0 },
  { 241, 1 },
  { 241, 1 },
  { 151, 1 },
  { 151, 1 },
  { 151, 1 },
  { 242, 2 },
  { 243, 4 },
  { 244, 5 },
  { 245, 1 },
  { 245, 0 },
  { 247, 2 },
  { 247, 1 },
  { 246, 0 },
  { 246, 2 },
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
#line 1747 "parse.c"
        break;
      case 7:
#line 102 "parse.y"
{ sqlite3BeginParse(pParse, 0); }
#line 1752 "parse.c"
        break;
      case 8:
#line 104 "parse.y"
{ sqlite3BeginParse(pParse, 1); }
#line 1757 "parse.c"
        break;
      case 9:
#line 105 "parse.y"
{ sqlite3BeginParse(pParse, 2); }
#line 1762 "parse.c"
        break;
      case 10:
#line 112 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_BEGIN);}
#line 1767 "parse.c"
        break;
      case 11:
#line 113 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_START);}
#line 1772 "parse.c"
        break;
      case 14:
#line 124 "parse.y"
{sqlite3CommitTransaction(pParse);}
#line 1777 "parse.c"
        break;
      case 15:
#line 126 "parse.y"
{sqlite3RollbackTransaction(pParse);}
#line 1782 "parse.c"
        break;
      case 17:
#line 131 "parse.y"
{
   sqlite3StartTable(pParse, 0, 0, 0, 0, 0);
}
#line 1789 "parse.c"
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
{yygotominor.yy316 = 0;}
#line 1804 "parse.c"
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
{yygotominor.yy316 = 1;}
#line 1816 "parse.c"
        break;
      case 22:
#line 143 "parse.y"
{
  //sqlite3EndTable(pParse,&X,&Y,0);
}
#line 1823 "parse.c"
        break;
      case 23:
#line 146 "parse.y"
{
  sqlite3EndTable(pParse,0,0,0);
  //sqlite3SelectDelete(S);
  yy_destructor(163,&yymsp[0].minor);
}
#line 1832 "parse.c"
        break;
      case 33:
#line 168 "parse.y"
{
  //A.z = X.z;
  //A.n = (pParse->sLastToken.z-X.z) + pParse->sLastToken.n;
}
#line 1840 "parse.c"
        break;
      case 34:
#line 172 "parse.y"
{
  //sqlite3AddColumn(pParse,&X);
  //A = X;
}
#line 1848 "parse.c"
        break;
      case 35:
      case 36:
      case 37:
      case 38:
      case 39:
      case 246:
#line 182 "parse.y"
{yygotominor.yy178 = yymsp[0].minor.yy0;}
#line 1858 "parse.c"
        break;
      case 41:
#line 241 "parse.y"
{ /*sqlite3AddColumnType(pParse,&X);*/ }
#line 1863 "parse.c"
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
{yygotominor.yy178 = yymsp[0].minor.yy178;}
#line 1876 "parse.c"
        break;
      case 43:
#line 243 "parse.y"
{
  yygotominor.yy178.z = yymsp[-3].minor.yy178.z;
  yygotominor.yy178.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-3].minor.yy178.z;
}
#line 1884 "parse.c"
        break;
      case 44:
#line 247 "parse.y"
{
  yygotominor.yy178.z = yymsp[-5].minor.yy178.z;
  yygotominor.yy178.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-5].minor.yy178.z;
}
#line 1892 "parse.c"
        break;
      case 46:
#line 253 "parse.y"
{yygotominor.yy178.z=yymsp[-1].minor.yy178.z; yygotominor.yy178.n=yymsp[0].minor.yy178.n+(yymsp[0].minor.yy178.z-yymsp[-1].minor.yy178.z);}
#line 1897 "parse.c"
        break;
      case 47:
#line 255 "parse.y"
{ yygotominor.yy316 = atoi((char*)yymsp[0].minor.yy178.z); }
#line 1902 "parse.c"
        break;
      case 48:
#line 256 "parse.y"
{ yygotominor.yy316 = -atoi((char*)yymsp[0].minor.yy178.z); }
#line 1907 "parse.c"
        break;
      case 53:
#line 265 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/   yy_destructor(178,&yymsp[0].minor);
}
#line 1913 "parse.c"
        break;
      case 54:
#line 266 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/ }
#line 1918 "parse.c"
        break;
      case 55:
#line 267 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/  yy_destructor(178,&yymsp[0].minor);
}
#line 1924 "parse.c"
        break;
      case 56:
#line 268 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_UMINUS, X, 0, 0);
  //sqlite3AddDefaultValue(pParse,p);
  yy_destructor(178,&yymsp[0].minor);
}
#line 1933 "parse.c"
        break;
      case 57:
#line 272 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_STRING, 0, 0, &X);
  //sqlite3AddDefaultValue(pParse,p);
}
#line 1941 "parse.c"
        break;
      case 60:
#line 282 "parse.y"
{/*sqlite3AddNotNull(pParse, R);*/}
#line 1946 "parse.c"
        break;
      case 61:
#line 284 "parse.y"
{/*sqlite3AddPrimaryKey(pParse,0,R,I,Z);*/}
#line 1951 "parse.c"
        break;
      case 62:
#line 285 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,0,R,0,0,0,0);*/}
#line 1956 "parse.c"
        break;
      case 63:
#line 286 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,X);*/  sqlite3ExprDelete(yymsp[-1].minor.yy450); }
#line 1961 "parse.c"
        break;
      case 64:
#line 288 "parse.y"
{/*sqlite3CreateForeignKey(pParse,0,&T,TA,R);*/ sqlite3ExprListDelete(yymsp[-1].minor.yy242); }
#line 1966 "parse.c"
        break;
      case 65:
#line 289 "parse.y"
{/*sqlite3DeferForeignKey(pParse,D);*/}
#line 1971 "parse.c"
        break;
      case 66:
#line 290 "parse.y"
{/*sqlite3AddCollateType(pParse, (char*)C.z, C.n);*/}
#line 1976 "parse.c"
        break;
      case 69:
#line 303 "parse.y"
{ yygotominor.yy316 = OE_Restrict * 0x010101; }
#line 1981 "parse.c"
        break;
      case 70:
#line 304 "parse.y"
{ yygotominor.yy316 = (yymsp[-1].minor.yy316 & yymsp[0].minor.yy207.mask) | yymsp[0].minor.yy207.value; }
#line 1986 "parse.c"
        break;
      case 71:
#line 306 "parse.y"
{ yygotominor.yy207.value = 0;     yygotominor.yy207.mask = 0x000000; }
#line 1991 "parse.c"
        break;
      case 72:
#line 307 "parse.y"
{ yygotominor.yy207.value = yymsp[0].minor.yy316;     yygotominor.yy207.mask = 0x0000ff; }
#line 1996 "parse.c"
        break;
      case 73:
#line 308 "parse.y"
{ yygotominor.yy207.value = yymsp[0].minor.yy316<<8;  yygotominor.yy207.mask = 0x00ff00; }
#line 2001 "parse.c"
        break;
      case 74:
#line 309 "parse.y"
{ yygotominor.yy207.value = yymsp[0].minor.yy316<<16; yygotominor.yy207.mask = 0xff0000; }
#line 2006 "parse.c"
        break;
      case 75:
#line 311 "parse.y"
{ yygotominor.yy316 = OE_SetNull; }
#line 2011 "parse.c"
        break;
      case 76:
#line 312 "parse.y"
{ yygotominor.yy316 = OE_SetDflt; }
#line 2016 "parse.c"
        break;
      case 77:
#line 313 "parse.y"
{ yygotominor.yy316 = OE_Cascade; }
#line 2021 "parse.c"
        break;
      case 78:
#line 314 "parse.y"
{ yygotominor.yy316 = OE_Restrict; }
#line 2026 "parse.c"
        break;
      case 79:
      case 80:
      case 95:
      case 97:
      case 98:
#line 316 "parse.y"
{yygotominor.yy316 = yymsp[0].minor.yy316;}
#line 2035 "parse.c"
        break;
      case 90:
#line 335 "parse.y"
{ sqlite3ExprListDelete(yymsp[-3].minor.yy242); }
#line 2040 "parse.c"
        break;
      case 91:
#line 337 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,yymsp[-2].minor.yy242,R,0,0,0,0);*/ sqlite3ExprListDelete(yymsp[-2].minor.yy242);}
#line 2045 "parse.c"
        break;
      case 92:
#line 338 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,yymsp[-2].minor.yy450);*/ sqlite3ExprDelete(yymsp[-2].minor.yy450);}
#line 2050 "parse.c"
        break;
      case 93:
#line 340 "parse.y"
{ 
        sqlite3ExprListDelete(yymsp[-6].minor.yy242);
        sqlite3ExprListDelete(yymsp[-2].minor.yy242);
 }
#line 2058 "parse.c"
        break;
      case 96:
#line 355 "parse.y"
{yygotominor.yy316 = OE_Default;}
#line 2063 "parse.c"
        break;
      case 99:
#line 360 "parse.y"
{yygotominor.yy316 = OE_Ignore;}
#line 2068 "parse.c"
        break;
      case 100:
      case 170:
#line 361 "parse.y"
{yygotominor.yy316 = OE_Replace;}
#line 2074 "parse.c"
        break;
      case 101:
#line 365 "parse.y"
{
  sqlite3DropTable(pParse, yymsp[0].minor.yy419, 0, yymsp[-1].minor.yy316);
}
#line 2081 "parse.c"
        break;
      case 104:
#line 385 "parse.y"
{
  sqlite3Select(pParse, yymsp[0].minor.yy43, SRT_Callback, 0, 0, 0, 0, 0);
  // sqlite3SelectDelete(yymsp[0].minor.yy43);
}
#line 2089 "parse.c"
        break;
      case 105:
      case 128:
#line 395 "parse.y"
{yygotominor.yy43 = yymsp[0].minor.yy43;}
#line 2095 "parse.c"
        break;
      case 106:
#line 397 "parse.y"
{
  if( yymsp[0].minor.yy43 ){
    yymsp[0].minor.yy43->op = yymsp[-1].minor.yy316;
    yymsp[0].minor.yy43->pPrior = yymsp[-2].minor.yy43;
  }
  yygotominor.yy43 = yymsp[0].minor.yy43;
}
#line 2106 "parse.c"
        break;
      case 107:
      case 109:
#line 405 "parse.y"
{yygotominor.yy316 = yymsp[0].major;}
#line 2112 "parse.c"
        break;
      case 108:
#line 406 "parse.y"
{yygotominor.yy316 = TK_ALL;}
#line 2117 "parse.c"
        break;
      case 110:
#line 410 "parse.y"
{
  yygotominor.yy43 = sqlite3SelectNew(yymsp[-6].minor.yy242,yymsp[-5].minor.yy419,yymsp[-4].minor.yy450,yymsp[-3].minor.yy242,yymsp[-2].minor.yy450,yymsp[-1].minor.yy242,yymsp[-7].minor.yy316,yymsp[0].minor.yy84.pLimit,yymsp[0].minor.yy84.pOffset);
}
#line 2124 "parse.c"
        break;
      case 114:
      case 240:
#line 431 "parse.y"
{yygotominor.yy242 = yymsp[-1].minor.yy242;}
#line 2130 "parse.c"
        break;
      case 115:
      case 141:
      case 151:
      case 239:
#line 432 "parse.y"
{yygotominor.yy242 = 0;}
#line 2138 "parse.c"
        break;
      case 116:
#line 433 "parse.y"
{
   yygotominor.yy242 = sqlite3ExprListAppend(yymsp[-2].minor.yy242,yymsp[-1].minor.yy450,yymsp[0].minor.yy178.n?&yymsp[0].minor.yy178:0);
}
#line 2145 "parse.c"
        break;
      case 117:
#line 436 "parse.y"
{
  yygotominor.yy242 = sqlite3ExprListAppend(yymsp[-1].minor.yy242, sqlite3Expr(TK_ALL, 0, 0, 0), 0);
}
#line 2152 "parse.c"
        break;
      case 118:
#line 439 "parse.y"
{
  Expr *pRight = sqlite3Expr(TK_ALL, 0, 0, 0);
  Expr *pLeft = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy178);
  yygotominor.yy242 = sqlite3ExprListAppend(yymsp[-3].minor.yy242, sqlite3Expr(TK_DOT, pLeft, pRight, 0), 0);
}
#line 2161 "parse.c"
        break;
      case 121:
#line 451 "parse.y"
{yygotominor.yy178.n = 0;}
#line 2166 "parse.c"
        break;
      case 122:
#line 463 "parse.y"
{yygotominor.yy419 = sqliteMalloc(sizeof(*yygotominor.yy419));}
#line 2171 "parse.c"
        break;
      case 123:
#line 464 "parse.y"
{yygotominor.yy419 = yymsp[0].minor.yy419;}
#line 2176 "parse.c"
        break;
      case 124:
#line 469 "parse.y"
{
   yygotominor.yy419 = yymsp[-1].minor.yy419;
   if( yygotominor.yy419 && yygotominor.yy419->nSrc>0 ) yygotominor.yy419->a[yygotominor.yy419->nSrc-1].jointype = yymsp[0].minor.yy316;
}
#line 2184 "parse.c"
        break;
      case 125:
#line 473 "parse.y"
{yygotominor.yy419 = 0;}
#line 2189 "parse.c"
        break;
      case 126:
#line 474 "parse.y"
{
  yygotominor.yy419 = sqlite3SrcListAppend(yymsp[-5].minor.yy419,&yymsp[-4].minor.yy178,&yymsp[-3].minor.yy178);
  if( yymsp[-2].minor.yy178.n ) sqlite3SrcListAddAlias(yygotominor.yy419,&yymsp[-2].minor.yy178);
  if( yymsp[-1].minor.yy450 ){
    if( yygotominor.yy419 && yygotominor.yy419->nSrc>1 ){ yygotominor.yy419->a[yygotominor.yy419->nSrc-2].pOn = yymsp[-1].minor.yy450; }
    else { sqlite3ExprDelete(yymsp[-1].minor.yy450); }
  }
  if( yymsp[0].minor.yy352 ){
    if( yygotominor.yy419 && yygotominor.yy419->nSrc>1 ){ yygotominor.yy419->a[yygotominor.yy419->nSrc-2].pUsing = yymsp[0].minor.yy352; }
    else { sqlite3IdListDelete(yymsp[0].minor.yy352); }
  }
}
#line 2205 "parse.c"
        break;
      case 127:
#line 488 "parse.y"
{
    yygotominor.yy419 = sqlite3SrcListAppend(yymsp[-6].minor.yy419,0,0);
    yygotominor.yy419->a[yygotominor.yy419->nSrc-1].pSelect = yymsp[-4].minor.yy43;
    if( yymsp[-2].minor.yy178.n ) sqlite3SrcListAddAlias(yygotominor.yy419,&yymsp[-2].minor.yy178);
    if( yymsp[-1].minor.yy450 ){
      if( yygotominor.yy419 && yygotominor.yy419->nSrc>1 ){ yygotominor.yy419->a[yygotominor.yy419->nSrc-2].pOn = yymsp[-1].minor.yy450; }
      else { sqlite3ExprDelete(yymsp[-1].minor.yy450); }
    }
    if( yymsp[0].minor.yy352 ){
      if( yygotominor.yy419 && yygotominor.yy419->nSrc>1 ){ yygotominor.yy419->a[yygotominor.yy419->nSrc-2].pUsing = yymsp[0].minor.yy352; }
      else { sqlite3IdListDelete(yymsp[0].minor.yy352); }
    }
  }
#line 2222 "parse.c"
        break;
      case 129:
#line 509 "parse.y"
{
     yygotominor.yy43 = sqlite3SelectNew(0,yymsp[0].minor.yy419,0,0,0,0,0,0,0);
  }
#line 2229 "parse.c"
        break;
      case 130:
#line 515 "parse.y"
{yygotominor.yy178.z=0; yygotominor.yy178.n=0;}
#line 2234 "parse.c"
        break;
      case 132:
#line 520 "parse.y"
{yygotominor.yy419 = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy178,&yymsp[0].minor.yy178);}
#line 2239 "parse.c"
        break;
      case 133:
#line 524 "parse.y"
{ yygotominor.yy316 = JT_INNER; }
#line 2244 "parse.c"
        break;
      case 134:
#line 525 "parse.y"
{ yygotominor.yy316 = sqlite3JoinType(pParse,&yymsp[-1].minor.yy0,0,0); }
#line 2249 "parse.c"
        break;
      case 135:
#line 526 "parse.y"
{ yygotominor.yy316 = sqlite3JoinType(pParse,&yymsp[-2].minor.yy0,&yymsp[-1].minor.yy178,0); }
#line 2254 "parse.c"
        break;
      case 136:
#line 528 "parse.y"
{ yygotominor.yy316 = sqlite3JoinType(pParse,&yymsp[-3].minor.yy0,&yymsp[-2].minor.yy178,&yymsp[-1].minor.yy178); }
#line 2259 "parse.c"
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
{yygotominor.yy450 = yymsp[0].minor.yy450;}
#line 2272 "parse.c"
        break;
      case 138:
      case 153:
      case 160:
      case 208:
      case 232:
      case 234:
      case 238:
#line 533 "parse.y"
{yygotominor.yy450 = 0;}
#line 2283 "parse.c"
        break;
      case 139:
      case 178:
#line 537 "parse.y"
{yygotominor.yy352 = yymsp[-1].minor.yy352;}
#line 2289 "parse.c"
        break;
      case 140:
      case 176:
      case 177:
#line 538 "parse.y"
{yygotominor.yy352 = 0;}
#line 2296 "parse.c"
        break;
      case 142:
      case 152:
#line 549 "parse.y"
{yygotominor.yy242 = yymsp[0].minor.yy242;}
#line 2302 "parse.c"
        break;
      case 143:
#line 550 "parse.y"
{
  yygotominor.yy242 = sqlite3ExprListAppend(yymsp[-4].minor.yy242,yymsp[-2].minor.yy450,yymsp[-1].minor.yy178.n>0?&yymsp[-1].minor.yy178:0);
  if( yygotominor.yy242 ) yygotominor.yy242->a[yygotominor.yy242->nExpr-1].sortOrder = yymsp[0].minor.yy316;
}
#line 2310 "parse.c"
        break;
      case 144:
#line 554 "parse.y"
{
  yygotominor.yy242 = sqlite3ExprListAppend(0,yymsp[-2].minor.yy450,yymsp[-1].minor.yy178.n>0?&yymsp[-1].minor.yy178:0);
  if( yygotominor.yy242 && yygotominor.yy242->a ) yygotominor.yy242->a[0].sortOrder = yymsp[0].minor.yy316;
}
#line 2318 "parse.c"
        break;
      case 146:
      case 148:
#line 563 "parse.y"
{yygotominor.yy316 = SQLITE_SO_ASC;}
#line 2324 "parse.c"
        break;
      case 147:
#line 564 "parse.y"
{yygotominor.yy316 = SQLITE_SO_DESC;}
#line 2329 "parse.c"
        break;
      case 149:
#line 566 "parse.y"
{yygotominor.yy178.z = 0; yygotominor.yy178.n = 0;}
#line 2334 "parse.c"
        break;
      case 155:
#line 584 "parse.y"
{yygotominor.yy84.pLimit = 0; yygotominor.yy84.pOffset = 0;}
#line 2339 "parse.c"
        break;
      case 156:
#line 585 "parse.y"
{yygotominor.yy84.pLimit = yymsp[0].minor.yy450; yygotominor.yy84.pOffset = 0;}
#line 2344 "parse.c"
        break;
      case 157:
#line 587 "parse.y"
{yygotominor.yy84.pLimit = yymsp[-2].minor.yy450; yygotominor.yy84.pOffset = yymsp[0].minor.yy450;}
#line 2349 "parse.c"
        break;
      case 158:
#line 589 "parse.y"
{yygotominor.yy84.pOffset = yymsp[-2].minor.yy450; yygotominor.yy84.pLimit = yymsp[0].minor.yy450;}
#line 2354 "parse.c"
        break;
      case 159:
#line 593 "parse.y"
{sqlite3DeleteFrom(pParse,yymsp[-2].minor.yy419,yymsp[-1].minor.yy450, yymsp[0].minor.yy84.pLimit, yymsp[0].minor.yy84.pOffset);}
#line 2359 "parse.c"
        break;
      case 162:
#line 605 "parse.y"
{sqlite3Update(pParse,yymsp[-4].minor.yy419,yymsp[-2].minor.yy242,yymsp[-1].minor.yy450,OE_Default, yymsp[0].minor.yy84.pLimit, yymsp[0].minor.yy84.pOffset);}
#line 2364 "parse.c"
        break;
      case 163:
#line 611 "parse.y"
{yygotominor.yy242 = sqlite3ExprListAppend(yymsp[-4].minor.yy242,yymsp[0].minor.yy450,&yymsp[-2].minor.yy178);}
#line 2369 "parse.c"
        break;
      case 164:
#line 612 "parse.y"
{yygotominor.yy242 = sqlite3ExprListAppend(0,yymsp[0].minor.yy450,&yymsp[-2].minor.yy178);}
#line 2374 "parse.c"
        break;
      case 165:
#line 621 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy419, 0, yymsp[0].minor.yy447, 0, yymsp[-2].minor.yy352, yymsp[-5].minor.yy316);}
#line 2379 "parse.c"
        break;
      case 166:
#line 625 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy419, yymsp[0].minor.yy242, 0, 0, yymsp[-2].minor.yy352, yymsp[-5].minor.yy316);}
#line 2384 "parse.c"
        break;
      case 167:
#line 629 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy419, yymsp[0].minor.yy242, 0, 0, yymsp[-2].minor.yy352, yymsp[-4].minor.yy316);}
#line 2389 "parse.c"
        break;
      case 168:
#line 632 "parse.y"
{sqlite3Insert(pParse, yymsp[-2].minor.yy419, 0, 0, yymsp[0].minor.yy43, yymsp[-1].minor.yy352, yymsp[-4].minor.yy316);}
#line 2394 "parse.c"
        break;
      case 169:
#line 636 "parse.y"
{ yygotominor.yy316 = OE_Default; }
#line 2399 "parse.c"
        break;
      case 171:
#line 642 "parse.y"
{ yygotominor.yy447 = sqlite3ValuesListAppend(yymsp[-4].minor.yy447, yymsp[-1].minor.yy242);}
#line 2404 "parse.c"
        break;
      case 172:
#line 643 "parse.y"
{ yygotominor.yy447 = sqlite3ValuesListAppend(0, yymsp[-1].minor.yy242); }
#line 2409 "parse.c"
        break;
      case 173:
#line 644 "parse.y"
{ yygotominor.yy447 = 0; }
#line 2414 "parse.c"
        break;
      case 174:
      case 235:
#line 649 "parse.y"
{yygotominor.yy242 = sqlite3ExprListAppend(yymsp[-2].minor.yy242,yymsp[0].minor.yy450,0);}
#line 2420 "parse.c"
        break;
      case 175:
      case 236:
#line 650 "parse.y"
{yygotominor.yy242 = sqlite3ExprListAppend(0,yymsp[0].minor.yy450,0);}
#line 2426 "parse.c"
        break;
      case 179:
#line 660 "parse.y"
{yygotominor.yy352 = sqlite3IdListAppend(yymsp[-2].minor.yy352,&yymsp[0].minor.yy178);}
#line 2431 "parse.c"
        break;
      case 180:
#line 661 "parse.y"
{yygotominor.yy352 = sqlite3IdListAppend(0,&yymsp[0].minor.yy178);}
#line 2436 "parse.c"
        break;
      case 182:
#line 672 "parse.y"
{yygotominor.yy450 = yymsp[-1].minor.yy450; sqlite3ExprSpan(yygotominor.yy450,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0); }
#line 2441 "parse.c"
        break;
      case 183:
      case 188:
      case 189:
#line 673 "parse.y"
{yygotominor.yy450 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0);}
#line 2448 "parse.c"
        break;
      case 184:
      case 185:
#line 674 "parse.y"
{yygotominor.yy450 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy0);}
#line 2454 "parse.c"
        break;
      case 186:
#line 676 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy178);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy178);
  yygotominor.yy450 = sqlite3Expr(TK_DOT, temp1, temp2, 0);
}
#line 2463 "parse.c"
        break;
      case 187:
#line 681 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-4].minor.yy178);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy178);
  Expr *temp3 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy178);
  Expr *temp4 = sqlite3Expr(TK_DOT, temp2, temp3, 0);
  yygotominor.yy450 = sqlite3Expr(TK_DOT, temp1, temp4, 0);
}
#line 2474 "parse.c"
        break;
      case 190:
#line 690 "parse.y"
{yygotominor.yy450 = sqlite3RegisterExpr(pParse, &yymsp[0].minor.yy0);}
#line 2479 "parse.c"
        break;
      case 191:
      case 192:
#line 691 "parse.y"
{
  Token *pToken = &yymsp[0].minor.yy0;
  Expr *pExpr = yygotominor.yy450 = sqlite3Expr(TK_VARIABLE, 0, 0, pToken);
  //sqlite3ExprAssignVarNumber(pParse, pExpr);
}
#line 2489 "parse.c"
        break;
      case 193:
#line 702 "parse.y"
{
  yygotominor.yy450 = sqlite3Expr(TK_CAST, yymsp[-3].minor.yy450, 0, &yymsp[-1].minor.yy178);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-5].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2497 "parse.c"
        break;
      case 194:
#line 707 "parse.y"
{
  yygotominor.yy450 = sqlite3ExprFunction(yymsp[-1].minor.yy242, &yymsp[-4].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-4].minor.yy0,&yymsp[0].minor.yy0);
  if( yymsp[-2].minor.yy316 && yygotominor.yy450 ){
    yygotominor.yy450->flags |= EP_Distinct;
  }
}
#line 2508 "parse.c"
        break;
      case 195:
#line 714 "parse.y"
{
  yygotominor.yy450 = sqlite3ExprFunction(0, &yymsp[-3].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2516 "parse.c"
        break;
      case 196:
#line 718 "parse.y"
{
  /* The CURRENT_TIME, CURRENT_DATE, and CURRENT_TIMESTAMP values are
  ** treated as functions that return constants */
  yygotominor.yy450 = sqlite3ExprFunction(0,&yymsp[0].minor.yy0);
  if( yygotominor.yy450 ) yygotominor.yy450->op = TK_CONST_FUNC;  
}
#line 2526 "parse.c"
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
{yygotominor.yy450 = sqlite3Expr(yymsp[-1].major, yymsp[-2].minor.yy450, yymsp[0].minor.yy450, 0);}
#line 2538 "parse.c"
        break;
      case 205:
#line 734 "parse.y"
{yygotominor.yy86.eOperator = yymsp[0].minor.yy0; yygotominor.yy86.not = 0;}
#line 2543 "parse.c"
        break;
      case 206:
#line 735 "parse.y"
{yygotominor.yy86.eOperator = yymsp[0].minor.yy0; yygotominor.yy86.not = 1;}
#line 2548 "parse.c"
        break;
      case 209:
#line 740 "parse.y"
{
  ExprList *pList;
  pList = sqlite3ExprListAppend(0, yymsp[-3].minor.yy450, 0);
  pList = sqlite3ExprListAppend(pList, yymsp[-1].minor.yy450, 0);
  if( yymsp[0].minor.yy450 ){
    pList = sqlite3ExprListAppend(pList, yymsp[0].minor.yy450, 0);
  }
  //yygotominor.yy450 = sqlite3ExprFunction(pList, &yymsp[-2].minor.yy86.eOperator);
  yygotominor.yy450 = sqlite3ExprLikeOp(pList, &yymsp[-2].minor.yy86.eOperator);
  if( yymsp[-2].minor.yy86.not ) yygotominor.yy450 = sqlite3Expr(TK_NOT, yygotominor.yy450, 0, 0);
  sqlite3ExprSpan(yygotominor.yy450, &yymsp[-3].minor.yy450->span, &yymsp[-1].minor.yy450->span);
}
#line 2564 "parse.c"
        break;
      case 210:
#line 753 "parse.y"
{
  yygotominor.yy450 = sqlite3Expr(yymsp[0].major, yymsp[-1].minor.yy450, 0, 0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-1].minor.yy450->span,&yymsp[0].minor.yy0);
}
#line 2572 "parse.c"
        break;
      case 211:
#line 757 "parse.y"
{
  yygotominor.yy450 = sqlite3Expr(TK_ISNULL, yymsp[-2].minor.yy450, 0, 0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-2].minor.yy450->span,&yymsp[0].minor.yy0);
}
#line 2580 "parse.c"
        break;
      case 212:
#line 761 "parse.y"
{
  yygotominor.yy450 = sqlite3Expr(TK_NOTNULL, yymsp[-2].minor.yy450, 0, 0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-2].minor.yy450->span,&yymsp[0].minor.yy0);
}
#line 2588 "parse.c"
        break;
      case 213:
#line 765 "parse.y"
{
  yygotominor.yy450 = sqlite3Expr(TK_NOTNULL, yymsp[-3].minor.yy450, 0, 0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-3].minor.yy450->span,&yymsp[0].minor.yy0);
}
#line 2596 "parse.c"
        break;
      case 214:
#line 769 "parse.y"
{
  yygotominor.yy450 = sqlite3Expr(yymsp[-1].major, yymsp[0].minor.yy450, 0, 0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy450->span);
}
#line 2604 "parse.c"
        break;
      case 215:
#line 773 "parse.y"
{
  yygotominor.yy450 = sqlite3Expr(TK_UMINUS, yymsp[0].minor.yy450, 0, 0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy450->span);
}
#line 2612 "parse.c"
        break;
      case 216:
#line 777 "parse.y"
{
  yygotominor.yy450 = sqlite3Expr(TK_UPLUS, yymsp[0].minor.yy450, 0, 0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy450->span);
}
#line 2620 "parse.c"
        break;
      case 219:
#line 788 "parse.y"
{ yygotominor.yy450 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0); }
#line 2625 "parse.c"
        break;
      case 220:
#line 791 "parse.y"
{
  ExprList *pList = sqlite3ExprListAppend(0, yymsp[-2].minor.yy450, 0);
  pList = sqlite3ExprListAppend(pList, yymsp[0].minor.yy450, 0);
  yygotominor.yy450 = sqlite3Expr(TK_BETWEEN, yymsp[-4].minor.yy450, 0, 0);
  if( yygotominor.yy450 ){
    yygotominor.yy450->pList = pList;
  }else{
    sqlite3ExprListDelete(pList);
  } 
  if( yymsp[-3].minor.yy316 ) yygotominor.yy450 = sqlite3Expr(TK_NOT, yygotominor.yy450, 0, 0);
  sqlite3ExprSpan(yygotominor.yy450,&yymsp[-4].minor.yy450->span,&yymsp[0].minor.yy450->span);
}
#line 2641 "parse.c"
        break;
      case 223:
#line 807 "parse.y"
{
    yygotominor.yy450 = sqlite3Expr(TK_IN, yymsp[-4].minor.yy450, 0, 0);
    if( yygotominor.yy450 ){
      yygotominor.yy450->pList = yymsp[-1].minor.yy242;
    }else{
      sqlite3ExprListDelete(yymsp[-1].minor.yy242);
    }
    if( yymsp[-3].minor.yy316 ) yygotominor.yy450 = sqlite3Expr(TK_NOT, yygotominor.yy450, 0, 0);
    sqlite3ExprSpan(yygotominor.yy450,&yymsp[-4].minor.yy450->span,&yymsp[0].minor.yy0);
  }
#line 2655 "parse.c"
        break;
      case 224:
#line 817 "parse.y"
{
    yygotominor.yy450 = sqlite3Expr(TK_SELECT, 0, 0, 0);
    if( yygotominor.yy450 ){
      yygotominor.yy450->pSelect = yymsp[-1].minor.yy43;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy43);
    }
    sqlite3ExprSpan(yygotominor.yy450,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0);
  }
#line 2668 "parse.c"
        break;
      case 225:
#line 826 "parse.y"
{
    yygotominor.yy450 = sqlite3Expr(TK_IN, yymsp[-4].minor.yy450, 0, 0);
    if( yygotominor.yy450 ){
      yygotominor.yy450->pSelect = yymsp[-1].minor.yy43;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy43);
    }
    if( yymsp[-3].minor.yy316 ) yygotominor.yy450 = sqlite3Expr(TK_NOT, yygotominor.yy450, 0, 0);
    sqlite3ExprSpan(yygotominor.yy450,&yymsp[-4].minor.yy450->span,&yymsp[0].minor.yy0);
  }
#line 2682 "parse.c"
        break;
      case 226:
#line 836 "parse.y"
{
    SrcList *pSrc = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy178,&yymsp[0].minor.yy178);
    yygotominor.yy450 = sqlite3Expr(TK_IN, yymsp[-3].minor.yy450, 0, 0);
    if( yygotominor.yy450 ){
      yygotominor.yy450->pSelect = sqlite3SelectNew(0,pSrc,0,0,0,0,0,0,0);
    }else{
      sqlite3SrcListDelete(pSrc);
    }
    if( yymsp[-2].minor.yy316 ) yygotominor.yy450 = sqlite3Expr(TK_NOT, yygotominor.yy450, 0, 0);
    sqlite3ExprSpan(yygotominor.yy450,&yymsp[-3].minor.yy450->span,yymsp[0].minor.yy178.z?&yymsp[0].minor.yy178:&yymsp[-1].minor.yy178);
  }
#line 2697 "parse.c"
        break;
      case 227:
#line 847 "parse.y"
{
    Expr *p = yygotominor.yy450 = sqlite3Expr(TK_EXISTS, 0, 0, 0);
    if( p ){
      p->pSelect = yymsp[-1].minor.yy43;
      sqlite3ExprSpan(p,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy43);
    }
  }
#line 2710 "parse.c"
        break;
      case 228:
#line 859 "parse.y"
{
  yygotominor.yy450 = sqlite3Expr(TK_CASE, yymsp[-3].minor.yy450, yymsp[-1].minor.yy450, 0);
  if( yygotominor.yy450 ){
    yygotominor.yy450->pList = yymsp[-2].minor.yy242;
  }else{
    sqlite3ExprListDelete(yymsp[-2].minor.yy242);
  }
  sqlite3ExprSpan(yygotominor.yy450, &yymsp[-4].minor.yy0, &yymsp[0].minor.yy0);
}
#line 2723 "parse.c"
        break;
      case 229:
#line 870 "parse.y"
{
  yygotominor.yy242 = sqlite3ExprListAppend(yymsp[-4].minor.yy242, yymsp[-2].minor.yy450, 0);
  yygotominor.yy242 = sqlite3ExprListAppend(yygotominor.yy242, yymsp[0].minor.yy450, 0);
}
#line 2731 "parse.c"
        break;
      case 230:
#line 874 "parse.y"
{
  yygotominor.yy242 = sqlite3ExprListAppend(0, yymsp[-2].minor.yy450, 0);
  yygotominor.yy242 = sqlite3ExprListAppend(yygotominor.yy242, yymsp[0].minor.yy450, 0);
}
#line 2739 "parse.c"
        break;
      case 241:
#line 918 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy178.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy178.z, yymsp[-1].minor.yy178.n);
  }
  yygotominor.yy242 = sqlite3ExprListAppend(yymsp[-4].minor.yy242, p, &yymsp[-2].minor.yy178);
  if( yygotominor.yy242 ) yygotominor.yy242->a[yygotominor.yy242->nExpr-1].sortOrder = yymsp[0].minor.yy316;
}
#line 2752 "parse.c"
        break;
      case 242:
#line 927 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy178.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy178.z, yymsp[-1].minor.yy178.n);
  }
  yygotominor.yy242 = sqlite3ExprListAppend(0, p, &yymsp[-2].minor.yy178);
  if( yygotominor.yy242 ) yygotominor.yy242->a[yygotominor.yy242->nExpr-1].sortOrder = yymsp[0].minor.yy316;
}
#line 2765 "parse.c"
        break;
      case 249:
#line 1058 "parse.y"
{yygotominor.yy316 = OE_Rollback;}
#line 2770 "parse.c"
        break;
      case 250:
#line 1059 "parse.y"
{yygotominor.yy316 = OE_Abort;}
#line 2775 "parse.c"
        break;
      case 251:
#line 1060 "parse.y"
{yygotominor.yy316 = OE_Fail;}
#line 2780 "parse.c"
        break;
      case 252:
#line 1116 "parse.y"
{
    sqlite3SetStatement(pParse, yymsp[0].minor.yy242, 0, SQLTYPE_SET);
}
#line 2787 "parse.c"
        break;
      case 253:
#line 1120 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy178, SQLTYPE_SET_NAMES);   
}
#line 2794 "parse.c"
        break;
      case 254:
#line 1124 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy178, SQLTYPE_SET_CHARACTER_SET);
}
#line 2801 "parse.c"
        break;
      case 255:
#line 1130 "parse.y"
{
    yygotominor.yy242 = sqlite3ExprListAppend(yymsp[-5].minor.yy242, yymsp[0].minor.yy450, &yymsp[-2].minor.yy178);
}
#line 2808 "parse.c"
        break;
      case 256:
#line 1134 "parse.y"
{
    yygotominor.yy242 = sqlite3ExprListAppend(0, yymsp[0].minor.yy450, &yymsp[-2].minor.yy178);                         
}
#line 2815 "parse.c"
        break;
      case 260:
#line 1142 "parse.y"
{ sqlite3CheckSetScope(pParse, &yymsp[-1].minor.yy0); }
#line 2820 "parse.c"
        break;
      case 262:
#line 1146 "parse.y"
{ yygotominor.yy178 = yymsp[0].minor.yy178; }
#line 2825 "parse.c"
        break;
      case 263:
#line 1147 "parse.y"
{ yygotominor.yy178 = yymsp[0].minor.yy0; }
#line 2830 "parse.c"
        break;
      case 267:
#line 1154 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_DATABASES);
}
#line 2837 "parse.c"
        break;
      case 268:
#line 1158 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_TABLES);
}
#line 2844 "parse.c"
        break;
      case 269:
#line 1162 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_TABLE_STATUS);
}
#line 2851 "parse.c"
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
#line 2918 "parse.c"
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
