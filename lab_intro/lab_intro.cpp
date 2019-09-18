/**
 * @file lab_intro.cpp
 * Implementations of image manipulation functions.
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "lab_intro.h"

using cs225::HSLAPixel;
using cs225::PNG;

/**
 * Returns an image that has been transformed to grayscale.
 *
 * The saturation of every pixel is set to 0, removing any color.
 *
 * @return The grayscale image.
 */
PNG grayscale(PNG image) {
  /// This function is already written for you so you can see how to
  /// interact with our PNG class.
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel & pixel = image.getPixel(x, y);

      // `pixel` is a pointer to the memory stored inside of the PNG `image`,
      // which means you're changing the image directly.  No need to `set`
      // the pixel since you're directly changing the memory of the image.
      pixel.s = 0;
    }
  }

  return image;
}



/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 160 pixels away, the luminance will always decreased by 80%.
 * 
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param centerX The center x coordinate of the crosshair which is to be drawn.
 * @param centerY The center y coordinate of the crosshair which is to be drawn.
 *
 * @return The image with a spotlight.
 */
PNG createSpotlight(PNG image, int centerX, int centerY) {
	for(unsigned int i=0;i<image.width();i++){
		for(unsigned int j=0;j<image.height();j++){
			
			unsigned center_x= (unsigned) centerX;
			unsigned center_y= (unsigned) centerY;
	
			double dist_x;
			double dist_y;
			if(center_x>i){
				dist_x= center_x-i;

			} else{
				dist_x=i-center_x;

			}

			if(center_y>j){
				dist_y=center_y-j;

			}
			
			else{
				dist_y=j-center_y;

			}

			double distance=sqrt(dist_x*dist_x+dist_y*dist_y);

			double percent_decrease=1-.005*distance;

			if(percent_decrease<.2){
				percent_decrease=.2;
			}
			
			HSLAPixel & pixel= image.getPixel(i,j);
			
			pixel.l*=percent_decrease;

		}
	}
  return image;
  
}
 

/**
 * Returns a image transformed to Illini colors.
 *
 * The hue of every pixel is set to the a hue value of either orange or
 * blue, based on if the pixel's hue value is closer to orange than blue.
 *
 * @param image A PNG object which holds the image data to be modified.
 *
 * @return The illinify'd image.**/
PNG illinify(PNG image) {
	for(unsigned  int i=0;i<image.width();i++){
		for(unsigned int j=0;j<image.height();j++){
			HSLAPixel & pixel=image.getPixel(i,j);
			//std::cout<<__LINE__<<std::endl;
			unsigned int distance_blue;
			unsigned int distance_orange;
			if(pixel.h>216){
				distance_blue=pixel.h-216;
				distance_orange=(360-pixel.h)+11;
			}

			else if(pixel.h>11){
				distance_blue=216-pixel.h;
				distance_orange=pixel.h-11;

			}

			else{
				distance_blue=216-pixel.h;
				distance_orange=11-pixel.h;

			}

			pixel.h=distance_blue<distance_orange?216:11;


		}
	}
  return image;
}
 

/**
* Returns an immge that has been watermarked by another image.
*
* The luminance of every pixel of the second image is checked, if that
* pixel's luminance is 1 (100%), then the pixel at the same location on
* the first image has its luminance increased by 0.2.
*
* @param firstImage  The first of the two PNGs to be averaged together.
* @param secondImage The second of the two PNGs to be averaged together.
*
* @return The watermarked image.
*/
PNG watermark(PNG firstImage, PNG secondImage) {

unsigned int width;
unsigned int height;

if(firstImage.width()<secondImage.width()){
	width=firstImage.width();
} else{
	width=secondImage.width();

} 

if(firstImage.height()<secondImage.height()){
	height=firstImage.height();
	
}
 else{
	height=secondImage.height();
}




for(unsigned int i=0;i<width;i++){
	for(unsigned int j=0;j<height;j++){
		HSLAPixel & secondPixel= secondImage.getPixel(i,j);
		HSLAPixel &firstPixel= firstImage.getPixel(i,j);
		//std::cout<<__LINE__<<std::endl;
		if(secondPixel.l==1.0 && firstPixel.l<.8){
			firstPixel.l+=.2;

		}	
		else if(secondPixel.l==1.0 && firstPixel.l>=.8){
			firstPixel.l=1.0;
				

		}
		
	}
}

	

  return firstImage;
}
