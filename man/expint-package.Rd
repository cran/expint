\name{expint-package}
\alias{expint-package}
\docType{package}
\title{
  \packageTitle{expint}
}
\description{
  The exponential integrals \eqn{E_1(x)}, \eqn{E_2(x)}, \eqn{E_n(x)} and
  \eqn{Ei(x)}, and the incomplete gamma function \eqn{\Gamma(a, x)}{G(a,
    x)} that is defined for negative values of its first argument.
}
\details{
  The exponential integral
  \deqn{
    E_1(x) = \int_x^\infty \frac{e^{-t}}{t}\, dt}{%
    E_1(x) = int_x^Inf exp(-t)/t dt}
  and the incomplete gamma function
  \deqn{
    \Gamma(a, x) = \int_x^\infty t^{a-1} e^{-t}\, dt}{%
    G(a, x) = int_x^Inf t^(a-1) exp(-t) dt}
  are closely related functions that arise in various fields of
  mathematics.

  \pkg{expint} is a small package that provides \R functions to compute
  the exponential integral and the incomplete gamma function.

  Most conveniently for \R package developers, the package also gives
  access to the underlying C workhorses through an API; see the package
  vignette for instructions.

  The C routines are adapted versions of those of the GNU Scientific
  Library \url{https://www.gnu.org/software/gsl/}.
}
\seealso{
  \code{\link{expint}} for the exponential integral family of functions.

  \code{\link{gammainc}} for the incomplete gamma function.

  \code{vignette("expint")} for a detailed presentation of the package.
}
\author{
  Vincent Goulet \email{vincent.goulet@act.ulaval.ca}
}
\references{
  Abramowitz, M. and Stegun, I. A. (1972), \emph{Handbook of Mathematical
  Functions}, Dover.
}
\keyword{package}
\keyword{math}
