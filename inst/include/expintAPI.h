/*  == expint: Exponential Integral and Incomplete Gamma Function ==
 *
 *  Support for exported functions at the C level.
 *
 *  AUTHOR: Vincent Goulet <vincent.goulet@act.ulaval.ca>
 */

#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <R_ext/Visibility.h>

#ifdef  __cplusplus
extern "C" {
#endif

double expint_E1(double x, int scale);
double expint_E2(double x, int scale);
double expint_En(double x, int order, int scale);
double gamma_inc(double a, double x);

#ifdef  __cplusplus
}
#endif
