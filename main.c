#include <stdio.h>
#include "bmp8.h"

int main() {
    // Charger l'image depuis le fichier
    t_bmp8 *img = bmp8_loadImage("C:\\Users\\jules\\CLionProjects\\image_processing_c\\barbara_gray.bmp");
    if (img != NULL) {
        bmp8_printInfo(img);  // Affiche les informations sur l'image

        // Appliquer l'inversion des couleurs (négatif)
        bmp8_negative(img);

        // Affichage d'un seul pixel avant et après inversion
        int pixel_index = 0;  // Index du pixel à afficher (par exemple le premier pixel)
        unsigned char original_pixel = img->data[pixel_index];
        unsigned char inverted_pixel = 255 - original_pixel;

        // Affichage de la valeur avant et après inversion pour un pixel
        printf("Pixel %d avant : %d, apres : %d\n", pixel_index, original_pixel, inverted_pixel);

        // Libérer la mémoire de l'image
        bmp8_free(img);
    } else {
        printf("Échec du chargement de l'image.\n");
    }

    return 0;
}
