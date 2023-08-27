
10 rem goto 5000

90 print "please enter your age..."
100 let age = 0
110 input age
120 let age = age + 1
150 print "you are ..."
160 print age
170 print "years old"
180 print "(computers never make mistakes, lol)"

1100 print "main routine"
1110 gosub 2000
1120 print "main routine again"
1130 gosub 3000
1140 goto 3020

2000 print "subroutine at line 2000"
2010 return

3000 print "subroutine at line 3000"
3010 return
3020 print "end subroutines"

4000 print "repeat until loop"
4010 let counter = 10
4020 repeat 
4030 let counter = counter - 1
4040 print counter
4050 until counter <= 0
4060 print "end repeats"


5000 print "for next loop"
5010 let maxx = 10
5010 for xpos = 1 to maxx
5030 print xpos
5060 next
5070 print "end for next loop"

6000 print "all done"
