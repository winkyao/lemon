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
#define YYCODETYPE unsigned short int
#define YYNOCODE 253
#define YYACTIONTYPE unsigned short int
#define sqlite3ParserTOKENTYPE Token
typedef union {
  sqlite3ParserTOKENTYPE yy0;
  int yy4;
  struct {int value; int mask;} yy215;
  SrcList* yy259;
  ValuesList* yy287;
  struct LimitVal yy292;
  Expr* yy314;
  ExprList* yy322;
  struct LikeOp yy342;
  Token yy378;
  IdList* yy384;
  Select* yy387;
  int yy505;
} YYMINORTYPE;
#define YYSTACKDEPTH 100
#define sqlite3ParserARG_SDECL Parse *pParse;
#define sqlite3ParserARG_PDECL ,Parse *pParse
#define sqlite3ParserARG_FETCH Parse *pParse = yypParser->pParse
#define sqlite3ParserARG_STORE yypParser->pParse = pParse
#define YYNSTATE 510
#define YYNRULE 280
#define YYERRORSYMBOL 148
#define YYERRSYMDT yy505
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
 /*     0 */   238,  257,  288,  150,  271,  373,   57,   56,   56,   56,
 /*    10 */    56,  271,   58,   58,   58,   58,   59,   59,   60,   60,
 /*    20 */    60,   61,  363,    4,  363,   31,  321,  326,   61,  315,
 /*    30 */   167,  363,   26,  386,  183,  316,  487,  488,  489,  163,
 /*    40 */    58,   58,   58,   58,   59,   59,   60,   60,   60,   61,
 /*    50 */    55,   53,  246,  394,  397,  391,  391,   57,   56,   56,
 /*    60 */    56,   56,  169,   58,   58,   58,   58,   59,   59,   60,
 /*    70 */    60,   60,   61,  238,  364,   74,  373,   72,  204,   57,
 /*    80 */   381,  172,   63,   58,   58,   58,   58,   59,   59,   60,
 /*    90 */    60,   60,   61,  242,  339,  450,  791,  106,  509,  104,
 /*   100 */    99,    1,  447,  217,  319,  242,  386,   62,  420,  173,
 /*   110 */    52,  135,   62,  408,  173,  217,  135,   17,  493,  494,
 /*   120 */   495,  496,  497,   55,   53,  246,  394,  397,  391,  391,
 /*   130 */    57,   56,   56,   56,   56,  127,   58,   58,   58,   58,
 /*   140 */    59,   59,   60,   60,   60,   61,  238,  426,  258,   94,
 /*   150 */   453,  167,   57,   59,   59,   60,   60,   60,   61,  235,
 /*   160 */   163,  343,  383,  457,  147,   62,  455,  173,  447,  135,
 /*   170 */   271,  143,  344,  193,  267,  197,  268,  154,  150,  386,
 /*   180 */   373,  133,  218,  506,  344,  193,  267,  197,  268,  154,
 /*   190 */   363,   43,  373,  395,  218,  364,   55,   53,  246,  394,
 /*   200 */   397,  391,  391,   57,   56,   56,   56,   56,  415,   58,
 /*   210 */    58,   58,   58,   59,   59,   60,   60,   60,   61,  238,
 /*   220 */   104,  315,  383,  275,  147,   57,  271,  395,  487,  488,
 /*   230 */   489,  134,  121,  121,  340,  445,  771,  125,  255,  493,
 /*   240 */   494,  495,  496,  497,   76,   19,  363,   25,  458,  320,
 /*   250 */   190,  373,  386,  373,  469,  159,   18,  318,  290,  293,
 /*   260 */   294,  313,  120,  373,  410,  373,  364,  295,  251,   55,
 /*   270 */    53,  246,  394,  397,  391,  391,   57,   56,   56,   56,
 /*   280 */    56,  138,   58,   58,   58,   58,   59,   59,   60,   60,
 /*   290 */    60,   61,  238,   60,   60,   60,   61,  271,   57,  362,
 /*   300 */   271,  486,  271,  361,  415,  341,  342,  159,  385,  271,
 /*   310 */   290,  293,  294,  216,  245,  376,  377,  363,   21,  295,
 /*   320 */   363,   30,  363,   30,  373,  386,  130,  131,  159,  363,
 /*   330 */    30,  290,  293,  294,  340,  454,  373,   68,  424,  367,
 /*   340 */   295,  152,   55,   53,  246,  394,  397,  391,  391,   57,
 /*   350 */    56,   56,   56,   56,  430,   58,   58,   58,   58,   59,
 /*   360 */    59,   60,   60,   60,   61,  249,  467,  458,  238,  369,
 /*   370 */   369,  369,  284,  338,   57,   18,  364,  404,  171,  405,
 /*   380 */   298,  340,  271,  429,    3,  385,  405,  271,  153,  140,
 /*   390 */   274,  376,  377,  287,  459,  340,  481,  256,  132,  468,
 /*   400 */   456,  386,  363,   36,  340,  341,  342,  363,   43,  451,
 /*   410 */    71,   67,  454,   69,  155,  340,  367,  485,   55,   53,
 /*   420 */   246,  394,  397,  391,  391,   57,   56,   56,   56,   56,
 /*   430 */   433,   58,   58,   58,   58,   59,   59,   60,   60,   60,
 /*   440 */    61,  350,  282,  208,  238,  117,  369,  369,  369,  400,
 /*   450 */    57,   10,  341,  342,  171,  254,  351,  401,  271,  340,
 /*   460 */   466,  271,  434,  340,  198,  239,  341,  342,  465,  218,
 /*   470 */   324,  340,  352,    1,  348,  341,  342,  386,  363,   29,
 /*   480 */   119,  363,   36,  205,  115,  349,  341,  342,  314,  278,
 /*   490 */   416,  399,  399,  139,   55,   53,  246,  394,  397,  391,
 /*   500 */   391,   57,   56,   56,   56,   56,  452,   58,   58,   58,
 /*   510 */    58,   59,   59,   60,   60,   60,   61,  387,  325,  322,
 /*   520 */   238,  510,  206,  227,  325,  322,   57,  428,  420,  271,
 /*   530 */   341,  342,  169,  358,  341,  342,  250,  389,  390,  315,
 /*   540 */   271,  359,  341,  342,  439,  232,  487,  488,  489,  363,
 /*   550 */    48,  346,  347,  386,  417,  278,  485,  399,  399,  420,
 /*   560 */   363,   22,  233,  278,  388,  399,  399,  210,  440,  424,
 /*   570 */    55,   53,  246,  394,  397,  391,  391,   57,   56,   56,
 /*   580 */    56,   56,  221,   58,   58,   58,   58,   59,   59,   60,
 /*   590 */    60,   60,   61,  271,  227,  271,  238,  271,  212,  271,
 /*   600 */   136,  271,   57,  271,  445,  271,  445,    6,  445,  285,
 /*   610 */   289,  271,  209,  363,   46,  363,   30,  363,   85,  363,
 /*   620 */    83,  363,   87,  363,   88,  363,   95,  317,  248,  386,
 /*   630 */   499,  363,   96,  473,  362,  364,  307,  181,  361,  165,
 /*   640 */   227,  252,  156,  157,  158,  307,   55,   53,  246,  394,
 /*   650 */   397,  391,  391,   57,   56,   56,   56,   56,  247,   58,
 /*   660 */    58,   58,   58,   59,   59,   60,   60,   60,   61,  238,
 /*   670 */   271,  137,  405,  271,  364,   57,  271,  445,  271,  228,
 /*   680 */   355,  170,  216,  271,  215,  164,  216,  271,   49,  356,
 /*   690 */   363,   16,  271,  363,   86,  271,  363,   47,  363,   97,
 /*   700 */   182,  499,  386,  363,   98,  227,  364,  363,   23,  310,
 /*   710 */   253,  227,  363,   32,  272,  363,   33,  500,  144,   55,
 /*   720 */    53,  246,  394,  397,  391,  391,   57,   56,   56,   56,
 /*   730 */    56,  271,   58,   58,   58,   58,   59,   59,   60,   60,
 /*   740 */    60,   61,  238,  271,  305,  271,  500,  271,   57,  271,
 /*   750 */   231,  363,   24,  271,  413,  216,  271,  161,  271,  307,
 /*   760 */   271,  498,  271,  363,   34,  363,   35,  363,   37,  363,
 /*   770 */    38,  149,  140,  363,   39,  386,  363,   27,  363,   28,
 /*   780 */   363,   40,  363,   41,  278,  110,  399,  399,   74,  500,
 /*   790 */   501,  500,  364,   53,  246,  394,  397,  391,  391,   57,
 /*   800 */    56,   56,   56,   56,  155,   58,   58,   58,   58,   59,
 /*   810 */    59,   60,   60,   60,   61,  238,  271,  500,  271,  166,
 /*   820 */   271,   57,  276,  312,  379,  379,  261,  263,  241,  192,
 /*   830 */   101,  547,  374,  503,  194,  504,  363,   42,  363,   44,
 /*   840 */   363,   45,  438,  195,  403,  443,  368,  422,  386,  129,
 /*   850 */    20,  382,  406,  414,  419,  239,  423,  214,  436,  435,
 /*   860 */   461,  505,   13,  110,  166,  151,  441,  246,  394,  397,
 /*   870 */   391,  391,   57,   56,   56,   56,   56,    5,   58,   58,
 /*   880 */    58,   58,   59,   59,   60,   60,   60,   61,    5,  480,
 /*   890 */   442,  431,   64,  279,  220,  297,  478,  244,  479,  482,
 /*   900 */   460,  222,  392,   64,  279,  225,  306,  502,  244,   13,
 /*   910 */   273,  196,  110,  110,   80,  437,   80,  151,  333,  199,
 /*   920 */   128,  273,  378,  380,  280,  277,  409,  396,  230,  491,
 /*   930 */   434,  412,  492,  444,  446,  122,  123,  329,  328,  292,
 /*   940 */   331,  385,  332,    9,  260,  264,  336,  265,  266,  345,
 /*   950 */   353,  243,  385,  354,  357,  360,  365,   74,  200,   66,
 /*   960 */    65,    5,   73,  203,  283,  201,  281,   64,  269,  270,
 /*   970 */    66,   65,  367,  202,   51,  148,   64,  279,   64,  269,
 /*   980 */   270,  244,   70,  367,  366,  407,  176,  207,  169,  410,
 /*   990 */   107,  411,  177,  175,  273,  286,   75,  211,   90,  236,
 /*  1000 */   421,  213,  369,  369,  369,  370,  371,  372,   12,  425,
 /*  1010 */   179,  180,  449,  369,  369,  369,  370,  371,  372,   12,
 /*  1020 */   462,    5,  448,    2,  237,  385,  472,  299,  463,  187,
 /*  1030 */   259,  300,  464,  188,  189,  223,   64,  279,  162,  303,
 /*  1040 */   229,  244,  470,   66,   65,  427,  474,  102,  476,  105,
 /*  1050 */    11,   64,  269,  270,  273,  111,  367,  116,  311,  187,
 /*  1060 */   259,   84,  477,  188,  189,  223,  240,  178,   89,  327,
 /*  1070 */   330,  234,  262,  103,  334,  335,  191,  102,  484,  337,
 /*  1080 */   168,  308,   50,  548,  549,  385,  369,  369,  369,  370,
 /*  1090 */   371,  372,   12,  145,  146,   54,  393,  375,  384,  174,
 /*  1100 */   398,  126,    7,   66,   65,  402,   14,    8,  484,   13,
 /*  1110 */   418,   64,  269,  270,  108,  141,  367,  109,  432,  291,
 /*  1120 */    91,  296,  219,   93,  304,  113,  483,   92,   77,  302,
 /*  1130 */   160,  195,  224,  301,  169,  114,  112,  226,  471,   15,
 /*  1140 */   185,  475,  490,  186,  507,  309,  369,  369,  369,  370,
 /*  1150 */   371,  372,   12,   78,  304,  113,  483,   79,  118,  302,
 /*  1160 */   164,   81,  142,  100,  169,  124,  323,  534,  184,   82,
 /*  1170 */   508,  534,  534,  534,  534,  534,  534,  534,  534,  534,
 /*  1180 */   534,  534,  534,  534,  534,  534,  534,  534,  534,  534,
 /*  1190 */   534,  534,  534,  100,
};
static const YYCODETYPE yy_lookahead[] = {
 /*     0 */    16,   49,  160,   19,  160,   21,   22,   74,   75,   76,
 /*    10 */    77,  160,   79,   80,   81,   82,   83,   84,   85,   86,
 /*    20 */    87,   88,  180,  181,  180,  181,  152,  153,   88,  131,
 /*    30 */   156,  180,  181,   49,  136,  137,  138,  139,  140,  165,
 /*    40 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*    50 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*    60 */    76,   77,  112,   79,   80,   81,   82,   83,   84,   85,
 /*    70 */    86,   87,   88,   16,  200,  123,   92,   20,  234,   22,
 /*    80 */    83,   84,   78,   79,   80,   81,   82,   83,   84,   85,
 /*    90 */    86,   87,   88,   16,  178,  179,  149,  150,  151,  225,
 /*   100 */    23,  154,  186,   26,   14,   16,   49,  229,  172,  231,
 /*   110 */    53,  233,  229,  230,  231,   26,  233,    1,  244,  245,
 /*   120 */   246,  247,  248,   66,   67,   68,   69,   70,   71,   72,
 /*   130 */    73,   74,   75,   76,   77,   19,   79,   80,   81,   82,
 /*   140 */    83,   84,   85,   86,   87,   88,   16,  211,  153,   19,
 /*   150 */   180,  156,   22,   83,   84,   85,   86,   87,   88,  169,
 /*   160 */   165,  179,  172,  173,  174,  229,  180,  231,  186,  233,
 /*   170 */   160,   94,   95,   96,   97,   98,   99,  100,   19,   49,
 /*   180 */    21,   20,  105,   93,   95,   96,   97,   98,   99,  100,
 /*   190 */   180,  181,   21,   92,  105,  200,   66,   67,   68,   69,
 /*   200 */    70,   71,   72,   73,   74,   75,   76,   77,   20,   79,
 /*   210 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   220 */   225,  131,  172,  173,  174,   22,  160,  126,  138,  139,
 /*   230 */   140,  165,  142,  143,   21,  160,  146,  147,  228,  244,
 /*   240 */   245,  246,  247,  248,    1,    1,  180,  181,  160,  242,
 /*   250 */   162,   92,   49,   21,  166,   94,  168,  250,   97,   98,
 /*   260 */    99,  241,  242,   92,   21,   21,  200,  106,  193,   66,
 /*   270 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   280 */    77,   93,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   290 */    87,   88,   16,   85,   86,   87,   88,  160,   22,  109,
 /*   300 */   160,  130,  160,  113,  116,   92,   93,   94,   65,  160,
 /*   310 */    97,   98,   99,  238,  175,  176,  177,  180,  181,  106,
 /*   320 */   180,  181,  180,  181,   92,   49,   83,   84,   94,  180,
 /*   330 */   181,   97,   98,   99,   21,   92,   92,  134,  160,   96,
 /*   340 */   106,  165,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   350 */    74,   75,   76,   77,    2,   79,   80,   81,   82,   83,
 /*   360 */    84,   85,   86,   87,   88,  223,  192,  160,   16,  126,
 /*   370 */   127,  128,  223,  166,   22,  168,  200,  237,  239,  237,
 /*   380 */    16,   21,  160,    2,    1,   65,  237,  160,  212,  213,
 /*   390 */   175,  176,  177,  217,  192,   21,    2,  219,  191,  192,
 /*   400 */   171,   49,  180,  181,   21,   92,   93,  180,  181,  180,
 /*   410 */   134,  133,   92,  135,   50,   21,   96,  172,   66,   67,
 /*   420 */    68,   69,   70,   71,   72,   73,   74,   75,   76,   77,
 /*   430 */     2,   79,   80,   81,   82,   83,   84,   85,   86,   87,
 /*   440 */    88,   12,  220,  221,   16,   25,  126,  127,  128,    2,
 /*   450 */    22,    1,   92,   93,  239,  228,   27,    2,  160,   21,
 /*   460 */   186,  160,  188,   21,  201,  101,   92,   93,  194,  105,
 /*   470 */   151,   21,   43,  154,   45,   92,   93,   49,  180,  181,
 /*   480 */   242,  180,  181,  160,  124,   56,   92,   93,  243,  108,
 /*   490 */   116,  110,  111,  160,   66,   67,   68,   69,   70,   71,
 /*   500 */    72,   73,   74,   75,   76,   77,    2,   79,   80,   81,
 /*   510 */    82,   83,   84,   85,   86,   87,   88,   49,    3,    4,
 /*   520 */    16,    0,  221,  160,    3,    4,   22,   85,  172,  160,
 /*   530 */    92,   93,  112,   30,   92,   93,   25,   69,   70,  131,
 /*   540 */   160,   38,   92,   93,   33,  125,  138,  139,  140,  180,
 /*   550 */   181,  196,  197,   49,  116,  108,  172,  110,  111,  172,
 /*   560 */   180,  181,  199,  108,   96,  110,  111,  211,   57,  160,
 /*   570 */    66,   67,   68,   69,   70,   71,   72,   73,   74,   75,
 /*   580 */    76,   77,    2,   79,   80,   81,   82,   83,   84,   85,
 /*   590 */    86,   87,   88,  160,  160,  160,   16,  160,  211,  160,
 /*   600 */   165,  160,   22,  160,  160,  160,  160,  202,  160,  160,
 /*   610 */    85,  160,  160,  180,  181,  180,  181,  180,  181,  180,
 /*   620 */   181,  180,  181,  180,  181,  180,  181,  243,  219,   49,
 /*   630 */    21,  180,  181,  199,  109,  200,  160,  193,  113,  165,
 /*   640 */   160,  193,  102,  103,  104,  160,   66,   67,   68,   69,
 /*   650 */    70,   71,   72,   73,   74,   75,   76,   77,  223,   79,
 /*   660 */    80,   81,   82,   83,   84,   85,   86,   87,   88,   16,
 /*   670 */   160,  165,  237,  160,  200,   22,  160,  160,  160,  199,
 /*   680 */    37,  203,  238,  160,  238,   20,  238,  160,  210,   46,
 /*   690 */   180,  181,  160,  180,  181,  160,  180,  181,  180,  181,
 /*   700 */   224,   92,   49,  180,  181,  160,  200,  180,  181,  224,
 /*   710 */   193,  160,  180,  181,  160,  180,  181,  205,    1,   66,
 /*   720 */    67,   68,   69,   70,   71,   72,   73,   74,   75,   76,
 /*   730 */    77,  160,   79,   80,   81,   82,   83,   84,   85,   86,
 /*   740 */    87,   88,   16,  160,  199,  160,  205,  160,   22,  160,
 /*   750 */   199,  180,  181,  160,   20,  238,  160,  165,  160,  160,
 /*   760 */   160,  249,  160,  180,  181,  180,  181,  180,  181,  180,
 /*   770 */   181,  212,  213,  180,  181,   49,  180,  181,  180,  181,
 /*   780 */   180,  181,  180,  181,  108,   20,  110,  111,  123,  205,
 /*   790 */   249,  205,  200,   67,   68,   69,   70,   71,   72,   73,
 /*   800 */    74,   75,   76,   77,   50,   79,   80,   81,   82,   83,
 /*   810 */    84,   85,   86,   87,   88,   16,  160,  205,  160,   70,
 /*   820 */   160,   22,   16,  224,  126,  127,   21,   24,   23,   26,
 /*   830 */   160,  114,    2,  249,   96,  249,  180,  181,  180,  181,
 /*   840 */   180,  181,   23,  105,    2,    2,  160,    2,   49,  115,
 /*   850 */    20,  172,  160,  214,  160,  101,  160,  160,  189,  160,
 /*   860 */    95,  249,   20,   20,  115,   20,  189,   68,   69,   70,
 /*   870 */    71,   72,   73,   74,   75,   76,   77,    1,   79,   80,
 /*   880 */    81,   82,   83,   84,   85,   86,   87,   88,    1,    2,
 /*   890 */   189,    2,   16,   17,    2,    2,    2,   21,    2,    2,
 /*   900 */   160,  160,   96,   16,   17,  160,  160,  160,   21,   20,
 /*   910 */    34,  183,   20,   20,   20,   96,   20,   20,  157,  204,
 /*   920 */   202,   34,  240,  240,  236,  232,  183,  232,  205,  172,
 /*   930 */   188,  183,  172,  183,  183,  251,  251,   10,  155,  187,
 /*   940 */   155,   65,  155,   20,  163,  167,   22,  167,  101,  182,
 /*   950 */   182,   47,   65,  190,  182,  182,  200,  123,  205,   83,
 /*   960 */    84,    1,  121,  208,  120,  206,  118,   91,   92,   93,
 /*   970 */    83,   84,   96,  207,  122,  114,   16,   17,   91,   92,
 /*   980 */    93,   21,  133,   96,  209,  161,  222,   26,  112,   21,
 /*   990 */   161,  171,  222,  235,   34,  117,  101,  215,    1,  184,
 /*  1000 */   216,  215,  126,  127,  128,  129,  130,  131,  132,  216,
 /*  1010 */   222,  222,  190,  126,  127,  128,  129,  130,  131,  132,
 /*  1020 */   182,    1,  171,    1,  184,   65,   18,  158,  182,    7,
 /*  1030 */     8,   15,  182,   11,   12,   13,   16,   17,  159,   15,
 /*  1040 */   205,   21,  161,   83,   84,   85,  161,   25,  209,    1,
 /*  1050 */     1,   91,   92,   93,   34,  198,   96,  226,  226,    7,
 /*  1060 */     8,  170,  209,   11,   12,   13,  164,  185,  185,    2,
 /*  1070 */     9,    2,   22,   35,   21,   21,   25,   25,   56,   21,
 /*  1080 */    51,  227,    1,  114,  114,   65,  126,  127,  128,  129,
 /*  1090 */   130,  131,  132,  114,  114,    1,   96,    2,    2,   67,
 /*  1100 */   109,    1,  119,   83,   84,   41,   20,  119,   56,   20,
 /*  1110 */   116,   91,   92,   93,    1,  114,   96,    2,    2,   51,
 /*  1120 */     1,   51,    2,    1,  102,  103,  104,    1,    1,  107,
 /*  1130 */   100,  105,   14,   16,  112,   25,  115,   14,   17,    1,
 /*  1140 */   144,   17,  114,  145,    3,   20,  126,  127,  128,  129,
 /*  1150 */   130,  131,  132,   22,  102,  103,  104,   22,   25,  107,
 /*  1160 */    20,   22,   20,  141,  112,  146,    5,  252,   25,   22,
 /*  1170 */     6,  252,  252,  252,  252,  252,  252,  252,  252,  252,
 /*  1180 */   252,  252,  252,  252,  252,  252,  252,  252,  252,  252,
 /*  1190 */   252,  252,  252,  141,
};
#define YY_SHIFT_USE_DFLT (-103)
#define YY_SHIFT_MAX 323
static const short yy_shift_ofst[] = {
 /*     0 */   515, 1022, 1052,  876,  -16,  876, 1020, 1020, 1020,  213,
 /*    10 */   -50,  887, 1020, 1020, 1020, 1020,    4,  313,  232,   -3,
 /*    20 */    -3,   57,  130,  203,  276,  352,  428,  504,  580,  653,
 /*    30 */   653,  653,  653,  653,  653,  653,  653,  653,  653,  653,
 /*    40 */   653,  653,  653,  653,  653,  653,  726,  799,  799,  960,
 /*    50 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    60 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    70 */  1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020, 1020,
 /*    80 */  1020, 1020, 1020,  -67,   77,  -39,  -39,   70,  208,  364,
 /*    90 */   313,  313,  313,  313,  232,  -60, -103, -103, -103,  243,
 /*   100 */    90,   89, -102,  429,  360,  394,  521,  159,  313,  159,
 /*   110 */   313,  313,  313,  313,  313,  313,  420,  313,  313,  171,
 /*   120 */   171,  -48,  -48,  -48,  -48,  -48,  -50,  -50, -103, -103,
 /*   130 */   320,  320,  161,  234,  381,  383,  447,  455,  374,  438,
 /*   140 */   450,  442,  408,  313,  525,  313,  313,  244,  313,  188,
 /*   150 */   313,  313,  676,  188,  313,  313,  511,  511,  511,  313,
 /*   160 */   313,  676,  313,  676,  313,  676,  313,  116,  503,  190,
 /*   170 */   734,  698,  698,  101,  101,  278,  503,  503,  754,  503,
 /*   180 */   503,  765,  665,  232,  232,  749,  749,  927,  927,  927,
 /*   190 */   923,  924,  924,  847,  847,  904,  847,  847,  -50,  834,
 /*   200 */   844,  841,  848,  852,  849,  861,  961,  968,  961,  861,
 /*   210 */   895,  878,  895,  878,  997,  961,  961,  968,  904,  847,
 /*   220 */   847,  847,  997, 1008, 1016,  861, 1024,  861,  834,  852,
 /*   230 */   852, 1048, 1049, 1048, -103, -103, -103, -103,  468,  540,
 /*   240 */   805,  803,  738,  643,  717,  830,  806,  842,  845,  889,
 /*   250 */   819,  843,  892,  893,  894,  896,  897,  609, 1067, 1061,
 /*   260 */  1069, 1050, 1053, 1051, 1054, 1058, 1038, 1029, 1081,  969,
 /*   270 */   970,  979,  980, 1094, 1095, 1096, 1000, 1032,  991, 1100,
 /*   280 */  1064,  983, 1086,  988, 1089,  994, 1113, 1115, 1001, 1116,
 /*   290 */  1068, 1119, 1120, 1126, 1127, 1070, 1122, 1030, 1026, 1118,
 /*   300 */  1117, 1121, 1123, 1124, 1021, 1110, 1131, 1135, 1125, 1138,
 /*   310 */  1140, 1133, 1140, 1142, 1139, 1028, 1143, 1147,  996,  998,
 /*   320 */  1019, 1141, 1161, 1164,
};
#define YY_REDUCE_USE_DFLT (-159)
#define YY_REDUCE_MAX 237
static const short yy_reduce_ofst[] = {
 /*     0 */   -53, -126,   -5,  435,  -64,   66,  142,  222,  149,  207,
 /*    10 */   176,   10, -156,  140,  301,  227, -117,   88,  -10,  139,
 /*    20 */   215, -122, -122, -122, -122, -122, -122, -122, -122, -122,
 /*    30 */  -122, -122, -122, -122, -122, -122, -122, -122, -122, -122,
 /*    40 */  -122, -122, -122, -122, -122, -122, -122, -122, -122, -158,
 /*    50 */  -149,  137,  298,  369,  380,  433,  437,  439,  441,  443,
 /*    60 */   445,  451,  510,  513,  516,  518,  523,  527,  532,  535,
 /*    70 */   571,  583,  585,  587,  589,  593,  596,  598,  600,  602,
 /*    80 */   656,  658,  660, -122,  -84, -122, -122, -122, -122,  274,
 /*    90 */    75,  444,  448,  517,   50, -122, -122, -122, -122,  229,
 /*   100 */     7,  -18,   20,  355,  363,  178,  319,  356,  409,  387,
 /*   110 */   446,  434,  480,  545,  476,  551,  474,  485,  599,  245,
 /*   120 */   384,  512,  541,  584,  586,  612,  506,  592,  478,  559,
 /*   130 */   -30,  -14,  174,  202,  263,  323,  263,  263,  333,  449,
 /*   140 */   452,  554,  238,  670,  405,  554,  686,  679,  692,  639,
 /*   150 */   694,  696,  263,  639,  697,  699,  669,  677,  701,  740,
 /*   160 */   741,  263,  745,  263,  746,  263,  747,  761,  728,  718,
 /*   170 */   715,  682,  683,  693,  695,  688,  743,  748,  742,  750,
 /*   180 */   751,  752,  723,  757,  760,  684,  685,  783,  785,  787,
 /*   190 */   781,  778,  780,  767,  768,  763,  772,  773,  756,  753,
 /*   200 */   759,  766,  755,  775,  758,  824,  764,  820,  770,  829,
 /*   210 */   782,  784,  786,  793,  815,  788,  789,  851,  822,  838,
 /*   220 */   846,  850,  840,  869,  879,  881,  857,  885,  835,  839,
 /*   230 */   853,  831,  854,  832,  902,  891,  882,  883,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   517,  790,  790,  748,  631,  790,  748,  790,  748,  790,
 /*    10 */   635,  790,  744,  748,  790,  790,  718,  790,  550,  758,
 /*    20 */   758,  666,  790,  790,  790,  790,  790,  790,  790,  667,
 /*    30 */   747,  743,  739,  741,  740,  668,  655,  664,  671,  647,
 /*    40 */   673,  674,  684,  685,  765,  766,  708,  724,  707,  790,
 /*    50 */   790,  790,  790,  790,  790,  790,  790,  790,  790,  790,
 /*    60 */   790,  790,  790,  790,  790,  790,  790,  790,  790,  790,
 /*    70 */   790,  790,  790,  790,  790,  790,  790,  790,  790,  790,
 /*    80 */   790,  790,  790,  710,  543,  709,  717,  711,  712,  604,
 /*    90 */   790,  790,  790,  790,  790,  713,  714,  725,  726,  790,
 /*   100 */   785,  790,  771,  790,  790,  790,  517,  631,  790,  631,
 /*   110 */   790,  790,  790,  790,  790,  790,  790,  790,  790,  790,
 /*   120 */   790,  670,  670,  670,  670,  670,  790,  790,  625,  635,
 /*   130 */   790,  790,  595,  790,  790,  790,  790,  790,  790,  790,
 /*   140 */   790,  790,  771,  790,  623,  790,  790,  552,  790,  633,
 /*   150 */   790,  790,  638,  639,  790,  790,  790,  790,  790,  790,
 /*   160 */   790,  533,  790,  614,  790,  678,  790,  790,  658,  623,
 /*   170 */   632,  790,  790,  790,  790,  742,  658,  658,  574,  658,
 /*   180 */   658,  577,  670,  790,  790,  788,  788,  522,  522,  522,
 /*   190 */   594,  541,  541,  606,  606,  591,  606,  606,  790,  670,
 /*   200 */   661,  663,  651,  665,  790,  640,  659,  790,  659,  640,
 /*   210 */   648,  650,  648,  650,  749,  659,  659,  790,  591,  606,
 /*   220 */   606,  606,  749,  531,  528,  640,  613,  640,  670,  665,
 /*   230 */   665,  686,  790,  686,  536,  560,  579,  579,  790,  790,
 /*   240 */   532,  790,  790,  790,  694,  790,  790,  790,  790,  790,
 /*   250 */   790,  790,  790,  790,  790,  790,  790,  790,  790,  790,
 /*   260 */   790,  537,  790,  790,  790,  790,  790,  790,  790,  699,
 /*   270 */   695,  790,  696,  790,  790,  790,  790,  790,  617,  790,
 /*   280 */   790,  790,  652,  790,  662,  790,  790,  790,  790,  790,
 /*   290 */   790,  790,  790,  790,  790,  790,  790,  790,  790,  790,
 /*   300 */   790,  790,  790,  790,  790,  790,  790,  790,  675,  790,
 /*   310 */   676,  790,  677,  762,  790,  790,  790,  790,  790,  790,
 /*   320 */   790,  790,  518,  790,  511,  515,  513,  514,  520,  523,
 /*   330 */   521,  524,  525,  526,  538,  539,  542,  540,  534,  559,
 /*   340 */   547,  548,  549,  561,  568,  569,  607,  608,  609,  610,
 /*   350 */   759,  760,  761,  570,  589,  592,  593,  571,  656,  657,
 /*   360 */   572,  621,  622,  691,  615,  616,  620,  693,  697,  698,
 /*   370 */   700,  701,  702,  546,  553,  554,  557,  558,  754,  756,
 /*   380 */   755,  757,  556,  555,  703,  706,  715,  716,  722,  728,
 /*   390 */   732,  720,  721,  723,  727,  729,  730,  731,  618,  619,
 /*   400 */   735,  737,  738,  733,  745,  746,  641,  736,  719,  653,
 /*   410 */   545,  660,  654,  624,  634,  643,  644,  645,  646,  629,
 /*   420 */   630,  636,  649,  689,  690,  637,  626,  627,  628,  734,
 /*   430 */   692,  704,  705,  573,  580,  581,  582,  585,  586,  587,
 /*   440 */   588,  583,  584,  750,  751,  753,  752,  575,  576,  590,
 /*   450 */   562,  563,  564,  565,  699,  566,  567,  551,  544,  596,
 /*   460 */   599,  578,  600,  601,  602,  603,  605,  597,  598,  535,
 /*   470 */   527,  529,  530,  611,  642,  612,  669,  672,  681,  682,
 /*   480 */   683,  687,  688,  679,  680,  772,  773,  767,  768,  769,
 /*   490 */   770,  763,  764,  774,  775,  776,  777,  778,  779,  786,
 /*   500 */   787,  780,  789,  781,  782,  783,  784,  516,  519,  512,
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
    0,  /*  COLLATION => nothing */
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
  "TABLES",        "STATUS",        "VARIABLES",     "COLLATION",   
  "error",         "input",         "cmdlist",       "ecmd",        
  "cmdx",          "cmd",           "explain",       "trans_opt",   
  "create_table",  "create_table_args",  "temp",          "ifnotexists", 
  "nm",            "dbnm",          "columnlist",    "conslist_opt",
  "table_opt",     "select",        "column",        "eq_or_null",  
  "columnid",      "type",          "carglist",      "id",          
  "ids",           "typetoken",     "typename",      "signed",      
  "plus_num",      "minus_num",     "carg",          "ccons",       
  "term",          "expr",          "onconf",        "sortorder",   
  "idxlist_opt",   "refargs",       "defer_subclause",  "autoinc",     
  "refarg",        "refact",        "init_deferred_pred_opt",  "conslist",    
  "tcons",         "idxlist",       "defer_subclause_opt",  "orconf",      
  "resolvetype",   "raisetype",     "ifexists",      "fullname",    
  "oneselect",     "multiselect_op",  "distinct",      "selcollist",  
  "from",          "where_opt",     "groupby_opt",   "having_opt",  
  "orderby_opt",   "limit_opt",     "sclp",          "as",          
  "seltablist",    "stl_prefix",    "joinop",        "on_opt",      
  "using_opt",     "seltablist_paren",  "joinop2",       "inscollist",  
  "sortlist",      "sortitem",      "collate",       "exprlist",    
  "setlist",       "insert_cmd",    "inscollist_opt",  "valueslist",  
  "itemlist",      "likeop",        "escape",        "between_op",  
  "between_elem",  "in_op",         "case_operand",  "case_exprlist",
  "case_else",     "expritem",      "idxitem",       "plus_opt",    
  "number",        "variable_assignment_list",  "scope_qualifier",  "user_var_name",
  "show_databes",  "show_tables",   "show_table_status",  "show_variables",
  "show_collation",  "show_statement_pattern",  "full_keyword",  "from_db",     
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
 /* 268 */ "cmd ::= show_collation",
 /* 269 */ "show_databes ::= SHOW DATABASES|SCHEMAS show_statement_pattern",
 /* 270 */ "show_tables ::= SHOW full_keyword TABLES from_db show_statement_pattern",
 /* 271 */ "show_table_status ::= SHOW TABLE STATUS from_db show_statement_pattern",
 /* 272 */ "show_variables ::= SHOW scope_qualifier VARIABLES show_statement_pattern",
 /* 273 */ "show_collation ::= SHOW COLLATION show_statement_pattern",
 /* 274 */ "full_keyword ::= JOIN_KW",
 /* 275 */ "full_keyword ::=",
 /* 276 */ "show_statement_pattern ::= LIKE_KW STRING|ID",
 /* 277 */ "show_statement_pattern ::= where_opt",
 /* 278 */ "from_db ::=",
 /* 279 */ "from_db ::= FROM|IN nm",
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
    case 165:
    case 200:
    case 217:
#line 391 "parse.y"
{sqlite3SelectDelete((yypminor->yy387));}
#line 1183 "parse.c"
      break;
    case 180:
    case 181:
    case 205:
    case 207:
    case 215:
    case 221:
    case 230:
    case 232:
    case 234:
    case 236:
    case 237:
#line 669 "parse.y"
{sqlite3ExprDelete((yypminor->yy314));}
#line 1198 "parse.c"
      break;
    case 184:
    case 193:
    case 203:
    case 206:
    case 208:
    case 210:
    case 220:
    case 223:
    case 224:
    case 228:
    case 235:
#line 913 "parse.y"
{sqlite3ExprListDelete((yypminor->yy322));}
#line 1213 "parse.c"
      break;
    case 199:
    case 204:
    case 212:
    case 213:
#line 519 "parse.y"
{sqlite3SrcListDelete((yypminor->yy259));}
#line 1221 "parse.c"
      break;
    case 209:
#line 580 "parse.y"
{
  sqlite3ExprDelete((yypminor->yy292).pLimit);
  sqlite3ExprDelete((yypminor->yy292).pOffset);
}
#line 1229 "parse.c"
      break;
    case 216:
    case 219:
    case 226:
#line 536 "parse.y"
{sqlite3IdListDelete((yypminor->yy384));}
#line 1236 "parse.c"
      break;
    case 227:
#line 640 "parse.y"
{sqlite3ValuesListDelete((yypminor->yy287));}
#line 1241 "parse.c"
      break;
    case 241:
#line 1129 "parse.y"
{ sqlite3ExprListDelete((yypminor->yy322)); }
#line 1246 "parse.c"
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
#line 1398 "parse.c"
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
  { 149, 1 },
  { 150, 2 },
  { 150, 1 },
  { 152, 1 },
  { 152, 3 },
  { 151, 1 },
  { 151, 3 },
  { 154, 0 },
  { 154, 1 },
  { 154, 3 },
  { 153, 2 },
  { 153, 2 },
  { 155, 0 },
  { 155, 1 },
  { 153, 2 },
  { 153, 2 },
  { 153, 2 },
  { 156, 6 },
  { 159, 0 },
  { 159, 3 },
  { 158, 1 },
  { 158, 0 },
  { 157, 5 },
  { 157, 2 },
  { 162, 3 },
  { 162, 1 },
  { 164, 0 },
  { 164, 2 },
  { 164, 4 },
  { 164, 6 },
  { 164, 5 },
  { 167, 0 },
  { 167, 1 },
  { 166, 3 },
  { 168, 1 },
  { 171, 1 },
  { 172, 1 },
  { 160, 1 },
  { 160, 1 },
  { 160, 1 },
  { 169, 0 },
  { 169, 1 },
  { 173, 1 },
  { 173, 4 },
  { 173, 6 },
  { 174, 1 },
  { 174, 2 },
  { 175, 1 },
  { 175, 1 },
  { 170, 2 },
  { 170, 0 },
  { 178, 3 },
  { 178, 1 },
  { 178, 2 },
  { 178, 4 },
  { 178, 3 },
  { 178, 3 },
  { 178, 2 },
  { 179, 1 },
  { 179, 2 },
  { 179, 3 },
  { 179, 4 },
  { 179, 2 },
  { 179, 4 },
  { 179, 4 },
  { 179, 1 },
  { 179, 2 },
  { 187, 0 },
  { 187, 1 },
  { 185, 0 },
  { 185, 2 },
  { 188, 2 },
  { 188, 3 },
  { 188, 3 },
  { 188, 3 },
  { 189, 2 },
  { 189, 2 },
  { 189, 1 },
  { 189, 1 },
  { 186, 3 },
  { 186, 2 },
  { 190, 0 },
  { 190, 2 },
  { 190, 2 },
  { 163, 0 },
  { 163, 2 },
  { 191, 3 },
  { 191, 2 },
  { 191, 1 },
  { 192, 2 },
  { 192, 7 },
  { 192, 5 },
  { 192, 5 },
  { 192, 10 },
  { 194, 0 },
  { 194, 1 },
  { 182, 0 },
  { 182, 3 },
  { 196, 1 },
  { 196, 1 },
  { 196, 1 },
  { 153, 4 },
  { 198, 2 },
  { 198, 0 },
  { 153, 1 },
  { 165, 1 },
  { 165, 3 },
  { 201, 1 },
  { 201, 2 },
  { 201, 1 },
  { 200, 9 },
  { 202, 1 },
  { 202, 1 },
  { 202, 0 },
  { 210, 2 },
  { 210, 0 },
  { 203, 3 },
  { 203, 2 },
  { 203, 4 },
  { 211, 2 },
  { 211, 1 },
  { 211, 0 },
  { 204, 0 },
  { 204, 2 },
  { 213, 2 },
  { 213, 0 },
  { 212, 6 },
  { 212, 7 },
  { 217, 1 },
  { 217, 1 },
  { 161, 0 },
  { 161, 2 },
  { 199, 2 },
  { 214, 1 },
  { 214, 2 },
  { 214, 3 },
  { 214, 4 },
  { 215, 2 },
  { 215, 0 },
  { 216, 4 },
  { 216, 0 },
  { 208, 0 },
  { 208, 3 },
  { 220, 5 },
  { 220, 3 },
  { 221, 1 },
  { 183, 1 },
  { 183, 1 },
  { 183, 0 },
  { 222, 0 },
  { 222, 2 },
  { 206, 0 },
  { 206, 3 },
  { 207, 0 },
  { 207, 2 },
  { 209, 0 },
  { 209, 2 },
  { 209, 4 },
  { 209, 4 },
  { 153, 5 },
  { 205, 0 },
  { 205, 2 },
  { 153, 6 },
  { 224, 5 },
  { 224, 3 },
  { 153, 6 },
  { 153, 6 },
  { 153, 5 },
  { 153, 5 },
  { 225, 1 },
  { 225, 1 },
  { 227, 5 },
  { 227, 3 },
  { 227, 2 },
  { 228, 3 },
  { 228, 1 },
  { 226, 0 },
  { 226, 2 },
  { 226, 3 },
  { 219, 3 },
  { 219, 1 },
  { 181, 1 },
  { 181, 3 },
  { 180, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 3 },
  { 181, 5 },
  { 180, 1 },
  { 180, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 1 },
  { 181, 6 },
  { 181, 5 },
  { 181, 4 },
  { 180, 1 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 181, 3 },
  { 229, 1 },
  { 229, 2 },
  { 230, 2 },
  { 230, 0 },
  { 181, 4 },
  { 181, 2 },
  { 181, 3 },
  { 181, 3 },
  { 181, 4 },
  { 181, 2 },
  { 181, 2 },
  { 181, 2 },
  { 231, 1 },
  { 231, 2 },
  { 232, 1 },
  { 181, 5 },
  { 233, 1 },
  { 233, 2 },
  { 181, 5 },
  { 181, 3 },
  { 181, 5 },
  { 181, 4 },
  { 181, 4 },
  { 181, 5 },
  { 235, 5 },
  { 235, 4 },
  { 236, 2 },
  { 236, 0 },
  { 234, 1 },
  { 234, 0 },
  { 223, 3 },
  { 223, 1 },
  { 237, 1 },
  { 237, 0 },
  { 184, 0 },
  { 184, 3 },
  { 193, 5 },
  { 193, 3 },
  { 238, 1 },
  { 176, 2 },
  { 177, 2 },
  { 240, 1 },
  { 239, 1 },
  { 239, 0 },
  { 197, 1 },
  { 197, 1 },
  { 197, 1 },
  { 153, 2 },
  { 153, 3 },
  { 153, 4 },
  { 241, 6 },
  { 241, 4 },
  { 242, 1 },
  { 242, 1 },
  { 242, 1 },
  { 242, 2 },
  { 242, 0 },
  { 243, 1 },
  { 243, 1 },
  { 153, 1 },
  { 153, 1 },
  { 153, 1 },
  { 153, 1 },
  { 153, 1 },
  { 244, 3 },
  { 245, 5 },
  { 246, 5 },
  { 247, 4 },
  { 248, 3 },
  { 250, 1 },
  { 250, 0 },
  { 249, 2 },
  { 249, 1 },
  { 251, 0 },
  { 251, 2 },
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
#line 1757 "parse.c"
        break;
      case 7:
#line 102 "parse.y"
{ sqlite3BeginParse(pParse, 0); }
#line 1762 "parse.c"
        break;
      case 8:
#line 104 "parse.y"
{ sqlite3BeginParse(pParse, 1); }
#line 1767 "parse.c"
        break;
      case 9:
#line 105 "parse.y"
{ sqlite3BeginParse(pParse, 2); }
#line 1772 "parse.c"
        break;
      case 10:
#line 112 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_BEGIN);}
#line 1777 "parse.c"
        break;
      case 11:
#line 113 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_START);}
#line 1782 "parse.c"
        break;
      case 14:
#line 124 "parse.y"
{sqlite3CommitTransaction(pParse);}
#line 1787 "parse.c"
        break;
      case 15:
#line 126 "parse.y"
{sqlite3RollbackTransaction(pParse);}
#line 1792 "parse.c"
        break;
      case 17:
#line 131 "parse.y"
{
   sqlite3StartTable(pParse, 0, 0, 0, 0, 0);
}
#line 1799 "parse.c"
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
{yygotominor.yy4 = 0;}
#line 1814 "parse.c"
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
{yygotominor.yy4 = 1;}
#line 1826 "parse.c"
        break;
      case 22:
#line 143 "parse.y"
{
  //sqlite3EndTable(pParse,&X,&Y,0);
}
#line 1833 "parse.c"
        break;
      case 23:
#line 146 "parse.y"
{
  sqlite3EndTable(pParse,0,0,0);
  //sqlite3SelectDelete(S);
  yy_destructor(165,&yymsp[0].minor);
}
#line 1842 "parse.c"
        break;
      case 33:
#line 168 "parse.y"
{
  //A.z = X.z;
  //A.n = (pParse->sLastToken.z-X.z) + pParse->sLastToken.n;
}
#line 1850 "parse.c"
        break;
      case 34:
#line 172 "parse.y"
{
  //sqlite3AddColumn(pParse,&X);
  //A = X;
}
#line 1858 "parse.c"
        break;
      case 35:
      case 36:
      case 37:
      case 38:
      case 39:
      case 246:
#line 182 "parse.y"
{yygotominor.yy378 = yymsp[0].minor.yy0;}
#line 1868 "parse.c"
        break;
      case 41:
#line 241 "parse.y"
{ /*sqlite3AddColumnType(pParse,&X);*/ }
#line 1873 "parse.c"
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
{yygotominor.yy378 = yymsp[0].minor.yy378;}
#line 1886 "parse.c"
        break;
      case 43:
#line 243 "parse.y"
{
  yygotominor.yy378.z = yymsp[-3].minor.yy378.z;
  yygotominor.yy378.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-3].minor.yy378.z;
}
#line 1894 "parse.c"
        break;
      case 44:
#line 247 "parse.y"
{
  yygotominor.yy378.z = yymsp[-5].minor.yy378.z;
  yygotominor.yy378.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-5].minor.yy378.z;
}
#line 1902 "parse.c"
        break;
      case 46:
#line 253 "parse.y"
{yygotominor.yy378.z=yymsp[-1].minor.yy378.z; yygotominor.yy378.n=yymsp[0].minor.yy378.n+(yymsp[0].minor.yy378.z-yymsp[-1].minor.yy378.z);}
#line 1907 "parse.c"
        break;
      case 47:
#line 255 "parse.y"
{ yygotominor.yy4 = atoi((char*)yymsp[0].minor.yy378.z); }
#line 1912 "parse.c"
        break;
      case 48:
#line 256 "parse.y"
{ yygotominor.yy4 = -atoi((char*)yymsp[0].minor.yy378.z); }
#line 1917 "parse.c"
        break;
      case 53:
#line 265 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/   yy_destructor(180,&yymsp[0].minor);
}
#line 1923 "parse.c"
        break;
      case 54:
#line 266 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/ }
#line 1928 "parse.c"
        break;
      case 55:
#line 267 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/  yy_destructor(180,&yymsp[0].minor);
}
#line 1934 "parse.c"
        break;
      case 56:
#line 268 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_UMINUS, X, 0, 0);
  //sqlite3AddDefaultValue(pParse,p);
  yy_destructor(180,&yymsp[0].minor);
}
#line 1943 "parse.c"
        break;
      case 57:
#line 272 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_STRING, 0, 0, &X);
  //sqlite3AddDefaultValue(pParse,p);
}
#line 1951 "parse.c"
        break;
      case 60:
#line 282 "parse.y"
{/*sqlite3AddNotNull(pParse, R);*/}
#line 1956 "parse.c"
        break;
      case 61:
#line 284 "parse.y"
{/*sqlite3AddPrimaryKey(pParse,0,R,I,Z);*/}
#line 1961 "parse.c"
        break;
      case 62:
#line 285 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,0,R,0,0,0,0);*/}
#line 1966 "parse.c"
        break;
      case 63:
#line 286 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,X);*/  sqlite3ExprDelete(yymsp[-1].minor.yy314); }
#line 1971 "parse.c"
        break;
      case 64:
#line 288 "parse.y"
{/*sqlite3CreateForeignKey(pParse,0,&T,TA,R);*/ sqlite3ExprListDelete(yymsp[-1].minor.yy322); }
#line 1976 "parse.c"
        break;
      case 65:
#line 289 "parse.y"
{/*sqlite3DeferForeignKey(pParse,D);*/}
#line 1981 "parse.c"
        break;
      case 66:
#line 290 "parse.y"
{/*sqlite3AddCollateType(pParse, (char*)C.z, C.n);*/}
#line 1986 "parse.c"
        break;
      case 69:
#line 303 "parse.y"
{ yygotominor.yy4 = OE_Restrict * 0x010101; }
#line 1991 "parse.c"
        break;
      case 70:
#line 304 "parse.y"
{ yygotominor.yy4 = (yymsp[-1].minor.yy4 & yymsp[0].minor.yy215.mask) | yymsp[0].minor.yy215.value; }
#line 1996 "parse.c"
        break;
      case 71:
#line 306 "parse.y"
{ yygotominor.yy215.value = 0;     yygotominor.yy215.mask = 0x000000; }
#line 2001 "parse.c"
        break;
      case 72:
#line 307 "parse.y"
{ yygotominor.yy215.value = yymsp[0].minor.yy4;     yygotominor.yy215.mask = 0x0000ff; }
#line 2006 "parse.c"
        break;
      case 73:
#line 308 "parse.y"
{ yygotominor.yy215.value = yymsp[0].minor.yy4<<8;  yygotominor.yy215.mask = 0x00ff00; }
#line 2011 "parse.c"
        break;
      case 74:
#line 309 "parse.y"
{ yygotominor.yy215.value = yymsp[0].minor.yy4<<16; yygotominor.yy215.mask = 0xff0000; }
#line 2016 "parse.c"
        break;
      case 75:
#line 311 "parse.y"
{ yygotominor.yy4 = OE_SetNull; }
#line 2021 "parse.c"
        break;
      case 76:
#line 312 "parse.y"
{ yygotominor.yy4 = OE_SetDflt; }
#line 2026 "parse.c"
        break;
      case 77:
#line 313 "parse.y"
{ yygotominor.yy4 = OE_Cascade; }
#line 2031 "parse.c"
        break;
      case 78:
#line 314 "parse.y"
{ yygotominor.yy4 = OE_Restrict; }
#line 2036 "parse.c"
        break;
      case 79:
      case 80:
      case 95:
      case 97:
      case 98:
#line 316 "parse.y"
{yygotominor.yy4 = yymsp[0].minor.yy4;}
#line 2045 "parse.c"
        break;
      case 90:
#line 335 "parse.y"
{ sqlite3ExprListDelete(yymsp[-3].minor.yy322); }
#line 2050 "parse.c"
        break;
      case 91:
#line 337 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,yymsp[-2].minor.yy322,R,0,0,0,0);*/ sqlite3ExprListDelete(yymsp[-2].minor.yy322);}
#line 2055 "parse.c"
        break;
      case 92:
#line 338 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,yymsp[-2].minor.yy314);*/ sqlite3ExprDelete(yymsp[-2].minor.yy314);}
#line 2060 "parse.c"
        break;
      case 93:
#line 340 "parse.y"
{ 
        sqlite3ExprListDelete(yymsp[-6].minor.yy322);
        sqlite3ExprListDelete(yymsp[-2].minor.yy322);
 }
#line 2068 "parse.c"
        break;
      case 96:
#line 355 "parse.y"
{yygotominor.yy4 = OE_Default;}
#line 2073 "parse.c"
        break;
      case 99:
#line 360 "parse.y"
{yygotominor.yy4 = OE_Ignore;}
#line 2078 "parse.c"
        break;
      case 100:
      case 170:
#line 361 "parse.y"
{yygotominor.yy4 = OE_Replace;}
#line 2084 "parse.c"
        break;
      case 101:
#line 365 "parse.y"
{
  sqlite3DropTable(pParse, yymsp[0].minor.yy259, 0, yymsp[-1].minor.yy4);
}
#line 2091 "parse.c"
        break;
      case 104:
#line 385 "parse.y"
{
  sqlite3Select(pParse, yymsp[0].minor.yy387, SRT_Callback, 0, 0, 0, 0, 0);
  // sqlite3SelectDelete(yymsp[0].minor.yy387);
}
#line 2099 "parse.c"
        break;
      case 105:
      case 128:
#line 395 "parse.y"
{yygotominor.yy387 = yymsp[0].minor.yy387;}
#line 2105 "parse.c"
        break;
      case 106:
#line 397 "parse.y"
{
  if( yymsp[0].minor.yy387 ){
    yymsp[0].minor.yy387->op = yymsp[-1].minor.yy4;
    yymsp[0].minor.yy387->pPrior = yymsp[-2].minor.yy387;
  }
  yygotominor.yy387 = yymsp[0].minor.yy387;
}
#line 2116 "parse.c"
        break;
      case 107:
      case 109:
#line 405 "parse.y"
{yygotominor.yy4 = yymsp[0].major;}
#line 2122 "parse.c"
        break;
      case 108:
#line 406 "parse.y"
{yygotominor.yy4 = TK_ALL;}
#line 2127 "parse.c"
        break;
      case 110:
#line 410 "parse.y"
{
  yygotominor.yy387 = sqlite3SelectNew(yymsp[-6].minor.yy322,yymsp[-5].minor.yy259,yymsp[-4].minor.yy314,yymsp[-3].minor.yy322,yymsp[-2].minor.yy314,yymsp[-1].minor.yy322,yymsp[-7].minor.yy4,yymsp[0].minor.yy292.pLimit,yymsp[0].minor.yy292.pOffset);
}
#line 2134 "parse.c"
        break;
      case 114:
      case 240:
#line 431 "parse.y"
{yygotominor.yy322 = yymsp[-1].minor.yy322;}
#line 2140 "parse.c"
        break;
      case 115:
      case 141:
      case 151:
      case 239:
#line 432 "parse.y"
{yygotominor.yy322 = 0;}
#line 2148 "parse.c"
        break;
      case 116:
#line 433 "parse.y"
{
   yygotominor.yy322 = sqlite3ExprListAppend(yymsp[-2].minor.yy322,yymsp[-1].minor.yy314,yymsp[0].minor.yy378.n?&yymsp[0].minor.yy378:0);
}
#line 2155 "parse.c"
        break;
      case 117:
#line 436 "parse.y"
{
  yygotominor.yy322 = sqlite3ExprListAppend(yymsp[-1].minor.yy322, sqlite3Expr(TK_ALL, 0, 0, 0), 0);
}
#line 2162 "parse.c"
        break;
      case 118:
#line 439 "parse.y"
{
  Expr *pRight = sqlite3Expr(TK_ALL, 0, 0, 0);
  Expr *pLeft = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy378);
  yygotominor.yy322 = sqlite3ExprListAppend(yymsp[-3].minor.yy322, sqlite3Expr(TK_DOT, pLeft, pRight, 0), 0);
}
#line 2171 "parse.c"
        break;
      case 121:
#line 451 "parse.y"
{yygotominor.yy378.n = 0;}
#line 2176 "parse.c"
        break;
      case 122:
#line 463 "parse.y"
{yygotominor.yy259 = sqliteMalloc(sizeof(*yygotominor.yy259));}
#line 2181 "parse.c"
        break;
      case 123:
#line 464 "parse.y"
{yygotominor.yy259 = yymsp[0].minor.yy259;}
#line 2186 "parse.c"
        break;
      case 124:
#line 469 "parse.y"
{
   yygotominor.yy259 = yymsp[-1].minor.yy259;
   if( yygotominor.yy259 && yygotominor.yy259->nSrc>0 ) yygotominor.yy259->a[yygotominor.yy259->nSrc-1].jointype = yymsp[0].minor.yy4;
}
#line 2194 "parse.c"
        break;
      case 125:
#line 473 "parse.y"
{yygotominor.yy259 = 0;}
#line 2199 "parse.c"
        break;
      case 126:
#line 474 "parse.y"
{
  yygotominor.yy259 = sqlite3SrcListAppend(yymsp[-5].minor.yy259,&yymsp[-4].minor.yy378,&yymsp[-3].minor.yy378);
  if( yymsp[-2].minor.yy378.n ) sqlite3SrcListAddAlias(yygotominor.yy259,&yymsp[-2].minor.yy378);
  if( yymsp[-1].minor.yy314 ){
    if( yygotominor.yy259 && yygotominor.yy259->nSrc>1 ){ yygotominor.yy259->a[yygotominor.yy259->nSrc-2].pOn = yymsp[-1].minor.yy314; }
    else { sqlite3ExprDelete(yymsp[-1].minor.yy314); }
  }
  if( yymsp[0].minor.yy384 ){
    if( yygotominor.yy259 && yygotominor.yy259->nSrc>1 ){ yygotominor.yy259->a[yygotominor.yy259->nSrc-2].pUsing = yymsp[0].minor.yy384; }
    else { sqlite3IdListDelete(yymsp[0].minor.yy384); }
  }
}
#line 2215 "parse.c"
        break;
      case 127:
#line 488 "parse.y"
{
    yygotominor.yy259 = sqlite3SrcListAppend(yymsp[-6].minor.yy259,0,0);
    yygotominor.yy259->a[yygotominor.yy259->nSrc-1].pSelect = yymsp[-4].minor.yy387;
    if( yymsp[-2].minor.yy378.n ) sqlite3SrcListAddAlias(yygotominor.yy259,&yymsp[-2].minor.yy378);
    if( yymsp[-1].minor.yy314 ){
      if( yygotominor.yy259 && yygotominor.yy259->nSrc>1 ){ yygotominor.yy259->a[yygotominor.yy259->nSrc-2].pOn = yymsp[-1].minor.yy314; }
      else { sqlite3ExprDelete(yymsp[-1].minor.yy314); }
    }
    if( yymsp[0].minor.yy384 ){
      if( yygotominor.yy259 && yygotominor.yy259->nSrc>1 ){ yygotominor.yy259->a[yygotominor.yy259->nSrc-2].pUsing = yymsp[0].minor.yy384; }
      else { sqlite3IdListDelete(yymsp[0].minor.yy384); }
    }
  }
#line 2232 "parse.c"
        break;
      case 129:
#line 509 "parse.y"
{
     yygotominor.yy387 = sqlite3SelectNew(0,yymsp[0].minor.yy259,0,0,0,0,0,0,0);
  }
#line 2239 "parse.c"
        break;
      case 130:
#line 515 "parse.y"
{yygotominor.yy378.z=0; yygotominor.yy378.n=0;}
#line 2244 "parse.c"
        break;
      case 132:
#line 520 "parse.y"
{yygotominor.yy259 = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy378,&yymsp[0].minor.yy378);}
#line 2249 "parse.c"
        break;
      case 133:
#line 524 "parse.y"
{ yygotominor.yy4 = JT_INNER; }
#line 2254 "parse.c"
        break;
      case 134:
#line 525 "parse.y"
{ yygotominor.yy4 = sqlite3JoinType(pParse,&yymsp[-1].minor.yy0,0,0); }
#line 2259 "parse.c"
        break;
      case 135:
#line 526 "parse.y"
{ yygotominor.yy4 = sqlite3JoinType(pParse,&yymsp[-2].minor.yy0,&yymsp[-1].minor.yy378,0); }
#line 2264 "parse.c"
        break;
      case 136:
#line 528 "parse.y"
{ yygotominor.yy4 = sqlite3JoinType(pParse,&yymsp[-3].minor.yy0,&yymsp[-2].minor.yy378,&yymsp[-1].minor.yy378); }
#line 2269 "parse.c"
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
{yygotominor.yy314 = yymsp[0].minor.yy314;}
#line 2282 "parse.c"
        break;
      case 138:
      case 153:
      case 160:
      case 208:
      case 232:
      case 234:
      case 238:
#line 533 "parse.y"
{yygotominor.yy314 = 0;}
#line 2293 "parse.c"
        break;
      case 139:
      case 178:
#line 537 "parse.y"
{yygotominor.yy384 = yymsp[-1].minor.yy384;}
#line 2299 "parse.c"
        break;
      case 140:
      case 176:
      case 177:
#line 538 "parse.y"
{yygotominor.yy384 = 0;}
#line 2306 "parse.c"
        break;
      case 142:
      case 152:
#line 549 "parse.y"
{yygotominor.yy322 = yymsp[0].minor.yy322;}
#line 2312 "parse.c"
        break;
      case 143:
#line 550 "parse.y"
{
  yygotominor.yy322 = sqlite3ExprListAppend(yymsp[-4].minor.yy322,yymsp[-2].minor.yy314,yymsp[-1].minor.yy378.n>0?&yymsp[-1].minor.yy378:0);
  if( yygotominor.yy322 ) yygotominor.yy322->a[yygotominor.yy322->nExpr-1].sortOrder = yymsp[0].minor.yy4;
}
#line 2320 "parse.c"
        break;
      case 144:
#line 554 "parse.y"
{
  yygotominor.yy322 = sqlite3ExprListAppend(0,yymsp[-2].minor.yy314,yymsp[-1].minor.yy378.n>0?&yymsp[-1].minor.yy378:0);
  if( yygotominor.yy322 && yygotominor.yy322->a ) yygotominor.yy322->a[0].sortOrder = yymsp[0].minor.yy4;
}
#line 2328 "parse.c"
        break;
      case 146:
      case 148:
#line 563 "parse.y"
{yygotominor.yy4 = SQLITE_SO_ASC;}
#line 2334 "parse.c"
        break;
      case 147:
#line 564 "parse.y"
{yygotominor.yy4 = SQLITE_SO_DESC;}
#line 2339 "parse.c"
        break;
      case 149:
#line 566 "parse.y"
{yygotominor.yy378.z = 0; yygotominor.yy378.n = 0;}
#line 2344 "parse.c"
        break;
      case 155:
#line 584 "parse.y"
{yygotominor.yy292.pLimit = 0; yygotominor.yy292.pOffset = 0;}
#line 2349 "parse.c"
        break;
      case 156:
#line 585 "parse.y"
{yygotominor.yy292.pLimit = yymsp[0].minor.yy314; yygotominor.yy292.pOffset = 0;}
#line 2354 "parse.c"
        break;
      case 157:
#line 587 "parse.y"
{yygotominor.yy292.pLimit = yymsp[-2].minor.yy314; yygotominor.yy292.pOffset = yymsp[0].minor.yy314;}
#line 2359 "parse.c"
        break;
      case 158:
#line 589 "parse.y"
{yygotominor.yy292.pOffset = yymsp[-2].minor.yy314; yygotominor.yy292.pLimit = yymsp[0].minor.yy314;}
#line 2364 "parse.c"
        break;
      case 159:
#line 593 "parse.y"
{sqlite3DeleteFrom(pParse,yymsp[-2].minor.yy259,yymsp[-1].minor.yy314, yymsp[0].minor.yy292.pLimit, yymsp[0].minor.yy292.pOffset);}
#line 2369 "parse.c"
        break;
      case 162:
#line 605 "parse.y"
{sqlite3Update(pParse,yymsp[-4].minor.yy259,yymsp[-2].minor.yy322,yymsp[-1].minor.yy314,OE_Default, yymsp[0].minor.yy292.pLimit, yymsp[0].minor.yy292.pOffset);}
#line 2374 "parse.c"
        break;
      case 163:
#line 611 "parse.y"
{yygotominor.yy322 = sqlite3ExprListAppend(yymsp[-4].minor.yy322,yymsp[0].minor.yy314,&yymsp[-2].minor.yy378);}
#line 2379 "parse.c"
        break;
      case 164:
#line 612 "parse.y"
{yygotominor.yy322 = sqlite3ExprListAppend(0,yymsp[0].minor.yy314,&yymsp[-2].minor.yy378);}
#line 2384 "parse.c"
        break;
      case 165:
#line 621 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy259, 0, yymsp[0].minor.yy287, 0, yymsp[-2].minor.yy384, yymsp[-5].minor.yy4);}
#line 2389 "parse.c"
        break;
      case 166:
#line 625 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy259, yymsp[0].minor.yy322, 0, 0, yymsp[-2].minor.yy384, yymsp[-5].minor.yy4);}
#line 2394 "parse.c"
        break;
      case 167:
#line 629 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy259, yymsp[0].minor.yy322, 0, 0, yymsp[-2].minor.yy384, yymsp[-4].minor.yy4);}
#line 2399 "parse.c"
        break;
      case 168:
#line 632 "parse.y"
{sqlite3Insert(pParse, yymsp[-2].minor.yy259, 0, 0, yymsp[0].minor.yy387, yymsp[-1].minor.yy384, yymsp[-4].minor.yy4);}
#line 2404 "parse.c"
        break;
      case 169:
#line 636 "parse.y"
{ yygotominor.yy4 = OE_Default; }
#line 2409 "parse.c"
        break;
      case 171:
#line 642 "parse.y"
{ yygotominor.yy287 = sqlite3ValuesListAppend(yymsp[-4].minor.yy287, yymsp[-1].minor.yy322);}
#line 2414 "parse.c"
        break;
      case 172:
#line 643 "parse.y"
{ yygotominor.yy287 = sqlite3ValuesListAppend(0, yymsp[-1].minor.yy322); }
#line 2419 "parse.c"
        break;
      case 173:
#line 644 "parse.y"
{ yygotominor.yy287 = 0; }
#line 2424 "parse.c"
        break;
      case 174:
      case 235:
#line 649 "parse.y"
{yygotominor.yy322 = sqlite3ExprListAppend(yymsp[-2].minor.yy322,yymsp[0].minor.yy314,0);}
#line 2430 "parse.c"
        break;
      case 175:
      case 236:
#line 650 "parse.y"
{yygotominor.yy322 = sqlite3ExprListAppend(0,yymsp[0].minor.yy314,0);}
#line 2436 "parse.c"
        break;
      case 179:
#line 660 "parse.y"
{yygotominor.yy384 = sqlite3IdListAppend(yymsp[-2].minor.yy384,&yymsp[0].minor.yy378);}
#line 2441 "parse.c"
        break;
      case 180:
#line 661 "parse.y"
{yygotominor.yy384 = sqlite3IdListAppend(0,&yymsp[0].minor.yy378);}
#line 2446 "parse.c"
        break;
      case 182:
#line 672 "parse.y"
{yygotominor.yy314 = yymsp[-1].minor.yy314; sqlite3ExprSpan(yygotominor.yy314,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0); }
#line 2451 "parse.c"
        break;
      case 183:
      case 188:
      case 189:
#line 673 "parse.y"
{yygotominor.yy314 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0);}
#line 2458 "parse.c"
        break;
      case 184:
      case 185:
#line 674 "parse.y"
{yygotominor.yy314 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy0);}
#line 2464 "parse.c"
        break;
      case 186:
#line 676 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy378);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy378);
  yygotominor.yy314 = sqlite3Expr(TK_DOT, temp1, temp2, 0);
}
#line 2473 "parse.c"
        break;
      case 187:
#line 681 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-4].minor.yy378);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy378);
  Expr *temp3 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy378);
  Expr *temp4 = sqlite3Expr(TK_DOT, temp2, temp3, 0);
  yygotominor.yy314 = sqlite3Expr(TK_DOT, temp1, temp4, 0);
}
#line 2484 "parse.c"
        break;
      case 190:
#line 690 "parse.y"
{yygotominor.yy314 = sqlite3RegisterExpr(pParse, &yymsp[0].minor.yy0);}
#line 2489 "parse.c"
        break;
      case 191:
      case 192:
#line 691 "parse.y"
{
  Token *pToken = &yymsp[0].minor.yy0;
  Expr *pExpr = yygotominor.yy314 = sqlite3Expr(TK_VARIABLE, 0, 0, pToken);
  //sqlite3ExprAssignVarNumber(pParse, pExpr);
}
#line 2499 "parse.c"
        break;
      case 193:
#line 702 "parse.y"
{
  yygotominor.yy314 = sqlite3Expr(TK_CAST, yymsp[-3].minor.yy314, 0, &yymsp[-1].minor.yy378);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-5].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2507 "parse.c"
        break;
      case 194:
#line 707 "parse.y"
{
  yygotominor.yy314 = sqlite3ExprFunction(yymsp[-1].minor.yy322, &yymsp[-4].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-4].minor.yy0,&yymsp[0].minor.yy0);
  if( yymsp[-2].minor.yy4 && yygotominor.yy314 ){
    yygotominor.yy314->flags |= EP_Distinct;
  }
}
#line 2518 "parse.c"
        break;
      case 195:
#line 714 "parse.y"
{
  yygotominor.yy314 = sqlite3ExprFunction(0, &yymsp[-3].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2526 "parse.c"
        break;
      case 196:
#line 718 "parse.y"
{
  /* The CURRENT_TIME, CURRENT_DATE, and CURRENT_TIMESTAMP values are
  ** treated as functions that return constants */
  yygotominor.yy314 = sqlite3ExprFunction(0,&yymsp[0].minor.yy0);
  if( yygotominor.yy314 ) yygotominor.yy314->op = TK_CONST_FUNC;  
}
#line 2536 "parse.c"
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
{yygotominor.yy314 = sqlite3Expr(yymsp[-1].major, yymsp[-2].minor.yy314, yymsp[0].minor.yy314, 0);}
#line 2548 "parse.c"
        break;
      case 205:
#line 734 "parse.y"
{yygotominor.yy342.eOperator = yymsp[0].minor.yy0; yygotominor.yy342.not = 0;}
#line 2553 "parse.c"
        break;
      case 206:
#line 735 "parse.y"
{yygotominor.yy342.eOperator = yymsp[0].minor.yy0; yygotominor.yy342.not = 1;}
#line 2558 "parse.c"
        break;
      case 209:
#line 740 "parse.y"
{
  ExprList *pList;
  pList = sqlite3ExprListAppend(0, yymsp[-3].minor.yy314, 0);
  pList = sqlite3ExprListAppend(pList, yymsp[-1].minor.yy314, 0);
  if( yymsp[0].minor.yy314 ){
    pList = sqlite3ExprListAppend(pList, yymsp[0].minor.yy314, 0);
  }
  //yygotominor.yy314 = sqlite3ExprFunction(pList, &yymsp[-2].minor.yy342.eOperator);
  yygotominor.yy314 = sqlite3ExprLikeOp(pList, &yymsp[-2].minor.yy342.eOperator);
  if( yymsp[-2].minor.yy342.not ) yygotominor.yy314 = sqlite3Expr(TK_NOT, yygotominor.yy314, 0, 0);
  sqlite3ExprSpan(yygotominor.yy314, &yymsp[-3].minor.yy314->span, &yymsp[-1].minor.yy314->span);
}
#line 2574 "parse.c"
        break;
      case 210:
#line 753 "parse.y"
{
  yygotominor.yy314 = sqlite3Expr(yymsp[0].major, yymsp[-1].minor.yy314, 0, 0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-1].minor.yy314->span,&yymsp[0].minor.yy0);
}
#line 2582 "parse.c"
        break;
      case 211:
#line 757 "parse.y"
{
  yygotominor.yy314 = sqlite3Expr(TK_ISNULL, yymsp[-2].minor.yy314, 0, 0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-2].minor.yy314->span,&yymsp[0].minor.yy0);
}
#line 2590 "parse.c"
        break;
      case 212:
#line 761 "parse.y"
{
  yygotominor.yy314 = sqlite3Expr(TK_NOTNULL, yymsp[-2].minor.yy314, 0, 0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-2].minor.yy314->span,&yymsp[0].minor.yy0);
}
#line 2598 "parse.c"
        break;
      case 213:
#line 765 "parse.y"
{
  yygotominor.yy314 = sqlite3Expr(TK_NOTNULL, yymsp[-3].minor.yy314, 0, 0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-3].minor.yy314->span,&yymsp[0].minor.yy0);
}
#line 2606 "parse.c"
        break;
      case 214:
#line 769 "parse.y"
{
  yygotominor.yy314 = sqlite3Expr(yymsp[-1].major, yymsp[0].minor.yy314, 0, 0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy314->span);
}
#line 2614 "parse.c"
        break;
      case 215:
#line 773 "parse.y"
{
  yygotominor.yy314 = sqlite3Expr(TK_UMINUS, yymsp[0].minor.yy314, 0, 0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy314->span);
}
#line 2622 "parse.c"
        break;
      case 216:
#line 777 "parse.y"
{
  yygotominor.yy314 = sqlite3Expr(TK_UPLUS, yymsp[0].minor.yy314, 0, 0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy314->span);
}
#line 2630 "parse.c"
        break;
      case 219:
#line 788 "parse.y"
{ yygotominor.yy314 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0); }
#line 2635 "parse.c"
        break;
      case 220:
#line 791 "parse.y"
{
  ExprList *pList = sqlite3ExprListAppend(0, yymsp[-2].minor.yy314, 0);
  pList = sqlite3ExprListAppend(pList, yymsp[0].minor.yy314, 0);
  yygotominor.yy314 = sqlite3Expr(TK_BETWEEN, yymsp[-4].minor.yy314, 0, 0);
  if( yygotominor.yy314 ){
    yygotominor.yy314->pList = pList;
  }else{
    sqlite3ExprListDelete(pList);
  } 
  if( yymsp[-3].minor.yy4 ) yygotominor.yy314 = sqlite3Expr(TK_NOT, yygotominor.yy314, 0, 0);
  sqlite3ExprSpan(yygotominor.yy314,&yymsp[-4].minor.yy314->span,&yymsp[0].minor.yy314->span);
}
#line 2651 "parse.c"
        break;
      case 223:
#line 807 "parse.y"
{
    yygotominor.yy314 = sqlite3Expr(TK_IN, yymsp[-4].minor.yy314, 0, 0);
    if( yygotominor.yy314 ){
      yygotominor.yy314->pList = yymsp[-1].minor.yy322;
    }else{
      sqlite3ExprListDelete(yymsp[-1].minor.yy322);
    }
    if( yymsp[-3].minor.yy4 ) yygotominor.yy314 = sqlite3Expr(TK_NOT, yygotominor.yy314, 0, 0);
    sqlite3ExprSpan(yygotominor.yy314,&yymsp[-4].minor.yy314->span,&yymsp[0].minor.yy0);
  }
#line 2665 "parse.c"
        break;
      case 224:
#line 817 "parse.y"
{
    yygotominor.yy314 = sqlite3Expr(TK_SELECT, 0, 0, 0);
    if( yygotominor.yy314 ){
      yygotominor.yy314->pSelect = yymsp[-1].minor.yy387;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy387);
    }
    sqlite3ExprSpan(yygotominor.yy314,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0);
  }
#line 2678 "parse.c"
        break;
      case 225:
#line 826 "parse.y"
{
    yygotominor.yy314 = sqlite3Expr(TK_IN, yymsp[-4].minor.yy314, 0, 0);
    if( yygotominor.yy314 ){
      yygotominor.yy314->pSelect = yymsp[-1].minor.yy387;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy387);
    }
    if( yymsp[-3].minor.yy4 ) yygotominor.yy314 = sqlite3Expr(TK_NOT, yygotominor.yy314, 0, 0);
    sqlite3ExprSpan(yygotominor.yy314,&yymsp[-4].minor.yy314->span,&yymsp[0].minor.yy0);
  }
#line 2692 "parse.c"
        break;
      case 226:
#line 836 "parse.y"
{
    SrcList *pSrc = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy378,&yymsp[0].minor.yy378);
    yygotominor.yy314 = sqlite3Expr(TK_IN, yymsp[-3].minor.yy314, 0, 0);
    if( yygotominor.yy314 ){
      yygotominor.yy314->pSelect = sqlite3SelectNew(0,pSrc,0,0,0,0,0,0,0);
    }else{
      sqlite3SrcListDelete(pSrc);
    }
    if( yymsp[-2].minor.yy4 ) yygotominor.yy314 = sqlite3Expr(TK_NOT, yygotominor.yy314, 0, 0);
    sqlite3ExprSpan(yygotominor.yy314,&yymsp[-3].minor.yy314->span,yymsp[0].minor.yy378.z?&yymsp[0].minor.yy378:&yymsp[-1].minor.yy378);
  }
#line 2707 "parse.c"
        break;
      case 227:
#line 847 "parse.y"
{
    Expr *p = yygotominor.yy314 = sqlite3Expr(TK_EXISTS, 0, 0, 0);
    if( p ){
      p->pSelect = yymsp[-1].minor.yy387;
      sqlite3ExprSpan(p,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy387);
    }
  }
#line 2720 "parse.c"
        break;
      case 228:
#line 859 "parse.y"
{
  yygotominor.yy314 = sqlite3Expr(TK_CASE, yymsp[-3].minor.yy314, yymsp[-1].minor.yy314, 0);
  if( yygotominor.yy314 ){
    yygotominor.yy314->pList = yymsp[-2].minor.yy322;
  }else{
    sqlite3ExprListDelete(yymsp[-2].minor.yy322);
  }
  sqlite3ExprSpan(yygotominor.yy314, &yymsp[-4].minor.yy0, &yymsp[0].minor.yy0);
}
#line 2733 "parse.c"
        break;
      case 229:
#line 870 "parse.y"
{
  yygotominor.yy322 = sqlite3ExprListAppend(yymsp[-4].minor.yy322, yymsp[-2].minor.yy314, 0);
  yygotominor.yy322 = sqlite3ExprListAppend(yygotominor.yy322, yymsp[0].minor.yy314, 0);
}
#line 2741 "parse.c"
        break;
      case 230:
#line 874 "parse.y"
{
  yygotominor.yy322 = sqlite3ExprListAppend(0, yymsp[-2].minor.yy314, 0);
  yygotominor.yy322 = sqlite3ExprListAppend(yygotominor.yy322, yymsp[0].minor.yy314, 0);
}
#line 2749 "parse.c"
        break;
      case 241:
#line 918 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy378.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy378.z, yymsp[-1].minor.yy378.n);
  }
  yygotominor.yy322 = sqlite3ExprListAppend(yymsp[-4].minor.yy322, p, &yymsp[-2].minor.yy378);
  if( yygotominor.yy322 ) yygotominor.yy322->a[yygotominor.yy322->nExpr-1].sortOrder = yymsp[0].minor.yy4;
}
#line 2762 "parse.c"
        break;
      case 242:
#line 927 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy378.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy378.z, yymsp[-1].minor.yy378.n);
  }
  yygotominor.yy322 = sqlite3ExprListAppend(0, p, &yymsp[-2].minor.yy378);
  if( yygotominor.yy322 ) yygotominor.yy322->a[yygotominor.yy322->nExpr-1].sortOrder = yymsp[0].minor.yy4;
}
#line 2775 "parse.c"
        break;
      case 249:
#line 1058 "parse.y"
{yygotominor.yy4 = OE_Rollback;}
#line 2780 "parse.c"
        break;
      case 250:
#line 1059 "parse.y"
{yygotominor.yy4 = OE_Abort;}
#line 2785 "parse.c"
        break;
      case 251:
#line 1060 "parse.y"
{yygotominor.yy4 = OE_Fail;}
#line 2790 "parse.c"
        break;
      case 252:
#line 1116 "parse.y"
{
    sqlite3SetStatement(pParse, yymsp[0].minor.yy322, 0, SQLTYPE_SET);
}
#line 2797 "parse.c"
        break;
      case 253:
#line 1120 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy378, SQLTYPE_SET_NAMES);   
}
#line 2804 "parse.c"
        break;
      case 254:
#line 1124 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy378, SQLTYPE_SET_CHARACTER_SET);
}
#line 2811 "parse.c"
        break;
      case 255:
#line 1130 "parse.y"
{
    yygotominor.yy322 = sqlite3ExprListAppend(yymsp[-5].minor.yy322, yymsp[0].minor.yy314, &yymsp[-2].minor.yy378);
}
#line 2818 "parse.c"
        break;
      case 256:
#line 1134 "parse.y"
{
    yygotominor.yy322 = sqlite3ExprListAppend(0, yymsp[0].minor.yy314, &yymsp[-2].minor.yy378);                         
}
#line 2825 "parse.c"
        break;
      case 260:
#line 1142 "parse.y"
{ sqlite3CheckSetScope(pParse, &yymsp[-1].minor.yy0); }
#line 2830 "parse.c"
        break;
      case 262:
#line 1146 "parse.y"
{ yygotominor.yy378 = yymsp[0].minor.yy378; }
#line 2835 "parse.c"
        break;
      case 263:
#line 1147 "parse.y"
{ yygotominor.yy378 = yymsp[0].minor.yy0; }
#line 2840 "parse.c"
        break;
      case 269:
#line 1156 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_DATABASES);
}
#line 2847 "parse.c"
        break;
      case 270:
#line 1160 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_TABLES);
}
#line 2854 "parse.c"
        break;
      case 271:
#line 1164 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_TABLE_STATUS);
}
#line 2861 "parse.c"
        break;
      case 272:
#line 1168 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_VARIABLES);
}
#line 2868 "parse.c"
        break;
      case 273:
#line 1172 "parse.y"
{
    sqlite3ShowStatement(pParse, SHOWTYPE_SHOW_COLLATION);              
}
#line 2875 "parse.c"
        break;
      case 277:
#line 1180 "parse.y"
{
    if (yymsp[0].minor.yy314) {
        sqlite3ExprDelete(yymsp[0].minor.yy314);
    }
}
#line 2884 "parse.c"
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
#line 2951 "parse.c"
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
