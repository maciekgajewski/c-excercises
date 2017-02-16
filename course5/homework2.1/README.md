I measured the error of the fast inverse square root used by John Carmack in
the original Quake compared to sqrt implemented in the standard C++ library.

I calculated the difference of the two function and the relative difference to
the input value. The program measures the difference for a range of input
values interesting to real time 3D graphics calculations.

The results are written to the standard output tab separated. I plotted the
relative difference with gnuplot:

    gnuplot> set logscale xy
    gnuplot> plot 'sqrt.dat' using 1:5 title "relative difference
