This is the benchmarking code that was used in this Stackoverflow question:
http://stackoverflow.com/q/22684123/1128289

The benchmark is run by sourcing the file test_all.sh. Running the benchmark
requires g++ 4.8 and icc.  The script also plots and summarizes the results.
For this R and ggplot2 are required.

The directory output contains the contents of the directory for me after
sourcing test_all.sh.

The benchmark produces a curious result. Code produced by icc seems to
be slower when allocating memory using malloc() compared to new.

Elapsed clock cycles for allocating a 16000 elment char array:

![alt text](http://i.stack.imgur.com/BKQR4.png "elapsed clock cycles for allocating array")

Check the Stackoverflow question for more details.
