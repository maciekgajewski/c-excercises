set datafile separator ","
set logscale xy
#set xtics 1
set xlabel "size [bytes]"
set ylabel "time [ns]"

plot "seq.csv" using 11:3 with lines, "rand.csv" using 11:3 with lines