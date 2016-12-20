\name{gammainc}
\alias{gammainc}
\alias{gamma_inc}
\alias{IncompleteGammaFunction}
\title{Incomplete Gamma Function}
\description{
  The incomplete gamma function \eqn{\Gamma(a, x)}{G(a, x)}.
}
\usage{
gammainc(a, x)
}
\arguments{
  \item{a}{vector of real numbers.}
  \item{x}{vector of non-negative real numbers.}
}
\details{
  As defined in 6.5.3 of Abramowitz and Stegun (1972), the incomplete
  gamma function is
  \deqn{
    \Gamma(a, x) = \int_x^\infty t^{a-1} e^{-t}\, dt}{%
    G(a, x) = int_x^Inf t^(a - 1) exp(-t) dt}
  for \eqn{a} real and \eqn{x \ge 0}.

  For non-negative values of \eqn{a}, we have
  \deqn{
    \Gamma(a, x) = \Gamma(a) (1 - P(a, x)),}{%
    G(a, x) = Gamma(a) (1 - P(a, x)),}
  where \eqn{\Gamma(a)}{Gamma(a)} is the function implemented
  by \R's \code{\link{gamma}()} and \eqn{P(a, x)}{P(a, x)} is the
  cumulative distribution function of the gamma distribution (with scale
  equal to one) implemented by \R's \code{\link{pgamma}()}.

  Also, \eqn{\Gamma(0, x) = E_1(x)}{G(0, x) = E_1(x)}, \eqn{x > 0},
  where \eqn{E_1(x)} is the exponential integral implemented in
  \code{\link{expint}}.
}
\value{
  The value of the incomplete gamma function.

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
  \code{\link{expint}}
}
\author{
  Vincent Goulet \email{vincent.goulet@act.ulaval.ca}
}
\examples{
## a > 0
x <- c(0.2, 2.5, 5, 8, 10)
a <- 1.2
gammainc(a, x)
gamma(a) * pgamma(x, a, 1, lower = FALSE) # same

## a = 0
a <- 0
gammainc(a, x)
expint(x)                                 # same

## a < 0
a <- c(-0.25, -1.2, -2)
sapply(a, gammainc, x = x)
}
\keyword{math}
