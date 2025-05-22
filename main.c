#include <stdio.h>
#include <stdlib.h>
#include "bmp8.h"

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

int main() {
    t_bmp8 *img = bmp8_loadImage("../image/barbara_gray.bmp");
    if (!img) return 1;

    bmp8_printInfo(img);

    // 1. Négatif
    t_bmp8 *neg = bmp8_loadImage("../image/barbara_gray.bmp");
    bmp8_negative(neg);
    bmp8_saveImage("barbara_gray_negative.bmp", neg);
    bmp8_free(neg);

    // 2. Luminosité +50
    t_bmp8 *bright = bmp8_loadImage("../image/barbara_gray.bmp");
    bmp8_brightness(bright, 50);
    bmp8_saveImage("barbara_gray_brightness.bmp", bright);
    bmp8_free(bright);

    // 3. Seuillage (threshold = 128)
    t_bmp8 *thresh = bmp8_loadImage("../image/barbara_gray.bmp");
    bmp8_threshold(thresh, 128);
    bmp8_saveImage("barbara_gray_threshold.bmp", thresh);
    bmp8_free(thresh);

    // 4. Flou (box blur)
    t_bmp8 *blur = bmp8_loadImage("../image/barbara_gray.bmp");
    bmp8_applyFilter(blur, (float **)kernel_box_blur, 3);
    bmp8_saveImage("barbara_gray_blur.bmp", blur);
    bmp8_free(blur);

    // 5. Flou gaussien
    t_bmp8 *gauss = bmp8_loadImage("../image/barbara_gray.bmp");
    bmp8_applyFilter(gauss, (float **)kernel_gaussian_blur, 3);
    bmp8_saveImage("barbara_gray_gaussian.bmp", gauss);
    bmp8_free(gauss);

    // 6. Contours
    t_bmp8 *contour = bmp8_loadImage("../image/barbara_gray.bmp");
    bmp8_applyFilter(contour, (float **)kernel_outline, 3);
    bmp8_saveImage("barbara_gray_outline.bmp", contour);
    bmp8_free(contour);

    // 7. Relief
    t_bmp8 *emboss = bmp8_loadImage("../image/barbara_gray.bmp");
    bmp8_applyFilter(emboss, (float **)kernel_emboss, 3);
    bmp8_saveImage("barbara_gray_emboss.bmp", emboss);
    bmp8_free(emboss);

    // 8. Netteté
    t_bmp8 *sharp = bmp8_loadImage("../image/barbara_gray.bmp");
    bmp8_applyFilter(sharp, (float **)kernel_sharpen, 3);
    bmp8_saveImage("barbara_gray_sharpen.bmp", sharp);
    bmp8_free(sharp);

    // Libération finale
    bmp8_free(img);
    return 0;
}
