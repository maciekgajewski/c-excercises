Square root calculation using Newton's method, recusrively

Usage: carmack [<number> [<number> [...]]]

This program calculates square roots using a recusrive implementation
of Newton's method. The recursion continues until the result converges
to stable (i.e. there is no difference between the input and the output
of the recursion step), or the recursion reaches a depth of 10000.

For educational purposes, the program also records the recursion depth
reached and the growth of the stack.

For each input value, the program outputs one line containing
- the square root of the input
- the recusrion depth reeached
- growth of the stack between the first and last level of recursion

Example:

$ ./newton 1 4 9 16 25 36
newtonSqrt(1)=1; recursion depth: 1; stack growth between first and last recursion: 0
newtonSqrt(4)=2; recursion depth: 7; stack growth between first and last recursion: 84
newtonSqrt(9)=3; recursion depth: 7; stack growth between first and last recursion: 84
newtonSqrt(16)=4; recursion depth: 7; stack growth between first and last recursion: 84
newtonSqrt(25)=5; recursion depth: 7; stack growth between first and last recursion: 84
newtonSqrt(36)=6; recursion depth: 7; stack growth between first and last recursion: 84

This output can be used to illustrate the effect of building with debug flags
on:

$ ./newton 1 4 9 16 25 36
newtonSqrt(1)=1; recursion depth: 1; stack growth between first and last recursion: 0
newtonSqrt(4)=2; recursion depth: 5; stack growth between first and last recursion: 256
newtonSqrt(9)=3; recursion depth: 6; stack growth between first and last recursion: 320
newtonSqrt(16)=4; recursion depth: 7; stack growth between first and last recursion: 384
newtonSqrt(25)=5; recursion depth: 7; stack growth between first and last recursion: 384
newtonSqrt(36)=6; recursion depth: 7; stack growth between first and last recursion: 384

It is very interesting to see that not only are the stack frames of a debug
build significantly larger, for some cases the algorithm even requires a
different number of recursions to reach the same result. One possible
explanation is certain compiler optimizations not being enabled on debug
builds leading to different execution path, but more research would be
required as to which mechanism exactly is responsible for this behavior.

Also of note is that the stack size calculation is done by subtracting the
"top" memory address from the "bottom" memory address instead of the other
way around, because the stack grows downward on x86 architectures.
