#include "particle.hpp"
#include <iostream>

Particle::Particle() : position({0, 0}), velocity({0, 0}), acceleration({0, 0}), mass(1)
{
}

Particle::Particle(Vec2 position) : position(position), velocity({0, 0}), acceleration({0, 0}), mass(1)
{
}

void Particle::ApllyForce(Vec2 force, float dt)
{
    this->acceleration = force / this->mass;
    this->velocity += this->acceleration * dt;
    this->position += this->velocity * dt;
}

Vec2 Particle::getPosition()
{
    return position;
}