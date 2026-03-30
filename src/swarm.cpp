#include "swarm.hpp"
#include <random>

#define TURN_FACTOR 1
#define MARGIN 10

Swarm::Swarm(int nboids, int width, int height) : m_width(width), m_height(height) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis1(1, width);
    std::uniform_real_distribution<> dis2(1, height);
    std::uniform_real_distribution<> dis3(-0.05, 0.05);

    for (int i = 0; i < nboids; ++i) {
      Vector2D loc(dis1(gen), dis2(gen));
      Vector2D vel(dis3(gen), dis3(gen));
      
      m_agents.emplace_back(loc, vel);
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
    
    for (auto& agent : m_agents) {
        agent.update();
        keepWithinBounds(agent);
    }
}

void Swarm::keepWithinBounds(Agent& agent) {

    Vector2D loc = agent.getLocation();
    Vector2D vel = agent.getVelocity();

    if (loc.getX() < MARGIN) {
        vel.setX(vel.getX() + TURN_FACTOR);
    }

    if (loc.getX() > m_width - MARGIN) {
        vel.setX(vel.getX() - TURN_FACTOR);
    }
    
    if (loc.getY() < MARGIN) {
        vel.setY(vel.getY() + TURN_FACTOR);
    }

    if (loc.getY() > m_height - MARGIN) {
        vel.setY(vel.getY() - TURN_FACTOR);
    }

    agent.setLocation(loc);
    agent.setVelocity(vel);
}
