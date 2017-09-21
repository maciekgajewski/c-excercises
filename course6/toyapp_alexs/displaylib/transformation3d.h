#pragma once

#include "vector3d.h"

namespace Display {

class Transformation3D {
public:
    Transformation3D() {};
    virtual Vector3D Apply(Vector3D vertex) const = 0;
    virtual ~Transformation3D() = default;

    // TODO: implement transformation in terms of matrices and implement Combine
    // Transformation3D Combine(Transformation3D otherTransformation);
};

class Move3D: public Transformation3D {
public:
    Move3D(Vector3D move);
    Vector3D Apply(Vector3D vertex) const;
private:
    Vector3D mMove;
};

class Scale3D: public Transformation3D {
public:
    Scale3D(Vector3D scale);
    Vector3D Apply(Vector3D vertex) const;
private:
    Vector3D mScale;
};

class Rotate3D: public Transformation3D {
public:
    Rotate3D(double thetaX, double thetaY, double thetaZ);
    Vector3D Apply(Vector3D vertex) const;
private:
    double mThetaX;
    double mThetaY;
    double mThetaZ;

    Vector3D ApplyX(Vector3D vertex) const;
    Vector3D ApplyY(Vector3D vertex) const;
    Vector3D ApplyZ(Vector3D vertex) const;
};

}