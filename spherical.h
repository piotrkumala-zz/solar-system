//
// Created by kumak98 on 09.12.2020.
//

#ifndef GRAFIKA3D_SPHERICAL_H
#define GRAFIKA3D_SPHERICAL_H

struct Spherical
{
    float distance, theta, fi;
    Spherical(float gdistance, float gtheta, float gfi) : distance(gdistance) , theta(gtheta), fi(gfi) { }
    float getX() const { return distance * std::cos(theta)*std::cos(fi); }
    float getY() const { return distance * std::sin(theta); }
    float getZ() const { return distance * std::cos(theta)*std::sin(fi); }
};
#endif //GRAFIKA3D_SPHERICAL_H
