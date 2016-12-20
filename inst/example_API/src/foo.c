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

SEXP pkg_do_foo(SEXP args)
{
    SEXP sx, sy;
    int i, nx;
    double xi, *x, *y;
    Rboolean naflag = FALSE;

    if (!isNumeric(CADR(args)))
        error(_("invalid arguments"));

    nx = LENGTH(CADR(args));
    if (nx == 0)
        return(allocVector(REALSXP, 0));

    PROTECT(sx = coerceVector(CADR(args), REALSXP));
    PROTECT(sy = allocVector(REALSXP, nx));
    x = REAL(sx);
    y = REAL(sy);

    for (i = 0; i < nx; i++)
    {
        xi = x[i];
	if (ISNA(xi))
	    y[i] = NA_REAL;			\
        else if (ISNAN(xi))
	    y[i] = R_NaN;
        else
        {
	    /* this is where the expint routine is used */
            y[i] = pkg_expint_E1(xi, 0);
            if (ISNAN(y[i])) naflag = TRUE;
        }
    }

    if (naflag)
        warning(R_MSG_NA);

    SET_ATTRIB(sy, duplicate(ATTRIB(sx)));
    SET_OBJECT(sy, OBJECT(sx));
    UNPROTECT(2);

    return sy;
}
