#!/bin/bash

binaries=( "./C/bin/sierpinski" )
args=( "./image-test.bmp 6" )
iterations=10
benchmark_bin=./do_benchmark;

if [ ! -f $benchmark_bin ]; then
    echo -n "Compiling benchmark ... "
    gcc -Wall $benchmark_bin.c -o $benchmark_bin
    echo "Done."
fi

for (( i=0; $i < ${#binaries[*]}; i++ ))
do
    counter=0
    min=;
    max=;
    avg=;
    current_time=;
    total_time=0.0;

    exe=${binaries[$i]};
    arg=${args[$i]};
    echo "Benchmarking: $exe $arg";
    while [ $counter -lt $iterations ]; do
	current_time=$($benchmark_bin $exe $arg | awk 'NR == 4 {print $2}');
	rm ./image-test.bmp;

	if [ -z $min ] || (( $(echo "$min > $current_time" | bc -l) )); then
	    min=$current_time;
	fi
	if [ -z $max ] || (( $(echo "$max < $current_time" | bc -l) )); then
	    max=$current_time;
	fi
	total_time=$(echo "$total_time+$current_time" | bc -l);
	(( counter++ ))
    done
    avg=$(echo "scale=6; $total_time/$iterations" | bc -l)
    # Prepend 0 if needed
    if [[ $avg == .* ]]; then
	avg="0"$avg;
    fi
    echo "Min: $min, Max: $max, Avg: $avg";
done

