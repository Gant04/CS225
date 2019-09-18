#include "StickerSheet.h"
#include <iostream>

StickerSheet::StickerSheet(const Image& picture,unsigned max){
	image_array= new Image*[max];
	max_=max;
	for(unsigned i=0;i<max_;i++){
		image_array[i]=NULL;

	}

	base_picture=picture;

	x_array=new unsigned[max];
	y_array=new unsigned[max];


}



void StickerSheet::copy(const StickerSheet& other){
	base_picture=other.base_picture;
	max_=other.max_;
	image_array= new Image*[other.max_];
	x_array= new unsigned[other.max_];
	y_array=new unsigned[other.max_];
	for(unsigned i=0;i<max_;i++){
		if(other.image_array[i]!=NULL){
			Image image_copy= *(other.image_array[i]);
			image_array[i]=new Image(image_copy);
			x_array[i]=other.x_array[i];
			y_array[i]=other.y_array[i];
		}

		else{
			image_array[i]=NULL;
			x_array[i]=0;
			y_array[i]=0;
		}
	}

}

void StickerSheet::destroy(){

	for(unsigned i=0;i<max_;i++){
			if(image_array[i]!=NULL){
			delete image_array[i];
			image_array[i]=NULL;
			}
	}
	
	delete[] image_array;
	delete[] x_array;
	delete[] y_array;
	
}

StickerSheet::StickerSheet(const StickerSheet& other){
	copy(other);

}

const StickerSheet & StickerSheet::operator=(const StickerSheet& other){
	if(this!=&other){
	destroy();
	copy(other);
	}

	return *this;
}

StickerSheet::~StickerSheet(){
	destroy();
}


void StickerSheet::changeMaxStickers(unsigned max){
	Image** temp1= new Image*[max];
	unsigned* temp2=new unsigned[max];
	unsigned* temp3=new unsigned[max];

	unsigned min=(unsigned)max_<max?(unsigned) max_:max;
	for(unsigned i=0;i<min;i++){
		temp1[i]=image_array[i];
		temp2[i]=x_array[i];
		temp3[i]=y_array[i];
	}

	for(unsigned i=min;i<max;i++){
		temp1[i]=NULL;
		temp2[i]=0;
			
		temp3[i]=0;



	}

	for( unsigned i=min;i<max_;i++){
		delete image_array[i];

	}
	
	delete[] image_array;
	delete[] x_array;
	delete[] y_array;


	image_array=temp1;
	x_array=temp2;
	y_array=temp3;
	max_=max;

	
	
}

Image* StickerSheet::getSticker(unsigned index){
	if(index>=max_){
		return NULL;
	}

	return image_array[index];

	
}

void StickerSheet::removeSticker(unsigned index){

	Image* temp=image_array[index];
	image_array[index]=NULL;
	delete temp;

}

int StickerSheet::addSticker(Image& sticker,unsigned x,unsigned y){
	
	for(unsigned i=0;i<max_;i++){
		if(image_array[i]==NULL){
			image_array[i]=new Image(sticker);
			x_array[i]=x;
			y_array[i]=y;
			return i;

		}
	}

	return -1;

}

bool StickerSheet::translate(unsigned index,unsigned x,unsigned y){
	if(index>=max_|| image_array[index]==NULL){
		return false;
	}

	x_array[index]=x;
	y_array[index]=y;

	return true;
}

Image StickerSheet::render() const{

	unsigned max_width=base_picture.width();
	unsigned max_height=base_picture.height();

	Image sticker_image= Image(base_picture);

	for(unsigned i=0;i<max_;i++){
		if(image_array[i]!=NULL){
			unsigned poss_x=image_array[i]->width()+x_array[i];
			unsigned poss_y=image_array[i]->height()+y_array[i];
			
			if(poss_x>max_width){
				max_width=poss_x;	
			} 
	
			if(poss_y>max_height){
				max_height=poss_y;
			}
		}
	}

	double scale1= (double) max_width/(sticker_image.width());
	double scale2= (double) max_height/(sticker_image.height());



	sticker_image.scale((scale2>scale1?scale2:scale1));


	for(unsigned i=0;i<max_;i++){
		if(image_array[i]!=NULL){
			unsigned lower_bound_x=x_array[i];
			unsigned lower_bound_y=y_array[i];
			unsigned upper_bound_x=lower_bound_x+image_array[i]->width();
			unsigned upper_bound_y=lower_bound_y+image_array[i]->height();

			for(unsigned j=lower_bound_x;j<upper_bound_x;j++){
				for(unsigned k=lower_bound_y;k<upper_bound_y;k++){
					cs225::HSLAPixel & pixel= sticker_image.getPixel(j,k);				
					if(image_array[i]->getPixel(j-lower_bound_x,k-lower_bound_y).a==0){
						continue;
					} else{
						pixel=image_array[i]->getPixel(j-lower_bound_x,k-lower_bound_y);
					}
					
				}

			}
			
		}
	}
	
	//std::cout<< max_width<<max_height<<std::endl;
	
	return sticker_image;

}


