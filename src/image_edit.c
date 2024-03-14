#include "image_edit.h"

#include <stdlib.h>

#include "structures.h"
#include "util.h"

void rotate_counterclockwise(image_t *img) {
  int n=img->w;// width 
  int m=img->h; // height
  
  pixel_t* maal = malloc(n*m*sizeof(pixel_t));

    //y*w+x
    for (int r=0;r < m ;++r){
        for (int c=0;c<n;++c){
         maal[(n - (c + 1)) * m + r] = img->img[r * n + c];

        }
    }
free(img->img);
img->w=m;
img->h=n;
img->img=maal;
}

void rotate_clockwise(image_t *img) {
 rotate_counterclockwise(img);
 rotate_counterclockwise(img);
 rotate_counterclockwise(img);
}

void mirror_horizontal(image_t *img) {
    // NOT_IMPLEMENTED;
    // UNUSED(img);
  int n=img->w;// width 
  int m=img->h; // height
  pixel_t* baal = malloc(n*m*sizeof(pixel_t));
  
    //y*w+x
    for (int r=0;r < m ;++r){
        for (int c=0;c<n;++c){
          baal[r*n+c] = img->img[((r))*n+(n-(c+1))];
        } 
    }
free(img->img);
img->w=n;
img->h=m;
img->img=baal;
}







void mirror_vertical(image_t *img) {
  rotate_counterclockwise(img);
  rotate_counterclockwise(img);
 mirror_horizontal(img);
}

void resize(image_t *img, int new_width, int new_height) {
   int n = img->w; // width
   int m = img->h; // height
   pixel_t* laal = malloc(new_width * new_height * sizeof(pixel_t));
      for (int r = 0; r < new_height; ++r) {
         for (int c = 0; c < new_width; ++c) {
            laal[r * new_width + c].r = 0;   // Set red component to 0
            laal[r * new_width + c].g = 0;   // Set green component to 0
            laal[r * new_width + c].b = 0;   // Set blue component to 0 
         }
      }


   // Resize when new width and height are smaller
   if (n >= new_width && m > new_height) {
      for (int r = 0; r < new_height; ++r) {
         for (int c = 0; c < new_width; ++c) {
            laal[r * new_width + c] = img->img[r * n + c];
         }
      }
   }
   // Resize when new width and height are larger
   if (n <= new_width && m < new_height) {
      for (int r = 0; r < m; ++r) {
         for (int c = 0; c < n; ++c) {
            laal[r * new_width + c] = img->img[r * n + c];
         }
      }
     
     
   }
   // Resize when  width and height is equal
    if ((n==new_width) && (m ==new_height)) {
      for (int r = 0; r < m; ++r) {
         for (int c = 0; c < n; ++c) {
            laal[r * new_width + c] = img->img[r * n + c];
         }
      }

   }
   //Resize when width is reduced but height is increased
     if ((n>new_width) && (m <=new_height)) {
      for (int r = 0; r < m; ++r) {
         for (int c = 0; c < new_width; ++c) {
            laal[r * new_width + c] = img->img[r * n + c];
         }
      }

   }
   
   //Resize when width is increased but height is reduced
      if ((n<new_width) && (m >=new_height)) {
      for (int r = 0; r < new_height; ++r) {
         for (int c = 0; c < n; ++c) {
            laal[r * new_width + c] = img->img[r * n + c];
         }
      }

   }

   free(img->img);
   img->w = new_width;
   img->h = new_height;
   img->img = laal;
}