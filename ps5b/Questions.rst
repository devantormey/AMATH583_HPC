
pnorm
-----

* What was the data race?
the data race occured when accessing the partioned x in multiple threads. Everytime worker A was called it required the accessing of the data in x. 

* What did you do to fix the data race?  Explain why the race is actually eliminated (rather than, say, just made less likely).
I used mutex.lock() to block the other threads from access x while it was being read by one thread

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?

Lookin at the largest vector size (this should be where the speedup is most noticable):
1: 3.32222 
2: 5.14244 
4: 6.21378
8: 6.04584 

At first there is a large jump where 2 cores is going at ~160% faster. By the time we get to 4 cores we have doubled the speed which then seems to level out at 8 cores. So we can double the speed with multi threading but  not much better than that.

fnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_a``?
Lookin at the largest vector size (this should be where the speedup is most noticable):
1: 3.58871
2: 5.39027
4: 6.33102
8: 5.81029
So again we have doubling through 4 cores, although now once we go to 8 cores we actually see a fall off in performance. 


* How much parallel speedup do you see for 1, 2, 4, and 8 threads for ``partitioned_two_norm_b``? 
Lookin at the largest vector size (this should be where the speedup is most noticable):
1: 3.65716
2: 8.7724
4: 20.0325
8: 43.296

Now we see doubling in performance each time the number of cores doubles! 

* Explain the differences you see between ``partitioned_two_norm_a`` and ``partitioned_two_norm_b``.
Deferred will invoke the function on the current thready so you don't have spend extra time creating a new thread and re-initializing everything. Having to spool up a new thread (such as in async) significantly drops the performance.

cnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?

Honestly the trend is pretty much the same as pnorm. Some doubling at first but saturates at 4-8 cores.

* How does the performance of cyclic partitioning compare to blocked?  Explain any significant differences, referring to, say, performance models or CPU architectural models.

The only one that stands out is the deferred async. Cyclic is pretty much the same as the other two and I can see why it's a sneaky way of doing block partitioning.  The main thing limiting these tasks is the size of the L1 cache. 


rnorm
-----

* How much parallel speedup do you see for 1, 2, 4, and 8 threads?
Same doubling as before with diminishing returns for 8 threads
1 thread:     3.50438 
2 thread:    5.24288 
4 thread:     5.26344  
8 thread:   6.12866

* What will happen if you use ``std:::launch::deferred`` instead of ``std:::launch::async`` when launching tasks?  When will the computations happen?  Will you see any speedup?  For your convenience, the driver program will also call ``recursive_two_norm_b`` -- which you can implement as a copy of ``recursive_two_norm_a`` but with the launch policy changed.
It won't improve anything. In fact deferred will make it the same efficiency as sequentially because having to wait in this case will just slow things down. If each thread awoken from the recursion has to wait for the other threads it's the same as no multithreading. 

General
-------

* For the different approaches to parallelization, were there any major differences in how much parallel speedup that you saw?

I think the one that stands out the most was running launch::deferred on the fnorm problem. It seemed to actually hit the roofline theoretical speed. The other one that stands out is running deferred on the recursive problem which had the opposite effect


* You may have seen the speedup slowing down as the problem sizes got larger -- if you didn't keep trying larger problem sizes.  What is limiting parallel speedup for two_norm (regardless of approach)?  What would determine the problem sizes where you should see ideal speedup?  (Hint: Roofline model.)

the 33554432 size problem saw diminishing returns after the 4 core split it. This is because at 33554432X4 we have filled up the cache so any more cores just gotta wait. 


Conundrum #1
------------

1. What is causing this behavior?

from what i can reckon once the problem size is small enough you end up just spending most of your time spooling up threads rather than actually running the math

2. How could this behavior be fixed?

remove the wait time. Basically have them spool up simultaneously

3. Is there a simple implementation for this fix?

I beleive you can solve it by running things asynchronously


Parallel matvec
---------------

* Which methods did you implement?

* How much parallel speedup do you see for the methods that you implemented for 1, 2, 4, and 8 threads?



Conundrum #2
------------

1. What are the two "matrix vector" operations that we could use?

2. How would we use the first in pagerank?  I.e., what would we have to do differently in the rest of pagerank.cpp to use that first operation?

3. How would we use the second?
