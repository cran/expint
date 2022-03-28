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
SEXP expint_do_expint(SEXP args);
SEXP expint_do_gammainc(SEXP args);

/* Exported function */
double expint_E1(double x, int scale);
double expint_E2(double x, int scale);
double expint_En(double x, int order, int scale);
double gamma_inc(double a, double x);

/* Constants (taken from gsl_machine.h in GSL sources) */
#define LOG_DBL_MIN   (-7.0839641853226408e+02)
#define LOG_DBL_MAX    7.0978271289338397e+02
#define EULER_CNST     0.57721566490153286060651209008

/* Macros */
#define E1_IS_ODD(n)  ((n) & 1)	/* taken from GSL */
