#include <stdio.h>
#include <stdlib.h>
#include "bmp8.h"

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
    const char *input = "../image/barbara_gray.bmp";

    // Afficher les infos de base
    t_bmp8 *img = bmp8_loadImage(input);
    if (!img) {
        printf("Erreur : impossible de charger l'image d'origine.\n");
        return 1;
    }
    bmp8_printInfo(img);

    // Appliquer le négatif
    bmp8_negative(img);
    bmp8_saveImage("../Image/barbara_gray_negative.bmp", img);

    // Appliquer la luminosité +50
    bmp8_brightness(img, 50);
    bmp8_saveImage("../Image/barbara_gray_brightness.bmp", img);

    // Appliquer le seuillage à 128
    bmp8_threshold(img, 128);
    bmp8_saveImage("../Image/barbara_gray_threshold.bmp", img);

    // Appliquer les filtres de convolution
    img = bmp8_loadImage(input);
    float **k;

    k = toFloatPtr(kernel_box_blur);
    bmp8_applyFilter(img, k, 3);
    bmp8_saveImage("../Image/barbara_gray_boxblur.bmp", img);
    bmp8_free(img);

    freeKernel(k);

    k = toFloatPtr(kernel_gaussian_blur);
    bmp8_applyFilter(img, k, 3);
    bmp8_saveImage("../Image/barbara_gray_gaussian.bmp", img);
    bmp8_free(img);
    freeKernel(k);


    k = toFloatPtr(kernel_outline);
    bmp8_applyFilter(img, k, 3);
    bmp8_saveImage("../Image/barbara_gray_outline.bmp", img);
    bmp8_free(img);
    freeKernel(k);


    k = toFloatPtr(kernel_emboss);
    bmp8_applyFilter(img, k, 3);
    bmp8_saveImage("../Image/barbara_gray_emboss.bmp", img);
    bmp8_free(img);
    freeKernel(k);

    k = toFloatPtr(kernel_sharpen);
    bmp8_applyFilter(img, k, 3);
    bmp8_saveImage("../Image/barbara_gray_sharpen.bmp", img);
    bmp8_free(img);
    freeKernel(k);

    printf("\n Tous les filtres ont été appliqués et enregistrés.\n");

    return 0;
}

