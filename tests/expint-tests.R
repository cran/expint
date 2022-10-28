### == expint: Exponential Integral and Incomplete Gamma Function ==
###
### Tests for the exponential integral Ei and the exponential integral
### of order 'n = 1, 2, ...'
###
###     E_n = int_x^infty exp(-t)/t^n dt.
###
### AUTHOR: Vincent Goulet <vincent.goulet@act.ulaval.ca>

## Load the package
library(expint)

###
### Basic functionality
###

## Some values of x
x <- runif(10, 0, 10)

## Equivalence between interfaces
stopifnot(exprs = {
    identical(expint(x, order = 1),
              expint_E1(x),
              expint_En(x, order = 1))
    identical(expint(x, order = 2),
              expint_E2(x),
              expint_En(x, order = 2))
    identical(expint(x, order = 3),
              expint_En(x, order = 3))
    identical(expint(x, order = 10),
              expint_En(x, order = 10))
    identical(expint(x, order = 1, scale = TRUE),
              expint_E1(x, scale = TRUE))
    identical(expint(x, order = 2, scale = TRUE),
              expint_E2(x, scale = TRUE))
    identical(expint(x, order = 3, scale = TRUE),
              expint_En(x, order = 3, scale = TRUE))
    identical(expint(x, order = 10, scale = TRUE),
              expint_En(x, order = 10, scale = TRUE))
})

## Identity between Ei and E1
stopifnot(exprs = {
    identical(expint_Ei(x),
              -expint_E1(-x))
    identical(expint_Ei(x, scale = TRUE),
              -expint_E1(-x, scale = TRUE))
})

## Vectorization of arguments
stopifnot(exprs = {
    identical(expint(head(x), order = 1:3),
              c(expint(x[1], 1), expint(x[2], 2), expint(x[3], 3),
                expint(x[4], 1), expint(x[5], 2), expint(x[6], 3)))
})

###
### Values from Table 5.1 of Abramovitz and Stegun
###

## Target values
xsmall <- c(1:4/100, seq(0.05, 0.5, by = 0.05))
TARGET_EI_SMALL <- c(1.002505566, 1.005022306, 1.007550283, 1.010089560,
                     1.012640202, 1.025566141, 1.038786018, 1.052308298, 1.066141726,
                     1.080295334, 1.094778451, 1.109600714, 1.124772082, 1.140302841)
TARGET_E1_SMALL <- c(0.9975055452, 0.9950221392, 0.9925497201, 0.9900882265,
                     0.9876375971, 0.9755453033, 0.9637156702, 0.9521414833, 0.9408157528,
                     0.9297317075, 0.9188827858, 0.9082626297, 0.8978650778, 0.8876841584)

xmed <- c(0.50, 0.60, 0.75, 1.00, 1.25, 1.55, 1.80, 2.00)
TARGET_EI_MED <- c(0.454219905, 0.769881290, 1.207332816, 1.895117816,
                   2.581047974, 3.451954503, 4.249867557, 4.954234356)
TARGET_E1_MED <- c(0.559773595, 0.454379503, 0.340340813, 0.219383934,
                   0.146413373, 0.092882108, 0.064713129, 0.048900511)

xlarge <- c(2.0, 3.5, 5.0, 7.5, 10.0)
TARGET_EI_LARGE <- c(1.340965420, 1.471782389, 1.353831278, 1.200421500, 1.131470205)
TARGET_E1_LARGE <- c(0.722657234, 0.807867661, 0.852110880, 0.892687854, 0.915633339)

EULER <- 0.57721566490153286060651209008

## Tests
stopifnot(exprs = {
    all.equal((expint_Ei(xsmall) - log(xsmall) - EULER)/xsmall, TARGET_EI_SMALL)
    all.equal((expint_E1(xsmall) + log(xsmall) + EULER)/xsmall, TARGET_E1_SMALL)
    all.equal(expint_Ei(xmed), TARGET_EI_MED)
    all.equal(expint_E1(xmed), TARGET_E1_MED)
    all.equal(xlarge * exp(-xlarge) * expint_Ei(xlarge), TARGET_EI_LARGE)
    all.equal(xlarge * expint_Ei(xlarge, scale = TRUE), TARGET_EI_LARGE)
    all.equal(xlarge * exp(xlarge) * expint_E1(xlarge), TARGET_E1_LARGE)
    all.equal(xlarge * expint_E1(xlarge, scale = TRUE), TARGET_E1_LARGE)
})

###
### Values from Table 5.2 of Abramovitz and Stegun
###

## Target values
xinv <- seq(0.100, 0.005, by = -0.005)
TARGET_EI <- c(1.13147021, 1.12249671, 1.11389377, 1.10564739, 1.09773775,
               1.09014087, 1.08283054, 1.07578038, 1.06896548, 1.06236365,
               1.05595591, 1.04972640, 1.04366194, 1.03775135, 1.03198503,
               1.02635451, 1.02085228, 1.01547157, 1.01020625, 1.00505077)
TARGET_E1 <- c(0.9156333394, 0.9192568286, 0.9229315844, 0.9266590998, 0.9304409399,
               0.9342787466, 0.9381742450, 0.9421292486, 0.9461456670, 0.9502255126,
               0.9543709099, 0.9585841038, 0.9628674711, 0.9672235311, 0.9716549596,
               0.9761646031, 0.9807554965, 0.9854308813, 0.9901942287, 0.9950492646)

## Tests
stopifnot(exprs = {
    all.equal(expint_Ei(1/xinv) * exp(-1/xinv)/xinv, TARGET_EI)
    all.equal(expint_Ei(1/xinv, scale = TRUE)/xinv, TARGET_EI)
    all.equal(expint_E1(1/xinv) * exp(1/xinv)/xinv, TARGET_E1)
    all.equal(expint_E1(1/xinv, scale = TRUE)/xinv, TARGET_E1)
})

###
### Values from Table 5.4 of Abramovitz and Stegun
###

## Target values
xsmall <- c(0.01, 0.10, 0.25, 0.30, 0.50)
osmall <- c(3, 4, 10, 20)
TARGET_E2_SMALL <- c(0.9957222, 0.9528035, 0.8643037, 0.8303071, 0.6732175)
TARGET_EN_SMALL <- c(0.4902766, 0.3283824, 0.1098682, 0.0520790,
                     0.4162915, 0.2877361, 0.0992984, 0.0473600,
                     0.3246841, 0.2325432, 0.0839220, 0.0404285,
                     0.3000418, 0.2169352, 0.0793524, 0.0383518,
                     0.2216044, 0.1652428, 0.0634583, 0.0310612)
TARGET_EN_SMALL <- matrix(TARGET_EN_SMALL, nrow = length(xsmall),
                          ncol = length(osmall), byrow = TRUE)

xlarge <- c(0.55, 1.00, 1.25, 1.50, 2.00)
olarge <- c(2, 3, 4, 10, 20)
TARGET_EN_LARGE <- c(0.3000996, 0.2059475, 0.1545596, 0.0600159, 0.0294670,
                     0.1484955, 0.1096920, 0.0860625, 0.0363940, 0.0183460,
                     0.1034881, 0.0785723, 0.0627631, 0.0275988, 0.0141035,
                     0.0731008, 0.0567395, 0.0460070, 0.0209461, 0.0108440,
                     0.0375343, 0.0301334, 0.0250228, 0.0120921, 0.0064143)
TARGET_EN_LARGE <- matrix(TARGET_EN_LARGE, nrow = length(xlarge),
                          ncol = length(olarge), byrow = TRUE)

## Tests
stopifnot(exprs = {
    all.equal(expint_E2(xsmall) - xsmall * log(xsmall),
              TARGET_E2_SMALL, tol = 5e-8)
    all.equal(outer(xsmall, osmall, expint),
              TARGET_EN_SMALL, tol = 5e-7)
    all.equal(outer(xlarge, olarge, expint),
              TARGET_EN_LARGE, tol = 5e-7)
})

###
### Values from Table 5.5 of Abramovitz and Stegun
###

## Target values
xinv <- c(seq(0.50, 0.10, by = -0.05), seq(0.09, 0.01, by = -0.01))
order <- c(2, 3, 4, 10, 20)
TARGET_EN <- c(1.10937, 1.11329, 1.10937, 1.07219, 1.04270,
               1.09750, 1.10285, 1.10071, 1.06926, 1.04179,
               1.08533, 1.09185, 1.09136, 1.06586, 1.04067,
               1.07292, 1.08026, 1.08125, 1.06187, 1.03932,
               1.06034, 1.06808, 1.07031, 1.05712, 1.03762,
               1.04770, 1.05536, 1.05850, 1.05138, 1.03543,
               1.03522, 1.04222, 1.04584, 1.04432, 1.03249,
               1.02325, 1.02895, 1.03247, 1.03550, 1.02837,
               1.01240, 1.01617, 1.01889, 1.02436, 1.02222,
               1.01045, 1.01377, 1.01624, 1.02182, 1.02060,
               1.00861, 1.01147, 1.01366, 1.01917, 1.01883,
               1.00688, 1.00927, 1.01116, 1.01642, 1.01688,
               1.00528, 1.00721, 1.00878, 1.01360, 1.01472,
               1.00384, 1.00531, 1.00654, 1.01074, 1.01234,
               1.00258, 1.00361, 1.00451, 1.00790, 1.00973,
               1.00152, 1.00217, 1.00275, 1.00516, 1.00692,
               1.00071, 1.00103, 1.00133, 1.00271, 1.00401,
               1.00019, 1.00027, 1.00036, 1.00081, 1.00137)
TARGET_EN <- matrix(TARGET_EN, nrow = length(xinv),
                    ncol = length(order), byrow = TRUE)

## Tests
stopifnot(exprs = {
    all.equal(outer(1/xinv, order, "+") * exp(1/xinv) *
              outer(1/xinv, order, expint),
              TARGET_EN, tolerance = 5e-6)
    all.equal(outer(1/xinv, order, "+") *
              outer(1/xinv, order, expint, scale = TRUE),
              TARGET_EN, tolerance = 5e-6)
})

###
### Examples from section 5.3 of Abramowitz and Stegun
###

## Target values
order <- 1:10
xsmall <- 1.275
TARGET_SMALL <- c(0.1408099, 0.0998984, 0.0760303, 0.0608307, 0.0504679,
                  0.0430168, 0.0374307, 0.0331009, 0.0296534, 0.0268469)

xlarge <- 10
TARGET_LARGE <- c(0.41570, 0.38302, 0.35488, 0.33041, 0.30898,
                  0.29005, 0.27325, 0.25822, 0.24472, 0.23253)

## Tests
stopifnot(exprs = {
    all.equal(expint(xsmall, order),
              TARGET_SMALL, tolerance = 1e-6)
    all.equal(expint(xlarge, order) * 1e5,
              TARGET_LARGE, tolerance = 1e-5)
})
