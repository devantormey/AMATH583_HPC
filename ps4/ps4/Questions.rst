


1. What level of SIMD/vector support does the CPU your computer provide?

Looks like it has: 
As far as SSE,

CPUID_ECX_SSE3
CPUID_ECX_SSSE3
CPUID_ECX_SSE4A
CPUID_ECX_SSE41
CPUID_ECX_SSE42
CPUID_EDX_SSE2

and for AVX,

CPUID_ECX_AVX
CPUID_EBX_AVX2

2. What is the maximum operand size that your computer will support?

AVX2 provides it with 16 256-bit registers. So you could give it 16 sets of 256 bit operations

3. How many double-precision floating point numbers can fit into one operand given the maximum operand size that your CPU will support?

4 per register. So at any one time you could crunch 64 doubles

. What is the clock speed of your CPU?  (You may need to look this up via "About this Mac" or "lscpu").

2.8GHz Clock speed

5. Based on the output from bandwidth.exe on your computer, what do you expect L1 cache and L2 cache sizes to be?  What are the corresponding bandwidths?   How do the cache sizes compare to what "about this mac" (or equivalent) tells you about your CPU?  (There is no "right" answer for this question -- but I do want you to do the experiment.)

It looks like there is a drop from 16K to 32K So L1 is probably 16K. There is a second drop from 256 to 512 so Im guessing L2 is around 256K. Looks like the bandwidths are 214GB/s and 47.2GB/s respectively. The sizes of these two caches match directly what is reported in my "about this mac" although I'm only seeing a size for L2 cache?

6. Based on the output from running this image on your computer, what do you expect L1 cache and L2 cache sizes to be? What are the corresponding bandwidths? How do the cache sizes compare to what “about this mac” (or equivalent) tells you about your CPU? (There is no “right” answer for this question – but I do want you to do the experiment.)

-Cannot get the docker to run

7. What is the (potential) maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and RAM bandwidths?  How do those bandwidths correspond to  what was measured above with the bandwidth program?

The bandwidth when running the bandwith.exe go as high as 256GB/s wich I would expect from the L1 cache (based on the Chart). So for L1 I am getting around 256GB/s and L2 I am getting around 60GB/s

8. Based on the clock speed of your CPU and its maximum Glop rate, what is the (potential) maximum number of *double precision* floating point operations that can be done per clock cycle?  (Hint: Glops / sec :math:`\div` GHz = flops / cycle.)  There are several hardware capabilities that can contribute to supporting more than one operation per cycle: fused multiply add (FMA) and AVX registers.  Assuming FMA contributes a factor of two, SSE contributes a factor of two,  AVX/AVX2 contribute a factor of four, and AVX contributes a factor of eight of eight, what is the expected maximum number of floating point operations your CPU could perform per cycle, based on the capabilities your CPU advertises via cpuinfo (equiv. lscpu)?  Would your answer change for single precision (would any of the previous assumptions change)?  

-First calc 8GLOPS/2.8MHz = 2.8 or 9/2.8 = 3.2
-with AVX 2 => 12.8
-with SSE => 25.6
-so 3.2-15.6 per cycle
-if you allow another 4X you get 62.4 which is around the 64 we would expect from before
-not quite sure how avx can both contribute a factor of 4 and a factor "of eight of eight" but I'm just gonna use 4
-Single precision would double this number. I could throw in more instructions

9. What is the maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and DRAM bandwidths?  How do those bandwidths correspond to what was measured above?

It looks to be around 8-20GFLOPS from running roofline at various sizes. If my L1 cache is 16 running roofline at 8K shows a speed of only 5.5 GB/s which differs from the previous test. But for L2 running at 128K shows a bandwidth of ~70K which is again a lot lower than I would expect. So my guess is that DRAM is just slower than RAM.

10. Referring to the figures about how data are stored in memory, what is it about the best performing pair of loops that is so advantageous?

The ones with the best performance have the least "row jumps" during a computation. You can order it such that you only perform a row jump once you reach the end of the row for both B and A. This means the numbers are "spacially" closer within memory and can be accessed faster. 

11. What will the data access pattern be when we are executing ``mult_trans`` in i,j,k order?  What data are accessed in each if the matrices at step (i,j,k) and what data are accessed at step (i, j, k+1)? Are these accesses advantageous in any way?

Based on the images our B matrix will be forced to jump rows and we will have to access data much "further" away. The advantages of doing it this way is at least A is going to cycle through one row at a time. 

12. Referring again to how data are stored in memory, explain why hoisting  ``C(i,j)`` out of the inner loop is so beneficial in mult_trans with the "ijk" loop ordering.

Because We only need to access that memory one time for the inner loop. Otherwise we have to jump through the Whole C matrix each time we wanna add two numbers. 

13. What optimization is applied in going from ``mult_2`` to ``mult_3``?

I think from mult_2 to mult_3 you employing Blocking. This also has a few other names but I think the main step is from just tiling to full on blocking in mult_3.

14. How does your maximum achieved performance for ``mult`` (any version) compare to what bandwidth and roofline predicted?

-Roofline: running at 128 (which was my highest bandwidth for roofline) I get somewhere around 13-19GFLOPS whereas mmult gets as high as 12 GFLOPS. So similar orders of magnitude




