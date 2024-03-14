#include "flood_fill.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "util.h"

void flood(image_t *img, int x, int y, pixel_t *target_color) {
    int n = img->w; // width
    int m = img->h; // height

    // Check if the starting position (x, y) is within the image bounds
    if (x < 0 || y < 0 || x >= n || y >= m) {
        return;
    }

    pixel_t start_pixel = img->img[y * n + x];

    // Base case: if the current pixel is already the target color or different from the start pixel, return
    if (start_pixel.r == target_color->r && start_pixel.g == target_color->g && start_pixel.b == target_color->b) {
        return;
    }

    // Set the color of the current pixel to the target color
    img->img[y * n + x] = *target_color;

    // Recursive calls for the neighboring pixels (up, down, left, right)

    // Up
    if (y - 1 >= 0 && img->img[(y - 1) * n + x].r == start_pixel.r &&
        img->img[(y - 1) * n + x].g == start_pixel.g && img->img[(y - 1) * n + x].b == start_pixel.b) {
        flood(img, x, y - 1, target_color);
    }

    // Down
    if (y + 1 < m && img->img[(y + 1) * n + x].r == start_pixel.r &&
        img->img[(y + 1) * n + x].g == start_pixel.g && img->img[(y + 1) * n + x].b == start_pixel.b) {
        flood(img, x, y + 1, target_color);
    }

    // Left
    if (x - 1 >= 0 && img->img[y * n + (x - 1)].r == start_pixel.r &&
        img->img[y * n + (x - 1)].g == start_pixel.g && img->img[y * n + (x - 1)].b == start_pixel.b) {
        flood(img, x - 1, y, target_color);
    }

    // Right
    if (x + 1 < n && img->img[y * n + (x + 1)].r == start_pixel.r &&
        img->img[y * n + (x + 1)].g == start_pixel.g && img->img[y * n + (x + 1)].b == start_pixel.b) {
        flood(img, x + 1, y, target_color);
    }
}