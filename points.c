#include "points.h"
#include <stdlib.h>

static int
realloc_pts_failed (points_t * pts, int size)
{
	double *tmpx, *tmpy;
	tmpx = realloc(pts->x, size * sizeof *pts->x);
	tmpy = realloc(pts->y, size * sizeof *pts->y);
  	if (tmpx == NULL || tmpy == NULL)
	{
		free(tmpx);
		free(tmpy);
		return 1;
	}
	pts->x = tmpx;
	pts->y = tmpy;
	return 0;
	
	//return pts->x == NULL || pts->y == NULL;
}

int
read_pts_failed (FILE * inf, points_t * pts)
{
  int size, a, b;
  double x, y;

  if (pts->n == 0) {
    pts->x = malloc (100 * sizeof *pts->x);
    if (pts->x == NULL)
      return 1;
    pts->y = malloc (100 * sizeof *pts->y);
    if (pts->y == NULL) {
      free (pts->x);
      return 1;
    }
    size = 100;
  }
  else
    size = pts->n;

  while (fscanf (inf, "%lf %lf", &x, &y) == 2) {
    pts->x[pts->n] = x;
    pts->y[pts->n] = y;
    pts->n++;
    if (!feof (inf) && pts->n == size) {
      if (a = realloc_pts_failed (pts, 2 * size)){
        return 1;
    	}
      else
        size *= 2;
    }
  }

  if (pts->n != size)
    if (b = realloc_pts_failed (pts, pts->n)){
      return 1;
    }

  return 0;
}
