\name{NEWS}
\title{\pkg{expint} News}
\encoding{UTF-8}

\section{CHANGES IN \pkg{expint} VERSION 0.1-1}{
  \subsection{BUG FIX}{
    \itemize{
      \item{Fixed improper use of macro \code{ISNAN} (and \code{ISNA})
	that caused compilation to fail on Linux and Solaris.}
    }
  }
  \subsection{OTHER CHANGES}{
    \itemize{
      \item{Original author of GSL code for \code{expint} and
	\code{gamma_inc} (G. Jungman) added as an author of the
	package.}
      \item{Improved (read: more explicit) copyright notices to GSL,
	R Core Team and R Foundation where appropriate.}
    }
  }
}

\section{CHANGES IN \pkg{expint} VERSION 0.1-0}{
  \itemize{
    \item{Initial release. The package provides the \R functions to compute
      the exponential integrals \eqn{E_1(x)}, \eqn{E_2(x)}, \eqn{E_n(x)}
      and \eqn{Ei(x)}, and the incomplete gamma function \eqn{G(a, x)}.
      The package also provides a C API to access the actual workhorses
      \code{expint_E1}, \code{expint_E2}, \code{expint_En} and
      \code{gamma_inc}. Sub-directory \file{example_API} of the package
      installation directory contains a complete test package
      implementing API usage.}
  }
}

