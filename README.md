# vanilla-basic

MIT Licensed BASIC interpreter.

Old fashioned basic interpreter written in c++. Wherever possible using stl datastructures instead of mimicing a low level machine to maintain the exection status.

Working from the definition of basic outlined in the wikipedia [page on BASIC](https://en.wikipedia.org/wiki/BASIC) and [BASIC interpreters](https://en.wikipedia.org/wiki/BASIC_interpreter).

Small and Simple to understand.

Collaborations welcome!

Parses and executes BASIC code like this...

~~~ basic
10 print "hello world"
20 goto 10
~~~

~~~ basic
50 print "please enter your age..."
100 let age = 0
110 input age
120 let age = age + 1
150 print "you are ..."
160 print age
170 print "years old"
180 print "(computers never make mistakes, lol)"
~~~

~~~ basic
1100 print "main routine"
1110 gosub 2000
1120 print "main routine again"
1130 gosub 3000
1140 goto 3020
2000 print "subroutine at line 2000"
2010 return
3000 print "subroutine at line 3000"
3010 return
3020 print "end"
~~~

~~~ basic
5000 print "repeat until loop"
5010 let counter = 10
5020 repeat 
5030 let counter = counter - 1
5040 print counter
5050 until counter <= 0
~~~

~~~ basic
4000 print "prints some numbers out, demos nexted for loops"
4010 for xpos = 1 to 10
4015 for ypos = 1 to 10
4020 print xpos
4025 print ypos
4030 next
4035 next
~~~


## language features include

- **rem** 
  - single line comments
- **goto** expression
  - jumps/continues execution at the line which has the number equal to the result of the expression
- **expressions v1**
  - expr :== const | identifier
  - expr ::= expr op expr
  - expr ::= expr rop expr
  - op ::= + - * / etc
  - rop ::= >= <= etc
- **gosub** expression 
- **return**
  - similar to goto except the line jumped from is stored on a stack and retrieved for a jump using the return command 
- **input** identifier
  - takes input from std::cin and stores it in the var
- **print** expression
  - outputs result of the expression once evaluated to std::cout 
- **let** lhs_expression **=** expression
  - assignment 
- **repeat until** 
  - bottom comparison
  - jump back fom bottom

## todo

- **expressions v2**
  - expressions now include brackets
  - expr ::= ( expr )
- **while wend** 
  - top comparison
  - jump forward over optinal OR jump back from bottom?
- **for loop** 
  - top comparison
  - counter logic
  - jump back fom bottom
- **array declaration and access** 
  - dim identifier ( expression )
  - identifier [ expression ]
- **arrays evaluated correctly in rhs expressions** 
  -  lhs = identifier ( expression )
- **arrays evaluated correctly in lhs expressions** 
  -  expression op identifier [ expression ] op expression = rhs
- **sigils** 
  - for types $ for text and % for numbers
  - how do strings interract with expressions?
- **TUI** 
  - ncurses or similar
- **Graphics** 
  - SFML/SDL or similar
- **metaprogramming** 
  - expose the interpreter via API to the language
- **threads** 
  - exactly how tbd
  - perhaps each BASIC file is a thread?
  - and spawn ( fname ) ?


## Instructions

### linux

build via cmake

~~~ csh
git clone proj-name 
cd proj-name
cd build
cmake ..
make
./vanillabasic
~~~

### windows / osx

please help

