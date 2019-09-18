#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
    if((x+y)%2==0){
      return HSLAPixel(280,1,.5,1);
    }
  else{
    return HSLAPixel(98,1,.5,1);
  }
}
