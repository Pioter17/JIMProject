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
double
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
	
	return 4*dfi(i-1, x) + 2*x*d2fi(i-1, x) - 2*(i-1)*d2fi(i-2, x);
}

/* Trzecia pochodna fi */
double
d3fi(int i, double x)
{
	if (i == 0)
		return 0;
	if (i == 1)
		return 0;
	if (i == 2)
		return 0;
	if (i == 3)
		return 48;

	return 6*d2fi(i-1, x) + 2*x*d3fi(i-1, x) - 2*(i-1)*d3fi(i-2, x);
}

/* Pomocnicza f. do rysowania bazy */

void
make_spl(points_t * pts, spline_t * spl)
{

	matrix_t       *eqs= NULL;
	double         *x = pts->x;
	double         *y = pts->y;
	int		i, j, k;
	int		nb = pts->n - 3 > 10 ? 10 : pts->n - 3;
  	char *nbEnv= getenv( "APPROX_BASE_SIZE" );

	if( nbEnv != NULL && atoi( nbEnv ) > 0 )
		nb = atoi( nbEnv );

	eqs = make_matrix(nb, nb + 1);


	for (j = 0; j < nb; j++) {
		for (i = 0; i < nb; i++)
			for (k = 0; k < pts->n; k++)
				add_to_entry_matrix(eqs, j, i, fi(i, x[k]) * fi(j, x[k]));

		for (k = 0; k < pts->n; k++)
			add_to_entry_matrix(eqs, j, nb, y[k] * fi(j, x[k]));
	}


	if (piv_ge_solver(eqs)) {
		spl->n = 0;
		free_matrix(eqs);
		return;
	}

	if (alloc_spl(spl, nb) == 0) {
		for (i = 0; i < spl->n; i++) {
			double xx = spl->x[i] = x[i];
			spl->f[i] = 0;
			spl->f1[i] = 0;
			spl->f2[i] = 0;
			spl->f3[i] = 0;
			for (k = 0; k < nb; k++) {
				double ck = get_entry_matrix(eqs, k, nb);
				spl->f[i]  += ck * fi  (k, xx);
				spl->f1[i] += ck * dfi (k, xx);
				spl->f2[i] += ck * d2fi(k, xx);
				spl->f3[i] += ck * d3fi(k, xx);
			}
		}	
	}
	free_matrix(eqs);
}
