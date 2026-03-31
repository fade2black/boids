#include "agent.hpp"
#include <vector>

const float MARGIN = 15.0f;
const float SPEED_FACTOR = 0.01f;
const float SEPARATION_RANGE = 50.0f;   // Distance to trigger Separation
const float SEPARATION_WEIGHT = 0.05f;  // Strong push away from overlap
const float COHESION_WEIGHT = 0.00001f; // Weak pull to center
const float ALIGNMENT_WEIGHT  = 0.001f;  // Match neighbor direction
const float MAX_SPEED = 3.0f;   // Limit top speed
const float MIN_SPEED = 1.0f;   // Prevent stopping
const float MIN_NUDGE_VELOCITY = 0.1f; // Small nudge value to avoid stopping
const float RECOVERY_SPEED = MIN_NUDGE_VELOCITY * std::sqrt(2);    // Target speed after nudge
const float TURN_FACTOR = 2.0f;

Agent::Agent() : x(0), y(0), vx(0), vy(0) {}

Agent::Agent(const float x, const float y, const float vx, const float vy) 
    : x(x), y(y), vx(vx), vy(vy) {}
 
float Agent::getX() const {
    return x;
}

float Agent::getY() const {
    return y;
}

float Agent::getVx() const {
    return vx;
}

float Agent::getVy() const {
    return vy;
}

void Agent::setX(const float x) {
    this->x = x;
}

void Agent::setY(const float y) {
    this->y = y;
}

void Agent::setVx(const float vx) {
    this->vx = vx;
}

void Agent::setVy(const float vy) {
    this->vy = vy;
}

void Agent::update(std::vector<Agent>& neighbours, float width, float height) {
    float repelling_dx = 0, repelling_dy = 0;
    float avgX = 0, avgY = 0;
    float avgVx = 0, avgVy = 0;

    for (auto& other : neighbours) {
        float dx = x - other.getX();
        float dy = y - other.getY();
        float dist = std::sqrt(dx*dx + dy*dy);

        if (dist < SEPARATION_RANGE) {
            repelling_dx += dx;
            repelling_dy += dy;
        }

        avgX += other.getX();
        avgY += other.getY();
        avgVx += other.getVx();
        avgVy += other.getVy();
    }

    int numNeighbours = neighbours.size();
    if (numNeighbours > 0) {
        avgX /= numNeighbours;
        avgY /= numNeighbours;
        avgVx /= numNeighbours;
        avgVy /= numNeighbours;

        // Cohesion: move toward center of mass
        vx += (avgX - x) * COHESION_WEIGHT;
        vy += (avgY - y) * COHESION_WEIGHT;

        // Alignment: move toward average velocity
        vx += (avgVx - vx) * ALIGNMENT_WEIGHT;
        vy += (avgVy - vy) * ALIGNMENT_WEIGHT;

    }

    // Separation: move away from close neighbors
    vx += repelling_dx * SEPARATION_WEIGHT;
    vy += repelling_dy * SEPARATION_WEIGHT;

    // Speed Clamping: to avoid clustering and stopping
    float speed = std::sqrt(vx*vx + vy*vy);
    if (speed > MAX_SPEED) {
        vx = (vx / speed) * MAX_SPEED;
        vy = (vy / speed) * MAX_SPEED;
    } else if (speed < MIN_SPEED) {
        if (speed == 0) {
            vx = MIN_NUDGE_VELOCITY;
            vy = MIN_NUDGE_VELOCITY;
            speed = RECOVERY_SPEED;
        }

        vx = (vx / speed) * MIN_SPEED;
        vy = (vy / speed) * MIN_SPEED;
    }

    // Keep within bounds
    if (x < MARGIN) {
        vx = vx + TURN_FACTOR;
    }

    if (x > width - MARGIN) {
        vx = vx - TURN_FACTOR;
    }
    
    if (y < MARGIN) {
        vy = vy + TURN_FACTOR;
    }

    if (y > height - MARGIN) {
        vy = vy - TURN_FACTOR;
    }


    x = x + vx * SPEED_FACTOR;
    y = y + vy * SPEED_FACTOR;
}