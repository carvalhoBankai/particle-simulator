#ifndef CONVERSION_H_
#define CONVERSION_H_

#include "particle.hpp"
#include "point.hpp"
#include <vector>

std::vector<Point> toPoints(const std::vector<Particle>& particles);

#endif