set datafile separator ","
set logscale xy
set xlabel "size [bytes]"
set ylabel "time [ns]"

plot 'vector.csv' using 11:3, 'list.csv' using 11:3