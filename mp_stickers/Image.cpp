#include "Image.h"

void Image::darken(){
	unsigned width=this->width();
	unsigned height=this->height();
	
	for(unsigned x=0;x<width;x++){
		for(unsigned y=0;y<height;y++){
			cs225::HSLAPixel & pixel=this->getPixel(x,y);
			if(pixel.l<=.1){
				pixel.l=0;
			} else{
				pixel.l-=.1;
			}			
		}
	}
	

}

void Image::darken(double amount){
	unsigned width=this->width();
        unsigned height=this->height();

        for(unsigned x=0;x<width;x++){
                for(unsigned y=0;y<height;y++){
                        cs225::HSLAPixel & pixel=this->getPixel(x,y);
                        if(pixel.l<=amount){
                                pixel.l=0;
                        } else{
                                pixel.l-=amount;
                        }
                }
        }

}

void Image::desaturate(){
	unsigned width=this->width();
        unsigned height=this->height();

        for(unsigned x=0;x<width;x++){
                for(unsigned y=0;y<height;y++){
                        cs225::HSLAPixel & pixel=this->getPixel(x,y);
                        if(pixel.s>=.9){
                                pixel.s=1.0;
                        } else{
                                pixel.s+=.1;
                        }
                }
        }
}

void Image::desaturate(double amount){
        unsigned width=this->width();
        unsigned height=this->height();

        for(unsigned x=0;x<width;x++){
                for(unsigned y=0;y<height;y++){
                        cs225::HSLAPixel & pixel=this->getPixel(x,y);
                        if(pixel.s>=.9){
                                pixel.s=1.0;
                        } else{
                                pixel.s+=.1;
                        }
                }
        }

}

void Image:: grayscale(){
for (unsigned x = 0; x < this->width(); x++) {
    for (unsigned y = 0; y < this->height(); y++) {
      	cs225::HSLAPixel & pixel = this->getPixel(x, y);
	pixel.s=0;
    }
}
}

void Image:: illinify(){
	for(unsigned  int i=0;i<this->width();i++){
		for(unsigned int j=0;j<this->height();j++){
			cs225::HSLAPixel & pixel=this->getPixel(i,j);
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


}

void Image:: lighten(){
	unsigned width=this->width();
        unsigned height=this->height();

        for(unsigned x=0;x<width;x++){
                for(unsigned y=0;y<height;y++){
                        cs225::HSLAPixel & pixel=this->getPixel(x,y);
                        if(pixel.l>=.9){
                                pixel.l=1.0;
                        } else{
                                pixel.l+=.1;
                        }
                }
        }

	

}

void Image:: lighten(double amount){
	unsigned width=this->width();
        unsigned height=this->height();

        for(unsigned x=0;x<width;x++){
                for(unsigned y=0;y<height;y++){
                        cs225::HSLAPixel & pixel=this->getPixel(x,y);
                        if(pixel.l>=1-amount){
                                pixel.l=1.0;
                        } else{
                                pixel.l+=amount;
                        }
                }
        }

}

void Image:: rotateColor(double degrees){
	unsigned width=this->width();
        unsigned height=this->height();

        for(unsigned x=0;x<width;x++){
                for(unsigned y=0;y<height;y++){
                        cs225::HSLAPixel & pixel=this->getPixel(x,y);
                        double num=pixel.h+degrees;
			while(num>360.0){
				num-=360.0;
			}

			if(num<0){
				num+=360.0;

			}
			pixel.h=num;
                }
        }


}

void Image::saturate(){
	unsigned width=this->width();
        unsigned height=this->height();

        for(unsigned x=0;x<width;x++){
                for(unsigned y=0;y<height;y++){
                        cs225::HSLAPixel & pixel=this->getPixel(x,y);
                        if(pixel.s>=.9){
				pixel.s=1.0;

			} else{
				pixel.s+=.1;

			}
                }
        }
}

void Image::saturate(double amount){
        unsigned width=this->width();
        unsigned height=this->height();

        for(unsigned x=0;x<width;x++){
                for(unsigned y=0;y<height;y++){
                        cs225::HSLAPixel & pixel=this->getPixel(x,y);
                        if(pixel.s>=1.0-amount){
                                pixel.s=1.0;

                        } else{
                                pixel.s+=amount;

                        }
                }
        }
}

void Image::scale(double factor){
	unsigned  width=this->width();
	unsigned height=this->height();
	
	width= (unsigned)((double)width *factor);
	height= (unsigned)((double)height*factor);
	cs225::HSLAPixel *temp=new cs225::HSLAPixel[width*height];	

	for(unsigned i=0;i<width;i++){
		for(unsigned j=0;j<height;j++){
			unsigned og_i= (unsigned) ((double)i/factor);
			unsigned og_j= (unsigned) ((double)j/factor);

			temp[i*height+j]=this->getPixel(og_i,og_j);

		}

	}

	this->resize(width,height);

	for(unsigned i=0;i<width;i++){
		for(unsigned j=0;j<height;j++){
			this->getPixel(i,j)=temp[i*height+j];

		}

	}
	delete[] temp;
	
}

void Image::scale(unsigned w,unsigned h){
	unsigned width=this->width();
	unsigned height=this->height();
	
	double scale1= (double) w/((double)width);
	double scale2= (double) h/((double)height);

	if(scale1<scale2){
		scale(scale1);

	} else{
		scale(scale2);


	}

}
