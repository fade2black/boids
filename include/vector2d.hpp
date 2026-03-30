#pragma once
#include <iostream>

class Vector2D {
  private:
    float x;
    float y;

  public:
    Vector2D();
    Vector2D(float x, float y);
    float getX() const;
    float getY() const;
    void setX(float x);
    void setY(float y);
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;

    friend std::ostream& operator<<(std::ostream& os, const Vector2D& v);
};