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
#define YYNSTATE 484
#define YYNRULE 268
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
 /*     0 */   228,  753,  102,  483,  441,  141,    1,  358,   56,   55,
 /*    10 */    55,   55,   55,  436,   57,   57,   57,   57,   58,   58,
 /*    20 */    59,   59,   59,   60,   62,   57,   57,   57,   57,   58,
 /*    30 */    58,   59,   59,   59,   60,  371,   57,   57,   57,   57,
 /*    40 */    58,   58,   59,   59,   59,   60,   58,   58,   59,   59,
 /*    50 */    59,   60,   54,   52,  236,  379,  382,  376,  376,   56,
 /*    60 */    55,   55,   55,   55,  161,   57,   57,   57,   57,   58,
 /*    70 */    58,   59,   59,   59,   60,  228,   60,  260,  358,  303,
 /*    80 */   232,   71,  125,   56,  175,  304,  470,  471,  472,   98,
 /*    90 */   414,  370,  208,  232,  443,  260,  438,  348,   24,  260,
 /*   100 */   323,  358,   17,  324,  435,  208,  310,  307,  247,  311,
 /*   110 */   371,  432,  159,  124,   51,  348,   30,  349,  439,  348,
 /*   120 */    42,  154,  352,  366,  164,  123,  453,   54,   52,  236,
 /*   130 */   379,  382,  376,  376,   56,   55,   55,   55,   55,  409,
 /*   140 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   150 */   228,  430,  354,  354,  354,   93,  349,  440,   56,  325,
 /*   160 */   134,  329,  184,  256,  188,  257,  145,  244,   16,  195,
 /*   170 */   118,  209,  358,  260,  329,  184,  256,  188,  257,  145,
 /*   180 */   267,  297,  384,  384,  209,  371,  452,  150,  405,  113,
 /*   190 */   279,  282,  283,  348,   29,  235,  361,  362,  238,  284,
 /*   200 */   476,  477,   54,   52,  236,  379,  382,  376,  376,   56,
 /*   210 */    55,   55,   55,   55,  380,   57,   57,   57,   57,   58,
 /*   220 */    58,   59,   59,   59,   60,  228,  451,  411,  419,  206,
 /*   230 */   326,  327,  150,   56,  450,  279,  282,  283,   61,  393,
 /*   240 */   165,  260,  126,  277,  284,   61,  260,  165,  380,  126,
 /*   250 */   389,  260,  141,  150,  358,  400,  279,  282,  283,  163,
 /*   260 */   371,  348,   29,  348,    3,  284,  348,   29,  143,  301,
 /*   270 */   116,  348,   35,  263,  361,  362,  161,   54,   52,  236,
 /*   280 */   379,  382,  376,  376,   56,   55,   55,   55,   55,  223,
 /*   290 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   300 */   228,  260,  385,  349,  239,  444,  127,  386,   56,  273,
 /*   310 */   405,  271,  199,  260,  287,  144,  131,  325,  390,  260,
 /*   320 */   276,  348,   29,  390,  443,  358,  181,    2,  129,  189,
 /*   330 */   454,  325,   17,  348,   42,  371,  325,  163,    9,  348,
 /*   340 */    35,  349,  325,  225,  325,   67,  368,  442,  138,  201,
 /*   350 */   146,  400,   54,   52,  236,  379,  382,  376,  376,   56,
 /*   360 */    55,   55,   55,   55,  237,   57,   57,   57,   57,   58,
 /*   370 */    58,   59,   59,   59,   60,  228,  335,  196,  390,  415,
 /*   380 */   197,  245,  130,   56,   59,   59,   59,   60,  326,  327,
 /*   390 */   468,  325,  267,  336,  384,  384,  274,  267,  343,  384,
 /*   400 */   384,  229,  326,  327,  372,  209,  344,  326,  327,  337,
 /*   410 */   371,  333,  401,  326,  327,  326,  327,   61,  156,  165,
 /*   420 */    70,  126,  334,  430,  374,  375,  405,   54,   52,  236,
 /*   430 */   379,  382,  376,  376,   56,   55,   55,   55,   55,  402,
 /*   440 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   450 */   228,  373,  260,  349,  418,  413,  241,  328,   56,  303,
 /*   460 */   260,  302,  326,  327,  432,  203,  470,  471,  472,  260,
 /*   470 */   115,  260,  348,   25,  260,  267,  260,  384,  384,  260,
 /*   480 */   348,   20,  368,  264,  138,  371,  484,  310,  307,  348,
 /*   490 */    28,  348,   47,  146,  348,   21,  348,   45,  200,  348,
 /*   500 */    84,  207,   54,   52,  236,  379,  382,  376,  376,   56,
 /*   510 */    55,   55,   55,   55,  260,   57,   57,   57,   57,   58,
 /*   520 */    58,   59,   59,   59,   60,  228,  260,  347,  260,  437,
 /*   530 */   260,  346,  260,   56,  348,   82,  260,  430,  260,  430,
 /*   540 */    66,  260,   68,  260,  229,  260,  348,   86,  348,   87,
 /*   550 */   348,   94,  348,   95,  135,  260,  348,   15,  348,   85,
 /*   560 */   371,  348,   46,  348,   96,  348,   97,   18,  106,  430,
 /*   570 */   173,  358,  242,  140,  131,  348,   22,   54,   52,  236,
 /*   580 */   379,  382,  376,  376,   56,   55,   55,   55,   55,  260,
 /*   590 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   600 */   228,  260,  243,  260,  212,  260,  358,  260,   56,  348,
 /*   610 */    31,  398,  260,  331,  332,  207,  260,  207,  260,  261,
 /*   620 */   260,  348,   32,  348,   23,  348,   33,  348,   34,  260,
 /*   630 */    99,  309,  348,   36,    1,  371,  348,   37,  348,   38,
 /*   640 */   348,   26,  358,  446,  481,  409,  468,  207,  296,  348,
 /*   650 */    27,  520,   54,   52,  236,  379,  382,  376,  376,   56,
 /*   660 */    55,   55,   55,   55,  260,   57,   57,   57,   57,   58,
 /*   670 */    58,   59,   59,   59,   60,  228,  260,  358,  260,  240,
 /*   680 */   260,  278,  260,   56,  348,   39,  218,  424,  128,  147,
 /*   690 */   148,  149,  296,  478,  478,  155,  348,   40,  348,   41,
 /*   700 */   348,   43,  348,   44,  246,  347,  120,  364,  364,  346,
 /*   710 */   371,  425,  174,  218,  218,  469,  218,  305,  158,  250,
 /*   720 */   265,  231,  152,  349,  252,  458,  183,   54,   52,  236,
 /*   730 */   379,  382,  376,  376,   56,   55,   55,   55,   55,    5,
 /*   740 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   750 */   228,  185,  219,  294,  162,  222,  300,  349,   56,  340,
 /*   760 */   186,   48,  359,  158,   19,  388,  353,   11,  341,  407,
 /*   770 */   416,  142,   11,  423,  428,  211,  106,  106,  286,  463,
 /*   780 */   106,   79,  464,  367,   79,  371,  465,  391,  142,  399,
 /*   790 */   404,  408,  205,  420,  421,  445,  426,  427,   73,  213,
 /*   800 */   216,  295,  377,   52,  236,  379,  382,  376,  376,   56,
 /*   810 */    55,   55,   55,   55,  306,   57,   57,   57,   57,   58,
 /*   820 */    58,   59,   59,   59,   60,  228,  480,  318,  119,  187,
 /*   830 */   363,  365,  190,   56,  266,  381,  269,  394,   63,  268,
 /*   840 */   397,    4,  429,  419,  431,  234,  422,  281,  221,  474,
 /*   850 */   475,  479,  314,  313,  316,  317,    8,  249,  262,  321,
 /*   860 */   371,  330,  338,  253,  255,  233,  339,  342,  254,  345,
 /*   870 */   191,  350,   73,  272,  192,   72,  193,  270,   69,  236,
 /*   880 */   379,  382,  376,  376,   56,   55,   55,   55,   55,  370,
 /*   890 */    57,   57,   57,   57,   58,   58,   59,   59,   59,   60,
 /*   900 */   194,   50,  351,  139,  392,  198,  168,   65,   64,  167,
 /*   910 */   395,   63,  268,  169,    4,   63,  258,  259,  234,  202,
 /*   920 */   352,   74,   63,  268,  103,    4,  396,  275,  406,  234,
 /*   930 */   204,  262,  410,   89,  447,  171,  161,  433,  457,  172,
 /*   940 */   288,  289,  262,  226,  448,  455,  449,  153,  292,  461,
 /*   950 */   354,  354,  354,  355,  356,  357,   10,  434,  227,  178,
 /*   960 */   248,  459,  370,  179,  180,  214,  107,  114,   14,  230,
 /*   970 */   170,  112,   83,  370,  220,   88,  312,  315,  224,  100,
 /*   980 */    65,   64,  412,  251,  462,  319,  320,  182,   63,  258,
 /*   990 */   259,   65,   64,  352,  322,  160,   49,  298,   75,   63,
 /*  1000 */   258,  259,  395,  101,  352,  521,  522,  136,  137,   53,
 /*  1010 */   467,  360,  369,  378,  166,  383,  117,  387,    6,    7,
 /*  1020 */    12,   11,  104,  354,  354,  354,  355,  356,  357,   10,
 /*  1030 */   403,  105,  132,  417,  354,  354,  354,  355,  356,  357,
 /*  1040 */    10,  280,   90,  151,  210,   91,  370,   76,  285,   92,
 /*  1050 */   186,  215,  290,  217,  108,  456,  293,  109,  466,  460,
 /*  1060 */   110,  291,  111,  299,  121,  122,  161,   77,   78,   13,
 /*  1070 */   155,  133,  473,  439,  176,   80,   81,  352,  177,  308,
 /*  1080 */   515,  482,  515,  515,  515,  515,  515,  515,  515,  515,
 /*  1090 */   515,  515,  515,  515,  515,  157,  515,  515,  515,  515,
 /*  1100 */   515,  515,  515,  515,  515,  515,  515,  354,  354,  354,
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
 /*    90 */    18,   65,   26,   14,  157,  157,  177,  177,  178,  157,
 /*   100 */   163,   21,  165,  175,  176,   26,    1,    2,  149,  150,
 /*   110 */    49,  183,  153,   20,   53,  177,  178,  197,   92,  177,
 /*   120 */   178,  162,   96,   83,   84,  188,  189,   66,   67,   68,
 /*   130 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  157,
 /*   140 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   150 */    14,  157,  126,  127,  128,   19,  197,  177,   22,   21,
 /*   160 */    94,   95,   96,   97,   98,   99,  100,  225,   17,  231,
 /*   170 */    19,  105,   92,  157,   95,   96,   97,   98,   99,  100,
 /*   180 */   108,  222,  110,  111,  105,   49,  189,   94,  169,   25,
 /*   190 */    97,   98,   99,  177,  178,  172,  173,  174,  216,  106,
 /*   200 */   241,  242,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   210 */    74,   75,   76,   77,   92,   79,   80,   81,   82,   83,
 /*   220 */    84,   85,   86,   87,   88,   14,  183,  208,  185,  235,
 /*   230 */    92,   93,   94,   22,  191,   97,   98,   99,  226,  227,
 /*   240 */   228,  157,  230,  157,  106,  226,  157,  228,  126,  230,
 /*   250 */   234,  157,   19,   94,   21,   20,   97,   98,   99,  236,
 /*   260 */    49,  177,  178,  177,  178,  106,  177,  178,  162,  238,
 /*   270 */   239,  177,  178,  172,  173,  174,  112,   66,   67,   68,
 /*   280 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  125,
 /*   290 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   300 */    14,  157,   18,  197,  220,  189,  162,   18,   22,  220,
 /*   310 */   169,  217,  218,  157,   14,  209,  210,   21,  234,  157,
 /*   320 */   214,  177,  178,  234,  157,   92,  159,   17,   93,  198,
 /*   330 */   163,   21,  165,  177,  178,   49,   21,  236,   17,  177,
 /*   340 */   178,  197,   21,  166,   21,  134,  169,  170,  171,  208,
 /*   350 */    50,  116,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   360 */    74,   75,   76,   77,  220,   79,   80,   81,   82,   83,
 /*   370 */    84,   85,   86,   87,   88,   14,   10,  157,  234,   18,
 /*   380 */   218,  225,  157,   22,   85,   86,   87,   88,   92,   93,
 /*   390 */   169,   21,  108,   27,  110,  111,  157,  108,   30,  110,
 /*   400 */   111,  101,   92,   93,   49,  105,   38,   92,   93,   43,
 /*   410 */    49,   45,  116,   92,   93,   92,   93,  226,  162,  228,
 /*   420 */   134,  230,   56,  157,   69,   70,  169,   66,   67,   68,
 /*   430 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  116,
 /*   440 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   450 */    14,   96,  157,  197,   18,   85,  190,  176,   22,  131,
 /*   460 */   157,  240,   92,   93,  183,  208,  138,  139,  140,  157,
 /*   470 */   239,  157,  177,  178,  157,  108,  157,  110,  111,  157,
 /*   480 */   177,  178,  169,  170,  171,   49,    0,    1,    2,  177,
 /*   490 */   178,  177,  178,   50,  177,  178,  177,  178,  157,  177,
 /*   500 */   178,  235,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   510 */    74,   75,   76,   77,  157,   79,   80,   81,   82,   83,
 /*   520 */    84,   85,   86,   87,   88,   14,  157,  109,  157,   18,
 /*   530 */   157,  113,  157,   22,  177,  178,  157,  157,  157,  157,
 /*   540 */   133,  157,  135,  157,  101,  157,  177,  178,  177,  178,
 /*   550 */   177,  178,  177,  178,   17,  157,  177,  178,  177,  178,
 /*   560 */    49,  177,  178,  177,  178,  177,  178,   17,   20,  157,
 /*   570 */   190,   21,  190,  209,  210,  177,  178,   66,   67,   68,
 /*   580 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  157,
 /*   590 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   600 */    14,  157,  190,  157,   18,  157,   21,  157,   22,  177,
 /*   610 */   178,   20,  157,  193,  194,  235,  157,  235,  157,  157,
 /*   620 */   157,  177,  178,  177,  178,  177,  178,  177,  178,  157,
 /*   630 */   157,  148,  177,  178,  151,   49,  177,  178,  177,  178,
 /*   640 */   177,  178,   92,   95,   93,  157,  169,  235,  157,  177,
 /*   650 */   178,  114,   66,   67,   68,   69,   70,   71,   72,   73,
 /*   660 */    74,   75,   76,   77,  157,   79,   80,   81,   82,   83,
 /*   670 */    84,   85,   86,   87,   88,   14,  157,   92,  157,   25,
 /*   680 */   157,   85,  157,   22,  177,  178,  157,   33,  162,  102,
 /*   690 */   103,  104,  157,  142,  143,   20,  177,  178,  177,  178,
 /*   700 */   177,  178,  177,  178,  216,  109,  115,  126,  127,  113,
 /*   710 */    49,   57,  221,  157,  157,  130,  157,  240,   70,   21,
 /*   720 */    14,   23,  162,  197,   24,  196,   26,   66,   67,   68,
 /*   730 */    69,   70,   71,   72,   73,   74,   75,   76,   77,  199,
 /*   740 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   750 */    14,   96,  196,  196,  200,  196,  221,  197,   22,   37,
 /*   760 */   105,  207,   18,  115,   20,   18,  157,   20,   46,   18,
 /*   770 */    18,   20,   20,   23,   18,   18,   20,   20,   18,   18,
 /*   780 */    20,   20,   18,  169,   20,   49,   18,  157,   20,  211,
 /*   790 */   157,  157,  157,  157,  186,  157,  186,  186,  123,  157,
 /*   800 */   157,  157,   96,   67,   68,   69,   70,   71,   72,   73,
 /*   810 */    74,   75,   76,   77,  243,   79,   80,   81,   82,   83,
 /*   820 */    84,   85,   86,   87,   88,   14,  157,  154,  199,  180,
 /*   830 */   237,  237,  201,   22,  229,  229,  233,  180,   14,   15,
 /*   840 */   180,   17,  180,  185,  180,   21,   96,  184,  202,  169,
 /*   850 */   169,  244,    8,  152,  152,  152,   20,  160,   34,   22,
 /*   860 */    49,  179,  179,  164,  101,   47,  187,  179,  164,  179,
 /*   870 */   202,  197,  123,  120,  203,  121,  204,  118,  133,   68,
 /*   880 */    69,   70,   71,   72,   73,   74,   75,   76,   77,   65,
 /*   890 */    79,   80,   81,   82,   83,   84,   85,   86,   87,   88,
 /*   900 */   205,  122,  206,  114,  158,   26,  219,   83,   84,  232,
 /*   910 */    21,   14,   15,  219,   17,   91,   92,   93,   21,  212,
 /*   920 */    96,  101,   14,   15,  158,   17,  168,  117,  213,   21,
 /*   930 */   212,   34,  213,   17,  179,  219,  112,  168,   16,  219,
 /*   940 */   155,   13,   34,  181,  179,  158,  179,  156,   13,  206,
 /*   950 */   126,  127,  128,  129,  130,  131,  132,  187,  181,    5,
 /*   960 */     6,  158,   65,    9,   10,   11,  195,   17,   17,  161,
 /*   970 */   182,  223,  167,   65,  202,  182,    1,    7,   18,   25,
 /*   980 */    83,   84,   85,   22,  206,   21,   21,   25,   91,   92,
 /*   990 */    93,   83,   84,   96,   21,   51,   17,  224,   17,   91,
 /*  1000 */    92,   93,   21,   35,   96,  114,  114,  114,  114,   17,
 /*  1010 */    56,   18,   18,   96,   67,  109,   17,   41,  119,  119,
 /*  1020 */    20,   20,   17,  126,  127,  128,  129,  130,  131,  132,
 /*  1030 */   116,   18,  114,   18,  126,  127,  128,  129,  130,  131,
 /*  1040 */   132,   51,   17,  100,   18,   17,   65,   17,   51,   17,
 /*  1050 */   105,   12,   14,   12,  115,   15,  102,  103,  104,   15,
 /*  1060 */    25,  107,  124,   20,   83,   84,  112,   22,   22,   17,
 /*  1070 */    20,   20,  114,   92,   25,   22,   22,   96,  144,    3,
 /*  1080 */   245,    4,  245,  245,  245,  245,  245,  245,  245,  245,
 /*  1090 */   245,  245,  245,  245,  245,  141,  245,  245,  245,  245,
 /*  1100 */   245,  245,  245,  245,  245,  245,  245,  126,  127,  128,
};
#define YY_SHIFT_USE_DFLT (-66)
#define YY_SHIFT_MAX 308
static const short yy_shift_ofst[] = {
 /*     0 */   105,  954,  824,  -14,  824,  908,  908,  908,  138,  -48,
 /*    10 */   908,  908,  908,  908,  908,  -54,  315,   80,   40,   40,
 /*    20 */    61,  136,  211,  286,  361,  436,  511,  586,  661,  661,
 /*    30 */   661,  661,  661,  661,  661,  661,  661,  661,  661,  661,
 /*    40 */   661,  661,  661,  661,  661,  736,  811,  811,  897,  908,
 /*    50 */   908,  908,  908,  908,  908,  908,  908,  908,  908,  908,
 /*    60 */   908,  908,  908,  908,  908,  908,  908,  908,  908,  908,
 /*    70 */   908,  908,  908,  908,  908,  908,  908,  908,  908,  908,
 /*    80 */   908,  908,  -65,   66,  -43,  -43,  -37,  299,  300,  315,
 /*    90 */   315,  315,  315,   80,  -12,  -66,  -66,  -66,  981,   79,
 /*   100 */   -52,  366,  486,  233,  315,  233,  315,  315,  315,  315,
 /*   110 */   315,  315,  164,  315,  315,  585,  585,  -48,  -48,  -66,
 /*   120 */   -66,   26,   26,   93,  159,   72,  310,  284,  289,  296,
 /*   130 */   323,  321,  370,  328,  315,  596,  315,  315,  550,  315,
 /*   140 */   235,  315,  315,  367,  235,  315,  315,  654,  654,  654,
 /*   150 */   315,  315,  367,  315,  367,  315,  367,  551,  315,  151,
 /*   160 */   368,  418,  591,  581,  581,  122,  122,  407,  368,  368,
 /*   170 */   443,  368,  368,  548,  675,   80,   80,  648,  844,  844,
 /*   180 */   844,  836,  837,  837,  763,  763,  818,  763,  763,  -48,
 /*   190 */   749,  753,  754,  759,  779,  745,  789,  879,  889,  879,
 /*   200 */   789,  820,  810,  820,  810,  916,  879,  879,  889,  818,
 /*   210 */   763,  763,  763,  916,  922,  928,  789,  935,  789,  749,
 /*   220 */   779,  779,  950,  951,  -66,  -66,  -66,  -66,  355,  587,
 /*   230 */   698,  700,  655,  722,  537,  744,  706,  747,  751,  752,
 /*   240 */   750,  756,  757,  760,  761,  764,  768,  975,  970,  960,
 /*   250 */   961,  964,  962,  965,  973,  968,  944,  979,  891,  892,
 /*   260 */   893,  894,  992,  993,  994,  917,  947,  906,  999,  976,
 /*   270 */   899, 1000,  900, 1001,  914, 1005, 1013,  918, 1015,  990,
 /*   280 */  1025, 1026, 1028, 1030,  997, 1032,  943,  945, 1039, 1038,
 /*   290 */  1040, 1041, 1044,  939, 1035, 1045, 1046,  938, 1043, 1052,
 /*   300 */  1050, 1051, 1053,  958, 1049, 1054,  934, 1076, 1077,
};
#define YY_REDUCE_USE_DFLT (-165)
#define YY_REDUCE_MAX 227
static const short yy_reduce_ofst[] = {
 /*     0 */  -145,  -41,  144,   19,  -80,   84,   94,   89,  -63,  106,
 /*    10 */   -62,   16,  162,  -58,  156,   12,  167,  177,   23,  101,
 /*    20 */   191,  191,  191,  191,  191,  191,  191,  191,  191,  191,
 /*    30 */   191,  191,  191,  191,  191,  191,  191,  191,  191,  191,
 /*    40 */   191,  191,  191,  191,  191,  191,  191,  191,   86,  295,
 /*    50 */   303,  312,  314,  317,  319,  322,  357,  369,  371,  373,
 /*    60 */   375,  379,  381,  384,  386,  388,  398,  432,  444,  446,
 /*    70 */   448,  450,  455,  459,  461,  463,  472,  507,  519,  521,
 /*    80 */   523,  525,  191,  -72,  191,  191,  191,  191,   43,  266,
 /*    90 */   380,  382,  412,  313,  191,  191,  191,  191, -164,  281,
 /*   100 */    31,  420,  483,  141,  -18,  257,   -6,  529,  556,  557,
 /*   110 */   491,  559,  256,  535,  488,  221,  477,  526,  560,  554,
 /*   120 */   364,  -81,  -20,   -3,  116,  131,  220,  131,  131,  225,
 /*   130 */   239,  341,  462,  231,  473,  540,  462,  609,  614,  630,
 /*   140 */   578,  633,  634,  131,  578,  635,  636,  608,  610,  611,
 /*   150 */   638,  642,  131,  643,  131,  644,  131,  571,  669,  673,
 /*   160 */   649,  629,  631,  593,  594,  605,  606,  603,  657,  660,
 /*   170 */   658,  662,  664,  663,  646,  680,  681,  607,  701,  702,
 /*   180 */   703,  697,  699,  704,  682,  683,  679,  688,  690,  674,
 /*   190 */   668,  671,  672,  695,  696,  677,  746,  687,  758,  694,
 /*   200 */   766,  707,  715,  718,  719,  762,  716,  720,  769,  770,
 /*   210 */   755,  765,  767,  777,  785,  791,  787,  771,  803,  772,
 /*   220 */   743,  778,  748,  773,  808,  805,  788,  793,
};
static const YYACTIONTYPE yy_default[] = {
 /*     0 */   490,  752,  718,  604,  752,  718,  752,  718,  752,  608,
 /*    10 */   714,  718,  752,  752,  752,  688,  752,  523,  728,  728,
 /*    20 */   639,  752,  752,  752,  752,  752,  752,  752,  640,  717,
 /*    30 */   713,  709,  711,  710,  641,  628,  637,  644,  620,  646,
 /*    40 */   647,  655,  656,  735,  736,  678,  694,  677,  752,  752,
 /*    50 */   752,  752,  752,  752,  752,  752,  752,  752,  752,  752,
 /*    60 */   752,  752,  752,  752,  752,  752,  752,  752,  752,  752,
 /*    70 */   752,  752,  752,  752,  752,  752,  752,  752,  752,  752,
 /*    80 */   752,  752,  680,  516,  679,  687,  681,  682,  577,  752,
 /*    90 */   752,  752,  752,  752,  683,  684,  695,  696,  752,  752,
 /*   100 */   741,  752,  490,  604,  752,  604,  752,  752,  752,  752,
 /*   110 */   752,  752,  752,  752,  752,  752,  752,  752,  752,  598,
 /*   120 */   608,  752,  752,  568,  752,  752,  752,  752,  752,  752,
 /*   130 */   752,  752,  752,  741,  752,  596,  752,  752,  525,  752,
 /*   140 */   606,  752,  752,  611,  612,  752,  752,  752,  752,  752,
 /*   150 */   752,  752,  506,  752,  587,  752,  650,  749,  752,  752,
 /*   160 */   631,  596,  605,  752,  752,  752,  752,  712,  631,  631,
 /*   170 */   547,  631,  631,  550,  643,  752,  752,  750,  495,  495,
 /*   180 */   495,  567,  514,  514,  579,  579,  564,  579,  579,  752,
 /*   190 */   643,  634,  636,  624,  638,  752,  613,  632,  752,  632,
 /*   200 */   613,  621,  623,  621,  623,  719,  632,  632,  752,  564,
 /*   210 */   579,  579,  579,  719,  504,  501,  613,  586,  613,  643,
 /*   220 */   638,  638,  657,  752,  509,  533,  552,  552,  752,  752,
 /*   230 */   505,  752,  752,  752,  664,  752,  752,  752,  752,  752,
 /*   240 */   752,  752,  752,  752,  752,  752,  752,  752,  752,  752,
 /*   250 */   510,  752,  752,  752,  752,  752,  752,  752,  669,  665,
 /*   260 */   752,  666,  752,  752,  752,  752,  752,  590,  752,  752,
 /*   270 */   752,  625,  752,  635,  752,  752,  752,  752,  752,  752,
 /*   280 */   752,  752,  752,  752,  752,  752,  752,  752,  752,  752,
 /*   290 */   752,  752,  752,  752,  752,  752,  752,  752,  648,  752,
 /*   300 */   649,  732,  752,  752,  752,  752,  752,  491,  752,  485,
 /*   310 */   488,  487,  489,  493,  496,  494,  497,  498,  499,  511,
 /*   320 */   512,  515,  513,  507,  532,  520,  521,  522,  534,  541,
 /*   330 */   542,  580,  581,  582,  583,  729,  730,  731,  543,  562,
 /*   340 */   565,  566,  544,  629,  630,  545,  594,  595,  661,  588,
 /*   350 */   589,  593,  663,  667,  668,  670,  671,  672,  519,  526,
 /*   360 */   527,  530,  531,  724,  726,  725,  727,  529,  528,  673,
 /*   370 */   676,  685,  686,  692,  698,  702,  690,  691,  693,  697,
 /*   380 */   699,  700,  701,  591,  592,  705,  707,  708,  703,  715,
 /*   390 */   716,  614,  706,  689,  626,  518,  633,  627,  597,  607,
 /*   400 */   616,  617,  618,  619,  602,  603,  609,  622,  659,  660,
 /*   410 */   610,  599,  600,  601,  704,  662,  674,  675,  546,  553,
 /*   420 */   554,  555,  558,  559,  560,  561,  556,  557,  720,  721,
 /*   430 */   723,  722,  548,  549,  563,  535,  536,  537,  538,  669,
 /*   440 */   539,  540,  524,  517,  569,  572,  551,  573,  574,  575,
 /*   450 */   576,  578,  570,  571,  508,  500,  502,  503,  584,  615,
 /*   460 */   585,  642,  645,  653,  654,  658,  651,  652,  742,  743,
 /*   470 */   737,  738,  739,  740,  733,  734,  744,  745,  746,  747,
 /*   480 */   751,  748,  492,  486,
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
 /* 166 */ "cmd ::= insert_cmd INTO fullname inscollist_opt select",
 /* 167 */ "insert_cmd ::= INSERT",
 /* 168 */ "insert_cmd ::= REPLACE",
 /* 169 */ "valueslist ::= valueslist COMMA LP itemlist RP",
 /* 170 */ "valueslist ::= LP itemlist RP",
 /* 171 */ "itemlist ::= itemlist COMMA expr",
 /* 172 */ "itemlist ::= expr",
 /* 173 */ "inscollist_opt ::=",
 /* 174 */ "inscollist_opt ::= LP inscollist RP",
 /* 175 */ "inscollist ::= inscollist COMMA nm",
 /* 176 */ "inscollist ::= nm",
 /* 177 */ "expr ::= term",
 /* 178 */ "expr ::= LP expr RP",
 /* 179 */ "term ::= NULL",
 /* 180 */ "expr ::= ID",
 /* 181 */ "expr ::= JOIN_KW",
 /* 182 */ "expr ::= nm DOT nm",
 /* 183 */ "expr ::= nm DOT nm DOT nm",
 /* 184 */ "term ::= INTEGER|FLOAT|BLOB",
 /* 185 */ "term ::= STRING",
 /* 186 */ "expr ::= REGISTER",
 /* 187 */ "expr ::= VARIABLE",
 /* 188 */ "expr ::= VARIABLE1",
 /* 189 */ "expr ::= CAST LP expr AS typetoken RP",
 /* 190 */ "expr ::= ID LP distinct exprlist RP",
 /* 191 */ "expr ::= ID LP STAR RP",
 /* 192 */ "term ::= CTIME_KW",
 /* 193 */ "expr ::= expr AND expr",
 /* 194 */ "expr ::= expr OR expr",
 /* 195 */ "expr ::= expr LT|GT|GE|LE expr",
 /* 196 */ "expr ::= expr EQ|NE expr",
 /* 197 */ "expr ::= expr BITAND|BITOR|LSHIFT|RSHIFT expr",
 /* 198 */ "expr ::= expr PLUS|MINUS expr",
 /* 199 */ "expr ::= expr STAR|SLASH|REM expr",
 /* 200 */ "expr ::= expr CONCAT expr",
 /* 201 */ "likeop ::= LIKE_KW",
 /* 202 */ "likeop ::= NOT LIKE_KW",
 /* 203 */ "escape ::= ESCAPE expr",
 /* 204 */ "escape ::=",
 /* 205 */ "expr ::= expr likeop expr escape",
 /* 206 */ "expr ::= expr ISNULL|NOTNULL",
 /* 207 */ "expr ::= expr IS NULL",
 /* 208 */ "expr ::= expr NOT NULL",
 /* 209 */ "expr ::= expr IS NOT NULL",
 /* 210 */ "expr ::= NOT|BITNOT expr",
 /* 211 */ "expr ::= MINUS expr",
 /* 212 */ "expr ::= PLUS expr",
 /* 213 */ "between_op ::= BETWEEN",
 /* 214 */ "between_op ::= NOT BETWEEN",
 /* 215 */ "between_elem ::= INTEGER|STRING",
 /* 216 */ "expr ::= expr between_op between_elem AND between_elem",
 /* 217 */ "in_op ::= IN",
 /* 218 */ "in_op ::= NOT IN",
 /* 219 */ "expr ::= expr in_op LP exprlist RP",
 /* 220 */ "expr ::= LP select RP",
 /* 221 */ "expr ::= expr in_op LP select RP",
 /* 222 */ "expr ::= expr in_op nm dbnm",
 /* 223 */ "expr ::= EXISTS LP select RP",
 /* 224 */ "expr ::= CASE case_operand case_exprlist case_else END",
 /* 225 */ "case_exprlist ::= case_exprlist WHEN expr THEN expr",
 /* 226 */ "case_exprlist ::= WHEN expr THEN expr",
 /* 227 */ "case_else ::= ELSE expr",
 /* 228 */ "case_else ::=",
 /* 229 */ "case_operand ::= expr",
 /* 230 */ "case_operand ::=",
 /* 231 */ "exprlist ::= exprlist COMMA expritem",
 /* 232 */ "exprlist ::= expritem",
 /* 233 */ "expritem ::= expr",
 /* 234 */ "expritem ::=",
 /* 235 */ "idxlist_opt ::=",
 /* 236 */ "idxlist_opt ::= LP idxlist RP",
 /* 237 */ "idxlist ::= idxlist COMMA idxitem collate sortorder",
 /* 238 */ "idxlist ::= idxitem collate sortorder",
 /* 239 */ "idxitem ::= nm",
 /* 240 */ "plus_num ::= plus_opt number",
 /* 241 */ "minus_num ::= MINUS number",
 /* 242 */ "number ::= INTEGER|FLOAT",
 /* 243 */ "plus_opt ::= PLUS",
 /* 244 */ "plus_opt ::=",
 /* 245 */ "raisetype ::= ROLLBACK",
 /* 246 */ "raisetype ::= ABORT",
 /* 247 */ "raisetype ::= FAIL",
 /* 248 */ "cmd ::= SET variable_assignment_list",
 /* 249 */ "cmd ::= SET NAMES ids",
 /* 250 */ "cmd ::= SET CHARACTER SET ids",
 /* 251 */ "variable_assignment_list ::= variable_assignment_list COMMA scope_qualifier user_var_name EQ expr",
 /* 252 */ "variable_assignment_list ::= scope_qualifier user_var_name EQ expr",
 /* 253 */ "scope_qualifier ::= GLOBAL",
 /* 254 */ "scope_qualifier ::= LOCAL",
 /* 255 */ "scope_qualifier ::= SESSION",
 /* 256 */ "scope_qualifier ::= VARIABLE1 DOT",
 /* 257 */ "scope_qualifier ::=",
 /* 258 */ "user_var_name ::= ids",
 /* 259 */ "user_var_name ::= VARIABLE",
 /* 260 */ "cmd ::= show_databes",
 /* 261 */ "cmd ::= show_tables",
 /* 262 */ "show_databes ::= SHOW DATABASES|SCHEMAS",
 /* 263 */ "show_tables ::= SHOW full_keyword TABLES from_db",
 /* 264 */ "full_keyword ::= JOIN_KW",
 /* 265 */ "full_keyword ::=",
 /* 266 */ "from_db ::=",
 /* 267 */ "from_db ::= FROM|IN nm",
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
#line 1144 "parse.c"
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
#line 662 "parse.y"
{sqlite3ExprDelete((yypminor->yy342));}
#line 1159 "parse.c"
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
#line 906 "parse.y"
{sqlite3ExprListDelete((yypminor->yy462));}
#line 1174 "parse.c"
      break;
    case 196:
    case 201:
    case 209:
    case 210:
#line 518 "parse.y"
{sqlite3SrcListDelete((yypminor->yy287));}
#line 1182 "parse.c"
      break;
    case 206:
#line 579 "parse.y"
{
  sqlite3ExprDelete((yypminor->yy474).pLimit);
  sqlite3ExprDelete((yypminor->yy474).pOffset);
}
#line 1190 "parse.c"
      break;
    case 213:
    case 216:
    case 223:
#line 535 "parse.y"
{sqlite3IdListDelete((yypminor->yy440));}
#line 1197 "parse.c"
      break;
    case 224:
#line 635 "parse.y"
{sqlite3ValuesListDelete((yypminor->yy49));}
#line 1202 "parse.c"
      break;
    case 238:
#line 1122 "parse.y"
{ sqlite3ExprListDelete((yypminor->yy462)); }
#line 1207 "parse.c"
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
#line 1359 "parse.c"
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
#line 1705 "parse.c"
        break;
      case 6:
#line 101 "parse.y"
{ sqlite3BeginParse(pParse, 0); }
#line 1710 "parse.c"
        break;
      case 7:
#line 103 "parse.y"
{ sqlite3BeginParse(pParse, 1); }
#line 1715 "parse.c"
        break;
      case 8:
#line 104 "parse.y"
{ sqlite3BeginParse(pParse, 2); }
#line 1720 "parse.c"
        break;
      case 9:
#line 111 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_BEGIN);}
#line 1725 "parse.c"
        break;
      case 10:
#line 112 "parse.y"
{sqlite3BeginTransaction(pParse, SQLTYPE_TRANSACTION_START);}
#line 1730 "parse.c"
        break;
      case 13:
#line 123 "parse.y"
{sqlite3CommitTransaction(pParse);}
#line 1735 "parse.c"
        break;
      case 14:
#line 125 "parse.y"
{sqlite3RollbackTransaction(pParse);}
#line 1740 "parse.c"
        break;
      case 16:
#line 130 "parse.y"
{
   sqlite3StartTable(pParse, 0, 0, 0, 0, 0);
}
#line 1747 "parse.c"
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
      case 213:
      case 217:
#line 135 "parse.y"
{yygotominor.yy32 = 0;}
#line 1762 "parse.c"
        break;
      case 18:
      case 19:
      case 67:
      case 81:
      case 101:
      case 110:
      case 214:
      case 218:
#line 136 "parse.y"
{yygotominor.yy32 = 1;}
#line 1774 "parse.c"
        break;
      case 21:
#line 142 "parse.y"
{
  //sqlite3EndTable(pParse,&X,&Y,0);
}
#line 1781 "parse.c"
        break;
      case 22:
#line 145 "parse.y"
{
  sqlite3EndTable(pParse,0,0,0);
  //sqlite3SelectDelete(S);
  yy_destructor(162,&yymsp[0].minor);
}
#line 1790 "parse.c"
        break;
      case 32:
#line 167 "parse.y"
{
  //A.z = X.z;
  //A.n = (pParse->sLastToken.z-X.z) + pParse->sLastToken.n;
}
#line 1798 "parse.c"
        break;
      case 33:
#line 171 "parse.y"
{
  //sqlite3AddColumn(pParse,&X);
  //A = X;
}
#line 1806 "parse.c"
        break;
      case 34:
      case 35:
      case 36:
      case 37:
      case 38:
      case 242:
#line 181 "parse.y"
{yygotominor.yy308 = yymsp[0].minor.yy0;}
#line 1816 "parse.c"
        break;
      case 40:
#line 240 "parse.y"
{ /*sqlite3AddColumnType(pParse,&X);*/ }
#line 1821 "parse.c"
        break;
      case 41:
      case 44:
      case 118:
      case 119:
      case 130:
      case 149:
      case 239:
      case 240:
      case 241:
#line 241 "parse.y"
{yygotominor.yy308 = yymsp[0].minor.yy308;}
#line 1834 "parse.c"
        break;
      case 42:
#line 242 "parse.y"
{
  yygotominor.yy308.z = yymsp[-3].minor.yy308.z;
  yygotominor.yy308.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-3].minor.yy308.z;
}
#line 1842 "parse.c"
        break;
      case 43:
#line 246 "parse.y"
{
  yygotominor.yy308.z = yymsp[-5].minor.yy308.z;
  yygotominor.yy308.n = &yymsp[0].minor.yy0.z[yymsp[0].minor.yy0.n] - yymsp[-5].minor.yy308.z;
}
#line 1850 "parse.c"
        break;
      case 45:
#line 252 "parse.y"
{yygotominor.yy308.z=yymsp[-1].minor.yy308.z; yygotominor.yy308.n=yymsp[0].minor.yy308.n+(yymsp[0].minor.yy308.z-yymsp[-1].minor.yy308.z);}
#line 1855 "parse.c"
        break;
      case 46:
#line 254 "parse.y"
{ yygotominor.yy32 = atoi((char*)yymsp[0].minor.yy308.z); }
#line 1860 "parse.c"
        break;
      case 47:
#line 255 "parse.y"
{ yygotominor.yy32 = -atoi((char*)yymsp[0].minor.yy308.z); }
#line 1865 "parse.c"
        break;
      case 52:
#line 264 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/   yy_destructor(177,&yymsp[0].minor);
}
#line 1871 "parse.c"
        break;
      case 53:
#line 265 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/ }
#line 1876 "parse.c"
        break;
      case 54:
#line 266 "parse.y"
{ /*sqlite3AddDefaultValue(pParse,X);*/  yy_destructor(177,&yymsp[0].minor);
}
#line 1882 "parse.c"
        break;
      case 55:
#line 267 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_UMINUS, X, 0, 0);
  //sqlite3AddDefaultValue(pParse,p);
  yy_destructor(177,&yymsp[0].minor);
}
#line 1891 "parse.c"
        break;
      case 56:
#line 271 "parse.y"
{
  //Expr *p = sqlite3Expr(TK_STRING, 0, 0, &X);
  //sqlite3AddDefaultValue(pParse,p);
}
#line 1899 "parse.c"
        break;
      case 59:
#line 281 "parse.y"
{/*sqlite3AddNotNull(pParse, R);*/}
#line 1904 "parse.c"
        break;
      case 60:
#line 283 "parse.y"
{/*sqlite3AddPrimaryKey(pParse,0,R,I,Z);*/}
#line 1909 "parse.c"
        break;
      case 61:
#line 284 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,0,R,0,0,0,0);*/}
#line 1914 "parse.c"
        break;
      case 62:
#line 285 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,X);*/  sqlite3ExprDelete(yymsp[-1].minor.yy342); }
#line 1919 "parse.c"
        break;
      case 63:
#line 287 "parse.y"
{/*sqlite3CreateForeignKey(pParse,0,&T,TA,R);*/ sqlite3ExprListDelete(yymsp[-1].minor.yy462); }
#line 1924 "parse.c"
        break;
      case 64:
#line 288 "parse.y"
{/*sqlite3DeferForeignKey(pParse,D);*/}
#line 1929 "parse.c"
        break;
      case 65:
#line 289 "parse.y"
{/*sqlite3AddCollateType(pParse, (char*)C.z, C.n);*/}
#line 1934 "parse.c"
        break;
      case 68:
#line 302 "parse.y"
{ yygotominor.yy32 = OE_Restrict * 0x010101; }
#line 1939 "parse.c"
        break;
      case 69:
#line 303 "parse.y"
{ yygotominor.yy32 = (yymsp[-1].minor.yy32 & yymsp[0].minor.yy47.mask) | yymsp[0].minor.yy47.value; }
#line 1944 "parse.c"
        break;
      case 70:
#line 305 "parse.y"
{ yygotominor.yy47.value = 0;     yygotominor.yy47.mask = 0x000000; }
#line 1949 "parse.c"
        break;
      case 71:
#line 306 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32;     yygotominor.yy47.mask = 0x0000ff; }
#line 1954 "parse.c"
        break;
      case 72:
#line 307 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32<<8;  yygotominor.yy47.mask = 0x00ff00; }
#line 1959 "parse.c"
        break;
      case 73:
#line 308 "parse.y"
{ yygotominor.yy47.value = yymsp[0].minor.yy32<<16; yygotominor.yy47.mask = 0xff0000; }
#line 1964 "parse.c"
        break;
      case 74:
#line 310 "parse.y"
{ yygotominor.yy32 = OE_SetNull; }
#line 1969 "parse.c"
        break;
      case 75:
#line 311 "parse.y"
{ yygotominor.yy32 = OE_SetDflt; }
#line 1974 "parse.c"
        break;
      case 76:
#line 312 "parse.y"
{ yygotominor.yy32 = OE_Cascade; }
#line 1979 "parse.c"
        break;
      case 77:
#line 313 "parse.y"
{ yygotominor.yy32 = OE_Restrict; }
#line 1984 "parse.c"
        break;
      case 78:
      case 79:
      case 94:
      case 96:
      case 97:
#line 315 "parse.y"
{yygotominor.yy32 = yymsp[0].minor.yy32;}
#line 1993 "parse.c"
        break;
      case 89:
#line 334 "parse.y"
{ sqlite3ExprListDelete(yymsp[-3].minor.yy462); }
#line 1998 "parse.c"
        break;
      case 90:
#line 336 "parse.y"
{/*sqlite3CreateIndex(pParse,0,0,0,yymsp[-2].minor.yy462,R,0,0,0,0);*/ sqlite3ExprListDelete(yymsp[-2].minor.yy462);}
#line 2003 "parse.c"
        break;
      case 91:
#line 337 "parse.y"
{/*sqlite3AddCheckConstraint(pParse,yymsp[-2].minor.yy342);*/ sqlite3ExprDelete(yymsp[-2].minor.yy342);}
#line 2008 "parse.c"
        break;
      case 92:
#line 339 "parse.y"
{ 
        sqlite3ExprListDelete(yymsp[-6].minor.yy462);
        sqlite3ExprListDelete(yymsp[-2].minor.yy462);
 }
#line 2016 "parse.c"
        break;
      case 95:
#line 354 "parse.y"
{yygotominor.yy32 = OE_Default;}
#line 2021 "parse.c"
        break;
      case 98:
#line 359 "parse.y"
{yygotominor.yy32 = OE_Ignore;}
#line 2026 "parse.c"
        break;
      case 99:
      case 168:
#line 360 "parse.y"
{yygotominor.yy32 = OE_Replace;}
#line 2032 "parse.c"
        break;
      case 100:
#line 364 "parse.y"
{
  sqlite3DropTable(pParse, yymsp[0].minor.yy287, 0, yymsp[-1].minor.yy32);
}
#line 2039 "parse.c"
        break;
      case 103:
#line 384 "parse.y"
{
  sqlite3Select(pParse, yymsp[0].minor.yy149, SRT_Callback, 0, 0, 0, 0, 0);
  // sqlite3SelectDelete(yymsp[0].minor.yy149);
}
#line 2047 "parse.c"
        break;
      case 104:
      case 127:
#line 394 "parse.y"
{yygotominor.yy149 = yymsp[0].minor.yy149;}
#line 2053 "parse.c"
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
#line 2064 "parse.c"
        break;
      case 106:
      case 108:
#line 404 "parse.y"
{yygotominor.yy32 = yymsp[0].major;}
#line 2070 "parse.c"
        break;
      case 107:
#line 405 "parse.y"
{yygotominor.yy32 = TK_ALL;}
#line 2075 "parse.c"
        break;
      case 109:
#line 409 "parse.y"
{
  yygotominor.yy149 = sqlite3SelectNew(yymsp[-6].minor.yy462,yymsp[-5].minor.yy287,yymsp[-4].minor.yy342,yymsp[-3].minor.yy462,yymsp[-2].minor.yy342,yymsp[-1].minor.yy462,yymsp[-7].minor.yy32,yymsp[0].minor.yy474.pLimit,yymsp[0].minor.yy474.pOffset);
}
#line 2082 "parse.c"
        break;
      case 113:
      case 236:
#line 430 "parse.y"
{yygotominor.yy462 = yymsp[-1].minor.yy462;}
#line 2088 "parse.c"
        break;
      case 114:
      case 140:
      case 150:
      case 235:
#line 431 "parse.y"
{yygotominor.yy462 = 0;}
#line 2096 "parse.c"
        break;
      case 115:
#line 432 "parse.y"
{
   yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-2].minor.yy462,yymsp[-1].minor.yy342,yymsp[0].minor.yy308.n?&yymsp[0].minor.yy308:0);
}
#line 2103 "parse.c"
        break;
      case 116:
#line 435 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-1].minor.yy462, sqlite3Expr(TK_ALL, 0, 0, 0), 0);
}
#line 2110 "parse.c"
        break;
      case 117:
#line 438 "parse.y"
{
  Expr *pRight = sqlite3Expr(TK_ALL, 0, 0, 0);
  Expr *pLeft = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-3].minor.yy462, sqlite3Expr(TK_DOT, pLeft, pRight, 0), 0);
}
#line 2119 "parse.c"
        break;
      case 120:
#line 450 "parse.y"
{yygotominor.yy308.n = 0;}
#line 2124 "parse.c"
        break;
      case 121:
#line 462 "parse.y"
{yygotominor.yy287 = sqliteMalloc(sizeof(*yygotominor.yy287));}
#line 2129 "parse.c"
        break;
      case 122:
#line 463 "parse.y"
{yygotominor.yy287 = yymsp[0].minor.yy287;}
#line 2134 "parse.c"
        break;
      case 123:
#line 468 "parse.y"
{
   yygotominor.yy287 = yymsp[-1].minor.yy287;
   if( yygotominor.yy287 && yygotominor.yy287->nSrc>0 ) yygotominor.yy287->a[yygotominor.yy287->nSrc-1].jointype = yymsp[0].minor.yy32;
}
#line 2142 "parse.c"
        break;
      case 124:
#line 472 "parse.y"
{yygotominor.yy287 = 0;}
#line 2147 "parse.c"
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
#line 2163 "parse.c"
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
#line 2180 "parse.c"
        break;
      case 128:
#line 508 "parse.y"
{
     yygotominor.yy149 = sqlite3SelectNew(0,yymsp[0].minor.yy287,0,0,0,0,0,0,0);
  }
#line 2187 "parse.c"
        break;
      case 129:
#line 514 "parse.y"
{yygotominor.yy308.z=0; yygotominor.yy308.n=0;}
#line 2192 "parse.c"
        break;
      case 131:
#line 519 "parse.y"
{yygotominor.yy287 = sqlite3SrcListAppend(0,&yymsp[-1].minor.yy308,&yymsp[0].minor.yy308);}
#line 2197 "parse.c"
        break;
      case 132:
#line 523 "parse.y"
{ yygotominor.yy32 = JT_INNER; }
#line 2202 "parse.c"
        break;
      case 133:
#line 524 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-1].minor.yy0,0,0); }
#line 2207 "parse.c"
        break;
      case 134:
#line 525 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-2].minor.yy0,&yymsp[-1].minor.yy308,0); }
#line 2212 "parse.c"
        break;
      case 135:
#line 527 "parse.y"
{ yygotominor.yy32 = sqlite3JoinType(pParse,&yymsp[-3].minor.yy0,&yymsp[-2].minor.yy308,&yymsp[-1].minor.yy308); }
#line 2217 "parse.c"
        break;
      case 136:
      case 144:
      case 153:
      case 160:
      case 177:
      case 203:
      case 227:
      case 229:
      case 233:
#line 531 "parse.y"
{yygotominor.yy342 = yymsp[0].minor.yy342;}
#line 2230 "parse.c"
        break;
      case 137:
      case 152:
      case 159:
      case 204:
      case 228:
      case 230:
      case 234:
#line 532 "parse.y"
{yygotominor.yy342 = 0;}
#line 2241 "parse.c"
        break;
      case 138:
      case 174:
#line 536 "parse.y"
{yygotominor.yy440 = yymsp[-1].minor.yy440;}
#line 2247 "parse.c"
        break;
      case 139:
      case 173:
#line 537 "parse.y"
{yygotominor.yy440 = 0;}
#line 2253 "parse.c"
        break;
      case 141:
      case 151:
#line 548 "parse.y"
{yygotominor.yy462 = yymsp[0].minor.yy462;}
#line 2259 "parse.c"
        break;
      case 142:
#line 549 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462,yymsp[-2].minor.yy342,yymsp[-1].minor.yy308.n>0?&yymsp[-1].minor.yy308:0);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2267 "parse.c"
        break;
      case 143:
#line 553 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[-2].minor.yy342,yymsp[-1].minor.yy308.n>0?&yymsp[-1].minor.yy308:0);
  if( yygotominor.yy462 && yygotominor.yy462->a ) yygotominor.yy462->a[0].sortOrder = yymsp[0].minor.yy32;
}
#line 2275 "parse.c"
        break;
      case 145:
      case 147:
#line 562 "parse.y"
{yygotominor.yy32 = SQLITE_SO_ASC;}
#line 2281 "parse.c"
        break;
      case 146:
#line 563 "parse.y"
{yygotominor.yy32 = SQLITE_SO_DESC;}
#line 2286 "parse.c"
        break;
      case 148:
#line 565 "parse.y"
{yygotominor.yy308.z = 0; yygotominor.yy308.n = 0;}
#line 2291 "parse.c"
        break;
      case 154:
#line 583 "parse.y"
{yygotominor.yy474.pLimit = 0; yygotominor.yy474.pOffset = 0;}
#line 2296 "parse.c"
        break;
      case 155:
#line 584 "parse.y"
{yygotominor.yy474.pLimit = yymsp[0].minor.yy342; yygotominor.yy474.pOffset = 0;}
#line 2301 "parse.c"
        break;
      case 156:
#line 586 "parse.y"
{yygotominor.yy474.pLimit = yymsp[-2].minor.yy342; yygotominor.yy474.pOffset = yymsp[0].minor.yy342;}
#line 2306 "parse.c"
        break;
      case 157:
#line 588 "parse.y"
{yygotominor.yy474.pOffset = yymsp[-2].minor.yy342; yygotominor.yy474.pLimit = yymsp[0].minor.yy342;}
#line 2311 "parse.c"
        break;
      case 158:
#line 592 "parse.y"
{sqlite3DeleteFrom(pParse,yymsp[-2].minor.yy287,yymsp[-1].minor.yy342, yymsp[0].minor.yy474.pLimit, yymsp[0].minor.yy474.pOffset);}
#line 2316 "parse.c"
        break;
      case 161:
#line 604 "parse.y"
{sqlite3Update(pParse,yymsp[-4].minor.yy287,yymsp[-2].minor.yy462,yymsp[-1].minor.yy342,OE_Default, yymsp[0].minor.yy474.pLimit, yymsp[0].minor.yy474.pOffset);}
#line 2321 "parse.c"
        break;
      case 162:
#line 610 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462,yymsp[0].minor.yy342,&yymsp[-2].minor.yy308);}
#line 2326 "parse.c"
        break;
      case 163:
#line 611 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[0].minor.yy342,&yymsp[-2].minor.yy308);}
#line 2331 "parse.c"
        break;
      case 164:
#line 620 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, 0, yymsp[0].minor.yy49, 0, yymsp[-2].minor.yy440, yymsp[-5].minor.yy32);}
#line 2336 "parse.c"
        break;
      case 165:
#line 624 "parse.y"
{sqlite3Insert(pParse, yymsp[-3].minor.yy287, yymsp[0].minor.yy462, 0, 0, yymsp[-2].minor.yy440, yymsp[-5].minor.yy32);}
#line 2341 "parse.c"
        break;
      case 166:
#line 627 "parse.y"
{sqlite3Insert(pParse, yymsp[-2].minor.yy287, 0, 0, yymsp[0].minor.yy149, yymsp[-1].minor.yy440, yymsp[-4].minor.yy32);}
#line 2346 "parse.c"
        break;
      case 167:
#line 631 "parse.y"
{ yygotominor.yy32 = OE_Default; }
#line 2351 "parse.c"
        break;
      case 169:
#line 637 "parse.y"
{ yygotominor.yy49 = sqlite3ValuesListAppend(yymsp[-4].minor.yy49, yymsp[-1].minor.yy462);}
#line 2356 "parse.c"
        break;
      case 170:
#line 638 "parse.y"
{ yygotominor.yy49 = sqlite3ValuesListAppend(0, yymsp[-1].minor.yy462); }
#line 2361 "parse.c"
        break;
      case 171:
      case 231:
#line 643 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-2].minor.yy462,yymsp[0].minor.yy342,0);}
#line 2367 "parse.c"
        break;
      case 172:
      case 232:
#line 644 "parse.y"
{yygotominor.yy462 = sqlite3ExprListAppend(0,yymsp[0].minor.yy342,0);}
#line 2373 "parse.c"
        break;
      case 175:
#line 653 "parse.y"
{yygotominor.yy440 = sqlite3IdListAppend(yymsp[-2].minor.yy440,&yymsp[0].minor.yy308);}
#line 2378 "parse.c"
        break;
      case 176:
#line 654 "parse.y"
{yygotominor.yy440 = sqlite3IdListAppend(0,&yymsp[0].minor.yy308);}
#line 2383 "parse.c"
        break;
      case 178:
#line 665 "parse.y"
{yygotominor.yy342 = yymsp[-1].minor.yy342; sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0); }
#line 2388 "parse.c"
        break;
      case 179:
      case 184:
      case 185:
#line 666 "parse.y"
{yygotominor.yy342 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0);}
#line 2395 "parse.c"
        break;
      case 180:
      case 181:
#line 667 "parse.y"
{yygotominor.yy342 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy0);}
#line 2401 "parse.c"
        break;
      case 182:
#line 669 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy308);
  yygotominor.yy342 = sqlite3Expr(TK_DOT, temp1, temp2, 0);
}
#line 2410 "parse.c"
        break;
      case 183:
#line 674 "parse.y"
{
  Expr *temp1 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-4].minor.yy308);
  Expr *temp2 = sqlite3Expr(TK_ID, 0, 0, &yymsp[-2].minor.yy308);
  Expr *temp3 = sqlite3Expr(TK_ID, 0, 0, &yymsp[0].minor.yy308);
  Expr *temp4 = sqlite3Expr(TK_DOT, temp2, temp3, 0);
  yygotominor.yy342 = sqlite3Expr(TK_DOT, temp1, temp4, 0);
}
#line 2421 "parse.c"
        break;
      case 186:
#line 683 "parse.y"
{yygotominor.yy342 = sqlite3RegisterExpr(pParse, &yymsp[0].minor.yy0);}
#line 2426 "parse.c"
        break;
      case 187:
      case 188:
#line 684 "parse.y"
{
  Token *pToken = &yymsp[0].minor.yy0;
  Expr *pExpr = yygotominor.yy342 = sqlite3Expr(TK_VARIABLE, 0, 0, pToken);
  //sqlite3ExprAssignVarNumber(pParse, pExpr);
}
#line 2436 "parse.c"
        break;
      case 189:
#line 695 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_CAST, yymsp[-3].minor.yy342, 0, &yymsp[-1].minor.yy308);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-5].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2444 "parse.c"
        break;
      case 190:
#line 700 "parse.y"
{
  yygotominor.yy342 = sqlite3ExprFunction(yymsp[-1].minor.yy462, &yymsp[-4].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-4].minor.yy0,&yymsp[0].minor.yy0);
  if( yymsp[-2].minor.yy32 && yygotominor.yy342 ){
    yygotominor.yy342->flags |= EP_Distinct;
  }
}
#line 2455 "parse.c"
        break;
      case 191:
#line 707 "parse.y"
{
  yygotominor.yy342 = sqlite3ExprFunction(0, &yymsp[-3].minor.yy0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
}
#line 2463 "parse.c"
        break;
      case 192:
#line 711 "parse.y"
{
  /* The CURRENT_TIME, CURRENT_DATE, and CURRENT_TIMESTAMP values are
  ** treated as functions that return constants */
  yygotominor.yy342 = sqlite3ExprFunction(0,&yymsp[0].minor.yy0);
  if( yygotominor.yy342 ) yygotominor.yy342->op = TK_CONST_FUNC;  
}
#line 2473 "parse.c"
        break;
      case 193:
      case 194:
      case 195:
      case 196:
      case 197:
      case 198:
      case 199:
      case 200:
#line 717 "parse.y"
{yygotominor.yy342 = sqlite3Expr(yymsp[-1].major, yymsp[-2].minor.yy342, yymsp[0].minor.yy342, 0);}
#line 2485 "parse.c"
        break;
      case 201:
#line 727 "parse.y"
{yygotominor.yy118.eOperator = yymsp[0].minor.yy0; yygotominor.yy118.not = 0;}
#line 2490 "parse.c"
        break;
      case 202:
#line 728 "parse.y"
{yygotominor.yy118.eOperator = yymsp[0].minor.yy0; yygotominor.yy118.not = 1;}
#line 2495 "parse.c"
        break;
      case 205:
#line 733 "parse.y"
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
#line 2511 "parse.c"
        break;
      case 206:
#line 746 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(yymsp[0].major, yymsp[-1].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2519 "parse.c"
        break;
      case 207:
#line 750 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_ISNULL, yymsp[-2].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2527 "parse.c"
        break;
      case 208:
#line 754 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_NOTNULL, yymsp[-2].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2535 "parse.c"
        break;
      case 209:
#line 758 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_NOTNULL, yymsp[-3].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-3].minor.yy342->span,&yymsp[0].minor.yy0);
}
#line 2543 "parse.c"
        break;
      case 210:
#line 762 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(yymsp[-1].major, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2551 "parse.c"
        break;
      case 211:
#line 766 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_UMINUS, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2559 "parse.c"
        break;
      case 212:
#line 770 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_UPLUS, yymsp[0].minor.yy342, 0, 0);
  sqlite3ExprSpan(yygotominor.yy342,&yymsp[-1].minor.yy0,&yymsp[0].minor.yy342->span);
}
#line 2567 "parse.c"
        break;
      case 215:
#line 781 "parse.y"
{ yygotominor.yy342 = sqlite3Expr(yymsp[0].major, 0, 0, &yymsp[0].minor.yy0); }
#line 2572 "parse.c"
        break;
      case 216:
#line 784 "parse.y"
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
#line 2588 "parse.c"
        break;
      case 219:
#line 800 "parse.y"
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
#line 2602 "parse.c"
        break;
      case 220:
#line 810 "parse.y"
{
    yygotominor.yy342 = sqlite3Expr(TK_SELECT, 0, 0, 0);
    if( yygotominor.yy342 ){
      yygotominor.yy342->pSelect = yymsp[-1].minor.yy149;
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy149);
    }
    sqlite3ExprSpan(yygotominor.yy342,&yymsp[-2].minor.yy0,&yymsp[0].minor.yy0);
  }
#line 2615 "parse.c"
        break;
      case 221:
#line 819 "parse.y"
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
#line 2629 "parse.c"
        break;
      case 222:
#line 829 "parse.y"
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
#line 2644 "parse.c"
        break;
      case 223:
#line 840 "parse.y"
{
    Expr *p = yygotominor.yy342 = sqlite3Expr(TK_EXISTS, 0, 0, 0);
    if( p ){
      p->pSelect = yymsp[-1].minor.yy149;
      sqlite3ExprSpan(p,&yymsp[-3].minor.yy0,&yymsp[0].minor.yy0);
    }else{
      sqlite3SelectDelete(yymsp[-1].minor.yy149);
    }
  }
#line 2657 "parse.c"
        break;
      case 224:
#line 852 "parse.y"
{
  yygotominor.yy342 = sqlite3Expr(TK_CASE, yymsp[-3].minor.yy342, yymsp[-1].minor.yy342, 0);
  if( yygotominor.yy342 ){
    yygotominor.yy342->pList = yymsp[-2].minor.yy462;
  }else{
    sqlite3ExprListDelete(yymsp[-2].minor.yy462);
  }
  sqlite3ExprSpan(yygotominor.yy342, &yymsp[-4].minor.yy0, &yymsp[0].minor.yy0);
}
#line 2670 "parse.c"
        break;
      case 225:
#line 863 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462, yymsp[-2].minor.yy342, 0);
  yygotominor.yy462 = sqlite3ExprListAppend(yygotominor.yy462, yymsp[0].minor.yy342, 0);
}
#line 2678 "parse.c"
        break;
      case 226:
#line 867 "parse.y"
{
  yygotominor.yy462 = sqlite3ExprListAppend(0, yymsp[-2].minor.yy342, 0);
  yygotominor.yy462 = sqlite3ExprListAppend(yygotominor.yy462, yymsp[0].minor.yy342, 0);
}
#line 2686 "parse.c"
        break;
      case 237:
#line 911 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy308.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy308.z, yymsp[-1].minor.yy308.n);
  }
  yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-4].minor.yy462, p, &yymsp[-2].minor.yy308);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2699 "parse.c"
        break;
      case 238:
#line 920 "parse.y"
{
  Expr *p = 0;
  if( yymsp[-1].minor.yy308.n>0 ){
    p = sqlite3Expr(TK_COLUMN, 0, 0, 0);
    if( p ) p->pColl = sqlite3LocateCollSeq(pParse, (char*)yymsp[-1].minor.yy308.z, yymsp[-1].minor.yy308.n);
  }
  yygotominor.yy462 = sqlite3ExprListAppend(0, p, &yymsp[-2].minor.yy308);
  if( yygotominor.yy462 ) yygotominor.yy462->a[yygotominor.yy462->nExpr-1].sortOrder = yymsp[0].minor.yy32;
}
#line 2712 "parse.c"
        break;
      case 245:
#line 1051 "parse.y"
{yygotominor.yy32 = OE_Rollback;}
#line 2717 "parse.c"
        break;
      case 246:
#line 1052 "parse.y"
{yygotominor.yy32 = OE_Abort;}
#line 2722 "parse.c"
        break;
      case 247:
#line 1053 "parse.y"
{yygotominor.yy32 = OE_Fail;}
#line 2727 "parse.c"
        break;
      case 248:
#line 1109 "parse.y"
{
    sqlite3SetStatement(pParse, yymsp[0].minor.yy462, 0, SQLTYPE_SET);
}
#line 2734 "parse.c"
        break;
      case 249:
#line 1113 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy308, SQLTYPE_SET_NAMES);   
}
#line 2741 "parse.c"
        break;
      case 250:
#line 1117 "parse.y"
{
    sqlite3SetStatement(pParse, 0, &yymsp[0].minor.yy308, SQLTYPE_SET_CHARACTER_SET);
}
#line 2748 "parse.c"
        break;
      case 251:
#line 1123 "parse.y"
{
    yygotominor.yy462 = sqlite3ExprListAppend(yymsp[-5].minor.yy462, yymsp[0].minor.yy342, &yymsp[-2].minor.yy308);
}
#line 2755 "parse.c"
        break;
      case 252:
#line 1127 "parse.y"
{
    yygotominor.yy462 = sqlite3ExprListAppend(0, yymsp[0].minor.yy342, &yymsp[-2].minor.yy308);                         
}
#line 2762 "parse.c"
        break;
      case 256:
#line 1135 "parse.y"
{ sqlite3CheckSetScope(pParse, &yymsp[-1].minor.yy0); }
#line 2767 "parse.c"
        break;
      case 258:
#line 1139 "parse.y"
{ yygotominor.yy308 = yymsp[0].minor.yy308; }
#line 2772 "parse.c"
        break;
      case 259:
#line 1140 "parse.y"
{ yygotominor.yy308 = yymsp[0].minor.yy0; }
#line 2777 "parse.c"
        break;
      case 262:
#line 1146 "parse.y"
{
    sqlite3ShowStatement(pParse, yymsp[0].major);
}
#line 2784 "parse.c"
        break;
      case 263:
#line 1150 "parse.y"
{
    sqlite3ShowStatement(pParse, yymsp[-1].major);
}
#line 2791 "parse.c"
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
#line 2858 "parse.c"
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
