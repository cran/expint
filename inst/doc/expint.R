### R code from vignette source 'expint.Rnw'

###################################################
### code chunk number 1: expint.Rnw:15-17
###################################################
library(expint)
options(width = 60)


###################################################
### code chunk number 2: expint.Rnw:181-182
###################################################
expint(c(1.275, 10, 12.3), order = 1:3)


###################################################
### code chunk number 3: expint.Rnw:196-199
###################################################
expint_E1(1.275)
expint_E2(10)
expint_En(12.3, order = 3L)


###################################################
### code chunk number 4: expint.Rnw:204-206
###################################################
expint_Ei(5)
-expint_E1(-5)     # same


###################################################
### code chunk number 5: expint.Rnw:318-319
###################################################
op <- options() # remember default number of digits


###################################################
### code chunk number 6: expint.Rnw:321-324
###################################################
options(digits = 20)
gammainc(1.2, 3)
gamma(1.2) * pgamma(3, 1.2, 1, lower = FALSE)


###################################################
### code chunk number 7: expint.Rnw:326-327
###################################################
options(op)     # restore defaults


###################################################
### code chunk number 8: expint.Rnw:392-397
###################################################
x <- c(1.275, 10, 12.3)
n <- 1:10
structure(t(outer(x, n, expint)),
          dimnames = list(paste("n =", n),
                          paste("x =", x)))


###################################################
### code chunk number 9: expint.Rnw:402-407
###################################################
a <- c(-1.5, -1, -0.5, 1)
x <- 1:10
structure(t(outer(a, x, gammainc)),
          dimnames = list(paste("x =", x),
                          paste("a =", a)))


###################################################
### code chunk number 10: expint.Rnw:439-451
###################################################
a <- seq(-0.501, -0.499, length.out = 1000)
x <- 1e-5
if (requireNamespace("gsl"))
    gGamma <- gsl::gamma_inc(a, x)
if (requireNamespace("pracma"))
    pGamma <- sapply(a, pracma::incgam, x = x)
plot(a, gGamma, type = "l", ylab = expression(Gamma(a, x)),
     main = "Versions of package expint prior to 0.2-0")
lines(a, pGamma, lty = 2, lwd = 2, col = "orange")
legend(-0.5002, 635,
       c("expint::gammainc(a, 1e-05)", "pracma::incgam(1e-05, a)"),
       lty = c(1, 2), lwd = c(1, 2), col = c("black", "orange"))


###################################################
### code chunk number 11: expint.Rnw:607-618
###################################################
a <- seq(-0.501, -0.499, length.out = 1000)
x <- 1e-5
eGamma <- gammainc(a, x)
if (requireNamespace("pracma"))
    pGamma <- sapply(a, pracma::incgam, x = x)
plot(a, eGamma, type = "l", ylab = expression(Gamma(a, x)),
     main = "Versions of package expint from 0.2-0")
lines(a, pGamma, lty = 2, lwd = 2, col = "orange")
legend(-0.5002, 635,
       c("expint::gammainc(a, 1e-05)", "pracma::incgam(1e-05, a)"),
       lty = c(1, 2), lwd = c(1, 2), col = c("black", "orange"))


