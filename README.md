# vanilla-basic

MIT Licensed old fashioned basic interpreter written in c++. Wsing stl datastructures instead of a low level machine to maintain the exection status.

~~~ basic

10 print "hello world"
20 goto 10

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
- **dim** identifier ( expression )

