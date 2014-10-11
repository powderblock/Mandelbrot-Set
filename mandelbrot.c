/*By Blade Nelson
Code based on Eric R. Weeks' mandelbrot render(http://www.physics.emory.edu/faculty/weeks//software/mandel.c), originally released under the following license:
www.physics.emory.edu*/

/**  mandel.c   by Eric R. Weeks   written 9-28-96
 **  weeks@physics.emory.edu
 **  http://www.physics.emory.edu/~weeks/
 **  
 **  This program is public domain, but this header must be left intact
 **  and unchanged.
 **  
 **  to compile:  cc -o mand mandel.c
 ** 
 **/

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Width and height of our render
#define width 512
#define height 512

// How many total pixels the image is.
#define imageSize (width * height)

// Make a struct to hold a pixel. (Color information).
typedef struct{
    char r, g, b;
} pixel;

// Array to hold information about all pixels in the image.
pixel imageArray[imageSize];

// Main function:
int main(){
    double zx, tmp, zy, cx, cy;
    double magnify = 1.0; // How much zoom on the render.
    int i, hx, hy;
    int max_iterations = 64; // How many times we want to run over the set. More = finer sampling.
    printf("P6\n"); // Define what type of BM we are going to do.
    printf("%d %d\n255\n", width, height); // Give information about height and color depth.
    for(hy = 0; hy < height; ++hy){
        for(hx = 0; hx < width; ++hx){
			 // Starting imaginary number:
			 cx = (((float)hx)/((float)width)-0.5)/magnify*3.0-0.7;
			 cy = (((float)hy)/((float)height)-0.5)/magnify*3.0;
			 
			 zx = cx;
			 zy = cy;
			 for(i = 0; i < max_iterations; ++i){
				// z^2 + c
				tmp = zx * zx - zy * zy + cx;
				zy = (2.0 * zx)*zy+cy;
				zx = tmp;
				// if it's diviriging, break out of the loop.
				// if r > 2, it's guarnteed to diverge 
				if(zx * zx + zy * zy > 4.0){
					break;
				}
			 }
			// Control the color based on where and how long it takes to diverge
			 if(i < max_iterations){
				imageArray [hx + hy*width].b = i * 4;
			 }
			 
			 // If it's within the set, make it black
			 else{
				imageArray[hx + hy*width].r = 0;
			 }
		}
	}
	// Once we have all the values, fputc them!
	for(i = 0; i < imageSize; ++i){
		fputc (imageArray[i].r,stdout);
		fputc(imageArray[i].g,stdout);
		fputc(imageArray[i].b,stdout);
	}
}
