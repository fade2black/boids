#pragma once

#include <vector>

class Agent{
  private:
    float x, y; // Location
    float vx, vy; // Velocity

  public:
    Agent();
    Agent(const float x, const float y, const float vx, const float vy);
    float getX() const;
    float getY() const;
    float getVx() const;
    float getVy() const;
    void setX(const float x);
    void setY(const float y);
    void setVx(const float vx);
    void setVy(const float vy);

    void update(std::vector<Agent>& neighbours, float width, float height);
};