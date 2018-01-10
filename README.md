# lemon
C Sql parser from sqlite, the lemon is using in Atlas sharding branch. 

please See [sharding doc](https://github.com/Qihoo360/Atlas/wiki/Atlas-Sharding)

# Lemon 简介及sqlite parse.y改进

Lemon 是一个sqlite用于解析sql语句的语法分析器. 配合着sqlite 源码tokenize.c中的分词器, 可以完整的处理sql语句.

Lemon的作用类似于"yacc" 或者 "bison", 但是lemon作为后期之秀, 有着其独特的语法以及一些优势.

Lemon 相比yacc 的区别(优势)如下:

* 由于lemon作者声明绝不(或者极少)使用全局变量和static变量, Lemon是可重入和线程安全的. 
* 输出的解析引擎比yacc和Bison的速度更快
* 在yacc中, 由parser(语法分析器)调用lexer(词法分析器), 而在lemon中由lexer调用parser
* Lemon不使用全局变量在lexer和parser之间传递信息

线程安全这个对于现代并行的程序来说是很重要的一个效率提升点. 我们也可以看到Mysql中使用了yacc, 故其调用语法分析器的时候都是需要加上锁的. sqlite在分词器中还使用了一些小技巧, 其分词器的效率表现也是非常的优秀的.

## 编译lemon

Lemon的源代码只有4000多行, 在sqlite就是一个lemon.c文件. 编译lemon非常的简单:

```
$ gcc -o lemon lemon.c
```

它还依赖一个src/lempar.c文件, 这是用于生成解析引擎的时候的模板文件. 在sqlite中, 要生成语法解析器, 只需要如下几步:

```
$ ./lemon parse.y

$ mv parse.h parse.h.temp
$ awk -f addopcodes.awk parse.h.temp > parse.h
```
```./lemon parse.y```这个操作会生成parse.h文件和parse.c文件, 实际环境中sqlite还会在parse.h通过awk加入一些定义, 这个不是我们讨论的重点.

## 解析器接口

lemon生成的并不是可以直接运行的程序, 其生成的是给宿主如sqlite, 调用的c代码, 在每次分析sql时调用这些函数.

在使用Lemon生成的解析器之前，必须先创建一个解析器实例，就像下面这样：

```
   void *pParser = ParseAlloc( malloc );
 ```
 
ParseAlloc()函数分配并初始化一个新解析器，并返回指向它的指针。而解析器实际的数据结构对用户是透明的——内部结构不可见。因此，ParseAlloc()返回的是void *指针而不是指向某种特定结构的指针。仅有的一个参数是用来分配内存的接口，其原型同标准库的malloc()函数。

我们在sqlite源码中看到的对应函数就是sqlite3ParserAlloc, 这是因为sqlte在语法文件中用如下指令声明了前缀.

```
%name sqlite3Parser
```

在不再需要此解析器时，可以回收分配的内存：

```
  ParseFree(pParser, free);
```

在解析器实例化后，就可以向其中输入记号（终结符）流进行解析了。下面的函数每次接受一个非终结符。

```
   Parse(pParser, hTokenID, sTokenData, pArg);
```

第一个参数为解析器实例，第二个参数是一个 正整数，代表非终结符类型。这些类型都用#define预处理指令定义在Lemon输出的头文件"parse.h"中。如果第二个实际参数值为0，则表明输入记号流终结（EOF）。第三个参数代表此Token的值，在默认情况下，第三个参数的默认参数类型是int，但语法文件中经常需要重定义这个类型为某种结构。

Parse()函数可以有三个或四个参数，这取决于语法定义。如果语法需要，Parse()函数可以有任意类型（由用户定义）的第四个参数，解析器并不处理这个参数，而仅仅把它传递给用户提供的动作。这可以方便的被用来传递参数给解析器内部，而不需要动用全局变量。

## Lemon语法

### 终结符和非终结符

lemon语法中的符号分为终结符和非终结符两种, 终结符的意思是这个符号已经是定义的终点了, 不会再有其他的定义, 但是非终结符会有别的语法规则对其进行定义. 终结符在lemon里面一般是全部大写表示的, 非终结符里面一般是全部小写表示.

### 终结符是如何产生的

我们看到这里, 在parse.y语法文件中有许多的终结符, 诸如STRING, AND, SEMI, OR, SELECT等等等, 这些终结符会被相应的加上前缀"TK_"在parse.h中定义(./lemon parse.y生成):

```
#define TK_SEMI                            1
#define TK_EXPLAIN                         2
#define TK_QUERY                           3
#define TK_PLAN                            4
#define TK_BEGIN                           5
#define TK_START                           6
#define TK_TRANSACTION                     7
#define TK_WORK                            8
#define TK_COMMIT                          9
#define TK_ROLLBACK                       10
...
```

那么一串SQL字符串是怎么变成这些记号的呢, 这个时候就需要分词器了, 我们看到在sqlite的src/tokenize.c中有

```
static int getToken(const unsigned char *z, int *tokenType)
```
函数, 这个就是sqlite的分词器, 例如参数z传入";", 它会由

```
switch( *z ){
...

case ';': {
      *tokenType = TK_SEMI;
      return 1;
    }
    
...
}
```

就是这样得到了tokenType 为TK_SEMI, 然后通过

```
sqlite3Parser(pEngine, tokenType, pParse->sLastToken, pParse);
```

这个函数传给语法分析器, 这样语法分析器就能对这些符号进行语法分析了. 这就是所谓的与yacc不同的方式, 分词器调用语法分析器.

### 语法规则

Lemon语法文件的主要部分是一系列的语法规则。每个语法规则由一个非终结符后跟"::="，接着是（非）终结符的列表。产生式右侧可以为空。产生式可以以任何顺序书写，但第一条被当作开始符号。（除非用%start指令另外指定）。典型的语法规则就像下面这样：

```
// Input is a single SQL command
input ::= cmdlist.
cmdlist ::= cmdlist ecmd.
cmdlist ::= ecmd.
cmdx ::= cmd.           { sqlite3FinishCoding(pParse); }
ecmd ::= SEMI.
ecmd ::= explain cmdx SEMI.

explain ::= .           { sqlite3BeginParse(pParse, 0); }

explain ::= EXPLAIN.              { sqlite3BeginParse(pParse, 1); }
explain ::= EXPLAIN QUERY PLAN.   { sqlite3BeginParse(pParse, 2); }

```

这是sqlite parse.y中的第一段语法规则定义.解析就是从这里开始.

***input ::= cmdlist.***

input和cmdlist都是非终结符, 就是说还有对其的定义. 我们看到SEMI就是一个终结符, 在parse.h就定义为TK_SEMI, 表示是一个";"分号, 这是没办法再对它定义的了, 所以是一个终结符.

到目前我们还不知道cmdlist为何物, 我们继续往下看

```
cmdlist ::= cmdlist ecmd.
cmdlist ::= ecmd.
```

这里定义了两个cmdlist. ***cmdlist ::= cmdlist ecmd.*** 它自己本身再接一个ecmd, 说明这个cmdlist是一个列表, 组成成分为多个ecmd或者***cmdlist ::= ecmd.***, 单个ecmd.

ecmd 同样不是终结符, 那么我们继续看下去

```
ecmd ::= SEMI.
ecmd ::= explain cmdx SEMI.
explain ::= .           { sqlite3BeginParse(pParse, 0); }

explain ::= EXPLAIN.              { sqlite3BeginParse(pParse, 1); }
explain ::= EXPLAIN QUERY PLAN.   { sqlite3BeginParse(pParse, 2); }
```

这里的意思是, ecmd可以为";", 就是一个空的sql, 或者是一个explain语句, 我们看到这个explain 有一个定义如下```explain ::= .```, 也就是说也可以没有explain, 正常的explain语法是:

```
explain ::= EXPLAIN.              
explain ::= EXPLAIN QUERY PLAN.   
```

我们看到cmd其实是我们真正的sql语句. 下面会挑一些相应的sql语句的cmd定义来分析

***注意***, 我们看到这里sqlite规定的sql语句是必须";"分号结尾的, 那么对于没有分号的sql语句sqlite难道就不支持吗, 其实, sqlite是自己帮我们加上了这个SEMI的终结符, 我们看到sqlite3RunParser函数里面的最后有这么一段代码:

```
if( zSql[i]==0 && nErr==0 && pParse->rc==SQLITE_OK ){
    if( lastTokenParsed!=TK_SEMI ){ // 如果最后一个TOKEN不是TK_SEMI, 那么补上一个
      sqlite3Parser(pEngine, TK_SEMI, pParse->sLastToken, pParse);
      pParse->zTail = &zSql[i];
    }
    sqlite3Parser(pEngine, 0, pParse->sLastToken, pParse);
}
```

我们看到语法定义的右边有一些有"{}"括起来的c代码, 那些就是当匹配到当前规则时做的操作.

### 动作与语法的关联变量

为了对语义值进行操作，语义动作必须和语法规则联系起来。在yacc和bison中，用'$$'标志产生式左侧非终结符的语义值，而用符号"$1"，"$2"等来代表产生式右侧的终结符/非终结符的语义值。这个方法广为人知，但也很容易导致错误。最常见的就是数错产生式右侧符号的个数。

Lemon不使用这种Shell风格的变量表示方法，而是在产生式中使用显式的符号名字，然后在动作部分可以用这些名字应用对应的语义值。在yacc或bison中，可能写成这样：

```
  expr -> expr PLUS expr  { $$ = $1 + $3; };
```

这种按index来指定语义值的方法, 稍不留神就会出错.

但在Lemon中，同样的规则则是：

```
 expr(A) ::= expr(B) PLUS expr(C).  { A = B+C; }
```

在Lemon规则中，任何在跟在语法规则符号之后，由括号包裹的符号自动成为语义值占位符，占位符可以在C代码中被引用来表示其语义值。
Lemon的方法在很多方面优于yacc; 第一，就像之前提到的，Lemon的方法避免了对语法符号进行记数; 第二，如果在语法规则中指定了占位符，但在规约动作中没有引用它，那么Lemon会提示出错，例如：

```
  expr(A) ::= expr(B) PLUS expr(C).  { A = B; }
```

上面的规则将产生错误，因为占位符C在规约动作中没用到。同时这种记法还可以方便的在语义动作中回收相关的内存资源。

另外还有一种'@'符号, 这个在其文档中并未提及, 但是我们在parse.y中看到, 如:

```
term(A) ::= STRING(X).       {A = sqlite3Expr(@X, 0, 0, &X);}
```

***"@X"*** 在这里表示的就是TK_STRING, 就是终结符自己本身.

### 优先级

在众多的终结符中, 不是所有的终结符都是一样的, 他们之间有运算的优先级, 如加法的终结符PLUS跟乘法的终结符TIMES, 当然是TIMES的优先级要高, 那么这个时候要怎么办呢, lemon是通过特殊指令"%left", "%right" 和 "%nonassoc"来指定的.

在文件较上方的指令指定的终结符比下方的优先级低。

```
   %left AND.
   %left OR.
   %nonassoc EQ NE GT GE LT LE.
   %left PLUS MINUS.
   %left TIMES DIVIDE MOD.
   %right NOT.
```

PLUS和MINUS有左结合性, TIMES DIVIDE MOD也有左结合性, 但是其位于PLUS MINUS之后定义优先级规则, 所以其有更高的优先级, 而NOT有右结合性.

在上面的指令序列中，AND运算符的优先级最低，OR比AND高……因此，语法会解决二义性的表达式：

```
     a AND b OR c
```

像这样:

```
  a AND (b OR c).
```

结合性（left,right或者nonassoc）用来决定有限级相同时的二义性问题，AND在例子中是左结合的

```
     a AND b AND c
```

等价于

```
     (a AND b) AND c.
```

nonassoc指令用于指出无结合性的运算符，例如

```
     a EQ b EQ c
```

将产生错误。

产生式之间的优先级取决于产生式右侧最左边的已经定义了优先级的终结符/。这可能是你想要的，但在某些情况下，当你需要调整产生式优先级时，像下面这样，在规则之后，C代码之前放置：

```
   expr = MINUS expr.  [NOT]
```

这个产生式的优先级将等于NOT符号，而不是默认的减号(MINUS)。

### 特殊指令

Lemon接受的输入语法包括语法规则和特殊指令, 上面我们已经介绍过了语法规则的定义, 下面介绍特殊指令.Lemon中的指令可以按照任意顺序出现，你可以把它们放置在语法规则之前，或者之后，甚至中间，效果是相同的。赋优先级值的指令之间的相对顺序是有意义的，但其他的指令顺序则无所谓。

这里只挑几个对我们分析有用的几个特殊指令解释, 其他请参考lemon的[文档](http://www.hwaci.com/sw/lemon/lemon.html)

#### %destructor 

%destructor指令用来为非终结符指定析构函数(类似的%token_destructor指令则为终结符指定析构函数)。

当非终结符被弹出栈时，包括下面这些情况，将执行析构函数：

* 当产生式规约，同时产生式右侧某非终结符的语义值在C代码中未被引用。(这个在一些规则中实际情况是未调用析构函数的, 需要手动释放, 否则会有内存泄露, 这个问题还没有找到具体的原因)
* 错误处理时，堆栈中不断弹出记号。
* 执行ParseFree()函数。
  
析构函数可以对非终结符的语义值做任何事情，但设计上，一般只用来释放占用的内存等资源.


#### %token_type 和 %type

这两条指令用于为解析器堆栈中的终结符和非终结符指定数据类型。所有的终结符数据类型一致，也就是Parse()函数的第三个参数。典型的，终结符的类型可以是指向某个结构的指针。

```
   %token_type    {Token*}
```   
   
如果没有为终结符指定数据类型，默认值为"int"。

不同的非终结符一般有自己的数据类型，典型的非终结符数据类型是指向包含所有信息的解析树树根的指针，例如：

```
   %type   expr  {Expr*}
```



### Insert/Replace Statement

下面我们就可以开始看看parse.y对一些sql语句的解析了.

这里我们挑Insert/Replace这个常见的sql语句的语法来分析以及我们对其做了一些什么改进.我们先看parse.y 对其的定义, 

```
////////////////////////// The INSERT command /////////////////////////////////
//                                                                                                                                                                                cmd ::= insert_cmd(R) INTO fullname(X) inscollist_opt(F)                                                                                                                                  VALUES LP itemlist(Y) RP.                                                                                                                                                             {sqlite3Insert(pParse, X, Y, 0, F, R);}  
                                                                                                                             cmd ::= insert_cmd(R) INTO fullname(X) inscollist_opt(F) select(S).                                                                                                                           {sqlite3Insert(pParse, X, 0, S, F, R);}    
                                                                                                                                                                                                                                                                                                                                                                                                                                          %type insert_cmd {int}                                                                                                                                                            insert_cmd(A) ::= INSERT.   {A = OE_Default;}                                                                                                                                    insert_cmd(A) ::= REPLACE.            {A = OE_Replace;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               %type itemlist {ExprList*}                                                                                                                                                        %destructor itemlist {sqlite3ExprListDelete($$);}
```
作为Insert的语法定义, 并不算长, 我们先看cmd的定义:```cmd ::= insert_cmd(R) INTO fullname(X) inscollist_opt(F) VALUES LP itemlist(Y) RP.```, 

首先```insert_cmd(R)``` 用来定义INSERT或者REPLACE, 

```
%type insert_cmd {int}
insert_cmd(A) ::= INSERT.   {A = OE_Default;}                                                                                                                                    insert_cmd(A) ::= REPLACE.            {A = OE_Replace;} 
```

%type 定义insert_cmd为一个int类型, 所以, insert_cmd(R)中的R是一个int变量, 如果是遇到的是INSERT终结符, 其值会为OE_Default, 如果是REPLACE, 其值就会为OE_Replace, 会在最后归约的时候传入```sqlite3Insert(pParse, X, Y, 0, F, R);```的最后一个参数

然后会语法解析器期望得到一个TK_INTO的终结符, 如果不是这个终结符, 那么这条语法规则就无法成立, 就会寻找下一个语法规则.

```fullname```, 从名字上看, 这应该是一个名字, 是要插入的表的名字(也可以包含数据库的名字, 所以这里叫fullname). ```inscollist_opt```, 应该是要插入的column的列表. 我们逐一来看.

```
%type fullname {SrcList*}
%destructor fullname {sqlite3SrcListDelete($$);}
fullname(A) ::= nm(X) dbnm(Y).  {A = sqlite3SrcListAppend(0,&X,&Y);}

// The name of a column or table can be any of the following:
//
%type dbnm {Token}
dbnm(A) ::= .          {A.z=0; A.n=0;}
dbnm(A) ::= DOT nm(X). {A = X;}

%type nm {Token}
nm(A) ::= ID(X).         {A = X;}
nm(A) ::= STRING(X).     {A = X;}
nm(A) ::= JOIN_KW(X).    {A = X;}
```

%type指定了fullname是一个SrcList*, %destructor指定了fullname的析构器是调用sqlite3SrcListDelete. 我们看到fullname是由nm和dbnm组成的, 其中```dbnm(A) ::= .```, 说明dbnm是可以为空的. 也可以是一个"."接上一个nm.

nm的语法规则可以看到, 可以是一个STRING, "CROSS", ID(一个不带引号的字符串), 具体为什么是这几个终结符, 请查看mkkeywordhash.c以及tokenize.c文件. 这里我们可以理解就是一个表示表名的一个字符串.

我们接着看***inscollist_opt***

```
%type inscollist_opt {IdList*}
%destructor inscollist_opt {sqlite3IdListDelete($$);}
%type inscollist {IdList*}
%destructor inscollist {sqlite3IdListDelete($$);}

inscollist_opt(A) ::= .                       {A = 0;}
inscollist_opt(A) ::= LP inscollist(X) RP.    {A = X;}
inscollist(A) ::= inscollist(X) COMMA nm(Y).  {A = sqlite3IdListAppend(X,&Y);}
inscollist(A) ::= nm(Y).                      {A = sqlite3IdListAppend(0,&Y);}
```

inscollist_opt是一个IdList结构. 其可以为空, 也就是不需要提供要插入的column, 如"insert into test values(1, 'test');": 

```
inscollist_opt(A) ::= .
```

正常提供column的例子是(id, name), 由以下的规则来匹配:

```
inscollist_opt(A) ::= LP inscollist(X) RP.
```

LP在这里表示的"(", 左括号的终结符, RP是")"右括号的终结符, 这些终结符都是由分词器产生的. 我们继续看看inscollist的语法规则, 它可以单独就只有一列

```
inscollist(A) ::= nm(Y).
```
但是还有多列的情况, 用如下的规则来匹配:

```
inscollist(A) ::= inscollist(X) COMMA nm(Y).
```

这里很特别, 自己用了自己的定义, 这是定义一个列表的标准写法. 意思是一个递归, 如果后面不断的COMMA 和 nm, 那么就会不断的扩展这个inscollist. 把inscollist写在左边是有原因, 是lemon为了避免递归导致栈溢出的一种做法.

***

看完了这些, 我们再来看看insert产生式中最后一部分 ```"VALUES LP itemlist(Y) RP."``` 

VALUES终结符对应的是"VALUES"这个关键字, 我们看看itemlist, 看起来又是一个列表.应该和inscollist差不多.

```
%type itemlist {ExprList*}
%destructor itemlist {sqlite3ExprListDelete($$);}

itemlist(A) ::= itemlist(X) COMMA expr(Y).  {A = sqlite3ExprListAppend(X,Y,0);}
itemlist(A) ::= expr(X).                    {A = sqlite3ExprListAppend(0,X,0);}
```

我们看到, 它也是一个左递归, 可以不断的扩展这个列表, 每一个值都是一个expr(表达式), 这个expr的表达式的语法规则比较复杂, 我们就不继续往下深入看了, 有兴趣的同学可以自己到parse.y中研究.

第二种情况是Insert的值来自于select, 这个语法就留给大家去研究了(大同小异).

```
cmd ::= insert_cmd(R) INTO fullname(X) inscollist_opt(F) select(S). 
```

到这里我们就把insert的语法规则分析完了, 细心的同学可能已经发现了问题, sqlite中直支持单个values插入的sql, 而不支持mysql那样多值插入的特性, 如"insert into test values(1, 'test'), (2, 'test')", 是会报语法错误的.

### 增加INSERT多值插入语法.

我们将VALUES部分的语法修改为:

```
cmd ::= insert_cmd(R) INTO fullname(X) inscollist_opt(F) VALUES valueslist(VL).
            {sqlite3Insert(pParse, X, VL, 0, F, R);}
            
%type valueslist {ValuesList*}
%destructor valueslist {sqlite3ValuesListDelete($$);}

valueslist(VL) ::= valueslist(V) COMMA LP itemlist(Y) RP.   { VL = sqlite3ValuesListAppend(V, Y);}
valueslist(VL) ::= LP itemlist(Y) RP.                       { VL = sqlite3ValuesListAppend(0, Y); }
```

我们只需要增加一个valueslist, 把itemlist包起来就可以了.这样就可以支持多值插入了.

## 结论

lemon作为语法分析器, 其语法相信大家已经领略过了, 是很简单易懂的, 而且其提供的语法特性也防止了内存泄露和一些人为的疏漏. 在性能方面, 由于其线程安全, 没用使用全局变量来共享数据, 所以可以不用加锁使用它, 在这一点上, 是要比yacc优秀不少的.



