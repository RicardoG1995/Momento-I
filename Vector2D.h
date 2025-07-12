#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>
#include <iostream>

//Clase para representar vectores bidimensionales.

class Vector2D {
public:
    float x;
    float y;

    // Constructores
    Vector2D();
    Vector2D(float xVal, float yVal);

    // Operaciones vectoriales
    float magnitude() const;
    Vector2D normalize() const;
    float dot(const Vector2D& other) const;
    Vector2D operator+(const Vector2D& other) const;
    Vector2D operator-(const Vector2D& other) const;
    Vector2D operator*(float scalar) const;
    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);

    // Utilidad
    void print() const;
};

#endif // VECTOR2D_H
