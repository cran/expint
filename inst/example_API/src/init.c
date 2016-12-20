/*
 *  Native routines registration, as per "Writing R extensions" and
 *  definition of native interfaces to two routines exported by
 *  package expint.
 *
 *  This is derived from code in packages zoo and xts.
 */

#include <Rinternals.h>
#include <R_ext/Rdynload.h>
#include <expintAPI.h>		/* this is actually optional */
#include "pkg.h"

/* This package uses the .External interface between R and C */
static const R_ExternalMethodDef ExternalEntries[] = {
    {"pkg_do_foo", (DL_FUNC) &pkg_do_foo, -1},
    {"pkg_do_bar", (DL_FUNC) &pkg_do_bar, -1},
    {NULL, NULL, 0}
};

/* Routine registration and native interfaces definitions. We prepend
 * names with pkg_ to avoid name clashes with expintAPI.h. */
void R_init_pkg(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, NULL, NULL, ExternalEntries);

    /* native interfaces to routines from package expint */
    pkg_expint_E1 = (double(*)(double,int))    R_GetCCallable("expint", "expint_E1");
    pkg_gamma_inc = (double(*)(double,double)) R_GetCCallable("expint", "gamma_inc");
}
