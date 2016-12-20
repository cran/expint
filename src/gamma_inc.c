/*  == expint: Exponential Integral and Incomplete Gamma Function ==
 *
 *  Functions to compute the incomplete gamma function
 *
 *     G(a,x) = int_x^infty t^{a-1} exp(-t) dt
 *
 *  for a real and x >= 0. [This differs from 'pgamma' of base R in
 *  that negative values of 'a' are admitted.]
 *
 *  The code in this file is adapted from code in the GNU Scientific
 *  Library (GSL) v2.2.1 <https://www.gnu.org/software/gsl/>
 *
 *  Copyright (C) 2016 Vincent Goulet
 *  Copyright (C) 2007 Brian Gough
 *  Copyright (C) 1996, 1997, 1998, 1999, 2000, 2001, 2002 Gerard Jungman
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
 */

#include <R.h>
#include <Rinternals.h>
#include <Rmath.h>
#include "locale.h"
#include "expint.h"

/* Continued fraction which occurs in evaluation
 * of Q(a,x) or Gamma(a,x).
 *
 *              1   (1-a)/x  1/x  (2-a)/x   2/x  (3-a)/x
 *   F(a,x) =  ---- ------- ----- -------- ----- -------- ...
 *             1 +   1 +     1 +   1 +      1 +   1 +
 *
 * Hans E. Plesser, 2002-01-22 (hans dot plesser at itf dot nlh dot no).
 *
 * Split out from gamma_inc_Q_CF() by GJ [Tue Apr  1 13:16:41 MST 2003].
 * See gamma_inc_Q_CF() below.
 *
 */
double gamma_inc_F_CF(double a, double x)
{
    const int    nmax  =  5000;
    const double small =  R_pow_di(DOUBLE_EPS, 3);

    double hn = 1.0;           /* convergent */
    double Cn = 1.0 / small;
    double Dn = 1.0;
    int n;

    /* n == 1 has a_1, b_1, b_0 independent of a,x,
       so that has been done by hand                */
    for (n = 2 ; n < nmax ; n++)
    {
	double an;
	double delta;

	if (E1_IS_ODD(n))
	    an = 0.5 * (n - 1)/x;
	else
	    an = (0.5 * n - a)/x;

	Dn = 1.0 + an * Dn;
	if (fabs(Dn) < small)
	    Dn = small;
	Cn = 1.0 + an/Cn;
	if (fabs(Cn) < small)
	    Cn = small;
	Dn = 1.0/Dn;
	delta = Cn * Dn;
	hn *= delta;
	if (fabs(delta-1.0) < DOUBLE_EPS)
	    break;
    }

    if (n == nmax)
	warning(_("maximum number of iterations reached in gamma_inc_F_CF"));

    return hn;
}

/* Useful for small a and x. Handles the subtraction analytically. */
double gamma_inc_Q_series(double a, double x)
{
    const int nmax = 5000;
    double term1;  /* 1 - x^a/Gamma(a+1) */
    double sum;    /* 1 + (a+1)/(a+2)(-x)/2! + (a+1)/(a+3)(-x)^2/3! + ... */
    int n;
    double term2;  /* a temporary variable used at the end */

    {
	/* Evaluate series for 1 - x^a/Gamma(a+1), small a */
	const double pg21 = -2.404113806319188570799476;  /* PolyGamma[2,1] */
	const double lnx = log(x);
	const double el = EULER_CNST + lnx;
	const double c1 = -el;
	const double c2 = M_PI*M_PI/12.0 - 0.5*el*el;
	const double c3 = el*(M_PI*M_PI/12.0 - el*el/6.0) + pg21/6.0;
	const double c4 = -0.04166666666666666667
	    * (-1.758243446661483480 + lnx)
	    * (-0.764428657272716373 + lnx)
	    * ( 0.723980571623507657 + lnx)
	    * ( 4.107554191916823640 + lnx);
	const double c5 = -0.0083333333333333333
	    * (-2.06563396085715900 + lnx)
	    * (-1.28459889470864700 + lnx)
	    * (-0.27583535756454143 + lnx)
	    * ( 1.33677371336239618 + lnx)
	    * ( 5.17537282427561550 + lnx);
	const double c6 = -0.0013888888888888889
	    * (-2.30814336454783200 + lnx)
	    * (-1.65846557706987300 + lnx)
	    * (-0.88768082560020400 + lnx)
	    * ( 0.17043847751371778 + lnx)
	    * ( 1.92135970115863890 + lnx)
	    * ( 6.22578557795474900 + lnx);
	const double c7 = -0.00019841269841269841
	    * (-2.5078657901291800 + lnx)
	    * (-1.9478900888958200 + lnx)
	    * (-1.3194837322612730 + lnx)
	    * (-0.5281322700249279 + lnx)
	    * ( 0.5913834939078759 + lnx)
	    * ( 2.4876819633378140 + lnx)
	    * ( 7.2648160783762400 + lnx);
	const double c8 = -0.00002480158730158730
	    * (-2.677341544966400 + lnx)
	    * (-2.182810448271700 + lnx)
	    * (-1.649350342277400 + lnx)
	    * (-1.014099048290790 + lnx)
	    * (-0.191366955370652 + lnx)
	    * ( 0.995403817918724 + lnx)
	    * ( 3.041323283529310 + lnx)
	    * ( 8.295966556941250 + lnx);
	const double c9 = -2.75573192239859e-6
	    * (-2.8243487670469080 + lnx)
	    * (-2.3798494322701120 + lnx)
	    * (-1.9143674728689960 + lnx)
	    * (-1.3814529102920370 + lnx)
	    * (-0.7294312810261694 + lnx)
	    * ( 0.1299079285269565 + lnx)
	    * ( 1.3873333251885240 + lnx)
	    * ( 3.5857258865210760 + lnx)
	    * ( 9.3214237073814600 + lnx);
	const double c10 = -2.75573192239859e-7
	    * (-2.9540329644556910 + lnx)
	    * (-2.5491366926991850 + lnx)
	    * (-2.1348279229279880 + lnx)
	    * (-1.6741881076349450 + lnx)
	    * (-1.1325949616098420 + lnx)
	    * (-0.4590034650618494 + lnx)
	    * ( 0.4399352987435699 + lnx)
	    * ( 1.7702236517651670 + lnx)
	    * ( 4.1231539047474080 + lnx)
	    * ( 10.342627908148680 + lnx);

	term1 = a*(c1+a*(c2+a*(c3+a*(c4+a*(c5+a*(c6+a*(c7+a*(c8+a*(c9+a*c10)))))))));
    }

    {
	/* Evaluate the sum */
	double t = 1.0;
	sum = 1.0;

	for (n = 1; n < nmax; n++)
	{
	    t *= -x/(n+1.0);
	    sum += (a+1.0)/(a+n+1.0)*t;
	    if (fabs(t/sum) < DOUBLE_EPS)
		break;
	}
    }

    term2 = (1.0 - term1) * a/(a + 1.0) * x * sum;

    if (n == nmax)
	warning(_("maximum number of iterations reached in gamma_inc_F_CF"));

    return term1 + term2;
}

/* Adapted from specfun/gamma_inc.c in GSL sources. Note that base R
 * function 'gammafn' and 'pgamma' are used for postive values of
 * 'a'. */
double gamma_inc(double a, double x)
{
#ifdef IEEE_754
    if (ISNAN(x) || ISNAN(a))
	return a + x;
#endif

    if (x < 0.0)
	return(R_NaN);
    else if (x == 0.0)
	return gammafn(a);
    else if (a == 0.0)
	return expint_E1(x, 0);
    else if (a > 0.0)
	return gammafn(a) * pgamma(x, a, 1, 0, 0);
    else if (x > 0.25)
    {
	/* continued fraction seems to fail for x too small; otherwise
	   it is ok, independent of the value of |x/a|, because of the
	   non-oscillation in the expansion, i.e. the CF is
	   un-conditionally convergent for a < 0 and x > 0
	*/
	return exp((a - 1) * log(x) - x) * gamma_inc_F_CF(a, x);
    }
    else if (fabs(a) < 0.5)
    {
	return gammafn(a) * gamma_inc_Q_series(a, x);
    }
    else
    {
	/* a = fa + da; da >= 0 */
	const double fa = floor(a);
	const double da = a - fa;

	double gax  = (da > 0.0 ? gammafn(da) * pgamma(x, da, 1, 0, 0)
		                : expint_E1(x, 0));
	double alpha = da;

	/* Gamma(alpha-1,x) = 1/(alpha-1) (Gamma(a,x) - x^(alpha-1) e^-x) */
	do
	{
	    const double shift = exp(-x + (alpha - 1.0) * log(x));
	    gax = (gax - shift)/(alpha - 1.0);
	    alpha -= 1.0;
	} while (alpha > a);

	return gax;
  }
}


/* R interface. Inspired from R sources and dpq.c in actuar */
#define mod_iterate1(n1, n2, i1, i2)            \
        for (i = i1 = i2 = 0; i < n;            \
             i1 = (++i1 == n1) ? 0 : i1,        \
             i2 = (++i2 == n2) ? 0 : i2,        \
             ++i)

SEXP expint_do_gammainc(SEXP args)
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
	    y[i] = gamma_inc(ai, xi);
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
