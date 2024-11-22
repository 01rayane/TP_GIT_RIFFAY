#ifndef PPM_H
#define PPM_H

struct ppm_pixel { // Structure qui permet de gérer la couleur d'un pixel (Sous forme RGB avec R,G,B qui varient de 0 a 255)
  unsigned char r;
  unsigned char g;
  unsigned char b;
};

static inline void ppm_setpixel(struct ppm_pixel *px, unsigned char r,
                                unsigned char g, unsigned char b) { // Fonction simple qui permet de changer la couleur d'un pixel (avec en arguments le code rgb)
  px->r = r;
  px->g = g;
  px->b = b;
}

struct ppm_image { //Structure permettant de gerener une image garce a sa longueur, sa largeur et un tableau dynamique ou chaque case represente un pixel
  unsigned int width;
  unsigned int height;
  struct ppm_pixel *px;
};

int ppm_image_init(struct ppm_image *im, int w, int h); // Initialise une image
int ppm_image_release(struct ppm_image *im); // Libère l'image (l'espace alloué par les pixels)

static inline void ppm_image_setpixel(struct ppm_image *im, int x, int y,
                                      unsigned char r, unsigned char g,
                                      unsigned char b) { // Permet de changer la couleur d'un pixel dans une image
  struct ppm_pixel *px = im->px + im->width * y + x;
  ppm_setpixel(px, r, g, b);
}

int ppm_image_dump(struct ppm_image *im, char *path); // Permet de charger l'image dans un fichier (selon le path/chemin)

#endif /* PPM_H */

