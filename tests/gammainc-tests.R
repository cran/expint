### == expint: Exponential Integral and Incomplete Gamma Function ==
###
### Tests for the incomplete gamma function
###
###    G(a,x) = int_x^infty t^{a-1} exp(-t) dt
###
### for a *real* and x >= 0.
###
### AUTHOR: Vincent Goulet <vincent.goulet@act.ulaval.ca>

## Load the package
library(expint)

## a > 0; direct link to the standard incomplete gamma function
x <- c(0.2, 2.5, 5, 8, 10)
a <- 1.2
stopifnot(exprs = {
    identical(gammainc(a, x),
              gamma(a) * pgamma(x, a, 1, lower = FALSE))
})

## a = 0; direct link to the exponential integral
x <- c(0.2, 2.5, 5, 8, 10)
a <- 0
stopifnot(exprs = {
    identical(gammainc(a, x), expint(x))
    identical(gammainc(a, x), expint_E1(x))
})

## a < 0; compare to the recursive formula
x <- c(0.2, 2.5, 5, 8, 10)
a <- c(-0.25, -1.2, -2)
stopifnot(exprs = {
    all.equal(gammainc(a[1], x),
              -(x^a[1] * exp(-x))/a[1] +
              gamma(a[1] + 1) * pgamma(x, a[1] + 1, 1, lower = FALSE)/a[1])
    all.equal(gammainc(a[2], x),
              -(x^a[2] * exp(-x))/a[2] +
              (-(x^(a[2] + 1) * exp(-x))/(a[2] + 1) +
               gamma(a[2] + 2) * pgamma(x, a[2] + 2, 1, lower = FALSE)/(a[2] + 1))/a[2])
    all.equal(
        gammainc(a[3], x),
        -(x^a[3] * exp(-x))/a[3] +
        (-(x^(a[3] + 1) * exp(-x))/(a[3] + 1) + expint_E1(x)/(a[3] + 1))/a[3])
})

## Issue #2: use the recursion even for -0.5 < a < 0 (unlike GSL
## sources), relying on the accuracy of 'pgamma' near a = 0.5
x <- 1e-5
a <- seq(-0.501, -0.499, length.out = 1000)
stopifnot(exprs = {
    all.equal(gammainc(a, x),
              -(x^a * exp(-x))/a +
              gamma(a + 1) * pgamma(x, a + 1, 1, lower = FALSE)/a)
})
