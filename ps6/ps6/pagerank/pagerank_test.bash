#!/bin/bash
echo " " > pagerank_log.log

echo "*   *   *" >> pagerank_log.log
echo "Running 1 thread:" >> pagerank_log.log

./pagerank.exe -v 10 ../data/G_n_pin_pout.mtx -n 1 >> pagerank_log.log

echo "*   *   *" >> pagerank_log.log
echo "Running 2 threads:" >> pagerank_log.log

./pagerank.exe -v 10 ../data/G_n_pin_pout.mtx -n 2 >> pagerank_log.log 

echo "*   *   *" >> pagerank_log.log
echo "Running 4 threads:" >> pagerank_log.log

./pagerank.exe -v 10 ../data/G_n_pin_pout.mtx -n 4 >> pagerank_log.log

echo "*   *   *" >> pagerank_log.log
echo "Running 8 threads:" >> pagerank_log.log

./pagerank.exe -v 10 ../data/G_n_pin_pout.mtx -n 8 >> pagerank_log.log

