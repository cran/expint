/*  == expint: Exponential Integral and Incomplete Gamma Function ==
 *
 *  Declarations for the package and various constant and macro
 *  definitions.
 *
 *  AUTHOR: Vincent Goulet <vincent.goulet@act.ulaval.ca>
 */

#include <Rinternals.h>

/* Error messages */
#define R_MSG_NA        _("NaNs produced")

/* Functions accessed from .External() */
SEXP expint_do_expint(SEXP);
SEXP expint_do_expint1(int, SEXP);
SEXP expint_do_expint2(int, SEXP);
SEXP expint_do_gammainc(SEXP);

/* Exported functions */
double expint_E1(double, int);
double expint_E2(double, int);
double expint_En(double, int, int);
double gamma_inc(double, double);

/* Constants (taken from gsl_machine.h in GSL sources) */
#define LOG_DBL_MIN   (-7.0839641853226408e+02)
#define LOG_DBL_MAX    7.0978271289338397e+02
#define EULER_CNST     0.57721566490153286060651209008

/* Macros */
#define E1_IS_ODD(n)  ((n) & 1)	/* taken from GSL */
