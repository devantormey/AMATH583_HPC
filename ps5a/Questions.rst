

- At what problem size do the answers between the computed norms start to differ?
Reversed: at around 5000 and below it started to have a more significant effect
Sorted: at length 10,000 it jumps up and steadly grows (albeit the error is on the order of 1e-12).

- How do the absolute and relative errors change as a function of problem size?
If you run norm_runs (bash script) it should produce a plot showing the results of ten trials going from 1M to size 50 vectors. Smaller sizes the revers order error is most significant and as the length grows it begins to matter less and less. Conversly the sorted norm error grows with the vector length, although the error didn't always print so the number of trials is less. 

- Does the Vector class behave strictly like a member of an abstract vector class?
No because we have modified the abstract member functions to do different things than is typical.

- Do you have any concerns about this kind of behavior?
The fact that order matters in these operations is interesting, There has to be some best practices for how to order these operations in order to get the most consistent results.

