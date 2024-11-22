#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"
 
 
#define TRSH 2.0
#define ITER 1024
 
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
 
int main(int argc, char *argv[])
{
    struct ppm_image im;
    ppm_image_init( &im , SIZEX , SIZEY ); // Initialise l'mage pour afficher l'ensemble
 
    int i,j;
    double colref = 255.0/log(ITER); // Initialise la varibale colref qui permettra de gérér l'intensité de la couleur
 
    for (i = 0; i < SIZEX; ++i) { // Debut de la boucle de calcul
        for (j = 0; j < SIZEY; ++j) {
 
            unsigned long int iter = 0;
 
            double complex c =  cx(i) + cy(j) * I; // Initialisation des nombres complexes. cx permet de normaliser i (qui varie de 0 a 1500)
            double complex z = 0; //Idem pour cy. z commence a 0
 
            while(iter < ITER)
            {
                double mod = cabs(z);
 
                if( TRSH < mod )
                {
                    break;
                }
 
                z = z*z + c; // Calcul du point (z^2 + c)
 
                iter++;
            }
 
            int grey = colref*log(iter); 
            ppm_image_setpixel(&im, i,j, grey, grey , grey );
        }
    }
 
    ppm_image_dump( &im, "m.ppm");
    ppm_image_release( &im );
 
 
    return 0;
}
