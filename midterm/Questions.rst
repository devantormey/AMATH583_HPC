TO-DO-6: Write (and answer) your own question about sparse matrix computation. This should be a non-trival question. “How do you spell CSR?” is not non-trivial.

ANSWER:
Question: When do CSR and COO have the same efficiency. 
-Answer: if there are no repeated rows then they will be the same orgonization.
Alternate Question: If you still have to loop through some matrix to convert it to CSR?
-Answer: from thinking about this a little it seems like the power of CSR really comes into affect when you are to be reausing a matrix multiple times or if the actual multiplication is long form. I can really se this become efficient when you are doing matrix matrix product as you are now essentially multiplying vectors instead of matrices. CSR really doesn't matter for diagonal matrices because well those are essentially already in CSR due to the identity of diag(A)*Diag(B) = sum aii*bii.

How does the performance (in GFLOP/s) for sparse-matrix by vector
product compare to what you previously achieved for dense-matrix by
dense-matrix product?  Explain, and quantify if you can, (e.g., using
the roofline model).

ANSWER:
For the intesity 1 of Roofline it gets around 1-2 GFLOPS
For the matvec speeds across all arrangements I get a range from .5 to 2GFLOPS So they are all operating on the same order of magnitude.
We really only compared the speeds of matrix-matrix multiplication so I don't actually see the value in comparing these but Even for the relatively huge value of 2048 these matvec product are producing GFLOPS similar or equivalent to the dense Matrix-matrix sizes of 64. On the order of 1-2GLFOPS.

How does the performance (in GFLOP/s) for sparse-matrix by vector
product for COO compare to CSR?  Explain, and quantify if you can,
(e.g., using the roofline model).

ANSWER:
CSR starts out nearly twice as good at nearly 2GFLOPS while COO is is at ~1.2. As we get higher and higher numbers (we are exiting the L1 cache) they both receive a significant drop in performance and while their performance begins to level out (.9 vs 1.2) CSR remains dominant. THis makes sense because given a random matrix CSR will simply just be carrying around less information. 

How does the performance (in GFLOP/s) for sparse-matrix by dense
matrix product (**SPMM**) compare to sparse-matrix by vector product
(**SPMV**)? The performance for SPMM should be about the same as for
SPMV in the case of a 1 column dense matrix.  What is the trend with
increasing numbers of columns?  Explain, and quantify if you can,
using the roofline model.

ANSWER:
The multiplication is fairly similar in terms of run times. Looking across roofline.log and mmult_ps3.log it seems to get around the same performance as mult_0 mult_1 and mult_t 1 especially for the larger sizes. This puts it around 1.2-1.5 GFLOPS range

How does the performance of sparse matrix by dense matrix product (in
GFLOP/s) compare to the results you got dense matrix-matrix product in
previous assignments?  Explain, and quantify if you can, using the
roofline model.

ANSWER:
Significantly better. The Dense matrix product is performing at around 1 GFLOPS by the time the size hits 64, the Sparse-Dense matrix product is still at 1GFLOP even at a size of 2048. Although this performance drops incredibly fast as I make the matrix larger and larger. At 64 x 64 my computer cant even finish the test! at 32 x 32 this is roughly comperable to the mult_1 performance in mmult_ps3.log. And is looking more like the higher end of roofline at around .3 GFLOPS


APPENDED QUESTIONS
a) The most important thing I learned from this assignment was… 
If you are carrying around useless or repetetive information there might be a formulation of the problem in which that information can be removed. It's not always the direct method of computation of the algorithm that makes it efficient it can often just be the way the problem is stated. the actual data format can be reworked in order to "parametrize" the problem.
b) One thing I am still not clear on is…
Do people use this after data has been taken? As in are the COO CSR etc matrices created while you are taking data or are they instead created by converting an existing non COO/CSR matrix to this form?