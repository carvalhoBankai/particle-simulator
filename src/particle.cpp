#include "particle.hpp"
#include <iostream>

Particle::Particle():
    position({0, 0}),
    velocity({0, 0}),
    acceleration({0, 0}),
    force({0, 0}), mass(1)
{
}

Particle::Particle(Vec2 position, ParticleType type): 
    position(position),
    velocity({0, 0}),
    acceleration({0, 0}),
    type(type),
    force({0, 0}), mass(1)
{
}

void Particle::ApplyForce(Vec2 _force)
{
    force += _force;
}

void Particle::setPosition(const Vec2 _position) {
    position = _position;
}

void Particle::setVelocity(const Vec2 _velocity) {
    velocity = _velocity;
}

Vec2 Particle::getVelocity() const {
    return velocity;
}

Vec2 Particle::getPosition() const {
    return position;
}

void Particle::update(float dt) {

    acceleration = force / mass;

    velocity += acceleration * dt;

    position += velocity * dt;

    force = Vec2{0, 0};
}

ParticleType Particle::getType() const {
    return type;
}