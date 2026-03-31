#pragma once

#include "agent.hpp"
#include <vector>

class Swarm {
private:
    std::vector<Agent> m_agents;
    int m_width;
    int m_height;
    
public:
    Swarm(int nboids,int width, int height);
    int getSize() const;
    Agent getAgent(int index);
    void addAgent(const Agent&);
    void update();
    const std::vector<Agent>& getAgents() const;
};