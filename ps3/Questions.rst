
PS3 Questions
=============

Add your answers to this file in plain text after each question.  Leave a blank line between the text of the question and the text of your answer.

argv
----

1. What does `argv[0]` always contain?
the executable itself. "./main.exe"

2. Which entry of `argv` holds the first argument passed to the program?
argv[1]

3. Which entry of `argv` holds the second argument passed to the program?
argv[2]

4. How would you print just the last argument passed to a program?
Argc tell you the number of arguments passed. so use argv[argc - 1]

float vs double
----------------

5.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with no optimization*? Explain.

It comes down to the fact that doubles are more precise than floats. But that precision comes with a price. It's going to take a whole lot more memory to store an "equivalent" double than a float. So that is reflected in the construction times

6.  What is the difference (ratio) in execution times
between single and double precision for    *multiplication with no optimization*? Explain.

Again with large double you are essentially storing multiple numbers. So it comes down to performing an operation on a large double really looks like mulptiple instructions (operations) to a cpu. 

7.  What is the difference (ratio) in execution times 
between single and double precision for    *construction with optimization*? Explain.

The difference in timing has effectively become 2 to one. This is due to the fact that as we get closer to the most bits moved per second the fact the float is half the bits of a double is going to show.

8.  What is the difference (ratio) in execution times 
between single and double precision for    *multiplication with optimization*? Explain. 

This kinda has the same answer. We are now doing these operations as fast as possible and in modern computing the difference between floating point and double operations (multiplication in this case) is really non existant (very small). So it just becomes a memory game and the bigger one (the double) is going to take longer to move around.

9.  What is the difference (ratio) in execution times 
for double precision    multiplication with and without optimization? Explain. 
For my computer it's around 2X-3X. It's doing everything it can to parallelize those 8bit numbers into 2 4bit operations.

Efficiency
----------

10.  If you double the problem size for matrix-matrix product, how many more operations will matrix-matrix product perform?

Goes up as the cube because we have 3 nested loops. So N^3

11.  If the time to perform a given operation is constant, when you double the problem size for matrix-matrix product, how much more time will be required to compute the answer?

It will go up by 8X

12.  What ratio did you see when doubling the problem size when mmtime called `mult_0`?  (Hint, it may be larger than what pure operation count would predict.)  Explain.

It was 10X except for 256 -> 512.

13.  What raio did you see when doubling the problem size when mmtime called `mult_3`?  Was this the same for `mult_0`?  Referring to the function in amath583.cpp, what optimizations are implemented and what kinds of performance benefits might they provide?

mult_3 was closer to 8X. Optimizations move you closer to the theoretical outcome.

14. (Extra credit.)  Try also with `mult_1` and `mult_2`.




All-Pairs
---------

15. What do you observe about the different approaches to doing the similarity computation?  Which algorithm (optimizations) are most effective?  Does it pay to make a transpose of A vs a copy of A vs just passing in A itself.  What about passing in A twice vs passing it in once (mult_trans_3 vs mult_trans_4)?
-For a lot of these the similarity transform operation starts off being super effective getting like 6 GFLOPS. But as the matrices get larger and larger this efficiency starts to wear off. My guess is the cost of that extra operation becomes more and more heavily weighted.
-It seems they operate with roughly the same efficiency until the matrices become sufficiently large, then a single A becomes slower. The process of copying the data may start to weigh down on the efficiency.


16. What is the best performance over all the algorithms that you observed for the case of 1024 images?  What would the execution time be for 10 times as many images?  For 60 times as many images?  (Hint: the answer is not cubic but still potentially a problem.)  What if we wanted to do, say 56 by 56 images instead of 28 by 28?

Mult_trans_3 and Mult_3 seem to perform the best at 1024. 

my data is showing the relationship between GFLOPS and number of images is logarithmic. So for every doubling of the number of images I drop 1 GFLOP. So it should run about 8GFLOPS slower or at whatever percentage that slope would take you (as it can't be negative)

I don't think it will be cubic. I think it's something like N^2Log(N). So the result is that it would be N^2LogN slower.


About PS3
---------


17. The most important thing I learned from this assignment was ...
Memory matters. If you know how much data you are going to be moving always use the minimum memory data type.

18. One thing I am still not clear on is ...
Problem 16. The results are really clicking for me.
