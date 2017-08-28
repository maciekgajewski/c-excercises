Fast square root a.k.a. Carmack's square root

Usage: carmack [<number> [<number> [...]]]

This program implements the fast square root (more precisely, the inverse
of the fast inverse square root). This algorithm gives a fast approximation
of the inverse square root of a number which is then once refined using
Newton's method.

For each input value, the program outputs one line containing
- the fast square root result
- the square root as calculated by std::sqrt
- the error percentage of the fast method compared to the std method

Example:

$ ./carmack 0.125 0.25 0.5 1 4 9 16 25 36
fastSqrt(0.125)=0.353642; std::sqrt(0.125)=0.353553; error=0.0250015%
fastSqrt(0.25)=0.500848; std::sqrt(0.25)=0.5; error=0.169575%
fastSqrt(0.5)=0.707284; std::sqrt(0.5)=0.707107; error=0.0250015%
fastSqrt(1)=1.0017; std::sqrt(1)=1; error=0.169575%
fastSqrt(4)=2.00339; std::sqrt(4)=2; error=0.169575%
fastSqrt(9)=3.00342; std::sqrt(9)=3; error=0.114163%
fastSqrt(16)=4.00678; std::sqrt(16)=4; error=0.169575%
fastSqrt(25)=5.00777; std::sqrt(25)=5; error=0.155363%
fastSqrt(36)=6.00685; std::sqrt(36)=6; error=0.114163%

The error percentage of this implementation remains under 0.17% which
is consistent with documentation [1]. The error is also always positive,
i.e. the fast square root result is always greater than the std square
root result.

[1] https://en.wikipedia.org/wiki/Fast_inverse_square_root
