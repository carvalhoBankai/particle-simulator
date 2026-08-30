#include "vec2.hpp"
#include <cmath>

Vec2::Vec2(float x, float y) : x(x), y(y) {

}

Vec2 Vec2::operator+(const Vec2& other) const {
    return {x + other.x, y + other.y};
}

Vec2 Vec2::operator-(const Vec2& other) const {
    return {x - other.x, y - other.y};
}

Vec2 Vec2::operator/(const Vec2& other) const {

    if (x == 0 || y == 0) {
        return {0, 0};
    }

    return {x / other.x, y / other.y};
}

Vec2 Vec2::operator*(const float lambda) const {
    return { x * lambda, y * lambda};
}

Vec2 Vec2::operator/(const float lambda) const {
    if (lambda == 0) {
        return {0, 0};
    }

    return {x / lambda, y / lambda};
}

Vec2& Vec2::operator+=(const Vec2& other) {
    x = x + other.x;
    y = y + other.y;
    return *this;
}

double Vec2::norm() {
    return std::sqrt(x * x + y * y);
}