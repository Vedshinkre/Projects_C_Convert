#include "file_io.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

int image_read(image_t *img, FILE *fin) {
  int max_value; // to check if the number is 255 or not
int width = 0;
int height = 0;
char array[3]; // to store the first three characters of a given file

// Read the first two characters from the file and store them in 'array'
fscanf(fin, "%2s", array);

// Check if the first two characters are "P3"
if (strcmp("P3", array) != 0) {
    return -1; // Return -1 to indicate an error
}

// Read the width, height, and maximum value from the file
fscanf(fin, " %d %d %d", &width, &height, &max_value);

// Check if the width, height, or maximum value is invalid
if (width < 1 || height < 1 || max_value != 255) {
    return -1; // Return -1 to indicate an error
}

// Allocate memory for the image data based on the width and height
pixel_t* boom = malloc(width * height * sizeof(pixel_t));

// Check if memory allocation failed
if (boom == NULL) {
    return -1;
}

// Read the RGB values for each pixel in the image
for (int a = 0; a < width * height; ++a) {
    fscanf(fin, "%d %d %d", &boom[a].r, &boom[a].g, &boom[a].b);

    // Check if any RGB value is invalid
    if (boom[a].r < 0 || boom[a].r > 255 || boom[a].g < 0 || boom[a].g > 255 || boom[a].b < 0 || boom[a].b > 255) {
        free(boom);
        return -1; 
    }
}

// Update the image structure with the width, height, and image data
img->w = width;
img->h = height;
img->img = boom;

return 0;
   }
  

void image_write(const image_t *img, FILE *fout) {
    // NOT_IMPLEMENTED;
   // UNUSED(img);
    // UNUSED(fout);
 fprintf(fout,"P3 %d %d 255\n", img->w,img->h);
   for(int a = 0;a< img -> w * img -> h ; ++a){
     fprintf(fout,"%d %d %d\n",img -> img[a].r, img -> img[a].g,img ->img[a].b) ;
     
       }


}

void image_free(image_t *img) {
    if (img->img != NULL) {
        free(img->img);
    }
    img->w = img->h = 0;
    img->img = NULL;
}
