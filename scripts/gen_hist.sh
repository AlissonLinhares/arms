WSCALE=40
HSCALE=5

data_size=`cat $1 | wc -l`
width=`expr $data_size \* $WSCALE`
height=`expr $data_size \* $HSCALE`

gnuplot <<- EOF
	#!/usr/bin/gnuplot
	set terminal png size $width, $height noenhanced font "Helvetica,20"
	set output "$2"
	set style data histogram
	set style histogram cluster gap 1
	set style fill solid
	set boxwidth 1
	set xtics format ""
	set grid ytics
	set xtics rotate by 45 right
	set key noenhanced
	set title "$(basename $1)"
	set autoscale y
	set ylabel "Mapping size"
	set style line 1 lt 2 lw 4 pt 3 ps 0.5 lc rgb "#00FF00"

	plot "$1" using 2:xtic(1) axes x1y1 title "$3" linecolor rgb "$4"
EOF

gpicview $2
