set datafile separator ","
set logscale xy
#set xtics 1
set xlabel "size [bytes]"
set ylabel "time [ns]"

plot "seq.csv" using 11:3, "rand.csv" using 11:3