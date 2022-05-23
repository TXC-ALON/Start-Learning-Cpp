# Matters Computational

## Part I    Low level algorithms  p.1

### 1   Bit wizardry  p.2

####     1.1    Trivia

####     1.2    Operations on individual bits

####     1.3    Operations on low bits or blocks of a word

####     1.4    Extraction of ones, zeros, or blocks near transitions

####     1.5    Computing the index of a single set bit

####     1.6    Operations on high bits or blocks of a word

####     1.7    Functions related to the base-2 logarithm

####     1.8    Counting the bits and blocks of a word

####     1.9    Words as bitsets

####     1.10   Index of the i-th set bit

####     1.11   Avoiding branches

####     1.12   Bit-wise rotation of a word

####     1.13   Binary necklaces z

####     1.14   Reversing the bits of a word

####     1.15   Bit-wise zip

####     1.16   Gray code and parity

####     1.17   Bit sequency z

####     1.18   Powers of the Gray code z

####     1.19   Invertible transforms on words z

####     1.20   Scanning for zero bytes

####     1.21   Inverse and square root modulo 2n

####     1.22   Radix -2 (minus two) representation

####     1.23   A sparse signed binary representation

####     1.24   Generating bit combinations

####     1.25   Generating bit subsets of a given word

####     1.26   Binary words in lexicographic order for subsets

####     1.27   Fibonacci words z

####     1.28   Binary words and parentheses strings z

####     1.29   Permutations via primitives z

####     1.30   CPU instructions often missed

####     1.31   Some space filling curves z

### 2   Permutations and their operations  p.102

​    2.1    Basic definitions and operations
​    2.2    Representation as disjoint cycles
​    2.3    Compositions of permutations
​    2.4    In-place methods to apply permutations to data
​    2.5    Random permutations
​    2.6    The revbin permutation
​    2.7    The radix permutation
​    2.8    In-place matrix transposition
​    2.9    Rotation by triple reversal
​    2.10   The zip permutation
​    2.11   The XOR permutation
​    2.12   The Gray permutation
​    2.13   The reversed Gray permutation

### 3   Sorting and searching  p.134

​    3.1    Sorting algorithms
​    3.2    Binary search
​    3.3    Variants of sorting methods
​    3.4    Searching in unsorted arrays
​    3.5    Determination of equivalence classes

### 4   Data structures  p.153

​    4.1    Stack (LIFO)
​    4.2    Ring buffer
​    4.3    Queue (FIFO)
​    4.4    Deque (double-ended queue)
​    4.5    Heap and priority queue
​    4.6    Bit-array
​    4.7    Left-right array

## Part II    Combinatorial generation  p.171

### 5   Conventions and considerations  p.172

​    5.1    Representations and orders
​    5.2    Ranking, unranking, and counting
​    5.3    Characteristics of the algorithms
​    5.4    Optimization techniques
​    5.5    Implementations, demo-programs, and timings

### 6   Combinations  p.176

​    6.1    Binomial coefficients
​    6.2    Lexicographic and co-lexicographic order
​    6.3    Order by prefix shifts (cool-lex)
​    6.4    Minimal-change order
​    6.5    The Eades-McKay strong minimal-change order
​    6.6    Two-close orderings via endo/enup moves
​    6.7    Recursive generation of certain orderings

### 7   Compositions  p.194

​    7.1    Co-lexicographic order
​    7.2    Co-lexicographic order for compositions into exactly k parts
​    7.3    Compositions and combinations
​    7.4    Minimal-change orders

### 8   Subsets  p.202

​    8.1    Lexicographic order
​    8.2    Minimal-change order
​    8.3    Ordering with De Bruijn sequences
​    8.4    Shifts-order for subsets
​    8.5    k-subsets where k lies in a given range

### 9   Mixed radix numbers  p.217

​    9.1    Counting (lexicographic) order
​    9.2    Minimal-change (Gray code) order
​    9.3    gslex order
​    9.4    endo order
​    9.5    Gray code for endo order
​    9.6    Fixed sum of digits

### 10  Permutations  p.232

​    10.1   Factorial representations of permutations
​    10.2   Lexicographic order
​    10.3   Co-lexicographic order
​    10.4   An order from reversing prefixes
​    10.5   Minimal-change order (Heap's algorithm)
​    10.6   Lipski's Minimal-change orders
​    10.7   Strong minimal-change order (Trotter's algorithm)
​    10.8   Star-transposition order
​    10.9   Minimal-change orders from factorial numbers
​    10.10  Derangement order
​    10.11  Orders where the smallest element always moves right
​    10.12  Single track orders

### 11  Permutations with special properties  p.277

​    11.1   The number of certain permutations
​    11.2   Permutations with distance restrictions
​    11.3   Self-inverse permutations (involutions)
​    11.4   Cyclic permutations

### 12  k-permutations  p.291

​    12.1   Lexicographic order
​    12.2   Minimal-change order

### 13  Multisets  p.295

​    13.1   Subsets of a multiset
​    13.2   Permutations of a multiset

### 14  Gray codes for strings with restrictions  p.304

​    14.1   List recursions
​    14.2   Fibonacci words
​    14.3   Generalized Fibonacci words
​    14.4   Run-length limited (RLL) words
​    14.5   Digit x followed by at least x zeros
​    14.6   Generalized Pell words
​    14.7   Sparse signed binary words
​    14.8   Strings with no two consecutive nonzero digits
​    14.9   Strings with no two consecutive zeros
​    14.10  Binary strings without substrings 1x1 or 1xy1 z

### 15  Parentheses strings  p.323

​    15.1   Co-lexicographic order
​    15.2   Gray code via restricted growth strings
​    15.3   Order by prefix shifts (cool-lex)
​    15.4   Catalan numbers
​    15.5   Increment-i RGS, k-ary Dyck words, and k-ary trees

### 16  Integer partitions  p.339

​    16.1   Solution of a generalized problem
​    16.2   Iterative algorithm
​    16.3   Partitions into m parts
​    16.4   The number of integer partitions

### 17  Set partitions  p.354

​    17.1   Recursive generation
​    17.2   The number of set partitions: Stirling set numbers and Bell numbers
​    17.3   Restricted growth strings

### 18  Necklaces and Lyndon words  p.370

​    18.1   Generating all necklaces
​    18.2   Lex-min De Bruijn sequence from necklaces
​    18.3   The number of binary necklaces
​    18.4   Sums of roots of unity that are zero z

### 19  Hadamard and conference matrices  p.384

​    19.1   Hadamard matrices via LFSR
​    19.2   Hadamard matrices via conference matrices
​    19.3   Conference matrices via finite fields

### 20  Searching paths in directed graphs z  p.391

​    20.1   Representation of digraphs
​    20.2   Searching full paths
​    20.3   Conditional search
​    20.4   Edge sorting and lucky paths
​    20.5   Gray codes for Lyndon words

## Part III    Fast transforms  p.409

### 21  The Fourier transform  p.410

​    21.1   The discrete Fourier transform
​    21.2   Radix-2 FFT algorithms
​    21.3   Saving trigonometric computations
​    21.4   Higher radix FFT algorithms
​    21.5   Split-radix algorithm
​    21.6   Symmetries of the Fourier transform
​    21.7   Inverse FFT for free
​    21.8   Real-valued Fourier transforms
​    21.9   Multi-dimensional Fourier transforms
​    21.10  The matrix Fourier algorithm (MFA)

### 22  Convolution, correlation, and more FFT algorithms  p.440

​    22.1   Convolution
​    22.2   Correlation
​    22.3   Correlation, convolution, and circulant matrices z
​    22.4   Weighted Fourier transforms and convolutions
​    22.5   Convolution using the MFA
​    22.6   The z-transform (ZT)
​    22.7   Prime length FFTs

### 23  The Walsh transform and its relatives  p.459

​    23.1   Transform with Walsh-Kronecker basis
​    23.2   Eigenvectors of the Walsh transform z
​    23.3   The Kronecker product
​    23.4   Higher radix Walsh transforms
​    23.5   Localized Walsh transforms
​    23.6   Transform with Walsh-Paley basis
​    23.7   Sequency-ordered Walsh transforms
​    23.8   XOR (dyadic) convolution
​    23.9   Slant transform
​    23.10  Arithmetic transform
​    23.11  Reed-Muller transform
​    23.12  The OR-convolution and the AND-convolution
​    23.13  The MAX-convolution z
​    23.14  Weighted arithmetic transform and subset convolution

### 24  The Haar transform  p.497

​    24.1   The `standard' Haar transform
​    24.2   In-place Haar transform
​    24.3   Non-normalized Haar transforms
​    24.4   Transposed Haar transforms z
​    24.5   The reversed Haar transform z
​    24.6   Relations between Walsh and Haar transforms
​    24.7   Prefix transform and prefix convolution
​    24.8   Nonstandard splitting schemes z

### 25  The Hartley transform  p.515

​    25.1   Definition and symmetries
​    25.2   Radix-2 FHT algorithms
​    25.3   Complex FFT by FHT
​    25.4   Complex FFT by complex FHT and vice versa
​    25.5   Real FFT by FHT and vice versa
​    25.6   Higher radix FHT algorithms
​    25.7   Convolution via FHT
​    25.8   Localized FHT algorithms
​    25.9   2-dimensional FHTs
​    25.10  Automatic generation of transform code
​    25.11  Eigenvectors of the Fourier and Hartley transform z

### 26  Number theoretic transforms (NTTs)  p.535

​    26.1   Prime moduli for NTTs
​    26.2   Implementation of NTTs
​    26.3   Convolution with NTTs

### 27  Fast wavelet transforms  p.543

​    27.1   Wavelet filters
​    27.2   Implementation
​    27.3   Moment conditions

## Part IV    Fast arithmetic  p.549

### 28  Fast multiplication and exponentiation  p.550

​	28.1   Splitting schemes for multiplication
​	28.2   Fast multiplication via FFT
​	28.3   Radix/precision considerations with FFT multiplication
​	28.4   The sum-of-digits test
​	28.5   Binary exponentiation

### 29  Root extraction  p.567

​    29.1   Division, square root and cube root
​    29.2   Root extraction for rationals
​    29.3   Divisionless iterations for the inverse a-th root
​    29.4   Initial approximations for iterations
​    29.5   Some applications of the matrix square root
​    29.6   Goldschmidt's algorithm
​    29.7   Products for the a-th root z
​    29.8   Divisionless iterations for polynomial roots

### 30  Iterations for the inversion of a function  p.587

​    30.1   Iterations and their rate of convergence
​    30.2   Schr"oder's formula
​    30.3   Householder's formula
​    30.4   Dealing with multiple roots
​    30.5   More iterations
​    30.6   Convergence improvement by the delta squared process

### 31  The AGM, elliptic integrals, and algorithms for computing ss  p.599

​    31.1   The arithmetic-geometric mean (AGM)
​    31.2   The elliptic integrals K and E
​    31.3   Theta functions, eta functions, and singular values
​    31.4   AGM-type algorithms for hypergeometric functions
​    31.5   Computation of ss

### 32  Logarithm and exponential function  p.622

​    32.1   Logarithm
​    32.2   Exponential function
​    32.3   Logarithm and exponential function of power series
​    32.4   Simultaneous computation of logarithms of small primes
​    32.5   Arctangent relations for ss z

### 33  Computing the elementary functions with limited resources  p.641

​    33.1   Shift-and-add algorithms for log b(x) and bx
​    33.2   CORDIC algorithms

### 34  Numerical evaluation of power series  p.651

​    34.1   The binary splitting algorithm for rational series
​    34.2   Rectangular schemes for evaluation of power series
​    34.3   The magic sumalt algorithm for alternating series

### 35  Recurrences and Chebyshev polynomials  p.666

​    35.1   Recurrences
​    35.2   Chebyshev polynomials

### 36  Hypergeometric series  p.685

​    36.1   Definition and basic operations
​    36.2   Transformations of hypergeometric series
​    36.3   Examples: elementary functions
​    36.4   Transformations for elliptic integrals z
​    36.5   The function xx z

### 37  Cyclotomic polynomials, product forms, and continued fractions  p.704

​    37.1   Cyclotomic polynomials, M"obius inversion, Lambert series
​    37.2   Conversion of power series to infinite products
​    37.3   Continued fractions

### 38  Synthetic Iterations z  p.726

​    38.1   A variation of the iteration for the inverse
​    38.2   An iteration related to the Thue constant
​    38.3   An iteration related to the Golay-Rudin-Shapiro sequence
​    38.4   Iteration related to the ruler function
​    38.5   An iteration related to the period-doubling sequence
​    38.6   An iteration from substitution rules with sign
​    38.7   Iterations related to the sum of digits
​    38.8   Iterations related to the binary Gray code
​    38.9   A function encoding the Hilbert curve
​    38.10  Sparse power series
​    38.11  An iteration related to the Fibonacci numbers
​    38.12  Iterations related to the Pell numbers

## Part V    Algorithms for finite fields  p.763

### 39  Modular arithmetic and some number theory  p.764

​    39.1   Implementation of the arithmetic operations
​    39.2   Modular reduction with structured primes
​    39.3   The sieve of Eratosthenes
​    39.4   The Chinese Remainder Theorem (CRT)
​    39.5   The order of an element
​    39.6   Prime modulus: the field Z=pZ = Fp = GF  (p)
​    39.7   Composite modulus: the ring Z=mZ
​    39.8   Quadratic residues
​    39.9   Computation of a square root modulo m
​    39.10  The Rabin-Miller test for compositeness
​    39.11  Proving primality
​    39.12  Complex modulus: the field GF  (p2)
​    39.13  Solving the Pell equation
​    39.14  Multiplication of hypercomplex numbers z

### 40  Binary polynomials  p.822

​    40.1   The basic arithmetical operations
​    40.2   Multiplying binary polynomials of high degree
​    40.3   Modular arithmetic with binary polynomials
​    40.4   Irreducible polynomials
​    40.5   Primitive polynomials
​    40.6   The number of irreducible and primitive polynomials
​    40.7   Transformations that preserve irreducibility
​    40.8   Self-reciprocal polynomials
​    40.9   Irreducible and primitive polynomials of special forms z
​    40.10  Generating irreducible polynomials from Lyndon words
​    40.11  Irreducible and cyclotomic polynomials z
​    40.12  Factorization of binary polynomials

### 41  Shift registers  p.864

​    41.1   Linear feedback shift registers (LFSR)
​    41.2   Galois and Fibonacci setup
​    41.3   Error detection by hashing: the CRC
​    41.4   Generating all revbin pairs
​    41.5   The number of m-sequences and De Bruijn sequences
​    41.6   Auto-correlation of m-sequences
​    41.7   Feedback carry shift registers (FCSR)
​    41.8   Linear hybrid cellular automata (LHCA)
​    41.9   Additive linear hybrid cellular automata

### 42  Binary finite fields:  GF (2n )  p.886

​    42.1   Arithmetic and basic properties
​    42.2   Minimal polynomials
​    42.3   Fast computation of the trace vector
​    42.4   Solving quadratic equations
​    42.5   Representation by matrices z
​    42.6   Representation by normal bases
​    42.7   Conversion between normal and polynomial representation
​    42.8   Optimal normal bases (ONB)
​    42.9   Gaussian normal bases

A   The electronic version of the book  p.921

B   Machine used for benchmarking  p.922

C   The GP language  p.923

## Bibliography  p.931

## Part Index  p.951