/**
 * @file flower.h
 * Declaration of the Flower class.
 */

#pragma once

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

/**
 * A subclass of Drawable that can draw a flower
 */
class Flower : public Drawable
{
  private:
    Shape* stem;
    Shape* pistil; // ceter piece of flower
    Shape* leaf;

    void drawPetals(cs225::PNG* canvas, const Vector2& center, int x, int y) const;

  public:
    Flower(const Vector2& center);
    void draw(cs225::PNG* canvas) const;
    ~Flower();
};
