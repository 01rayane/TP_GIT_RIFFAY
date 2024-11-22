#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"
#include <omp.h>
 
 
#define TRSH 2.0
#define ITER 1024 //Correction, ce n'est pas 1024ull mais bien 1024
 
#define SIZEX 1500
#define SIZEY 1500
 
double cx( int x ) //Normalise un vexteur (x)
{
    /* -2 ---> 1 */
    static const double qx = 3.0 / (double)SIZEX;
    return -2.0 +  x * qx;
}
 
double cy( int y ) // Normalise un vecteur (y)
{
    /* -1 ---> 1 */
    static const double qy = 2.0 / (double)SIZEY;
    return -1.0 + y * qy;
}
 

struct col
{
    int r;
    int g;
    int b;
};
 
struct col getcol( int val , int max )
{
    double q = (double)val/(double)max;
 
    struct col c = { 0, 0, 0 };
 
    if( q < 0.25 )
    {
            c.r = ( q * 4.0 ) * 255.0;
            c.b = 255;
        }
    else if( q < 0.5 )
    {
            c.b = 255;
            c.g = 255;
            c.r = (q-0.25)*4.0*255.0;
 
        }
    else if( q < 0.75 )
    {
            c.b = 255;
            c.r = 255;
            c.g = 255.0 - (q-0.5)*4.0*255.0;
        }
    else
    {
            c.b = 255-(q-0.75)*4.0*255.0;
            c.g = 0;
            c.r = 255;
        }
 
    return c;
}


int main(int argc, char *argv[]) {
  struct ppm_image im;
  ppm_image_init(&im, SIZEX, SIZEY); // Initialise l'mage pour afficher l'ensemble

  int i, j;
  int colref = log(ITER); // Initialise la varibale colref qui permettra de gérér l'intensité de la couleur

	#pragma omp parallel for //Parallélise automatiquement les boucles for
	for (i = 0; i < SIZEX; ++i) {// Debut de la boucle de calcul
        for (j = 0; j < SIZEY; ++j) {
 
            unsigned long int iter = 0;
 
            double complex c =  cx(i) + cy(j) * I; // Initialisation des nombres complexes. cx permet de normaliser i afin qu'il reste dans l'ensemble (qui varie de 0 a 1500)
            double complex z = 0; //Idem pour cy. z commence a 0
 
            while(iter < ITER) // Lorsque l'on depassera le nombre d'itérations, on calcule la couleur du pixel.
            {
                double mod = cabs(z);
                if( TRSH < mod ) //Correction : ce n'est pas TRSH -lt ... (on n'est pas en bash)

                {
                    break;
                }
 
                z = z*z + c; // Calcul du point (z^2 + c)
 
                iter++;
            }
 
            struct col cc = getcol( log(iter), colref );
            ppm_image_setpixel(&im, i,j, cc.r, cc.g , cc.b );
        }
    }

  ppm_image_dump(&im, "m.ppm"); //Correction, ce n'est pas "&amp ; im" mais simplement &im, le ponteur vers l'image
  ppm_image_release(&im);

  return 0;
}

