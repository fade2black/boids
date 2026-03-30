#pragma once

#include "vector2d.hpp"

class Agent{
  private:
    Vector2D m_location;
    Vector2D m_velocity;

  public:
    Agent();
    Agent(const Vector2D& location, const Vector2D& velocity);
    Vector2D getLocation() const;
    Vector2D  getVelocity() const;

    void update();
};