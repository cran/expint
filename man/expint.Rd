\name{expint}
\alias{expint}
\alias{expint_E1}
\alias{expint_E2}
\alias{expint_En}
\alias{expint_Ei}
\alias{ExponentialIntegral}
\title{Exponential Integral}
\description{
  The exponential integrals \eqn{E_1(x)}, \eqn{E_2(x)}, \eqn{E_n(x)} and
  \eqn{Ei}.
}
\usage{
expint(x, order = 1L, scale = FALSE)
expint_E1(x, scale = FALSE)
expint_E2(x, scale = FALSE)
expint_En(x, order, scale = FALSE)
expint_Ei(x, scale = FALSE)
}
\arguments{
  \item{x}{vector of real numbers.}
  \item{order}{vector of non-negative integers; see Details.}
  \item{scale}{logical; when \code{TRUE} the result will be scaled by
    \eqn{e^x}{exp(x)}.}
}
\details{
  Abramowitz and Stegun (1972) first define the exponential
  integral as
  \deqn{
    E_1(x) = \int_x^\infty \frac{e^{-t}}{t}\, dt, \quad x \ne 0.}{%
    E_1(x) = int_x^Inf exp(-t)/t dt,  x != 0.}

  An alternative definition (to be understood in terms of the Cauchy
  principal value due to the singularity of the integrand at zero) is
  \deqn{
    \mathrm{Ei}(x) = - \int_{-x}^\infty \frac{e^{-t}}{t}\, dt
                   = - E_1(-x).}{%
    Ei(x) = - int_{-x}^Inf exp(-t)/t dt = - E_1(-x).}

  The exponential integral can also generalized to \code{order} \eqn{n} as
  \deqn{
    E_n(x) = \int_1^\infty \frac{e^{-xt}}{t^n}\, dt,}{%
    E_n(x) = int_1^Inf exp(-xt)/t^n dt,}
  for \eqn{n = 0, 1, 2, \dots}; \eqn{x} a real number (non-negative when
  \eqn{n > 2}).

  The following relation holds:
  \deqn{
    E_n(x) = x^{n - 1} \Gamma(1 - n, x),}{%
    E_n(x) = x^(n-1) G(1-n, x),}
  where \eqn{\Gamma(a, x)}{G(a, x)} is the incomplete gamma function
  implemented in \code{\link{gammainc}}.

  By definition, \eqn{E_0(x) = x^{-1} e^{-x}}{E_0(x) = exp(-x)/x},
  \eqn{x \ne 0}{x != 0}.

  Function \code{expint} is vectorized in both \code{x} and
  \code{order}, whereas function \code{expint_En} expects a single value
  for \code{order} and will only use the first value if \code{order} is
  a vector.

  Non-integer values of \code{order} will be silently coerced to
  integers using truncation towards zero.
}
\value{
  The value of the exponential integral.

  Invalid arguments will result in return value \code{NaN}, with a warning.
}
\note{
  The C implementation is based on code from the GNU Software Library
  \url{https://www.gnu.org/software/gsl/}.
}
\references{
  Abramowitz, M. and Stegun, I. A. (1972), \emph{Handbook of Mathematical
  Functions}, Dover.
}
\seealso{
  \code{\link{gammainc}}
}
\author{
  Vincent Goulet \email{vincent.goulet@act.ulaval.ca}
}
\examples{
## See section 5.3 of Abramowitz and Stegun
expint(1.275, order = 1:10)
expint(10, order = 1:10) * 1e5
expint(c(1.275, 10), order = c(1, 2))

expint_E1(1.275)                        # same as above
expint_E2(10)                           # same as above

## Figure 5.1 of Abramowitz and Stegun
curve(expint_Ei, xlim = c(0, 1.6), ylim = c(-3.9, 3.9),
      ylab = "y")
abline(h = 0)
curve(expint_E1, add = TRUE)
x <- 1.5
text(x, c(expint_Ei(x), expint_E1(x)),
     expression(Ei(x), E[1](x)),
     adj = c(0.5, -0.5))

## Figure 5.2 of Abramowitz and Stegun
plot(NA, xlim = c(-1.6, 1.6), ylim = c(0, 1),
     xlab = "x", ylab = expression(E[n](x)))
n <- c(10, 5, 3, 2, 1, 0)
for (order in n)
    curve(expint_En(x, order), add = TRUE)
x <- c(0.1, 0.15, 0.25, 0.35, 0.5, 0.7)
text(x, expint(x, n), paste("n =", n),
     adj = c(-0.2, -0.5))
}
\keyword{math}
