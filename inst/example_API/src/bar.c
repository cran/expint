/*
 *  Example of a routine making use of the interface defined in
 *  init.c. The routine will iterate on both arguments passed from R,
 *  thereby making the R function vectorized.
 *
 *  The code is derived from package actuar and base R.
 */

#include <R.h>
#include <Rinternals.h>
#include "locale.h"
#include "pkg.h"

#define mod_iterate1(n1, n2, i1, i2)            \
        for (i = i1 = i2 = 0; i < n;            \
             i1 = (++i1 == n1) ? 0 : i1,        \
             i2 = (++i2 == n2) ? 0 : i2,        \
             ++i)

SEXP pkg_do_bar(SEXP args)
{
    SEXP sx, sa, sy;
    int i, ix, ia, n, nx, na;
    double ai, *a, xi, *x, *y;
    Rboolean naflag = FALSE;

    args = CDR(args);	       /* drop function name from arguments */

    if (!isNumeric(CAR(args)) || !isNumeric(CADR(args)))
        error(_("invalid arguments"));

    na = LENGTH(CAR(args));
    nx = LENGTH(CADR(args));
    if ((na == 0) || (nx == 0))
        return(allocVector(REALSXP, 0));

    n = (nx < na) ? na : nx;

    PROTECT(sa = coerceVector(CAR(args), REALSXP));
    PROTECT(sx = coerceVector(CADR(args), REALSXP));
    PROTECT(sy = allocVector(REALSXP, n));
    a = REAL(sa);
    x = REAL(sx);
    y = REAL(sy);

    mod_iterate1(na, nx, ia, ix)
    {
        ai = a[ia];
        xi = x[ix];
	if (ISNA(ai) || ISNA(xi))
	    y[i] = NA_REAL;
        else if (ISNAN(ai) || ISNAN(xi))
	    y[i] = R_NaN;
        else
        {
	    /* this is where the expint routine is used */
	    y[i] = pkg_gamma_inc(ai, xi);
	    if (ISNAN(y[i])) naflag = TRUE;
        }
    }

    if (naflag)
        warning(R_MSG_NA);

    if (n == na)
    {
        SET_ATTRIB(sy, duplicate(ATTRIB(sa)));
        SET_OBJECT(sy, OBJECT(sa));
    }
    else if (n == nx)
    {
        SET_ATTRIB(sy, duplicate(ATTRIB(sx)));
        SET_OBJECT(sy, OBJECT(sx));
    }

    UNPROTECT(3);

    return sy;
}
