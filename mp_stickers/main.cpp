#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
	
	Image base_picture;
	base_picture.readFromFile("license.png");
	Image picture1;
	picture1.readFromFile("fogell1.png");
	Image picture2;
	picture2.readFromFile("fogell2.png");
	Image picture3;
	picture3.readFromFile("fogell3.png");
	
	StickerSheet Fogell_Collage(base_picture,3);
	StickerSheet a=Fogell_Collage;
        Fogell_Collage=Fogell_Collage;	
	Fogell_Collage.addSticker(picture1,1,1);
	Fogell_Collage.addSticker(picture2,50,50);
	Fogell_Collage.addSticker(picture3,100,100);
	

	Image return_image=Fogell_Collage.render();

	return_image.writeToFile("myImage.png");




  	return 0;
}
