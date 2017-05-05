/*  == expint: Exponential Integral and Incomplete Gamma Function ==
 *
 *  Native routines registration, as per "Writing R extensions".
 *
 *  AUTHOR: Vincent Goulet <vincent.goulet@act.ulaval.ca>
 */

#include <Rinternals.h>
#include <R_ext/Visibility.h>
#include <R_ext/Rdynload.h>
#include "expint.h"

static const R_ExternalMethodDef ExternalEntries[] = {
    {"expint_do_expint", (DL_FUNC) &expint_do_expint, -1},
    {"expint_do_gammainc", (DL_FUNC) &expint_do_gammainc, -1},
    {NULL, NULL, 0}
};

void attribute_visible R_init_expint(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, NULL, NULL, ExternalEntries);
    R_useDynamicSymbols(dll, FALSE);
    R_forceSymbols(dll, TRUE);

    R_RegisterCCallable("expint", "expint_E1", (DL_FUNC) expint_E1);
    R_RegisterCCallable("expint", "expint_E2", (DL_FUNC) expint_E2);
    R_RegisterCCallable("expint", "expint_En", (DL_FUNC) expint_En);
    R_RegisterCCallable("expint", "gamma_inc", (DL_FUNC) gamma_inc);
}
