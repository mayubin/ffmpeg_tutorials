# Introduction to Algorithms
算法导论
[网上公开课视频地址](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/)
## Foundations
### The Role of Algorithms in Computing
2019.04.20 1-3章计划阅读完成  
fertile (富饶的)  
permutation (排列)  
convex (凸)  
proportional (按比例)  
contemporary (现代的)  
Having a solid base of algorithmic knowledge and technique is one characteristic
that separates the truly skilled programmers from the novices.  

总体地介绍算法的应用。  

### Getting Started
**insert sort** (插入排序)  
伪代码
<pre><code>  
INSERTION_SORT(A)  
for j = 2 to A.length  
    key = A[j]  
    // Insert A[j] into the sorted sequence A[1.. j-1]  
    i = j - 1  
    while i > 0 and A[i] > key  
        a[i+1] = a[i]  
        i = i - 1  
    a[i+1] = key  
</code></pre>

**loop invariant**    
At the start of each iteration of the for loop of lines 1 - 8, the subarray A[1.. j-1] consists of
the elements originally in A[1.. j-1], but in sorted order.  
三点要素  
**Initialization**: It is true prior to the first iteration of the loop.  
**Maintenance**: If it is true before an iteration of the loop, it remains true before the next iteration.  
**Termination**: When the loop terminates, the invariant gives us a useful property that helps show that the algorithm is correct.  

介绍伪代码的规则  

分析算法的时间复杂度  
linear function (线性方程)  
quadratic function (二次方程)  

The **divide-and-conquer** paradigm involves three steps at each level of the recursion:  
**Divide** the problem into a number of subproblems that are smaller instances of the same problem.  
**Conquer** the subproblems by solving them recursively. If the subproblem sizes are small enough,   
however, just solve the subproblems in a straightforward manner.  
**Combine** the solution to the subproblems into the solution for the original problem.

设计算法  
**merge sort**
<pre><code>
MERGE(A, p, q, r)
n1 = q - p + 1
n2 = r -  q
let L[1.. n1+1] and R[1.. n2+1] be new arrays
for i = 1 to n1
    L[i] = A[p+i-1]
for j = 1 to n2
    R[j] = A[q+j]
L[n1+1] = $
R[n2+1] = $
i = 1
j = 1
for k = p to r
    if L[i] <= R[j]
        A[k] = L[i]
        i = i + 1
    else
        A[k] = R[j]
        j = j + 1            
</code></pre> 

<pre><code>
MERGE-SORT(A, p, r)
if p < r
    q = [(p + r) / 2]
    MERGE-SORT(A, p, q)
    MERGE-SORT(A, q+1, r)
    MERGE(A, p, q, r)
</code></pre>
    
When an algorithm contains a recursive call to itself, we can often describe its
running time by a recurrence equation or recurrence, which describes the overall
running time on a problem of size n in terms of the running time on smaller inputs.


### Growth of Functions
asymptotic (渐进) efficiency of algorithms  
三种描述函数增长的方式
**C-notation** bounds a functions from above and below.
**O-notation** asymptotic upper bound
**L-notation** asymptotic lower bound

**Monotonicity** 单调性
A function f(n) is monotonically increasing if m <= n implies f(m) <= f(n).

**Floors and ceilings**

**Modular arithmetic**  
求余  
For any integer a and any positive integer n, the value a mod n is the remainder (or residue) of the quotient a/n.

**Polynomials**
多项式

**Exponentials**  
指数

**Logarithms**  
对数
lgn = log2n (binary logarithm)
lnn = logen (natural logarithm)

**Factorials**

**Fibonacci numbers**  
F0 = 0  
F1 = 1  
Fi = F(i-1) + F(i-2)  

### Divide-and-Conquer
### Probabilistic Analysis and Randomized Algorithms

## Sorting and Order Statistics

### Heapsort
### Quicksort
### Sorting in Linear Time
### Medians and Order Statistics

