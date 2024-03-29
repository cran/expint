/*  == expint: Exponential Integral and Incomplete Gamma Function ==
 *
 *  Functions to compute the exponential integral functions
 *
 *     E_1(x) = int_x^infty exp(-t)/t dt,
 *     E_2(x) = int_x^infty exp(-t)/t^2 dt
 *
 *  and
 *
 *     E_n(x) = int_x^infty exp(-t)/t^n dt.
 *
 *  Copyright (C) 2016 Vincent Goulet
 *
 *  The code in part IMPLEMENTATION is derived from the GNU Scientific
 *  Library (GSL) v2.2.1 <https://www.gnu.org/software/gsl/>
 *
 *  Copyright (C) 2007 Brian Gough
 *  Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002 Gerard Jungman
 *
 *  The code in part R TO C INTERFACE is derived from R source code.
 *
 *  Copyright (C) 1995--1997 Robert Gentleman and Ross Ihaka
 *  Copyright (C) 1998--2016 The R Core Team.
 *  Copyright (C) 2003--2016 The R Foundation
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as
 *  published by the Free Software Foundation; either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 *  02110-1301, USA.
 *
 *  AUTHOR for the GSL: G. Jungman
 *  AUTHOR for expint: Vincent Goulet <vincent.goulet@act.ulaval.ca>
 *                     with much indirect help from the R Core Team
 */

#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>
#include "locale.h"
#include "expint.h"

/* Prototypes of auxiliary functions */
static SEXP expint1_1(SEXP, SEXP, double (*f)(double, int));
static SEXP expint2_1(SEXP, SEXP, SEXP, double (*f)(double, int, int));

/*
 *  IMPLEMENTATION OF THE WORKHORSES
 *
 *  Adapted from "special functions" material in the GSL.
 *
 */

/* Data structure for a Chebyshev series over a given interval */
struct cheb_series_struct {
    double * c;   /* coefficients                */
    int order;    /* order of expansion          */
    double a;     /* lower interval point        */
    double b;     /* upper interval point        */
    int order_sp; /* effective single precision order */
};
typedef struct cheb_series_struct cheb_series;


/*
 Chebyshev expansions: based on SLATEC e1.f, W. Fullerton

 Series for AE11       on the interval -1.00000D-01 to  0.
                                        with weighted error   1.76E-17
                                         log weighted error  16.75
                               significant figures required  15.70
                                    decimal places required  17.55


 Series for AE12       on the interval -2.50000D-01 to -1.00000D-01
                                        with weighted error   5.83E-17
                                         log weighted error  16.23
                               significant figures required  15.76
                                    decimal places required  16.93


 Series for E11        on the interval -4.00000D+00 to -1.00000D+00
                                        with weighted error   1.08E-18
                                         log weighted error  17.97
                               significant figures required  19.02
                                    decimal places required  18.61


 Series for E12        on the interval -1.00000D+00 to  1.00000D+00
                                        with weighted error   3.15E-18
                                         log weighted error  17.50
                        approx significant figures required  15.8
                                    decimal places required  18.10


 Series for AE13       on the interval  2.50000D-01 to  1.00000D+00
                                        with weighted error   2.34E-17
                                         log weighted error  16.63
                               significant figures required  16.14
                                    decimal places required  17.33


 Series for AE14       on the interval  0.          to  2.50000D-01
                                        with weighted error   5.41E-17
                                         log weighted error  16.27
                               significant figures required  15.38
                                    decimal places required  16.97
*/

static double AE11_data[39] = {
   0.121503239716065790,
  -0.065088778513550150,
   0.004897651357459670,
  -0.000649237843027216,
   0.000093840434587471,
   0.000000420236380882,
  -0.000008113374735904,
   0.000002804247688663,
   0.000000056487164441,
  -0.000000344809174450,
   0.000000058209273578,
   0.000000038711426349,
  -0.000000012453235014,
  -0.000000005118504888,
   0.000000002148771527,
   0.000000000868459898,
  -0.000000000343650105,
  -0.000000000179796603,
   0.000000000047442060,
   0.000000000040423282,
  -0.000000000003543928,
  -0.000000000008853444,
  -0.000000000000960151,
   0.000000000001692921,
   0.000000000000607990,
  -0.000000000000224338,
  -0.000000000000200327,
  -0.000000000000006246,
   0.000000000000045571,
   0.000000000000016383,
  -0.000000000000005561,
  -0.000000000000006074,
  -0.000000000000000862,
   0.000000000000001223,
   0.000000000000000716,
  -0.000000000000000024,
  -0.000000000000000201,
  -0.000000000000000082,
   0.000000000000000017
};
static cheb_series AE11_cs = {
  AE11_data,
  38,
  -1, 1,
  20
};

static double AE12_data[25] = {
   0.582417495134726740,
  -0.158348850905782750,
  -0.006764275590323141,
   0.005125843950185725,
   0.000435232492169391,
  -0.000143613366305483,
  -0.000041801320556301,
  -0.000002713395758640,
   0.000001151381913647,
   0.000000420650022012,
   0.000000066581901391,
   0.000000000662143777,
  -0.000000002844104870,
  -0.000000000940724197,
  -0.000000000177476602,
  -0.000000000015830222,
   0.000000000002905732,
   0.000000000001769356,
   0.000000000000492735,
   0.000000000000093709,
   0.000000000000010707,
  -0.000000000000000537,
  -0.000000000000000716,
  -0.000000000000000244,
  -0.000000000000000058
};
static cheb_series AE12_cs = {
  AE12_data,
  24,
  -1, 1,
  15
};

static double E11_data[19] = {
  -16.11346165557149402600,
    7.79407277874268027690,
   -1.95540581886314195070,
    0.37337293866277945612,
   -0.05692503191092901938,
    0.00721107776966009185,
   -0.00078104901449841593,
    0.00007388093356262168,
   -0.00000620286187580820,
    0.00000046816002303176,
   -0.00000003209288853329,
    0.00000000201519974874,
   -0.00000000011673686816,
    0.00000000000627627066,
   -0.00000000000031481541,
    0.00000000000001479904,
   -0.00000000000000065457,
    0.00000000000000002733,
   -0.00000000000000000108
};
static cheb_series E11_cs = {
  E11_data,
  18,
  -1, 1,
  13
};

static double E12_data[16] = {
  -0.03739021479220279500,
   0.04272398606220957700,
  -0.13031820798497005440,
   0.01441912402469889073,
  -0.00134617078051068022,
   0.00010731029253063780,
  -0.00000742999951611943,
   0.00000045377325690753,
  -0.00000002476417211390,
   0.00000000122076581374,
  -0.00000000005485141480,
   0.00000000000226362142,
  -0.00000000000008635897,
   0.00000000000000306291,
  -0.00000000000000010148,
   0.00000000000000000315
};
static cheb_series E12_cs = {
  E12_data,
  15,
  -1, 1,
  10
};

static double AE13_data[25] = {
  -0.605773246640603460,
  -0.112535243483660900,
   0.013432266247902779,
  -0.001926845187381145,
   0.000309118337720603,
  -0.000053564132129618,
   0.000009827812880247,
  -0.000001885368984916,
   0.000000374943193568,
  -0.000000076823455870,
   0.000000016143270567,
  -0.000000003466802211,
   0.000000000758754209,
  -0.000000000168864333,
   0.000000000038145706,
  -0.000000000008733026,
   0.000000000002023672,
  -0.000000000000474132,
   0.000000000000112211,
  -0.000000000000026804,
   0.000000000000006457,
  -0.000000000000001568,
   0.000000000000000383,
  -0.000000000000000094,
   0.000000000000000023
};
static cheb_series AE13_cs = {
  AE13_data,
  24,
  -1, 1,
  15
};

static double AE14_data[26] = {
  -0.18929180007530170,
  -0.08648117855259871,
   0.00722410154374659,
  -0.00080975594575573,
   0.00010999134432661,
  -0.00001717332998937,
   0.00000298562751447,
  -0.00000056596491457,
   0.00000011526808397,
  -0.00000002495030440,
   0.00000000569232420,
  -0.00000000135995766,
   0.00000000033846628,
  -0.00000000008737853,
   0.00000000002331588,
  -0.00000000000641148,
   0.00000000000181224,
  -0.00000000000052538,
   0.00000000000015592,
  -0.00000000000004729,
   0.00000000000001463,
  -0.00000000000000461,
   0.00000000000000148,
  -0.00000000000000048,
   0.00000000000000016,
  -0.00000000000000005
};
static cheb_series AE14_cs = {
  AE14_data,
  25,
  -1, 1,
  13
};

/* Adapted from specfun/cheb_eval.c in GSL sources */
static inline double cheb_eval(const cheb_series * cs,
				 const double x)
{
    int j;
    double d  = 0.0;
    double dd = 0.0;

    double y  = (2.0*x - cs->a - cs->b) / (cs->b - cs->a);
    double y2 = 2.0 * y;

    for(j = cs->order; j >= 1; j--)
    {
	double temp = d;
	d = y2*d - dd + cs->c[j];
	dd = temp;
    }

    return y*d - dd + 0.5 * cs->c[0];
}

/* Adapted from specfun/expint.c::expint_E1_impl in GSL sources */
double expint_E1(double x, int scale)
{
#ifdef IEEE_754
    if (ISNAN(x))
	return x;
#endif

    const double xmaxt = -LOG_DBL_MIN;       /* XMAXT = -LOG(DBL_MIN) */
    const double xmax  = xmaxt - log(xmaxt); /* XMAX = XMAXT - LOG(XMAXT) */

    if (x < -xmax && !scale)
    {
	warning(_("overflow in expint_E1"));
	return R_PosInf;
    }
    else if (x <= -10.0)
    {
	const double s = 1.0/x * (scale ? 1.0 : exp(-x));
	const double cheb = cheb_eval(&AE11_cs, 20.0/x+1.0);
	return s * (1.0 + cheb);
    }
    else if (x <= -4.0)
    {
	const double s = 1.0/x * (scale ? 1.0 : exp(-x));
	const double cheb = cheb_eval(&AE12_cs, (40.0/x+7.0)/3.0);
	return s * (1.0 + cheb);
    }
    else if (x <= -1.0)
    {
	const double s = (scale ? exp(x) : 1.0);
	const double ln_term = -log(fabs(x));
	const double cheb = cheb_eval(&E11_cs, (2.0*x+5.0)/3.0);
	return s * (ln_term + cheb);
    }
    else if (x == 0.0)
    {
	return R_NaN;
    }
    else if (x <= 1.0)
    {
	const double s = (scale ? exp(x) : 1.0);
	const double ln_term = -log(fabs(x));
	const double cheb = cheb_eval(&E12_cs, x);
	return s * (ln_term - 0.6875 + x + cheb);
    }
    else if (x <= 4.0)
    {
	const double s = 1.0/x * (scale ? 1.0 : exp(-x));
	const double cheb = cheb_eval(&AE13_cs, (8.0/x-5.0)/3.0);
	return s * (1.0 + cheb);
    }
    else if (x <= xmax || scale)
    {
	const double s = 1.0/x * (scale ? 1.0 : exp(-x));
	const double cheb = cheb_eval(&AE14_cs, 8.0/x-1.0);
	double res = s * (1.0 +  cheb);
	if (res == 0.0)
	{
	    warning(_("underflow in expint_E1"));
	    return 0.0;
	}
	else
	    return res;
    }
    else {
	warning(_("underflow in expint_E1"));
	return 0.0;
    }
}

/* Adapted from specfun/expint.c::expint_E2_impl in GSL sources */
double expint_E2(double x, int scale)
{
#ifdef IEEE_754
    if (ISNAN(x))
	return x;
#endif

    const double xmaxt = -LOG_DBL_MIN;
    const double xmax  = xmaxt - log(xmaxt);

    if (x < -xmax && !scale)
    {
	warning(_("overflow in expint_E2"));
	return R_PosInf;
    }
    else if (x == 0.0)
    {
	return 1.0;
    }
    else if (x < 100.0)
    {
	const double ex = (scale ? 1.0 : exp(-x));
	return ex - x * expint_E1(x, scale);
    }
    else if (x < xmax || scale)
    {
	const double s = (scale ? 1.0 : exp(-x));
	const double c1  = -2.0;
	const double c2  =  6.0;
	const double c3  = -24.0;
	const double c4  =  120.0;
	const double c5  = -720.0;
	const double c6  =  5040.0;
	const double c7  = -40320.0;
	const double c8  =  362880.0;
	const double c9  = -3628800.0;
	const double c10 =  39916800.0;
	const double c11 = -479001600.0;
	const double c12 =  6227020800.0;
	const double c13 = -87178291200.0;
	const double y = 1.0/x;
	const double sum6 = c6+y*(c7+y*(c8+y*(c9+y*(c10+y*(c11+y*(c12+y*c13))))));
	const double sum  = y*(c1+y*(c2+y*(c3+y*(c4+y*(c5+y*sum6)))));
	double res = s * (1.0 + sum)/x;
	if (res == 0.0)
	{
	    warning(_("underflow in expint_E2"));
	    return 0.0;
	}
	else
	    return res;
    }
    else {
	warning(_("underflow in expint_E2"));
	return 0.0;
    }
}

/* Macro used in expint_En (only) */
#define CHECK_UNDERFLOW(x)			\
    if (fabs(x) < DBL_MIN) {			\
        warning(_("underflow in expint_En"));	\
	return 0.0;				\
    }						\

/* Adapted from specfun/expint.c::expint_En_impl in GSL sources */
double expint_En(double x, int n, int scale)
{
#ifdef IEEE_754
    if (ISNAN(x))
	return x;
#endif

    if (n < 0)
	return R_NaN;
    else if (n == 0)
    {
	if (x == 0)
	    return R_NaN;
	else
	{
	    double res = (scale ? 1.0 : exp(-x)) / x;
	    CHECK_UNDERFLOW(res);
	    return res;
	}
    }
    else if (n == 1)
	return expint_E1(x, scale);
    else if (n == 2)
	return expint_E2(x, scale);
    else
    {
	if (x < 0)
	    return R_NaN;
	if (x == 0)
	{
	    double res = (scale ? exp(x) : 1 ) * (1/(n-1.0));
	    CHECK_UNDERFLOW(res);
	    return res;
	}
	else
	{
	    double s = (scale ? exp(x) : 1.0);
	    double res = gamma_inc((double) 1 - n, x);
	    res *= s * R_pow_di(x, n - 1);
	    CHECK_UNDERFLOW(res);
	    return res;
	}
    }
}


/*
 *  R TO C INTERFACE
 *
 *  Adapted from src/main/arithmetic.c in R sources and from a similar
 *  scheme in package actuar. Main difference: everything is in this
 *  one file.
 *
 */

/* Functions to handle cases with one argument (REAL) and an integer
 * flag */
static SEXP expint1_1(SEXP sx, SEXP sI, double (*f)(double, int))
{
    SEXP sy;
    int i, nx, sxo = OBJECT(sx);
    double xi, *x, *y;
    int i_1;
    Rboolean naflag = FALSE;

    if (!isNumeric(sx))
        error(_("invalid arguments"));

    nx = LENGTH(sx);
    if (nx == 0)
        return(allocVector(REALSXP, 0));
    PROTECT(sx = coerceVector(sx, REALSXP));
    PROTECT(sy = allocVector(REALSXP, nx));
    x = REAL(sx);
    y = REAL(sy);

    i_1 = asInteger(sI);

    for (i = 0; i < nx; i++)
    {
        xi = x[i];
	if (ISNA(xi))
	    y[i] = NA_REAL;
        else if (ISNAN(xi))
	    y[i] = R_NaN;
        else
        {
            y[i] = f(xi, i_1);
            if (ISNAN(y[i])) naflag = TRUE;
        }
    }

    if (naflag)
        warning(R_MSG_NA);

    SET_ATTRIB(sy, duplicate(ATTRIB(sx)));
    SET_OBJECT(sy, sxo);
    UNPROTECT(2);

    return sy;
}

#define EXPINT1_1(A, FUN) expint1_1(CAR(A), CADR(A), FUN);

SEXP expint_do_expint1(int code, SEXP args)
{
    switch (code)
    {
    case 1: return EXPINT1_1(args, expint_E1);
    case 2: return EXPINT1_1(args, expint_E2);
    default:
        error(_("internal error in expint_do_expint1"));
    }

    return args;                /* never used; to keep -Wall happy */
}

/* Functions to handle cases with two arguments (REAL and INTEGER) and
 * an integer flag */
#define mod_iterate2(n1, n2, i1, i2)            \
        for (i = i1 = i2 = 0; i < n;            \
             i1 = (++i1 == n1) ? 0 : i1,        \
             i2 = (++i2 == n2) ? 0 : i2,        \
             ++i)

static SEXP expint2_1(SEXP sx, SEXP sa, SEXP sI, double (*f)(double, int, int))
{
    SEXP sy;
    int i, ix, ia, n, nx, na,
	sxo = OBJECT(sx), sao = OBJECT(sa);
    double xi, *x, *y;
    int ai, *a, i_1;
    Rboolean naflag = FALSE;

    if (!isNumeric(sx) || !isNumeric(sa))
        error(_("invalid arguments"));

    nx = LENGTH(sx);
    na = LENGTH(sa);
    if ((nx == 0) || (na == 0))
        return(allocVector(REALSXP, 0));

    n = (nx < na) ? na : nx;

    PROTECT(sx = coerceVector(sx, REALSXP));
    PROTECT(sa = coerceVector(sa, INTSXP));
    PROTECT(sy = allocVector(REALSXP, n));
    x = REAL(sx);
    a = INTEGER(sa);
    y = REAL(sy);

    i_1 = asInteger(sI);

    mod_iterate2(nx, na, ix, ia)
    {
        xi = x[ix];
        ai = a[ia];
	if (ISNA(xi) || ai == NA_INTEGER)
	    y[i] = NA_REAL;
        else if (ISNAN(xi))
	    y[i] = R_NaN;
        else
        {
	    if (ai == 1)
		y[i] = expint_E1(xi, i_1);
	    else if (ai == 2)
		y[i] = expint_E2(xi, i_1);
	    else
		y[i] = f(xi, ai, i_1);
	    if (ISNAN(y[i])) naflag = TRUE;
        }
    }

    if (naflag)
        warning(R_MSG_NA);

    if (n == nx)
    {
        SET_ATTRIB(sy, duplicate(ATTRIB(sx)));
        SET_OBJECT(sy, sxo);
    }
    else if (n == na)
    {
        SET_ATTRIB(sy, duplicate(ATTRIB(sa)));
        SET_OBJECT(sy, sao);
    }

    UNPROTECT(3);

    return sy;
}

#define EXPINT2_1(A, FUN) expint2_1(CAR(A), CADR(A), CADDR(A), FUN);

SEXP expint_do_expint2(int code, SEXP args)
{
    switch (code)
    {
    case 1: return EXPINT2_1(args, expint_En);
    default:
        error(_("internal error in expint_do_expint2"));
    }

    return args;                /* never used; to keep -Wall happy */
}

/* Data structure for internal functions */
typedef struct {
    char *name;
    SEXP (*cfun)(int, SEXP);
    int code;
} expint_tab_struct;

static expint_tab_struct expint_tab[] = {
    /* One argument functions */
    {"E1", expint_do_expint1, 1},
    {"E2", expint_do_expint1, 2},
    /* Two argument functions */
    {"En", expint_do_expint2, 1},
    {0, 0, 0}
};

/* Function called by .External() */
SEXP expint_do_expint(SEXP args)
{
    int i;
    const char *name;

    /* Extract type of exponential integral */
    args = CDR(args);
    name = CHAR(STRING_ELT(CAR(args), 0));

    /* Dispatch to expint_do_expint[1,2] */
    for (i = 0; expint_tab[i].name; i++)
    {
        if (!strcmp(expint_tab[i].name, name))
        {
            return expint_tab[i].cfun(expint_tab[i].code, CDR(args));
        }
    }

    /* No dispatch is an error */
    error("internal error in expint_do_expint");

    return args;                /* never used; to keep -Wall happy */
}
