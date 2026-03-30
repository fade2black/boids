#include "swarm.hpp"
#include <random>

Swarm::Swarm(int nboids, int width, int height) : m_width(width), m_height(height) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis1(1, width);
    std::uniform_real_distribution<> dis2(1, height);
    std::uniform_real_distribution<> dis3(-5, 5);

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
    }
}