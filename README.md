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
4000 print "prints some numbers out, demos for loops, and thats it"
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
- **gosub** expression 
- **return**
  - similar to goto except the line jumped from is stored on a stack and retrieved for a jump using the return command 
- **input** identifier
  - takes input from std::cin and stores it in the var
- **print** expression
  - outputs result of the expression once evaluated to std::cout 
- **let** lhs_expression **=** expression
  - assignment 

## todo

- **loops** 
  - various loops while, for, etc
- **dim** 
  - dim identifier ( expression )
- **sigils** 
  - for types $ for text and % for numbers
- **TUI** 
  - ncurses or similar
- **Graphics** 
  - SFML/SDL or similar
- **metaprogramming** 
  - expose the interpreter via API to the language
- **threads** 
  - exactly how tbd


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