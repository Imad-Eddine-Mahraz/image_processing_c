#include <stdio.h>
#include <stdlib.h>
#include "t_bmp24.h"

// Noyaux 3x3 statiques
float kernel_box_blur[3][3] = {
    {1.0/9, 1.0/9, 1.0/9},
    {1.0/9, 1.0/9, 1.0/9},
    {1.0/9, 1.0/9, 1.0/9}
};

float kernel_gaussian_blur[3][3] = {
    {1.0/16, 2.0/16, 1.0/16},
    {2.0/16, 4.0/16, 2.0/16},
    {1.0/16, 2.0/16, 1.0/16}
};

float kernel_outline[3][3] = {
    {-1, -1, -1},
    {-1,  8, -1},
    {-1, -1, -1}
};

float kernel_emboss[3][3] = {
    {-2, -1, 0},
    {-1,  1, 1},
    { 0,  1, 2}
};

float kernel_sharpen[3][3] = {
    { 0, -1,  0},
    {-1,  5, -1},
    { 0, -1,  0}
};

float **toFloatPtr(float kernel[3][3]) {
    float **result = malloc(3 * sizeof(float *));
    for (int i = 0; i < 3; i++) {
        result[i] = malloc(3 * sizeof(float));
        for (int j = 0; j < 3; j++) {
            result[i][j] = kernel[i][j];
        }
    }
    return result;
}

void freeKernel(float **kernel) {
    for (int i = 0; i < 3; i++) {
        free(kernel[i]);
    }
    free(kernel);
}

int main() {
    const char *input = "../image/flowers_color.bmp";

    // Charger l'image couleur
    t_bmp24 *img = bmp24_loadImage(input);
    if (!img) {
        printf("Erreur :impossible de charger l'image couleur.\n");
        return 1;
    }

    // Afficher les informations
    printf("Image chargée : %dx%d, profondeur %d bits\n", img->width, img->height, img->colorDepth);

    // Appliquer la luminosité +50

    bmp24_brightness(img, 50);
    bmp24_saveImage(img, "../Image/flowers_brightness.bmp");

    // Appliquer le négatif
    img = bmp24_loadImage(input);
    bmp24_negative(img);
    bmp24_saveImage(img, "../Image/flowers_negative.bmp");

    // Appliquer la conversion en niveaux de gris
    img = bmp24_loadImage(input);
    bmp24_grayscale(img);
    bmp24_saveImage(img, "../Image/flowers_grayscale.bmp");

    // Appliquer les filtres de convolution (sans recharger, enchaînés)
    float **k;

    k = toFloatPtr(kernel_box_blur);
    img = bmp24_loadImage(input);
    bmp24_applyFilter(img, k, 3);
    bmp24_saveImage(img, "../Image/flowers_boxblur.bmp");
    freeKernel(k);

    k = toFloatPtr(kernel_gaussian_blur);
    img = bmp24_loadImage(input);
    bmp24_applyFilter(img, k, 3);
    bmp24_saveImage(img, "../Image/flowers_gaussian.bmp");
    freeKernel(k);

    k = toFloatPtr(kernel_outline);
    img = bmp24_loadImage(input);
    bmp24_applyFilter(img, k, 3);
    bmp24_saveImage(img, "../Image/flowers_outline.bmp");
    freeKernel(k);

    k = toFloatPtr(kernel_emboss);
    img = bmp24_loadImage(input);
    bmp24_applyFilter(img, k, 3);
    bmp24_saveImage(img, "../Image/flowers_emboss.bmp");
    freeKernel(k);

    k = toFloatPtr(kernel_sharpen);
    img = bmp24_loadImage(input);
    bmp24_applyFilter(img, k, 3);
    bmp24_saveImage(img, "../Image/flowers_sharpen.bmp");
    freeKernel(k);

    bmp24_free(img);
    printf("\nTous les filtres ont été appliqués et enregistrés.\n");

    return 0;
}
