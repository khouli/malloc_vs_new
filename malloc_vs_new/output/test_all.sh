#!/usr/bin/env bash

#ARRAY_SIZE=4000
ARRAY_SIZE=16000

g++-4.8 -Ofast -march=native -std=c++11 -DARRAY_SIZE=$ARRAY_SIZE malloc_heap_version3.cpp -o gcc_malloc_heap_version3
g++-4.8 -Ofast -march=native -std=c++11 -DARRAY_SIZE=$ARRAY_SIZE heap_version3.cpp        -o gcc_heap_version3
icc -O3 -ipo -no-prec-div    -std=c++11 -DARRAY_SIZE=$ARRAY_SIZE malloc_heap_version3.cpp -o icc_malloc_heap_version3
icc -O3 -ipo -no-prec-div    -std=c++11 -DARRAY_SIZE=$ARRAY_SIZE heap_version3.cpp        -o icc_heap_version3

echo "compiler method cycles" > cycles.txt
for i in $(seq 1 10000); do
	echo gcc malloc $(./gcc_malloc_heap_version3 | head -n 1 | cut -d" " -f 4-)
	echo icc malloc $(./icc_malloc_heap_version3 | head -n 1 | cut -d" " -f 4-)
	echo gcc new $(./gcc_heap_version3 | head -n 1 | cut -d" " -f 4-)
	echo icc new $(./icc_heap_version3 | head -n 1 | cut -d" " -f 4-)
done >> cycles.txt

Rscript plot.R

g++-4.8 -v 2> info.txt
icc -v 2>> info.txt
