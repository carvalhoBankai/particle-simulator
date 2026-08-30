#include "particle.hpp"

Particle::Particle() : position({0, 0}), velocity({0, 0}), acceleration({0, 0}) {

}

void Particle::ApllyForce(Vec2 force, float dt)
{
    this->acceleration = force / this->mass;
    this->velocity += acceleration * dt;
    this->position += velocity * dt;
}