#include "makespl.h"
#include "piv_ge_solver.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

/* UWAGA: liczbę używanych f. bazowych można ustawić przez wartość
          zmiennej środowiskowej APPROX_BASE_SIZE
*/

// i -> numer wielomianu
// x -> parametr
fi(int i, double x)
{
	if( i == 0 )
		return 1;
	if( i == 1 )
		return 2*x;
	
	return 2*x*fi(i-1, x) - 2*(i-1)*fi(i-2, x);	
}

/* Pierwsza pochodna fi */
double
dfi(int i, double x)
{
	if (i == 0)
		return 0;
	if (i == 1)
		return 2;
	return 2*fi(i-1, x) + 2*x*dfi(i-1, x) - 2*(i-1)*dfi(i-2, x);	
}

/* Druga pochodna fi */
double
d2fi(int i, double x)
{
	if( i == 0 )
		return 0;
	if( i == 1 )
		return 0;
	if( i == 2 )
		return 8;
	
	return 4*dfi(i-1, x) + 2*x*d2fi(i-1, x) - 2*n*d2fi(i-2, x);
}

/* Trzecia pochodna fi */
double
d3fi(double a, double b, int n, int i, double x)
{
	double		h = (b - a) / (n - 1);
	double		h3 = h * h * h;
	int		hi         [5] = {i - 2, i - 1, i, i + 1, i + 2};
	double		hx      [5];
	int		j;

	for (j = 0; j < 5; j++)
		hx[j] = a + h * hi[j];

	if ((x < hx[0]) || (x > hx[4]))
		return 0;
	else if (x >= hx[0] && x <= hx[1])
		return 6 / h3;
	else if (x > hx[1] && x <= hx[2])
		return -18 / h3;
	else if (x > hx[2] && x <= hx[3])
		return 18 / h3;
	else			/* if (x > hx[3]) && (x <= hx[4]) */
		return -6 / h3;
}

/* Pomocnicza f. do rysowania bazy */
double
xfi(double a, double b, int n, int i, FILE *out)
{
	double		h = (b - a) / (n - 1);
	double		h3 = h * h * h;
	int		hi         [5] = {i - 2, i - 1, i, i + 1, i + 2};
	double		hx      [5];
	int		j;

	for (j = 0; j < 5; j++)
		hx[j] = a + h * hi[j];

	fprintf( out, "# nb=%d, i=%d: hi=[", n, i );
	for( j= 0; j < 5; j++ )
		fprintf( out, " %d", hi[j] );
	fprintf( out, "] hx=[" );
	for( j= 0; j < 5; j++ )
		fprintf( out, " %g", hx[j] );
	fprintf( out, "]\n" );
}

void
make_spl(points_t * pts, spline_t * spl)
{

	matrix_t       *eqs= NULL;
	double         *x = pts->x;
	double         *y = pts->y;
	double		a = x[0];
	double		b = x[pts->n - 1];
	int		i, j, k;
	int		nb = pts->n - 3 > 10 ? 10 : pts->n - 3;
  char *nbEnv= getenv( "APPROX_BASE_SIZE" );

	if( nbEnv != NULL && atoi( nbEnv ) > 0 )
		nb = atoi( nbEnv );

	eqs = make_matrix(nb, nb + 1);

#ifdef DEBUG
#define TESTBASE 500
	{
		FILE           *tst = fopen("debug_base_plot.txt", "w");
		double		dx = (b - a) / (TESTBASE - 1);
		for( j= 0; j < nb; j++ )
			xfi( a, b, nb, j, tst );
		for (i = 0; i < TESTBASE; i++) {
			fprintf(tst, "%g", a + i * dx);
			for (j = 0; j < nb; j++) {
				fprintf(tst, " %g", fi  (a, b, nb, j, a + i * dx));
				fprintf(tst, " %g", dfi (a, b, nb, j, a + i * dx));
				fprintf(tst, " %g", d2fi(a, b, nb, j, a + i * dx));
				fprintf(tst, " %g", d3fi(a, b, nb, j, a + i * dx));
			}
			fprintf(tst, "\n");
		}
		fclose(tst);
	}
#endif

	for (j = 0; j < nb; j++) {
		for (i = 0; i < nb; i++)
			for (k = 0; k < pts->n; k++)
				add_to_entry_matrix(eqs, j, i, fi(a, b, nb, i, x[k]) * fi(a, b, nb, j, x[k]));

		for (k = 0; k < pts->n; k++)
			add_to_entry_matrix(eqs, j, nb, y[k] * fi(a, b, nb, j, x[k]));
	}

#ifdef DEBUG
	write_matrix(eqs, stdout);
#endif

	if (piv_ge_solver(eqs)) {
		spl->n = 0;
		return;
	}
#ifdef DEBUG
	write_matrix(eqs, stdout);
#endif

	if (alloc_spl(spl, nb) == 0) {
		for (i = 0; i < spl->n; i++) {
			double xx = spl->x[i] = a + i*(b-a)/(spl->n-1);
			xx+= 10.0*DBL_EPSILON;  // zabezpieczenie przed ulokowaniem punktu w poprzednim przedziale
			spl->f[i] = 0;
			spl->f1[i] = 0;
			spl->f2[i] = 0;
			spl->f3[i] = 0;
			for (k = 0; k < nb; k++) {
				double		ck = get_entry_matrix(eqs, k, nb);
				spl->f[i]  += ck * fi  (a, b, nb, k, xx);
				spl->f1[i] += ck * dfi (a, b, nb, k, xx);
				spl->f2[i] += ck * d2fi(a, b, nb, k, xx);
				spl->f3[i] += ck * d3fi(a, b, nb, k, xx);
			}
		}
	}

#ifdef DEBUG
	{
		FILE           *tst = fopen("debug_spline_plot.txt", "w");
		double		dx = (b - a) / (TESTBASE - 1);
		for (i = 0; i < TESTBASE; i++) {
			double yi= 0;
			double dyi= 0;
			double d2yi= 0;
			double d3yi= 0;
			double xi= a + i * dx;
			for( k= 0; k < nb; k++ ) {
							yi += get_entry_matrix(eqs, k, nb) * fi(a, b, nb, k, xi);
							dyi += get_entry_matrix(eqs, k, nb) * dfi(a, b, nb, k, xi);
							d2yi += get_entry_matrix(eqs, k, nb) * d2fi(a, b, nb, k, xi);
							d3yi += get_entry_matrix(eqs, k, nb) * d3fi(a, b, nb, k, xi);
			}
			fprintf(tst, "%g %g %g %g %g\n", xi, yi, dyi, d2yi, d3yi );
		}
		fclose(tst);
	}
#endif

}
