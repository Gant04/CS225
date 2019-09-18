#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */


double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 *	Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator():image(*(new PNG()) ){
  /** @todo [Part 1] */
		Point start= Point(0,0);
	curr=start;
	tolerance=0;
  //visited=NULL;
  sentinel=false;
}

ImageTraversal::Iterator::Iterator(PNG & png,Point start,double tolerance,ImageTraversal* traverse):image(png){
    //image=png;
    this->start=start;
    this->curr=start;
    this->tolerance=tolerance;
    copy=traverse;
    //visited= new bool[png.height()*png.width()];
    /*for(unsigned int i=0;i<png.height()*png.width();i++){
        visited[i]=false;
    }*/



    sentinel=false;
    //visited[start.x*image.height()+start.y]=true;

}

bool ImageTraversal::Iterator::visitable(Point point){
	if(point.x>=image.width()){
		return false;
	}

	if(point.y>=image.height()){
		return false;
	}

  if(visited.find(point.x*image.height()+point.y)!=visited.end()){
      return false;
  }

	cs225::HSLAPixel p1=image.getPixel(start.x,start.y);
	cs225::HSLAPixel p2=image.getPixel(point.x,point.y);
	if(calculateDelta(p1,p2)>=tolerance){
		return false;
	} else{
		return true;
	}


}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  visited[curr.x*image.height()+curr.y]=true;

  if(visitable(Point(curr.x+1,curr.y))){
      copy->add(Point(curr.x+1,curr.y));

	}

	if(visitable(Point(curr.x,curr.y+1))){
      copy->add(Point(curr.x,curr.y+1));

	}

  if(visitable(Point(curr.x-1,curr.y))){
      copy->add(Point(curr.x-1,curr.y));

	}

  if(visitable(Point(curr.x,curr.y-1))){
      copy->add(Point(curr.x,curr.y-1));
  }

  if(copy->empty()==true){
    sentinel=true;
    return *this;
  }

  Point test=copy->peek();
  while(visited.find(test.x*image.height()+test.y)!=visited.end()){
      copy->pop();
      if(copy->empty()==true){
        sentinel=true;
        return *this;
      }
      test=copy->peek();
  }



  curr= copy->pop();




  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return curr;
}


/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  return other.sentinel!=this->sentinel;
}
