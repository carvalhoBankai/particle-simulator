#ifndef VEC2_H_
#define VEC2_H_

class Vec2 {
    public:
        float x;
        float y;

        Vec2(float x, float y);
        Vec2 operator+(const Vec2& other) const;
        Vec2 operator-(const Vec2& other) const;
        Vec2 operator/(const Vec2& other) const;
        Vec2& operator+=(const Vec2& other);

        // vector * lambda
        Vec2 operator*(const float lambda) const;
        // vector / lambda
        Vec2 operator/(const float lambda) const;

        double norm() const;

        double squaredNorm() const;

        Vec2 normalized() const;
};

#endif