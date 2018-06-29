# expint
[![Travis-CI Build Status](https://travis-ci.org/vigou3/expint.svg?branch=master)](https://travis-ci.org/vigou3/expint) [![CRAN\_Status\_Badge](http://www.r-pkg.org/badges/version/expint)](https://cran.r-project.org/package=expint) ![downloads](http://cranlogs.r-pkg.org/badges/grand-total/expint)

Exponential integral and incomplete gamma function for R.

## What it is

The exponential integral `E_1(x) = int_x^Inf exp(-t)/t dt` and the
incomplete gamma function `G(a, x) = int_x^Inf t^(a-1) exp(-t) dt`
are closely related functions that arise in various fields of
mathematics and statistics.

**expint** is a small R package that provides functions to compute
the exponential integral and the incomplete gamma function.

Most conveniently for R package developers, the package also gives
access to the underlying C workhorses through an API.

## Features

- R interface consisting of one main and four auxiliary functions to
  compute the exponential integral, and one function to compute the
  incomplete gamma function.
- Underlying C routines derived from mature and stable code of the
  [GNU Scientific Library](https://www.gnu.org/software/gsl/).
- Test package implementing the access to the C routine
  through the API. This test package uses the `.External` R to C
  interface and, as a bonus, shows how to vectorize an R function on
  the C side.
- Exhaustive
  [package vignette](https://cran.r-project.org/package=expint/vignettes/expint.pdf)
  providing all the details about the formulas that are implemented in
  the package as well as a complete presentation of the API and its
  usage.

## Examples

We tabulate the values of the exponential integral of order `n` for `x = 1.275, 10, 12.3` and
`n = 1, 2, ..., 10` as found in examples 4 through 6 of
[Abramowitz and Stegun (1972)](http://people.math.sfu.ca/~cbm/aands/), section 5.3.

```R
R> x <- c(1.275, 10, 12.3)
R > n <- 1:10
R> structure(t(outer(x, n, expint)),
+            dimnames = list(n, paste("x =", x)))

    x = 1.275       x = 10     x = 12.3
1  0.14080993 4.156969e-06 3.439534e-07
2  0.09989831 3.830240e-06 3.211177e-07
3  0.07603031 3.548763e-06 3.009983e-07
4  0.06083077 3.304101e-06 2.831550e-07
5  0.05046793 3.089729e-06 2.672346e-07
6  0.04301687 2.900528e-06 2.529517e-07
7  0.03743074 2.732441e-06 2.400730e-07
8  0.03310097 2.582217e-06 2.284066e-07
9  0.02965340 2.447221e-06 2.177930e-07
10 0.02684699 2.325303e-06 2.080990e-07
```

We also tabulate the values of the incomplete gamma function for
`a = -1.5, -1, -0.5, 1` and `x = 1, 2, ..., 10`.

```R
R> a <- c(-1.5, -1, -0.5, 1)
R> x <- 1:10
R> structure(t(outer(a, x, gammainc)),
+            dimnames = list(x, paste("a =", a)))

         a=-1.5         a=-1       a=-0.5          a=1
1  1.264878e-01 1.484955e-01 1.781477e-01 3.678794e-01
2  1.183299e-02 1.876713e-02 3.009876e-02 1.353353e-01
3  1.870260e-03 3.547308e-03 6.776136e-03 4.978707e-02
4  3.706365e-04 7.995573e-04 1.733500e-03 1.831564e-02
5  8.350921e-05 1.992938e-04 4.773965e-04 6.737947e-03
6  2.045031e-05 5.304291e-05 1.379823e-04 2.478752e-03
7  5.310564e-06 1.478712e-05 4.127115e-05 9.118820e-04
8  1.440569e-06 4.267206e-06 1.266464e-05 3.354626e-04
9  4.042025e-07 1.264846e-06 3.964430e-06 1.234098e-04
10 1.165117e-07 3.830240e-07 1.260904e-06 4.539993e-05
```

## Status

Unless important bugs are discovered either upstream in the GSL
functions or in our adaptation, the code base of the package is not
expected to change much in the future. In other words: stable.

## Installation

You  should install the stable version of the package from the
[Comprehensive R Archive Network (CRAN)](https://cran.r-project.org/package=expint)
using:

```R
install.packages("expint")
```

## Author

Vincent Goulet is the author and maintainer of the package. Many other
copyright holders (for the original GSL code and for parts of the base
R code) are credited in the `DESCRIPTION` file.

## License

**expint** is free software licensed under the [GNU General Public
License (GPL)](https://www.gnu.org/copyleft/gpl.html), version 2 or later.

