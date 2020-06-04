#!/bin/bash
echo " " > norm_logs.log
echo "Norm_block_reduction: " >> norm_logs.log
./norm_block_reduction.exe 128 4096 8 >> norm_logs.log 
echo "* 		* 		*" >> norm_logs.log
echo "Norm_block_critical: " >> norm_logs.log
./norm_block_critical.exe 128 4096 8 >> norm_logs.log 
echo "* 		* 		*" >> norm_logs.log
echo "Norm_cyclic_critical: " >> norm_logs.log
./norm_cyclic_critical.exe 128 4096 8 >> norm_logs.log
echo "* 		* 		*" >> norm_logs.log
echo "Norm_cyclic_reduction: " >> norm_logs.log
./norm_cyclic_reduction.exe 128 4096 8 >> norm_logs.log
echo "* 		* 		*" >> norm_logs.log
echo "Norm_parfor: " >> norm_logs.log
./norm_parfor.exe 128 4096 8 >> norm_logs.log