#include "swarm.hpp"
#include <random>
#include <vector> 


const float PROTECTED_RANGE = 15.0f;
const float VISUAL_RANGE = 250.0f;

Swarm::Swarm(int nboids, int width, int height) : m_width(width), m_height(height) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis_pos_x(1, width);
    std::uniform_real_distribution<> dis_pos_y(1, height);
    std::uniform_real_distribution<> dis_vel(-5.0f, 5.0f);

    for (int i = 0; i < nboids; ++i) {
        float x = dis_pos_x(gen);
        float y = dis_pos_y(gen);
        float vx = dis_vel(gen);
        float vy = dis_vel(gen);
      
      m_agents.emplace_back(x, y, vx, vy);
    }
}

int Swarm::getSize() const {
    return m_agents.size();
}

Agent Swarm::getAgent(int index) {
    return m_agents[index];
}

void Swarm::addAgent(const Agent& agent) {
    m_agents.push_back(agent);
}

void Swarm::update() {
    std::vector<Agent> neighbours;

    for (auto& agent : m_agents) {
        for (auto& other : m_agents) {
            if (&agent == &other) continue;

            float vx = agent.getVx() - other.getVx();
            float vy = agent.getVy() - other.getVy();
            float dist = std::sqrt(vx*vx + vy*vy);
            
            if (dist < VISUAL_RANGE) {
                neighbours.push_back(other);
            }
        }
        
        agent.update(neighbours, m_width, m_height);
        neighbours.clear();
       
        // moveTowardsCenter(agent);
        // moveAwayFromNeighbours(agent);
        // adjustVelocity(agent);
        // limitVelocity(agent);
        // keepWithinBounds(agent);
    }
}

// Cohesion: Move towards the center of mass of the swarm
// void Swarm::moveTowardsCenter(Agent& agent) {
//     Vector2D vel = agent.getVelocity();
//     Vector2D centerOfMass = computeCenterOfMass(agent);

//     vel = vel + (centerOfMass - agent.getLocation()) * CENTERING_FACTOR;
//     agent.setVelocity(vel);
// }

// // Cohesion: Adjust velocity to match the average velocity of nearby agents
// void Swarm::adjustVelocity(Agent& agent) {
//     Vector2D vel = agent.getVelocity();
//     Vector2D avgVelocity = computeAverageVelocity(agent);

//     vel = vel + (avgVelocity - vel) * VELOCITY_ADJUSTING_FACTOR;
//     agent.setVelocity(vel);
// }

// void Swarm::limitVelocity(Agent& agent) {
//     Vector2D vel = agent.getVelocity();
//     float speed = std::sqrt(vel.getX() * vel.getX() + vel.getY() * vel.getY());
    

//     if (speed > SPEED_LIMIT) {
//         vel = vel * (SPEED_LIMIT / speed);
//         agent.setVelocity(vel);
//     }
// }

// void Swarm::moveAwayFromNeighbours(Agent& agent) {
//     Vector2D loc = agent.getLocation();
//     Vector2D vel = agent.getVelocity();

//     Vector2D avoidVel(0, 0);

//     for (const auto& other : m_agents) {
//         if (&agent == &other) { continue; }

//         Vector2D otherLoc = other.getLocation();
//         float distance = loc.distanceTo(otherLoc);

//         if (distance < MARGIN) {
//              avoidVel = avoidVel + (loc - otherLoc);
//         }
//     }

//     vel = vel + avoidVel * AVOID_FACTOR;
//     agent.setVelocity(vel);
// }

// Vector2D Swarm::computeCenterOfMass(Agent& agent) const {
//     float centerX = 0;
//     float centerY = 0;
//     int numAgents = 0;

//     for (auto& neighbour : m_agents) {
//         if (&agent == &neighbour) { continue; }

//         Vector2D loc = neighbour.getLocation();
//         float dist = agent.getLocation().distanceTo(loc);
        
//         if ( dist < VISUAL_RANGE ) {
//             centerX += loc.getX();
//             centerY += loc.getY();
//             numAgents++;
//         }
//     }

//     if (numAgents > 0) {
//         centerX /= numAgents;
//         centerY /= numAgents;
//     }

//     return Vector2D(centerX, centerY);
// }

// Vector2D Swarm::computeAverageVelocity(Agent& agent) const {
//     float centerDX = 0;
//     float centerDY = 0;
//     int numAgents = 0;

//     for (const auto& neighbour : m_agents) {
//         if (&agent == &neighbour) { continue; }
        
//         float dist = agent.getLocation().distanceTo(neighbour.getLocation());
        
//         if ( dist < VISUAL_RANGE ) {
//             Vector2D vel = neighbour.getVelocity();
//             centerDX += vel.getX();
//             centerDY += vel.getY();
//             numAgents++;
//         }
//     }

//     if (numAgents > 0) {
//         centerDX /= numAgents;
//         centerDY /= numAgents;
//     }

//     return Vector2D(centerDX, centerDY);
// }

// void Swarm::keepWithinBounds(Agent& agent) {

//     Vector2D loc = agent.getLocation();
//     Vector2D vel = agent.getVelocity();

//     if (loc.getX() < MARGIN) {
//         vel.setX(vel.getX() + TURN_FACTOR);
//     }

//     if (loc.getX() > m_width - MARGIN) {
//         vel.setX(vel.getX() - TURN_FACTOR);
//     }
    
//     if (loc.getY() < MARGIN) {
//         vel.setY(vel.getY() + TURN_FACTOR);
//     }

//     if (loc.getY() > m_height - MARGIN) {
//         vel.setY(vel.getY() - TURN_FACTOR);
//     }

//     agent.setLocation(loc);
//     agent.setVelocity(vel);
// }
