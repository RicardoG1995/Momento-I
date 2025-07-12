#include "Vector2D.h"
#include <cmath>
#include <iostream>
using namespace std;
Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(float xVal, float yVal) : x(xVal), y(yVal) {}

float Vector2D::magnitude() const {
    return sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize() const {
    float mag = magnitude();
    if (mag == 0) return Vector2D(0, 0);
    return Vector2D(x / mag, y / mag);
}

float Vector2D::dot(const Vector2D& other) const {
    return x * other.x + y * other.y;
}

Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float scalar) const {
    return Vector2D(x * scalar, y * scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

void Vector2D::print() const {
    cout << "(" << x << ", " << y << ")" << endl;
}

