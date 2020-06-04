
Questions
=========

Norm
----

* Look through the code for ``run()`` in ``norm_utils.hpp``.  How are we setting the number of threads for OpenMP to use?
we are setting it in a for loop using,
omp_set_num_threads(nthreads)

* Which version of ``norm`` provides the best parallel performance?  How do the results compare to the parallelized versions of ``norm`` from ps5?
norm_block_critical has the highest performance on par witht he performance we saw in last weeks asignment. and all i did was add like 1 line. I put all the results in norm_logs.log (great redundant performance)

* Which version of ``norm`` provides the best parallel performance for larger problems (i.e., problems at the top end of the default sizes in the drivers or larger)?  How do the results compare to the parallelized versions of ``norm`` from ps5?
excluding Block_critical()
norm_parfor() seems to do the best at low sizes. It didn't break at 128 like the ones from last week

* Which version of ``norm`` provides the best parallel performance for small problems (i.e., problems smller than the low end of the default sizes in the drivers)?  How do the results compare to the parallelized versions of ``norm`` from ps5?  
xcluding Block_critical()
norm_parfor() seems to do the best at high sizes. still a lot lower than critical.

Sparse Matrix-Vector Product
----------------------------

* How does ``pmatvec.cpp`` set the number of OpenMP threads to use?
omp_set_num_threads(nthreads);
same as before

* (For discussion on Piazza.)
What characteristics of a matrix would make it more or less likely to exhibit an error 
if improperly parallelized?  Meaning, if, say, you parallelized ``CSCMatrix::matvec`` with just basic  columnwise partitioning -- there would be potential races with the same locations in ``y`` being read and written by multiple threads.  But what characteristics of the matrix give rise to that kind of problem?  Are there ways to maybe work around / fix that if we knew some things in advance about the (sparse) matrix?
i could see a solution being to do a critical hold on any columns with repeated locations in y to try and resolve the race.


* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?
at first i just put, 
#pragma omp parallel for
on each of the threads, and that worked big performance increase with thread count

So then I tried,
#pragma omp critical
#pragma omp parallel for
 on some of the CSC ones and I noticed a drop in performance of around a GFLOP. 


then I added,
#pragma omp parallel for schedule(static,1)
To CSR and again performance dropped but only slightly (~.3)

So the best was just straight up #pragma omp parallel for. but this could be because I had to use an old OpenMP because I have like stoneage XCode on this monster

Sparse Matrix Dense Matrix Product (AMATH583 Only)
--------------------------------------------------


* Which methods did you parallelize?  What directives did you use?  How much parallel speedup did you see for 1, 2, 4, and 8 threads?  How does the parallel speedup compare to sparse matrix by vector product?
for COO i did the classic:
#pragma omp parallel for 
and that seemed to speed it up. It had doubled by 4 threads and then leveled off at 8. silimar to before.
then for CSC I did.
#pragma omp parallel for schedule(static,1)
which had more of a steady linear increase from .66 to 1.2 to 2.4 at 8 threads
then finally i tried to combine 
#pragma omp parallel for 
with 
#pragma omp critical
and this actually caused everything to slow down tremendously. So i think you would need to combine this with somecareful parallel coding to make it work better.



PageRank Reprise
----------------

* Describe any changes you made to pagerank.cpp to get parallel speedup.  How much parallel speedup did you get for 1, 2, 4, and 8 threads?
I changed CSR matrix to CSC matrix and used the #pragma omp parallel command. As you can see from pagerank_log.log there is a significant doubling of speed up to 4 threads which levels off at 8

* (EC) Which functions did you parallelize?  How much additional speedup did you achieve?
again just parallelizing CSC worked

Load Balanced Partitioning with OpenMP (Extra Credit)
-----------------------------------------------------

* Are there any choices for scheduling that make an improvement in the parallel performance (most importantly, scalability) of pagerank?