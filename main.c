#include <stdio.h>
#include "bmp8.h"

int main() {
    t_bmp8 *img =bmp8_loadImage("C:\\Users\\mahra\\OneDrive\\Bureau\\ecole\\image_processing_c\\barbara_gray.bmp");
    if (img != NULL) {
        bmp8_printInfo(img);  // Tu pourras écrire cette fonction aussi
        bmp8_free(img);       // N'oublie pas de libérer la mémoire
    } else {
        printf("Échec du chargement de l'image.\n");
    }
    return 0;
}