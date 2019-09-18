#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>


void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  	cs225::PNG IN_IMAGE;
	
	IN_IMAGE.readFromFile(inputFile);
	
	unsigned int width= IN_IMAGE.width();
	unsigned int height= IN_IMAGE.height();

	cs225::PNG OUT_IMAGE(width,height);

	for(unsigned int i=0;i<width;i++){
		for(unsigned int j=0;j<height;j++){
			OUT_IMAGE.getPixel(width-1-i,height-1-j)=IN_IMAGE.getPixel(i,j);

		}
	}
	
	OUT_IMAGE.writeToFile(outputFile);

	
}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  
	for(unsigned int i=0;i<width;i++){
		for(unsigned int j=0;j<height;j++){

			if(i-j<100){
				cs225::HSLAPixel pixel(300,1.0,.5);
                                png.getPixel(i,j)=pixel;
				
				

			}

			else if(i-j<400){
				
				//double saturation=(100.00-i+j)/100.00;
				cs225::HSLAPixel & pixel=png.getPixel(i,j);
				pixel.h=60;
				pixel.s=1.0;
				pixel.l=.5;
				pixel.a=1.0;

			}

			else if(i-j<=800){
				cs225::HSLAPixel pixel(240,1.0,.5);
				png.getPixel(i,j)=pixel;


			}

			else if(i-j>=100){
				//double saturation=(100.00+i-j)/100.00;
				cs225::HSLAPixel pixel(150,1.0,.5);
				png.getPixel(i,j)=pixel;
			}

		}

	}	



	




  return png;
}
