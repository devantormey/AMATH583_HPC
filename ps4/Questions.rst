


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

4. What is the clock speed of your CPU?  (You may need to look this up via "About this Mac" or "lscpu").

2.8GHz Clock speed

5. Based on the output from bandwidth.exe on your computer, what do you expect L1 cache and L2 cache sizes to be?  What are the corresponding bandwidths?   How do the cache sizes compare to what "about this mac" (or equivalent) tells you about your CPU?  (There is no "right" answer for this question -- but I do want you to do the experiment.)

It looks like there is a drop from 16K to 32K So L1 is probably 16K. There is a second drop from 256 to 512 so Im guessing L2 is around 256K. Looks like the bandwidths are 214GB/s and 47.2GB/s

6. What is the (potential) maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and RAM bandwidths?  How do those bandwidths correspond to  what was measured above with the bandwidth program?


7. Based on the clock speed of your CPU and its maximum Glop rate, what is the (potential) maximum number of *double precision* floating point operations that can be done per clock cycle?  (Hint: Glops / sec :math:`\div` GHz = flops / cycle.)  There are several hardware capabilities that can contribute to supporting more than one operation per cycle: fused multiply add (FMA) and AVX registers.  Assuming FMA contributes a factor of two, SSE contributes a factor of two,  AVX/AVX2 contribute a factor of four, and AVX contributes a factor of eight of eight, what is the expected maximum number of floating point operations your CPU could perform per cycle, based on the capabilities your CPU advertises via cpuinfo (equiv. lscpu)?  Would your answer change for single precision (would any of the previous assumptions change)?  

8. What is the maximum compute performance of your computer?  (The horizontal line.)  What are the L1, L2, and DRAM bandwidths?  How do those bandwidths correspond to what was measured above?

9. Referring to the figures about how data are stored in memory, what is it about the best performing pair of loops that is so advantageous?

10. What will the data access pattern be when we are executing ``mult_trans`` in i,j,k order?  What data are accessed in each if the matrices at step (i,j,k) and what data are accessed at step (i, j, k+1)? Are these accesses advantageous in any way?


11. Referring again to how data are stored in memory, explain why hoisting  ``C(i,j)`` out of the inner loop is so beneficial in mult_trans with the "ijk" loop ordering.

12. What optimization is applied in going from ``mult_2`` to ``mult_3``?

13. How does your maximum achieved performance for ``mult`` (any version) compare to what bandwidth and roofline predicted?





