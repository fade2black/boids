#include "agent.hpp"

Agent::Agent() : m_location(0, 0), m_velocity(0, 0) {}

Agent::Agent(const Vector2D& location, const Vector2D& velocity) 
    : m_location(location), m_velocity(velocity) {}
 
Vector2D Agent::getLocation() const {
    return m_location;
}

Vector2D Agent::getVelocity() const {
    return m_velocity;
}

void Agent::setLocation(const Vector2D& location) {
    m_location = location;
}   

void Agent::setVelocity(const Vector2D& velocity) {
    m_velocity = velocity;
}

void Agent::update() {
   m_location = m_location + m_velocity;
}